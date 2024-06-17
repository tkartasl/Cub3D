/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uahmed <uahmed@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 14:01:10 by uahmed            #+#    #+#             */
/*   Updated: 2024/05/30 14:01:12 by uahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	freecub_exit(t_cub *cub);

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

static	void	init_vecs(t_cub *cub)
{
	vec_new(cub->textures_paths, 0, sizeof(char **));
	vec_new(cub->textures_info, 0, sizeof(int));
	vec_new(cub->ceiling, 0, sizeof(int)); // TODO: change int to what it is
	vec_new(cub->floor, 0, sizeof(int)); // TODO: change int to what it is
	vec_new(cub->map, 0, sizeof(char **));
}

static	void	alloc_init_vecs(t_cub *cub)
{
	t_vec	*ceiling;
	t_vec	*floor;

	ceiling	= (t_vec *)malloc(sizeof(t_vec));
	if (ceiling == NULL)
		freecub_exit(cub);
	cub->ceiling = ceiling;
	floor	= (t_vec *)malloc(sizeof(t_vec));
	if (floor == NULL)
		freecub_exit(cub);
	cub->floor = floor;
	init_vecs(cub);
}

void	null_cub(t_cub *cub)
{
	cub->dir_info = 0;
	cub->line = NULL;
	cub->textures_info = NULL;
	cub->map = NULL;
	cub->floor = NULL;
	cub->ceiling = NULL;
}

void	init_cub(t_cub *cub)
{
	t_vec	*textures_paths;
	t_vec	*textures_info;
	t_vec	*map;

	null_cub(cub);
	textures_paths = (t_vec *)malloc(sizeof(t_vec));
	if (textures_paths == NULL)
		exit(EXIT_FAILURE);
	cub->textures_paths = textures_paths;
	textures_info = (t_vec *)malloc(sizeof(t_vec));
	if (textures_info == NULL)
		freecub_exit(cub);
	cub->textures_info = textures_info;
	map = (t_vec *)malloc(sizeof(t_vec));
	if (map  == NULL)
		freecub_exit(cub);
	cub->map = map;
	alloc_init_vecs(cub);
}
