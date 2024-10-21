#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <climits>
#include <vector>
#include <algorithm>

using namespace std;

pair<int, vector<pair<int, int>>> dijkstra(const vector<vector<char>> &map, const unordered_map<char, int> &tileCost,
                                           int rows, int cols, int start_row, int start_col, int end_row, int end_col)
{
    int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}; // check all adjacent cells in map (left, right, up, down)
    vector<vector<int>> dist(rows, vector<int>(cols, INT_MAX));

    // Previous array to track the path (stores the previous cell)
    vector<vector<pair<int, int>>> previous(rows, vector<pair<int, int>>(cols, {-1, -1}));

    // Using a tuple (cost, row, col)
    priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> pq;

    dist[start_row][start_col] = 0;
    pq.push({0, start_row, start_col});
}

int main()
{
    int tiles_n;
    cin >> tiles_n;

    unordered_map<char, int> tile_cost;
    for (int i = 0; i < tiles_n; ++i)
    {
        char tile_name;
        int cost;
        cin >> tile_name >> cost;
        tile_cost[tile_name] = cost;
    }

    int rows, cols;
    cin >> rows >> cols;

    vector<vector<char>> map(rows, vector<char>(cols));
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            cin >> map[i][j];
        }
    }

    int start_row, start_col, end_row, end_col;
    cin >> start_row >> start_col >> end_row >> end_col;

    // Call Dijkstra's algorithm
    auto result = dijkstra(map, tile_cost, rows, cols, start_row, start_col, end_row, end_col);

    // Output the total cost
    cout << result.first << endl;

    // Output the path
    for (const auto &p : result.second)
    {
        int r = p.first, c = p.second;
        char tile = map[r][c];                    // Get the tile character at the current position
        int tile_cost_value = tile_cost.at(tile); // Correct way to access the cost

        // Print the position and the cost of the tile
        cout << r << " " << c << " (Tile: " << tile << ", Cost: " << tile_cost_value << ")" << endl;
    }

    return 0;
}
