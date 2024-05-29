#include "../MLX42/include/MLX42/MLX42.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <memory.h>
#include <math.h>
#define PI 3.14159265
#define DR 0.01745329251

static void error(void)
{
	puts(mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

int get_r(int rgba)
{
    // Move 3 bytes to the right and mask out the first byte.
    return ((rgba >> 24) & 0xFF);
}

void	key_hook(mlx_key_data_t keydata, void* param)
{
	mlx_image_t	*img;

	img = param;

	if (keydata.key == MLX_KEY_D && (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
		img->instances[0].x += 5;
	// If we RELEASE the 'K' key, print "World".
	if (keydata.key == MLX_KEY_A && (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
		img->instances[0].x -= 5;
	// If we HOLD the 'L' key, print "!".
	if (keydata.key == MLX_KEY_W && (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
		img->instances[0].y -= 5;
	if (keydata.key == MLX_KEY_S && (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
		img->instances[0].y += 5;
	printf("%d x: \n%d y: ", img->instances->x, img->instances->y);
	//if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		//mlx_close_window(param);
}

int32_t	main(void)
{
	// Start mlx
	int arr[5][5] = {{1, 1, 1, 1, 1}, {1, 0, 0, 0, 1}, {1, 0, 0, 0, 1}, {1, 0, 0, 0, 1}, {1, 1, 1, 1, 1}};
	int	i = 0;
	int	j = 0;

	mlx_t* mlx = mlx_init(320, 320, "Test", true);
	if (!mlx)
        error();

	// Create a new image
	mlx_image_t* white = mlx_new_image(mlx, 63, 63);
	if (!white)
		error();
	mlx_image_t* black = mlx_new_image(mlx, 64, 64);
	if (!black)
		error();
	mlx_image_t* player = mlx_new_image(mlx, 8, 8);
	if (!player)
		error();
	//memset(white->pixels, 255, 360 * 360 * sizeof(int32_t));
	//memset(player->pixels, 127, 8 * 8 * sizeof(int32_t));	
// Set every pixel to white
	memset(white->pixels, 255, 64 * 64 * sizeof(int32_t));
	memset(black->pixels, 0, 64 * 64 * sizeof(int32_t));
	memset(player->pixels, 127, 8 * 8 * sizeof(int32_t));
	// Display an instance of the image
	while (j < 5)
	{
		while (i < 5)
		{
			if (arr[j][i] == 1)
			{
				if (mlx_image_to_window(mlx, black, i * 64, j * 64) < 0)
        			error();
			}
			else if (arr[j][i] == 0)
			{
				if (mlx_image_to_window(mlx, white, i * 64, j * 64) < 0)
        			error();
			}
			i++;
		}
		i = 0;
		j++;
	}
	if (mlx_image_to_window(mlx, player, 96, 224) < 0)
        error();
	mlx_key_hook(mlx, &key_hook, player);
	mlx_loop(mlx);
	double	raystart_x = player->instances->x;
	double	raystart_y = player->instances->y;
	double	mapcheck_x = raystart_x;
	double	mapcheck_y = raystart_y;
	double	viewdir_x = 64 / tan(PI / 3);
	double	viewdir_y = 64 * tan(PI / 3);
	double	raydir_x = viewdir_x - player->instances->x;
	double	raydir_y = viewdir_y - player->instances->y;
	double	stepsize_x = sqrt(1 + (raydir_y / raydir_x) * (raydir_y / raydir_x));
	double	stepsize_y = sqrt(1 + (raydir_x / raydir_y) * (raydir_x / raydir_y));;
	double	raylength_x = 0;
	double	raylength_y = 0;
	int 	step_x = 0;
	int		step_y = 0;
	float	distance = 0.0f;
	float	max_distance = 100.0f;
	int		ray_count = 60;

	if (raydir_x < 0)
	{
		step_x = -1;
		raylength_x = (raystart_x - (float)mapcheck_x) * stepsize_x; 
	}
	else 
	{
		step_x = 1;
		raylength_x = ((float)mapcheck_x + 1 - raystart_x) * stepsize_x;
	}
	if (raydir_y < 0)
	{
		step_y = -1;
		raylength_y = (raystart_y - (float)mapcheck_y) * stepsize_y; 
	}
	else 
	{
		step_y = 1;
		raylength_y = ((float)mapcheck_y + 1 - raystart_y) * stepsize_y;
	}
	while (i < i)
	{
		while (distance < max_distance)
		{
			if (raylength_x < raylength_y)
			{
				mapcheck_x += step_x;
				distance = raylength_x;
				raylength_x += stepsize_x;
			}
			else
			{
				mapcheck_y += step_y;
				distance = raylength_y;
				raylength_y += stepsize_y;
			}
		}
		if ()
		draw_line(raystart_x, raystart_y, );
		i++;
	}
	// Optional, terminate will clean up any leftovers, this is just to demonstrate.
	mlx_delete_image(mlx, white);
	mlx_delete_image(mlx, black);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
