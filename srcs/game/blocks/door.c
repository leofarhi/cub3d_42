/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 16:50:49 by lfarhi            #+#    #+#             */
/*   Updated: 2024/12/18 15:56:40 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube3d.h>

static void	render_behind(t_engine *engine, t_rendering *r, t_tile *tile)
{
	t_tile_id	old;

	old = tile->id;
	tile->id = EMPTY;
	r->ray_calc = raycast_calc(engine, r->ray_angle);
	render_line(engine, r);
	tile->id = old;
}

t_ltxt	render_door(t_engine *engine, t_rendering *r)
{
	t_tile	*tile;
	t_game	*game;
	t_ltxt		res;
	t_sprite	*door;

	game = (t_game *)engine->game;
	int idx = game->current_time.tv_usec / 200000 % 4;
	door = game->assets.door[idx];
	res.texture = door->texture;
	tile = &engine->map->grid[(int)r->ray_calc.ray.y][(int)r->ray_calc.ray.x];
	float opening = fabs(tile->data / 100.0);
	if (r->ray_calc.ray.x_t < 0.5)
	{
		res.x = (r->ray_calc.ray.x_t * door->rect.width) + ((opening * door->rect.width) / 2);
		if (res.x >= door->rect.width/2)
		{
			render_behind(engine, r, tile);
			res.texture = NULL;
		}
	}
	else
	{
		res.x = (r->ray_calc.ray.x_t * door->rect.width) - ((opening * door->rect.width) / 2);
		if (res.x < door->rect.width/2)
		{
			render_behind(engine, r, tile);
			res.texture = NULL;
		}
	}
	res.x += door->rect.x;
	return (res);
}
