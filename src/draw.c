/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibanez- <jibanez- <jibanez-@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 14:10:54 by jibanez-          #+#    #+#             */
/*   Updated: 2023/01/09 18:18:11 by jibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	encode_rgb(uint8_t red, uint8_t green, uint8_t blue)
{
	return (red << 16 | green << 8 | blue);
}

void	dda(t_mlx *cube)
{
	while (cube->p.x < WIDTH)
	{
		cube->p.camerax = 2 * cube->p.x / WIDTH - 1;
		cube->p.raydirx = cube->p.dirx * cube->p.camerax;
		cube->p.raydiry = cube->p.diry * cube->p.camerax;
		cube->p.deltadisx = ft_ternary_double(cube->p.raydirx == 0,
				1e30, ft_abs(1 / cube->p.raydirx));
		cube->p.deltadisx = ft_ternary_double(cube->p.raydirx == 0,
				1e30, ft_abs(1 / cube->p.raydirx));

		if (cube->p.raydirx < 0)
		{
			cube->p.stepx = -1;
			cube->p.sidedisx = 0.0;
		}
		else
		{
			cube->p.stepx = 1;
			cube->p.sidedisx = cube->p.deltadisx;
		}
		if (cube->p.raydiry < 0)
		{
			cube->p.stepy = -1;
			cube->p.sidedisy = 0.0;
		}
		else
		{
			cube->p.stepy = 1;
			cube->p.sidedisy = cube->p.deltadisy;
		}
	}
}

void	draw_wall(t_mlx *cube)
{
	int h;
	int w;

	h = -1;
	w = -1;
	while (++h < HEIGHT)
	{
		while (++w < WIDTH)
		{
			if (h > HEIGHT / 2)
				mlx_pixel_put(cube->mlx_ptr, cube->win_ptr, w, h,
					encode_rgb(cube->map.c_rgb.r, cube->map.c_rgb.g, cube->map.c_rgb.b));
			else
				mlx_pixel_put(cube->mlx_ptr, cube->win_ptr, w, h,
					encode_rgb(cube->map.f_rgb.r, cube->map.f_rgb.g, cube->map.f_rgb.b));
		}
	}
}