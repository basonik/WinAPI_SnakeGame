#pragma once
#include <Windows.h>
#include <vector>

class Snake {
    std::vector<POINT> body;
    int current_length;
    int direction;
public:
    Snake();
    void Grow();
    void drawSnake(HDC hdc) const;
    void Move();
    void ChangeDirection(int newDir);
    const POINT& GetHeadPosition() const;
    const std::vector<POINT>& GetBody() const;
    void setHeadPosition(const POINT& newPos);
    bool IsDead();
    void Dead();
};