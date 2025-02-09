/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 15:49:50 by lfarhi            #+#    #+#             */
/*   Updated: 2025/01/08 13:38:45 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>
#include <stdio.h>

t_bool	engine_init(t_engine *engine, t_window *window, t_map *map)
{
	engine->game = NULL;
	engine->window = window;
	engine->z_buffer = malloc(sizeof(float) * window->buffer->size.x);
	if (!engine->z_buffer)
		return (FAILURE);
	engine->map = map;
	engine->camera.x = map->start_coords.x + 0.5;
	engine->camera.y = map->start_coords.y + 0.5;
	if (map->start_direction == 'E')
		engine->camera.dir = 0;
	else if (map->start_direction == 'S')
		engine->camera.dir = M_PI_2;
	else if (map->start_direction == 'W')
		engine->camera.dir = M_PI;
	else if (map->start_direction == 'N')
		engine->camera.dir = 3 * M_PI_2;
	engine->camera.fov = M_PI / 2.8;
	engine->entities = NULL;
	ft_memset(engine->render_block, 0, sizeof(engine->render_block));
	return (SUCCESS);
}

void	destory_engine(t_engine *engine)
{
	free(engine->z_buffer);
	ft_lstclear(&engine->entities, free_entity);
	engine->entities = NULL;
}

static void	clear_screen(t_window *window, t_color top, t_color bottom)
{
	int		i;
	int		j;

	i = 0;
	while (i < window->buffer->size.y / 2)
	{
		j = 0;
		while (j < window->buffer->size.x)
		{
			mlxe_write_pixel(window->buffer, j, i, top);
			mlxe_write_pixel(window->buffer, j,
				window->buffer->size.y - i - 1, bottom);
			j++;
		}
		i++;
	}
}

void	render_engine(t_engine *engine)
{
	ft_memset(engine->z_buffer, 0,
		sizeof(float) * engine->window->buffer->size.x);
	clear_screen(engine->window, engine->map->c, engine->map->f);
	draw_map(engine);
	draw_entities(engine);
}
