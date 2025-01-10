/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entities.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfischof <pfischof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 18:15:55 by lfarhi            #+#    #+#             */
/*   Updated: 2025/01/10 18:23:17 by pfischof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENTITIES_H
# define ENTITIES_H

# include <cub3D.h>

# define ENTITY_SPEED	0.03
# define BIG_ORBS_DIST	5

/*
typedef struct s_entity
{
	t_game		*game;
	t_sprite	*sprites;
	float		pos[2];
	float		dir;
	void		(*update)(struct s_entity *entity);
	void		(*minimap)(struct s_entity *entity);
}				t_entity;
*/

t_bool		spawn_orb_entities(t_game *game, t_map *map);
t_bool		spawn_entities(t_game *game);

t_vector2	get_farthest_tile(t_map *map, t_vector2 player);

void		player_update(t_entity *entity);
void		player_minimap(t_entity *entity);

void		big_orb_update(t_entity *entity);
void		big_orb_minimap(t_entity *entity);

void		orb_update(t_entity *entity);
void		orb_minimap(t_entity *entity);

void		ghost_update(t_entity *entity);
void		ghost_minimap(t_entity *entity);

#endif
