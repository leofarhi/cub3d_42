/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ghost.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfischof <pfischof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:56:49 by lfarhi            #+#    #+#             */
/*   Updated: 2025/01/08 12:01:52 by pfischof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>
#include <entities.h>

t_vector2	find_next_tile(t_vector2 current_pos, t_vector2 target_pos, \
	t_map *map)
{
	t_vector2	next_pos;
	int			dx;
	int			dy;

	next_pos = current_pos;
	dx = target_pos.x - current_pos.x;
	dy = target_pos.y - current_pos.y;
	dprintf(2, "1 = %s\n2 = %s\ndebug (%d, %d)\n", (next_pos.x != target_pos.x || next_pos.y != target_pos.y) ? "true" : "false", map->grid[next_pos.y][next_pos.x].id == WALL ? "true" : "false", next_pos.x, next_pos.y);
	while ((next_pos.x != target_pos.x || next_pos.y != target_pos.y) \
		&& map->grid[next_pos.y][next_pos.x].id == WALL)
	{
		if (abs(dx) > abs(dy))
		{
			next_pos.x = current_pos.x;
			next_pos.y = current_pos.y + (dy > 0 ? 1 : -1);
		}
		else
		{
			next_pos.x = current_pos.x + (dx > 0 ? 1 : -1);
			next_pos.y = current_pos.y;
		}
		current_pos = next_pos;
		dx = target_pos.x - current_pos.x;
		dy = target_pos.y - current_pos.y;
	}
	return (next_pos);
}

void	get_next_target(t_entity *enemy, t_enemy_type type, \
	t_vector2 player_pos, float player_dir)
{
	t_enemy		*data;
	t_vector2	temp;
	t_game *game;

	game = (t_game *)enemy->game;
	data = (t_enemy *)enemy->data;
	temp = player_pos;
	if (type == ENEMY_PINK)
	{
		temp.x = player_pos.x + 4 * cos(player_dir);
		temp.y = player_pos.y + 4 * sin(player_dir);
	}
	else if (type == ENEMY_BLUE)
	{
		temp.x = player_pos.x + (player_pos.x - (int)data->red->pos[0]);
		temp.y = player_pos.y + (player_pos.y - (int)data->red->pos[1]);
	}
	else if (type == ENEMY_ORANGE)
	{
		temp.x = rand() % game->engine.map->width;
		temp.y = rand() % game->engine.map->height;
	}
	data->target = find_next_tile((t_vector2){(int)enemy->pos[0], \
		(int)enemy->pos[1]}, temp, game->engine.map);
}

void	ghost_update(t_entity *enemy)
{
	t_enemy	*data;
	t_game *game;

	game = (t_game *)enemy->game;
	data = (t_enemy *)enemy->data;
	if (data->target.x + 0.5 - enemy->pos[0] < 0.2 \
			&& data->target.y + 0.5 - enemy->pos[1] < 0.2)
		get_next_target(enemy, data->type, \
			(t_vector2){(int)game->player->pos[0], \
			(int)game->player->pos[1]}, game->player->mov_dir);
	dprintf(2, "enemy.x = %f\nenemy.y = %f\n\n", enemy->pos[0], enemy->pos[1]);
	dprintf(2, "target.x = %d\ntarget.y = %d\n\n", data->target.x, data->target.y);
	if (data->target.x + 0.5 < enemy->pos[0])
		add_move(enemy, -ENTITY_SPEED, 0);
	else if (data->target.x + 0.5 > enemy->pos[0])
		add_move(enemy, ENTITY_SPEED, 0);
	else if (data->target.y + 0.5 < enemy->pos[1])
		add_move(enemy, 0, -ENTITY_SPEED);
	else if (data->target.y + 0.5 > enemy->pos[1])
		add_move(enemy, 0, ENTITY_SPEED);
}

void	ghost_minimap(t_entity *enemy)
{
	int			monster_id = 0;
	t_camera	*camera;
	t_coords	coords;
	t_game *game;

	game = (t_game *)enemy->game;
	camera = &game->engine.camera;
	coords = (t_coords){game->assets.map_enemy[monster_id]->rect, \
				(t_rect){((enemy->pos[0] - camera->x + 5) *10) - 8,
				((enemy->pos[1] - camera->y + 5) *10) - 8, 16, 16}};
	coords = mask_minimap(coords);
	draw_sprite_mask(game->window, \
		game->assets.map_enemy[monster_id], \
		coords);
}
