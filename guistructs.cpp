#include "guistructs.h"

bool AABBMouseCheck(POINT boxStart, POINT boxEnd, POINT cursorPosition)
{
	if (cursorPosition.x > boxStart.x &&
		cursorPosition.y > boxStart.y &&
		cursorPosition.x < boxEnd.x &&
		cursorPosition.y < boxEnd.y)
	{
		return true;
	}

	return false;
}

void RenderGUI(SDL_Window* window,SDL_Renderer* renderer)
{
	for (auto& element : guiElements)
	{
		element->Render(renderer);
	}

	SDL_RenderPresent(renderer);
}

//--------------------------------------------------
// GUIElement
//--------------------------------------------------
void GUIElement::Render(SDL_Renderer* renderer)
{
	if (!borderOnly)
	{
		SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
		SDL_RenderFillRect(renderer, rect);
	}

	if (borderColor.a != 0)
	{
		SDL_SetRenderDrawColor(renderer, borderColor.r, borderColor.g, borderColor.b, borderColor.a);
		SDL_RenderRect(renderer, rect);
	}

	if (name != "")
	{
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	}
}

/*
//--------------------------------------------------
// TextBox
//--------------------------------------------------
void TextBox::Render(SDL_Renderer* renderer)
{
	GUIElement::Render(renderer);


}

void TextBox::Interact()
{

}*/

//--------------------------------------------------
// Button
//--------------------------------------------------
void Button::Interact()
{
	Behavior();
}

void SetMoney()
{
	*money = 99999;
}