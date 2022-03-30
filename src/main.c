/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibanez- <jibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 16:50:09 by jibanez-          #+#    #+#             */
/*   Updated: 2022/03/30 16:19:02 by jibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	main(int argc, char *argv[])
{
	t_mlx	cube;

	if (argc == 2)
	{
		ft_parse(&cube, argv[1]);
		// ft_print_map(cube);
		// ft_play(cube);
	}
	else
	{
		write(1, "INVALID NUMBER OF ARGUMENTS\n", 29);
		return (1);
	}
	return (0);
}