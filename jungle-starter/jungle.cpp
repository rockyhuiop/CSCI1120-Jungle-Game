/**
 * CSCI1120 Introduction to Computing Using C++
 *
 * I declare that the assignment here submitted is original
 * except for source material explicitly acknowledged,
 * and that the same or closely related material has not been
 * previously submitted for another course.
 * I also acknowledge that I am aware of University policy and
 * regulations on honesty in academic work, and of the disciplinary
 * guidelines and procedures applicable to breaches of such
 * policy and regulations, as contained in the website.
 *
 * University Guideline on Academic Honesty:
 *   http://www.cuhk.edu.hk/policy/academichonesty/
 *
 * Student Name : Rocky Hui
 * Student ID   : 1155172012
 * E-mail       : rockyhuiop@gmail.com
 * Class/Section: CSCI1120A
 * Date         : 13/12/2021
 */


#include <iostream>
#include "game.h"

using namespace std;

int main(int argc, char* argv[]) {
    char* filename = nullptr;
    if (argc > 1)
        filename = argv[1];

    cout << "Choose game mode (1, 2, 3): ";
    int mode;
    cin >> mode;
    Game game((Mode)mode, filename);
    game.run();
    return 0;
}
