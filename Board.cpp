#include "Board.h"
#include <fstream>
#include <iostream>
#include <sstream>

Board::Board() {}

bool Board::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Cannot open file.\n";
        return false;
    }

    std::string line;
    if (getline(file, line)) {
        std::istringstream iss(line);
        if (!(iss >> width >> height)) {
            logInputError("Invalid board dimensions");
            return false;
        }
    }

    grid.resize(height, std::vector<Cell>(width));
    int row = 0;
    while (getline(file, line) && row < height) {
        for (int col = 0; col < width && col < (int)line.size(); ++col) {
            fillCell(row, col, line[col]);
        }
        ++row;
    }

    return true;
}

void Board::fillCell(int x, int y, char symbol) {
    switch (symbol) {
        case '#':
            grid[x][y].type = CellType::Wall;
            grid[x][y].object = std::make_shared<Wall>();
            break;
        case '@':
            grid[x][y].type = CellType::Mine;
            grid[x][y].object = std::make_shared<Mine>();
            break;
        case '1':
            grid[x][y].type = CellType::Tank1;
            // Tank1 should be created by GameManager so reference can be shared
            break;
        case '2':
            grid[x][y].type = CellType::Tank2;
            break;
        default:
            if (symbol != ' ')
                logInputError(std::string("Unrecognized symbol: ") + symbol);
            break;
    }
}

Cell& Board::getCell(int x, int y) {
    auto [nx, ny] = wrapCoords(x, y);
    return grid[nx][ny];
}

std::pair<int, int> Board::wrapCoords(int x, int y) const {
    return { (x + height) % height, (y + width) % width };
}

void Board::logInputError(const std::string& message) {
    inputErrors.push_back(message);
}

int Board::getWidth() const { return width; }
int Board::getHeight() const { return height; }
