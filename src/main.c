/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpereira <tpereira@42Lisboa.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 16:50:09 by jibanez-          #+#    #+#             */
/*   Updated: 2023/03/21 21:35:39 by tpereira         ###   ########.fr       */
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

int	ft_add_str_to_arr(char *str, t_mlx *c)
{
	int		i;
	int		j;  
	char	**new_arr;
	char	*n_str;

	i = -1;
	j = -1;
	n_str = ft_calloc((ft_strlen(str) + 1), sizeof(char));
	if (!n_str)
		return (1);
	ft_strcpy(n_str, str);
	if (!c->map.map)
		i = 0;
	else
	{
		while (c->map.map[++i])
			;
	}
	new_arr = ft_calloc((i + 2), sizeof(char *));
	if (!new_arr)
		return (1);
	while (++j < i)
		new_arr[j] = ft_strdup(c->map.map[j]);
	new_arr[i] = n_str;
	new_arr[i + 1] = NULL;
	if (c->map.map)
		ft_clean_arr(c->map.map);
	c->map.map = new_arr;
	return (0);
}
