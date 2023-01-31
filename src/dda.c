/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibanez- <jibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 02:00:19 by jibanez-          #+#    #+#             */
/*   Updated: 2023/01/31 02:01:10 by jibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

t_coord	dda(t_mlx *cube, size_t x, size_t y)
{
	t_coord	endcell;
	t_coord	ray_dir;
	t_coord	cur_grid;
	t_coord	ray_len;
	t_coord	ray_step;
	t_coord	ray_unit_step_size;
	t_coord	intersection;
	double	distance;
	bool	reach_end;

	endcell = ft_init_coord(x, y);
	ray_dir = ft_init_coord(endcell.x - cube->player.pos.x,
			endcell.y - cube->player.pos.y);
	ray_unit_step_size = ft_init_coord(sqrt(1 + ft_powd((ray_dir.y / ray_dir.x), 2.0)),
			sqrt(1 + ft_powd((ray_dir.x / ray_dir.y), 2.0)));
	cur_grid = ft_init_coord(cube->player.pos.x, cube->player.pos.y);
	if (ray_dir.x < 0)
	{
		ray_step.x = -1;
		ray_len.x = (cube->player.pos.x - cur_grid.x) * ray_unit_step_size.x;
	}
	else
	{
		ray_step.x = 1;
		ray_len.x = ((cur_grid.x + 1) - cube->player.pos.x) * ray_unit_step_size.x;
	}
	if (ray_dir.y < 0)
	{
		ray_step.y = -1;
		ray_len.y = (cube->player.pos.y - cur_grid.y) * ray_unit_step_size.y;
	}
	else
	{
		ray_step.y = 1;
		ray_len.y = ((cur_grid.y + 1) - cube->player.pos.y) * ray_unit_step_size.y;
	}
	reach_end = false;
	distance = 0.0;
	while (!reach_end)
	{
		if (ray_len.x < ray_len.y)
		{
			cur_grid.x += ray_step.x;
			distance = ray_len.x;
			ray_len.x += ray_unit_step_size.x;
		}
		else
		{
			cur_grid.y += ray_step.y;
			distance = ray_len.y;
			ray_len.y += ray_unit_step_size.y;
		}
		if (ft_strncmp(&cube->map.map[(int)cur_grid.y][(int)cur_grid.x], "1", 1))
			reach_end = true;
	}
	intersection.x = cube->player.pos.x + ray_dir.x * distance;
	intersection.y = cube->player.pos.y + ray_dir.y * distance;
	return (intersection);
}