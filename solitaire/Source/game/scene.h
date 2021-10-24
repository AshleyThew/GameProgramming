// COMP710 GP Framework 2021
#ifndef __SCENE_H__
#define __SCENE_H__
#include "inputsystem.h"
// Forward declarations:
class InputSystem;
class Renderer;
// Class declaration:
class Scene
{
	// Member methods:
public:
	Scene();
	virtual ~Scene();
	virtual bool Initialise(Renderer& renderer) = 0;
	virtual void Process(float deltaTime) = 0;
	virtual void Draw(Renderer& inputSyste) = 0;
	virtual void ProcessInput(InputSystem& inputSystem) = 0;
	virtual void DebugDraw() = 0;
protected:
private:
	Scene(const Scene& scene);
	Scene& operator=(const Scene& scene);
	// Member data:
public:
protected:

};

#endif