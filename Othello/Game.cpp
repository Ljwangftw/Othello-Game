
#include "Game.h"
#include <iostream>
#include <regex>
#include <cstdlib>
#include <limits>
#include <fstream>
#include <filesystem>
#include <cstring>
#include <string>
#include <vector>
#include <algorithm>

Game::Game() : player1("Player1", 'b'), player2("Player2", 'w') {}

void Game::displayMenu() {
    std::cout << "Welcome to Othello!\n";
    std::cout << "Please select an option:\n";
    std::cout << "1. Quit\n";
    std::cout << "2. Load a Game\n";
    std::cout << "3. Start a New Game\n";
    std::cout << "Enter your choice: ";
}
void Game::StartNewGame() {
    std::string player1Name, player2Name;
    std::regex namePattern("[a-zA-Z]+");

    // Set Player 1's name
    do {
        std::cout << "Enter player 1 name: ";
        std::cin >> player1Name;
        if (!std::regex_match(player1Name, namePattern)) {
            std::cout << "Invalid name. Please try again.\n";
        }
    } while (!std::regex_match(player1Name, namePattern));
    player1.setName(player1Name);

    // Set Player 2's name
    do {
        std::cout << "Enter player 2 name: ";
        std::cin >> player2Name;
        if (!std::regex_match(player2Name, namePattern)) {
            std::cout << "Invalid name. Please try again.\n";
        }
    } while (!std::regex_match(player2Name, namePattern));
    player2.setName(player2Name);

    char player1Colour;
    do {
        std::cout << "Enter player 1 colour (b or w): ";
        std::cin >> player1Colour;
        if (player1Colour != 'b' && player1Colour != 'w') {
            std::cout << "Invalid colour. Please try again.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    } while (player1Colour != 'b' && player1Colour != 'w');
    player1.setColour(player1Colour);
    player2.setColour((player1Colour == 'w' ? 'b' : 'w'));

    // Set the current player to the player with the black color
    currentPlayer = (player1Colour == 'b') ? &player1 : &player2;

    while (true) {
        std::cout << "Choose starting position:\n";
        std::cout << "1. Standard starting position\n";
        std::cout << "2. Four-by-Four starting position\n";
        std::cout << "Enter your choice: ";

        int choice;
        std::cin >> choice;

        if (choice == 1) {
            board.initializeStandard();
            break;
        } else if (choice == 2) {
            board.initializeFourByFour();
            break;
        } else {
            std::cout << "Invalid choice. Please try again.\n";
        }
    }

    PlayGame();
}
void Game::start() {
    while (true) {
        displayMenu();
        int choice;
        std::cin >> choice;

        if (choice == 1) {
            std::cout << "Goodbye!\n";
            std::exit(0);
        }
        else if (choice == 2) { //Changes to be made here
            LoadGame();
            return;
        }
        else if (choice == 3) {
            StartNewGame();
            break;
        }
        else {
            std::cout << "Invalid choice. Please try again.\n";
        }
    }

}



void Game::PlayGame() {
    currentPlayer = (player1.getColour() == 'b') ? &player1 : &player2;
    std::regex movePattern("[0-7],[0-7]");
    while (!board.isGameOver(board.getBoard())) {
        std::vector<std::vector<int>> legalMoves = board.calculateLegalMoves(board.getBoard(),currentPlayer->getColour());
        if (legalMoves.empty()) {
            std::cout << currentPlayer->getName() << " has no legal moves.\n";
            int option;
            std::cout << "Option 1. Save\n";
            std::cout << "Option 2. Concede\n";
            std::cout << "Option 3. Skip Turn\n";
            std::cout << "Enter your choice: ";
            std::cin >> option;

            if (option == 1) {
                SaveGame("");
                exit(0);
            } else if (option == 2) {
                std::cout << currentPlayer->getName() << " has conceded. Game over.\n";
                break;
            } else if (option == 3) {
                currentPlayer = (currentPlayer == &player1 ? &player2 : &player1);
                continue;
            } else {
                std::cout << "Invalid option. Please try again.\n";
                continue;
            }
        }
        int white_total = board.getScore(board.getBoard(),'w');
        int black_total = board.getScore(board.getBoard(),'b');

        std::cout << "Black total: " << black_total << std::endl;
        std::cout << "White total: " << white_total << std::endl;
        board.display();

        board.printLegalMoves(board.getBoard(),currentPlayer->getColour(), currentPlayer->getName());

        int option;
        std::cout << "It's " << currentPlayer->getName() << "'s turn, you may choose to save, concede, or make a move.\n";
        std::cout << "Option 1. Save\n";
        std::cout << "Option 2. Concede\n";
        std::cout << "Option 3. Make a Move\n";
        std::cout << "Enter your choice: ";
        std::cin >> option;

        if (option == 1) {
            SaveGame("");
            exit(0);
        } else if (option == 2) {
            std::cout << currentPlayer->getName() << " has conceded. Game over.\n";
            break;
        } else if (option == 3) {
            std::string move;
            do {
                std::cout << currentPlayer->getName() << ", enter your move (row,col): ";
                std::cin >> move;
                if (!std::regex_match(move, movePattern)) {
                    std::cout << "Invalid move format. Please try again.\n";
                    continue;
                }
                int row = move[0] - '0';
                int col = move[2] - '0';
                if (!board.isLegalMove(legalMoves, row, col, currentPlayer->getColour())) {
                    std::cout << "Invalid move. Please try again.\n";
                    continue;
                }
                board.makeMove(board.getBoard(),row, col, currentPlayer->getColour());
                break;
            } while (true);
        } else {
            std::cout << "Invalid option. Please try again.\n";
            continue;
        }

        currentPlayer = (currentPlayer == &player1 ? &player2 : &player1);
    }

    board.printWinner();
    // Delete the saved game file after the game is over
    if (!loadedFilename.empty()) {
        std::filesystem::remove(loadedFilename);
        std::cout << "Saved game file " << loadedFilename << " has been deleted.\n";
    }
}


void Game::SaveGame(const std::string& filename) {
    // Automatically generate the filename if not provided
    std::string fullFilename;
    if (filename.empty()) {
        fullFilename = player1.getName() + " (" + player1.getColour() + ") vs " +
                       player2.getName() + " (" + player2.getColour() + ").txt";
    } else {
        fullFilename = filename;
    }

    std::ofstream outFile(fullFilename);
    if (!outFile) {
        std::cerr << "Error opening file for saving.\n";
        return;
    }

    // Save player information
    outFile << player1.getName() << " (" << player1.getColour() << ")\n";
    outFile << player2.getName() << " (" << player2.getColour() << ")\n";
    outFile << currentPlayer->getName() << '\n';

    // Save score
    outFile << "Score: " << player1.getName() << " = " << board.getScore(board.getBoard(),player1.getColour())
            << ", " << player2.getName() << " = " << board.getScore(board.getBoard(),player2.getColour()) << "\n";

    // Save board state
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            outFile << board.getPiece(board.getBoard(),i, j);
        }
        outFile << '\n';
    }

    outFile.close();
    std::cout << "Game saved successfully to " << fullFilename << ".\n";
}

void Game::LoadGame() {
    std::string path = "./"; // Directory where saved games are stored
    std::vector<std::string> savedFiles;

    // List all saved game files with a specific naming convention
    for (const auto& entry : std::filesystem::directory_iterator(path)) {
        if (entry.path().extension() == ".txt" && entry.path().filename().string().find("vs") != std::string::npos) {
            savedFiles.push_back(entry.path().filename().string());
        }
    }

    if (savedFiles.empty()) {
        std::cout << "No saved games found.\n\n";
        start();
    }

    // Display saved files
    std::cout << "Saved games:\n";
    for (size_t i = 0; i < savedFiles.size(); ++i) {
        std::cout << i + 1 << ". " << savedFiles[i] << '\n';
    }

    int choice;
    std::cout << "Enter the number of the game you would like to load: ";
    std::cin >> choice;

    if (choice < 1 || choice > savedFiles.size()) {
        std::cout << "Invalid choice. Please try again.\n";
        return;
    }

    loadedFilename = savedFiles[choice - 1]; // Set the loaded filename

    // Open the selected file
    std::ifstream inFile(loadedFilename);
    if (!inFile) {
        std::cerr << "Error: Could not open file.\n";
        return;
    }

    // Load game state
    std::string player1Info, player2Info, currentPlayerName;
    std::getline(inFile, player1Info);
    std::getline(inFile, player2Info);
    std::getline(inFile, currentPlayerName);

    player1.setName(player1Info.substr(0, player1Info.find(" (")));
    player1.setColour(player1Info[player1Info.find("(") + 1]);
    player2.setName(player2Info.substr(0, player2Info.find(" (")));
    player2.setColour(player2Info[player2Info.find("(") + 1]);

    currentPlayer = (currentPlayerName == player1.getName()) ? &player1 : &player2;

    std::string line;
    std::getline(inFile, line); // Skip "Score" line
    std::getline(inFile, line); // Skip actual score data line

    for (int i = 0; i < 8; ++i) {
        std::getline(inFile, line);
        for (int j = 0; j < 8; ++j) {
            board.setPiece(board.getBoard(),i, j, line[j]);
        }
    }

    inFile.close();
    std::cout << "Game loaded successfully.\n";

    PlayGame();
}




