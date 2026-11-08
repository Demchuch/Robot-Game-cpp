# Robot Game (C++)

A console turn-based tactical game written in C++20 as a university OOP project. You control a robot on a grid: move, fight enemy robots, fight alongside an ally, use abilities and level up. Enemies and allies are driven by a simple AI, a factory keeps spawning new enemies, cells can carry hidden effects, and a fog of war limits what you can see.

The main goal of the project is not the game itself but the design: every class has one responsibility, guards its own invariants, and depends only on classes "below" it.

## Gameplay

At the start you pick one of four abilities. Then enter a command and press Enter:

| Key | Action |
| --- | --- |
| `w` `a` `s` `d` | move up / left / down / right (or attack / heal when the cell is occupied) |
| `1`-`4` | use the ability in the given slot (only slots you already own) |
| `m` | switch display mode |
| `e` | end turn |

- Every action costs energy; a step also spends speed equal to the cell's movement cost (slow cells are drawn as yellow dots and cost 3).
- Moving into an enemy attacks it, moving into an ally heals it.
- Killing an enemy gives experience; a new rank raises health, attack and energy, and lets you pick a reward: a new ability or an upgrade of one you already have.
- After your turn all enemies and allies move, then factories may spawn new enemies, then statuses tick.
- You win when no enemies are left, and lose when your robot dies.

Symbols: `P` player, `A` ally, `E` enemy, `F` factory, `#` wall.

### Abilities

All abilities implement the `Ability` interface. Abilities that need a target ask for an offset `rows cols` relative to the player.

| Ability | Target | Effect | Upgrade |
| --- | --- | --- | --- |
| Area strike | no | damages every hostile robot within radius 1, applies **Overload** | radius +1 |
| Ranged strike | yes, radius 3 | damages one hostile robot, applies **Burn** | damage +10 |
| Heal | no | restores health; overheal turns into a **Shield** | heal +5 |
| Teleport | yes, radius 5 | moves the robot to a free walkable cell | energy cost -10 (min 10) |

### Statuses

Statuses are attached to robots through the `Status` interface. Applying a status the robot already has stacks it instead of adding a second copy.

| Status | Effect |
| --- | --- |
| Slow | blocks movement for a number of turns (stacks add turns) |
| Overload | blocks the next ability attempt, then disappears |
| Burn | 5 damage at the end of each turn for 3 turns |
| Shield | absorbs damage until its capacity runs out |

Some cells hold hidden statuses (about 10% of cells get one or two). When a robot steps on such a cell, it receives them and one of them is removed from the cell. Display mode `m` cycles through: standard, enemies highlighted, impassable cells highlighted, cells with statuses highlighted.

## Architecture

Dependencies point strictly downward; there are no include cycles.

| Layer | Classes | Responsibility |
| --- | --- | --- |
| Data | `Team`, `Cell`, `GameField`, `Robot`, `RobotFactory` | State of the world, invariants |
| Behaviour | `Ability` (+ 4 implementations, `AbilityFactory`), `Status` (+ 4 implementations, `StatusFactory`) | Abilities and effects on robots |
| Rules | `MovementSystem` | Is a step or attack allowed, and what happens |
| Control | `GameLoop`, `EnemyController` | Turn order, player input, AI |
| View | `Visualizer`, `DisplayMode` | Draws a frame, read-only |

Design decisions worth a look:

- **Cell vs. field.** `Cell` stores one cell's state, `GameField` owns the geometry and bounds checks, so every check is written exactly once. `GetCell` returns `const Cell&`, so a cell cannot be changed bypassing the field.
- **Two visibility flags.** `known` is only ever switched on (explored map stays), `visible` is recomputed after every player action.
- **Polymorphism for abilities and statuses.** `Robot` stores `std::shared_ptr<Ability>` and `std::shared_ptr<Status>` and never checks concrete types. A new ability or status is a new class plus one `case` in its factory.
- **Statuses hook into the robot's life cycle.** `OnTurnEnd`, `AbsorbDamage`, `BlocksMovement`, `BlocksAbilities` and `IsExpired` let a status change behaviour without `Robot` knowing which status it is.
- **`Visualizer` only reads.** `Draw` is `const` and takes `const` references, so rendering cannot change the game and the model never prints anything.
- **Movement is not part of `Robot`.** The decision "may I step here, and what happens if someone is there" depends on the robot, the field and the neighbour at once. A refused action never spends resources.
- **AI is separate from the loop.** `EnemyController` talks to the field only through `MovementSystem`: each enemy or ally moves toward the nearest hostile robot. Enemies get a random Heal or Teleport and use it by simple thresholds (low health, long distance).
- **Factory returns a robot, the loop adds it.** Adding to the `std::vector` outside the AI loop keeps pointers to robots valid.
- **No magic numbers.** All numbers, keys and symbols live in `config/game_constants.h`.

Patterns actually used: game loop, model/view separation, constructor dependency injection, polymorphism (`Ability`, `Status`), simple factories (`RobotFactory`, `AbilityFactory`, `StatusFactory`).

## Build and run

Requires a C++20 compiler.

**CMake** (also works directly in CLion):

```
cmake -S . -B build
cmake --build build
./build/OOP        # on Windows with Visual Studio generators: build\Debug\OOP.exe
```

**Plain g++:**

```
g++ -std=c++20 -I. main.cpp robot/*.cpp cell/*.cpp gamefield/*.cpp movement/*.cpp gameloop/*.cpp visualizer/*.cpp robotfactory/*.cpp enemycontroller/*.cpp ability/*.cpp status/*.cpp -o game
./game
```

The terminal must support ANSI colors (Windows Terminal, PowerShell 7, most Linux/macOS terminals).

## Project structure

```
main.cpp              sets up the field, robots and factory, starts the game
config/               game constants (numbers, keys, symbols)
robot/, cell/, gamefield/, robotfactory/      data layer
ability/              Ability interface, 4 abilities, AbilityFactory
status/               Status interface, 4 statuses, StatusFactory
movement/             movement and attack rules
gameloop/, enemycontroller/                   turn order, input, AI
visualizer/           console rendering and display modes
```
