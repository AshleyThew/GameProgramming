// COMP710 GP Framework 2021
#ifndef __SCENEAUT_H__
#define __SCENEAUT_H__
// Local includes:
#include "scene.h"
// Forward declarations:
class Renderer;
class Sprite;
// Class declaration:
class SceneAUT : public Scene
{
	// Member methods:
public:
	SceneAUT();
	virtual ~SceneAUT();
	virtual bool Initialise(Renderer& renderer);
	virtual void Process(float deltaTime);
	virtual void Draw(Renderer& renderer);
	virtual void ProcessInput(InputSystem& inputSystem);
	virtual void DebugDraw();
protected:
private:
	SceneAUT(const SceneAUT& sceneAUT);
	SceneAUT& operator=(const SceneAUT& sceneAUT);
	// Member data:
public:
protected:
	float m_opacity;
	float m_totalTime;
	Sprite* m_autLogo;
	Sprite* m_autText;
private:
};
#endif // __SCENE4X01_H__