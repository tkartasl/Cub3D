#include "../MLX42/include/MLX42/MLX42.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <memory.h>
#include <math.h>
#define PI 3.14159265359
#define	PI2 PI / 2
#define PI3 3 * PI / 2
#define	DEGREE 0.1875
#define P_PLANE_W 320
#define P_PLANE_H 200
#define P_PLANE_MID_W 160
#define P_PLANE_MID_H 100
#define DIST_TO_P_PLANE 277
#define	MAX_VIEW_DISTANCE 1000
#define	FOV	60
#define EAST 0
#define NORTH 90
#define WEST 180
#define SOUTH 270
#define BLOCK 64

typedef struct s_rayinfo
{
	mlx_image_t *player;
	mlx_image_t *screen;
	double		angle;
	double		ray_angle;
	double		rayh_y;
	double		rayh_x;
	double		rayv_y;
	double		rayv_x;
	double		playerdir_x;
	double		playerdir_y;
	double		distance_h;
	double		distance_v;
}			t_rayinfo;

int	compare(int a, int b)
{
	int	ret;

	if (a < b)
		ret = 1;
	else
		ret = -1;
	return (ret);
}

void	bresenham(int x_end, int y_end, int x_start, int y_start, mlx_image_t *screen)
{
	int dx = abs(x_end - x_start);
	int	sx = compare(x_start, x_end);
	int dy = -abs(y_end - y_start);
	int	sy = compare(y_start, y_end);
	int	err = dx + dy;
	int	e2;

	e2 = 0;
	while (1)
	{
		if (x_start >= 0 && y_start >= 0 && x_start <= 320 && y_start <= 320)
			mlx_put_pixel(screen, x_start, y_start, 155);
		if (x_start == x_end && y_start == y_end)
			break ;
		e2 = 2 * err;
		if (e2 >= dy)
		{
			err += dy;
			x_start += sx;
		}	
		if (e2 <= dx)
		{
			err += dx;
			y_start += sy;
		}
	}
}

void	key_hook_move(mlx_key_data_t keydata, void* param)
{
	t_rayinfo	*info;

	info = param;
	if (keydata.key == MLX_KEY_RIGHT && (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
	{
		info->angle += 10;
		if (info->angle > 2 * 180)
			info->angle -= 2 * 180;
		info->playerdir_x = cos(info->angle * PI / 180) * 10;
		info->playerdir_y = sin(info->angle * PI / 180) * 10;
	//	cast_rays(info);
	}
	if (keydata.key == MLX_KEY_LEFT && (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
	{
		info->angle -= 10;
		if (info->angle < 0)
			info->angle += 2 * 180;
		info->playerdir_x = cos(info->angle * PI / 180) * 10;
		info->playerdir_y = sin(info->angle * PI / 180) * 10;
	//	cast_rays(info);
	}
	printf("player dir x %f , player dir y %f\n" ,info->playerdir_x, info->playerdir_y);
	if (keydata.key == MLX_KEY_D && (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
	{
		info->player->instances[0].x -= (int)info->playerdir_x;
		info->player->instances[0].x += (int)info->playerdir_y;
	//	cast_rays(info);
	}
	printf("player dir x %f , player dir y %f\n" ,info->playerdir_x, info->playerdir_y);
	if (keydata.key == MLX_KEY_A && (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
	{
		info->player->instances[0].x += (int)info->playerdir_x;
		info->player->instances[0].x -= (int)info->playerdir_y;
	//	cast_rays(info);
	}
	if (keydata.key == MLX_KEY_W && (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
	{
		info->player->instances[0].x -= (int)info->playerdir_x;
		info->player->instances[0].y -= (int)info->playerdir_y;
	//	cast_rays(info);
	}
	if (keydata.key == MLX_KEY_S && (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
	{
		info->player->instances[0].x += (int)info->playerdir_x;
		info->player->instances[0].y += (int)info->playerdir_y;
	//	cast_rays(info);
	}
	printf("%d x: \n%d y: ", info->player->instances->x, info->player->instances->y);
	//if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		//mlx_close_window(param);
}

int32_t	main(void)
{
	// Start mlx
	int arr[5][5] = {{1, 1, 1, 1, 1}, {1, 0, 0, 0, 1}, {1, 0, 0, 0, 1}, {1, 0, 0, 0, 1}, {1, 1, 1, 1, 1}};
	int	i = 0;
	int	j = 0;
	t_rayinfo	rayinfo;

	mlx_t* mlx = mlx_init(320, 320, "Test", true);
	if (!mlx)
		return (1);
	memset(&rayinfo, 0, sizeof(t_rayinfo));
	mlx_image_t* black = mlx_new_image(mlx, 63, 63);
	if (!black)
		return (1);
	rayinfo.player = mlx_new_image(mlx, 8, 8);
	if (!rayinfo.player)
		return (1);
	mlx_image_t* screen = mlx_new_image(mlx, 320, 320);
	if (!screen)
		return (1);
	rayinfo.screen = screen;
	rayinfo.angle = 60;
	rayinfo.playerdir_x = cos(rayinfo.angle * PI / 180) * 10;
	rayinfo.playerdir_y = sin(rayinfo.angle * PI / 180) * 10;
	printf("playerdir_x %f\nplayerdir_y %f\n", rayinfo.playerdir_x, rayinfo.playerdir_y);
	memset(black->pixels, 100, 64 * 64 * sizeof(int32_t));
	memset(rayinfo.player->pixels, 127, 8 * 8 * sizeof(int32_t));
	memset(screen->pixels, 255, 320 * 320 * sizeof(int32_t));
	if (mlx_image_to_window(mlx, screen, 0, 0) < 0)
        return (1);
	while (j < 5)
	{
		while (i < 5)
		{
			if (arr[j][i] == 1)
			{
				if (mlx_image_to_window(mlx, black, i * 64, j * 64) < 0)
        			return (1);
			}
			i++;
		}
		i = 0;
		j++;
	}
	if (mlx_image_to_window(mlx, rayinfo.player, 96, 224) < 0)
		return (1);
	bresenham(96, 224, 64, 128, rayinfo.screen);
	mlx_key_hook(mlx, &key_hook_move, &rayinfo);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}