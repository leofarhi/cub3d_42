/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entities.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfischof <pfischof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 18:15:55 by lfarhi            #+#    #+#             */
/*   Updated: 2024/12/17 10:15:04 by pfischof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENTITIES_H
# define ENTITIES_H

# include <cub3D.h>

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

t_bool	spawn_entities(t_game *game);

void	player_update(t_entity *entity);
void	player_minimap(t_entity *entity);

void	update_coin(t_entity *entity);
void	draw_minimap_coin(t_entity *entity);

void	update_enemy(t_entity *entity);
void	draw_minimap_enemy(t_entity *entity);

#endif
