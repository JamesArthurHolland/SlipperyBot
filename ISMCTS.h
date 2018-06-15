//
// Created by jamie on 12/06/18.
//

#ifndef SLIPPERYBOT_ISMCTS_H
#define SLIPPERYBOT_ISMCTS_H


#include "Trick.h"
#include "Board.h"

class ISMCTS {
public:
    static player_move run_search(Board root_state, int itermax);
};


#endif //SLIPPERYBOT_ISMCTS_H
