/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpereira <tpereira@42Lisboa.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 14:10:54 by jibanez-          #+#    #+#             */
/*   Updated: 2023/03/17 08:50:32 by tpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	int				wh;
	int				hold;
	int				tex_y;

	ray->dist = sqrt(distance(cube, ray));
	fix_fisheye(cube->p.angle, ray);
	wh = (int)((WIN_HEIGHT) / ray->dist);
	w_top.x = ray->col;
	w_top.y = ((WIN_HEIGHT) - (wh)) / 2;
	w_bottom.x = ray->col;
	w_bottom.y = ((WIN_HEIGHT) + (wh)) / 2;
	hold = w_top.y;
	ray->pixel = 0;
	tex_y = 0;
	while (w_top.y++ < w_bottom.y)
	{
		ray->offset = (int)ray->offset;
		tex_y = (((w_top.y - hold) / wh) - ((int)(w_top.y - hold) / wh))
			* ray->tex.img_height;
		ray->pixel = tex_y * ray->tex.img_height + ray->offset;
		add_pixel(&cube->frame, ray->tex.data[ray->pixel], w_top.x, w_top.y);
	}
}

void	set_rays(t_raycast *ray, t_mlx *c, int col)
{
	ray[0].hit = false;
	ray[0].col = col;
	ray[0].angle = c->p.angle - (c->p.fov / 2)
		+ ((double)ray[0].col / (double)WIN_WIDTH) * c->p.fov;
	ray[1].hit = false;
	ray[1].col = col;
	ray[1].angle = c->p.angle - (c->p.fov / 2)
		+ ((double)ray[0].col / (double)WIN_WIDTH) * c->p.fov;
	ray[2].hit = false;
	ray[2].col = col;
	ray[2].angle = c->p.angle - (c->p.fov / 2)
		+ ((double)ray[0].col / (double)WIN_WIDTH) * c->p.fov;
	fix_angle(&ray[2].angle);
	fix_angle(&ray[1].angle);
}

void	draw_rays_2d(t_mlx *c)
{
	int			col;
	t_raycast	ray[3];
	t_coord		p;
	t_coord		r;

	col = -1;
	ray[2].color = 0xa10000;
	ray[1].color = 0xa10000;
	p.x = c->p.pos.x * TILE_SIZE - 1;
	p.y = c->p.pos.y * TILE_SIZE - 1;
	r.x = ray[0].pos.x * TILE_SIZE - 1;
	r.y = ray[0].pos.y * TILE_SIZE - 1;
	while (++col < WIN_WIDTH)
	{
		set_rays(ray, c, col);
		ray[1].dist = horizontal_hit(&ray[1], c);
		ray[2].dist = vertical_hit(&ray[2], c);
		get_shortest_ray(&ray[0]);
		if (c->show_minimap)
			draw_line(c, p, r, ray[0].color);
		raycaster_3d(c, &ray[0]);
	}
}
