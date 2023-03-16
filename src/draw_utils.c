/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpereira <tpereira@42Lisboa.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 22:47:09 by tpereira          #+#    #+#             */
/*   Updated: 2023/03/16 18:02:27 by tpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	blackout(t_mlx *cube)
{
	int	x;
	int	y;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
			add_pixel(&cube->frame, 0, x, y);
	}
}

double	distance(t_mlx *c, t_raycast *ray)
{
	double	squared_dist;

	squared_dist = pow(ray->pos.x - c->p.pos.x, 2)
		+ pow(ray->pos.y - c->p.pos.y, 2);
	return (squared_dist);
}

void	fix_fisheye(float p_angle, t_raycast *ray)
{
	float	cos_angle;

	cos_angle = p_angle - ray->angle;
	if (cos_angle < 0)
		cos_angle += (PII);
	if (cos_angle > (PII))
		cos_angle -= (PII);
	ray->dist = ray->dist * cos(cos_angle);
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
