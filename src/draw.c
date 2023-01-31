/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpereira <tpereira@42Lisboa.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 14:10:54 by jibanez-          #+#    #+#             */
/*   Updated: 2023/01/31 15:56:52 by tpereira         ###   ########.fr       */
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

void	raycaster_3D(t_mlx *cube, float dist, float angle, int r)
{
	float	ray_x;
	float	ray_y;
	float	xo;
	float	yo;
	int		dof;
	int		wall_height;
	int		wall_top;
	int		wall_bottom;
	int		wall_color;

	dof = 0;
	ray_y = ((cube->player.posy / TILE_SIZE) * TILE_SIZE);
	ray_x = (cube->player.posy - ray_y) * (-1 / tan(angle)) + cube->player.posx;
	xo = cos(angle) * 0.002;
	yo = sin(angle) * 0.002;
	while (dof < INT_MAX)
	{
		if (ray_x > 0 && ray_y > 0 && ray_x < cube->map.width && ray_y < cube->map.height)
		{
			if (cube->map.map[(int)floor(ray_y)][(int)floor(ray_x)] == '1')
				dof = INT_MAX;
			else
			{
				dof++;
				ray_x += xo;
				ray_y += yo;
			}
		}
		else
			dof = INT_MAX;
	}
	dist = distance(cube->player.posx, cube->player.posy, ray_x, ray_y);
	wall_height = (TILE_SIZE / dist) * cube->player.dirx;	// not working properly - needs to be fixed
	wall_top = (WIN_HEIGHT / 2) - (wall_height / 2);
	wall_bottom = (WIN_HEIGHT / 2) + (wall_height / 2);
	wall_color = GREEN;
	if (angle > 0 && angle < M_PI)
		wall_color = BLUE;
	else
		wall_color = YELLOW;
	draw_line(cube, r, 0, r, wall_top, 0x000000);
	draw_line(cube, r, wall_top, r, wall_bottom, wall_color);
	draw_line(cube, r, wall_bottom, r, WIN_HEIGHT, 0x000000);
}

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
		while (dof < INT_MAX)
		{
			if (rx > 0 && ry > 0 && rx < cube->map.width && ry < cube->map.height)
			{
				//printf("cube->map.map[(int)floor(ry)][(int)floor(rx)]: %c\n", cube->map.map[(int)floor(ry)][(int)floor(rx)]);
				if (cube->map.map[(int)floor(ry)][(int)floor(rx)] == '1')
					dof = INT_MAX;
				else
				{
					dof += 1;
					rx += xo;
					ry += yo;
				}
			}
			else
				dof = INT_MAX;
		}
		draw_line(cube, (cube->player.posx * TILE_SIZE) + TILE_SIZE / 8, (cube->player.posy * TILE_SIZE) + TILE_SIZE / 8, rx * TILE_SIZE, ry  * TILE_SIZE, RED);
		//raycaster_3D(cube, distance(cube->player.posx, cube->player.posy, rx, ry), ra, r);
	}
}
