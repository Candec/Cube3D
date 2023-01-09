/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibanez- <jibanez- <jibanez-@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 14:10:54 by jibanez-          #+#    #+#             */
/*   Updated: 2023/01/09 17:42:41 by jibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	dda(t_mlx *cube)
{
	while (cube->p.x < WIDTH)
	{
		cube->p.camerax = 2 * cube->p.x / double (WIDTH) - 1;
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
