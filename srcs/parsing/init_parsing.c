/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfischof <pfischof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 16:31:04 by pfischof          #+#    #+#             */
/*   Updated: 2024/12/12 15:29:15 by pfischof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	init_parsing(t_parsing *parsing)
{
	parsing->map = (t_map *)malloc(sizeof(t_map));
	if (parsing->map == NULL)
	{
		parsing_error("malloc() failed on [t_map *]");
		return ;
	}
	parsing->map->no = NULL;
	parsing->map->so = NULL;
	parsing->map->we = NULL;
	parsing->map->ea = NULL;
	parsing->map->grid = NULL;
	parsing->map->f = UINT_MAX;
	parsing->map->c = UINT_MAX;
	parsing->map->width = 0;
	parsing->map->height = 0;
	parsing->map->start_coords = (t_vector2){-1, -1};
	parsing->map->start_direction = 0;
	parsing->state = PARSING_OTHER;
	parsing->path_prefix = NULL;
	parsing->line = NULL;
	parsing->cub = NULL;
}
