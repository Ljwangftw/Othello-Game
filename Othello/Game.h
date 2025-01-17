#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include "Player.h"

class Game {
public:
    Game();
    static void displayMenu();
    void StartNewGame();
    void start();
    void PlayGame();
    void SaveGame(const std::string& filename);
    void LoadGame();


private:
    Player player1;
    Player player2;
    Player* currentPlayer;
    Board board;
    std::string loadedFilename;
    Position* current_board[8][8]; // Add this line
    char player_char;

};



#endif //GAME_H
