/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibanez- <jibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 16:09:33 by jibanez-          #+#    #+#             */
/*   Updated: 2022/12/20 00:03:58 by jibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	error(char *msg, t_mlx *cube)
{
	printf("Error\n%s\n", msg);
	quit(cube);
}

int	quit(t_mlx *cube)
{
	ft_clean_arr(cube->map.map);
	ft_free(cube->map.NO);
	ft_free(cube->map.SO);
	ft_free(cube->map.EA);
	ft_free(cube->map.WE);
	if (cube->mlx_ptr || cube->win_init)
		mlx_destroy_window(cube->mlx_ptr, cube->win_ptr);
	(void)cube;
	exit(EXIT_FAILURE);
	return (TRUE);
}
