#pragma once
#include <windows.h>
#include <string>
#include <vector>
#include "SDL3/SDL.h"
#include "SDL3_ttf/SDL_ttf.h"

extern int32_t* money;
bool AABBMouseCheck(POINT boxStart, POINT boxEnd, POINT cursorPosition);
void RenderGUI(SDL_Window* window, SDL_Renderer* renderer);
void SetMoney();

struct GUIElement
{
	SDL_Color color{255,255,255,255};
	SDL_Color borderColor{255,255,255,0};
	SDL_FRect *rect = nullptr;
	bool borderOnly = false;
	std::string name = "";

	virtual void Render(SDL_Renderer* renderer);
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