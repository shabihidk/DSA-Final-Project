
---

# A*Mazer - Maze Game

**A*Mazer** is a fun and challenging maze game built using **Raylib** in **C++**. The goal of the game is to navigate through a maze and reach the designated goal while keeping track of your time. Once you complete the maze, you can save your score to a leaderboard and challenge yourself to improve your speed.

---

## Features

- **Player Movement & Maze Navigation**: Move the player using the arrow keys through a maze where some cells are walls and others are open paths.
- **Timer System**: Track your completion time, displayed in real-time at the top-left corner of the screen.
- **Leaderboard**: After winning the game, players can enter their name to record their completion time. The leaderboard is saved in a file and displays the fastest times.
- **Goal System**: Reach the red block (goal) to win the game.
- **Dynamic Maze**: The maze layout is loaded from an external file, allowing easy modifications to the maze design.
- **Start Screen**: Displays a welcome screen with the game title and an option to start by pressing "ENTER".
- **Retry Option**: After viewing the leaderboard, players can retry the game directly from the leaderboard screen.

---

## How to Play

1. **Start the Game**: Press "ENTER" on the start screen to begin.
2. **Navigate the Maze**: Use the arrow keys to move the player through the maze.
3. **Win the Game**: Reach the goal (marked by a red block) to win the game.
4. **Leaderboard**: After winning, you can enter your name to save your score and see how it compares with other players.
5. **Retry**: You can retry the game after viewing the leaderboard by clicking the "Retry" button.

---

## Installation

### Prerequisites

- **Raylib 4.5** is required to run this project.
- Ensure that you have a C++ compiler installed, such as **g++**.
- This game has been tested on **Windows 10** and **Windows 11**.

### Step 1: Install Raylib

To install **Raylib**, you can follow the instructions for **Windows** provided in the official [Raylib installation guide](https://github.com/raysan5/raylib/blob/master/README.md).

Alternatively, you can use **vcpkg** to install Raylib with the following commands:

```bash
git clone https://github.com/microsoft/vcpkg.git
cd vcpkg
./vcpkg install raylib
```

Make sure to set up the necessary environment variables to link Raylib in your project.

---

### Step 2: Clone the Repository

Clone this repository to your local machine:

```bash
git clone https://github.com/YOUR_USERNAME/A-Mazer.git
cd A-Mazer
```

---

### Step 3: Build and Run

1. Open the project in **Visual Studio Code** or your preferred IDE.
2. Set up the build tasks to use a C++ compiler (like `g++` or `clang++`).
3. Compile and run the project. The game window should open, and you can start playing!

---

## Screenshots

### Start Screen

![image](https://github.com/user-attachments/assets/5b8d0e4e-2284-424d-997e-f5c208e611c7)

### Gameplay

![image](https://github.com/user-attachments/assets/82609a62-bce1-42f2-81f3-3a1a950cecb7)

### Win Screen

![image](https://github.com/user-attachments/assets/f1e36234-edf4-475a-9c1a-1161260a43bb)

### Leaderboard

![image](https://github.com/user-attachments/assets/6f2763db-4aa0-45f6-97e9-649959dde0b6)

---

## Future Plans

- Adding additional levels and maze difficulty.
- Introducing obstacles, enemies, or power-ups to increase challenge.
- Adding background music and sound effects.
- Implementing a multiplayer mode for competitive play.

---

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

---

## Resources

- 🎥 [Watch the Video Tutorial on YouTube](https://www.youtube.com/watch?v=PaAcVk5jUd8)

