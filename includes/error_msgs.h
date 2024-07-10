/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msgs.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 16:49:37 by uahmed            #+#    #+#             */
/*   Updated: 2024/07/10 11:38:46 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_MSGS_H
# define ERROR_MSGS_H

# include "macros.h"

// ERROR MSGS
# define USAGE "USAGE:\n\t./cub3D <mapfile>\n"
# define TIDS "Type Identifiers are not correct in the map file\n"
# define DPATH "Textures path is a directory\n"
# define NOPATH "Textures path is not given\n"
# define WRPATH "Textures path is wrong\n"
# define OPATH "Textures file can not be opened\n"
# define NOMAP "Mapfile does not contain the MAP\n"
# define FHWALL "First horizontal wall of the map is invalid\n"
# define LHWALL "Last horizontal wall of the map is invalid\n"
# define FVWALL "First vertical wall of the map is invalid\n"
# define LVWALL "Last vertical wall of the map is invalid\n"
# define ALLSPACES "A map line is all spaces\n"
# define NOPLAYER "The map has got no player\n"
# define MOREPLAYER "The map has got more than one player\n"
# define INVALMAP "Map is overall invalid\n"
# define INVALCHAR "Map has got an invalid character in it\n"
# define SOMETHING "Something follows the valid map which makes it invalid\n"
# define MOREFLOOR "More than one floor color given\n"
# define MORECEILING "More than one ceiling color given\n"
# define INVALCOLOR "Invalid color\n"
# define TEXREPEAT "More than one same textures given\n"
# define MAPHOLE "The map has got a hole\n"

#endif
