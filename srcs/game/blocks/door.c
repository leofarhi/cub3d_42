/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 16:50:49 by lfarhi            #+#    #+#             */
/*   Updated: 2025/01/08 16:04:06 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

static void	render_behind(t_engine *engine, t_rendering *r, t_tile *tile)
{
	t_tile_id	old;

	old = tile->id;
	tile->id = EMPTY;
	r->ray_calc = raycast(engine, r->ray_angle);
	render_line(engine, r);
	tile->id = old;
}

static t_ltxt	door_texture(t_engine *engine,
	t_rendering *r, t_tile *tile, t_sprite *door)
{
	const float	opening = fabs(tile->data / 100.0);
	t_ltxt		res;

	res.texture = door->texture;
	res.x = (r->ray_calc.ray.x_t * door->rect.width);
	if (r->ray_calc.ray.x_t < 0.5)
	{
		res.x += ((opening * door->rect.width) / 2);
		if (res.x >= door->rect.width / 2)
		{
			render_behind(engine, r, tile);
			res.texture = NULL;
		}
	}
	else
	{
		res.x -= ((opening * door->rect.width) / 2);
		if (res.x < door->rect.width / 2)
		{
			render_behind(engine, r, tile);
			res.texture = NULL;
		}
	}
	res.x += door->rect.x;
	return (res);
}

t_ltxt	render_door(t_engine *engine, t_rendering *r)
{
	t_tile		*tile;
	t_game		*game;
	t_ltxt		res;
	t_sprite	*door;

	game = (t_game *)engine->game;
	door = game->assets.door[game->current_time.tv_usec / 200000 % 4];
	tile = &engine->map->grid[(int)r->ray_calc.ray.y][(int)r->ray_calc.ray.x];
	res = door_texture(engine, r, tile, door);
	return (res);
}

void	toggle_door(t_game	*game, t_tile *tile)
{
	if (tile->id == DOOR)
	{
		if (tile->data == 100)
		{
			tile->data = -96;
		}
		else if (tile->data == 0)
			tile->data = 4;
	}
}

t_bool	door_is_open(t_tile *tile)
{
	if (tile->id == DOOR && tile->data > 0)
		return (TRUE);
	return (FALSE);
}
