/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpereira <tpereira@42Lisboa.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 18:28:13 by jibanez-          #+#    #+#             */
/*   Updated: 2023/01/26 17:14:36 by tpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	xpm_to_image_wrapper(t_mlx *data, void *img, char *filename)
{
	int	size;

	size = SQ_S;
	img = mlx_xpm_file_to_image(data->mlx_ptr, filename, &size, &size);
	if (!img)
		return (0);
	return (1);
}

void	load_img(t_mlx *cube)
{
	bool	err;

	err = FALSE;
	if (!xpm_to_image_wrapper(cube, cube->img_no, cube->map.no))
		err = TRUE;
	if (!xpm_to_image_wrapper(cube, cube->img_so, cube->map.so))
		err = TRUE;
	if (!xpm_to_image_wrapper(cube, cube->img_ea, cube->map.ea))
		err = TRUE;
	if (!xpm_to_image_wrapper(cube, cube->img_we, cube->map.we))
		err = TRUE;
	if (err)
		error("COULDN'T LOAD IMG\n", cube);
}

void	start_mlx_and_window(t_mlx *cube)
{
	bool	err;

	err = TRUE;
	cube->mlx_ptr = mlx_init();
	if (!cube->mlx_ptr)
		err = FALSE;
	cube->win_ptr = mlx_new_window(cube->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "Cube_3d");
	if (!cube->win_ptr)
		err = FALSE;
	if (!err)
		error("COULDN'T CREATE WINDOW\n", cube);
	cube->win = TRUE;
}

void	move_player(t_mlx *cube, int keysym)
{
	double x;
	double y;

	x = cube->player.posx;
	y = cube->player.posy;
	if (keysym == MOVE_UP)
		cube->player.posy -= 0.1;
	if (keysym == MOVE_DOWN)
		cube->player.posy += 0.1;
	if (keysym == MOVE_LEFT)
		cube->player.posx -= 0.1;
	if (keysym == MOVE_RIGHT)
		cube->player.posx += 0.1;
	if (cube->map.map[(int)cube->player.posy][(int)cube->player.posx] == '1')
	{
		cube->player.posx = x;
		cube->player.posy = y;
	}
}

void	player(t_mlx *cube, int keysym)
{
	if (keysym == MOVE_UP || keysym == MOVE_DOWN
		|| keysym == MOVE_LEFT || keysym == MOVE_RIGHT)
		move_player(cube, keysym);
	if (keysym == LOOK_LEFT)
		cube->player.angle -= 0.05;
	if (keysym == LOOK_RIGHT)
		cube->player.angle += 0.05;
	fix_angle(&cube->player.angle);
	cube->player.dirx = cos(cube->player.angle) * 5;
	cube->player.diry = sin(cube->player.angle) * 5;
	draw_map_2D(cube);
}

int	keypress(int keysym, t_mlx *cube)
{
	if (keysym == ESC)
		quit(cube);
	printf("%d\n", keysym);
	player(cube, keysym);
	// if (cube->map.player_escape == TRUE)
	// 	return (0);
	// else if (keysym == MOVE_UP|| keysym == MOVE_DOWN
	// 	|| keysym == MOVE_LEFT || keysym == MOVE_RIGHT)
	// move(data, keysym);
	return (0);
}

int	draw_frame(t_mlx *cube)
{
	cube->frame.img_width = WIN_WIDTH;
	cube->frame.img_height = WIN_HEIGHT;
	cube->frame.img = mlx_new_image(cube->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	cube->frame.data = (int *)mlx_get_data_addr(cube->frame.img, &cube->frame.bpp, &cube->frame.size_l, &cube->frame.endian);
	//draw_bg(cube);
	//draw_wall(cube, 500, 500, 100);
	draw_map_2D(cube);
	//draw_player_2D(cube);
	// draw_square(cube, 0, 0, 100, 0x00FF0000);
	mlx_put_image_to_window(cube->mlx_ptr, cube->win_ptr, cube->frame.img, 0, 0);
	return (0);
}

