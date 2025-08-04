#pragma once
#include <Windows.h>
#include <vector>

class Food {
    POINT position;
public:
    Food(); 
    void SpawnNew(const POINT& snakeHead, const std::vector<POINT>& snakeBody, int fieldWidth, int fieldHeight);
    const POINT& GetPosition() const;
    void Draw(HDC hdc) const;
    bool CheckEat(const POINT& SnakeHead) const;
};