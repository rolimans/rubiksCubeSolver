#include "cube.hpp"
#include "solverDFS.hpp"

#include <iostream>

int main() {

    RubiksCube cube;
    cube.scramble(3, 3);

    CubeSolverDFS solver(&cube);

    std::cout << "Scrambled Cube Moves: " << cube.getHistoryString()
              << std::endl;

    cube.print();

    cube.clearHistory();

    solver.solve();

    return 0;
}