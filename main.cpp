
#include <raylib.h>
#include <iostream>
#include <vector>
#include <cstring>
#include <fstream>
#include <algorithm>
#include<unistd.h>




const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int MAZE_WIDTH = 20;
const int MAZE_HEIGHT = 15;
const int CELL_SIZE = 40;
//const int TILE_SIZE = 50;

//constexpr int SIZE = 5;


using namespace std;

const Color BACKGROUND_COLOR = (Color){ 200, 230, 201, 255 };  // Light pastel green
const Color MAZE_COLOR = DARKGREEN;
const Color PLAYER_COLOR = BLUE;
const Color TEXT_COLOR = BLACK;
const Color WIN_SCREEN_COLOR = Fade(BLACK, 0.7f);
const Color BUTTON_COLOR = (Color){ 255, 235, 59, 255 };
const Color GOAL_COLOR = RED;



// LINKED LIST


class Node {
public:
    float time;
    std::string name;
    Node* next;

    Node(float t, const std::string& n) : time(t), name(n), next(nullptr) {}
};

class Linkedlist { 
private:
    Node* head = nullptr;
    Node* tail = nullptr;

public:
    void AddHead(float time, std::string name) {
        Node* newNode = new Node(time, name);
        if (head == nullptr) {
            head = tail = newNode;
            tail->next = head;  // Circular link for the last node
        } else {
            newNode->next = head;
            head = newNode;
        }
    };

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
        // Initialize the window for displaying the leaderboard
        InitWindow(800, 600, "Leaderboard");
        SetTargetFPS(60);  // Limit to 60 frames per second

        // Main loop to display the linked list
        while (!WindowShouldClose()) {
            BeginDrawing();
            ClearBackground(RAYWHITE);

            // Display the title at the top of the window
            DrawText("Leaderboard", 350, 20, 30, DARKGRAY);

            // Check if the list is empty
            if (head == nullptr) {
                DrawText("Empty List", 10, 50, 20, RED);
            } else {
                // Traverse through the linked list and display the entries
                Node* temp = head;
                int y = 50;  // Starting y-position for text
                bool first = true; // Used to check if we are looping back to head
                while (temp) {
                    std::string displayText = temp->name + " : " + std::to_string(temp->time) + " seconds";
                    DrawText(displayText.c_str(), 10, y, 20, BLACK);
                    y += 30;  // Increase y-position for the next entry

                    temp = temp->next;

                    // Break if we have circled back to the head node (in case of circular list)
                    if (temp == head && !first) break;
                    first = false; // Set to false after the first loop to allow circular checking
                }
            }

            EndDrawing();
        }

        CloseWindow();  // Close the window after the loop ends
    };

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

    void SetTail(Node* newTail) {
        tail->next = newTail;
        tail = newTail;
    }
};
//QUEUE
class Queue 
{
    private:

    Linkedlist list;

    public:

    void Enqueue(float time, string name) 
    {
        list.AddTail(time, name);
    }

    Node* Search(string key) 
    {
        Node* temp = list.GetHead();
        while(temp!= nullptr && temp->name != key)
        {
            temp = temp->next;
        }

        if(temp == nullptr){
            return NULL;
        }

        else
        {
            if(temp == list.GetHead()){
                list.RemoveHead();
            }
            else
            {
                Node* prev = list.GetHead();
                while(prev->next!= temp){
                    prev = prev->next;
                }
                prev->next = temp->next;
            }
            return temp;
        }
    };

     Node* Dequeue() {
        if (list.GetHead() == NULL) {
            std::cout << "Queue is empty" << std::endl;
            return nullptr;
        }
        Node* dequeuedNode = list.GetHead();
        std::cout << "Dequeued: " << dequeuedNode->name << std::endl;
        list.RemoveHead();
        return dequeuedNode;
    }

    void Display(){
        list.Display();
        sleep(10);
    };
};



// BST
struct NodeT
{
    float time;
    string name;
    NodeT* left;
    NodeT* right;

       NodeT(float t, string n) : time(t), name(n), left(nullptr), right(nullptr) {}
};

class BinarySearchTree{
    
    NodeT* root = nullptr;

    void DescendingOutput(NodeT* root){
        if(root == NULL){
            return;
        }
        DescendingOutput(root->right);
        cout << root->name << " "<< root->time<<" ";
        DescendingOutput(root->left);
    }

   NodeT* InsertHelper(NodeT* node, float time, string name) {
    if (!node) {
        // Create a new NodeT using the constructor
        return new NodeT(time, name);
    }
    if (time < node->time) {
        node->left = InsertHelper(node->left, time, name);
    } 
    else {
        node->right = InsertHelper(node->right, time, name);
    }
    return node;
}
    public:
    void DOhelper(){
        DescendingOutput(root);
    }
    BinarySearchTree(){
        root = NULL;
    }
    void Insert(float time, string name){
        root = insertHelper(root, time, name);
    }
    NodeT* insertHelper(NodeT* node, float time, string name){
        if(node == NULL){
            node = new NodeT(time, name);
            node->left = node->right = NULL;
        }
        else if(time < node->time){
            node->left = insertHelper(node->left, time, name);
        }
        else if(time > node->time){
            node->right = insertHelper(node->right, time, name);
        }
        return node;
    }

    
};

//stack with linked list

class Stack_List{
    Linkedlist s;
    
    public:
    void push(float time, string name){
        s.AddHead(time, name);
    }
    void pop(){
        s.RemoveHead();
    }

    void display(){
        s.Display();
        sleep(10);
    }
};

//hashmap

// class HashMap {
// private:
//     static const int SIZE = 10; // Size of the hash table
//     Linkedlist table[SIZE];

//     int hashFunction(float time) {
//         return static_cast<int>(time) % SIZE; // Hash based on the time value
//     }

// public:
//     void insert(string name, float time) {
//         int index = hashFunction(time);
//         table[index].AddTail(time, name);
//     }

//     void display() {
//         for (int i = 0; i < SIZE; ++i) {
//             std::cout << "Bucket " << i << ": ";
//             table[i].Display();
//         }
//     }
// };

// //graph yayayayayay
// class Graph {
// private:
//     struct Node {
//         string name;
//         float time;
//         vector<Node*> neighbors;
//     };

//     vector<Node> nodes;

// public:
//     void addNode(const string& name, float time) {
//         nodes.push_back({name, time, {}});
//     }

//     void addEdge(int fromIndex, int toIndex) {
//         if (fromIndex >= 0 && fromIndex< nodes.size() && toIndex >= 0 && toIndex < nodes.size()) {
//             nodes[fromIndex].neighbors.push_back(&nodes[toIndex]); 
//         }
//     }
//     void display() {
//         for (const auto& node : nodes) {
//             cout << "Node: " << node.name << ", Time: " << node.time << " -> ";
//             if (node.neighbors.empty()) {
//                 cout << "No neighbors.";
//             } else {
//                 for (const auto& neighbor : node.neighbors) {
//                     cout << neighbor->name << " ";
//                 }
//             }
//             cout << endl;
//         }
//     }
// };


// STACK

class stack {
    private:
    
    pair<int, int> arr[100];
    int top;


    public:
    stack()
    {
        top = -1;
    };

    void push(pair<int,int> value)
    {
        if (top >= 100 - 1)
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

// MAZE GAME FUNCTIONS - Shabih
//LEADERBOARD FUNCTIONS
// Structure to hold player name and time
struct Player {
    string name;
    float time;
    Player(string playerName, float playerTime) {
        name = playerName;
        time = playerTime;
    }

    Player() : name(""), time(0.0f) {}
};

vector<Player> leaderboard;

// Maze array definition (to be populated by MapDefine function)
int maze[MAZE_HEIGHT][MAZE_WIDTH];

// Function prototypes
void MapDefine();
void ShowLeaderboard();
void SaveLeaderboard();
void LoadLeaderboard();
void DrawMaze();
void HandlePlayerMovement();
void ResetGame();
void LeaderboardDisplay();

bool gamePaused = false;
int playerX = 1, playerY = 1;
int goalX = MAZE_WIDTH - 2, goalY = MAZE_HEIGHT - 2;
float timer = 0.0f;
bool gameWon = false;
bool startScreen = true;
char playerName[20] = "";
bool showingLeaderboard = false;

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

            if (IsKeyPressed(KEY_ENTER)) startScreen = false;

        } else if (showingLeaderboard) {
            LeaderboardDisplay();  // Keep the Leaderboard Display logic intact
        } else if (gameWon) {
            DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, WIN_SCREEN_COLOR);
            DrawText("YOU WON!", SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 - 50, 30, WHITE);

            DrawText("Enter your name:", SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2, 20, WHITE);
            int key = GetCharPressed();
            if (key > 0 && strlen(playerName) < 19) playerName[strlen(playerName)] = (char)key;
            if (IsKeyPressed(KEY_BACKSPACE) && strlen(playerName) > 0) playerName[strlen(playerName) - 1] = '\0';

            if (IsKeyPressed(KEY_ENTER)) {
                Player newPlayer;
                newPlayer.name = playerName;
                newPlayer.time = timer;
                leaderboard.push_back(newPlayer);
                sort(leaderboard.begin(), leaderboard.end(), [](const Player &a, const Player &b) {
                    return a.time < b.time;
                });
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

void ResetGame() {
    playerX = 1;
    playerY = 1;
    timer = 0.0f;
    gameWon = false;
    startScreen = true;
    showingLeaderboard = false;
    gamePaused = false;
}

// void LoadLeaderboard() {
//     ifstream file("leaderboard.txt");
//     leaderboard.clear();
//     string name;
//     float time;
//     while (file >> name >> time) {
//         Player p;
//         p.name = name;
//         p.time = time;
//         leaderboard.push_back(p);
//     }

//     file.close();
// }

void SaveLeaderboard() {
    ofstream file("leaderboard.txt");
    for (size_t i = 0; i < leaderboard.size(); i++) {
        file << leaderboard[i].name << " " << leaderboard[i].time << endl;
    }
}

void LoadLeaderboard() {
    ifstream file("leaderboard.txt");
    leaderboard.clear();
    string name;
    float time;
    while (file >> name >> time) {
        Player p;
        p.name = name;
        p.time = time;
        leaderboard.push_back(p);
    }
}


void LeaderboardDisplay() {

    // Set up window
    InitWindow(800, 600, "Leaderboard Display");

    // Variable to track user selection
    char selectedOption = '\0';

    // Declare all data structures outside of the switch-case to avoid initialization issues
    Queue q;
    Linkedlist l;
    BinarySearchTree bst;
    Stack_List sl;

    // Main loop
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Display options
        DrawText("Select an option:", 100, 100, 20, BLACK);
        DrawText("1 - Queue", 100, 150, 20, BLACK);
        DrawText("2 - Linked List", 100, 200, 20, BLACK);
        DrawText("3 - Binary Search Tree (BST)", 100, 250, 20, BLACK);
        DrawText("4 - Stack", 100, 300, 20, BLACK);

        // Input for option selection
        DrawText("Enter a number (1-4) and press Enter:", 100, 350, 20, BLACK);

        // Check for key input (1 to 4)
        if (IsKeyPressed(KEY_ONE)) selectedOption = '1';
        if (IsKeyPressed(KEY_TWO)) selectedOption = '2';
        if (IsKeyPressed(KEY_THREE)) selectedOption = '3';
        if (IsKeyPressed(KEY_FOUR)) selectedOption = '4';

        // Handle the selected option with switch case
        if (selectedOption != '\0') {
            switch (selectedOption) {
                case '1':
                    // Initialize Queue
                    for (const auto& entry : leaderboard) {
                        q.Enqueue(entry.time, entry.name);
                    }
                    q.Display();
                    break;
                case '2':
                    // Initialize Linked List
                    for (size_t x = 0; x < leaderboard.size(); x++)
                        l.AddHead(leaderboard[x].time , leaderboard[x].name);
                    l.Display();
                    break;

                case '3':
                    // Initialize Binary Search Tree (BST)
                    for (size_t x = 0; x < leaderboard.size(); x++)
                        bst.Insert(leaderboard[x].time , leaderboard[x].name);
                    bst.DOhelper();
                    break;
                case '4':
                    // Initialize Stack
                    for (const auto& entry : leaderboard) {
                        sl.push(entry.time, entry.name);
                    }
                    sl.display();
                    break;
                default:
                    std::cout << "Invalid option selected.\n";
                    break;
            }
            selectedOption = '\0'; // Reset after selection
        }

        EndDrawing();
    }

    CloseWindow();  // Close window and cleanup
}





