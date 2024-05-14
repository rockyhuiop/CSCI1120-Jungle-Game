#include <iostream>
#include <cctype>
#include "game.h"
#include "board.h"
#include "piece.h"
#include "elephant.h"
#include "lion.h"
#include "tiger.h"
#include "dog.h"
#include "cat.h"
#include "rat.h"
#include "leopard.h"
#include "wolf.h"
// TODO: include more necessary headers
#include "fileman.h"

using namespace std;

Board::Board(Game* game, char* filename) : 
    game(game), cells() {  // initalize cells' elements to nullptr
    // Set up the initial game board
    if (filename != nullptr)
        loadFromFile(filename, this);
    else
        init();
}

// initial gameboard configuration
void Board::init() {
    // TODO:
    // set up the Jungle chess standard initial gameboard properly;
    // add Elephants, Lions, ..., Rats to the cells array at correct positions 
    put(0,0, new Lion(BLUE, 0, 0));
    put(0,6, new Tiger(BLUE, 0, 6));
    put(1,1, new Dog(BLUE, 1, 1));
    put(1,5, new Cat(BLUE, 1, 5));
    put(2,0, new Rat(BLUE, 2, 0));
    put(2,2, new Leopard(BLUE, 2, 2));
    put(2,4, new Wolf(BLUE, 2, 4));
    put(2,6, new Elephant(BLUE, 2, 6));

    put(8,6, new Lion(RED, 8, 6));
    put(8,0, new Tiger(RED, 8, 0));
    put(7,5, new Dog(RED, 7, 5));
    put(7,1, new Cat(RED, 7, 1));
    put(6,6, new Rat(RED, 6, 6));
    put(6,4, new Leopard(RED, 6, 4));
    put(6,2, new Wolf(RED, 6, 2));
    put(6,0, new Elephant(RED, 6, 0));

    
    // TODO: also add the created pieces to each player's vector of pieces
    for (int i = 0; i <= 2; i++) {
        for (int j = 0; j <= 6; j++) {
            if (!(isEmpty(i, j))) {
                if(cells[i][j]->getColor() == BLUE)
                    game->getPlayer(BLUE)->addPiece(get(i, j));
            }
        }
    }

    for (int i = 6; i <= 8; i++) {
        for (int j = 0; j <= 6; j++) {
            if (!(isEmpty(i, j))) {
                if (cells[i][j]->getColor() == RED)
                    game->getPlayer(RED)->addPiece(get(i, j));
            }
        }
    }
}

// Return true if (y, x) is an empty cell, and false otherwise
bool Board::isEmpty(int y, int x) {
    if (cells[y][x] == EMPTY)
        return true;
    return false;
}

// Return true if (y, x) is the den on the side of the specified color, 
// and false otherwise
bool Board::isDen(int y, int x, Color color) {
    // TODO: Add your code here
    if (color == RED) {
        if (y == 0 && x == 3)
            return true;
    }
    else if (color == BLUE) {
        if (y == 8 && x == 3)
            return true;
    }
    return false;
}

// Return true if (y, x) is a trap on the side of the specified color, 
// and false otherwise
bool Board::isTrap(int y, int x, Color color) {
    // TODO: Add your code here
    if (color == RED) {
        if (y == 0) {
            if (x == 2 || x == 4)
                return true;
        }
        else if (y == 1 && x == 3) {
            return true;
        }
    }
    else if (color == BLUE) {
        if (y == 8) {
            if (x == 2 || x == 4)
                return true;
        }
        else if (y == 7 && x == 3) {
            return true;
        }
    }
    return false;
}

// Return true if (y, x) is a river cell, and false otherwise
bool Board::isRiver(int y, int x) {
    return y >= 3 && y <= 5 && (x >= 1 && x <= 2 || x >= 4 && x <= 5);
}

// Get a piece from the specified cell
Piece* Board::get(int y, int x){
    if (0 <= y && y < H && 0 <= x && x < W)
        return cells[y][x];
    return OUT_BOUND; // out of bound
}

// Put piece p onto the specified cell
void Board::put(int y, int x, Piece* p){
    cells[y][x] = p;
    if (p != EMPTY) {
        p->setY(y);
        p->setX(x);
    }
}

// Print the gameboard
void Board::print() {
    // TODO: Add code to print the HxW gameboard by looping over cells array
    // Hint: Make use of isEmpty(), isRiver(), isTrap(), isDen(), and 
    //       getLabel() of Piece to ease your work
    // Remember * for river cells, # for trap cells, X for den cells
    cout << " ";
    for (int i = 0; i < 7; i++) {
        cout << "   " << (char)('A' + i);
    }
    cout << endl << "  +";
    for (int i = 0; i < 7; i++) {
        cout << "---+";
    }
    cout << endl;
    for (int i = 0; i < 9; i++) {
        cout << i + 1 << " |";
        for (int j = 0; j < 7; j++) {
            char label = ' ';
            if (!isEmpty(i, j)) {
                label = cells[i][j]->getLabel();
            } else if (isDen(i, j, BLUE) || isDen(i, j, RED)) {
                label = 'X';
            } else if (isTrap(i, j, BLUE) || isTrap(i, j, RED)) {
                label = '#';
            } else if (isRiver(i, j)) {
                label = '*';
            }
            cout << " " << label << " |";
        }
        cout << endl << "  +";
        for (int j = 0; j < 7; j++) {
            cout << "---+";
        }
        cout << endl;
    }
    
}

// Check if the move from (y1, x1) to (y2, x2) is valid
bool Board::isMoveValid(int y1, int x1, int y2, int x2) {
    // TODO:
    // check against invalid cases, for example,
    // - the source is an empty cell
    // - the source and destination are the same position
    // - the destination is out of bound of the board (hint: use OUT_BOUND)
    // - the source piece is not of same color of current turn of the game
    // (... and anymore ?)
    // [Note: you can modify the following code if it doesn't fit your design]
    bool inValid = isEmpty(y1, x1) || (y1 == y2 && x1 == x2) || cells[y2][x2] == OUT_BOUND ||
        !(cells[y1][x1]->getColor() == game->getTurn());
    if (inValid)
        return false;

    // Piece-specific validation
    bool pvalid = cells[y1][x1]->isMoveValid(this, y2, x2);
    return pvalid;
}

// Carry out the move from (y1, x1) to (y2, x2)
bool Board::move(int y1, int x1, int y2, int x2) {
    if (isMoveValid(y1, x1, y2, x2)) {
        get(y1, x1)->move(this, y2, x2);
        cells[y1][x1] = EMPTY;
        return true;
    }
    return false;
}

// Return the pointer to the Game object
Game* Board::getGame() const {
    return game;
}
