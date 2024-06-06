/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:54:58 by tkartasl          #+#    #+#             */
/*   Updated: 2024/06/06 09:46:11 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "../MLX42/include/MLX42/MLX42.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <memory.h>
# include <math.h>
# define PI 3.14159265359
# define	FOV	60
# define EAST 0
# define NORTH PI / 2
# define WEST PI
# define SOUTH 3 * PI / 2
# define DEGREE 0.01745329251
# define MAX_VIEW_DIST 4

typedef	struct s_rayinfo
{
	double	dist_h;
	double	dist_v;
	double	raydist;
	double	ray_angle;
	double	ntan;
	double	atan;
	double	step_x;
	double	step_y;	
	int		map_x;
	int		map_y;
	
}			t_rayinfo;

typedef struct s_line
{
	int	delta_x;
	int	delta_y;
	int	slope_x;
	int	slope_y;
}		t_line;

typedef struct s_data
{
	mlx_t		*mlx;
	mlx_image_t	*black;
	mlx_image_t *player;
	mlx_image_t *screen;
	double		player_angle;
	double		playerdir_x;
	double		playerdir_y;
	int			camera_x;
	int			camera_y;
	int			height;
	int			width;
	t_line		*line;
	t_rayinfo	*rayinfo;
}			t_data;


#endif
