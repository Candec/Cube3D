/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibanez- <jibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 14:10:54 by jibanez-          #+#    #+#             */
/*   Updated: 2023/02/03 10:53:39 by jibanez-         ###   ########.fr       */
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

void	draw_line(t_mlx *cube, double x, double y, double x2, double y2, int color)
{
	double dx;
	double dy;
	double step;
	double xinc;
	double yinc;
	double i;

	dx = fabs(x2 - x);
	dy = fabs(y2 - y);
	step = ft_ternary_double(dx > dy, dx, dy);
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

void	raycaster_3D(t_mlx *cube, double dist, double angle, int r)
{
	double	ray_x;
	double	ray_y;
	double	xo;
	double	yo;
	int		hit;
	int		wall_height;
	int		wall_top;
	int		wall_bottom;
	int		wall_color;

	hit = 0;
	ray_y = ((cube->player.pos.y / TILE_SIZE) * TILE_SIZE);
	ray_x = (cube->player.pos.y - ray_y) * (-1 / tan(angle)) + cube->player.pos.x;
	xo = cos(angle) * 0.002;
	yo = sin(angle) * 0.002;
	while (hit < INT_MAX)
	{
		if (ray_x > 0 && ray_y > 0 && ray_x < cube->map.width && ray_y < cube->map.height)
		{
			if (cube->map.map[(int)floor(ray_y)][(int)floor(ray_x)] == '1')
				hit = INT_MAX;
			else
			{
				hit++;
				ray_x += xo;
				ray_y += yo;
			}
		}
		else
			hit = INT_MAX;
	}
	dist = distance(cube->player.pos, cube->player.pos, ray_x, ray_y);
	wall_height = (TILE_SIZE / dist) * WALL_HEIGHT;
	wall_top = (WIN_HEIGHT / 2) - (wall_height / 2);
	wall_bottom = (WIN_HEIGHT / 2) + (wall_height / 2);
	wall_color = GREEN;
	if (angle > 0)
		wall_color = BLUE;
	else if (angle < M_PI)
		wall_color = RED;
	else
		wall_color = YELLOW;
	//draw_bg(cube);
	draw_line(cube, r, 0, r, wall_top, 0x000000);
	draw_line(cube, r, wall_top, r, wall_bottom, wall_color);
	draw_line(cube, r, wall_bottom, r, WIN_HEIGHT, 0x000000);
}

static void	ray_init(t_mlx *c, t_raycast *r)
{
	r->hit = false;
	r->ang = c->player.angle -(c->player.fov / 2)
		+ ((double)r->row / (double)WIN_WIDTH) * c->player.fov;
	r->pos.y = ((c->player.pos.y / (TILE_SIZE - 1)) * (TILE_SIZE - 1)) - 0.0001;
	r->pos.x = (c->player.pos.y - r->pos.y) * (-1 / tan(r->ang)) + c->player.pos.x;
	r->stp = ft_coord(cos(r->ang) * 0.002, sin(r->ang) * 0.002);
}

void	draw_rays_2d(t_mlx *c)
{
	t_raycast	*r;

	r = malloc(sizeof(t_raycast));
	r->row = -1;
	while (++r->row < WIN_WIDTH)
	{
		ray_init(c, r);
		while (!r->hit)
		{
			if (r->pos.x > 0 && r->pos.y > 0
				&& r->pos.x < c->map.width && r->pos.y < c->map.height)
			{
				if (c->map.map[(int)r->pos.y][(int)r->pos.x] == '1')
					r->hit = true;
				else
					r->pos = ft_coord(r->pos.x + r->stp.x, r->pos.y + r->stp.y);
			}
			else
				r->hit = true;
		}
		raycaster_3D(c, distance(c->player.pos, c->player.pos), r->ang, r->row);
		free(r);
	}
}
		// draw_line(c, (c->player.pos.x * TILE_SIZE) + TILE_SIZE / 8, (c->player.pos.y * TILE_SIZE) + TILE_SIZE / 8, r->pos.x * TILE_SIZE, r->pos.y * TILE_SIZE, RED);

// void	draw_rays_2D(t_mlx *cube)
// {
// 	int		r;
// 	int		hit;
// 	double	rx;
// 	double	ry;
// 	double	ra;
// 	double	xo;
// 	double	yo;

// 	r = -1;
// 	while (++r < WIN_WIDTH)
// 	{
// 		ra = cube->player.angle -(cube->player.fov / 2) + ((double)r / (double)WIN_WIDTH) * cube->player.fov;
// 		hit = 0;
// 		ry = ((cube->player.posy / (TILE_SIZE - 1)) * (TILE_SIZE - 1)) - 0.0001;
// 		rx = (cube->player.posy - ry) * (-1 / tan(ra)) + cube->player.posx;
// 		xo = cos(ra) * 0.001;
// 		yo = sin(ra) * 0.001;
// 		while (hit < INT_MAX)
// 		{
// 			if (rx > 0 && ry > 0 && rx < cube->map.width && ry < cube->map.height)
// 			{
// 				if (cube->map.map[(int)floor(ry)][(int)floor(rx)] == '1')
// 					hit = INT_MAX;
// 				else
// 				{
// 					hit += 1;
// 					rx += xo;
// 					ry += yo;
// 				}
// 			}
// 			else
// 				hit = INT_MAX;
// 		}
// 		draw_line(cube, (cube->player.posx * TILE_SIZE) + TILE_SIZE / 8, (cube->player.posy * TILE_SIZE) + TILE_SIZE / 8, rx * TILE_SIZE, ry * TILE_SIZE, RED);
// 		raycaster_3D(cube, distance(cube->player.posx, cube->player.posy, rx, ry), ra, r);
// 	}
// }