#include <SDL/SDL.h>
#include "events.h"

void UpdateEvents(Input* in)
{
	SDL_Event event;
	while(SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_KEYDOWN:
			in->key[event.key.keysym.sym] = 1;
			break;
		case SDL_KEYUP:
			in->key[event.key.keysym.sym] = 0;
			break;
		default:
			break;
		}
	}
}
