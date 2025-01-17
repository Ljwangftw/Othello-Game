#include "Board.h"
#include <iostream>
#include <algorithm>
#include <cassert>
#include <stdexcept>

Board::Board() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            board[i][j] = new PlayablePosition();
        }
    }
}

Board::~Board() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            delete board[i][j];
        }
    }
}

void Board::initializeStandard() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if ((i == 3 && j == 3) || (i == 4 && j == 4)) {
                board[i][j]->setPiece('w');
            } else if ((i == 3 && j == 4) || (i == 4 && j == 3)) {
                board[i][j]->setPiece('b');
            } else if ((i == 3 && j == 0) || (i == 4 && j == 0)) {
                delete board[i][j];
                board[i][j] = new UnplayablePosition();
            } else {
                board[i][j]->setPiece('-');
            }
        }
    }
}

void Board::initializeFourByFour() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if ((i == 3 && j == 3) || (i == 4 && j == 4) || (i == 2 && j == 2)
                || (i == 3 && j == 2) || (i == 2 && j == 3) || (i == 5 && j == 4) || (i == 4 && j == 5)
                || (i == 5 && j == 5)) {
                board[i][j]->setPiece('w');
            } else if ((i == 3 && j == 4) || (i == 4 && j == 3) ||
                (i == 4 && j == 2) || (i == 5 && j == 2) || (i == 5 && j == 3) || (i == 2 && j == 4) ||
                (i == 2 && j == 5) || (i == 3 && j == 5)) {
                board[i][j]->setPiece('b');
            } else if ((i == 3 && j == 0) || (i == 4 && j == 0)) {
                delete board[i][j];
                board[i][j] = new UnplayablePosition();
            } else {
                board[i][j]->setPiece('-');
            }
        }
    }
}

void Board::display(Position* state[8][8]) const {
    std::cout << "  0 1 2 3 4 5 6 7\n";
    for (int i = 0; i < 8; i++) {
        std::cout << i << " ";
        for (int j = 0; j < 8; j++) {
            if (state) {
                std::cout << state[i][j]->getPiece() << " ";
            } else {
                std::cout << board[i][j]->getPiece() << " ";
            }
        }
        std::cout << std::endl;
    }
}


std::vector<std::vector<int>> Board::getBlackLegalMoves(Position* board[8][8]) const {
    return calculateLegalMoves(board, 'b');
}

std::vector<std::vector<int>> Board::getWhiteLegalMoves(Position* board[8][8]) const {
    return calculateLegalMoves(board, 'w');
}

void Board:: flip(Position* board[8][8], int row, int col, char player) {
    std::vector<std::vector<int>> discsToFlip;
    char opponent = (player == 'b') ? 'w' : 'b';
    int surrounding[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};

    for (auto deltas : surrounding) {
        int cur_row = row + deltas[0];
        int cur_col = col + deltas[1];

        if (cur_row > 7 || cur_row < 0 || cur_col > 7 || cur_col < 0 || board[cur_row][cur_col]->getPiece() == '*')
            continue;

        char cur_char = board[cur_row][cur_col]->getPiece();
        bool shouldFlip = false;

        if (cur_char == opponent) {
            while (cur_char == opponent) {
                cur_row += deltas[0];
                cur_col += deltas[1];

                if (cur_row > 7 || cur_row < 0 || cur_col > 7 || cur_col < 0 || board[cur_row][cur_col]->getPiece() == '*')
                    break;

                cur_char = board[cur_row][cur_col]->getPiece();

                if (cur_char == player)
                    shouldFlip = true;

                if (shouldFlip) {
                    cur_row = row + deltas[0];
                    cur_col = col + deltas[1];
                    cur_char = board[cur_row][cur_col]->getPiece();

                    while (cur_char == opponent) {
                        discsToFlip.push_back({cur_row, cur_col});
                        cur_row += deltas[0];
                        cur_col += deltas[1];
                        cur_char = board[cur_row][cur_col]->getPiece();
                    }
                }
            }
        }
    }

    for (auto pos : discsToFlip) {
        board[pos[0]][pos[1]]->setPiece(player);
    }
}

bool Board::isFlippable(Position* board[8][8], int row, int col, char player) const {
    char opponent = (player == 'b') ? 'w' : 'b';
    int surrounding[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};

    for (auto deltas : surrounding) {
        int cur_row = row + deltas[0];
        int cur_col = col + deltas[1];

        if (cur_row > 7 || cur_row < 0 || cur_col > 7 || cur_col < 0 || board[cur_row][cur_col]->getPiece() == '*')
            continue;

        char cur_char = board[cur_row][cur_col]->getPiece();

        if (cur_char == opponent) {
            while (cur_char == opponent) {
                cur_row += deltas[0];
                cur_col += deltas[1];

                if (cur_row > 7 || cur_row < 0 || cur_col > 7 || cur_col < 0 || board[cur_row][cur_col]->getPiece() == '*')
                    break;

                cur_char = board[cur_row][cur_col]->getPiece();
            }

            if (cur_char == player)
                return true;
        }
    }

    return false;
}

void Board::makeMove(Position* board[8][8], int row, int col, char player) {
    board[row][col]->setPiece(player);
    flip(board, row, col, player);
}

std::vector<std::vector<int>> Board::calculateLegalMoves(Position* board[8][8], char player) const {
    std::vector<std::vector<int>> move_list;

    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (board[i][j]->getPiece() == '-') {
                if (isFlippable(board, i, j, player)) {
                    std::vector<int> move = {i, j};
                    move_list.push_back(move);
                }
            }
        }
    }

    return move_list;
}

bool Board::isLegalMove(const std::vector<std::vector<int>>& legalMoves, int row, int col, char player) const {
    std::vector<int> proposedMove = {row, col};

    if (row > 7 || row < 0 || col > 7 || col < 0 || board[row][col]->getPiece() == '*' || board[row][col]->getPiece() != '-') {
        throw std::range_error{"isLegalMove()"};
    }

    if (board[row][col]->getPiece() != '-')
        return false;

    if (std::find(legalMoves.begin(), legalMoves.end(), proposedMove) != legalMoves.end()) {
        return true;
    }
    return false;
}

void Board::printLegalMoves(Position*board[8][8],char player, const std::string& playerName) const {
    std::cout << (player == 'b' ? "Black" : "White") << " legal moves (" << playerName << "):";
    auto legalMoves = calculateLegalMoves(board, player);
    for (const auto& vec : legalMoves) {
        std::cout << "(" << vec[0] << "," << vec[1] << ") ";
    }
    std::cout << std::endl;
}

void Board::printLegalMoves(const std::vector<std::vector<int>>& legalMoves) {
    for (const auto& vec : legalMoves) {
        std::cout << "(" << vec[0] << "," << vec[1] << ") ";
    }
    std::cout << std::endl;
}

char Board::getPiece(Position*board[8][8], int row, int col) const {
    return board[row][col]->getPiece();
}

bool Board::isGameOver(Position* board[8][8]) const {
    auto blackMoves = calculateLegalMoves(board, 'b');
    auto whiteMoves = calculateLegalMoves(board, 'w');

    if (blackMoves.empty() && whiteMoves.empty()) {
        std::cout << "DEBUG: No legal moves for both players. Game is over.\n";
        return true;
    }

    return false;
}




int Board::getScore(Position* const board[8][8],char player) const {
    int score = 0;
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (board[i][j]->getPiece() == player) {
                score++;
            }
        }
    }
    return score;
}

void Board::printWinner() const {
    int white_total = getScore(board, 'w');
    int black_total = getScore(board, 'b');

    std::cout << "Black total: " << black_total << std::endl;
    std::cout << "White total: " << white_total << std::endl;
    if (black_total == white_total) {
        std::cout << "It's a tie!" << std::endl;
    } else if (black_total > white_total) {
        std::cout << "Black wins!" << std::endl;
    } else {
        std::cout << "White wins!" << std::endl;
    }
}

void Board::setPiece(Position*board[8][8], int row, int col, char piece) {
    delete board[row][col];
    if (piece == '*') {
        board[row][col] = new UnplayablePosition();
    } else {
        board[row][col] = new PlayablePosition(piece);
    }
}

Position* (*Board::getBoard())[8] {
    return board;
}
