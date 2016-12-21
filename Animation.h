#pragma once
#include <vector>

using namespace std;

struct FramePair {
	SDL_Rect frame;		// Sprite's x,y,w,h
	int offset;			// Distance from elements's x centre to frame's x center. (In character it's distance from hip to frame's x middle value.)
	//FramePair() : frame({ 0,0,0,0 }), offset(0) {};
};

class Animation
{
public:
	bool loop = true;
	float speed = 1.0f;
	vector<FramePair> frames;
private:
	float current_frame = 0.0f;
	int loops = 0;
	
public:
	Animation()
	{}

	Animation(const Animation& anim) : loop(anim.loop), speed(anim.speed), frames(anim.frames)
	{}

	FramePair& GetCurrentFrame()
	{
		float last_frame = (float) frames.size();

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