/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpereira <tpereira@42Lisboa.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 16:50:09 by jibanez-          #+#    #+#             */
/*   Updated: 2023/03/21 21:49:59 by tpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	validation(t_mlx *c)
{
	if (!c->map.map || !*c->map.map || !c->map.map[0])
		error("INVALID MAP", c);
	if (c->p.e == FALSE)
		error("PLAYER MISSING OR TOO MANY PLAYERS", c);
	if (c->map.valid == FALSE)
		error("MISSING INFORMATION", c);
}

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
	cube->map.map = NULL;
	cube->win = FALSE;
	cube->show_minimap = FALSE;
	cube->mouse.x = 0;
	cube->mouse.y = 0;
	cube->mouse.pressed = FALSE;
}

void	parse(t_mlx *cube, char *map)
{
	if (ft_file_format(map, ".cub"))
		error("INCORRECT FILE FORMAT", cube);
	info(cube, map);
	validate_chr(cube);
	ft_square_array(&cube->map.map, '.');
	validate_map(cube);
	init_player(cube);
	validation(cube);
}

void	play(t_mlx *cube)
{
	start_mlx_and_window(cube);
	mlx_hook(cube->win_ptr, KeyPress, KeyPressMask, keypress, cube);
	mlx_hook(cube->win_ptr, DestroyNotify, StructureNotifyMask, leave, cube);
	load_img(cube);
	draw_frame(cube);
	mlx_loop(cube->mlx_ptr);
}

int	main(int argc, char *argv[])
{
	t_mlx	cube;

	if (argc != 2)
	{
		write(1, "INVALID NUMBER OF ARGUMENTS", 29);
		return (1);
	}
	init(&cube);
	parse(&cube, argv[1]);
	play(&cube);
	return (0);
}
