#include <raylib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;


const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int MAZE_WIDTH = 20;
const int MAZE_HEIGHT = 15;
const int CELL_SIZE = 40;


const Color BACKGROUND_COLOR = (Color){ 200, 230, 201, 255 };  // Lighty pastel green
const Color MAZE_COLOR = DARKGREEN;
const Color PLAYER_COLOR = BLUE;
const Color TEXT_COLOR = BLACK;
const Color WIN_SCREEN_COLOR = Fade(BLACK, 0.7f);
const Color BUTTON_COLOR = (Color){ 255, 235, 59, 255 }; // Light yellow button color
const Color GOAL_COLOR = RED;


struct Player {
    string name;
    float time;
};



int maze[MAZE_HEIGHT][MAZE_WIDTH];

void MapDefine()
{
    ifstream file("map.txt");

    if (!file)
    {
        cerr << "Error opening file!" << endl;
        return;
    }

    for (int i = 0; i < MAZE_HEIGHT; i++)
    {
        for (int j = 0; j < MAZE_WIDTH; j++)
        {
            file >> maze[i][j]; 
        }
    }

    file.close();
};



vector<Player> leaderboard;
int playerX = 1, playerY = 1;
int goalX = MAZE_WIDTH - 2, goalY = MAZE_HEIGHT - 2;
float timer = 0.0f;
bool gameWon = false;
bool startScreen = true;
bool showingLeaderboard = false;
char playerName[20] = "";


void SaveLeaderboard();
void LoadLeaderboard();
void DrawMaze();
void ShowLeaderboard();
void HandlePlayerMovement();
void ResetGame();

int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Maze Game");
    SetTargetFPS(60);
    MapDefine();

    LoadLeaderboard();

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BACKGROUND_COLOR);

        if (startScreen) {
            DrawText("MAZE GAME", SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 - 50, 40, TEXT_COLOR);
            DrawText("Press ENTER to Start", SCREEN_WIDTH / 2 - 120, SCREEN_HEIGHT / 2, 20, TEXT_COLOR);
            if (IsKeyPressed(KEY_ENTER)) startScreen = false;
        } else if (showingLeaderboard) {
            ShowLeaderboard();
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                Vector2 mousePos = GetMousePosition();
                if (mousePos.x > SCREEN_WIDTH / 2 - 100 && mousePos.x < SCREEN_WIDTH / 2 + 100 &&
                    mousePos.y > SCREEN_HEIGHT - 50 && mousePos.y < SCREEN_HEIGHT - 10) {
                    ResetGame();
                }
            }
        } else if (gameWon) {
            DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, WIN_SCREEN_COLOR);
            DrawText("YOU WON!", SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 - 50, 30, WHITE);
            DrawText("Enter your name:", SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2, 20, WHITE);

            int key = GetCharPressed();
            if (key > 0 && strlen(playerName) < 19) playerName[strlen(playerName)] = (char)key;
            if (IsKeyPressed(KEY_BACKSPACE) && strlen(playerName) > 0) playerName[strlen(playerName) - 1] = '\0';

            if (IsKeyPressed(KEY_ENTER)) {
                leaderboard.push_back({playerName, timer});
                sort(leaderboard.begin(), leaderboard.end(), [](const Player &a, const Player &b) { return a.time < b.time; });
                SaveLeaderboard();
                showingLeaderboard = true;
            }
            DrawText(playerName, SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 + 30, 20, YELLOW);
        } else {
            timer += GetFrameTime();
            HandlePlayerMovement();  
            DrawMaze();
            DrawText(TextFormat("Time: %.2f seconds", timer), 10, 10, 20, TEXT_COLOR);
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}

void DrawMaze() {
    for (int y = 0; y < MAZE_HEIGHT; y++) {
        for (int x = 0; x < MAZE_WIDTH; x++) {
            if (x == goalX && y == goalY) {
                DrawRectangle(x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE, CELL_SIZE, GOAL_COLOR);
            } else {
                DrawRectangle(x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE, CELL_SIZE, maze[y][x] == 1 ? MAZE_COLOR : WHITE);
            }
        }
    }
    DrawCircle(playerX * CELL_SIZE + CELL_SIZE / 2, playerY * CELL_SIZE + CELL_SIZE / 2, 15, PLAYER_COLOR);
}

void HandlePlayerMovement() {
    if (IsKeyPressed(KEY_UP) && maze[playerY - 1][playerX] == 0) playerY--;
    if (IsKeyPressed(KEY_DOWN) && maze[playerY + 1][playerX] == 0) playerY++;
    if (IsKeyPressed(KEY_LEFT) && maze[playerY][playerX - 1] == 0) playerX--;
    if (IsKeyPressed(KEY_RIGHT) && maze[playerY][playerX + 1] == 0) playerX++;

    if (playerX == goalX && playerY == goalY) gameWon = true;
}

void ShowLeaderboard() {
    ClearBackground(BACKGROUND_COLOR);
    DrawText("LEADERBOARD", SCREEN_WIDTH / 2 - 100, 50, 30, TEXT_COLOR);

    int y = 100;
    for (auto &p : leaderboard) {
        DrawText(TextFormat("%s - %.2f", p.name.c_str(), p.time), SCREEN_WIDTH / 2 - 100, y, 20, TEXT_COLOR);
        y += 30;
    }

    
    DrawRectangle(SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT - 50, 200, 40, BUTTON_COLOR);
    DrawText("Retry", SCREEN_WIDTH / 2 - 30, SCREEN_HEIGHT - 40, 20, TEXT_COLOR);
}

void ResetGame() {
    playerX = 1;
    playerY = 1;
    timer = 0.0f;
    gameWon = false;
    startScreen = true;
    showingLeaderboard = false;
    memset(playerName, 0, sizeof(playerName));
}

void SaveLeaderboard() {
    ofstream file("leaderboard.txt");
    for (const auto &p : leaderboard) file << p.name << " " << p.time << endl;
}

void LoadLeaderboard() {
    ifstream file("leaderboard.txt");
    leaderboard.clear();
    string name;
    float time;
    while (file >> name >> time) leaderboard.push_back({name, time});
}
