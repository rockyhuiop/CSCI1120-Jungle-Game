#include "rat.h"
#include <iostream>

using namespace std;

Rat::Rat(Color color, int y, int x) : Piece(color, y, x) {
    setName(PIECE_NAME[RAT-1]);
    setRank(RAT);
}

bool Rat::isMoveValid(Board* board, int y, int x) {
    // TODO: Override the superclass version of valid move checks
    // e.g., to allow a Rat to move into a square occuppied by an Elephant 
    //       to allow a Rat to enter a water square
    Piece* q = board->get(y, x);  // target cell
    if (board->isRiver(this->getY(), this->getX())) {
        if (isOpponent(q) && !(board->isRiver(q->getY(), q->getX()))) {
            return false;
        }
    }
    if (isOpponent(q) && !canCapture(q))  // cell occupied by higher-rank opponent
        return false;
    return true;
    
}

bool Rat::canCapture(Piece* p) {
    // TODO: Override the superclass version of capture checks
    // A Rat can capture an Elephant
    if (isTrapped()) {
        return true;
    }
    else {
        if ((this->getRank() >= p->getRank()) || p->getRank() == ELEPHANT) {
            return true;
        }
        else {
            return false;
        }
    }

}