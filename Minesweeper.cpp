// Ayush Kamath
// CLA 18
// Making CLA16 as a basic and playable version of Minesweeper

#include <cstdlib>
#include <ctime>
#include <iostream>

// Declare the constant defining levels
const int EASY = 6;
const int MEDIUM = 16;
const int HARD = 30;

void initializeBoard(int arr[][HARD], int rows, int cols, int numMines) {
  // Initialize all tiles to 0
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      arr[i][j] = 0;
    }
  }

  // The function would then randomly assign mine locations on the game board.
  // It would take in the number of mines to be placed as an input parameter
  // based on the difficulty level. For example, "Easy" difficulty will have 8
  // mines, "Medium" will have 10, and "Hard" will have 15. The function would
  // ensure that there are no repeated mine locations on the game board.
  int placedMines = 0;
  while (placedMines < numMines) {
    int x = rand() % rows;
    int y = rand() % cols;
    if (arr[x][y] != -1) { // Only place a mine if there isn't one already
      arr[x][y] = -1;
      placedMines++;
    }
  }

  // Fill in the tile counts
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      if (arr[i][j] != -1) { // Ignore tiles with mines
        int count = 0;
        for (int dx = -1; dx <= 1; dx++) {
          for (int dy = -1; dy <= 1; dy++) {
            int nx = i + dx;
            int ny = j + dy;
            if (nx >= 0 && ny >= 0 && nx < rows && ny < cols &&
                arr[nx][ny] == -1) {
              count++;
            }
          }
        }
        arr[i][j] = count;
      }
    }
  }
}

void printBoard(int arr[][HARD], bool revealed[][HARD], int rows, int cols) {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      if (revealed[i][j]) {
        if (arr[i][j] == -1) {
          std::cout << "X ";
        } else {
          std::cout << arr[i][j] << " ";
        }
      } else {
        std::cout << "* ";
      }
    }
    std::cout << std::endl;
  }
}

void Initialize(int level, int &rows, int &cols, int &numMines) {
  if (level == 1) {
    rows = EASY;
    cols = EASY;
    numMines = 3;
  } else if (level == 2) {
    rows = MEDIUM;
    cols = MEDIUM;
    numMines = 10;
  } else if (level == 3) {
    rows = HARD;
    cols = HARD;
    numMines = 15;
  }
}

int main() {
  // Seed the random number generator
  srand(time(0));

  // Ask the user for the difficulty level
  int level;
  std::cout << "Welcome to my Minesweeper Game!\nAfter you start playing, please keep in mind that the top left tile is (0,0) for reference" << std::endl;
  std::cout << "Please choose a difficulty level\nEnter 1 for Easy\nEnter 2 "
               "for Medium\nEnter 3 for Hard ";
  std::cin >> level;

  // Initialize game board
  int rows, cols, numMines;
  bool isTrue = true;
  while (isTrue) {
    if (level == 1 || level == 2 || level == 3) {
      Initialize(level, rows, cols, numMines);
      isTrue = false;
    } else {
      std::cout << "Invalid level option. Please run again and enter a valid difficulty input (1, 2, or 3)." << std::endl;
      return(0);
    }
  }

  int board[rows][HARD];
  bool revealed[rows][HARD];
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < HARD; j++) {
      revealed[i][j] = false;
    }
  }

  initializeBoard(board, rows, cols, numMines);

  // Play game
  bool gameOver = false;
  int numRevealed = 0;
  while (!gameOver) {
    // Print board
    std::cout << std::endl;
    std::cout << "Current board:" << std::endl;
    printBoard(board, revealed, rows, cols);

    // Ask user for input
    int x, y;
    std::cout << std::endl;
    std::cout << "Enter a column number and row number to reveal (in a column,row format ex. 1 2): ";
    std::cin >> x >> y;

    // Check input validity
    if (x < 1 || x > rows || y < 1 || y > cols) {
      std::cout << "Invalid input. Please try again." << std::endl;
      continue;
    }
    x--; // Adjust for 0-based indexing
    y--;

    // Check if user revealed a mine
    if (board[x][y] == -1) {
      std::cout << "Game over! You hit a mine." << std::endl;
      revealed[x][y] = true;
      gameOver = true;
      continue;
    }

    // Reveal tile and update count
    if (!revealed[x][y]) {
      revealed[x][y] = true;
      numRevealed++;
    }

    // Check if user has won
    if (numRevealed == rows * cols - numMines) {
      std::cout << std::endl;
      std::cout << "Congratulations! You won!" << std::endl;
      printBoard(board, revealed, rows, cols);
      gameOver = true;
    }
  }

  return 0;
}



