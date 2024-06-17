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
# include "macros.h"
# include "get_next_line.h"
#include "../vec/include/vec.h"
# include <fcntl.h>
# include <errno.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <memory.h>
# include <math.h>

typedef	struct	s_indices
{
	int	st;
	int	end;
	int	counter;
}	t_indices;

typedef	struct	s_count
{
	int	no;
	int	so;
	int	we;
	int	ea;
	int	f;
	int	c;
}	t_count;

typedef struct	s_cub
{
	int	dir_info;
	char	**line;
	char	*file;
	t_vec	*textures_paths;
	t_vec	*textures_info;
	t_vec	*floor;	
	t_vec	*ceiling;	
	t_vec	*map;
}	t_cub;


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
	char		**map;
	t_line		*line;
	t_rayinfo	*rayinfo;
}			t_data;

void	init_cub(t_cub *cub);
int	valid_map(char **argv);
void	skip_spaces(char *s, int *ind);
void	next_strings_end(char *line, int *end, int check_comma);
void	eof_malloc_check(t_cub *cub, int malloc_flag, int map, int fd);
void	validate_horizontal(t_cub *cub, char *line);
void	validate_middle(t_cub *cub, char *line);
int	open_validate_file(t_cub *cub, char *map_path, char *ext, int texture_path);
void	validate_type_identifier(t_cub *cub, char **type_id);
void	parse_file(t_cub *cub, char *map_path);

int32_t	raycaster(t_cub *cub);
void	free_exit(t_cub *cub, char **type_id, int print_err);
void	free_vecs(t_cub *cub, int exit_fail, int print_err);

#endif
