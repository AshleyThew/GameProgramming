#include "LocationMaster.h"
#include "Renderer.h"
#include "imgui.h"
#include "Sprite.h"

LocationMaster::LocationMaster()
	: x1(0)
	, y1(0)
	, x2(0)
	, y2(0)
	, sprite(0)
	, tileSize(0)
{

}

LocationMaster::~LocationMaster()
{
	delete sprite;
}

bool
LocationMaster::Initialise(Renderer& renderer, float tileSize)
{
	sprite = renderer.CreateSprite("..\\Assets\\bullet.png");
	this->tileSize = tileSize * 8;
	return false;
}

void
LocationMaster::Process(float deltaTime)
{

}

void
LocationMaster::Draw(Renderer& renderer)
{
	sprite->SetBlueTint(0);
	sprite->SetRedTint(1);
	sprite->SetX(x1 + 192);
	sprite->SetY(y1 + 108);
	sprite->Draw(renderer);
	sprite->SetBlueTint(1);
	sprite->SetRedTint(0);
	sprite->SetX(x2 + 192);
	sprite->SetY(y2 + 108);
	sprite->Draw(renderer);
}

void
LocationMaster::DebugDraw()
{
	/*
	//ImGui::SliderInt("x1", &x1, 0, 1920-(192 * 2));
	//ImGui::SliderInt("y1", &y1, 0, 1080- (108 * 2));
	//ImGui::SliderInt("x2", &x2, 0, 1920 - (192 * 2));
	//ImGui::SliderInt("y2", &y2, 0, 1080 - (108 * 2));
	x1 = 500;
	y1 = 600;
	x2 = 550;
	y2 = 800;

	float dx = x1 - x2;
	float dy = y1 - y2;
	float maxDistance = sqrt(pow(dx, 2) + pow(dy, 2));

	float xUnit;
	float yUnit;
	if (dx != 0)
	{
		xUnit = sqrt(1 + pow(dy / dx, 2));
	}
	else
	{
		xUnit = 0;
	}

	if (dy != 0)
	{
		yUnit = sqrt(1 + pow(dx / dy, 2));
	}
	else
	{
		yUnit = 0;
	}

	Vector2 startingTile;
	startingTile.x = (int)(x2 / tileSize);
	startingTile.y = (int)(y2 / (tileSize));
	Vector2 topLeft;
	topLeft.x = startingTile.x * tileSize;
	topLeft.y = startingTile.y * tileSize;

	Vector2 step;
	step.x = dx;
	step.y = dy;

	if (dx != 0)
	{
		step.x = ((int)dx / abs((int)dx)) * tileSize;
	}
	if (dy != 0)
	{
		step.y = ((int)dy / abs((int)dy)) * tileSize;
	}

	Vector2 intervalRayLength;
	if (step.x > 0)
	{
		intervalRayLength.x = (tileSize + topLeft.x - x2) * xUnit;
	}
	else if (step.x < 0)
	{
		intervalRayLength.x = (x2 - topLeft.x) * xUnit;
	}
	else
	{
		intervalRayLength.x = 0;
	}

	if (step.y > 0)
	{
		intervalRayLength.y = (tileSize + topLeft.y - y2) * yUnit;
	}
	else if (step.y < 0)
	{
		intervalRayLength.y = (y2 - topLeft.y) * yUnit;
	}
	else
	{
		intervalRayLength.y = 0;
	}

	Vector2 currentTile;
	currentTile.x = x2;
	currentTile.y = y2;

	Vector2 totalRayLength;
	totalRayLength.x = 0;
	totalRayLength.y = 0;


	float currentDistance = 0;
	while (currentDistance < maxDistance)
	{

		if (intervalRayLength.x + totalRayLength.x < intervalRayLength.y + totalRayLength.y)
		{
			currentTile.x += step.x;
			totalRayLength.x += intervalRayLength.x;
			currentDistance = totalRayLength.x;
			intervalRayLength.x = tileSize * xUnit;


		}
		else
		{
			currentTile.y += step.y;
			totalRayLength.y += intervalRayLength.y;
			currentDistance = totalRayLength.y;
			intervalRayLength.y = tileSize * yUnit;

		}

		Vector2 currentTileUnit;
		currentTileUnit.x = (int)(currentTile.x / tileSize);
		currentTileUnit.y = (int)(currentTile.y / (tileSize));
		int x = 0;

	}


	ImGui::Text("stepx: %f, stepy: %f", step.x, step.y);
	ImGui::Text("Grid Location: %f, %f", startingTile.x, startingTile.y);
	ImGui::Text("Position Location: %f, %f", topLeft.x, topLeft.y);
	//ImGui::Text("Ray Length: %f, %f", rayLength.x, rayLength.y);
	ImGui::Text("Distance: %f", maxDistance);
	*/
}
