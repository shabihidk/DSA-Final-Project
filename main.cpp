#include <raylib.h>
#include <iostream>
#include <vector>
#include <cstring>
#include <fstream>
#include <algorithm>
#include <unistd.h>

using namespace std;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int MAZE_WIDTH = 20;
const int MAZE_HEIGHT = 15;
const int CELL_SIZE = 40;

const Color BACKGROUND_COLOR = (Color){ 200, 230, 201, 255 };  // Light pastel green
const Color MAZE_COLOR = DARKGREEN;
const Color PLAYER_COLOR = BLUE;
const Color TEXT_COLOR = BLACK;
const Color WIN_SCREEN_COLOR = Fade(BLACK, 0.7f);
const Color BUTTON_COLOR = (Color){ 255, 235, 59, 255 };
const Color GOAL_COLOR = RED;

int maze[MAZE_HEIGHT][MAZE_WIDTH];

vector<pair<int, int>> aStarPath;
size_t aStarIndex = 0;


struct Player {
    string name;
    float time;
    Player(string playerName, float playerTime) {
        name = playerName;
        time = playerTime;
    }

    Player() : name(""), time(0.0f) {}
};

// Maze array definition (to be populated by MapDefine function)

class Node {
public:
    float time;
    string name;
    Node* next;

    Node(float t, const string& n) : time(t), name(n), next(nullptr) {}
};

class Linkedlist { 
private:
    Node* head = nullptr;
    Node* tail = nullptr;

public:
    void AddTail(float time, std::string name) {
        Node* newNode = new Node(time, name);

        if (!tail) {
            head = newNode;
        } else {
            tail->next = newNode;
        }
        tail = newNode;
        tail->next = head;  // Ensure circular linking to the head
    }

    void Display() {
        InitWindow(800, 600, "Leaderboard");
        SetTargetFPS(60);  // Limit to 60 frames per second

        while (!WindowShouldClose()) {
            BeginDrawing();
            ClearBackground(RAYWHITE);

            DrawText("Leaderboard", 350, 20, 30, DARKGRAY);

            if (head == nullptr) {
                DrawText("Empty List", 10, 50, 20, RED);
            } else {
                Node* temp = head;
                int y = 50;
                bool first = true;
                while (temp) {
                    std::string displayText = temp->name + " : " + std::to_string(temp->time) + " seconds";
                    DrawText(displayText.c_str(), 10, y, 20, BLACK);
                    y += 30;

                    temp = temp->next;

                    if (temp == head && !first) break;
                    first = false;
                }
            }

            EndDrawing();
        }

        CloseWindow();  // Close the window after the loop ends
    }

    Node* GetHead() const {
        return head;
    }

    Node* GetTail() const {
        return tail;
    }

    void RemoveHead() {
        if (!head) return;

        Node* temp = head;
        head = head->next;

        delete temp;
    }

    void RemoveTail() {
        if (!head) return;

        Node* temp2 = tail;
        Node* temp = head;

        while (temp->next != tail) {
            temp = temp->next;
        }

        temp->next = nullptr;
        tail = temp->next;

        delete temp2;
    }
};

class Queue {
private:
    Linkedlist list;

public:
    void Enqueue(float time, string name) {
        list.AddTail(time, name);
    }

    void Display() {
        list.Display();
        sleep(10);
    }
};

class BinarySearchTree {
    struct NodeT {
        float time;
        string name;
        NodeT* left;
        NodeT* right;

        NodeT(float t, string n) : time(t), name(n), left(nullptr), right(nullptr) {}
    };

    NodeT* root = nullptr;

    void DescendingOutput(NodeT* root) {
        if (root == nullptr) return;
        DescendingOutput(root->right);
        cout << root->name << " " << root->time << " ";
        DescendingOutput(root->left);
    }

    NodeT* InsertHelper(NodeT* node, float time, string name) {
        if (!node) {
            return new NodeT(time, name);
        }
        if (time < node->time) {
            node->left = InsertHelper(node->left, time, name);
        } else {
            node->right = InsertHelper(node->right, time, name);
        }
        return node;
    }

public:
    BinarySearchTree() : root(nullptr) {}

    void Insert(float time, string name) {
        root = InsertHelper(root, time, name);
    }

    void DisplayDescending() {
        DescendingOutput(root);
    }
};

class Stack_List {
    Linkedlist s;

public:
    void push(float time, string name) {
        s.AddTail(time, name);
    }

    void display() {
        s.Display();
        sleep(10);
    }
};

vector<Player> leaderboard;

Queue leaderboardQueue;
Linkedlist leaderboardList;
BinarySearchTree leaderboardBST;
Stack_List leaderboardStack;

void LeaderboardDisplay() {
    InitWindow(800, 600, "Leaderboard Display");
    char selectedOption = '\0';

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText("Select an option:", 100, 100, 20, BLACK);
        DrawText("1 - Queue", 100, 150, 20, BLACK);
        DrawText("2 - Linked List", 100, 200, 20, BLACK);
        DrawText("3 - Binary Search Tree (BST)", 100, 250, 20, BLACK);
        DrawText("4 - Stack", 100, 300, 20, BLACK);

        if (IsKeyPressed(KEY_ONE)) selectedOption = '1';
        if (IsKeyPressed(KEY_TWO)) selectedOption = '2';
        if (IsKeyPressed(KEY_THREE)) selectedOption = '3';
        if (IsKeyPressed(KEY_FOUR)) selectedOption = '4';

        if (selectedOption != '\0') {
            switch (selectedOption) {
                case '1':
                    for (const auto& entry : leaderboard) {
                        leaderboardQueue.Enqueue(entry.time, entry.name);
                    }
                    leaderboardQueue.Display();
                    break;
                case '2':
                    for (const auto& entry : leaderboard) {
                        leaderboardList.AddTail(entry.time, entry.name);
                    }
                    leaderboardList.Display();
                    break;
                case '3':
                    for (const auto& entry : leaderboard) {
                        leaderboardBST.Insert(entry.time, entry.name);
                    }
                    leaderboardBST.DisplayDescending();
                    break;
                case '4':
                    for (const auto& entry : leaderboard) {
                        leaderboardStack.push(entry.time, entry.name);
                    }
                    leaderboardStack.display();
                    break;
                default:
                    std::cout << "Invalid option selected.\n";
                    break;
            }
            selectedOption = '\0'; // Reset after selection
        }

        EndDrawing();
    }

    CloseWindow();
}

struct NodeA {
    int x, y;
    float gCost, hCost;
    Node* parent;
    float fCost() const { return gCost + hCost; }
};

void MapDefine();
void SaveLeaderboard();
void LoadLeaderboard();
void DrawMaze();
void HandlePlayerMovement();
void ResetGame();

void RunAStar();

bool gamePaused = false;
int playerX = 1, playerY = 1;
int goalX = MAZE_WIDTH - 2, goalY = MAZE_HEIGHT - 2;
float timer = 0.0f;
bool gameWon = false;
bool startScreen = true;
char playerName[20] = "";
bool showingLeaderboard = false;
bool usingAStar = false;

int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Maze Game");
    SetTargetFPS(60);
    MapDefine();

    LoadLeaderboard();

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BACKGROUND_COLOR);

        if (startScreen) {
            DrawText("MAZE GAME", SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 - 80, 40, TEXT_COLOR);
            DrawText("Press ENTER to Start", SCREEN_WIDTH / 2 - 120, SCREEN_HEIGHT / 2 - 20, 20, TEXT_COLOR);
            DrawRectangle(SCREEN_WIDTH / 2 - 120, SCREEN_HEIGHT / 2 + 20, 240, 40, BUTTON_COLOR);
            DrawText("Use A* Algorithm", SCREEN_WIDTH / 2 - 90, SCREEN_HEIGHT / 2 + 30, 20, TEXT_COLOR);

            if (IsKeyPressed(KEY_ENTER)) startScreen = false;

            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                Vector2 mousePos = GetMousePosition();
                if (mousePos.x > SCREEN_WIDTH / 2 - 120 && mousePos.x < SCREEN_WIDTH / 2 + 120 &&
                    mousePos.y > SCREEN_HEIGHT / 2 + 20 && mousePos.y < SCREEN_HEIGHT / 2 + 60) {
                    usingAStar = true;
                    startScreen = false;
                    RunAStar();
                }
            }
        } else if (gameWon) {
            DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, WIN_SCREEN_COLOR);
            DrawText("YOU WON!", SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 - 50, 30, WHITE);
            if (usingAStar) {
                strcpy(playerName, "A*Mazer");
                Player newPlayer;
                newPlayer.name = playerName;
                newPlayer.time = timer;
                leaderboard.push_back(newPlayer);
                sort(leaderboard.begin(), leaderboard.end(), [](const Player &a, const Player &b) {
                    return a.time < b.time;
                });
                SaveLeaderboard();
                showingLeaderboard = true;
                LeaderboardDisplay();}
            else
            {
            DrawText("Enter your name:", SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2, 20, WHITE);
            int key = GetCharPressed();
            if (key > 0 && strlen(playerName) < 19) playerName[strlen(playerName)] = (char)key;
            if (IsKeyPressed(KEY_BACKSPACE) && strlen(playerName) > 0) playerName[strlen(playerName) - 1] = '\0';

            if (IsKeyPressed(KEY_ENTER)) {
                Player newPlayer;
                newPlayer.name = playerName;
                newPlayer.time = timer;
                leaderboard.push_back(newPlayer);
                sort(leaderboard.begin(), leaderboard.end(), [](const Player& a, const Player& b) {
                    return a.time < b.time;
                });
                SaveLeaderboard();
                showingLeaderboard = true;
                LeaderboardDisplay();
            }
            
            DrawText(playerName, SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 + 30, 20, YELLOW);
            }
         } else {
            timer += GetFrameTime();

            if (usingAStar) {
                if (aStarIndex < aStarPath.size()) {
                    playerX = aStarPath[aStarIndex].first;
                    playerY = aStarPath[aStarIndex].second;
                    aStarIndex++;
                } else {
                    gameWon = true;
                }
            } else {
                HandlePlayerMovement();
            }

            DrawMaze();
            DrawText(TextFormat("Time: %.2f seconds", timer), 10, 10, 20, TEXT_COLOR);
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}

void MapDefine() {
    ifstream file("map.txt");

    if (!file) {
        cerr << "Error opening file!" << endl;
        return;
    }

    for (int i = 0; i < MAZE_HEIGHT; i++) {
        for (int j = 0; j < MAZE_WIDTH; j++) {
            file >> maze[i][j];
        }
    }

    file.close();
}


void DrawMaze() {
    for (int y = 0; y < MAZE_HEIGHT; y++) {
        for (int x = 0; x < MAZE_WIDTH; x++) {
            if (maze[y][x] == 1) {
                DrawRectangle(x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE, CELL_SIZE, MAZE_COLOR);  // Wall
            } else {
                DrawRectangle(x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE, CELL_SIZE, WHITE);  // Empty space
            }
        }
    }

    DrawRectangle(playerX * CELL_SIZE, playerY * CELL_SIZE, CELL_SIZE, CELL_SIZE, PLAYER_COLOR);
    DrawRectangle(goalX * CELL_SIZE, goalY * CELL_SIZE, CELL_SIZE, CELL_SIZE, GOAL_COLOR);
}

void HandlePlayerMovement() {
    if (gameWon || gamePaused) return;

    if (IsKeyPressed(KEY_UP) && maze[playerY - 1][playerX] == 0) playerY--;
    if (IsKeyPressed(KEY_DOWN) && maze[playerY + 1][playerX] == 0) playerY++;
    if (IsKeyPressed(KEY_LEFT) && maze[playerY][playerX - 1] == 0) playerX--;
    if (IsKeyPressed(KEY_RIGHT) && maze[playerY][playerX + 1] == 0) playerX++;

    if (playerX == goalX && playerY == goalY) {
        gameWon = true;
    }
}

void SaveLeaderboard() {
    ofstream file("leaderboard.txt");

    for (const auto& entry : leaderboard) {
        file << entry.name << " " << entry.time << endl;
    }

    file.close();
}

void LoadLeaderboard() {
    ifstream file("leaderboard.txt");

    if (!file) return;

    string name;
    float time;
    while (file >> name >> time) {
        leaderboard.push_back(Player(name, time));
    }

    file.close();
}

void RunAStar() {
    
    auto heuristic = [](int x1, int y1, int x2, int y2) {
        return abs(x1 - x2) + abs(y1 - y2);
    };

    
    vector<pair<int, int>> openList = {{playerX, playerY}};
    vector<pair<int, int>> visited;

    while (!openList.empty()) {
        pair<int, int> current = openList.back();
        openList.pop_back();

        // If we've reached the goal
        if (current.first == goalX && current.second == goalY) {
            aStarPath.push_back(current);  // Add goal to path
            break;
        }

        visited.push_back(current);  // Mark the current position as visited

        // Check neighbors (up, down, left, right)
        for (auto& dir : vector<pair<int, int>>{{0, -1}, {0, 1}, {-1, 0}, {1, 0}}) {
            int newX = current.first + dir.first;
            int newY = current.second + dir.second;

            // If the neighbor is within bounds and not a wall, and not visited
            if (newX >= 0 && newY >= 0 && newX < MAZE_WIDTH && newY < MAZE_HEIGHT &&
                maze[newY][newX] == 0 && find(visited.begin(), visited.end(), make_pair(newX, newY)) == visited.end()) {
                openList.push_back({newX, newY});
            }
        }
    }
}
