/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:54:58 by tkartasl          #+#    #+#             */
/*   Updated: 2024/06/19 13:51:57 by tkartasl         ###   ########.fr       */
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

typedef struct	s_parser
{
	int	dir_info;
	char	**line;
	char	*file;
	t_vec	*textures_paths;
	t_vec	*textures_info;
	t_vec	*floor;	
	t_vec	*ceiling;	
	t_vec	*map;
}	t_parser;

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
	double	ray_x;
	double	ray_y;
	int		map_x;
	int		map_y;
}			t_rayinfo;

typedef struct s_line
{
	int	delta_x;
	int	delta_y;
	int	slope_x;
	int	slope_y;
	int	error2;
}		t_line;

typedef struct s_textures
{
	mlx_texture_t	*wall[4];
	char			axis;
	int				idx;
}		t_textures;

typedef struct s_data
{
	mlx_t		*mlx;
	mlx_image_t *screen;
	mlx_image_t *minimap;
	double		player_angle;
	double		playerdir_x;
	double		playerdir_y;
	int			camera_x;
	int			camera_y;
	int			map_height;
	int			map_width;
	int			map_size;
	t_line		*line;
	t_rayinfo	*rayinfo;
	char		**map;
	char		playerdir;
	t_parser	*parser;
	t_textures	*texture;
}			t_data;

void	key_hook_movement(mlx_key_data_t keydata, void *param);
void	draw_walls(t_data *data, int color, int x_pos);
int		check_overflow(t_data *data);
void	reset_ray_angle(double *angle);
double	ray_length(t_data *data);
double	check_horizontal_hit(t_data *data);
double	check_vertical_hit(t_data *data);
void	cast_rays(t_data *data);
void	init_parser(t_parser *parser);
void	init_data_mlx(t_data *data, t_parser *parser);
int		valid_map(char **argv);
void	skip_spaces(char *s, int *ind);
void	next_strings_end(char *line, int *end, int check_comma);
void	eof_malloc_check(t_parser *parser, int malloc_flag, int map, int fd);
void	validate_horizontal(t_parser *parser, char *line);
void	validate_middle(t_parser *parser, char *line);
int		open_validate_file(t_parser *parser, char *map_path, char *ext, int texture_path);
void	validate_type_identifier(t_parser *parser, char **type_id);
void	parse_file(t_parser *parser, char *map_path);
int32_t	raycaster(t_data *data);
void	freeparser_exit(t_parser *parser);
void	free_exit(t_parser *parser, char **type_id, int print_err);
void	free_vecs(t_parser *parser, int exit_fail, int print_err);
void	freedata_exit(t_data *data, int exit_status, int terminate_mlx);
int get_rgba(int r, int g, int b, int a);
void	draw_colors(t_data *data);

#endif
