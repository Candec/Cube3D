/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibanez- <jibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 16:50:09 by jibanez-          #+#    #+#             */
/*   Updated: 2023/03/12 20:09:50 by jibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	init(t_mlx *cube)
{
	cube->map.height = 0;
	cube->map.width = 0;
	cube->map.rows = 0;
	cube->map.cols = 0;
	cube->map.c_rgb.r = -1;
	cube->map.c_rgb.g = -1;
	cube->map.c_rgb.b = -1;
	cube->map.c_rgb.fill = FALSE;
	cube->map.f_rgb.r = -1;
	cube->map.f_rgb.g = -1;
	cube->map.f_rgb.b = -1;
	cube->map.f_rgb.fill = FALSE;
	cube->map.no = NULL;
	cube->map.so = NULL;
	cube->map.we = NULL;
	cube->map.ea = NULL;
	cube->img_f = NULL;
	cube->img_c = NULL;
	cube->map.map = ft_calloc(sizeof(char **), 0);
	cube->win = FALSE;
	cube->show_minimap = FALSE;
	cube->mouse.x = 0;
	cube->mouse.y = 0;
	cube->mouse.pressed = FALSE;
}

void	parse(t_mlx *cube, char *map)
{
	if (ft_file_format(map, ".cub"))
		error("INCORRECT FILE FORMAT\n", cube);
	info(cube, map);
	validate_chr(cube);
	validate_map(cube);
	ft_square_array(&cube->map.map, ' ');
	init_player(cube);
	load_img(cube);
}

void	play(t_mlx *cube)
{
	start_mlx_and_window(cube);
	mlx_hook(cube->win_ptr, KeyPress, KeyPressMask, keypress, cube);
	mlx_hook(cube->win_ptr, DestroyNotify, StructureNotifyMask, quit, cube);
	draw_frame(cube);
	mlx_loop(cube->mlx_ptr);
}

int	main(int argc, char *argv[])
{
	t_mlx	cube;

	if (argc != 2)
	{
		write(1, "INVALID NUMBER OF ARGUMENTS\n", 29);
		return (1);
	}
	init(&cube);
	parse(&cube, argv[1]);
	play(&cube);
	quit(&cube);
	return (0);
}
