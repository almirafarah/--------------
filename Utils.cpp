#include "Utils.h"
#include <iostream>
#include <unordered_map>

std::pair<int, int> directionToDelta(Direction dir) {
    switch (dir) {
        case Direction::U:  return {-1, 0};
        case Direction::UR: return {-1, 1};
        case Direction::R:  return {0, 1};
        case Direction::DR: return {1, 1};
        case Direction::D:  return {1, 0};
        case Direction::DL: return {1, -1};
        case Direction::L:  return {0, -1};
        case Direction::UL: return {-1, -1};
        default: return {0, 0};
    }
}

Direction rotateLeft(Direction dir, int eighthTurns) {
    return static_cast<Direction>((static_cast<int>(dir) - eighthTurns + 8) % 8);
}

Direction rotateRight(Direction dir, int eighthTurns) {
    return static_cast<Direction>((static_cast<int>(dir) + eighthTurns) % 8);
}

std::string directionToString(Direction dir) {
    switch (dir) {
        case Direction::U: return "U";
        case Direction::UR: return "UR";
        case Direction::R: return "R";
        case Direction::DR: return "DR";
        case Direction::D: return "D";
        case Direction::DL: return "DL";
        case Direction::L: return "L";
        case Direction::UL: return "UL";
        default: return "Unknown";
    }
}

std::string actionToString(TankActionType action) {
    switch (action) {
        case TankActionType::MOVE_FORWARD: return "Move Forward";
        case TankActionType::MOVE_BACKWARD: return "Move Backward";
        case TankActionType::ROTATE_LEFT_1_8: return "Rotate Left 1/8";
        case TankActionType::ROTATE_RIGHT_1_8: return "Rotate Right 1/8";
        case TankActionType::ROTATE_LEFT_1_4: return "Rotate Left 1/4";
        case TankActionType::ROTATE_RIGHT_1_4: return "Rotate Right 1/4";
        case TankActionType::SHOOT: return "Shoot";
        case TankActionType::NONE: return "None";
        default: return "Unknown Action";
    }
}

int wrapIndex(int idx, int max) {
    return (idx + max) % max;
}

bool isValidChar(char c) {
    return c == '#' || c == '1' || c == '2' || c == '@' || c == ' ';
}

void logError(const std::string& message, std::ofstream& errorFile) {
    if (errorFile.is_open()) {
        errorFile << message << "\n";
    }
}

void logStep(int playerId, const TankActionType& action, std::ofstream& outputFile) {
    if (outputFile.is_open()) {
        outputFile << "Player " << playerId << ": " << actionToString(action) << "\n";
    }
}
