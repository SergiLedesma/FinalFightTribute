#ifndef __MODULERENDER_H__
#define __MODULERENDER_H__

#include "Module.h"
#include "Globals.h"
#include <list>

struct SDL_Texture;
struct SDL_Renderer;
struct SDL_Rect;
struct FrameInfo;

struct BlitInfo {
	SDL_Texture* texture = nullptr;
	int x = 0;
	int y = 0;
	const FrameInfo* section = nullptr;
	float speed = 0;
	bool direction = true;
	int z = 0;
};

class ModuleRender : public Module
{
public:
	ModuleRender();
	~ModuleRender();

	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();
	bool AddBlit(SDL_Texture * texture, int x, int y, const FrameInfo * section, float speed = 1.0f, bool direction = true, bool isBackground = false);
	bool Blit(SDL_Texture * texture, int x, int y, const FrameInfo * section, float speed = 1.0f, bool direction = true);
	bool DrawQuad(const SDL_Rect& rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a, bool use_camera = true);
	void DebugCamera();

public:
	SDL_Renderer* renderer = nullptr;
	SDL_Rect camera;

private:
	std::list<BlitInfo> blitList;
};

#endif // __MODULERENDER_H__