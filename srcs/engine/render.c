/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 15:06:39 by lfarhi            #+#    #+#             */
/*   Updated: 2024/12/16 15:56:22 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

static void	line_init(t_engine *engine, t_rendering *r)
{
	r->ray.dist *= cos(r->ray.dir - engine->camera.dir);
	r->line_height = (int)(engine->window->buffer->size.y
			/ fmax(r->ray.dist, 0.1f));
	r->draw_start = -r->line_height / 2 + engine->window->buffer->size.y / 2;
	r->draw_end = r->line_height / 2 + engine->window->buffer->size.y / 2;
	if (r->draw_start < 0)
		r->draw_start = 0;
	if (r->draw_end >= engine->window->buffer->size.y)
		r->draw_end = engine->window->buffer->size.y - 1;
	r->texture = engine->walls[r->ray.side_hit];
	r->tex_x = (int)(r->ray.x_t * r->texture->size.x);
	r->tex_x = r->tex_x % r->texture->size.x;
}

static void	draw_line(t_engine *engine, int x, t_rendering r)
{
	int		y;
	int		d;
	int		tex_y;
	t_color	color;

	y = r.draw_start;
	while (y < r.draw_end)
	{
		d = y * 256 - engine->window->buffer->size.y * 128
			+ r.line_height * 128;
		tex_y = ((d * r.texture->size.y) / r.line_height) / 256;
		color = mlxe_get_pixel(engine->walls[r.ray.side_hit], r.tex_x, tex_y);
		mlxe_draw_pixel(engine->window->buffer, x, y, color);
		y++;
	}
}

void	draw_map(t_engine *engine)
{
	int			x;
	t_rendering	r;

	r.camera_plane = engine->camera.fov / 2.0f;
	x = 0;
	while (x < engine->window->buffer->size.x)
	{
		r.camera_x = 2 * x / (float)engine->window->buffer->size.x - 1;
		r.ray_angle = engine->camera.dir + r.camera_x * r.camera_plane;
		r.ray = raycast(engine, r.ray_angle);
		if (r.ray.hit)
		{
			line_init(engine, &r);
			draw_line(engine, x, r);
		}
		x++;
	}
}
