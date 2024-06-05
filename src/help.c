#include "../headers/main.h"

/**
 * help - Initializes the help system.
 * @state: The game state.
 *
 * Description: This function initializes the help system.
 */

void help(State *state)
{
	if (TTF_Init() == -1)
	{
		printf("TTF_Init Error: %s\n", TTF_GetError());
		SDL_DestroyRenderer(state->renderer);
		SDL_DestroyWindow(state->window);
		SDL_Quit();
		exit(1);
	}

	state->font = TTF_OpenFont("./font/font.ttf", 16);
	if (state->font == NULL)
	{
		printf("TTF_OpenFont Error: %s\n", TTF_GetError());
		TTF_Quit();
		SDL_DestroyRenderer(state->renderer);
		SDL_DestroyWindow(state->window);
		SDL_Quit();
		exit(1);
	}
}

/**
 * renderText - Renders text to the screen.
 * @state: The game state.
 * @message: The message to render.
 * @x: The X position of the text.
 * @y: The Y position of the text.
 * @color: The color of the text.
 *
 * Description: This function renders text to the screen.
 */

void renderText(State *state, const char *message, int x, int y,
		SDL_Color color)
{
	SDL_Surface *surface = TTF_RenderText_Solid(state->font, message, color);
	SDL_Texture *texture = SDL_CreateTextureFromSurface(state->renderer, surface);

	SDL_Rect dest;

	dest.x = x;
	dest.y = y;
	dest.w = surface->w;
	dest.h = surface->h;

	SDL_FreeSurface(surface);

	SDL_RenderCopy(state->renderer, texture, NULL, &dest);
	SDL_DestroyTexture(texture);
}

/**
 * render_help - Renders the help screen.
 * @state: The game state.
 *
 * Description: This function renders the help screen.
 */

void render_help(State *state)
{
	SDL_Color white = {255, 255, 255, 255};

	renderText(state, "H -> Help", SCREEN_WIDTH - 100, SCREEN_HEIGHT - 700,
			white);

	if (state->showHelp)
	{
		SDL_Color white = {255, 255, 255, 255};

		renderText(state, "Change weapon: 1, 2, 3, 4", SCREEN_WIDTH - 200,
				SCREEN_HEIGHT - 670, white);
		renderText(state, "Show/hide map: M", SCREEN_WIDTH - 200,
				SCREEN_HEIGHT - 640, white);
		renderText(state, "Show/hide rain: R", SCREEN_WIDTH - 200,
				SCREEN_HEIGHT - 610, white);
	}
}
