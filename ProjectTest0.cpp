// Small maze with 1 for free space, 5 for visited/blocked spaces, and 9 for the exit.


#include <iostream>
#include <vector>

static const int MAX_SIZE = 100;

using namespace std;

constexpr int SIZE = 5;

class stack {
    private:
    
    pair<int, int> arr[MAX_SIZE];
    int top;


    public:
    stack()
    {
        top = -1;
    };

    void push(pair<int,int> value)
    {
        if (top >= MAX_SIZE - 1)
        {
            cout << "Stack Full!" << endl;
            return;
        }
        arr[++top] = value;
    };

    pair <int,int> pop() 
    {
        if (top < 0)
        {
            cout << "Stack Undeflow!" << endl;
            return {-1,-1};
        }

        return arr[top--];
    };

    
    pair <int,int> topElement() 
    {
        if (top < 0)
        {
            cout << "Stack Empty!" << endl;
            return {-1,-1};
        }

        return arr[top];
    };

    bool empty()
    {
        return top < 0;
    }
    

};

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

    void search() 
    {
        stack s;
        s.push({startX, startY}); 
        
        while(!s.empty())
        {
            int x;
            x = s.topElement().first;

            int y = s.topElement().second;

            s.pop();

            if (x == endX && y == endY)
            {
                cout << "Exit found at (" << x << ", " << y << ")\n";
                return;
            };

            maze[x][y] = 5;

            if ( x-1 >= 0 && maze[x - 1][y] == 1) 
            {
                s.push({x -1, y});
            };
            if (x + 1 < SIZE && maze[x + 1][y] == 1) 
            {
                s.push({x + 1, y});
            };
            if (y - 1 >= 0 && maze[x][y - 1] == 1) 
            {
                s.push({x, y - 1});
            };
            if (y + 1 < SIZE && maze[x][y + 1] == 1) 
            {
                s.push({x, y + 1});
            };

        };

    }

    
};

int main() {
    
    vector<vector<int>> maze =
    { 
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
