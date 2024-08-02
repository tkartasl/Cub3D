/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:54:58 by tkartasl          #+#    #+#             */
/*   Updated: 2024/07/26 13:21:57 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../MLX42/include/MLX42/MLX42.h"
# include "../vec/include/vec.h"
# include "error_msgs.h"
# include "get_next_line.h"
# include "macros.h"
# include <errno.h>
# include <fcntl.h>
# include <pthread.h>
# include <math.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_indices
{
	int				st;
	int				end;
	int				counter;
}					t_indices;

typedef struct s_count
{
	int				no;
	int				so;
	int				we;
	int				ea;
	int				f;
	int				c;
}					t_count;

typedef struct s_parser
{
	int				dir_info;
	char			*line;
	char			*next_line;
	char			*file;
	t_vec			*textures_paths;
	t_vec			*textures_info;
	t_vec			*floor;
	t_vec			*ceiling;
	t_vec			*map;
}					t_parser;

typedef struct s_rayinfo
{
	double			dist_h;
	double			dist_v;
	double			raydist;
	double			ray_angle;
	double			step_x;
	double			step_y;
	double			h_ray_x;
	double			h_ray_y;
	double			v_ray_x;
	double			v_ray_y;
	double			ray_x;
	double			ray_y;
	int				map_x;
	int				map_y;
}					t_rayinfo;

typedef struct s_textures
{
	mlx_texture_t	*wall[4];
	char			axis;
	int				idx;
	double			x;
	double			y;
	double			ty_off;
	double			ty_step;
	int				height;
}					t_textures;

typedef struct s_data
{
	mlx_t			*mlx;
	mlx_image_t		*screen;
	mlx_image_t		*minimap;
	mlx_image_t		*player;
	double			player_angle;
	double			playerdir_x;
	double			playerdir_y;
	int				camera_x;
	int				camera_y;
	int				map_height;
	t_vec			*map_width;
	t_rayinfo		*rayinfo;
	t_parser		*parser;
	char			**map;
	char			**grid;
	int				colors[COLORS];
	t_textures		*texture;
	int				flag;
	int				tex_index;
	pthread_t		layers[LAYERS];
	pthread_mutex_t	layers_lock[LAYERS];
}					t_data;

typedef struct s_camera
{
	int				cx;
	int				cy;
	double			angle;
}					t_camera;

void				key_hook(mlx_key_data_t keydata, void *param);
int					get_line_end(char *line);
void				draw_walls(t_data *data, int x_pos);
int					check_overflow(t_data *data);
void				reset_ray_angle(double *angle);
double				ray_length(t_data *data, int horizontal);
void				init_parser(t_parser *parser);
void				init_data_mlx(t_data *data, t_parser *parser);
void				skip_spaces(char *s, int *ind);
void				next_strings_end(char *line, int *end, int check_comma);
void				eof_malloc_check(t_parser *parser, int malloc_flag, int map,
						int fd);
int					open_validate_file(t_parser *parser, char *map_path,
						char *ext, int texture_path);
void				validate_type_identifier(t_parser *parser, char **type_id);
void				parse_file(t_parser *parser, char *map_path);
void				raycaster(t_data *data);
void				freeparser_exit(t_parser *parser);
void				free_exit(t_parser *parser, char **type_id, char *msg);
void				free_vecs(t_parser *parser, int exit_fail,
						char *msg, char **map);
void				freedata_exit(t_data *data, int exit_status,
						int terminate_mlx, int premature);
int					get_rgba(int r, int g, int b, int a);
void				movement(void *param);
void				wall_collision(t_data *data, char key, int *new_x,
						int *new_y);
void				wall_collision_strafe(t_data *data, char key, int *new_x,
						int *new_y);
void				mouse_hook(double xpos, double ypos, void *param);
void				get_texture_index(t_data *data, int t_size);
void				get_arrow_textures(t_data *data, int dir);
void				*minimap(void *arg);
int					game_continues(t_data *data);
void				get_camera(t_data *data, t_camera *cam);
void				set_camera(t_data *data, t_camera *cam);

#endif
