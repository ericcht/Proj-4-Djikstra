#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <climits>
#include <vector>

using namespace std;
// dijsktras.cpp

// Main Execution

int main(int argc, char *argv[])
{
    int tilesNumber;
    cin >> tilesNumber;

    unordered_map<char, int> tileCost; // {symbol : cost}
    for (int i = 0; i < tilesNumber; i++)
    {
        char tileSymbol;
        int cost;
        cin >> tileSymbol >> cost;
        tileCost[tileSymbol] = cost;
    }

    int rows, cols;
    cin >> rows >> cols;

    vector<vector<char>> map(rows, vector<char>(cols)); // create graph of size rows and cols
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            cin >> map[i][j];
        }
    }

    int start_row, start_col, end_row, end_col;
    cin >> start_row >> start_col >> end_row >> end_col;

    return 0;
}
