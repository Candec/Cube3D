/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibanez- <jibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 16:50:09 by jibanez-          #+#    #+#             */
/*   Updated: 2022/12/19 02:17:39 by jibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	init(t_mlx *cube)
{
	cube->map.height = 0;
	cube->map.width = 0;
	cube->map.C_rgb.r = -1;
	cube->map.C_rgb.g = -1;
	cube->map.C_rgb.b = -1;
	cube->map.C_rgb.fill = FALSE;
	cube->map.F_rgb.r = -1;
	cube->map.F_rgb.g = -1;
	cube->map.F_rgb.b = -1;
	cube->map.F_rgb.fill = FALSE;
	cube->map.NO = NULL;
	cube->map.SO = NULL;
	cube->map.WE = NULL;
	cube->map.EA = NULL;
	cube->map.map = ft_calloc(sizeof(char **), 0);
}

void	parse(t_mlx *cube, char *map)
{
	if (ft_file_format(map, ".cub"))
		error("INCORRECT FILE FORMAT\n", cube);
	info(cube, map);
	validate_chr(cube);
	validate_map(cube);
}

int	main(int argc, char *argv[])
{
	t_mlx	cube;

	if (argc == 2)
	{
		init(&cube);
		parse(&cube, argv[1]);
		// ft_print_arr(cube.map.map);
		// ft_play(cube);
		quit(&cube);
	}
	else
	{
		write(1, "INVALID NUMBER OF ARGUMENTS\n", 29);
		return (1);
	}
	return (0);
}
