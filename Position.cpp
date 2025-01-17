#include "Position.h"

Position::Position(char piece) : piece(piece) {}

char Position::getPiece() const {
    return piece;
}

void Position::setPiece(char piece) {
    this->piece = piece;
}

Position::~Position() = default;