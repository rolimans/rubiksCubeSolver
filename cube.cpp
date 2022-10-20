#include "cube.hpp"
#include <iostream>
#include <sstream>

const char RubiksCube::colors[6] = {'W', 'O', 'G', 'R', 'B', 'Y'};

RubiksCube::RubiksCube() { init(); }

RubiksCube::RubiksCube(std::string scrambleMoves) {
    init();
    parseMoves(scrambleMoves);
}

void RubiksCube::init() {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                savedState[i][j][k] = cube[i][j][k] = colors[i];
            }
        }
    }
}

void RubiksCube::reset() {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                cube[i][j][k] = savedState[i][j][k];
            }
        }
    }
    clearHistory();
}

bool RubiksCube::isSolved() {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                if (cube[i][j][k] != colors[i]) {
                    return false;
                }
            }
        }
    }
    return true;
}

int RubiksCube::randomInt(int min, int max) {
    std::uniform_int_distribution<> dis(min, max);
    return dis(gen);
}

void RubiksCube::scramble() { scramble(5, 100); }

void RubiksCube::scramble(int minMoves, int maxMoves) {

    std::string possibleMoves[12] = {"R", "R'", "L", "L'", "U", "U'",
                                     "D", "D'", "F", "F'", "B", "B'"};

    int moves = randomInt(minMoves, maxMoves);

    for (int i = 0; i < moves; i++) {
        int move = randomInt(0, 11);
        parseMove(possibleMoves[move]);
    }
}

void RubiksCube::parseMoves(std::string moves) {
    std::stringstream sstream(moves);

    std::string move;
    while (std::getline(sstream, move, ' ')) {
        parseMove(move);
    }
}

void RubiksCube::parseMove(std::string move) {
    if (move == "R") {
        rightClockwise();
    } else if (move == "R'") {
        rightAntiClockwise();
    } else if (move == "L") {
        leftClockwise();
    } else if (move == "L'") {
        leftAntiClockwise();
    } else if (move == "U") {
        upClockwise();
    } else if (move == "U'") {
        upAntiClockwise();
    } else if (move == "D") {
        downClockwise();
    } else if (move == "D'") {
        downAntiClockwise();
    } else if (move == "F") {
        frontClockwise();
    } else if (move == "F'") {
        frontAntiClockwise();
    } else if (move == "B") {
        backClockwise();
    } else if (move == "B'") {
        backAntiClockwise();
    }
}

void RubiksCube::undoMove(std::string move) {
    if (move.back() == '\'') {
        move.pop_back();
    } else {
        move += '\'';
    }
    parseMove(move);
}

std::string RubiksCube::toString() {
    std::string str = "";
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                str += cube[i][j][k];
            }
        }
    }
    return str;
}

void RubiksCube::rightClockwise() {

    addToHistory("R");

    char tmp[6][2][2];
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                tmp[i][j][k] = cube[i][j][k];
            }
        }
    }

    // Adjacent faces
    cube[0][0][1] = tmp[2][0][1];
    cube[0][1][1] = tmp[2][1][1];
    cube[5][0][1] = tmp[4][1][0];
    cube[5][1][1] = tmp[4][0][0];
    cube[2][0][1] = tmp[5][0][1];
    cube[2][1][1] = tmp[5][1][1];
    cube[4][0][0] = tmp[0][1][1];
    cube[4][1][0] = tmp[0][0][1];

    // Right face rotation
    cube[3][0][0] = tmp[3][1][0];
    cube[3][0][1] = tmp[3][0][0];
    cube[3][1][0] = tmp[3][1][1];
    cube[3][1][1] = tmp[3][0][1];
}

void RubiksCube::rightAntiClockwise() {

    addToHistory("R'");

    char tmp[6][2][2];
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                tmp[i][j][k] = cube[i][j][k];
            }
        }
    }

    // Adjacent faces
    cube[0][0][1] = tmp[4][1][0];
    cube[0][1][1] = tmp[4][0][0];
    cube[5][0][1] = tmp[2][0][1];
    cube[5][1][1] = tmp[2][1][1];
    cube[2][0][1] = tmp[0][0][1];
    cube[2][1][1] = tmp[0][1][1];
    cube[4][0][0] = tmp[5][1][1];
    cube[4][1][0] = tmp[5][0][1];

    // Right face rotation
    cube[3][0][0] = tmp[3][0][1];
    cube[3][0][1] = tmp[3][1][1];
    cube[3][1][0] = tmp[3][0][0];
    cube[3][1][1] = tmp[3][1][0];
}

void RubiksCube::leftClockwise() {

    addToHistory("L");

    char tmp[6][2][2];
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                tmp[i][j][k] = cube[i][j][k];
            }
        }
    }

    // Adjacent faces
    cube[0][0][0] = tmp[4][1][1];
    cube[0][1][0] = tmp[4][0][1];
    cube[5][0][0] = tmp[2][0][0];
    cube[5][1][0] = tmp[2][1][0];
    cube[2][0][0] = tmp[0][0][0];
    cube[2][1][0] = tmp[0][1][0];
    cube[4][0][1] = tmp[5][1][0];
    cube[4][1][1] = tmp[5][0][0];

    // Left face rotation
    cube[1][0][0] = tmp[1][1][0];
    cube[1][0][1] = tmp[1][0][0];
    cube[1][1][0] = tmp[1][1][1];
    cube[1][1][1] = tmp[1][0][1];
}

void RubiksCube::leftAntiClockwise() {

    addToHistory("L'");

    char tmp[6][2][2];
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                tmp[i][j][k] = cube[i][j][k];
            }
        }
    }

    // Adjacent faces
    cube[0][0][0] = tmp[2][0][0];
    cube[0][1][0] = tmp[2][1][0];
    cube[5][0][0] = tmp[4][1][1];
    cube[5][1][0] = tmp[4][0][1];
    cube[2][0][0] = tmp[5][0][0];
    cube[2][1][0] = tmp[5][1][0];
    cube[4][0][1] = tmp[0][1][0];
    cube[4][1][1] = tmp[0][0][0];

    // Left face rotation
    cube[1][0][0] = tmp[1][0][1];
    cube[1][0][1] = tmp[1][1][1];
    cube[1][1][0] = tmp[1][0][0];
    cube[1][1][1] = tmp[1][1][0];
}

void RubiksCube::frontClockwise() {

    addToHistory("F");

    char tmp[6][2][2];
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                tmp[i][j][k] = cube[i][j][k];
            }
        }
    }

    // Adjacent faces
    cube[0][1][0] = tmp[1][1][1];
    cube[0][1][1] = tmp[1][0][1];
    cube[5][0][0] = tmp[3][1][0];
    cube[5][0][1] = tmp[3][0][0];
    cube[3][0][0] = tmp[0][1][0];
    cube[3][1][0] = tmp[0][1][1];
    cube[1][0][1] = tmp[5][0][0];
    cube[1][1][1] = tmp[5][0][1];

    // Front face rotation
    cube[2][0][0] = tmp[2][1][0];
    cube[2][0][1] = tmp[2][0][0];
    cube[2][1][0] = tmp[2][1][1];
    cube[2][1][1] = tmp[2][0][1];
}

void RubiksCube::frontAntiClockwise() {

    addToHistory("F'");

    char tmp[6][2][2];
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                tmp[i][j][k] = cube[i][j][k];
            }
        }
    }

    // Adjacent faces
    cube[0][1][0] = tmp[3][0][0];
    cube[0][1][1] = tmp[3][1][0];
    cube[5][0][0] = tmp[1][0][1];
    cube[5][0][1] = tmp[1][1][1];
    cube[3][0][0] = tmp[5][0][1];
    cube[3][1][0] = tmp[5][0][0];
    cube[1][0][1] = tmp[0][1][1];
    cube[1][1][1] = tmp[0][1][0];

    // Front face rotation
    cube[2][0][0] = tmp[2][0][1];
    cube[2][0][1] = tmp[2][1][1];
    cube[2][1][0] = tmp[2][0][0];
    cube[2][1][1] = tmp[2][1][0];
}

void RubiksCube::backClockwise() {

    addToHistory("B");

    char tmp[6][2][2];
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                tmp[i][j][k] = cube[i][j][k];
            }
        }
    }

    // Adjacent faces
    cube[0][0][0] = tmp[3][0][1];
    cube[0][0][1] = tmp[3][1][1];
    cube[5][1][0] = tmp[1][0][0];
    cube[5][1][1] = tmp[1][1][0];
    cube[3][0][1] = tmp[5][1][1];
    cube[3][1][1] = tmp[5][1][0];
    cube[1][0][0] = tmp[0][0][1];
    cube[1][1][0] = tmp[0][0][0];

    // Back face rotation
    cube[4][0][0] = tmp[4][1][0];
    cube[4][0][1] = tmp[4][0][0];
    cube[4][1][0] = tmp[4][1][1];
    cube[4][1][1] = tmp[4][0][1];
}

void RubiksCube::backAntiClockwise() {

    addToHistory("B'");

    char tmp[6][2][2];
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                tmp[i][j][k] = cube[i][j][k];
            }
        }
    }

    // Adjacent faces
    cube[0][0][0] = tmp[1][1][0];
    cube[0][0][1] = tmp[1][0][0];
    cube[5][1][0] = tmp[3][1][1];
    cube[5][1][1] = tmp[3][0][1];
    cube[3][0][1] = tmp[0][0][0];
    cube[3][1][1] = tmp[0][0][1];
    cube[1][0][0] = tmp[5][1][0];
    cube[1][1][0] = tmp[5][1][1];

    // Back face rotation
    cube[4][0][0] = tmp[4][0][1];
    cube[4][0][1] = tmp[4][1][1];
    cube[4][1][0] = tmp[4][0][0];
    cube[4][1][1] = tmp[4][1][0];
}

void RubiksCube::upClockwise() {

    addToHistory("U");

    char tmp[6][2][2];
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                tmp[i][j][k] = cube[i][j][k];
            }
        }
    }

    // Adjacent faces
    cube[3][0][0] = tmp[4][0][0];
    cube[3][0][1] = tmp[4][0][1];
    cube[1][0][0] = tmp[2][0][0];
    cube[1][0][1] = tmp[2][0][1];
    cube[2][0][0] = tmp[3][0][0];
    cube[2][0][1] = tmp[3][0][1];
    cube[4][0][0] = tmp[1][0][0];
    cube[4][0][1] = tmp[1][0][1];

    // Top face rotation
    cube[0][0][0] = tmp[0][1][0];
    cube[0][0][1] = tmp[0][0][0];
    cube[0][1][0] = tmp[0][1][1];
    cube[0][1][1] = tmp[0][0][1];
}

void RubiksCube::upAntiClockwise() {

    addToHistory("U'");

    char tmp[6][2][2];
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                tmp[i][j][k] = cube[i][j][k];
            }
        }
    }

    // Adjacent faces
    cube[3][0][0] = tmp[2][0][0];
    cube[3][0][1] = tmp[2][0][1];
    cube[1][0][0] = tmp[4][0][0];
    cube[1][0][1] = tmp[4][0][1];
    cube[2][0][0] = tmp[1][0][0];
    cube[2][0][1] = tmp[1][0][1];
    cube[4][0][0] = tmp[3][0][0];
    cube[4][0][1] = tmp[3][0][1];

    // Top face rotation
    cube[0][0][0] = tmp[0][0][1];
    cube[0][0][1] = tmp[0][1][1];
    cube[0][1][0] = tmp[0][0][0];
    cube[0][1][1] = tmp[0][1][0];
}

void RubiksCube::downClockwise() {

    addToHistory("D");

    char tmp[6][2][2];
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                tmp[i][j][k] = cube[i][j][k];
            }
        }
    }

    // Adjacent faces
    cube[3][1][0] = tmp[2][1][0];
    cube[3][1][1] = tmp[2][1][1];
    cube[1][1][0] = tmp[4][1][0];
    cube[1][1][1] = tmp[4][1][1];
    cube[2][1][0] = tmp[1][1][0];
    cube[2][1][1] = tmp[1][1][1];
    cube[4][1][0] = tmp[3][1][0];
    cube[4][1][1] = tmp[3][1][1];

    // Bottom face rotation
    cube[5][0][0] = tmp[5][1][0];
    cube[5][0][1] = tmp[5][0][0];
    cube[5][1][0] = tmp[5][1][1];
    cube[5][1][1] = tmp[5][0][1];
}

void RubiksCube::downAntiClockwise() {

    addToHistory("D'");

    char tmp[6][2][2];
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                tmp[i][j][k] = cube[i][j][k];
            }
        }
    }

    // Adjacent faces
    cube[3][1][0] = tmp[4][1][0];
    cube[3][1][1] = tmp[4][1][1];
    cube[1][1][0] = tmp[2][1][0];
    cube[1][1][1] = tmp[2][1][1];
    cube[2][1][0] = tmp[3][1][0];
    cube[2][1][1] = tmp[3][1][1];
    cube[4][1][0] = tmp[1][1][0];
    cube[4][1][1] = tmp[1][1][1];

    // Bottom face rotation
    cube[5][0][0] = tmp[5][0][1];
    cube[5][0][1] = tmp[5][1][1];
    cube[5][1][0] = tmp[5][0][0];
    cube[5][1][1] = tmp[5][1][0];
}

void RubiksCube::print() {

    for (int i = 0; i < 2; i++) {
        std::cout << "\t";
        for (int j = 0; j < 2; j++) {
            std::cout << cube[0][i][j] << " ";
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;

    for (int i = 0; i < 2; i++) {
        for (int j = 1; j < 5; j++) {
            for (int k = 0; k < 2; k++) {
                std::cout << cube[j][i][k] << " ";
            }
            std::cout << "\t";
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;

    for (int i = 0; i < 2; i++) {
        std::cout << "\t";

        for (int j = 0; j < 2; j++) {
            std::cout << cube[5][i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void RubiksCube::addToHistory(std::string move) {
    this->moveHistory.push_back(move);
}
std::vector<std::string> RubiksCube::getHistory() { return this->moveHistory; }

std::string RubiksCube::getHistoryString() {
    std::string history = "";
    for (size_t i = 0; i < this->moveHistory.size(); i++) {
        history += this->moveHistory[i] + " ";
    }
    return history;
}

void RubiksCube::clearHistory() {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                savedState[i][j][k] = cube[i][j][k];
            }
        }
    }
    this->moveHistory.clear();
}