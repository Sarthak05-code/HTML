import com.sun.management.OperatingSystemMXBean;
import java.io.File;
import java.lang.management.ManagementFactory;
import java.time.Duration;
import java.util.Comparator;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.stream.Stream;

public class SystemMonitor {

    // ANSI Escape Codes (still the cleanest way for terminal UIs)
    private static final String RESET = "\u001B[0m";
    private static final String BOLD = "\u001B[1m";
    private static final String GREEN = "\u001B[32m";
    private static final String YELLOW = "\u001B[33m";
    private static final String RED = "\u001B[31m";
    private static final String CYAN = "\u001B[36m";
    private static final String GRAY = "\u001B[90m";

    // Sampling state for per-process live CPU usage
    private static final Map<Long, Duration> PREV_CPU = new HashMap<>();
    private static final Map<Long, Long> PREV_SAMPLE = new HashMap<>();

    private record DiskInfo(String label, long total, long used, long free) {
        double usedPercent() {
            return total > 0 ? ((double) used / total) * 100.0 : 0.0;
        }
    }

    private record ProcSample(
        ProcessHandle handle,
        Duration liveCpu,
        Duration totalCpu
    ) {
        long pid() {
            return handle.pid();
        }

        String command() {
            return handle
                .info()
                .command()
                .map(SystemMonitor::extractExecutableName)
                .orElse("Unknown");
        }
    }

    public static void main(String[] args) {
        OperatingSystemMXBean osBean =
            (OperatingSystemMXBean) ManagementFactory.getOperatingSystemMXBean();

        System.out.println(
            "Starting Advanced System Monitor (Press Ctrl+C to stop)..."
        );
        sleep(1000);

        while (true) {
            clearTerminal();
            displayHeader();
            long now = System.currentTimeMillis();

            printCpu(osBean);
            printMemory(osBean);
            printSwap(osBean);
            printDisks();
            printTopProcesses(now);

            System.out.println(
                GRAY + "\nRefresh: 1.5s  |  Ctrl+C to exit" + RESET
            );
            sleep(1500);
        }
    }

    // ---------- CPU ----------
    private static void printCpu(OperatingSystemMXBean osBean) {
        double cpuLoad = Math.max(0, osBean.getCpuLoad() * 100); // -1 = not available
        String color = colorFor(cpuLoad);
        System.out.printf(
            "CPU Usage:    [%s%s%s] %s%s%.2f%%%s%n",
            color,
            bar(cpuLoad),
            RESET,
            color,
            BOLD,
            cpuLoad,
            RESET
        );
    }

    // ---------- Memory ----------
    private static void printMemory(OperatingSystemMXBean osBean) {
        long total = osBean.getTotalMemorySize();
        long used = total - osBean.getFreeMemorySize();
        double pct = ((double) used / total) * 100.0;
        String color = colorFor(pct);
        System.out.printf(
            "RAM Usage:    [%s%s%s] %s%s%.2f%%%s (%s / %s)%n",
            color,
            bar(pct),
            RESET,
            color,
            BOLD,
            pct,
            RESET,
            formatBytes(used),
            formatBytes(total)
        );
    }

    private static void printSwap(OperatingSystemMXBean osBean) {
        long total = osBean.getTotalSwapSpaceSize();
        if (total <= 0) return; // no swap on this system
        long used = total - osBean.getFreeSwapSpaceSize();
        double pct = ((double) used / total) * 100.0;
        String color = colorFor(pct);
        System.out.printf(
            "Swap Usage:   [%s%s%s] %s%s%.2f%%%s (%s / %s)%n",
            color,
            bar(pct),
            RESET,
            color,
            BOLD,
            pct,
            RESET,
            formatBytes(used),
            formatBytes(total)
        );
    }

    // ---------- All Disks (C:, D:, E:, /, /mnt/*, ...) ----------
    private static void printDisks() {
        File[] roots = File.listRoots();
        if (roots == null || roots.length == 0) {
            System.out.println(RED + "No accessible drives found!" + RESET);
            return;
        }

        for (File root : roots) {
            long total = root.getTotalSpace();
            long free = root.getFreeSpace();
            long used = total - free;
            DiskInfo d = new DiskInfo(root.getPath(), total, used, free);

            String color = colorFor(d.usedPercent());
            System.out.printf(
                "Disk %-8s [%s%s%s] %s%s%.2f%%%s (%s / %s)%n",
                d.label(),
                color,
                bar(d.usedPercent()),
                RESET,
                color,
                BOLD,
                d.usedPercent(),
                RESET,
                formatBytes(d.used()),
                formatBytes(d.total())
            );
        }
    }

    // ---------- Live Top Processes (CPU delta between samples) ----------
    private static void printTopProcesses(long now) {
        System.out.println(
            "\n" + CYAN + BOLD + "--- TOP PROCESSES (live CPU) ---" + RESET
        );
        System.out.printf(
            BOLD + "%-8s %-32s %-12s %-12s%n" + RESET,
            "PID",
            "COMMAND",
            "LIVE CPU",
            "TOTAL CPU"
        );

        List<ProcSample> top = ProcessHandle.allProcesses()
            .filter(ProcessHandle::isAlive)
            .filter(ph -> ph.info().command().isPresent())
            .map(ph -> sample(ph, now))
            .filter(p -> p.liveCpu().compareTo(Duration.ZERO) > 0)
            .sorted(Comparator.comparing(ProcSample::liveCpu).reversed())
            .limit(5)
            .toList();

        if (top.isEmpty()) {
            System.out.println(GRAY + "(sampling... wait one refresh)" + RESET);
        }

        for (ProcSample p : top) {
            System.out.printf(
                "%-8d %-32s %-12s %-12s%n",
                p.pid(),
                truncate(p.command(), 32),
                formatDuration(p.liveCpu()),
                formatDuration(p.totalCpu())
            );
        }
    }

    private static ProcSample sample(ProcessHandle ph, long now) {
        Duration total = ph.info().totalCpuDuration().orElse(Duration.ZERO);
        Duration prevTotal = PREV_CPU.getOrDefault(ph.pid(), total);
        long prevTime = PREV_SAMPLE.getOrDefault(ph.pid(), now);
        long elapsedMs = Math.max(now - prevTime, 1);

        // Live CPU% over the sampling window (delta of CPU time vs wall-clock)
        Duration liveCpu = total.minus(prevTotal);
        PREV_CPU.put(ph.pid(), total);
        PREV_SAMPLE.put(ph.pid(), now);

        // Store the live percentage scaled, so sorting reflects real load
        Duration scaledLive = Duration.ofMillis(
            (long) (((liveCpu.toMillis() * 100.0) / elapsedMs) * 1_000)
        );
        return new ProcSample(ph, scaledLive, total);
    }

    // ---------- Helpers ----------
    private static String extractExecutableName(String path) {
        int idx = Math.max(path.lastIndexOf('/'), path.lastIndexOf('\\'));
        return idx >= 0 ? path.substring(idx + 1) : path;
    }

    private static String truncate(String text, int max) {
        return text.length() <= max ? text : text.substring(0, max - 3) + "...";
    }

    private static String colorFor(double pct) {
        return switch ((int) (pct / 25)) {
            case 0, 1 -> GREEN; // 0–49%
            case 2 -> YELLOW; // 50–74%
            default -> RED; // 75%+
        };
    }

    private static String bar(double pct) {
        int filled = (int) Math.round((pct / 100.0) * 20);
        return "=".repeat(filled) + ".".repeat(20 - filled);
    }

    private static String formatDuration(Duration d) {
        long h = d.toHours();
        long m = d.toMinutesPart();
        long s = d.toSecondsPart();
        if (h > 0) return "%dh %dm".formatted(h, m);
        if (m > 0) return "%dm %ds".formatted(m, s);
        return "%ds".formatted(s);
    }

    private static String formatBytes(long bytes) {
        if (bytes >= 1L << 40) return "%.2f TB".formatted(
            bytes / (double) (1L << 40)
        );
        if (bytes >= 1L << 30) return "%.2f GB".formatted(
            bytes / (double) (1L << 30)
        );
        if (bytes >= 1L << 20) return "%.2f MB".formatted(
            bytes / (double) (1L << 20)
        );
        return "%.2f KB".formatted(bytes / (double) (1L << 10));
    }

    private static void clearTerminal() {
        System.out.print("\033[H\033[2J");
        System.out.flush();
    }

    private static void displayHeader() {
        System.out.println(
            CYAN +
                BOLD +
                """
                =========================================================
                                 LIVE SYSTEM MONITOR (Java 26)
                =========================================================""" +
                RESET
        );
    }

    private static void sleep(long millis) {
        try {
            Thread.sleep(millis);
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }
    }
}
