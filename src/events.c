#include "../headers/main.h"

/**
 * handleKeydownEvent - Handles keydown events.
 * @currentWeaponIndex: The current weapon index.
 * @key: The key pressed.
 * @state: The game state.
 */

void handleKeydownEvent(int *currentWeaponIndex, SDL_Keycode key, State *state)
{
	switch (key)
	{
		case SDLK_1:
			*currentWeaponIndex = 0;
			break;
		case SDLK_2:
			*currentWeaponIndex = 1;
			break;
		case SDLK_3:
			*currentWeaponIndex = 2;
			break;
		case SDLK_4:
			*currentWeaponIndex = 3;
			break;
		case SDLK_m:
			state->showMiniMap = !state->showMiniMap;
			break;
		case SDLK_r:
			state->rain = !state->rain;
			break;
		case SDLK_h:
			state->showHelp = !state->showHelp;
			break;
	}
}

/**
 * handleSDLEvents - Handles SDL events.
 * @state: The game state.
 * @player: The player.
 * @currentWeaponIndex: The current weapon index.
 * @mouse_xrel: The relative mouse position.
 */

void handleSDLEvents(State *state, Player *player,
		int *currentWeaponIndex, int *mouse_xrel)
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				state->quit = true;
				break;
			case SDL_MOUSEMOTION:
				*mouse_xrel = event.motion.xrel;
				player->verticalOffset -= event.motion.yrel;
				break;
			case SDL_KEYDOWN:
				handleKeydownEvent(currentWeaponIndex, event.key.keysym.sym, state);
				break;
		}
	}
}

/**
 * rotatePlayer - Rotates the player.
 * @player: The player.
 * @rotateSpeed: The rotation speed.
 * @mouse_xrel: The relative mouse position.
 */

void rotatePlayer(Player *player, float rotateSpeed, int mouse_xrel)
{
	if (mouse_xrel != 0)
	{
		float rotSpeed = rotateSpeed * (mouse_xrel * -0.1);
		Vec2F oldDir = player->dir;
		Vec2F oldPlane = player->plane;

		player->dir.x = player->dir.x * cosf(rotSpeed) -
			player->dir.y * sinf(rotSpeed);
		player->dir.y = oldDir.x * sinf(rotSpeed) + player->dir.y * cosf(rotSpeed);

		player->plane.x = player->plane.x * cosf(rotSpeed) -
			player->plane.y * sinf(rotSpeed);
		player->plane.y = oldPlane.x * sinf(rotSpeed) +
			player->plane.y * cosf(rotSpeed);
	}
}

/**
 * movePlayer - Moves the player.
 * @player: The player.
 * @MAP: The map.
 * @moveSpeed: The movement speed.
 * @keystate: The keyboard state.
 */

void movePlayer(Player *player, uint8_t *MAP,
		float moveSpeed, const uint8_t *keystate)
{
	Vec2F deltaPos = {
		.x = player->dir.x * moveSpeed,
		.y = player->dir.y * moveSpeed,
	};
	if (keystate[SDL_SCANCODE_W])
	{
		if (MAP[xy2index(player->pos.x + deltaPos.x, player->pos.y, MAP_SIZE)] == 0)
			player->pos.x += deltaPos.x;
		if (MAP[xy2index(player->pos.x, player->pos.y + deltaPos.y, MAP_SIZE)] == 0)
			player->pos.y += deltaPos.y;
	}
	if (keystate[SDL_SCANCODE_S])
	{
		if (MAP[xy2index(player->pos.x - deltaPos.x, player->pos.y, MAP_SIZE)] == 0)
			player->pos.x -= deltaPos.x;
		if (MAP[xy2index(player->pos.x, player->pos.y - deltaPos.y, MAP_SIZE)] == 0)
			player->pos.y -= deltaPos.y;
	}
	if (keystate[SDL_SCANCODE_A])
	{
		if (MAP[xy2index(player->pos.x - deltaPos.y, player->pos.y, MAP_SIZE)] == 0)
			player->pos.x -= deltaPos.y;
		if (MAP[xy2index(player->pos.x, player->pos.y + deltaPos.x, MAP_SIZE)] == 0)
			player->pos.y += deltaPos.x;
	}
	if (keystate[SDL_SCANCODE_D])
	{
		if (MAP[xy2index(player->pos.x + deltaPos.y, player->pos.y, MAP_SIZE)] == 0)
			player->pos.x += deltaPos.y;
		if (MAP[xy2index(player->pos.x, player->pos.y - deltaPos.x, MAP_SIZE)] == 0)
			player->pos.y -= deltaPos.x;
	}
}

/**
 * events - Handles game events.
 * @state: The game state.
 * @player: The player.
 * @currentWeaponIndex: The current weapon index.
 * @MAP: The map.
 * @weaponData: The weapon data.
 *
 * Return: The current weapon index.
 */

void events(State *state, Player *player, int *currentWeaponIndex,
	 uint8_t *MAP, WeaponData *weaponData)
{
	const float rotateSpeed = 0.025;
	const float moveSpeed = 0.035;

	while (!state->quit)
	{
		int mouse_xrel = 0;
		const uint8_t *keystate = SDL_GetKeyboardState(NULL);

		handleSDLEvents(state, player, currentWeaponIndex, &mouse_xrel);

		if (keystate[SDL_SCANCODE_ESCAPE])
			state->quit = true;

		rotatePlayer(player, rotateSpeed, mouse_xrel);
		movePlayer(player, MAP, moveSpeed, keystate);
		render(state, player, MAP);
		render_help(state);
		updateRain(state);
		renderRain(state);
		renderWeapon(state, weaponData, *currentWeaponIndex);
		SDL_RenderPresent(state->renderer);
	}
}
