/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpereira <tpereira@42Lisboa.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 22:47:09 by tpereira          #+#    #+#             */
/*   Updated: 2023/02/13 10:35:51 by tpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	blackout(t_mlx *cube)
{
	int x;
	int y;

	y = -1;
	while (++y < WIN_HEIGHT)
	{
		x = -1;
		while (++x < WIN_WIDTH)
			add_pixel(&cube->frame, 0, x, y);
	}
}

double	distance(double x1, double y1, double x2, double y2)
{
	double distance;

	distance = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
	//distance = x2 * cos(c->player.angle) + y2 * sin(ray->angle);  >>>>> MORE EFICIENT WAY -> no Square Root
	return (distance);
}

void	fix_fisheye(float p_angle, t_raycast *ray)
{
	float cos_angle;

	cos_angle = p_angle - ray->angle;
	if (cos_angle < 0)
		cos_angle += 2 * M_PI;
	if (cos_angle > 2 * M_PI)
		cos_angle -= 2 * M_PI;
	ray->dist = ray->dist * cos(cos_angle);
}
