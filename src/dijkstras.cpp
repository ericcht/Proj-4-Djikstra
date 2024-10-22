#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <climits>
#include <algorithm>

using namespace std;

pair<int, vector<pair<int, int>>> dijkstra(const vector<vector<char>> &map, const unordered_map<char, int> &tileCost,
                                           int rows, int cols, int start_row, int start_col, int end_row, int end_col)
{
    int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}; // check all adjacent cells in map (up, down, left, right)
    vector<vector<int>> dist(rows, vector<int>(cols, INT_MAX));

    // Previous array to track the path (stores the previous cell)
    vector<vector<pair<int, int>>> previous(rows, vector<pair<int, int>>(cols, {-1, -1}));

    // Using a tuple (cost, row, col)
    priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> pq;

    // **Include the starting tile's cost**
    dist[start_row][start_col] = tileCost.at(map[start_row][start_col]);
    pq.push({dist[start_row][start_col], start_row, start_col});

    while (!pq.empty())
    {
        auto [current_cost, row, col] = pq.top();
        pq.pop();

        // Stop if we reach the destination
        if (row == end_row && col == end_col)
        {
            break;
        }

        // If we've already found a better path to this cell, skip it
        if (current_cost > dist[row][col])
        {
            continue;
        }

        // Explore neighboring cells (up, down, left, right)
        for (auto &dir : directions)
        {
            int new_row = row + dir[0], new_col = col + dir[1];

            // Check if the new position is within bounds
            if (new_row >= 0 && new_row < rows && new_col >= 0 && new_col < cols)
            {
                // **Exclude the ending tile's cost**
                int cost_to_add;
                if (new_row == end_row && new_col == end_col)
                {
                    cost_to_add = 0;
                }
                else
                {
                    cost_to_add = tileCost.at(map[new_row][new_col]);
                }
                int new_cost = current_cost + cost_to_add;

                // If a shorter path to this cell is found
                if (new_cost < dist[new_row][new_col])
                {
                    dist[new_row][new_col] = new_cost;
                    previous[new_row][new_col] = {row, col};
                    pq.push({new_cost, new_row, new_col});
                }
            }
        }
    }

    // Reconstruct the path
    vector<pair<int, int>> path;
    int r = end_row, c = end_col;
    while (r != -1 && c != -1)
    {
        path.push_back({r, c});
        auto prev = previous[r][c];
        r = prev.first;
        c = prev.second;
    }
    reverse(path.begin(), path.end());

    // The total cost is now correctly calculated without adjustments
    int total_cost = dist[end_row][end_col];

    return {total_cost, path};
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
    for (const auto &path : result.second)
    {
        int r = path.first;
        int c = path.second;
        cout << r << " " << c << endl;
    }

    return 0;
}
