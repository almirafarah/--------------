#pragma once

#include <string>
#include <vector>
#include <utility>
#include <fstream>

enum class Direction {
    U, UR, R, DR, D, DL, L, UL
};

enum class TankActionType {
    MOVE_FORWARD,
    MOVE_BACKWARD,
    ROTATE_LEFT_1_8,
    ROTATE_RIGHT_1_8,
    ROTATE_LEFT_1_4,
    ROTATE_RIGHT_1_4,
    SHOOT,
    NONE
};

struct Position {
    int x, y;

    Position operator+(const std::pair<int, int>& delta) const {
        return {x + delta.first, y + delta.second};
    }

    bool operator==(const Position& other) const {
        return x == other.x && y == other.y;
    }
};

std::pair<int, int> directionToDelta(Direction dir);
Direction rotateLeft(Direction dir, int eighthTurns = 1);
Direction rotateRight(Direction dir, int eighthTurns = 1);
std::string directionToString(Direction dir);
std::string actionToString(TankActionType action);
int wrapIndex(int idx, int max);
bool isValidChar(char c);

void logError(const std::string& message, std::ofstream& errorFile);
void logStep(int playerId, const TankActionType& action, std::ofstream& outputFile);
