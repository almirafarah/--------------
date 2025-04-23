#include "tank.h"
#include <iostream>
#include <map>

// Utility to get dx, dy for direction
std::pair<int, int> directionToDelta(Direction dir) {
    static std::map<Direction, std::pair<int, int>> deltas = {
        {Direction::U,  {0, -1}},
        {Direction::UR, {1, -1}},
        {Direction::R,  {1, 0}},
        {Direction::DR, {1, 1}},
        {Direction::D,  {0, 1}},
        {Direction::DL, {-1, 1}},
        {Direction::L,  {-1, 0}},
        {Direction::UL, {-1, -1}}
    };
    return deltas[dir];
}

// Rotate a direction by given steps (45° = 1 step)
Direction rotateDirection(Direction dir, int steps, bool left) {
    static std::vector<Direction> dirs = {
        Direction::U, Direction::UR, Direction::R, Direction::DR,
        Direction::D, Direction::DL, Direction::L, Direction::UL
    };

    int idx = 0;
    for (size_t i = 0; i < dirs.size(); ++i) {
        if (dirs[i] == dir) {
            idx = i;
            break;
        }
    }

    int newIdx = (left) ? (idx - steps + 8) % 8 : (idx + steps) % 8;
    return dirs[newIdx];
}

// Constructor
Tank::Tank(int playerId, Position startPos, Direction startDir)
    : playerId(playerId), pos(startPos), dir(startDir) {}

// Accessors
int Tank::getPlayerId() const { return playerId; }
Position Tank::getPosition() const { return pos; }
Direction Tank::getDirection() const { return dir; }
bool Tank::isAlive() const { return alive; }
bool Tank::canShoot() const { return shootCooldown == 0 && shellCount > 0; }
bool Tank::hasShells() const { return shellCount > 0; }
int Tank::getShellCount() const { return shellCount; }
bool Tank::isWaitingForBackward() const { return waitingBackward; }

void Tank::setPosition(Position newPos) {
    pos = newPos;
}

void Tank::setDirection(Direction newDir) {
    dir = newDir;
}

void Tank::markDestroyed() {
    alive = false;
}

void Tank::updateCooldown() {
    if (shootCooldown > 0) shootCooldown--;
    if (waitingBackward && backwardWaitSteps > 0) backwardWaitSteps--;
}

// Cancel backward request
void Tank::cancelBackward() {
    waitingBackward = false;
    backwardWaitSteps = 0;
}

// Backward request logic
void Tank::requestBackward() {
    if (!waitingBackward) {
        waitingBackward = true;
        backwardWaitSteps = 2;  // wait 2 turns before moving
    }
}

// Core action processor
void Tank::performAction(ActionType action) {
    if (!alive) return;

    if (waitingBackward) {
        if (action == ActionType::MoveBackward && backwardWaitSteps == 0) {
            moveBackward();
            waitingBackward = false;
        } else if (action == ActionType::MoveForward) {
            cancelBackward(); // cancels backward wait
        } else {
            // ignore all other actions during wait
        }
        return;
    }

    switch (action) {
        case ActionType::MoveForward:
            moveForward();
            break;
        case ActionType::MoveBackward:
            requestBackward();
            break;
        case ActionType::RotateLeft1_8:
            dir = rotateDirection(dir, 1, true);
            break;
        case ActionType::RotateRight1_8:
            dir = rotateDirection(dir, 1, false);
            break;
        case ActionType::RotateLeft1_4:
            dir = rotateDirection(dir, 2, true);
            break;
        case ActionType::RotateRight1_4:
            dir = rotateDirection(dir, 2, false);
            break;
        case ActionType::Shoot:
            shoot();
            break;
        case ActionType::NoOp:
        default:
            break;
    }
}

// Move forward in the direction of the cannon
void Tank::moveForward() {
    auto [dx, dy] = directionToDelta(dir);
    pos.x += dx;
    pos.y += dy;
}

// Move backward (opposite of direction)
void Tank::moveBackward() {
    auto [dx, dy] = directionToDelta(dir);
    pos.x -= dx;
    pos.y -= dy;
}

// Shoot (only if cooldown allows)
void Tank::shoot() {
    if (canShoot()) {
        shellCount--;
        shootCooldown = 4;
        // Actual shell creation is handled by GameManager
    }
}
