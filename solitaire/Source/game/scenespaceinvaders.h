// COMP710 GP Framework 2021
#ifndef __SCENESPACEINVADERS_H__
#define __SCENESPACEINVADERS_H__
// Local includes:
#include "scene.h"
// Forward declarations:
class Renderer;
class Sprite;
// Class declaration:
class SceneSpaceInvaders : public Scene
{
	// Member methods:
public:
	SceneSpaceInvaders();
	virtual ~SceneSpaceInvaders();
	virtual bool Initialise(Renderer& renderer);
	virtual void Process(float deltaTime);
	virtual void Draw(Renderer& renderer);
	virtual void ProcessInput(InputSystem& inputSystem);
	virtual void DebugDraw();
protected:
private:
	SceneSpaceInvaders(const SceneSpaceInvaders& sceneAUT);
	SceneSpaceInvaders& operator=(const SceneSpaceInvaders& sceneAUT);
	// Member data:
public:
protected:
	float m_opacity;
	Sprite* m_autLogo;
private:
};
#endif // __SCENESPACEINVADERS_H__