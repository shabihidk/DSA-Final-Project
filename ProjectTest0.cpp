// Small maze with 1 for free space, 5 for visited/blocked spaces, and 9 for the exit.


#include <iostream>
#include <vector>
#include <stack>

using namespace std;

constexpr int SIZE = 5;

class Search {
private:
    vector<vector<int>> maze;
    int startX, startY, endX, endY;

public:
    Search(vector<vector<int>> m) : maze(m) {
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                if (maze[i][j] == 4) {
                    startX = i;
                    startY = j;
                }
                if (maze[i][j] == 9) {
                    endX = i;
                    endY = j;
                }
            }
        }
    }

    void search() {
        stack<pair<int, int>> s;
        s.push({startX, startY});

        while (!s.empty()) {
            int x = s.top().first;
            int y = s.top().second;
            s.pop();

            if (x == endX && y == endY) {
                cout << "Exit found at (" << y << ", " << x << ")\n";
                return;
            }

            maze[x][y] = 5;

            if (x - 1 >= 0 && maze[x - 1][y] == 1) s.push({x - 1, y});
            if (x + 1 < SIZE && maze[x + 1][y] == 1) s.push({x + 1, y});
            if (y - 1 >= 0 && maze[x][y - 1] == 1) s.push({x, y - 1});
            if (y + 1 < SIZE && maze[x][y + 1] == 1) s.push({x, y + 1});
        }

        cout << "No path found.\n";
    }
};

int main() {
    vector<vector<int>> maze = {
        {1, 1, 1, 1, 1},
        {1, 5, 5, 5, 1},
        {1, 5, 1, 9, 1},
        {1, 1, 1, 5, 1},
        {4, 5, 1, 1, 1}
    };

    Search search(maze);
    search.search();

    return 0;
}
