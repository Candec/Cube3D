/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibanez- <jibanez- <jibanez-@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 18:28:13 by jibanez-          #+#    #+#             */
/*   Updated: 2022/12/22 15:42:19 by jibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	xpm_to_image_wrapper(t_mlx *data, void *img, char *filename)
{
	int	size;

	size = SQ_S;
	img = mlx_xpm_file_to_image(data->mlx_ptr, filename, &size, &size);
	if (!img)
		return (0);
	return (1);
}

void	start_mlx_and_window(t_mlx *cube)
{
	bool	err;

	err = 1;
	cube->mlx_ptr = mlx_init();
	if (!cube->mlx_ptr)
		err = 0;
	cube->mlx_init = TRUE;
	cube->win_ptr = mlx_new_window(cube->mlx_ptr, 1920, 1080, "Cube_3D");
	if (!cube->win_ptr)
		err = 0;
	cube->win_init = TRUE;
	err = xpm_to_image_wrapper(cube, cube->img_NO, cube->map.NO);
	err = xpm_to_image_wrapper(cube, cube->img_SO, cube->map.SO);
	err = xpm_to_image_wrapper(cube, cube->img_EA, cube->map.EA);
	err = xpm_to_image_wrapper(cube, cube->img_WE, cube->map.WE);
	if (!err)
		error("COULDN'T LOAD IMAGES OR CREATE WINDOW\n", cube);
}
