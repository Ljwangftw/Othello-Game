
#ifndef PLAYER_H
#define PLAYER_H

#include <string>

class Player {
private:
    std::string name;
    char colour; //b or w
public:
    Player(const std::string& name, char colour);
    std::string getName() const;
    void setName(const std::string& newName);
    char getColour() const;
    void setColour(char newColour);

};

#endif //PLAYER_H
