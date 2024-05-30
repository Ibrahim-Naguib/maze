#include "../inc/main.h"

const uint8_t MAP[MAP_SIZE * MAP_SIZE] = {
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1,
	1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1, 1,
	1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 1, 1,
	1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1,
	1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1,
	1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1,
	1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1,
	1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1,
	1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1,
	1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
};

/**
 * xy2index - Converts 2D coordinates to a 1D array index.
 * @x: The X coordinate.
 * @y: The Y coordinate.
 * @w: The width of the 2D array.
 *
 * Return: The 1D array index.
 */

int xy2index(int x, int y, int w)
{
	return (y * w + x);
}

/**
 * render - Renders the game.
 * @state: The game state.
 * @player: The player.
 */

void render(State *state, Player *player)
{
	int x;
	int blockSize = MINI_MAP_WIDTH / MAP_SIZE;

	render_sky_ground(state, player);
	for (x = 0; x < SCREEN_WIDTH; ++x)
	{
		float cameraX = 2 * x / (float)SCREEN_WIDTH - 1;
		Vec2F rayDir = {
			.x = player->dir.x + player->plane.x * cameraX,
			.y = player->dir.y + player->plane.y * cameraX,
		};
		Vec2I mapBox = {
			.x = (int)player->pos.x,
			.y = (int)player->pos.y
		};
		Vec2F sideDist = {};
		Vec2F deltaDist = {
			.x = (rayDir.x == 0) ? 1e30 : fabsf(1 / rayDir.x),
			.y = (rayDir.y == 0) ? 1e30 : fabsf(1 / rayDir.y),
		};
		float perpWallDist = 1.0f / 1e30f;
		Vec2I stepDir = {};
		bool hit = false;
		Side side;

		calc_step_side(rayDir, &stepDir, &sideDist, &deltaDist, mapBox, player);

		perform_dda(hit, mapBox, sideDist, deltaDist, &perpWallDist,
				&side, stepDir, MAP);
		draw(state, player, x, &side, perpWallDist);
	}
	draw_mini_map(state, player, MAP, blockSize);
	draw_rays(state, player, MAP, blockSize);

}

/**
 * main - The entry point of the program.
 *
 * Return: 0 on success, non-zero on failure.
 */

int main(void)
{
	ASSERT(!SDL_Init(SDL_INIT_VIDEO),
			"SDL failed to initialize; %s\n",
			SDL_GetError());
	State state = {
		.quit = false,
	};
	init(&state);

	Player player = {
		.pos = {.x =  4.0f, .y =  4.0f},
		.dir = {.x = -1.0f, .y =  0.0f},
		.plane = {.x = 0.0f, .y = 0.66f},
		.verticalOffset = 0.0f,
	};

	int currentWeaponIndex = 0;
	WeaponData weaponData;

	loadWeaponTexture(&state, &weaponData);
	events(&state, &player, &currentWeaponIndex, MAP, &weaponData);

	for (int i = 0; i < NUM_WEAPONS; ++i)
	{
		SDL_DestroyTexture(weaponData.textures[i]);
	}
	SDL_DestroyRenderer(state.renderer);
	SDL_DestroyWindow(state.window);
	return (0);
}
