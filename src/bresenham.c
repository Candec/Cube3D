/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpereira <tpereira@42Lisboa.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 16:24:26 by tpereira          #+#    #+#             */
/*   Updated: 2023/01/25 11:00:21 by tpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	bresenham(t_mlx *cube, int x, int y, int x1, int y1)
{
	int	coord[2];

	coord[0] = x;
	coord[1] = y;
	while ((int)(x - x1) || (int)(y - y1))
	{
		add_pixel(cube->frame.img, x, y, WHITE);
		x += (x1 - x) / abs(x1 - x);
		y += (y1 - y) / abs(y1 - y);
	}
}
