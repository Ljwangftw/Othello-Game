//
// Created by jwang on 12/30/2024.
//

#ifndef UNPLAYABLEPOSITION_H
#define UNPLAYABLEPOSITION_H
#include "Position.h"


class UnplayablePosition : public Position{
public:
    UnplayablePosition(char piece = '*');
    bool canPlay() const override;
    char getPiece() const override;

};



#endif //UNPLAYABLEPOSITION_H
