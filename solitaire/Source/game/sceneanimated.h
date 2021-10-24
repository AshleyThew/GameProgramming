// COMP710 GP Framework 2021
#ifndef __SCENEANIMATED_H__
#define __SCENEANIMATED_H__
// Local includes:
#include "scene.h"
// Forward declarations:
class Renderer;
class AnimatedSprite;
// Class declaration:
class SceneAnimated : public Scene
{
	// Member methods:
public:
	SceneAnimated();
	virtual ~SceneAnimated();
	virtual bool Initialise(Renderer& renderer);
	virtual void Process(float deltaTime);
	virtual void Draw(Renderer& renderer);
	virtual void ProcessInput(InputSystem& inputSystem);
	virtual void DebugDraw();
protected:
private:
	SceneAnimated(const SceneAnimated& sceneAUT);
	SceneAnimated& operator=(const SceneAnimated& sceneAUT);
	// Member data:
public:
protected:
	float m_opacity;
	AnimatedSprite* m_animatedSprite;
private:
};
#endif // __SCENEANIMATED_H__