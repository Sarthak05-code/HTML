import * as readline from "readline/promises";
import { stdin as input, stdout as output } from "process";

type ElementType = "Fire" | "Water" | "Electric" | "Grass";

interface Stats {
  hp: number;
  maxHp: number;
  attack: number;
  defense: number;
}

interface Item {
  readonly id: string;
  name: string;
  healAmount: number;
  quantity: number;
}

type HeroAction =
  | { kind: "attack"; targetId: string }
  | { kind: "heal"; itemId: string }
  | { kind: "defend" };

// --- ELEMENTAL SYSTEM ---
const TYPE_CHART: Record<ElementType, Partial<Record<ElementType, number>>> = {
  Fire: { Grass: 2.0, Water: 0.5 },
  Water: { Fire: 2.0, Grass: 0.5 },
  Grass: { Water: 2.0, Fire: 0.5 },
  Electric: { Water: 2.0, Grass: 0.5 },
};

function getElementalMultiplier(
  attacker: ElementType,
  defender: ElementType,
): number {
  return TYPE_CHART[attacker]?.[defender] ?? 1.0;
}

// --- ENTITY REGISTRY ---
class EntityRegistry<T extends { id: string; name: string }> {
  private entities: Map<string, T> = new Map();

  register(entity: T): void {
    this.entities.set(entity.id, entity);
  }

  get(id: string): T | undefined {
    return this.entities.get(id);
  }

  getAll(): T[] {
    return Array.from(this.entities.values());
  }

  getAlive(): T[] {
    return this.getAll().filter((e) => (e as unknown as Character).isAlive());
  }
}

// --- CHARACTER CLASS ---
class Character {
  public readonly id: string;
  public readonly name: string;
  public readonly element: ElementType;
  public isDefending: boolean = false;
  public stats: Stats;

  constructor(id: string, name: string, element: ElementType, stats: Stats) {
    this.id = id;
    this.name = name;
    this.element = element;
    this.stats = { ...stats };
  }

  public isAlive(): boolean {
    return this.stats.hp > 0;
  }

  public takeDamage(
    amount: number,
    attackerElement: ElementType,
  ): { dealt: number; multiplier: number } {
    const multiplier = getElementalMultiplier(attackerElement, this.element);
    const effectiveDefense = this.isDefending
      ? this.stats.defense * 2
      : this.stats.defense;
    const calculated =
      Math.round(amount * multiplier) - Math.floor(effectiveDefense / 2);

    const actualDamage = Math.max(1, calculated);
    this.stats.hp = Math.max(0, this.stats.hp - actualDamage);
    return { dealt: actualDamage, multiplier };
  }

  public heal(amount: number): void {
    this.stats.hp = Math.min(this.stats.maxHp, this.stats.hp + amount);
  }

  public renderHealthBar(): string {
    const totalBars = 15;
    const fill = Math.round((this.stats.hp / this.stats.maxHp) * totalBars);
    const empty = totalBars - fill;
    const bar = "█".repeat(fill) + "░".repeat(empty);
    return `[${bar}] ${this.stats.hp}/${this.stats.maxHp} HP`;
  }
}

const sleep = (ms: number) => new Promise((resolve) => setTimeout(resolve, ms));

// --- BATTLE ENGINE ---
class BattleEngine {
  private registry = new EntityRegistry<Character>();
  private inventory: Item[] = [
    { id: "i1", name: "Health Potion", healAmount: 40, quantity: 3 },
    { id: "i2", name: "Elixir", healAmount: 80, quantity: 1 },
  ];

  constructor() {
    this.registry.register(
      new Character("hero", "Cyber Knight", "Electric", {
        hp: 120,
        maxHp: 120,
        attack: 30,
        defense: 12,
      }),
    );
    this.registry.register(
      new Character("e1", "Flame Imp", "Fire", {
        hp: 60,
        maxHp: 60,
        attack: 22,
        defense: 4,
      }),
    );
    this.registry.register(
      new Character("e2", "Aqua Golem", "Water", {
        hp: 90,
        maxHp: 90,
        attack: 18,
        defense: 14,
      }),
    );
  }

  private isCriticalHit(chance: number): boolean {
    return Math.random() < chance;
  }

  private async promptAction(
    rl: readline.Interface,
    hero: Character,
  ): Promise<HeroAction> {
    console.log("\nChoose your action:");
    console.log("1. Attack");
    console.log("2. Heal (Item)");
    console.log("3. Defend");

    const choice = await rl.question("> ");

    if (choice === "2") {
      const availableItems = this.inventory.filter((i) => i.quantity > 0);
      if (availableItems.length === 0) {
        console.log("No items remaining! Defaulting to Attack.");
      } else {
        console.log("\nSelect an Item:");
        availableItems.forEach((item, idx) => {
          console.log(
            `${idx + 1}. ${item.name} (+${item.healAmount} HP) x${item.quantity}`,
          );
        });
        const itemIdx = parseInt(await rl.question("> ")) - 1;
        const selectedItem = availableItems[itemIdx] ?? availableItems[0];
        return { kind: "heal", itemId: selectedItem.id };
      }
    }

    if (choice === "3") {
      return { kind: "defend" };
    }

    // Default to Attack: Target Selection
    const enemies = this.registry.getAlive().filter((c) => c.id !== hero.id);
    console.log("\nSelect Target:");
    enemies.forEach((enemy, idx) => {
      console.log(
        `${idx + 1}. ${enemy.name} (${enemy.element}) ${enemy.renderHealthBar()}`,
      );
    });

    const targetIdx = parseInt(await rl.question("> ")) - 1;
    const target = enemies[targetIdx] ?? enemies[0];
    return { kind: "attack", targetId: target.id };
  }

  public async startBattle(): Promise<void> {
    const rl = readline.createInterface({ input, output });
    const hero = this.registry.get("hero");

    if (!hero) throw new Error("Hero not initialized!");

    console.clear();
    console.log("====================================");
    console.log("TypeScript Tactical Terminal Engine");
    console.log("====================================\n");
    await sleep(1000);

    let round = 1;

    while (hero.isAlive() && this.registry.getAlive().length > 1) {
      hero.isDefending = false; // Reset defense stance

      console.log(`\n=================== ROUND ${round} ===================`);
      console.log(
        `HERO: ${hero.name} (${hero.element}) ${hero.renderHealthBar()}`,
      );
      console.log("ENEMIES:");

      const activeEnemies = this.registry
        .getAlive()
        .filter((c) => c.id !== hero.id);
      activeEnemies.forEach((e) => {
        console.log(` - ${e.name} (${e.element}) ${e.renderHealthBar()}`);
      });

      // --- HERO TURN ---
      const action = await this.promptAction(rl, hero);

      switch (action.kind) {
        case "attack": {
          const target = this.registry.get(action.targetId);
          if (target && target.isAlive()) {
            const isCrit = this.isCriticalHit(0.25);
            const rawDamage = hero.stats.attack * (isCrit ? 1.5 : 1.0);
            const { dealt, multiplier } = target.takeDamage(
              rawDamage,
              hero.element,
            );

            let extraMsg =
              multiplier > 1
                ? " (SUPER EFFECTIVE!)"
                : multiplier < 1
                  ? " (NOT EFFECTIVE...)"
                  : "";
            if (isCrit) extraMsg += " (CRITICAL HIT!)";

            console.log(
              `\n⚔️ ${hero.name} attacks ${target.name} for ${dealt} damage!${extraMsg}`,
            );
          }
          break;
        }
        case "heal": {
          const item = this.inventory.find((i) => i.id === action.itemId);
          if (item && item.quantity > 0) {
            hero.heal(item.healAmount);
            item.quantity--;
            console.log(
              `\n🧪 ${hero.name} used ${item.name} and recovered ${item.healAmount} HP!`,
            );
          }
          break;
        }
        case "defend": {
          hero.isDefending = true;
          console.log(
            `\n🛡️ ${hero.name} takes a defensive stance! (Takes reduced damage this round)`,
          );
          break;
        }
      }

      await sleep(1000);

      // --- ENEMY TURNS ---
      const remainingEnemies = this.registry
        .getAlive()
        .filter((c) => c.id !== hero.id);

      for (const enemy of remainingEnemies) {
        if (!hero.isAlive()) break;

        const isCrit = this.isCriticalHit(0.1);
        const rawDamage = enemy.stats.attack * (isCrit ? 1.3 : 1.0);
        const { dealt, multiplier } = hero.takeDamage(rawDamage, enemy.element);

        let extraMsg =
          multiplier > 1
            ? " (SUPER EFFECTIVE!)"
            : multiplier < 1
              ? " (RESISTED)"
              : "";
        console.log(
          `💥 ${enemy.name} strikes ${hero.name} for ${dealt} damage!${extraMsg}`,
        );
        await sleep(800);
      }

      round++;
    }

    rl.close();

    console.log("\n-------------------------------------");
    if (hero.isAlive()) {
      console.log("🏆 VICTORY! All enemies defeated.");
    } else {
      console.log("💀 DEFEAT! You were vanquished.");
    }
    console.log("-------------------------------------");
  }
}

const engine = new BattleEngine();
engine.startBattle().catch((err) => console.error("Engine Failure!", err));
