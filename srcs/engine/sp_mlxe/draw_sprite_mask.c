/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlxe_draw_subtexture_size.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 23:55:39 by lfarhi            #+#    #+#             */
/*   Updated: 2024/06/13 23:55:39 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

static void	change_bounds_neg(t_coords *coords,
	float x_ratio, float y_ratio)
{
	if (coords->dest.x < 0)
	{
		coords->src.x -= coords->dest.x * x_ratio;
		coords->src.width += coords->dest.x * x_ratio;
		coords->dest.width += coords->dest.x;
		coords->dest.x = 0;
	}
	if (coords->dest.y < 0)
	{
		coords->src.y -= coords->dest.y * y_ratio;
		coords->src.height += coords->dest.y * y_ratio;
		coords->dest.height += coords->dest.y;
		coords->dest.y = 0;
	}
}

static void	change_bounds(t_window *window,
	t_coords *coords, t_texture *texture)
{
	if (coords->src.x + coords->src.width > texture->size.x)
		coords->src.width = texture->size.x - coords->src.x;
	if (coords->src.y + coords->src.height > texture->size.y)
		coords->src.height = texture->size.y - coords->src.y;
	if (coords->dest.x + coords->dest.width > window->buffer->size.x)
		coords->dest.width = window->buffer->size.x - coords->dest.x;
	if (coords->dest.y + coords->dest.height > window->buffer->size.y)
		coords->dest.height = window->buffer->size.y - coords->dest.y;
}

void	draw_sprite_mask(t_window *window,
			t_sprite *sprite, t_coords coords)
{
	float		x_ratio;
	float		y_ratio;
	t_vector2	inc;
	t_color		texture_color;

	x_ratio = (float)coords.src.width / (float)coords.dest.width;
	y_ratio = (float)coords.src.height / (float)coords.dest.height;
	change_bounds_neg(&coords, x_ratio, y_ratio);
	change_bounds(window, &coords, sprite->texture);
	inc.y = 0;
	while (inc.y < coords.dest.height)
	{
		inc.x = 0;
		while (inc.x < coords.dest.width)
		{
			texture_color = mlxe_read_pixel(sprite->texture, coords.src.x
					+ (inc.x * x_ratio), coords.src.y + (inc.y * y_ratio));
			if (!(texture_color & 0xFF000000))
				mlxe_write_pixel(window->buffer, coords.dest.x + inc.x,
					coords.dest.y + inc.y, texture_color);
			inc.x++;
		}
		inc.y++;
	}
}
