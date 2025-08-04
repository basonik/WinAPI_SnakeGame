#include "foodSnake.h"
#include <cstdlib>
#include <ctime>

Food::Food() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    position = { 0, 0 };
}

void Food::SpawnNew(const POINT& snakeHead, const std::vector<POINT>& snakeBody, int fieldWidth, int fieldHeight) {
    const int cellSize = 20;
    std::vector<POINT> ocuupiedPos = snakeBody;
    ocuupiedPos.push_back(snakeHead);

    std::vector<POINT> freePos;
    for (int y = 0; y < fieldHeight; y+= 1) {
        for (int x = 0; x < fieldWidth; x += 1) {
            POINT candidate = { x, y };

            bool isOccupied = false;
            for (const auto& pos : ocuupiedPos) {
                if (pos.x == candidate.x && pos.y == candidate.y) {
                    isOccupied = true;
                    break;
                }
            }
            if (!isOccupied) {
                freePos.push_back(candidate);
            }
        }
    }

    if (!freePos.empty()) {
        int randomIndex = rand() % freePos.size();
        position = freePos[randomIndex];
    }
    else {
        position = { -1,-1 };
    }
}

const POINT& Food::GetPosition() const {
    return position;
}

void Food::Draw(HDC hdc) const {
    const int cellSize = 20;
    HBRUSH brush = CreateSolidBrush(RGB(255, 0, 0)); 
    HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, brush);

    Ellipse(hdc,
        position.x * cellSize,
        position.y * cellSize,
        (position.x + 1) * cellSize,
        (position.y + 1) * cellSize);

    SelectObject(hdc, oldBrush);
    DeleteObject(brush);
}

bool Food::CheckEat(const POINT& SnakeHead) const {
    return (SnakeHead.x == position.x && SnakeHead.y == position.y);
}