#include "../headers/main.h"

/**
 * updateRain - Updates the raindrops.
 * @state: The game state.
 *
 * Description: This function updates the raindrops.
 */

void updateRain(State *state)
{
	if (!state->rain)
		return;

	for (int i = 0; i < MAX_RAINDROPS; i++)
	{
		state->raindrops[i].x += FIXED_SPEED * ANGLE;
		state->raindrops[i].y += FIXED_SPEED;

		if (state->raindrops[i].y > SCREEN_HEIGHT)
		{
			state->raindrops[i].x = rand() % SCREEN_WIDTH;
			state->raindrops[i].y = 0;
			state->raindrops[i].z = (float)(rand() % 100) / 100.0f;
		}

		if (state->raindrops[i].x > SCREEN_WIDTH)
			state->raindrops[i].x -= SCREEN_WIDTH;
	}
}

/**
 * renderRain - Renders the raindrops.
 * @state: The game state.
 *
 * Description: This function renders the raindrops.
 */

void renderRain(State *state)
{
	if (!state->rain)
		return;

	SDL_SetRenderDrawColor(state->renderer, 173, 216, 230, 128);

	for (int i = 0; i < MAX_RAINDROPS; i++)
	{
		int x1 = (int)state->raindrops[i].x;
		int y1 = (int)state->raindrops[i].y;
		int dropLength = DROP_LENGTH * state->raindrops[i].z;
		int x2 = x1 + (int)(dropLength * ANGLE);
		int y2 = y1 + dropLength;

		SDL_RenderDrawLine(state->renderer, x1, y1, x2, y2);
	}
}
