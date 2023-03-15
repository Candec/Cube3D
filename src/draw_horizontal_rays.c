/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_horizontal_rays.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpereira <tpereira@42Lisboa.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 14:45:20 by tpereira          #+#    #+#             */
/*   Updated: 2023/03/15 12:34:06 by tpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	looking_down(t_raycast *ray, t_mlx *c)
{
	float	a_tan;

	a_tan = -1 / tan(ray->angle);
	ray->pos.y = floor(c->p.pos.y) + 1;
	ray->pos.x = ((c->p.pos.y - ray->pos.y) * a_tan + c->p.pos.x);
	ray->step.y = TILE_SIZE;
	ray->step.x = (-ray->step.y) * a_tan;
	ray->color = MAROON;
	ray->offset = (ray->pos.x - (int)(ray->pos.x)) * TILE_SIZE;
	printf("down: %f\n", ray->offset);
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
	ray->offset = (ray->pos.x - (int)(ray->pos.x)) * TILE_SIZE;
	printf("up: %f\n", ray->offset);
}

void	looking_left_right(t_raycast *ray, t_mlx *c)
{
	ray->pos.x = c->p.pos.x;
	ray->pos.y = c->p.pos.y;
	ray->step.x = 0;
	ray->step.y = 0;
	ray->color = RED;
	ray->offset = (ray->pos.x - (int)(ray->pos.x)) * TILE_SIZE;
	printf("left/right: %f\n", ray->offset);
}

float	horizontal_hit(t_raycast *ray, t_mlx *c)
{
	if (ray->angle > 0.0f && ray->angle < PI)
		looking_down(ray, c);
	if (ray->angle > PI && ray->angle < (PII))
		looking_up(ray, c);
	if (ray->angle == 0 || ray->angle == PI)
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
