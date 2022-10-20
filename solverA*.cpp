#include "solverA*.hpp"

#include <iostream>

const std::string CubeSolverAStar::moves[12] = {
    "R", "R'", "L", "L'", "U", "U'", "D", "D'", "F", "F'", "B", "B'"};

CubeSolverAStar::CubeSolverAStar(RubiksCube *cube) { this->cube = cube; }

void CubeSolverAStar::solve() {}
