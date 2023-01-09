/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibanez- <jibanez- <jibanez-@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 16:09:33 by jibanez-          #+#    #+#             */
/*   Updated: 2023/01/09 15:46:06 by jibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	error(char *msg, t_mlx *cube)
{
	printf("Error\n%s\n", msg);
	quit(cube);
}

void	unload(t_mlx *cube)
{
	if (cube->img_no)
		mlx_destroy_image(cube->mlx_ptr, cube->img_no);
	if (cube->img_so)
		mlx_destroy_image(cube->mlx_ptr, cube->img_so);
	if (cube->img_ea)
		mlx_destroy_image(cube->mlx_ptr, cube->img_ea);
	if (cube->img_we)
		mlx_destroy_image(cube->mlx_ptr, cube->img_we);
}

int	quit(t_mlx *cube)
{
	ft_clean_arr(cube->map.map);
	ft_free(cube->map.no);
	ft_free(cube->map.so);
	ft_free(cube->map.ea);
	ft_free(cube->map.we);
	// unload(cube);
	if (cube->win)
		mlx_destroy_window(cube->mlx_ptr, cube->win_ptr);
	(void)cube;
	exit(EXIT_FAILURE);
	return (TRUE);
}
