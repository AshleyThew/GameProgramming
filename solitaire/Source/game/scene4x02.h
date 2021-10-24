// COMP710 GP Framework 2021
#ifndef __SCENE4X02_H__
#define __SCENE4X02_H__
// Local includes:
#include "scene.h"
// Forward declarations:
class Renderer;
class Ball;
// Class declaration:
class Scene4x02 : public Scene
{
	// Member methods:
public:
	Scene4x02();
	virtual ~Scene4x02();
	virtual bool Initialise(Renderer& renderer);
	virtual void Process(float deltaTime);
	virtual void Draw(Renderer& renderer);
	virtual void ProcessInput(InputSystem& inputSystem);
	virtual void DebugDraw();
protected:
private:
	Scene4x02(const Scene4x02& scene4x02);
	Scene4x02& operator=(const Scene4x02& scene4x02);
	// Member data:
public:
protected:
	Ball* m_pBalls[100];
	int m_iShowCount;
private:
};
#endif // __SCENE4X02_H__