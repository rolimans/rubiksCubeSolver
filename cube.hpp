#ifndef _CUBE_HPP_
#define _CUBE_HPP_

#include <random>
#include <string>
#include <vector>

class RubiksCube {
  public:
    RubiksCube();
    RubiksCube(std::string scrambleMoves);
    void reset();
    bool isSolved();
    std::string toString();
    void scramble();
    void scramble(int minMoves, int maxMoves);
    void print();
    void rightAntiClockwise();
    void rightClockwise();
    void leftAntiClockwise();
    void leftClockwise();
    void upAntiClockwise();
    void upClockwise();
    void downAntiClockwise();
    void downClockwise();
    void frontAntiClockwise();
    void frontClockwise();
    void backAntiClockwise();
    void backClockwise();
    void parseMove(std::string move);
    void parseMoves(std::string moves);
    void addToHistory(std::string move);
    void undoMove(std::string move);
    std::vector<std::string> getHistory();
    std::string getHistoryString();
    void clearHistory();

  private:
    std::vector<std::string> moveHistory;
    static const char colors[6];
    char cube[6][2][2];
    char savedState[6][2][2];
    void init();
    std::random_device rd;
    std::mt19937 gen = std::mt19937(rd());
    int randomInt(int min, int max);
};

#endif