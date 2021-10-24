// COMP710 GP Framework 2021
#ifndef __SCENE4X01_H__
#define __SCENE4X01_H__
// Local includes:
#include "scene.h"
// Forward declarations:
class Renderer;
class Sprite;
// Class declaration:
class Scene4x01 : public Scene
{
	// Member methods:
public:
	Scene4x01();
	virtual ~Scene4x01();
	virtual bool Initialise(Renderer& renderer);
	virtual void Process(float deltaTime);
	virtual void Draw(Renderer& renderer);
	virtual void ProcessInput(InputSystem& inputSystem);
	virtual void DebugDraw();
protected:
private:
	Scene4x01(const Scene4x01& scene4x01);
	Scene4x01& operator=(const Scene4x01& scene4x01);
	// Member data:
public:
protected:
	Sprite* m_pCorners[4];
	Sprite* m_pCentre;
	float m_angle;
	float m_rotationSpeed;
private:
};
#endif // __SCENE4X01_H__