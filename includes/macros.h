/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 14:39:04 by uahmed            #+#    #+#             */
/*   Updated: 2024/07/08 13:11:15 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACROS_H
# define MACROS_H

# define USAGE "USAGE:\n\t./cub3D <mapfile>\n"
# define PI 3.14159265359
# define FOV 60
# define EAST 0
# define NORTH 1.57079632
# define WEST PI
# define SOUTH 4.71238898
# define DEGREE	0.01745329
# define MAX_VIEW_DIST 1000
# define HEIGHT 1024
# define WIDTH 1280
# define MINI_HEIGHT 320
# define MINI_WIDTH 320
# define UNITSIZE 64
# define MUNITSIZE 10
# define MSCALE 2

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
