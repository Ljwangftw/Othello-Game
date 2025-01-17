#include "UnplayablePosition.h"

UnplayablePosition::UnplayablePosition(char piece) : Position(piece) {}
bool UnplayablePosition::canPlay() const {
    return false;
}

char UnplayablePosition::getPiece() const {
    return '*';
}

