#ifndef TANK_H
#define TANK_H

#include "board.h" // for Position
#include <string>

enum class Direction {
    U, UR, R, DR, D, DL, L, UL
};

enum class ActionType {
    MoveForward,
    MoveBackward,
    RotateLeft1_8,
    RotateRight1_8,
    RotateLeft1_4,
    RotateRight1_4,
    Shoot,
    NoOp
};

class Tank {
public:
    Tank(int playerId, Position startPos, Direction startDir);

    // Basic getters
    int getPlayerId() const;
    Position getPosition() const;
    Direction getDirection() const;

    // State control
    void performAction(ActionType action);
    bool canShoot() const;
    bool hasShells() const;
    bool isAlive() const;

    // Frame updates
    void updateCooldown();
    void markDestroyed();
    void setPosition(Position newPos);
    void setDirection(Direction dir);

    // For backward move logic
    void requestBackward();
    bool isWaitingForBackward() const;
    void cancelBackward();

    int getShellCount() const;

private:
    int playerId;
    Position pos;
    Direction dir;
    bool alive = true;

    int shellCount = 16;
    int shootCooldown = 0;

    // backward movement delay
    bool waitingBackward = false;
    int backwardWaitSteps = 0;

    void moveForward();
    void moveBackward(); // actually executes move
    void rotate(bool left, int eighths);
    void shoot();
};

#endif // TANK_H
