/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibanez- <jibanez- <jibanez-@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 16:09:33 by jibanez-          #+#    #+#             */
/*   Updated: 2022/12/15 17:35:06 by jibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	ft_error(char *msg, t_mlx *cube)
{
	printf("Error\n%s\n", msg);
	ft_exit(cube);
}

void	ft_exit(t_mlx *cube)
{
	ft_clean_arr(cube->map.map);
	ft_free(cube->map.NO);
	ft_free(cube->map.SO);
	ft_free(cube->map.EA);
	ft_free(cube->map.WE);
	(void)cube;
	exit(EXIT_FAILURE);
}
