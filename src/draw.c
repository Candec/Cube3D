/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibanez- <jibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 14:10:54 by jibanez-          #+#    #+#             */
/*   Updated: 2023/02/01 02:39:04 by jibanez-         ###   ########.fr       */
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

// void	draw_rays_2D(t_mlx *cube)
// {
// 	int		row;
// 	bool	hit;
// 	double	angle;
// 	t_coord	ray;
// 	t_coord	step;

// 	row = -1;
// 	while (++row < WIN_WIDTH)
// 	{
// 		angle = cube->player.angle -(cube->player.fov / 2) + ((double)row / (double)WIN_WIDTH) * cube->player.fov;
// 		ray = ft_coord(cube->player.pos.x, cube->player.pos.y);
// 		step = ft_coord(cos(angle), sin(angle));
// 		hit = false;
// 		printf("cube->player.pos.x: %f, cube->player.pos.y: %f, step.x: %f, step.y: %f\n", cube->player.pos.x, cube->player.pos.y, step.x, step.y);
// 		while (!hit)
// 		{
// 			if ((ray.x <= 0 || ray.y <= 0) && (ray.x >= cube->map.width || ray.y >= cube->map.height))
// 				return ;
// 			printf("ray.x: %f, ray.y: %f\n", ray.x, ray.y);
// 			if (cube->map.map[(int)ray.y][(int)ray.x] == '1')
// 			{
// 				hit = true;
// 			}
// 			else
// 			{
// 				ray.x += step.x;
// 				ray.y += step.y;
// 			}
// 			draw_line(cube, cube->player.pos.x * TILE_SIZE, cube->player.pos.y * TILE_SIZE, ray.x * TILE_SIZE, ray.y  * TILE_SIZE, RED);
// 		}
// 	}
// }

void	draw_rays_2D(t_mlx *cube)
{
	int		r;
	int		dof;
	float	rx;
	float	ry;
	float	ra;
	float	xo;
	float	yo;

	r = -1;
	while (++r < WIN_WIDTH)
	{
		ra = cube->player.angle -(cube->player.fov / 2) + ((float)r / (float)WIN_WIDTH) * cube->player.fov;
		dof = 0;
		ry = ((cube->player.posy / (TILE_SIZE - 1)) * (TILE_SIZE - 1)) - 0.0001;
		rx = (cube->player.posy - ry) * (-1 / tan(ra)) + cube->player.posx;
		xo = cos(ra) * 0.001;
		yo = sin(ra) * 0.001;
		printf("cube->player.posx: %f, cube->player.posy: %f, xo: %f, yo: %f\n", cube->player.posx, cube->player.posy, xo, yo);
		while (dof < INT_MAX)
		{
			if (rx > 0 && ry > 0 && rx < cube->map.width && ry < cube->map.height)
			{
				if (cube->map.map[(int)floor(ry)][(int)floor(rx)] == '1')
				{
					printf("rx: %f, ry: %f\n", rx, ry);
					printf("map[%d][%d]: %c\n", (int)(ry), (int)(rx), cube->map.map[(int)(ry)][(int)(rx)]);
					dof = INT_MAX;
				}
				else
				{
					dof += 1;
					rx += xo;
					ry += yo;
				}
			}
			else
				dof = 100;
		}
		draw_line(cube, cube->player.pos.x * TILE_SIZE, cube->player.pos.y * TILE_SIZE, rx * TILE_SIZE, ry  * TILE_SIZE, RED);
	}
}
