/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parsing_structs.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 14:01:10 by uahmed            #+#    #+#             */
/*   Updated: 2024/06/18 14:36:37 by username         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_inds(t_indices *inds)
{
	inds->st = 0;
	inds->end = 0;
	inds->counter = 3;
}

void	init_tex_count(t_count *count)
{
	count->no = 0;
	count->so = 0;
	count->ea = 0;
	count->we = 0;
	count->f = 0;
	count->c = 0;
}

void	init_parser(t_parser *parser)
{
	ft_memset(parser, 0, sizeof(t_parser));
	parser->textures_paths = NULL;
	parser->textures_paths = (t_vec *)malloc(sizeof(t_vec));
	if (parser->textures_paths == NULL)
		exit(EXIT_FAILURE);
	parser->textures_info = (t_vec *)malloc(sizeof(t_vec));
	if (parser->textures_info == NULL)
		freeparser_exit(parser);
	parser->map = (t_vec *)malloc(sizeof(t_vec));
	if (parser->map == NULL)
		freeparser_exit(parser);
	parser->ceiling = (t_vec *)malloc(sizeof(t_vec));
	if (parser->ceiling == NULL)
		freeparser_exit(parser);
	parser->floor = (t_vec *)malloc(sizeof(t_vec));
	if (parser->floor == NULL)
		freeparser_exit(parser);
	vec_new(parser->textures_paths, 0, sizeof(char **));
	vec_new(parser->textures_info, 0, sizeof(int));
	vec_new(parser->ceiling, 0, sizeof(int));
	vec_new(parser->floor, 0, sizeof(int));
	vec_new(parser->map, 0, sizeof(char **));
}
