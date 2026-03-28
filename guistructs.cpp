#include "guistructs.h"

//--------------------------------------------------
// Texture
//--------------------------------------------------
std::string GetDLLPath(const std::string& path)
{
	char dllPath[MAX_PATH] = { 0 };
	GetModuleFileNameA(dll_handle, dllPath, MAX_PATH);

	std::string fullPath(dllPath);

	size_t lastSlash = fullPath.find_last_of("\\/");
	std::string baseDirectory = (lastSlash != std::string::npos) ? fullPath.substr(0, lastSlash + 1) : "";

	std::ostringstream ss;
	ss << baseDirectory << path;

	return ss.str();
}

Texture::Texture()
{
	texture = nullptr;
	width = 0;
	height = 0;
}

bool Texture::LoadTexture(const std::string& path)
{
	Free();

	SDL_Surface* textureSurface = IMG_Load(GetDLLPath(path).c_str());
	if (textureSurface == nullptr)
		return false;

	texture = SDL_CreateTextureFromSurface(renderer, textureSurface);

	if (texture == nullptr)
	{
		SDL_DestroySurface(textureSurface);
		return false;
	}

	width = texture->w;
	height = texture->h;

	SDL_DestroySurface(textureSurface);

	return true;
}

bool Texture::LoadTextTexture(const std::string& text,const SDL_Color color)
{
	if (texture != nullptr)
		Free();

	printf("Creating surface...\n");
	SDL_Surface* textureSurface = TTF_RenderText_Blended(windowFont, text.c_str(), text.length(), color);

	if (textureSurface == nullptr)
	{
		printf("Surface failed to create: %s\n", SDL_GetError());
		return false;
	}

	texture = SDL_CreateTextureFromSurface(renderer, textureSurface);

	if (texture == nullptr)
	{
		SDL_DestroySurface(textureSurface);
		return false;
	}

	width = texture->w;
	height = texture->h;

	SDL_DestroySurface(textureSurface);

	return true;
}

void Texture::Free()
{
	SDL_DestroyTexture(texture);
	width = 0;
	height = 0;
	texture = nullptr;

	return;
}

//--------------------------------------------------
// GUIElement
//--------------------------------------------------
void GUIElement::Render()
{
	if (!borderOnly)
	{
		SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
		SDL_RenderFillRect(renderer, &rect);
	}

	if (mainTexture != NULL)
	{
		SDL_RenderTexture(renderer, mainTexture->GetTexture(), NULL, &rect);
	}

	if (borderColor.a != 0)
	{
		SDL_SetRenderDrawColor(renderer, borderColor.r, borderColor.g, borderColor.b, borderColor.a);
		SDL_RenderRect(renderer, &rect);
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
void TextBox::Render()
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

//--------------------------------------------------
// Rendering
//--------------------------------------------------
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

void RenderGUI()
{
	for (auto& element : guiElements)
	{
		element->Render();
	}

	SDL_RenderPresent(renderer);
}