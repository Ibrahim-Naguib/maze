#include "../inc/main.h"

/**
 * init - Initializes the game.
 * @state: The game state.
 */

void init(State *state)
{
	state->window =
		SDL_CreateWindow("Maze",
				SDL_WINDOWPOS_CENTERED_DISPLAY(0),
				SDL_WINDOWPOS_CENTERED_DISPLAY(0),
				SCREEN_WIDTH,
				SCREEN_HEIGHT,
				SDL_WINDOW_ALLOW_HIGHDPI);
	ASSERT(state->window,
			"failed to create SDL window: %s\n",
			SDL_GetError());

	state->renderer =
		SDL_CreateRenderer(state->window,
				-1,
				SDL_RENDERER_PRESENTVSYNC);
	ASSERT(state->renderer,
			"failed to create SDL renderer: %s\n",
			SDL_GetError());

	SDL_SetHint(SDL_HINT_MOUSE_RELATIVE_MODE_WARP, "1");
	SDL_SetRelativeMouseMode(true);
}
