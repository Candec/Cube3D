/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpereira <tpereira@42Lisboa.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 14:10:54 by jibanez-          #+#    #+#             */
/*   Updated: 2023/03/14 23:02:16 by tpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char *dst;

	dst = img->img + (y * img->size_l + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

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

unsigned int	get_texture_color(t_img *texture, int pixel_x, int pixel_y)
{
	return (*(unsigned int *)((texture->data
			+ (pixel_y * texture->size_l) + (pixel_x * texture->bpp / 8))));
}

void	raycaster_3d(t_mlx *cube, t_raycast *ray)
{
	t_coord			w_top;
	t_coord			w_bottom;
	int				wall_height;

	ray->dist = sqrt(distance(cube, ray));
	fix_fisheye(cube->p.angle, ray);
	wall_height = (TILE_SIZE / ray->dist) * WALL_HEIGHT;
	w_top.x = ray->col;
	w_top.y = ((WIN_HEIGHT / 2) - (wall_height / 2)) / 2;
	w_bottom.x = ray->col;
	w_bottom.y = ((WIN_HEIGHT / 2) + (wall_height / 2)) / 2;
	
	printf("offset: %d\n", ray->offset);
	// while loop to print the wall with texture from xpm file
	while (w_top.y++ < w_bottom.y)
	{
		// calculate texture coordinate for current pixel (WALL_HEIGHT - lineheight)

		// int tex_y = ((w_top.y - WALL_HEIGHT / 2 + wall_height / 2) * 64) / wall_height;
		// char *dst = ray->texture.img + (tex_y * ray->texture.size_l + (ray->offset * TILE_SIZE) * (ray->texture.bpp / 8));
		// ray->color = *(unsigned int *)dst;
		// add_pixel(&cube->frame, ray->color, w_top.x, w_top.y);

		// int pixel = (ray->offset * 64) + (w_top.y);
		// add_pixel(&cube->frame, ray->texture.data[pixel], w_top.x, w_top.y);
		int pixel = (w_top.y * 64) + (ray->col);

		// add_pixel(&c->frame, ray->texture.data[((j) * 64) + (i)], i + 100, j + 100);
		
		// int pixel = (ray->offset * 16 + w_top.y) * 3;
		// ray->color = get_texture_color(&ray->texture, ray->offset, w_top.y);
		// add_pixel(&cube->frame, ray->color, w_top.x, w_top.y);
		add_pixel(&cube->frame, ray->texture.data[pixel], w_top.x, w_top.y);
	}

	//draw_line(cube, w_top, w_bottom, ray->color);
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
		// printf("ray[1].offset = %d\n", ray[1].offset);
		// printf("ray[2].offset = %d\n", ray[2].offset);
		ray[0] = ray[2];
		if (ray[1].dist < ray[2].dist)
			ray[0] = ray[1];
		if (c->show_minimap)
			draw_line(c, p, r, ray[0].color);

		if (ray->color == MAROON)
			ray->texture = c->img_so;
		if (ray->color == BLUE)
			ray->texture = c->img_ea;
		if (ray->color == GREEN)
			ray->texture = c->img_no;
		if (ray->color == YELLOW)
			ray->texture = c->img_we;
		raycaster_3d(c, &ray[0]);
	}
	// if (ray->color == MAROON)
	// 	ray->texture = c->img_so;
	// if (ray->color == BLUE)
	// 	ray->texture = c->img_ea;
	// if (ray->color == GREEN)
	// 	ray->texture = c->img_no;
	// if (ray->color == YELLOW)
	// 	ray->texture = c->img_we;
	// int i = 0;
	// while (i < ray->texture.img_width)
	// {
	// 	int j = 0;
	// 	while (j < ray->texture.img_height)
	// 	{
	// 		printf("ray->texture.data[%d + %d(%d)] -> %d\n",i, j,  i + j, ray->texture.data[i + j]);
	// 		add_pixel(&c->frame, ray->texture.data[((j) * 64) + (i)], i + 100, j + 100);
	// 		j++;
	// 	}
	// 	i++;
	// }
}
