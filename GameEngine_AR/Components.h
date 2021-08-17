#pragma once

#include <fstream>
#include <iostream>

#include <SFML/Graphics.hpp>

#include "Engine.h"
#include "Tile.h"
#include "Interface/States.h"

struct Transform {
public:
	ECS_DECLARE_TYPE;
	float xpos, ypos, rotation, xspeed, yspeed, xspeedMod, yspeedMod;
	bool colliding = false;

	Transform(
		float xpos,
		float ypos,
		float xspeed = 0.0f,
		float yspeed = 0.0f,
		float rotation = 0.0f) : 
		xpos(xpos),
		ypos(ypos),
		xspeed(xspeed),
		yspeed(yspeed),
		xspeedMod(xspeed),
		yspeedMod(yspeed), 
		rotation(rotation)
	{}

	void updateSpeed(float x, float y) {
		xspeed = x;
		yspeed = y;
	}

	void move() {
		if (!colliding) {
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
	bool w, a, s, d, left, right, up, down, space;

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

	bool containsTag(std::string tag) {
		return std::find(tagnames.begin(), tagnames.end(), tag) != tagnames.end();
	}
};

struct Camera {
	ECS_DECLARE_TYPE;

	sf::View cameraView;

	Camera(sf::Vector2f pivot) {
		cameraView.setCenter(pivot);
	}
};


struct TileMap
{
public:
	ECS_DECLARE_TYPE;

	float gridSizeF; // NOTE: Change this value to increase the size of the whole grid for more tile insertion

	uint32_t gridSizeU; // still unsigned int
	uint32_t layers; // The layer value used for rendering images in a certain order (see constructor)

	sf::Vector2u maxSize; // Vector to set the size of each tile
	sf::RectangleShape collisionBox; // The box outline of the tile which is rendered in RenderingSystem.cpp

	/**
		Map structure:
		1. Column of vectors
		2. Row of vectors
		3. Collection of tile pointers
	*/
	std::vector <std::vector<std::vector<Tile*>>> map; // vector in std is an "ArrayList" (not to be confused with math vector)

	TileMap()
	{
		this->gridSizeF = 50.0f;

		// return a value of new type, convert float to unsigned int
		//this->gridSizeU = static_cast<unsigned>(this->gridSizeF);
		this->gridSizeU = static_cast<unsigned int>(this->gridSizeF);

		// number of tiles (size of tiles given by gridSize)
		this->maxSize.x = 20;
		this->maxSize.y = 20;

		this->layers = 1;

		this->map.resize(this->maxSize.x);

		for (size_t _x = 0; _x < this->maxSize.x; _x++)
		{
			this->map.push_back(std::vector<std::vector<Tile*>>());

			for (size_t _y = 0; _y < this->maxSize.y; _y++)
			{
				this->map[_x].resize(this->maxSize.y);
				this->map[_x].push_back(std::vector<Tile*>());

				for (size_t _z = 0; _z < this->layers; _z++)
				{
					this->map[_x][_y].resize(this->layers);
					this->map[_x][_y].push_back(nullptr);
				}
			}
		}

		this->collisionBox.setSize(sf::Vector2f(this->gridSizeF, this->gridSizeF));
		this->collisionBox.setFillColor(sf::Color(0, 255, 0, 50));
		this->collisionBox.setOutlineColor(sf::Color::Green);
		this->collisionBox.setOutlineThickness(-1.0f);
	}

	~TileMap()
	{
		Clear();
	}

	void AddTile(const uint32_t x, const uint32_t y, const uint32_t z, bool bHasCollision)
	{
		if (States::getPause() == false)
		{
			printf("%d, %d, %d \n", maxSize.x, maxSize.y, layers);

			if (x < this->maxSize.x && x >= 0 &&
				y < this->maxSize.y && y >= 0 &&
				z < this->layers && z >= 0)
			{
				if (this->map[x][y][z] == nullptr) // if empty
				{
					this->map[x][y][z] = new Tile(x, y, this->gridSizeF, bHasCollision);
					std::cout << "Tile added" << std::endl;
				}
			}
		}
	}

	void Clear()
	{
		for (size_t _x = 0; _x < this->maxSize.x; _x++)
		{
			for (size_t _y = 0; _y < this->maxSize.y; _y++)
			{
				for (size_t _z = 0; _z < this->layers; _z++)
				{
					delete this->map[_x][_y][_z];
					this->map[_x][_y][_z] = NULL;
				}
				this->map[_x][_y].clear();
			}
			this->map[_x].clear();
		}
		this->map.clear();
	}

	void SaveTileMap(std::string fileName)
	{
		std::ofstream _saveFile;
		_saveFile.open(fileName);

		if (_saveFile.is_open() == true)
		{
			_saveFile << maxSize.x << " " << maxSize.y << "\n"
				<< gridSizeF << "\n"
				<< layers << "\n";

			for (size_t _x = 0; _x < this->maxSize.x; _x++)
			{
				for (size_t _y = 0; _y < this->maxSize.y; _y++)
				{
					for (size_t _z = 0; _z < this->layers; _z++)
					{
						if (this->map[_x][_y][_z] != nullptr)
						{
							_saveFile << _x << " " << _y << " " << _z << " " << this->map[_x][_y][_z]->ToString() << " " << "\n";
						}
					}
				}
			}
		}
		else
		{
			std::cerr << "Error: TileMap could not save to file " << fileName << "\n";
		}

		_saveFile.close();
	}

	void LoadTileMap(std::string filename)
	{
		std::printf("Loading TileMap\n");

		std::ifstream loadfile;
		loadfile.open(filename);

		if (loadfile.is_open() == true)
		{
			loadfile >> this->maxSize.x >> this->maxSize.y >> this->gridSizeF >> this->layers;
			this->gridSizeU = static_cast<uint32_t>(this->gridSizeF); // Return value of new type (float -> uint)

			Clear();

			this->map.resize(this->maxSize.x, std::vector<std::vector<Tile*>>());

			for (size_t x = 0; x < this->maxSize.x; ++x)
			{
				for (size_t y = 0; y < this->maxSize.y; ++y)
				{
					this->map.at(x).resize(this->maxSize.y, std::vector<Tile*>());
					for (size_t z = 0; z < this->layers; ++z)
					{
						this->map.at(x).at(y).resize(this->layers, nullptr);
					}
				}
			}

			int _tX, _tY, _tZ;
			bool _bColliding = false;

			while (loadfile >> _tX >> _tY >> _tZ >> _bColliding)
			{
				printf("Read %d, %d, %d\n", _tX, _tY, _tZ);
				this->map.at(_tX).at(_tY).at(_tZ) = new Tile(_tX, _tY, this->gridSizeF, _bColliding);
			}
		}
		else
			std::cerr << "Error: TileMap could not load from file `" << filename << "'" << std::endl;
		loadfile.close();
	}
};

struct FireDelay {
	float delay;
	float timeSinceLastShot;
};

ECS_DEFINE_TYPE(Transform)
ECS_DEFINE_TYPE(Sprite2D)
ECS_DEFINE_TYPE(Animator)
ECS_DEFINE_TYPE(InputController)
ECS_DEFINE_TYPE(BoxCollider)
ECS_DEFINE_TYPE(Tag)
ECS_DEFINE_TYPE(Camera)
ECS_DEFINE_TYPE(TileMap)