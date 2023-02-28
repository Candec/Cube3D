/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpereira <tpereira@42Lisboa.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 02:00:19 by jibanez-          #+#    #+#             */
/*   Updated: 2023/02/28 09:28:36 by tpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static void	init_dda(t_mlx *c, t_raycast *r)
{
	r->dist = 0.0;
	r->hit = false;
	r->pos = ft_coord(c->player.pos.x, c->player.pos.y);
	r->hit_pos = ft_coord(0.0, 0.0);
	r->step = ft_coord(0.0, 0.0);
	//r->dir = ft_coord(c->player.dirx, c->player.diry);
	r->dir.x = cos(r->angle);
	r->dir.y = sin(r->angle);
	r->step_size = ft_coord(fabs(1.0 / r->dir.x), fabs(1.0 / r->dir.y));
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
	int col;

	col = -1;
	while (++col < WIN_WIDTH)
	{
		r->angle = c->player.angle - (c->player.fov / 2) + ((double)col / (double)WIN_WIDTH) * c->player.fov;
		init_dda(c, r);
		while (!r->hit)
		{
			dir_dda(c, r);
			if (r->len.x < r->len.y)
			{
				r->pos.x += r->step.x;
				r->tot_len = r->len.x;
				r->len.x += r->step_size.x;
			}
			else
			{
				r->pos.y += r->step.y;
				r->tot_len = r->len.y;
				r->len.y += r->step_size.y;
			}
			if (c->map.map[(int)r->pos.y][(int)r->pos.x] == '1')
			{
				r->hit = true;
			}
		}
		r->hit_pos = ft_coord(c->player.pos.x + r->dir.x * r->tot_len,
				c->player.pos.y + r->dir.y * r->tot_len);
		draw_line(c, c->player.pos.x * TILE_SIZE, c->player.pos.y  * TILE_SIZE, r->hit_pos.x * TILE_SIZE - TILE_SIZE / 2, r->hit_pos.y * TILE_SIZE - TILE_SIZE / 2, RED);
	}
}

// printf("\n----\nLen X: %f - Len Y: %f\nDir X: %f - Dir Y: %f\nHit pos X: %f - Hit pos Y: %f\nPlayer X: %f - Player Y: %f\nStep_size X: %f - Step_size Y: %f\nMap Char: [%c]\n", r->len.x, r->len.y, r->dir.x, r->dir.y, r->pos.x, r->pos.y, c->player.pos.x, c->player.pos.y, r->step_size.x, r->step_size.y, c->map.map[(int)r->pos.y][(int)r->pos.x]);
// printf("HIT\n");
// printf("distance: %f\n", distance(c->player.pos.x, c->player.pos.y, r->hit_pos.x, r->hit_pos.y));