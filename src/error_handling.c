/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibanez- <jibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 16:09:33 by jibanez-          #+#    #+#             */
/*   Updated: 2022/12/19 00:52:33 by jibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	error(char *msg, t_mlx *cube)
{
	printf("Error\n%s\n", msg);
	quit(cube);
}

void	quit(t_mlx *cube)
{
	ft_clean_arr(cube->map.map);
	ft_free(cube->map.NO);
	ft_free(cube->map.SO);
	ft_free(cube->map.EA);
	ft_free(cube->map.WE);
	(void)cube;
	exit(EXIT_FAILURE);
}
