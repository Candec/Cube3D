/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpereira <tpereira@42Lisboa.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 10:48:01 by tpereira          #+#    #+#             */
/*   Updated: 2023/02/16 12:19:23 by tpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	add_ray(t_mlx *cube, t_raycast ray)
{
	while (cube->rays.next)
		cube->rays = *cube->rays.next;
	cube->rays.next = ft_calloc(sizeof(t_rays), 0);
	cube->rays = *cube->rays.next;
	cube->rays.ray = ray;
	printf("ray->row%d\n", ray.row);
}

// void	draw_rays_2D(t_mlx *c)
// {
// 	t_raycast *ray;

// 	ray = malloc(sizeof(t_raycast));
// 	ray->row = -1;
// 	while (++ray->row < WIN_WIDTH)
// 	{
// 		ray->hit = false;
// 		ray->angle = c->player.angle -(c->player.fov / 2) + ((double)ray->row / (double)WIN_WIDTH) * c->player.fov;
// 		ray->pos.y = ((c->player.pos.y / (TILE_SIZE - 1)) * (TILE_SIZE - 1)) - 0.0001;
// 		ray->pos.x = (c->player.pos.y - ray->pos.y) * (-1 / tan(ray->angle)) + c->player.pos.x;
// 		ray->step = ft_coord(cos(ray->angle) * 0.0001, sin(ray->angle) * 0.0001);
// 		while (!ray->hit)
// 		{
// 			if (ray->pos.x > 0 && ray->pos.y > 0)
// 			{
// 				if (c->map.map[(int)floor(ray->pos.y)][(int)floor(ray->pos.x)] == '1')
// 					ray->hit = true;
// 				else
// 				{
// 					ray->pos.x += ray->step.x;
// 					ray->pos.y += ray->step.y;
// 				}
// 			}
// 			else
// 				ray->hit = true;
// 		}
// 		ray->dist = distance(c->player.posx, c->player.posy, ray->pos.x, ray->pos.y);
// 		//add_ray(c, ray);
// 		draw_line(c, (c->player.pos.x * TILE_SIZE) + (TILE_SIZE * 0.5), (c->player.pos.y * TILE_SIZE) + (TILE_SIZE * 0.5), ray->pos.x * TILE_SIZE, ray->pos.y * TILE_SIZE, RED);
// 	}
// 	free(ray);
// }
