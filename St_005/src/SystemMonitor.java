import com.sun.management.OperatingSystemMXBean;
import java.io.File;
import java.lang.management.ManagementFactory;
import java.util.Comparator;
import java.util.List;
import java.util.Optional;

public class SystemMonitor {

    // ANSI Color Escape Codes
    private static final String RESET = "\u001B[0m";
    private static final String BOLD = "\u001B[1m";
    private static final String GREEN = "\u001B[32m";
    private static final String YELLOW = "\u001B[33m";
    private static final String RED = "\u001B[31m";
    private static final String CYAN = "\u001B[36m";

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

            // 1. CPU Metric
            double cpuLoad = osBean.getCpuLoad() * 100;
            if (cpuLoad < 0) cpuLoad = 0;
            String cpuColor = getColorForPercentage(cpuLoad);

            System.out.printf(
                "CPU Usage:    [%s%s%s] %s%.2f%%%s\n",
                cpuColor,
                getProgressBar(cpuLoad),
                RESET,
                cpuColor + BOLD,
                cpuLoad,
                RESET
            );

            // 2. RAM Metrics
            long totalMemory = osBean.getTotalMemorySize();
            long freeMemory = osBean.getFreeMemorySize();
            long usedMemory = totalMemory - freeMemory;
            double ramPercent = ((double) usedMemory / totalMemory) * 100;
            String ramColor = getColorForPercentage(ramPercent);

            System.out.printf(
                "RAM Usage:    [%s%s%s] %s%.2f%%%s (%s / %s)\n",
                ramColor,
                getProgressBar(ramPercent),
                RESET,
                ramColor + BOLD,
                ramPercent,
                RESET,
                formatBytes(usedMemory),
                formatBytes(totalMemory)
            );

            // 3. Disk Space Metrics
            File root = new File("/");
            long totalDisk = root.getTotalSpace();
            long freeDisk = root.getFreeSpace();
            long usedDisk = totalDisk - freeDisk;
            double diskPercent = ((double) usedDisk / totalDisk) * 100;
            String diskColor = getColorForPercentage(diskPercent);

            System.out.printf(
                "Disk Usage:   [%s%s%s] %s%.2f%%%s (%s / %s)\n",
                diskColor,
                getProgressBar(diskPercent),
                RESET,
                diskColor + BOLD,
                diskPercent,
                RESET,
                formatBytes(usedDisk),
                formatBytes(totalDisk)
            );

            // 4. Top Active Processes Section
            displayTopProcesses();

            System.out.println(
                "\n---------------------------------------------------------"
            );

            sleep(1500); // Slightly longer delay to allow process sampling
        }
    }

    private static void displayTopProcesses() {
        System.out.println(
            "\n" + CYAN + BOLD + "--- TOP ACTIVE PROCESSES ---" + RESET
        );
        System.out.printf(
            BOLD + "%-8s %-30s %-15s\n" + RESET,
            "PID",
            "COMMAND",
            "CPU TIME"
        );

        // Fetch all system processes via Java 9 ProcessHandle
        List<ProcessHandle> topProcesses = ProcessHandle.allProcesses()
            .filter(ProcessHandle::isAlive)
            .filter(ph -> ph.info().command().isPresent()) // Filter out OS background threads with no name
            .sorted(
                Comparator.comparing((ProcessHandle ph) ->
                    ph.info().totalCpuDuration().orElse(java.time.Duration.ZERO)
                ).reversed()
            ) // Sort by highest cumulative CPU time
            .limit(5)
            .toList();

        for (ProcessHandle ph : topProcesses) {
            long pid = ph.pid();
            ProcessHandle.Info info = ph.info();

            // Extract binary name from full executable path
            String fullPath = info.command().orElse("Unknown");
            String commandName = extractExecutableName(fullPath);

            // CPU time formatting
            String cpuTime = info
                .totalCpuDuration()
                .map(d ->
                    String.format("%dm %ds", d.toMinutes(), d.toSecondsPart())
                )
                .orElse("N/A");

            System.out.printf(
                "%-8d %-30s %-15s\n",
                pid,
                truncate(commandName, 30),
                cpuTime
            );
        }
    }

    private static String extractExecutableName(String path) {
        int lastSeparator = Math.max(
            path.lastIndexOf('/'),
            path.lastIndexOf('\\')
        );
        return lastSeparator >= 0 ? path.substring(lastSeparator + 1) : path;
    }

    private static String truncate(String text, int maxLength) {
        if (text.length() <= maxLength) return text;
        return text.substring(0, maxLength - 3) + "...";
    }

    private static String getColorForPercentage(double percentage) {
        if (percentage >= 80.0) return RED;
        if (percentage >= 50.0) return YELLOW;
        return GREEN;
    }

    private static String getProgressBar(double percentage) {
        int totalBlocks = 20;
        int filledBlocks = (int) Math.round((percentage / 100.0) * totalBlocks);

        StringBuilder bar = new StringBuilder();
        for (int i = 0; i < totalBlocks; i++) {
            bar.append(i < filledBlocks ? "=" : ".");
        }
        return bar.toString();
    }

    private static String formatBytes(long bytes) {
        double gb = bytes / (1024.0 * 1024.0 * 1024.0);
        if (gb >= 1.0) return String.format("%.2f GB", gb);
        double mb = bytes / (1024.0 * 1024.0);
        return String.format("%.2f MB", mb);
    }

    private static void clearTerminal() {
        System.out.print("\033[H\033[2J");
        System.out.flush();
    }

    private static void displayHeader() {
        System.out.println(
            CYAN +
                BOLD +
                "========================================================="
        );
        System.out.println(
            "                 LIVE SYSTEM MONITOR                     "
        );
        System.out.println(
            "=========================================================" + RESET
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
