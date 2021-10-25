#pragma once
#include "Entity.h"

class Vector2;


class Door : public Entity
{
	public:
		Door(int x, int y);
		~Door();
		virtual bool Initialise(Renderer& renderer, int rotation, float scale);
		virtual void Process(float deltaTime);
		virtual void Draw(Renderer& renderer);
		void SetOpen(bool pressed);
		Vector2 GetID();
	protected:
	private:
		void PlayAnimation(float deltaTime);
	public:
	protected:
	private:
		Vector2 id;
		float currentAnimationFrame; //From 0 to 1, 0 is not pressed and 1 is pressed
		float const MOVEMENTSPEED = 5;
		bool open;
		Vector2 MAXDISTANCE;
		Vector2 initialPosition;

};

