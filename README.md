Project 04: Path Finding
========================

This project implements a [Dijkstra's Algorithm] to perform rudimentary path
finding on a 2D tile-based map.

[Dijkstra's Algorithm]: https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm

| N    | Elapsed Time (seconds) | Memory Usage (MB) |
|------|------------------------|-------------------|
| 10   | 0.0224938               | 1.46              |
| 20   | 0.00231933              | ...               |
| 50   | 0.0144983               | ...               |
| 100  | 0.0606514               | ...               |
| 200  | 0.25838                 | ...               |
| 500  | 1.7509                  | ...               |
| 1000 | 7.45388                 | ...               |

Input
-----

    TILES_N
    TILE_NAME_0	TILE_COST_0
    ...
    TILE_NAME_N-1	TILE_COST_N-1

    MAP_ROWS MAP_COLUMNS
    TILE_0_0    ...
    ...

    TRAVELER_START_ROW TRAVELER_START_COL
    TRAVELER_END_ROW   TRAVELER_END_COL

Output
------

    Cost
    [(ROW_0, COL_0), ...]

