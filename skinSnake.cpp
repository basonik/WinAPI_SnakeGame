#include <Windows.h>
#include <vector>
#include "skinSnake.h"

Snake::Snake() : current_length(3), direction(0) {
	body.resize(100);
	body[0] = { 5, 5 };
	body[1] = { 4, 5 };
	body[2] = { 3, 5 };
}

void Snake::Grow() {
	if (current_length < 100) {
		body[current_length] = body[current_length - 1];
		current_length += 1;
	}
}

void Snake::drawSnake(HDC hdc) const{
	for (int i = 0; i < current_length; ++i) {
		Rectangle(hdc, body[i].x * 20, body[i].y * 20, (body[i].x + 1) * 20, (body[i].y + 1) * 20);
	}
}

void Snake::Move() {
	for (int i = current_length - 1; i > 0; --i) {
		body[i] = body[i - 1];
	}
	switch (direction) {
	case 0:
		body[0].x++; break; //up
	case 1:
		body[0].y--; break; //right
	case 2:
		body[0].x--; break; //left
	case 3:
		body[0].y++; break; //down
	}
}

const POINT& Snake::GetHeadPosition() const {
	return body[0];
}

const std::vector<POINT>& Snake::GetBody() const {
	return body;
}

void Snake::ChangeDirection(int newDir) {
	if ((direction == 0 && newDir != 2) ||
		(direction == 2 && newDir != 0) ||
		(direction == 1 && newDir != 3) ||
		(direction == 3 && newDir != 1)) {
		direction = newDir;
	}
}

void Snake::setHeadPosition(const POINT& newPos) {
	body[0] = newPos;
}

bool Snake::IsDead() {
	for (size_t i = 1; i < current_length; i++) {
		if (body[0].x == body[i].x && body[0].y == body[i].y) {
			return true;
		}
	}
	return false;
}

void Snake::Dead() {
	current_length = 0;
	body.clear();
}