#ifndef __SOLVER_DFS_HPP__
#define __SOLVER_DFS_HPP__

#include "cube.hpp"
#include <unordered_map>

class CubeSolverDFS {
  public:
    RubiksCube *cube;
    CubeSolverDFS(RubiksCube *cube);
    void solve();

  private:
    std::unordered_map<std::string, bool> visited;
    static const std::string moves[12];
    bool dfs(int depth);
};

#endif