/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpereira <tpereira@42Lisboa.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 14:10:54 by jibanez-          #+#    #+#             */
/*   Updated: 2023/03/01 14:08:19 by tpereira         ###   ########.fr       */
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
	double i;
	double j;

	i = WIN_HEIGHT - 1;
	j = 0;
	y = -1;
	while (++y < WIN_HEIGHT)
	{
		x = -1;
		while (++x < WIN_WIDTH)
		{
			if (y > (WIN_HEIGHT / 2))							// floor
				add_pixel(&cube->frame, 0x8888F0 + j, x, y);
			else if (y < (WIN_HEIGHT / 2))						// sky
				add_pixel(&cube->frame, 0x00ffff + i, x, y);
		}
		i -= 0.7;
		j -= 0.6;
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

void	raycaster_3D(t_mlx *cube, t_raycast *ray)
{

	int				wall_height;
	int				wall_top;
	int				wall_bottom;
	int				wall_color;

	ray->dist = distance(cube->player.pos.x, cube->player.pos.y, ray->pos.x, ray->pos.y);
	fix_fisheye(cube->player.angle, ray);
	wall_height = (TILE_SIZE / ray->dist) * WALL_HEIGHT;
	wall_top = (WIN_HEIGHT / 2) - (wall_height / 2);
	wall_bottom = (WIN_HEIGHT / 2) + (wall_height / 2);
	wall_color = GREEN;
	if (ray->angle < ((PI3)) && ray->angle > PI2)
		wall_color = RED;
	else
		wall_color = YELLOW;
	draw_line(cube, ray->row, wall_top, ray->row, wall_bottom, wall_color);
}

void	vertical_hit(t_raycast *ray, t_mlx *c)
{
	float	a_tan;
	
	a_tan = -tan(ray->angle);
	printf("ray->angle: %.9f\n", (double)ray->angle);
	printf("PI3: %.9f\n", (double)(PI3));
	if (ray->angle > PI2 && ray->angle < (PI3)) // Looking Left
	{
		ray->pos.x = floor((c->player.pos.x * TILE_SIZE) / TILE_SIZE) - 0.0001;
		ray->pos.y = ((c->player.pos.x - ray->pos.x) * a_tan + c->player.pos.y);
		ray->step.x = -TILE_SIZE;
		ray->step.y = (-ray->step.x) * a_tan;
		printf("LEFT\n");
	}
	if ((double)ray->angle > (double)(PI3) || ray->angle < PI2) // Looking Right
	{
		ray->pos.x = floor((c->player.pos.x * TILE_SIZE) / TILE_SIZE) + 1;
		ray->pos.y = (c->player.pos.x - ray->pos.x) * a_tan + c->player.pos.y; // ISSUES HERE
		ray->step.x = TILE_SIZE;
		ray->step.y = (-ray->step.x) * a_tan;
		printf("RIGHT\n");
	}
	if (ray->angle == PI2 || ray->angle == (PI3))								// Looking straight up/down
	{
		ray->pos.x = c->player.pos.x;
		ray->pos.y = c->player.pos.y;
		ray->hit = true;
		printf("test\n");
	}
	while (!ray->hit)
	{
		if (ray->pos.x > 0 && ray->pos.y > 0 && ray->pos.y < c->map.height && ray->pos.x < c->map.width)
		{
			if (c->map.map[(int)ray->pos.y][(int)ray->pos.x] == '1')
				ray->hit = true;
			else
			{
				ray->pos.x += ray->step.x / TILE_SIZE;
				ray->pos.y += ray->step.y / TILE_SIZE;
			}
		}
		else
			ray->hit = true;
	}
	printf("ray->pos.x = %f\n", ray->pos.x);
	printf("ray->pos.y = %f\n", ray->pos.y);
	// printf("c->player.pos.x = %f\n", c->player.pos.x);
	// printf("c->player.pos.y = %f\n", c->player.pos.y);
	draw_line(c, (c->player.pos.x * TILE_SIZE), (c->player.pos.y * TILE_SIZE), ray->pos.x * TILE_SIZE, ray->pos.y * TILE_SIZE, RED);
	ray->dist = distance(c->player.pos.x, c->player.pos.y, ray->pos.x, ray->pos.y);
}

void	horizontal_hit(t_raycast *ray, t_mlx *c)
{
	float	a_tan;
 	
	a_tan = -1 / tan(ray->angle);
	if (ray->angle > 0 && ray->angle < PI)					// Looking down
	{
		ray->pos.y = round((c->player.pos.y * TILE_SIZE) / TILE_SIZE);
		ray->pos.x = ((c->player.pos.y - ray->pos.y) * a_tan + c->player.pos.x);
		ray->step.y = TILE_SIZE;
		ray->step.x = (-ray->step.y) * a_tan;
	}
	if (ray->angle > PI && ray->angle < (PII)) 					// LOOking UP
	{
		ray->pos.y = round((c->player.pos.y * TILE_SIZE) / TILE_SIZE) - 0.0001;
		ray->pos.x = (c->player.pos.y - ray->pos.y) * a_tan + c->player.pos.x;
		ray->step.y = -TILE_SIZE;
		ray->step.x = (-ray->step.y) * a_tan;
	}
	if (ray->angle == 0 || ray->angle == PI)					// Looking straight left/right
	{
		ray->pos.x = c->player.pos.x;
		ray->pos.y = c->player.pos.y;
		ray->hit = true;
	}
	while (!ray->hit)
	{
		if (ray->pos.x > 0 && ray->pos.y > 0 && ray->pos.y < c->map.height && ray->pos.x < c->map.width)
		{
			if (c->map.map[(int)ray->pos.y][(int)ray->pos.x] == '1')
				ray->hit = true;
			else
			{
				ray->pos.x += ray->step.x / TILE_SIZE;
				ray->pos.y += ray->step.y / TILE_SIZE;
			}
		}
		else
			ray->hit = true;
	}
	draw_line(c, (c->player.pos.x * TILE_SIZE - 1), c->player.pos.y * TILE_SIZE - 1, ray->pos.x * TILE_SIZE - 1, ray->pos.y * TILE_SIZE - 1, YELLOW);
	ray->dist = distance(c->player.pos.x, c->player.pos.y, ray->pos.x, ray->pos.y);
}

void	draw_rays_2D(t_mlx *c)
{
	int			row;
	t_raycast	ray;
	row = -1;

	//draw_bg(c);
	draw_map_2D(c);
	draw_player_2D(c);
	while (++row < 1)
	{
		ray.hit = false;
		ray.row = row;
		//ray.angle = c->player.angle - (c->player.fov / 2) + ((double)ray.row / (double)WIN_WIDTH) * c->player.fov;
		ray.angle = c->player.angle;
		fix_angle(&ray.angle);
		//horizontal_hit(&ray, c);
		vertical_hit(&ray, c);
		//draw_line(c, (c->player.pos.x * TILE_SIZE) + (TILE_SIZE * 0.5), (c->player.pos.y * TILE_SIZE) + (TILE_SIZE * 0.5), ray.pos.x * TILE_SIZE, ray.pos.y * TILE_SIZE, RED);
		//raycaster_3D(c, &ray);
	}
	// if (c->show_minimap)
	// {
		// draw_map_2D(c);
		// draw_player_2D(c);
	// }
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