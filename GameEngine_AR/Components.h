#pragma once

#include "Engine.h"
#include <iostream>

struct Transform {
public:
	ECS_DECLARE_TYPE;
	float xpos, ypos, rotation, xspeed, yspeed, xspeedMod, yspeedMod;
	bool colliding = false;

	Transform(
		float xpos,
		float ypos,
		float xspeed = 0.0f,
		float yspeed = 0.0f) : 
		xpos(xpos),
		ypos(ypos),
		xspeed(xspeed),
		yspeed(yspeed),
		xspeedMod(xspeed),
		yspeedMod(yspeed) 
	{}

	void updateSpeed(float x, float y) {
		xspeed = x;
		yspeed = y;
	}

	void move() {
		if (!colliding) {
			// halve the speed when moving diagonally
			if (xspeed != 0 &&	yspeed != 0) {
				xspeed /= 2;
				yspeed /= 2;
			}

			xpos += xspeed;
			ypos += yspeed;
		}
	}
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
		currentColumn = currentRow = 0;
		currentTime = 0.0f;
		facingRight = true;
	}
};

struct InputController {
public:
	ECS_DECLARE_TYPE;

	bool inputActive;
	bool w, a, s, d, left, right, up, down;

	InputController() {
		std::memset(this, false, sizeof(InputController));
		inputActive = true;
	}
};

struct BoxCollider {
public:
	ECS_DECLARE_TYPE;
	int leftEdge, rightEdge, bottomEdge, topEdge;

	BoxCollider() {
		std::memset(this, 0, sizeof(BoxCollider));
	}

	void update(int x, int y, int width, int height) {
		leftEdge = x;
		rightEdge = x + width;
		topEdge = y;
		bottomEdge = y + height;
	}
};

struct Tag {
	ECS_DECLARE_TYPE;

	std::vector<std::string> tagnames;

	Tag() = default;

	void addTag(std::string tag) {
		tagnames.push_back(tag);
	}
};

struct Camera {
	ECS_DECLARE_TYPE;

	sf::View cameraView;

	Camera(sf::Vector2f pivot) {
		cameraView.setCenter(pivot);
	}
};

ECS_DEFINE_TYPE(Transform)
ECS_DEFINE_TYPE(Sprite2D)
ECS_DEFINE_TYPE(Animator)
ECS_DEFINE_TYPE(InputController)
ECS_DEFINE_TYPE(BoxCollider)
ECS_DEFINE_TYPE(Tag)
ECS_DEFINE_TYPE(Camera)