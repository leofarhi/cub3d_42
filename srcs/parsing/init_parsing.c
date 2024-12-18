/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfischof <pfischof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 16:31:04 by pfischof          #+#    #+#             */
/*   Updated: 2024/12/18 09:48:42 by pfischof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parsing.h>

t_bool	init_parsing(t_parsing *parsing)
{
	parsing->map = (t_map *)malloc(sizeof(t_map));
	if (parsing->map == NULL)
		return (parsing_error(ERR_MALLOC_TMAP));
	parsing->map->no = NULL;
	parsing->map->so = NULL;
	parsing->map->we = NULL;
	parsing->map->ea = NULL;
	parsing->map->grid = NULL;
	parsing->map->f = UINT_MAX;
	parsing->map->c = UINT_MAX;
	parsing->map->width = 0;
	parsing->map->height = 0;
	parsing->map->start_coords = (t_vector2){UNSET, UNSET};
	parsing->map->start_direction = 0;
	parsing->state = PARSING_METADATA;
	parsing->line = NULL;
	parsing->cub = NULL;
	return (SUCCESS);
}
