/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_vertical_rays.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpereira <tpereira@42Lisboa.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 14:42:48 by tpereira          #+#    #+#             */
/*   Updated: 2023/03/15 10:53:39 by tpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	looking_left(t_raycast *ray, t_mlx *c)
{
	float	a_tan;

	a_tan = -tan(ray->angle);
	ray->pos.x = floor(c->p.pos.x) - 0.0001;
	ray->pos.y = (c->p.pos.x - ray->pos.x) * a_tan + c->p.pos.y;
	ray->step.x = -TILE_SIZE;
	ray->step.y = (-ray->step.x) * a_tan;
	ray->color = YELLOW;
	ray->offset = fabs(ray->pos.y - (int)(ray->pos.y) * TILE_SIZE);
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
	ray->offset = fabs(ray->pos.y - (int)(ray->pos.y) * TILE_SIZE);
}

void	looking_up_down(t_raycast *ray, t_mlx *c)
{
	ray->pos.x = c->p.pos.x;
	ray->pos.y = c->p.pos.y;
	ray->step.x = 0;
	ray->step.y = 0;
	ray->color = RED;
	ray->offset = fabs(ray->pos.y - (int)(ray->pos.y) * TILE_SIZE);
}

float	vertical_hit(t_raycast *ray, t_mlx *c)
{
	//printf("ray->pos.y: %f\n", ray->pos.y);
	printf("ray->pos.y [%f] - (int)(ray->pos.y) [%d] = %f\n", ray->pos.y, (int)(ray->pos.y), ray->pos.y - (int)(ray->pos.y));
	if ((double)ray->angle > PI2 && (double)ray->angle < (PI3))
		looking_left(ray, c);
	if ((double)ray->angle > (double)(PI3) || (double)ray->angle < PI2)
		looking_right(ray, c);
	if ((double)ray->angle == PI2 || (double)ray->angle == (PI3))
		looking_up_down(ray, c);
	printf("offset_y: %d\n", ray->offset);
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
