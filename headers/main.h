#ifndef MAIN_H
#define MAIN_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

#define ASSERT(cond, ...) \
	do { \
		if (!(cond)) \
		{ \
			fprintf(stderr, __VA_ARGS__); \
			exit(1); \
		} \
	} while (0)


#define MIN(x, y) (x < y ? x : y)
#define MAX(x, y) (x > y ? x : y)

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define MINI_MAP_WIDTH 128
#define MINI_MAP_HEIGHT 128

#define MAP_SIZE 16
extern uint8_t MAP[MAP_SIZE * MAP_SIZE];
#define PI 3.14159265f
#define NUM_WEAPONS 4
#define MAX_RAINDROPS 400
#define MAX_CLOUDS 5
#define FIXED_SPEED 2.0f
#define ANGLE 0.5f
#define DROP_LENGTH 10


/**
 * enum side - Represents directions or sides.
 * @NorthSouth: Represents the North-South direction.
 * @EastWest: Represents the East-West direction.
 *
 * Description: This enum represents directions or sides, such as
 *              North-South and East-West.
 */

typedef enum side
{
	NorthSouth, EastWest
} Side;

/**
 * struct vec2f - Represents a 2D vector with float components.
 * @x: The X component of the vector.
 * @y: The Y component of the vector.
 *
 * Description: This struct represents a 2D vector with float components.
 */

typedef struct vec2f
{
	float x;
	float y;
} Vec2F;

/**
 * struct vec2i - Represents a 2D vector with integer components.
 * @x: The X component of the vector.
 * @y: The Y component of the vector.
 *
 * Description: This struct represents a 2D vector with integer components.
 */

typedef struct vec2i
{
	int x;
	int y;
} Vec2I;

/**
 * struct rain - Represents a raindrop.
 * @x: The X position of the raindrop.
 * @y: The Y position of the raindrop.
 * @z: The Z position of the raindrop.
 * @speed: The speed of the raindrop.
 *
 * Description: This struct represents a raindrop.
 */

typedef struct rain
{
	float x, y, z;
	float speed;
} Raindrop;


/**
 * struct state - Represents the state of the game.
 * @window: The SDL window.
 * @renderer: The SDL renderer.
 * @quit: A flag indicating whether the game should quit.
 * @showMiniMap: A flag indicating whether the mini-map should be shown.
 * @rain: A flag indicating whether it is raining.
 * @raindrops: An array of raindrops.
 * @font: The font used for rendering text.
 * @showHelp: A flag indicating whether the help screen should be shown.
 *
 * Description: This struct represents the state of the game.
 */

typedef struct state
{
	SDL_Window *window;
	SDL_Renderer *renderer;
	bool quit;
	bool showMiniMap;
	bool rain;
	Raindrop raindrops[MAX_RAINDROPS];
	TTF_Font *font;
	int showHelp;
} State;

/**
 * struct player - Represents the player in the game.
 * @pos: The position of the player.
 * @dir: The direction vector of the player.
 * @plane: The plane vector of the player.
 * @verticalOffset: The vertical offset of the player.
 *
 * Description: This struct represents the player in the game.
 */

typedef struct player
{
	Vec2F pos;
	Vec2F dir;
	Vec2F plane;
	float verticalOffset;
} Player;

/**
 * struct colorrgba - Represents a color in RGBA format.
 * @r: The red component of the color.
 * @g: The green component of the color.
 * @b: The blue component of the color.
 * @a: The alpha component of the color.
 *
 * Description: This struct represents a color in RGBA format.
 */

typedef struct colorrgba
{
	uint8_t r, g, b, a;
} ColorRGBA;

/**
 * struct weapondata - Represents data related to weapons.
 * @textures: An array of SDL textures for different weapons.
 * @width: The width of the weapon.
 * @height: The height of the weapon.
 *
 * Description: This struct represents data related to weapons.
 */

typedef struct weapondata
{
	SDL_Texture * textures[NUM_WEAPONS];
	int width;
	int height;
} WeaponData;

int xy2index(int x, int y, int w);
void init(State *state);
void events(State *state, Player *player, int *currentWeaponIndex,
		uint8_t *MAP, WeaponData *weaponData);
void render(State *state, Player *player, uint8_t *MAP);
void renderWeapon(State *state, WeaponData *weaponData,
		int currentWeaponIndex);
void loadWeaponTexture(State *state, WeaponData *weaponData);
void render_sky_ground(State *state, Player *player);
void perform_dda(bool hit, Vec2I mapBox, Vec2F sideDist, Vec2F deltaDist,
		float *perpWallDist, Side *side, Vec2I stepDir, uint8_t *MAP);
void draw(State *state, Player *player, int x, Side *side, float perpWallDist);
void draw_rays(State *state, Player *player, uint8_t *MAP,
		int blockSize);
void draw_mini_map(State *state, Player *player, uint8_t *MAP,
		int blockSize);
void calc_step_side(Vec2F rayDir, Vec2I *stepDir, Vec2F *sideDist,
		Vec2F *deltaDist, Vec2I mapBox, Player *player);
void ray_pos(Vec2F rayPos, Vec2F rayDir, Vec2I *mapBox, Vec2F *sideDist,
		Vec2F *deltaDist, Vec2I *stepDir);
void hit_wall(bool *hit, Vec2I *mapBox, Vec2F sideDist, Vec2F deltaDist,
		Vec2I stepDir, uint8_t *MAP);
int parse_map(const char *file_path, uint8_t *MAP);
void updateRain(State *state);
void renderRain(State *state);
void help(State *state);
void renderText(State *state, const char *message, int x, int y,
		SDL_Color color);
void render_help(State *state);

#endif
