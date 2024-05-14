#include "leopard.h"
#include <iostream>

using namespace std;

Leopard::Leopard(Color color, int y, int x) : Piece(color, y, x) {
    setName(PIECE_NAME[LEOPARD-1]);
    setRank(LEOPARD);
}

char Leopard::getLabel() const {
    char c = 'P';
    return this->getColor() == BLUE ? tolower(c) : c;
}

bool Leopard::isMoveValid(Board* board, int y, int x) {
    if (abs(getY() - y) + abs(getX() - x) != 1)  // move other than 1 square
        return false;
    return Piece::isMoveValid(board, y, x);
}
