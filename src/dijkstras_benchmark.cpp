#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <climits>
#include <algorithm>
#include <chrono>  // for benchmarking
#include <cstdlib> // for random number generation
#include <ctime>   // for seeding random number generator

using namespace std;

// Dijkstra's algorithm implementation
pair<int, vector<pair<int, int>>> dijkstra(const vector<vector<char>> &map, const unordered_map<char, int> &tileCost,
                                           int rows, int cols, int start_row, int start_col, int end_row, int end_col)
{
    int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}; // check all adjacent cells in map (up, down, left, right)
    vector<vector<int>> dist(rows, vector<int>(cols, INT_MAX));
    vector<vector<pair<int, int>>> previous(rows, vector<pair<int, int>>(cols, {-1, -1}));
    priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> pq;

    dist[start_row][start_col] = tileCost.at(map[start_row][start_col]);
    pq.push({dist[start_row][start_col], start_row, start_col});

    while (!pq.empty())
    {
        auto [current_cost, row, col] = pq.top();
        pq.pop();

        if (row == end_row && col == end_col) break;
        if (current_cost > dist[row][col]) continue;

        for (auto &dir : directions)
        {
            int new_row = row + dir[0], new_col = col + dir[1];
            if (new_row >= 0 && new_row < rows && new_col >= 0 && new_col < cols)
            {
                int cost_to_add = (new_row == end_row && new_col == end_col) ? 0 : tileCost.at(map[new_row][new_col]);
                int new_cost = current_cost + cost_to_add;

                if (new_cost < dist[new_row][new_col])
                {
                    dist[new_row][new_col] = new_cost;
                    previous[new_row][new_col] = {row, col};
                    pq.push({new_cost, new_row, new_col});
                }
            }
        }
    }

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
    int total_cost = dist[end_row][end_col];

    return {total_cost, path};
}

// Generate an NxN map with random tiles
vector<vector<char>> generate_map(int N, vector<char> tiles)
{
    vector<vector<char>> map(N, vector<char>(N));
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            map[i][j] = tiles[rand() % tiles.size()]; // pick random tile
        }
    }
    return map;
}

// Function to run Dijkstra's algorithm and measure time
void benchmark_dijkstra(int N, unordered_map<char, int> &tileCost)
{
    vector<char> tiles = {'A', 'B', 'C', 'D'}; // example tile types
    vector<vector<char>> map = generate_map(N, tiles);

    int start_row = 0, start_col = 0, end_row = N - 1, end_col = N - 1;

    auto start_time = chrono::high_resolution_clock::now();

    auto result = dijkstra(map, tileCost, N, N, start_row, start_col, end_row, end_col);

    auto end_time = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed_time = end_time - start_time;

    cout << "N = " << N << ": Elapsed time: " << elapsed_time.count() << " seconds" << endl;
}

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        cout << "Usage: " << argv[0] << " <map size>" << endl;
        return 1;
    }

    int N = atoi(argv[1]); // Get the map size from the command line argument
    srand(time(0)); // seed for random number generation

    unordered_map<char, int> tileCost;
    tileCost['A'] = 1;
    tileCost['B'] = 2;
    tileCost['C'] = 3;
    tileCost['D'] = 4;

    benchmark_dijkstra(N, tileCost);

    return 0;
}
