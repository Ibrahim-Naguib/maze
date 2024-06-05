#include "../headers/main.h"

/**
 * loadWeaponTexture - Loads the weapon texture.
 * @state: The game state.
 * @weaponData: The weapon data.
 */

void loadWeaponTexture(State *state, WeaponData *weaponData)
{
	const char *weaponFiles[NUM_WEAPONS] = {
		"./assets/ak_47.bmp",
		"./assets/sniper.bmp",
		"./assets/mp5.bmp",
		"./assets/knife.bmp",
	};
	for (int i = 0; i < NUM_WEAPONS; ++i)
	{
		SDL_Surface *tempSurface = SDL_LoadBMP(weaponFiles[i]);

		ASSERT(tempSurface, "Failed to load weapon image: %s\n", SDL_GetError());

		weaponData->textures[i] = SDL_CreateTextureFromSurface(state->renderer,
				tempSurface);
		ASSERT(weaponData->textures[i], "Failed to create weapon texture: %s\n",
				SDL_GetError());

		SDL_FreeSurface(tempSurface);
	}
	SDL_QueryTexture(weaponData->textures[0], NULL, NULL, &weaponData->width,
			&weaponData->height);
}

/**
 * renderWeapon - Renders the weapon.
 * @state: The game state.
 * @weaponData: The weapon data.
 * @currentWeaponIndex: The current weapon index.
 */

void renderWeapon(State *state, WeaponData *weaponData,
		int currentWeaponIndex)
{
	SDL_Rect destRect;

	destRect.w = weaponData->width;
	destRect.h = weaponData->height;
	destRect.x = (SCREEN_WIDTH - weaponData->width) / 2;
	destRect.y = SCREEN_HEIGHT - weaponData->height;

	SDL_RenderCopy(state->renderer, weaponData->textures[currentWeaponIndex],
			NULL, &destRect);
}
