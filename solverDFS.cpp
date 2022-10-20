#include "solverDFS.hpp"

#include <iostream>

const std::string CubeSolverDFS::moves[12] = {"R", "R'", "L", "L'", "U", "U'",
                                              "D", "D'", "F", "F'", "B", "B'"};

CubeSolverDFS::CubeSolverDFS(RubiksCube *cube) { this->cube = cube; }

void CubeSolverDFS::solve() {
    for (int i = 1; i <= 20; i++) {
        if (dfs(i)) {
            break;
        }
        cube->reset();
        visited.clear();
    }
    if (cube->isSolved()) {
        std::cout << "Solution Found!" << std::endl;

        std::cout << "Number of moves: " << cube->getHistory().size()
                  << std::endl;

        std::cout << "Moves: " << cube->getHistoryString() << std::endl;

        cube->print();

    } else {
        std::cout << "Solution Not Found!" << std::endl;
        cube->print();
    }
}

bool CubeSolverDFS::dfs(int depth) {

    if (cube->isSolved()) {
        return true;
    }

    if (depth == 0) {
        return false;
    }

    for (int i = 0; i < 12; i++) {
        cube->parseMove(moves[i]);
        if (visited[cube->toString()] != true) {
            visited[cube->toString()] = true;
            if (dfs(depth - 1)) {
                return true;
            }
        }
        cube->getHistory().pop_back();
        cube->undoMove(moves[i]);
    }
    return false;
}