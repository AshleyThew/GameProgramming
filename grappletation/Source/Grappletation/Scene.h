// COMP710 GP Framework 2021
#ifndef __SCENE_H__
#define __SCENE_H__
// Forward declarations:
class Renderer;
class InputSystem;
class SoundManager;
class Game;
// Class declaration:
class Scene
{
	// Member methods:
public:
	Scene();
	virtual ~Scene();
	virtual bool Initialise(Renderer& renderer) = 0;
	virtual void Process(float deltaTime, InputSystem& inputSystem, SoundManager& soundManager) = 0;
	virtual void Draw(Renderer& renderer) = 0;
	virtual void DebugDraw();
protected:
private:
	Scene(const Scene& scene);
	Scene& operator=(const Scene& scene);
	// Member data:
public:
protected:
};
#endif //__SCENE_H__