/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 14:39:04 by uahmed            #+#    #+#             */
/*   Updated: 2024/07/01 14:42:22 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACROS_H
# define MACROS_H

# define	USAGE "USAGE:\n\t./cub3D <mapfile>\n"
# define PI 3.14159265359
# define FOV 60
# define EAST 0
# define NORTH PI / 2
# define WEST PI
# define SOUTH 3 * PI / 2
# define DEGREE	0.01745329251
# define MAX_VIEW_DIST 1000
# define HEIGHT 1024
# define WIDTH 1280
# define MINI_HEIGHT 320
# define MINI_WIDTH 320
# define UNITSIZE 64
# define MUNITSIZE 10
# define MSCALE 2
# define LAYERS 2

enum	e_rgb
{
	R,
	G,
	B,
};

enum	e_game_status
{
	STOP,
	CONTINUE,
};

enum	e_mutexes
{
	CAMERA,
	STOP_FLG,
};

enum	e_layers
{
	RAYCASTER,
	MINIMAP,
};

enum	e_minimap_type
{
	WALL,
	EMPTY,
};

enum	e_type_identifiers
{
	TEXTURE,
	CEILING,
	FLOOR,
	MAP,
};

enum	e_flags
{
	SUCCESS,
	FAILURE,
	YES,
	NA,
	EMP_LINE,
	TOT_TIDS = 6,
};

enum	e_directions
{
	SO,
	NO,
	WE,
	EA,
};


#endif
