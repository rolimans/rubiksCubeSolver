#ifndef __SOLVER_ASTAR_HPP__
#define __SOLVER_ASTAR_HPP__

#include "cube.hpp"

class CubeSolverAStar {
  public:
    RubiksCube *cube;
    CubeSolverAStar(RubiksCube *cube);
    void solve();

  private:
    static const std::string moves[12];
    bool dfs(int depth);
};

#endif