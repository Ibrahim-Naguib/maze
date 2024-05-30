#include "../inc/main.h"

/**
 * draw_mini_map - Draws the mini-map.
 * @state: The game state.
 * @player: The player.
 * @MAP: The map.
 * @blockSize: The block size.
 */

void draw_mini_map(State *state, Player *player, const uint8_t *MAP,
		int blockSize)
{
	ColorRGBA RGBA_Yellow = {.r = 0xFF, .g = 0xFF, .b = 0x00, .a = 0xFF};

	for (int y = 0; y < MAP_SIZE; ++y)
	{
		for (int x = 0; x < MAP_SIZE; ++x)
		{
			if (MAP[xy2index(x, y, MAP_SIZE)] > 0)
			{
				SDL_Rect block = {x * blockSize, y * blockSize, blockSize, blockSize};

				SDL_SetRenderDrawColor(state->renderer, 0x80, 0x80, 0x80, 0xFF);
				SDL_RenderFillRect(state->renderer, &block);
			}
		}
	}

	SDL_SetRenderDrawColor(state->renderer, RGBA_Yellow.r, RGBA_Yellow.g,
			RGBA_Yellow.b, RGBA_Yellow.a);
	SDL_Rect playerRect = {(int)(player->pos.x * blockSize) - 2,
		(int)(player->pos.y * blockSize) - 2, 4, 4};
	SDL_RenderFillRect(state->renderer, &playerRect);
}

void ray_pos(Vec2F rayPos, Vec2F rayDir, Vec2I *mapBox, Vec2F *sideDist,
		Vec2F *deltaDist, Vec2I *stepDir)
{
	if (rayDir.x < 0)
	{
		stepDir->x = -1;
		sideDist->x = (rayPos.x - mapBox->x) * deltaDist->x;
	}
	else
	{
		stepDir->x = 1;
		sideDist->x = (mapBox->x + 1.0f - rayPos.x) * deltaDist->x;
	}
	if (rayDir.y < 0)
	{
		stepDir->y = -1;
		sideDist->y = (rayPos.y - mapBox->y) * deltaDist->y;
	}
	else
	{
		stepDir->y = 1;
		sideDist->y = (mapBox->y + 1.0f - rayPos.y) * deltaDist->y;
	}
}

void hit_wall(bool *hit, Vec2I *mapBox, Vec2F sideDist, Vec2F deltaDist,
		Vec2I stepDir, const uint8_t *MAP)
{
	while (!*hit)
	{
		if (sideDist.x < sideDist.y)
		{
			sideDist.x += deltaDist.x;
			mapBox->x += stepDir.x;
		}
		else
		{
			sideDist.y += deltaDist.y;
			mapBox->y += stepDir.y;
		}
		if (MAP[xy2index(mapBox->x, mapBox->y, MAP_SIZE)] > 0)
			*hit = true;
	}
}

/**
 * draw_rays - Draws rays.
 * @state: The game state.
 * @player: The player.
 * @MAP: The map.
 * @blockSize: The block size.
 */

void draw_rays(State *state, Player *player, const uint8_t *MAP, int blockSize)
{
	ColorRGBA RGBA_Red   = {.r = 0xFF, .g = 0x00, .b = 0x00, .a = 0xFF};

	for (int x = 0; x < SCREEN_WIDTH; x += 10)
	{
		float cameraX = 2 * x / (float)SCREEN_WIDTH - 1;
		Vec2F rayDir = {
			.x = player->dir.x + player->plane.x * cameraX,
			.y = player->dir.y + player->plane.y * cameraX,
		};
		Vec2F rayPos = player->pos;
		Vec2I mapBox = {
			.x = (int)rayPos.x,
			.y = (int)rayPos.y
		};
		Vec2F sideDist = {};
		Vec2F deltaDist = {
			.x = (rayDir.x == 0) ? 1e30 : fabsf(1 / rayDir.x),
			.y = (rayDir.y == 0) ? 1e30 : fabsf(1 / rayDir.y),
		};
		Vec2I stepDir = {};
		bool hit = false;

		ray_pos(rayPos, rayDir, &mapBox, &sideDist, &deltaDist, &stepDir);
		hit_wall(&hit, &mapBox, sideDist, deltaDist, stepDir, MAP);
		SDL_SetRenderDrawColor(state->renderer, RGBA_Red.r, RGBA_Red.g,
				RGBA_Red.b, RGBA_Red.a);
		SDL_RenderDrawLine(state->renderer, (int)(player->pos.x * blockSize),
				(int)(player->pos.y * blockSize),
				mapBox.x * blockSize, mapBox.y * blockSize);
	}
}
