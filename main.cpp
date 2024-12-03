// Small maze with 1 for free space, 5 for visited/blocked spaces, and 9 for the exit.

#include <raylib.h> 
#include <iostream>
#include <vector>
#include <cstring>
#include <fstream>


const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int MAZE_WIDTH = 20;
const int MAZE_HEIGHT = 15;
const int CELL_SIZE = 40;
const int TILE_SIZE = 50;



using namespace std;

const Color BACKGROUND_COLOR = (Color){ 200, 230, 201, 255 };  // Light pastel green
const Color MAZE_COLOR = DARKGREEN;
const Color PLAYER_COLOR = BLUE;
const Color TEXT_COLOR = BLACK;
const Color GOAL_COLOR = RED;


constexpr int SIZE = 5;

class stack {
    private:
    
    pair<int, int> arr[SIZE * SIZE];
    int top;


    public:
    stack()
    {
        top = -1;
    };

    void push(pair<int,int> value)
    {
        if (top >= SIZE * SIZE - 1)
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
    stack s;
    int startX, startY, endX, endY;
    bool searchComplete;
    string statusMessage;

public:
    Search(vector<vector<int>> m) : maze(m), searchComplete(false){
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
        s.push({startX,startY});

    }

    void searchstep() 
    {
        if (s.empty())
        {
            searchComplete = true;
            cout << "Exit Not Found. \n";
            return; 
        }   
        while(!s.empty())
        {
            int x;
            x = s.topElement().first;

            int y = s.topElement().second;

            s.pop();

            if (x == endX && y == endY)
            {
                searchComplete = true;
                statusMessage = "Exit found at (" + to_string(x) + ", " + to_string(y) + ")";
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

    };

    bool isSearchComplete()
    {
        return searchComplete;
    }

    void DrawMaze()
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        for (int i = 0; i < SIZE; ++i)
        {
            for (int j = 0; j < SIZE; ++j)
            {
                Color color;
                switch (maze[i][j])
                {   
                    case 1: color = DARKGRAY; break;
                    case 4: color = GREEN; break;
                    case 9: color = RED; break;
                    case 5: color = BLUE; break;
                    default: color = LIGHTGRAY; break; 

                }

                DrawRectangle(j * TILE_SIZE, i * TILE_SIZE, TILE_SIZE, TILE_SIZE, color);

            }
        }

        DrawText(statusMessage.c_str(), 10, SIZE * TILE_SIZE + 10, 20, DARKGRAY);

        EndDrawing();
    }
    
};

int playerX = 1, playerY = 1;
int goalX = SIZE - 2, goalY = SIZE - 2;
float timer = 0.0f;
bool gameWon = false;
bool startScreen = true;
char playerName[20] = "";

void MapDefine();
void DrawMaze();
void HandlePlayerMovement();
void ResetGame();

int main() {
    
    InitWindow(SIZE * TILE_SIZE, SIZE * TILE_SIZE, "Maze Search Visualization");
    SetTargetFPS(10);

    MapDefine();

    vector<vector<int>> maze =
    { 
    {1, 1, 1, 1, 1}, 
    {1, 5, 5, 5, 1},
    {1, 5, 1, 9, 1},
    {1, 1, 1, 5, 1},
    {4, 5, 1, 1, 1}
    };


Search search(maze);


while(!WindowShouldClose())
{
    BeginDrawing();
    ClearBackground();

    if(startScreen)

    {
        DrawText("MAZE GAME", SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 - 50, 40, TEXT_COLOR);
            DrawText("Press ENTER to Start", SCREEN_WIDTH / 2 - 120, SCREEN_HEIGHT / 2, 20, TEXT_COLOR);
            if (IsKeyPressed(KEY_ENTER)) startScreen = false;  
        } else {
            timer += GetFrameTime();  
            HandlePlayerMovement();
            DrawMaze();               
            DrawText(TextFormat("Time: %.2f seconds", timer), 10, 10, 20, TEXT_COLOR); 
        }

        search.searchstep();

        if (search.isSearchComplete())
        {
            search.DrawMaze();
        };
    
   EndDrawing();
   };


CloseWindow();


    return 0;
};
