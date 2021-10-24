// COMP710 GP Framework 2021
#ifndef __SCENESOLITAIRE_H__
#define __SCENESOLITAIRE_H__
// Local includes:
#include "vector2.h"
#include "scene.h"
// Forward declarations:
class Renderer;
class AnimatedSprite;
class Sprite;
class Board;
class Vector2;
// Class declaration:
class SceneSolitaire : public Scene
{
	// Member methods:
public:
	SceneSolitaire();
	virtual ~SceneSolitaire();
	virtual bool Initialise(Renderer& renderer);
	virtual void Process(float deltaTime);
	virtual void Draw(Renderer& renderer);
	virtual void ProcessInput(InputSystem& inputSystem);
	virtual void DebugDraw();
	virtual void CheckGameEnd();
	virtual void CreateGame(Renderer& renderer);
protected:
private:
	SceneSolitaire(const SceneSolitaire& sceneSolitaire);
	SceneSolitaire& operator=(const SceneSolitaire& sceneSolitaire);
	// Member data:
public:
protected:
	Sprite* m_cardFace;
	AnimatedSprite* m_cardBacking;
	Board* m_board;
	Vector2* m_mousePosition;
private:
};
#endif // __SCENESOLITAIRE_H__