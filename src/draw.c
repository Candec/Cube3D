/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpereira <tpereira@42Lisboa.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 14:10:54 by jibanez-          #+#    #+#             */
/*   Updated: 2023/03/08 14:12:28 by tpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	add_pixel(t_img *frame, int rgb, int x, int y)
{
	if (y < 0 || x < 0 || y > WIN_HEIGHT || x > WIN_WIDTH)
		return ;
	frame->data[y * WIN_WIDTH + x] = rgb;
}

void	draw_bg(t_mlx *cube)
{
	int	x;
	int	y;

	y = -1;
	while (++y < WIN_HEIGHT)
	{
		x = -1;
		while (++x < WIN_WIDTH)
		{
			if (y > (WIN_HEIGHT / 2)) // floor
				add_pixel(&cube->frame, cube->map.f_rgb.int_rgb, x, y);
			else if (y < (WIN_HEIGHT / 2)) // sky
				add_pixel(&cube->frame, cube->map.c_rgb.int_rgb, x, y);
		}
	}
}

void	draw_square(t_mlx *cube, t_coord pos, int height, int color)
{
	int	i;
	int	j;

	i = -1;
	while (++i < height)
	{
		j = -1;
		while (++j < height)
			add_pixel(&cube->frame, color, pos.x + i, pos.y + j);
	}
}

void	draw_line(t_mlx *cube, t_coord a, t_coord b, int color)
{
	t_coord	d;
	t_coord	inc;
	double	step;
	double	i;

	d.x = fabs(b.x - a.x);
	d.y = fabs(b.y - a.y);
	step = ft_ternary_double(d.x > d.y, d.x, d.y);
	inc.x = (b.x - a.x) / step;
	inc.y = (b.y - a.y) / step;
	i = 1;
	while (i <= step)
	{
		add_pixel(&cube->frame, color, round(a.x), round(a.y));
		a.x += inc.x;
		a.y += inc.y;
		i++;
	}
}

void	raycaster_3d(t_mlx *cube, t_raycast *ray)
{
	t_coord			w_top;
	t_coord			w_bottom;
	int				wall_height;

	ray->dist = sqrt(distance(cube, ray));
	fix_fisheye(cube->p.angle, ray);
	wall_height = (TILE_SIZE / ray->dist) * WALL_HEIGHT;
	w_top.x = ray->row;
	w_top.y = (WIN_HEIGHT / 2) - (wall_height / 2);
	w_bottom.x = ray->row;
	w_bottom.y = (WIN_HEIGHT / 2) + (wall_height / 2);
	draw_line(cube, w_top, w_bottom, ray->color);
}

void	looking_left(t_raycast *ray, t_mlx *c)
{
	float	a_tan;

	a_tan = -tan(ray->angle);
	ray->pos.x = floor(c->p.pos.x) - 0.0001;
	ray->pos.y = (c->p.pos.x - ray->pos.x) * a_tan + c->p.pos.y;
	ray->step.x = -TILE_SIZE;
	ray->step.y = (-ray->step.x) * a_tan;
	ray->color = YELLOW;
}

void	looking_right(t_raycast *ray, t_mlx *c)
{
	float	a_tan;

	a_tan = -tan(ray->angle);
	ray->pos.x = floor(c->p.pos.x) + 1;
	ray->pos.y = ((c->p.pos.x - ray->pos.x) * a_tan + c->p.pos.y);
	ray->step.x = TILE_SIZE;
	ray->step.y = (-ray->step.x) * a_tan;
	ray->color = BLUE;
}

void	looking_up_down(t_raycast *ray, t_mlx *c)
{
	ray->pos.x = c->p.pos.x;
	ray->pos.y = c->p.pos.y;
	ray->step.x = 0;
	ray->step.y = 0;
	ray->color = RED;
}

float	vertical_hit(t_raycast *ray, t_mlx *c)
{
	if ((double)ray->angle > PI2 && (double)ray->angle < (PI3))
		looking_left(ray, c);
	if ((double)ray->angle > (double)(PI3) || (double)ray->angle < PI2)
		looking_right(ray, c);
	if ((double)ray->angle == PI2 || (double)ray->angle == (PI3)) //down/up
		looking_up_down(ray, c);
	while (!ray->hit)
	{
		if (ray->pos.x > 0 && ray->pos.y > 0 && ray->pos.y < c->map.height
			&& ray->pos.x < c->map.width)
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
	ray->dist = distance(c, ray);
	return (ray->dist);
}

void	looking_down(t_raycast *ray, t_mlx *c)
{
	float	a_tan;

	a_tan = -1 / tan(ray->angle);
	ray->pos.y = floor(c->p.pos.y) + 1;
	ray->pos.x = ((c->p.pos.y - ray->pos.y) * a_tan + c->p.pos.x);
	ray->step.y = TILE_SIZE;
	ray->step.x = (-ray->step.y) * a_tan;
	ray->color = MAROON;
}

void	looking_up(t_raycast *ray, t_mlx *c)
{
	float	a_tan;

	a_tan = -1 / tan(ray->angle);
	ray->pos.y = floor(c->p.pos.y) - 0.0001;
	ray->pos.x = (c->p.pos.y - ray->pos.y) * a_tan + c->p.pos.x;
	ray->step.y = -TILE_SIZE;
	ray->step.x = (-ray->step.y) * a_tan;
	ray->color = GREEN;
}

void	looking_left_right(t_raycast *ray, t_mlx *c)
{
	ray->pos.x = c->p.pos.x;
	ray->pos.y = c->p.pos.y;
	ray->step.x = 0;
	ray->step.y = 0;
	ray->color = RED;
}

float	horizontal_hit(t_raycast *ray, t_mlx *c)
{
	if (ray->angle > 0.0f && ray->angle < PI) // Looking down
		looking_down(ray, c);
	if (ray->angle > PI && ray->angle < (PII)) // LOOking UP
		looking_up(ray, c);
	if (ray->angle == 0 || ray->angle == PI) // Looking straight left/right
		looking_left_right(ray, c);
	while (!ray->hit)
	{
		if (ray->pos.x > 0 && ray->pos.y > 0 && ray->pos.y < c->map.height
			&& ray->pos.x < c->map.width)
		{
			if (c->map.map[(int)ray->pos.y][(int)ray->pos.x] == '1')
				ray->hit = true;
			else
			{
				ray->pos.x += (ray->step.x / TILE_SIZE);
				ray->pos.y += (ray->step.y / TILE_SIZE);
			}
		}
		else
			ray->hit = true;
	}
	ray->dist = distance(c, ray);
	return (ray->dist);
}

void	set_rays(t_raycast *ray, t_mlx *c, int row)
{
	ray[0].hit = false;
	ray[0].row = row;
	ray[0].angle = c->p.angle - (c->p.fov / 2)
		+ ((double)ray[0].row / (double)WIN_WIDTH) * c->p.fov;
	ray[1].hit = false;
	ray[1].row = row;
	ray[1].angle = c->p.angle - (c->p.fov / 2)
		+ ((double)ray[0].row / (double)WIN_WIDTH) * c->p.fov;
	ray[2].hit = false;
	ray[2].row = row;
	ray[2].angle = c->p.angle - (c->p.fov / 2)
		+ ((double)ray[0].row / (double)WIN_WIDTH) * c->p.fov;
	fix_angle(&ray[2].angle);
	fix_angle(&ray[1].angle);
}

void	draw_rays_2d(t_mlx *c)
{
	int			row;
	t_raycast	ray[3];
	t_coord		p;
	t_coord		r;

	row = -1;
	ray[2].color = 0xa10000;
	ray[1].color = 0xa10000;
	p.x = c->p.pos.x * TILE_SIZE - 1;
	p.y = c->p.pos.y * TILE_SIZE - 1;
	r.x = ray[0].pos.x * TILE_SIZE - 1;
	r.y = ray[0].pos.y * TILE_SIZE - 1;
	while (++row < WIN_WIDTH)
	{
		set_rays(ray, c, row);
		ray[1].dist = horizontal_hit(&ray[1], c);
		ray[2].dist = vertical_hit(&ray[2], c);
		ray[0] = ray[2];
		if (ray[1].dist < ray[2].dist)
			ray[0] = ray[1];
		if (c->show_minimap)
			draw_line(c, p, r, ray[0].color);
		raycaster_3d(c, &ray[0]);
	}
}
