/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 14:39:04 by uahmed            #+#    #+#             */
/*   Updated: 2024/07/22 13:16:25 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACROS_H
# define MACROS_H

# define PI 3.14159265359
# define FOV 60
# define EAST 0
# define NORTH PI / 2
# define WEST PI
# define SOUTH (PI / 2) * 3
# define DEGREE 0.01745329
# define MAX_VIEW_DIST 1000
# define HEIGHT 1024
# define WIDTH 1280
# define MINI_HEIGHT 320
# define MINI_WIDTH 320
# define UNITSIZE 64
# define MUNITSIZE 10
# define MSCALE 2
# define ROTATE_SPEED 0.03
# define MOVE_SPEED 7.5
# define FT 42
# define COLORS 5
# define LAYERS 1

// Define color codes
# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define YELLOW "\033[1;33m"
# define BLUE "\033[1;34m"
# define MAGENTA "\033[1;35m"
# define CYAN "\033[1;36m"
# define WHITE "\033[1;37m"
# define RESET "\033[0m"


enum	e_colors
{
	C,
	F,
	MF,
	W,
	O,
};

enum	e_rgba
{
	R,
	G,
	B,
	A = 210,
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
