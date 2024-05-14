#include <iostream>
#include "machine.h"
#include "game.h"
#include "board.h"

using namespace std;

Machine::Machine(string name, Color color) : Player(name, color) {
    // TODO: randomize the seed of random number generator 
    //       using the current time
    int ran = 0 + (std::rand() % (this->getPieceCount() + 1));
}

// a sample machine that makes random valid moves
void Machine::makeMove(Board* board) {
    // TODO: make a random but valid move of a randomly picked piece on a board
    // Hint: there exist many ways to do so, one way is as follows:
    // - generate a random integer for picking a piece r from the player's pieces vector
    // - set y1, x1 to r->getY(), r->getX()
    // - generate random integers y2 and x2 in range of [0, H) and [0, W) respectively
    //   [or better in the y, x range of the 4 neighboring cells around (y1, x1), note to
    //    handle jumpable cells, 2 or 3 cells away, as well for Tiger and Lion]
    // - call board's move(y1, x1, y2, x2)
    // - once a valid move is returned, print the from and to cell addresses 
    //   and exit this function
    // Note: it can happen that no valid move can be found despite repeated picks.
    //       For example, only a Rat remains alive at a corner of the board while 
    //       the two cells it may go have been occupied by a Cat and a Dog.
    //       In this case, the player must surrender (set the opponent as winner).
    int y1, x1, y2, x2;
    Piece* r = this->getPiece(ran);
    y1 = r->getY();
    x1 = r->getX();


    y2 = 0 + (std::rand() % (board->H));
    x2 = 0 + (std::rand() % (board->W));

    int count = 0;
    bool valid = board->move(y1, x1, y2, x2);
    while (!valid) {
        y2 = 0 + (std::rand() % (board->H));
        x2 = 0 + (std::rand() % (board->W));
        valid = board->move(y1, x1, y2, x2);
        count++;
        if (count > 1000) {
            board->getGame()->setState(GAME_OVER);
            // TODO: set opponent as winner, 
            // e.g. by flipping the turn (if you assumed the player 
            // making the last turn before game over is the winner)
            if (this->getColor() == BLUE) {
                board->getGame()->setTurn(RED);
            }
            else {
                board->getGame()->setTurn(BLUE);
            }

            return;
        }
    }
}
