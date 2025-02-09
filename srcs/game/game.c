/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 15:51:32 by lfarhi            #+#    #+#             */
/*   Updated: 2025/01/14 11:32:15 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>
#include <entities.h>

void	update_entities(t_game *game)
{
	t_list		*current;
	t_entity	*entity;

	current = game->engine.entities;
	while (current)
	{
		entity = (t_entity *)current->content;
		entity->efunc.update(entity);
		current = current->next;
	}
	remove_empty_entities(&game->engine);
}

void	update_map(t_game *game)
{
	t_vector2	pos;
	t_tile		*tile;

	pos = (t_vector2){0, 0};
	while (pos.y < (int)game->engine.map->height)
	{
		pos.x = 0;
		while (pos.x < (int)game->engine.map->width)
		{
			tile = &game->engine.map->grid[(int)pos.y][(int)pos.x];
			if (tile->id == DOOR)
			{
				if (tile->data > 0 && tile->data < 100)
					tile->data += 4;
				if (tile->data < 0 && tile->data > -100)
					tile->data += 4;
			}
			pos.x++;
		}
		pos.y++;
	}
}

void	main_loop(t_window *window, void *data)
{
	t_game	*game;
	t_time	start;
	t_time	end;

	game = (t_game *)data;
	update_map(game);
	update_entities(game);
	start = get_time();
	game->current_time = start;
	render_engine(&game->engine);
	draw_minimap(game);
	if (mlxe_is_key_down(window, XK_Tab))
	{
		mlxe_update_input(window);
		window->funct_ptr = pause_menu_loop;
		mlxe_mouse_move(window, window->width / 2, window->height / 2);
		return ;
	}
	if (game->remaining_orbs == 0)
		window->funct_ptr = you_win_loop;
	mlxe_render(window);
	mlxe_mouse_move(window, window->width / 2, window->height - 1);
	end = get_time();
	game->delta_time = get_delta(start, end);
}

t_bool	game_init(t_game *game, t_window *window, t_map *map)
{
	ft_memset(game, 0, sizeof(t_game));
	game->window = window;
	if (!load_assets(&game->assets, map, window))
		return (print_error("Failed to load textures"), FAILURE);
	if (!engine_init(&game->engine, window, map))
		return (FAILURE);
	game->engine.game = (void *)game;
	game->engine.render_block[DOOR] = &render_door;
	game->engine.render_block[WALL] = &render_wall;
	game->remaining_orbs = 0;
	game->invulanerability_time = get_time();
	game->invulanerability_time.tv_sec -= INVULNERABILITY_TIME;
	reset_path(game);
	if (!spawn_entities(game))
		return (destory_engine(&game->engine), FAILURE);
	set_entity_pos(game->player, game->engine.camera.x, game->engine.camera.y);
	game->player->dir = game->engine.camera.dir;
	return (SUCCESS);
}

void	destroy_game(t_game *game)
{
	destory_engine(&game->engine);
	free_map(game->engine.map);
}
