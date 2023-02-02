/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibanez- <jibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 22:47:09 by tpereira          #+#    #+#             */
/*   Updated: 2023/02/01 16:27:42 by jibanez-         ###   ########.fr       */
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
	return (distance);
}
