/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibanez- <jibanez- <jibanez-@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 16:50:09 by jibanez-          #+#    #+#             */
/*   Updated: 2022/12/22 16:40:46 by jibanez-         ###   ########.fr       */
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
	cube->mlx_ptr = FALSE;
	cube->win_ptr = FALSE;
}

void	parse(t_mlx *cube, char *map)
{
	if (ft_file_format(map, ".cub"))
		error("INCORRECT FILE FORMAT\n", cube);
	info(cube, map);
	validate_chr(cube);
	validate_map(cube);
}

void	play(t_mlx *cube)
{
	start_mlx_and_window(cube);
	// mlx_hook(data->win_ptr, 02, 1L << 2, &handle_keypress, data);
	mlx_hook(cube->win_ptr, DestroyNotify, StructureNotifyMask, &quit, cube);
	mlx_loop(cube->mlx_ptr);
}

int	main(int argc, char *argv[])
{
	t_mlx	cube;

	if (argc == 2)
	{
		init(&cube);
		parse(&cube, argv[1]);
		play(&cube);
		quit(&cube);
	}
	else
	{
		write(1, "INVALID NUMBER OF ARGUMENTS\n", 29);
		return (1);
	}
	return (0);
}
