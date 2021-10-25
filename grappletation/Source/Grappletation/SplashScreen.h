#pragma once

class Renderer;
class Sprite;

class SplashScreen
{
public:
	SplashScreen();
	~SplashScreen();
	bool Initialise(Renderer& renderer, const char* spriteLocation);
	bool Process(float deltaTime);
	void Draw(Renderer& renderer);
protected:
private:
public:
protected:
private:
	Sprite* sprite;
	int direction;
	float alpha;
	const float SPEED = 0.5;
};

