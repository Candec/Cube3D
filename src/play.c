/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibanez- <jibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 18:28:13 by jibanez-          #+#    #+#             */
/*   Updated: 2022/12/20 00:07:41 by jibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	start_mlx_and_window(t_mlx *cube)
{
	cube->mlx_ptr = mlx_init();
	if (cube->mlx_ptr == NULL)
		error("MLX_PTR: COULDN'T INIT WINDOW\n", cube);
	cube->mlx_init = TRUE;
	cube->win_ptr = mlx_new_window(cube->mlx_ptr, 1920, 1080, "Cube_3D");
	if (cube->win_ptr == NULL)
		error("WIN_PTR: COULDN'T INIT WINDOW\n", cube);
	cube->win_init = TRUE;
}
