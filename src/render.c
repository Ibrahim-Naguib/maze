#include "../inc/main.h"

/**
 * render_sky_ground - Renders the sky and ground.
 * @state: The game state.
 * @player: The player.
 */

void render_sky_ground(State *state, Player *player)
{
	int skyHeight = SCREEN_HEIGHT / 2 + player->verticalOffset;
	ColorRGBA RGBA_Sky = {.r = 0x46, .g = 0xA4, .b = 0xFF, .a = 0xFF};
	ColorRGBA RGBA_Floor = {.r = 0x00, .g = 0x81, .b = 0x00, .a = 0xFF};
	SDL_Rect skyRect = {0, 0, SCREEN_WIDTH, skyHeight};
	SDL_Rect groundRect = {0, skyHeight, SCREEN_WIDTH, SCREEN_HEIGHT -
		skyHeight};

	SDL_SetRenderDrawColor(state->renderer, RGBA_Sky.r, RGBA_Sky.g,
			RGBA_Sky.b, RGBA_Sky.a);
	SDL_RenderFillRect(state->renderer, &skyRect);

	SDL_SetRenderDrawColor(state->renderer, RGBA_Floor.r, RGBA_Floor.g,
			RGBA_Floor.b, RGBA_Floor.a);
	SDL_RenderFillRect(state->renderer, &groundRect);
}

/**
 * calc_step_side - Calculates the step and side distances.
 * @rayDir: The ray direction.
 * @stepDir: The step direction.
 * @sideDist: The side distance.
 * @deltaDist: The delta distance.
 * @mapBox: The map box.
 * @player: The player.
 */

void calc_step_side(Vec2F rayDir, Vec2I *stepDir, Vec2F *sideDist,
		Vec2F *deltaDist, Vec2I mapBox, Player *player)
{
	if (rayDir.x < 0)
	{
		stepDir->x = -1;
		sideDist->x = (player->pos.x - mapBox.x) * deltaDist->x;
	} else
	{
		stepDir->x = 1;
		sideDist->x = (mapBox.x + 1.0f - player->pos.x) * deltaDist->x;
	}
	if (rayDir.y < 0)
	{
		stepDir->y = -1;
		sideDist->y = (player->pos.y - mapBox.y) * deltaDist->y;
	} else
	{
		stepDir->y = 1;
		sideDist->y = (mapBox.y + 1.0f - player->pos.y) * deltaDist->y;
	}
}

/**
 * perform_dda - Performs the DDA algorithm.
 * @hit: A flag to indicate if a wall was hit.
 * @mapBox: The map box.
 * @sideDist: The side distance.
 * @deltaDist: The delta distance.
 * @perpWallDist: The perpendicular wall distance.
 * @side: The side of the wall.
 * @stepDir: The step direction.
 * @MAP: The map.
 */

void perform_dda(bool hit, Vec2I mapBox, Vec2F sideDist, Vec2F deltaDist,
		float *perpWallDist, Side *side, Vec2I stepDir, const uint8_t *MAP)
{
	while (!hit)
	{
		if (sideDist.x < sideDist.y)
		{
			sideDist.x += deltaDist.x;
			mapBox.x += stepDir.x;
			*side = EastWest;
		}
		else
		{
			sideDist.y += deltaDist.y;
			mapBox.y += stepDir.y;
			*side = NorthSouth;
		}
		if (MAP[xy2index(mapBox.x, mapBox.y, MAP_SIZE)] > 0)
			hit = true;
	}

	switch (*side)
	{
		case EastWest:
			*perpWallDist = (sideDist.x - deltaDist.x);
			break;
		case NorthSouth:
			*perpWallDist = (sideDist.y - deltaDist.y);
			break;
	}
}

/**
 * draw - Draws a wall.
 * @state: The game state.
 * @player: The player.
 * @x: The X coordinate.
 * @side: The side of the wall.
 * @perpWallDist: The perpendicular wall distance.
 */

void draw(State *state, Player *player, int x, Side *side, float perpWallDist)
{
	ColorRGBA RGBA_DGray   = {.r = 0x60, .g = 0x60, .b = 0x60, .a = 0xFF};
	ColorRGBA RGBA_LGray   = {.r = 0x70, .g = 0x70, .b = 0x70, .a = 0xFF};
	ColorRGBA color = RGBA_DGray;

	int lineHeight = (int)(SCREEN_HEIGHT / perpWallDist);
	int drawStart = -lineHeight / 2 + SCREEN_HEIGHT / 2 + player->verticalOffset;
	int drawEnd = lineHeight / 2 + SCREEN_HEIGHT / 2 + player->verticalOffset;

	if (drawStart < 0)
		drawStart = 0;
	if (drawEnd >= SCREEN_HEIGHT)
		drawEnd = SCREEN_HEIGHT;

	if (*side == NorthSouth)
		color = RGBA_LGray;

	SDL_SetRenderDrawColor(state->renderer, color.r, color.g, color.b, color.a);
	SDL_RenderDrawLine(state->renderer, x, drawStart, x, drawEnd);
}
