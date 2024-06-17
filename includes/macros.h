/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uahmed <uahmed@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 14:39:04 by uahmed            #+#    #+#             */
/*   Updated: 2024/05/31 14:39:06 by uahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACROS_H
# define MACROS_H

# define	USAGE "USAGE:\n\t./cub3D <mapfile>\n"
# define PI 3.14159265359
# define	FOV	60
# define EAST 0
# define NORTH PI / 2
# define WEST PI
# define SOUTH 3 * PI / 2
# define DEGREE 0.01745329251
# define MAX_VIEW_DIST 4


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
