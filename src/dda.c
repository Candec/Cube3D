/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibanez- <jibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 02:00:19 by jibanez-          #+#    #+#             */
/*   Updated: 2023/02/24 02:15:01 by jibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static void	init_dda(t_mlx *c, t_raycast *r)
{
	r->dist = 0.0;
	r->hit = false;
	r->pos = ft_coord(c->player.pos.x, c->player.pos.y);
	r->len = ft_coord(0.0, 0.0);
	r->step = ft_coord(0.0, 0.0);
	r->dir = ft_coord(c->player.dirx, c->player.diry);
	r->step_size = ft_coord(fabs(1 / r->dir.x), fabs(1 / r->dir.y));
	// r->step_size = ft_coord(sqrt(1 + (r->dir.y / r->dir.x) * (r->dir.y / r->dir.x)),
			// sqrt(1 + (r->dir.x / r->dir.y) * (r->dir.x / r->dir.y)));
}

static void	dir_dda(t_mlx *c, t_raycast *r)
{
	if (r->dir.x < 0)
	{
		r->step.x = -1;
		r->len.x = (c->player.pos.x - r->pos.x) * r->step_size.x;
	}
	else
	{
		r->step.x = 1;
		r->len.x = ((r->pos.x + 1) - c->player.pos.x) * r->step_size.x;
	}
	if (r->dir.y < 0)
	{
		r->step.y = -1;
		r->len.y = (c->player.pos.y - r->pos.y) * r->step_size.y;
	}
	else
	{
		r->step.y = 1;
		r->len.y = ((r->pos.y + 1) - c->player.pos.y) * r->step_size.y;
	}
}

void	dda(t_mlx *c, t_raycast *r)
{
	init_dda(c, r);
	dir_dda(c, r);
	while (!r->hit)
	{
		if (r->len.x < r->len.y)
		{
			r->pos.x += r->step.x;
			r->len.x += r->step.x;
		}
		else
		{
			r->pos.y += r->step.y;
			r->len.y += r->step.y;
		}
		if (c->map.map[(int)r->pos.y][(int)r->pos.x] == '1')
		{
			r->hit = true;
			printf("HIT\n");
			printf("\n----\nLen X: %f - Len Y: %f\nDir X: %f - Dir Y: %f\nPos X: %f - Pos Y: %f\nStep_size X: %f - Step_size Y: %f\nMap Char: [%c]\n",
				r->len.x, r->len.y, r->dir.x, r->dir.y, r->pos.x, r->pos.y, r->step_size.x, r->step_size.y, c->map.map[(int)r->pos.y][(int)r->pos.x]);
		}
	}
	r->hit_pos = ft_coord(c->player.pos.x + r->dir.x * r->tot_len,
			c->player.pos.y + r->dir.y * r->tot_len);
}
