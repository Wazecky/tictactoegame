#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

// Function to display the Tic-Tac-Toe board
void displayBoard(const std::vector<std::vector<char>>& board) {
    for (const auto& row : board) {
        for (char cell : row) {
            std::cout << cell << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

// Function to check if a player has won
bool checkWin(const std::vector<std::vector<char>>& board, char player) {
    // Check rows and columns
    for (int i = 0; i < 3; ++i) {
        if ((board[i][0] == player && board[i][1] == player && board[i][2] == player) ||
            (board[0][i] == player && board[1][i] == player && board[2][i] == player)) {
            return true;
        }
    }

    // Check diagonals
    if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
        (board[0][2] == player && board[1][1] == player && board[2][0] == player)) {
        return true;
    }

    return false;
}

// Function to check if the board is full (a tie)
bool checkTie(const std::vector<std::vector<char>>& board) {
    for (const auto& row : board) {
        for (char cell : row) {
            if (cell == ' ') {
                return false; // There is an empty space, so the game is not a tie
            }
        }
    }
    return true; // The board is full, and there is no winner, so it's a tie
}

// Function to check if the current move is valid
bool isValidMove(const std::vector<std::vector<char>>& board, int row, int col) {
    return (row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == ' ');
}

// Function to display the instructions for the player
void displayInstructions() {
    std::cout << "Welcome to Tic-Tac-Toe!" << std::endl;
    std::cout << "Player is X, and AI is O." << std::endl;
    std::cout << "To make a move, enter the row and column where you want to place your symbol." << std::endl;
    std::cout << "For example, enter '1 2' to place your symbol in the first row, second column." << std::endl;
    std::cout << "The board is a 3x3 grid with rows and columns numbered from 1 to 3." << std::endl;
    std::cout << "Let's start the game!" << std::endl;
}

// Function to get the player's move
void getPlayerMove(std::vector<std::vector<char>>& board) {
    int row, col;
    do {
        std::cout << "Enter your move (row and column, e.g., 1 2): ";
        std::cin >> row >> col;
    } while (!isValidMove(board, row - 1, col - 1));

    board[row - 1][col - 1] = 'X';
}

// Function to get the AI's move
void getAIMove(std::vector<std::vector<char>>& board) {
    // Simple AI strategy: Randomly choose an empty cell
    std::vector<std::pair<int, int>> emptyCells;

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] == ' ') {
                emptyCells.push_back({ i, j });
            }
        }
    }

    if (!emptyCells.empty()) {
        std::srand(std::time(0));
        int randomIndex = std::rand() % emptyCells.size();
        board[emptyCells[randomIndex].first][emptyCells[randomIndex].second] = 'O';
    }
}

int main() {
    std::vector<std::vector<char>> board(3, std::vector<char>(3, ' '));

    displayInstructions();

    bool playerTurn = true; // Player goes first
    bool gameRunning = true;

    while (gameRunning) {
        displayBoard(board);

        if (playerTurn) {
            getPlayerMove(board);

            if (checkWin(board, 'X')) {
                displayBoard(board);
                std::cout << "Congratulations! You win!" << std::endl;
                gameRunning = false;
            } else if (checkTie(board)) {
                displayBoard(board);
                std::cout << "It's a tie!" << std::endl;
                gameRunning = false;
            }
        } else {
            getAIMove(board);

            if (checkWin(board, 'O')) {
                displayBoard(board);
                std::cout << "AI wins! Better luck next time." << std::endl;
                gameRunning = false;
            } else if (checkTie(board)) {
                displayBoard(board);
                std::cout << "It's a tie!" << std::endl;
                gameRunning = false;
            }
        }

        playerTurn = !playerTurn; // Switch turns
    }

    return 0;
}
