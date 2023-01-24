/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpereira <tpereira@42Lisboa.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 14:10:54 by jibanez-          #+#    #+#             */
/*   Updated: 2023/01/24 13:11:26 by tpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	add_pixel(t_img *frame, int rgb, int x, int y)
{
	frame->data[y * WIN_WIDTH + x] = rgb;
}

void	draw_bg(t_mlx *cube)
{
	int x;
	int y;

	y = -1;
	while (++y < WIN_HEIGHT)
	{
		x = -1;
		while (++x < WIN_WIDTH)
		{
			if (y > (WIN_HEIGHT / 2))
				add_pixel(&cube->frame, cube->map.c_rgb.int_rgb, x, y);
			else
				add_pixel(&cube->frame, cube->map.f_rgb.int_rgb, x, y);
		}
	}
}

void	draw_square(t_mlx *cube, int x, int y, int height, int color)
{
	int i;
	int j;

	i = -1;
	while (++i < height)
	{
		j = -1;
		while (++j < height)
			add_pixel(&cube->frame, color, x + i, y + j);
	}
}

void	draw_wall(t_mlx *cube, int x, int y, int height)
{
	int i;

	i = -1;
	printf("cube->map.c_rgb.int_rgb: %d\n", cube->map.c_rgb.int_rgb);
	while (++i < height)
	{
		add_pixel(&cube->frame, cube->map.c_rgb.int_rgb, x, y + i);
	}
}

void	draw_circle(t_mlx *cube, int x, int y, int radius, int color)
{
	int i;
	int j;

	i = -1;
	while (++i < radius)
	{
		j = -1;
		while (++j < radius)
		{
			if (i * i + j * j < radius * radius)
				add_pixel(&cube->frame, color, x, y);
		}
	}
}

void	draw_line(t_mlx *cube, int x1, int y1, int x2, int y2, int color)
{
	int dx;
	int dy;
	int i;
	int e;

	dx = x2 - x1;
	dy = y2 - y1;
	i = 1;
	e = (dx > dy ? dx : -dy) / 2;
	while (x1 != x2 || y1 != y2)
	{
		add_pixel(&cube->frame, color, x1, y1);
		e = e - (dx > dy ? dy : -dx);
		if (e < 0)
		{
			e = e + (dx > dy ? dx : -dy);
			x1 = x1 + (dx > 0 ? i : -i);
			y1 = y1 + (dy > 0 ? i : -i);
		}
	}
}
