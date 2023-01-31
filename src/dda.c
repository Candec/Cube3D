/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpereira <tpereira@42Lisboa.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 02:00:19 by jibanez-          #+#    #+#             */
/*   Updated: 2023/01/31 12:57:38 by tpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

// static void	init_dda(t_mlx *c, t_raycast *r, double x, double y)
// {
// 	r.distance = 0.0;
// 	r.reach_end = false;
// 	r.end = ft_coord(x, y);
// 	r.dir = ft_coord(r.end.x - c->player.pos.x, r.end.y - c->player.pos.y);
// 	r.step_size = ft_coord(sqrt(1 + ft_powd((r.dir.y / r.dir.x), 2.0)),
// 			sqrt(1 + ft_powd((r.dir.x / r.dir.y), 2.0)));
// 	r.grid = ft_coord(c->player.pos.x, c->player.pos.y);
// }

// static void	dir_dda(t_mlx *c, t_raycast *r)
// {
// 	if (r.dir.x < 0)
// 	{
// 		r.step.x = -1;
// 		r.len.x = (c->player.pos.x - r.grid.x) * r.step_size.x;
// 	}
// 	else
// 	{
// 		r.step.x = 1;
// 		r.len.x = ((r.grid.x + 1) - c->player.pos.x) * r.step_size.x;
// 	}
// 	if (r.dir.y < 0)
// 	{
// 		r.step.y = -1;
// 		r.len.y = (c->player.pos.y - r.grid.y) * r.step_size.y;
// 	}
// 	else
// 	{
// 		r.step.y = 1;
// 		r.len.y = ((r.grid.y + 1) - c->player.pos.y) * r.step_size.y;
// 	}
// }

// t_coord	dda(t_mlx *c, double x, double y)
// {
// 	t_raycast *r;

// 	init_dda(c, r, x, y);
// 	dir_dda(c, r);
// 	while (!r.reach_end)
// 	{
// 		if (r.len.x < r.len.y)
// 		{
// 			r.grid.x += r.step.x;
// 			r.distance = r.len.x;
// 			r.len.x += r.step_size.x;
// 		}
// 		else
// 		{
// 			r.grid.y += r.step.y;
// 			r.distance = r.len.y;
// 			r.len.y += r.step_size.y;
// 		}
// 		if (ft_strncmp(&c->map.map[(int)r.grid.y][(int)r.grid.x], "1", 1))
// 			r.reach_end = true;
// 	}
// 	r.intersection = ft_coord(c->player.pos.x + r.dir.x * r.distance,
// 		c->player.pos.y + r.dir.y * r.distance);
// 	return (r.intersection);
// }