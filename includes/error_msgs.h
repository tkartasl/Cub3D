/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msgs.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 16:49:37 by uahmed            #+#    #+#             */
/*   Updated: 2024/07/11 10:50:28 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_MSGS_H
# define ERROR_MSGS_H

# include "macros.h"

// ERROR MSGS
# define USAGE "USAGE:\n\t./cub3D <mapfile>\n"
# define TIDS "\tType Identifiers are not correct in the map file\n"
# define TDPATH "\tTextures path is a directory\n"
# define MDPATH "\tMap path is a directory\n"
# define NOPATH "\tTextures path is not given\n"
# define TWRPATH "\tTextures path is wrong\n"
# define MWRPATH "\tMap file path is wrong\n"
# define TOPATH "\tTextures file can not be opened\n"
# define MOPATH "\tMap file can not be opened\n"
# define NOMAP "\tMapfile does not contain the MAP\n"
# define FHWALL "\tFirst horizontal wall of the map is invalid\n"
# define LHWALL "\tLast horizontal wall of the map is invalid\n"
# define FVWALL "\tFirst vertical wall of the map is invalid\n"
# define LVWALL "\tLast vertical wall of the map is invalid\n"
# define ALLSPACES "\tA map line is all spaces\n"
# define NOPLAYER "\tThe map has got no player\n"
# define MOREPLAYER "\tThe map has got more than one player\n"
# define INVALMAP "\tMap is overall invalid\n"
# define INVALCHAR "\tMap has got an invalid character in it\n"
# define SOMETHING "\tSomething follows the valid map which makes it invalid\n"
# define MOREFLOOR "\tMore than one floor color given\n"
# define MORECEILING "\tMore than one ceiling color given\n"
# define INVALCOLOR "\tInvalid color\n"
# define TEXREPEAT "\tMore than one same textures given\n"
# define IVALTEX "\tTexture file is invalid\n"
# define MAPHOLE "\tThe map has got a hole\n"

#endif
