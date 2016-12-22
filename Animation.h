#pragma once
#include <vector>

using namespace std;

struct FrameInfo {
	SDL_Rect frame;		// Sprite's x,y,w,h
	int xOffset = 0;			// Distance from elements's x centre to frame's x center. (In character it's distance from hip to frame's x middle value.)
	int yOffset = 0;			// Distance from elements's y centre to frame's y center. (In character it's distance from hip to frame's y middle value.)
	FrameInfo(SDL_Rect frame) : FrameInfo(frame, 0, 0) {};
	FrameInfo(SDL_Rect frame, int xOffset) : FrameInfo(frame, xOffset, 0) {};
	FrameInfo(SDL_Rect frame, int xOffset, int yOffset) : frame(frame), xOffset(xOffset), yOffset(yOffset) {};
};

class Animation
{
public:
	bool loop = true;
	float speed = 1.0f;
	vector<FrameInfo> frames;
private:
	float current_frame = 0.0f;
	int loops = 0;

public:
	Animation()
	{}

	Animation(const Animation& anim) : loop(anim.loop), speed(anim.speed), frames(anim.frames)
	{}

	FrameInfo& GetCurrentFrame()
	{
		float last_frame = (float)frames.size();

		current_frame += speed;
		if (current_frame >= last_frame)
		{
			current_frame = (loop) ? 0.0f : MAX(last_frame - 1.0f, 0.0f);
			loops++;
		}

		return frames[(int)current_frame];
	}

	bool Finished() const
	{
		return loops > 0;
	}

	void Reset()
	{
		current_frame = 0.0f;
	}
};