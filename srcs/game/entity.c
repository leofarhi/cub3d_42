/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 18:00:37 by lfarhi            #+#    #+#             */
/*   Updated: 2024/12/16 18:33:12 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube3d.h>

t_entity	*spawn_entity(t_game *game,
	void (*update)(t_entity *entity),
	void (*minimap)(t_entity *entity),
	t_sprite *sprites)
{
	t_entity *entity;
	t_list *new;
	entity = malloc(sizeof(t_entity));
	if (!entity)
		return NULL;
	entity->game = game;
	entity->pos[0] = 0;
	entity->pos[1] = 0;
	entity->dir = 0;
	entity->update = update;
	entity->minimap = minimap;
	entity->anim = 0;
	entity->anim_map = 0;
	entity->sprites = sprites;
	new = ft_lstnew(entity);
	if (!new)
	{
		free(entity);
		return NULL;
	}
	ft_lstadd_back(&game->engine.entities, new);
	return entity;
}

void	set_entity_pos(t_entity *entity, float x, float y)
{
	entity->pos[0] = x;
	entity->pos[1] = y;
}
