#pragma once
#include <vector>
#include <string>
#include <memory>
#include "Tank.h"
#include "Shell.h"
#include "Wall.h"
#include "Mine.h"

enum class CellType { Empty, Wall, Mine, Tank1, Tank2, Shell };

struct Cell {
    CellType type = CellType::Empty;
    std::shared_ptr<void> object = nullptr;  // Use static_cast when accessing actual object
};

class Board {
public:
    Board();
    bool loadFromFile(const std::string& filename);
    
    int getWidth() const;
    int getHeight() const;

    Cell& getCell(int x, int y);
    const Cell& getCell(int x, int y) const;

    bool isInside(int x, int y) const;
    std::pair<int, int> wrapCoords(int x, int y) const;

    void printBoard() const; // Optional for debugging

private:
    int width = 0, height = 0;
    std::vector<std::vector<Cell>> grid;

    void fillCell(int x, int y, char symbol);
    void logInputError(const std::string& message);

    std::vector<std::string> inputErrors;
};
