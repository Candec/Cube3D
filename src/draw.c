/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpereira <tpereira@42Lisboa.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 14:10:54 by jibanez-          #+#    #+#             */
/*   Updated: 2023/01/30 21:22:35 by tpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	add_pixel(t_img *frame, int rgb, int x, int y)
{
	//printf("x: %d, y: %d\n", x, y);
	if (y < 0 || x < 0|| y > WIN_HEIGHT || x > WIN_WIDTH)
		return ;
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

	dx = fabs(x2 - x);
	dy = fabs(y2 - y);
	step = ft_ternary_float(dx > dy, dx, dy);
	xinc = (x2 - x) / step;
	yinc = (y2 - y) / step;
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
		ra = cube->player.angle;
		dof = 0;
		rx = cube->player.posx;
		ry = cube->player.posy;
		xo = cos(ra) * 10;
		yo = sin(ra) * 10;
		while (dof < 8)
		{
			rx += xo;
			ry += yo;
			mp = (int)rx / TILE_SIZE + (int)ry / TILE_SIZE * cube->map.width;
			if (ft_strcmp(cube->map.map[mp], "1"))
			{
				if (cube->map.map[mp][0] != '\0')
					dof = 8;
			}
			else
			{
				dof += 1;
				rx += xo;
				ry += yo;
			}
		}
		draw_line(cube, cube->player.posx * TILE_SIZE, cube->player.posy * TILE_SIZE, rx * TILE_SIZE, ry  * TILE_SIZE, RED);
	}
}
