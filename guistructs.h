#pragma once
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <string>
#include <vector>
#include <sstream>
#include "SDL3/SDL.h"
#include "SDL3_ttf/SDL_ttf.h"
#include "SDL3_image/SDL_image.h"

extern SDL_Window* window;
extern SDL_Renderer* renderer;

extern HMODULE dll_handle;

extern TTF_Font* windowFont;
bool AABBMouseCheck(POINT boxStart, POINT boxEnd, POINT cursorPosition);
void RenderGUI();

std::string GetDLLPath(const std::string& path);

class Texture
{
public:
	Texture();
	~Texture() { Free(); }

	bool LoadTexture(const std::string &path);
	bool LoadTextTexture(const std::string& text,const SDL_Color color);

	void Free();

	int GetWidth() { return width; }
	int GetHeight() { return height; }

	SDL_Texture* GetTexture() { return texture; }

private:
	SDL_Texture* texture = nullptr;
	int width, height;
};

struct GUIElement
{
	GUIElement() { mainTexture = new Texture(); }
	~GUIElement() { delete(mainTexture); }

	SDL_Color color{255,255,255,255};
	SDL_Color borderColor{255,255,255,0};
	SDL_FRect rect{100,100,100,100};
	bool borderOnly = false;
	std::string name = "";
	Texture* mainTexture;

	virtual void Render();
};

/*
struct TextBox : public GUIElement
{

};
*/

struct Button : public GUIElement
{
	void (*Behavior)();
	void Interact();
};

extern std::vector<GUIElement*> guiElements;