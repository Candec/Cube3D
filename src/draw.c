/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpereira <tpereira@42Lisboa.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 14:10:54 by jibanez-          #+#    #+#             */
/*   Updated: 2023/01/27 09:48:40 by tpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	add_pixel(t_img *frame, int rgb, int x, int y)
{
	//printf("x: %d, y: %d\n", x, y);
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

void	draw_line(t_mlx *cube, float x, float y, float x2, float y2, int color)
{
	float dx;
	float dy;
	float step;
	float xinc;
	float yinc;
	float i;

	dx = x2 - x;
	dy = y2 - y;
	if (fabs(dx) > fabs(dy))
		step = fabs(dx);
	else
		step = fabs(dy);
	xinc = dx / step;
	yinc = dy / step;
	i = 1;
	while (i <= step)
	{
		add_pixel(&cube->frame, color, round(x), round(y));
		x += xinc;
		y += yinc;
		i++;
	}
}

void	draw_rays_2D(t_mlx *cube)
{
	int r;
	int mp;
	int dof;
	float rx;
	float ry;
	float ra;
	float xo;
	float yo;

	r = -1;
	while (++r < WIN_WIDTH)
	{
		ra = cube->player.angle - cube->player.fov / 2 + (cube->player.fov / WIN_WIDTH) * r;
		dof = 0;
		rx = cube->player.posx;
		ry = cube->player.posy;
		xo = cos(ra) * 10;
		yo = sin(ra) * 10;
		while (dof < 8)
		{
			rx += xo;
			ry += yo;
			mp = (int)rx / (TILE_SIZE / 2) + (int)ry / (TILE_SIZE / 2) * cube->map.width;
			if (ft_strcmp(cube->map.map[mp], "1"))
			{
				if (cube->map.map[mp][0] != '\0')
					dof = 8;
			}
			else
				dof += 1;
		}
		draw_line(cube, cube->player.posx * (TILE_SIZE / 2), cube->player.posy * (TILE_SIZE / 2), rx * (TILE_SIZE / 2), ry  * (TILE_SIZE / 2), GREEN);
	}
}
