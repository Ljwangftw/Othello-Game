//
// Created by jwang on 12/30/2024.
//

#ifndef PLAYABLEPOSITION_H
#define PLAYABLEPOSITION_H

#include "Position.h"

class PlayablePosition: public Position {
public:
        explicit PlayablePosition(char piece = '-'); //Default is empty
        bool canPlay() const override; //Playable if piece is empty

};



#endif //PLAYABLEPOSITION_H
