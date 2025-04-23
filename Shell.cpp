#include "shell.h"
#include <utility>

// Constructor
Shell::Shell(Position startPos, Direction direction, int ownerId)
    : pos(startPos), dir(direction), ownerId(ownerId) {}

// Move 2 steps in direction of cannon
void Shell::move() {
    if (!active) return;

    auto [dx, dy] = directionToDelta(dir);
    pos.x += dx * 2;
    pos.y += dy * 2;
}

Position Shell::getPosition() const {
    return pos;
}

Direction Shell::getDirection() const {
    return dir;
}

int Shell::getOwnerId() const {
    return ownerId;
}

bool Shell::isActive() const {
    return active;
}

void Shell::deactivate() {
    active = false;
}
