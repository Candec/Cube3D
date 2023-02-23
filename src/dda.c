/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibanez- <jibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 02:00:19 by jibanez-          #+#    #+#             */
/*   Updated: 2023/02/23 15:11:00 by jibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static void	init_dda(t_mlx *c, t_raycast *r)
{
	r->dist = 0.0;
	r->hit = false;
	r->pos = ft_coord(c->player.pos.x, c->player.pos.y);
	r->len = ft_coord(0.0, 0.0);
	r->dir = ft_coord(c->player.dirx, c->player.diry);
	r->step = ft_coord(sqrt(1 + ft_powd((r->dir.y / r->dir.x), 2.0)),
			sqrt(1 + ft_powd((r->dir.x / r->dir.y), 2.0)));
}

static void	dir_dda(t_mlx *c, t_raycast *r)
{
	if (r->dir.x < 0)
	{
		r->step.x = -1;
		r->len.x = (c->player.pos.x - r->pos.x) * r->step.x;
	}
	else
	{
		r->step.x = 1;
		r->len.x = ((r->pos.x + 1) - c->player.pos.x) * r->step.x;
	}
	if (r->dir.y < 0)
	{
		r->step.y = -1;
		r->len.y = (c->player.pos.y - r->pos.y) * r->step.y;
	}
	else
	{
		r->step.y = 1;
		r->len.y = ((r->pos.y + 1) - c->player.pos.y) * r->step.y;
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
			r->tot_len = r->len.x;
			r->len.x += r->step.x;
		}
		else
		{
			r->pos.y += r->step.y;
			r->tot_len = r->len.y;
			r->len.y += r->step.y;
		}
		if (ft_strncmp(&c->map.map[(int)r->pos.y][(int)r->pos.x], "1", 1))
			r->hit = true;
	}
	r->hit_pos = ft_coord(c->player.pos.x + r->dir.x * r->tot_len,
			c->player.pos.y + r->dir.y * r->tot_len);
}
