#pragma once

#include "Engine.h"

struct Transform {
public:
	ECS_DECLARE_TYPE;
	float xpos, ypos, rotation;

	Transform(float xpos, float ypos) : xpos(xpos), ypos(ypos), rotation(0) {}

};

struct Sprite2D {
public:
	ECS_DECLARE_TYPE;
	sf::Sprite self;
	std::string texture;
	int width, height;

	Sprite2D(std::string texture) : texture(texture) {

	}
};

struct Animator {
public:
	ECS_DECLARE_TYPE;
	int spriteWidth, spriteHeight, currentColumn, currentRow, totalColumns, totalRows;
	float currentTime, nextFrameTime;
	bool facingRight;

	Animator(int spriteWidth, int spriteHeight, float nextFrameTime, int totalColumns, int totalRows) :
	spriteWidth(spriteWidth), spriteHeight(spriteHeight), nextFrameTime(nextFrameTime), totalColumns(totalColumns), totalRows(totalRows)
	{
		currentColumn = currentRow = currentTime = 0;
		facingRight = true;
	}
};

ECS_DEFINE_TYPE(Transform)
ECS_DEFINE_TYPE(Sprite2D)
ECS_DEFINE_TYPE(Animator)