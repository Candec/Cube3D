/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpereira <tpereira@42Lisboa.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 16:24:26 by tpereira          #+#    #+#             */
/*   Updated: 2023/01/26 16:59:02 by tpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

// void	bresenham(t_mlx *cube, int x, int y, int x1, int y1)
// {
// 	int	coord[2];

// 	coord[0] = x;
// 	coord[1] = y;
// 	while ((int)(x - x1) || (int)(y - y1))
// 	{
// 		add_pixel(cube->frame.img, x, y, WHITE);
// 		x += (x1 - x) / abs(x1 - x);
// 		y += (y1 - y) / abs(y1 - y);
// 	}
// }


void	my_mlx_pixel_put(t_mlx *cube, int x, int y, int color)
{
	char	*dst;

	if (x < cube->frame.img_width && y < cube->frame.img_height && x > 0 && y > 0)
	{
		dst = cube->frame.img + (y * cube->frame.size_l + x
				* (cube->frame.bpp / 8));
		*(unsigned int *)dst = color;
	}
}

void	bresenham(t_mlx *cube, float x1, float y1, int color)
{
	while ((int)(cube->player.posx- x1) || (int)(cube->player.posy - y1))
	{
		my_mlx_pixel_put(cube, cube->player.posx, cube->player.posy + 1, color);
		cube->player.posx+= 0.1;
		cube->player.posy += 0.1;
	}
}