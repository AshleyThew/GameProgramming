#pragma once
#define __TILE_H__
#ifdef __TILE_H__

#include "Vector2.h"
#include "Entity.h"
#include "Sprite.h"

class AnimatedSprite;
class InputSystem;
class Renderer;

enum TileType
{
	STRAIGHT,
	CORNERCONCAVE,
	CORNERCONVEX,
	RAILSTRAIGHT,
	RAILCONCAVE,
	RAILCONVEX,
	MIDDLE,
	GOOSURFACE,
	GOODEEP,
	BACKGROUNDLIGHT,
	BACKGROUNDDARK,
	LADDERTOP,
	LADDERMIDDLE,
	LADDERBOTTOM,
	UNDETERMINED
};

enum TileCategory
{
	BLOCK,
	RAIL = 3,
	LADDER = 12,
};

class Tile : public Entity
{
	// Member Methods:
public:
	Tile(int x, int y, TileCategory tileType);
	~Tile();
	virtual bool Initialise(Renderer& renderer, TileType tileType, int rotation);
	virtual void Process(float deltaTime);
	virtual void Draw(Renderer& renderer);
	void SetPosition(float x, float y);
	void SetScale(float scale);
	Vector2 GetID();
	void GetBounds(Vector2* &topLeft, Vector2* & bottomRight);
	TileType GetTileType();
	TileCategory GetTileCategory();
	float GetScale();
	bool GetLocked();
	void SetLocked();

protected:
private:
	Tile(const Tile& tile);
	Tile& operator=(const Tile& tile);
	// Member Data:
public:
protected:
private:
	TileType tileType;
	TileCategory tileCategory;
	Vector2 id;
	bool locked;

};
#endif __TILE_H__