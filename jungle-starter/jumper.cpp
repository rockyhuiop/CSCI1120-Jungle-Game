#include "jumper.h"
#include <algorithm>

using namespace std;

Jumper::Jumper() {
}

/* Check if animal p can jump over a river
   The 'steps' argument is used to control how many river cells to test.
   Call isJumpable(board, p, y, x, 2) to test if p can do a horizontal river jump (2 steps)
   Call isJumpable(board, p, y, x, 3) to test if p can do a vertical river jump (3 steps)
   Return true if p can jump and false otherwise (e.g. due to blocking by a Rat in river)
 */
bool Jumper::isJumpable(Board* board, Piece* p, int y, int x, int steps) {
    /* TODO: Add code to check if p can jump over 'steps' river squares 
             to the destination(y, x) */
    if (steps == 3) {
        // vertical jump
        if (y - p->getY() > 0) {
            // downward
            for (int i = p->getY() + 1; i < y; i++) {
                if (!board->isEmpty(i, x)) {
                    return false;
                }
            }
        }
        else {
            // upward
            for (int i = p->getY() - 1; i > y; i--) {
                if (!board->isEmpty(i, x)) {
                    return false;
                }
            }
        }

    }
    else if (steps == 2) {
        // horizontal jump
        if (x - p->getX() > 0) {
            // right
            for (int i = p->getX() + 1 ; i < x; i++) {
                if (!board->isEmpty(y, i)) {
                    return false;
                }
            }
        }
        else {
            // left
            for (int i = p->getX() - 1; i > x; i--) {
                if (!board->isEmpty(y, i)) {
                    return false;
                }
            }
        }
        
    }
    if (board->isRiver(y, x)) {
        return false;
    }

    return true;
}