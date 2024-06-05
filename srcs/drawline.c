#include "cub3D.h"

int	compare(int a, int b)
{
	int	ret;

	if (a < b)
		ret = 1;
	else
		ret = -1;
	return (ret);
}

void	draw_line(int x_start, int y_start, int x_end, int y_end, mlx_image_t * screen, int color)
{
	int dx = abs(x_end - x_start);
	int	sx = compare(x_start, x_end);
	int dy = -abs(y_end - y_start);
	int	sy = compare(y_start, y_end);
	int	err = dx + dy;
	int	e2;
	//int	color = get_rgba(255, 0, 0, 0);
	e2 = 0;
	while (1)
	{
		if (x_start >= 0 && y_start >= 0 && x_start <= 320 && y_start <= 320)
			mlx_put_pixel(screen, x_start, y_start, color);
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

int	main()
{	
	mlx_t* mlx = mlx_init(320, 320, "Test", true);
	if (!mlx)
        return (1);
	mlx_image_t* screen = mlx_new_image(mlx, 320, 320);
	if (!screen)
		return (1);
	memset(screen->pixels, 255, 320 * 320 * sizeof(int32_t));
	if (mlx_image_to_window(mlx, screen, 0, 0) < 0)
		return (1);
	int	i = 0;
	int	top = 160;
	int	bottom = 20;
	while (i < 320)
	{
		if (i < 160)
			draw_line(i, bottom, i, top, screen, 120);
		else
			draw_line(i, bottom, i, top, screen, 165);
		if (i % 10 == 0 && i < 160)
		{
			top -= 2;
			bottom += 2;
		}
		if (i % 10 == 0 && i >= 160)
		{
			top += 2;
			bottom -= 2;
		}
		i++;
	}
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (0);
}