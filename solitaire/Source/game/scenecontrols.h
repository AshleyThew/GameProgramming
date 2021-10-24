// COMP710 GP Framework 2021
#ifndef __SCENECONTROLS_H__
#define __SCENECONTROLS_H__
// Local includes:
#include "scene.h"
// Forward declarations:
class Renderer;
class Sprite;
// Class declaration:
class SceneControls : public Scene
{
	// Member methods:
public:
	SceneControls();
	virtual ~SceneControls();
	virtual bool Initialise(Renderer& renderer);
	virtual void Process(float deltaTime);
	virtual void Draw(Renderer& renderer);
	virtual void ProcessInput(InputSystem& inputSystem);
	virtual void DebugDraw();
protected:
private:
	SceneControls(const SceneControls& sceneAUT);
	SceneControls& operator=(const SceneControls& sceneAUT);
	// Member data:
public:
protected:
	float m_opacity;
	Sprite* m_controls;
private:
};
#endif // __SCENE4X01_H__