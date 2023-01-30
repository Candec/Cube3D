/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpereira <tpereira@42Lisboa.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 14:10:54 by jibanez-          #+#    #+#             */
/*   Updated: 2023/01/30 12:54:56 by tpereira         ###   ########.fr       */
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
	float mx;
	float my;
	float a_tan;

	r = -1;
	while (++r < WIN_WIDTH)
	{
		ra = cube->player.angle;
		a_tan = -1 / tan(ra);
		dof = 0;
		if (ra > M_PI)
		{
			ry = (((int)cube->player.posy >> 6) << 6) - 0.0001;
			rx = (cube->player.posy - ry) * a_tan + cube->player.posx;
			yo = -1 * (TILE_SIZE / 2);
			xo = -yo * a_tan;
		}
		if (ra < M_PI)
		{
			ry = (((int)cube->player.posy >> 6) << 6) + (TILE_SIZE / 2);
			rx = (cube->player.posy - ry) * a_tan + cube->player.posx;
			yo = TILE_SIZE / 2;
			xo = -yo * a_tan;
		}
		if (ra == 0 || ra == M_PI)
		{
			rx = cube->player.posx;
			ry = cube->player.posy;
			dof = 8;
		}
		while (dof < 8)
		{
			mx = (int)rx >> 3;
			my = (int)ry >> 3;
			mp = my * cube->map.width + mx;
			printf("mp: %d\n cube->map.width: %d\n cube->map.map[mp]: %s\n cube->map.map[mp][0]: %c\n dof: %d\n mx: %f\n my: %f\n", mp, (int)cube->map.width, cube->map.map[mp], (int)cube->map.map[mp][0], dof, mx, my);
			if ((size_t)mp < cube->map.width * cube->map.height && ft_strcmp(cube->map.map[mp], "1"))
				dof = 8;
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
		draw_line(cube, cube->player.posx * (TILE_SIZE / 2) + 2, cube->player.posy * (TILE_SIZE / 2) + 2, rx * (TILE_SIZE / 2), ry  * (TILE_SIZE / 2), GREEN);
	}
}
