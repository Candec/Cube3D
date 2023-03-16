/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpereira <tpereira@42Lisboa.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 18:53:27 by tpereira          #+#    #+#             */
/*   Updated: 2023/03/16 18:57:29 by tpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	get_shortest_ray(t_raycast *ray)
{
	ray[0] = ray[2];
	ray[0].offset = (ray[2].pos.y - (int)ray[2].pos.y) * ray[2].tex.img_height;
	if (ray[1].dist < ray[2].dist)
	{
		ray[0] = ray[1];
		ray[0].offset = (ray[1].pos.x - (int)ray[1].pos.x)
			* ray[2].tex.img_width;
	}
}
