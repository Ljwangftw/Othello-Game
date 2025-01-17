
#include "Player.h"

Player::Player(const std::string &name, char colour) : name(name), colour(colour){}

std::string Player::getName() const {
    return name;
}

char Player::getColour() const {
    return colour;
}
void Player::setName(const std::string &newName) {
    name = newName;
}

void Player::setColour(char newColour) {
    colour = newColour;
}



