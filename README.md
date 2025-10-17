# so_long

A small 2D tile-based game written in C with MiniLibX (X11). Navigate a maze, collect all collectibles, avoid enemies, and reach the exit. After collecting the last collectible, you must take an optimal path to the exit, deviating from the shortest path results in a loss.

## Overview

- Rendering with MiniLibX (Linux/X11) using 50×50 px tiles
- Smooth viewport following the player on large maps
- Animated sprites for player, enemies, and exit
- Enemies patrol randomly and chase the player with A* pathfinding
- Map parsing and validation with detailed error messages
- Move counter overlay and pause mode

## Requirements

- Linux with X11 available (Xorg)
- X11 runtime libraries (dev packages only required if you rebuild MLX)
- A standard C toolchain (`cc`, `make`)

This repository vendors MiniLibX and a custom `libft`, so you do not need network access to build.

## Build

```bash
make
```

Artifacts:
- Executable: `./so_long`
- Clean object files: `make clean`
- Clean objects + binary: `make fclean`
- Rebuild from scratch: `make re`

## Run

```bash
./so_long maps/map5.ber
```

You can try any of the sample maps under `maps/` (e.g., `map1.ber`, `map5.ber`, `pacman.ber`).

## Controls (Linux)

- Arrow keys: move
- Space: pause/resume
- ESC: quit

Notes:
- The exit activates (is rendered) only after all collectibles are gathered.
- Enemies patrol between random points and will chase when close.
- Getting caught (adjacent to an enemy) leads to a loss after a short hit animation.

## Game Rules and Win Condition

1. Collect all collectibles (`C`).
2. After you pick up the last collectible, the game computes the shortest path length to the exit using A*.
3. From that moment, every move you make is counted toward your “route to exit”.
4. Reach the exit (`E`) with exactly the same number of moves as the optimal path to win. Any deviation results in a loss.

## Map Format (`.ber`)

- Text-based grid using these characters:
  - `1`: wall (blocked)
  - `0`: free space
  - `C`: collectible
  - `P`: player start (exactly one)
  - `E`: exit (exactly one)
  - `N`: enemy (zero or more)
- Rules validated at startup:
  - Map is rectangular
  - Map is closed (outer borders are all `1`)
  - Exactly one `P` and one `E`, at least one `C`
  - All collectibles and the exit are reachable from the player

Example (`maps/map1.ber`):
```
111111
10P0C1
100001
100001
100001
100001
100001
100001
100001
100001
10E0N1
111111
```

## Project Structure

- `srcs/`: game source files
  - `parsing/`: `.ber` map loading and validation (shape, walls, elements, reachability)
  - `init_game/`: initialization of MLX, window, sprites, and game state
  - `render/`: drawing routines
    - `draw/`: static tiles, animated sprites, HUD (moves)
    - `viewport/`: camera centering on the player and bounds
    - `load_img/`: loading XPM textures (player, enemy, exit, walls, floor, coins)
  - `handle_game/`: main loop, input hooks, movement, patrol, chase, end conditions
  - `a_star_search/`: A* with a binary-heap priority queue for pathfinding
  - `utils/`: error handling and cleanup
- `include/`: headers (`so_long.h`, `assets_paths.h`)
- `assets/`: XPM textures (player, enemy, exit, walls, ground, collectibles)
- `maps/`: sample and invalid maps
- `mlx/`: MiniLibX (Linux) sources and prebuilt static libraries
- `libft/`: custom utility library used by the project

## Technical Notes

- Window size: 1600×1200, tile size: 50×50 (tweakable in `include/so_long.h`)
- Viewport follows the player while clamping to map bounds
- Animated sprites advance based on clock ticks (no frame cap dependency)
- Enemy behavior:
  - Patrol between randomly generated valid points within a range
  - Switch to chase mode when within a Manhattan distance threshold
  - Movement is rate-limited by a configurable delay
- A* pathfinding:
  - Manhattan distance heuristic on a 4-neighbor grid
  - Custom min-heap priority queue

## Errors and Exit Codes

- Invalid usage (wrong number of args) prints an error to `stderr` and exits with failure
- Map validation failures print a precise “Error\n...” message before exiting
- Runtime failures (e.g., MLX/image allocation) print an error and exit cleanly

## Developing and Tweaking

- Change assets or paths in `include/assets_paths.h`
- Adjust window and tile sizes, keycodes, and AI constants in `include/so_long.h`
- Add your own maps under `maps/`, then run `./so_long maps/your_map.ber`

## Credits

- Graphics framework: MiniLibX (included under `mlx/`)
- Utility library: `libft` (included)

If you want a macOS build section, Windows notes, or screenshots/GIFs added, let me know your target platform and I’ll extend this README accordingly.

