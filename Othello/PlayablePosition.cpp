
#include "PlayablePosition.h"

PlayablePosition::PlayablePosition(char piece) : Position(piece) {}
bool PlayablePosition::canPlay() const {
    return getPiece() == '-';
}

