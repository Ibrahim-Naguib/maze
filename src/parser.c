#include "../headers/main.h"

/**
 * parse_map - Parses the map file.
 * @file_path: The path to the map file.
 * @MAP: The map.
 *
 * Return: 0 on success, 1 on failure.
 */

int parse_map(const char *file_path, uint8_t *MAP)
{
	FILE *file = fopen(file_path, "r");

	if (!file)
	{
		perror("Error opening map file");
		return (1);
	}

	for (int y = 0; y < MAP_SIZE; ++y)
	{
		for (int x = 0; x < MAP_SIZE; ++x)
		{
			int value;

			if (fscanf(file, " %d ,", &value) != 1)
			{
				fprintf(stderr, "Invalid map format\n");
				fclose(file);
				return (1);
			}
			MAP[xy2index(x, y, MAP_SIZE)] = (uint8_t)value;
		}
	}

	fclose(file);
	return (0);
}
