/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpereira <tpereira@42Lisboa.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 14:10:54 by jibanez-          #+#    #+#             */
/*   Updated: 2023/03/13 12:45:28 by tpereira         ###   ########.fr       */
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
			if (y > (WIN_HEIGHT / 2))
				add_pixel(&cube->frame, cube->map.f_rgb.int_rgb, x, y);
			else if (y < (WIN_HEIGHT / 2))
				add_pixel(&cube->frame, cube->map.c_rgb.int_rgb, x, y);
		}
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
	// // draw images here

	if (ray->color == MAROON)
		ray->texture = cube->img_so;
	else if (ray->color == GREEN)
		ray->texture = cube->img_no;
	else if (ray->color == BLUE)
		ray->texture = cube->img_we;
	else if (ray->color == RED)
		ray->texture = cube->img_ea;


	//while loop to print the wall with texture from xpm file
	while (w_top.y < w_bottom.y)
	{
		ray->color = ray->texture.data + (int)((int)w_top.y * ray->texture.size_l + (int)w_top.x
				* (ray->texture.bpp / 8));
		add_pixel(&cube->frame, ray->color, w_top.x, w_top.y);
		w_top.y++;
	}

	//draw_line(cube, w_top, w_bottom, ray->color);
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
