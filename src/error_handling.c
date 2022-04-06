/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibanez- <jibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 16:09:33 by jibanez-          #+#    #+#             */
/*   Updated: 2022/03/31 09:03:47 by jibanez-         ###   ########.fr       */
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
	//clean memory
	(void)cube;
	exit(EXIT_FAILURE);
}
