#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include "Position.h"
#include "PlayablePosition.h"
#include "UnplayablePosition.h"
#include <string>

class Board {
private:
    Position* board[8][8]{};

public:
    Board();
    ~Board();
    void display(Position* state[8][8] = nullptr) const;
    void makeMove(Position* board[8][8], int row, int col, char player);
    bool isGameOver(Position*board[8][8]) const;
    int getScore(Position*const board[8][8], char player) const;
    char getPiece(Position*board[8][8], int row, int col) const;
    void setPiece(Position*board[8][8], int row, int col, char piece);
    void printLegalMoves(Position*board[8][8],char player, const std::string& playerName) const;
    void initializeStandard();
    void initializeFourByFour();
    void flip(Position* board[8][8], int row, int col, char player);
    bool isFlippable(Position* board[8][8], int row, int col, char player) const;
    std::vector<std::vector<int>> calculateLegalMoves(Position* board[8][8], char player) const;
    bool isLegalMove(const std::vector<std::vector<int>>& legalMoves, int row, int col, char player) const;
    Position* (*getBoard())[8];
    std::vector<std::vector<int>> getBlackLegalMoves(Position* board[8][8]) const;
    std::vector<std::vector<int>> getWhiteLegalMoves(Position* board[8][8]) const;


    static void printLegalMoves(const std::vector<std::vector<int>>& legalMoves);
    void printWinner() const;
};

#endif // BOARD_H