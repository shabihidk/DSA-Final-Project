// Small maze with 1 for free space, 5 for visited/blocked spaces, and 9 for the exit.
#include <raylib.h>
#include <iostream>
#include <vector>
#include <cstring>
#include <fstream>
#include <algorithm>

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

struct Node{
    string name;
    float time;
    Node* next;

    Node(float t, string n) :  name(n), time(t), next(nullptr) {};
};

class Linkedlist{ 
    private:

    Node* head = nullptr;
    Node* tail = nullptr;

    public:

    void AddHead(float time, string name){
        Node* newNode = new Node(time,name);
        if(head == nullptr)
        {
            head = tail = newNode;
            tail->next = head;
        }
        else 
        {
            newNode->next = head;
            head = newNode;
        }
    };

    void AddTail(float time, string name){
        Node* newNode = new Node(time, name);

        if(!tail){
            head = newNode;
        }
        else{
           
            tail->next = newNode;
        }
            tail = newNode;
    }

    void Display(){
        if(head == nullptr){
            cerr << "Empty List" << endl;
            return;
        }
        Node* temp = head;
        while(temp){
            cout << temp->name << " : " << temp->time << " seconds" << endl;
            temp = temp->next;
        }
    }

    Node* GetHead() const
    {
        return head;
    };

     Node* GetTail() const {
        return tail;
    }

   void RemoveHead() {
        if (!head) return;

        Node* temp = head;
        head = head->next;
        
        delete temp;
    };

    void RemoveTail()
    {
        if(!head) return;

        Node* temp2 = tail;
        Node* temp = head;
        
        while(temp->next != tail)
        {
            temp = temp->next;
        }

        temp->next = nullptr;
        tail = temp->next;

        delete temp2;
        
    };

    void SetTail(Node* newTail) {
        tail->next = newTail;
        tail = newTail;
    };
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
    }
    void RemoveNode(const string& key) {
    if (!list.GetHead()) {
        cout << "List is empty, nothing to remove." << endl;
        return;
    }

    Node* temp = list.GetHead();
    Node* prev = nullptr;

    while (temp && temp->name != key) {
        prev = temp;
        temp = temp->next;
    }

    if (!temp) {

        cout << "Key not found in the list." << endl;
        return;
    }

    if (temp == list.GetHead()) {
        list.RemoveHead(); 
    } else {
        prev->next = temp->next;
        if (temp == list.GetTail()) {

            list.SetTail(prev);
        }
        delete temp;
    }

    cout << "Node with key \"" << key << "\" removed successfully." << endl;
}

    void Dequeue(){

        if(list.GetHead() == NULL){
            cout << "Queue is empty" << endl;
            return;
        }
        cout << "Dequeued: " << list.GetHead()->name << endl;
        list.RemoveHead();
    };

    void Display(){
        list.Display();
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
    }
};

// LEADERBOARD FUNCTIONS

void LeaderboardDisplay(){
    ifstream file("leaderboard.txt");
    string name;
    float time;
    int choice;
    cout << "choose data structure" << endl;
    cout << "1. Queue" << endl;
    cout << "2. Linked List" << endl;
    cout << "3. Binary Search Tree" << endl;
    cout << "4. Stack with Linked List" << endl;
    cin >> choice;
    switch(choice){
    cout << "Enter your choice: ";
    cin >> choice;
    switch(choice){
        case 1:
            Queue q;
            while(file >> name >> time){
                q.Enqueue(time, name);
            }
            q.Display();
            break;
            
        case 2:
            Linkedlist l;
            while(file >> name >> time){
                l.AddHead(time, name);
            }
            l.Display();
            break;
            
        case 3:
            BinarySearchTree bst;
            while(file >> name >> time){
                bst.Insert(time, name);
            }
            bst.DOhelper();
            break;
        
        case 4:
        Stack_List sl;
        while(file >> name >> time){
                sl.push(time, name);
            }
        sl.display();
        break;
            
        default:
            cout << "Invalid choice" << endl;
            break;
    }
}

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

struct Player
{
    string name;
    float time;
};

int maze[MAZE_HEIGHT][MAZE_WIDTH];


void MapDefine()
{
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
};

//  ---------------------- CODE NOT WORKING [ segmentation error ]---------------------- 

// class Search {
// private:
//     vector<vector<int>> maze;
//     stack s;
//     int startX, startY, endX, endY;
//     bool searchComplete;
//     string statusMessage;

// public:
//     Search(vector<vector<int>> m) : maze(m), searchComplete(false){
//         for (int i = 0; i < SIZE; ++i) {
//             for (int j = 0; j < SIZE; ++j) {
//                 if (maze[i][j] == 4) {
//                     startX = i;
//                     startY = j;
//                 }
//                 if (maze[i][j] == 9) {
//                     endX = i;
//                     endY = j;
//                 }
//             }
//         }
//         s.push({startX,startY});

//     }

//     void searchstep() 
//     {
//         if (s.empty())
//         {
//             searchComplete = true;
//             cout << "Exit Not Found. \n";
//             return; 
//         }   
//         while(!s.empty())
//         {
//             int x;
//             x = s.topElement().first;

//             int y = s.topElement().second;

//             s.pop();

//             if (x == endX && y == endY)
//             {
//                 searchComplete = true;
//                 statusMessage = "Exit found at (" + to_string(x) + ", " + to_string(y) + ")";
//                 return;
//             };

//             maze[x][y] = 5;

//             if ( x-1 >= 0 && maze[x - 1][y] == 1) 
//             {
//                 s.push({x -1, y});
//             };
//             if (x + 1 < SIZE && maze[x + 1][y] == 1) 
//             {
//                 s.push({x + 1, y});
//             };
//             if (y - 1 >= 0 && maze[x][y - 1] == 1) 
//             {
//                 s.push({x, y - 1});
//             };
//             if (y + 1 < SIZE && maze[x][y + 1] == 1) 
//             {
//                 s.push({x, y + 1});
//             };

//         };

//     };

//     bool isSearchComplete()
//     {
//         return searchComplete;
//     }

    // void DrawMaze()
    // {
    //     BeginDrawing();
    //     ClearBackground(RAYWHITE);

    //     for (int i = 0; i < SIZE; ++i)
    //     {
    //         for (int j = 0; j < SIZE; ++j)
    //         {
    //             Color color;
    //             switch (maze[i][j])
    //             {   
    //                 case 1: color = DARKGRAY; break;
    //                 case 4: color = GREEN; break;
    //                 case 9: color = RED; break;
    //                 case 5: color = BLUE; break;
    //                 default: color = LIGHTGRAY; break; 

    //             }

    //             DrawRectangle(j * TILE_SIZE, i * TILE_SIZE, TILE_SIZE, TILE_SIZE, color);

    //         }
    //     }

    //     DrawText(statusMessage.c_str(), 10, SIZE * TILE_SIZE + 10, 20, DARKGRAY);

    //     EndDrawing();
    // };
    

int playerX = 1, playerY = 1;
int goalX = MAZE_WIDTH - 2, goalY = MAZE_HEIGHT - 2;
vector<Player> leaderboard;
float timer = 0.0f;
bool gameWon = false;
bool startScreen = true;
char playerName[20] = "";
bool showingLeaderboard = false;

void ShowLeaderboard();
void SaveLeaderboard();
void LoadLeaderboard();

void DrawMaze();
void HandlePlayerMovement();
void ResetGame();

int main() {
    
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Maze Search Visualization");
    SetTargetFPS(50);

    MapDefine();
    
    LoadLeaderboard();


    while(!WindowShouldClose())
    {   
        BeginDrawing();
        ClearBackground(BACKGROUND_COLOR);

        if (startScreen) {
            DrawText("MAZE GAME", SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 - 50, 40, TEXT_COLOR);
            DrawText("Press ENTER to Start", SCREEN_WIDTH / 2 - 120, SCREEN_HEIGHT / 2, 20, TEXT_COLOR);
            if (IsKeyPressed(KEY_ENTER)) startScreen = false;
        } else if(showingLeaderboard) 
        {
            ShowLeaderboard();
            if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                Vector2 mousePos = GetMousePosition();
                if (mousePos.x > SCREEN_WIDTH / 2 - 100 && mousePos.x < SCREEN_WIDTH / 2 + 100 &&
                    mousePos.y > SCREEN_HEIGHT - 50 && mousePos.y < SCREEN_HEIGHT - 10) {
                    ResetGame();
                }
            };
        }

        else if (gameWon)
        {
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
   };


CloseWindow();


    return 0;
};

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
};


void HandlePlayerMovement() {  // // Handle player movement with arrow keys
    if (IsKeyPressed(KEY_UP) && maze[playerY - 1][playerX] == 0) playerY--;  // // Up movement
    if (IsKeyPressed(KEY_DOWN) && maze[playerY + 1][playerX] == 0) playerY++;  // // Down movement
    if (IsKeyPressed(KEY_LEFT) && maze[playerY][playerX - 1] == 0) playerX--;  // // Left movement
    if (IsKeyPressed(KEY_RIGHT) && maze[playerY][playerX + 1] == 0) playerX++;  // // Right movement
};

void ShowLeaderboard() {
    ClearBackground(BACKGROUND_COLOR);
    DrawText("LEADERBOARD", SCREEN_WIDTH / 2 - 100, 50, 30, TEXT_COLOR);

    int y = 100;
    for (size_t i = 0; i < leaderboard.size(); i++) {
        DrawText(TextFormat("%s - %.2f", leaderboard[i].name.c_str(), leaderboard[i].time), SCREEN_WIDTH / 2 - 100, y, 20, TEXT_COLOR);
        y += 30;
    }

    DrawRectangle(SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT - 50, 200, 40, BUTTON_COLOR);
    DrawText("Retry", SCREEN_WIDTH / 2 - 30, SCREEN_HEIGHT - 40, 20, TEXT_COLOR);
};


void ResetGame() {  // // Reset game state
    playerX = 1;
    playerY = 1;
    timer = 0.0f;
    gameWon = false;
    startScreen = true;
    showingLeaderboard = false;
  };

void SaveLeaderboard() {
    ofstream file("leaderboard.txt");
    for (size_t i = 0; i < leaderboard.size(); i++) {
        file << leaderboard[i].name << " " << leaderboard[i].time << endl;
    }
};


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
};