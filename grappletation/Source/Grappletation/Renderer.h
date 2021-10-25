// COMP710 GP Framework 2021
#ifndef __RENDERER_H__
#define __RENDERER_H__
// Forward Declarations:
class TextureManager;
class Texture;
class Shader;
class VertexArray;
class Sprite;
class AnimatedSprite;
struct SDL_Window;
// Library includes:
#include <SDL.h>
class Renderer
{
	// Member methods:
public:
	Renderer();
	~Renderer();
	bool Initialise(bool windowed, int width = 0, int height = 0);
	void Clear();
	void Present();
	void SetClearColour(unsigned char r, unsigned char g, unsigned char b);
	void GetClearColour(unsigned char& r, unsigned char& g, unsigned char& b);
	int GetWidth() const;
	int GetHeight() const;
	Sprite* CreateSprite(const char* pcFilename);
	void DrawSprite(Sprite& sprite);
	AnimatedSprite* CreateAnimatedSprite(const char* pcFilename);
	void DrawAnimatedSprite(AnimatedSprite& sprite, int frame);
	void CreateStaticText(const char* pText, int pointsize);
protected:
	bool InitialiseOpenGL(int screenWidth, int screenHeight);
	void SetFullscreen(bool fullscreen);
	void LogSdlError();
	bool SetupSpriteShader();
	void SetupOffscreenFramebuffer(int fbWidth, int fbHeight);
private:
	Renderer(const Renderer& renderer);
	Renderer& operator=(const Renderer& renderer);
	// Member data:
public:
protected:
	TextureManager* m_pTextureManager;
	SDL_Window* m_pWindow;
	SDL_GLContext m_glContext;
	Shader* m_pSpriteShader;
	VertexArray* m_pSpriteVertexData;
	int m_iWidth;
	int m_iHeight;
	float m_fClearRed;
	float m_fClearGreen;
	float m_fClearBlue;
	Shader* m_pScreenQuadShader;
	unsigned int m_framebuffer;
	unsigned int m_framebufferColour;
	unsigned int m_framebufferDepthStencil;
	unsigned int m_screenQuadVarray;
	unsigned int m_screenQuadVbuffer;
	int m_frameBufferWidth;
	int m_frameBufferHeight;
private:
};
#endif // __RENDERER_H__