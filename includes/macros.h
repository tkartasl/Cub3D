/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 14:39:04 by uahmed            #+#    #+#             */
/*   Updated: 2024/06/18 14:24:56 by username         ###   ########.fr       */
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
# define MAX_VIEW_DIST 100
# define HEIGHT 1024
# define WIDTH 1280
# define MINI_HEIGHT 10
# define MINI_WIDTH 10


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
