// A C++ Program to Implement and Play Minesweeper

#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

const int ROWS = 10;
const int COLS = 10;
const int MINES = 10;

int grid[ROWS][COLS];
bool revealed[ROWS][COLS];

// Function to initialize the grid with random mines
void init() {
  // Seed the random number generator
  srand(time(0));

  int mines_placed = 0;
  while (mines_placed < MINES) {
    int row = rand() % ROWS;
    int col = rand() % COLS;
    if (grid[row][col] != -1) {
      grid[row][col] = -1;
      ++mines_placed;
    }
  }

  // Calculate the number of mines around each cell
  for (int i = 0; i < ROWS; ++i) {
    for (int j = 0; j < COLS; ++j) {
      if (grid[i][j] == -1) {
        continue;
      }

      int mines_around = 0;
      for (int x = i - 1; x <= i + 1; ++x) {
        for (int y = j - 1; y <= j + 1; ++y) {
          if (x >= 0 && x < ROWS && y >= 0 && y < COLS && grid[x][y] == -1) {
            ++mines_around;
          }
        }
      }

      grid[i][j] = mines_around;
    }
  }
}

// Function to reveal a cell
void reveal(int row, int col) {
  if (row < 0 || row >= ROWS || col < 0 || col >= COLS) {
    return;
  }

  if (revealed[row][col]) {
    return;
  }

  revealed[row][col] = true;

  if (grid[row][col] != 0) {
    return;
  }

  reveal(row - 1, col - 1);
  reveal(row - 1, col);
  reveal(row - 1, col + 1);
  reveal(row, col - 1);
  reveal(row, col + 1);
  reveal(row + 1, col - 1);
  reveal(row + 1, col);
  reveal(row + 1, col + 1);
}

// Function to print the grid
void print_grid() {
  for (int i = 0; i < ROWS; ++i) {
    for (int j = 0; j < COLS; ++j) {
      if (!revealed[i][j]) {
        std::cout << "?" << " ";
      } else if (grid[i][j] == -1) {
        std::cout << "*" << " ";
      } else {
        std::cout << grid[i][j] << " ";
      }
    }
    std::cout << std::endl;
  }
}

int main() {
  init();
  int row, col;

  while (true) {
    std::cout << "Enter the row and column of the cell to reveal: ";
    std::cin >> row >> col;
    reveal(row, col);
    print_grid();

    // Check if the game is over
    bool game_over = false;
    for (int i = 0; i < ROWS; ++i) {
      for (int j = 0; j < COLS; ++j) {
        if (grid[i][j] == -1 && revealed[i][j]) {
          std::cout << "You lose!" << std::endl;
          game_over = true;
          break;
        }
      }
      if (game_over) {
        break;
      }
    }
    if (game_over) {
      break;
    }

    int cells_revealed = 0;
    for (int i = 0; i < ROWS; ++i) {
      for (int j = 0; j < COLS; ++j) {
        if (revealed[i][j]) {
          ++cells_revealed;
        }
      }
    }
    if (cells_revealed == ROWS * COLS - MINES) {
      std::cout << "You win!" << std::endl;
      break;
    }
  }

  return 0;
}

