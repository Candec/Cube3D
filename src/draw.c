/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibanez- <jibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 14:10:54 by jibanez-          #+#    #+#             */
/*   Updated: 2023/02/08 18:09:28 by jibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	add_pixel(t_img *frame, int rgb, int x, int y)
{
	//printf("x: %d, y: %d\n", x, y);
	if (y < 0 || x < 0|| y > HEIGHT || x > WIDTH)
		return ;
	frame->data[y * WIDTH + x] = rgb;
}

void	draw_bg(t_mlx *cube)
{
	int x;
	int y;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			if (y > (HEIGHT / 2))
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
	while (++i < height)
		add_pixel(&cube->frame, cube->map.c_rgb.int_rgb, x, y + i);
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

void	raycaster_3D(t_mlx *cube, double dist, double angle, int row)
{
	t_raycast r;
	t_wall	wall;

	r.hit = false;
	r.pos.y = ((cube->player.pos.y / TILE_SIZE) * TILE_SIZE);
	r.pos.x = (cube->player.pos.y - r.pos.y) * (-1 / tan(angle)) + cube->player.pos.x;
	r.stp = ft_coord(cos(angle) * 0.002, sin(angle) * 0.002);
	while (!r.hit)
	{
		if (r.pos.x > 0 && r.pos.y > 0
			&& r.pos.x < cube->map.width && r.pos.y < cube->map.height)
		{
			if (cube->map.map[(int)r.pos.y][(int)r.pos.x] == '1')
				r.hit = true;
			else
				r.pos = ft_coord(r.pos.x + r.stp.x, r.pos.y + r.stp.y);
		}
		else
			r.hit = true;
	}
	dist = distance(cube->player.pos, r.pos);
	wall.height = (TILE_SIZE / dist) * WALL_HEIGHT;
	wall.top = (HEIGHT / 2) - (wall.height / 2);
	wall.bottom = (HEIGHT / 2) + (wall.height / 2);
	if (cube->player.dirx >= 0 && cube->player.diry >= 0)
	{
		if (cube->player.dirx > cube->player.diry)
			wall.color = YELLOW;
		else if (cube->player.dirx < cube->player.diry)
			wall.color = RED;
		else
			wall.color = GREEN;
	}
	else if (cube->player.dirx < 0 && cube->player.diry >= 0)
	{
		if (cube->player.dirx > cube->player.diry)
			wall.color = RED;
		else if (cube->player.dirx < cube->player.diry)
			wall.color = GREEN;
		else
			wall.color = BLUE;
	}
	else if (cube->player.dirx >= 0 && cube->player.diry < 0)
	{
		if (cube->player.dirx > cube->player.diry)
			wall.color = GREEN;
		else if (cube->player.dirx < cube->player.diry)
			wall.color = BLUE;
		else
			wall.color = YELLOW;
	}
	else if (cube->player.dirx < 0 && cube->player.diry < 0)
	{
		if (cube->player.dirx > cube->player.diry)
			wall.color = BLUE;
		else if (cube->player.dirx < cube->player.diry)
			wall.color = YELLOW;
		else
			wall.color = RED;
	}
	draw_line(cube, row, wall.top, row, wall.bottom, wall.color);
}

static void	ray_init(t_mlx *c, t_raycast *r, int row)
{
	r->hit = false;
	r->ang = c->player.angle -(c->player.fov / 2)
		+ ((double)row / (double)WIDTH) * c->player.fov;
	r->pos.y = ((c->player.pos.y / (TILE_SIZE - 1)) * (TILE_SIZE - 1)) - 0.0001;
	r->pos.x = (c->player.pos.y - r->pos.y) * (-1 / tan(r->ang)) + c->player.pos.x;
	r->stp = ft_coord(cos(r->ang) * 0.002, sin(r->ang) * 0.002);
}

void	draw_rays_2d(t_mlx *c)
{
	t_raycast	*r;
	int			row;

	r = malloc(sizeof(t_raycast));
	row = -1;
	while (++row < WIDTH)
	{
		ray_init(c, r, row);
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
		draw_line(c, (c->player.pos.x * TILE_SIZE) + TILE_SIZE / 8, (c->player.pos.y * TILE_SIZE) + TILE_SIZE / 8, r->pos.x * TILE_SIZE, r->pos.y * TILE_SIZE, RED);
		raycaster_3D(c, distance(c->player.pos, r->pos), r->ang, row);
	}
	free(r);
}

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