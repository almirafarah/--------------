#ifndef SHELL_H
#define SHELL_H

#include "board.h"
#include "tank.h"

class Shell {
public:
    Shell(Position startPos, Direction direction, int ownerId);

    void move(); // Moves 2 steps in its direction
    Position getPosition() const;
    Direction getDirection() const;
    int getOwnerId() const;
    bool isActive() const;

    void deactivate(); // Called if it hits something

private:
    Position pos;
    Direction dir;
    int ownerId;
    bool active = true;
};

#endif // SHELL_H
