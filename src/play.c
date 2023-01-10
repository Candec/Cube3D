/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibanez- <jibanez- <jibanez-@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 18:28:13 by jibanez-          #+#    #+#             */
/*   Updated: 2023/01/10 14:36:23 by jibanez-         ###   ########.fr       */
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
	cube->win_ptr = mlx_new_window(cube->mlx_ptr, 640, 360, "Cube_3d");
	if (!cube->win_ptr)
		err = FALSE;
	if (!err)
		error("COULDN'T CREATE WINDOW\n", cube);
	cube->win = TRUE;
}

int	keypress(int keysym, t_mlx *cube)
{
	if (keysym == ESC)
		quit(cube);
	printf("%d\n", keysym);
	// if (cube->map.player_escape == TRUE)
	// 	return (0);
	// else if (keysym == MOVE_UP|| keysym == MOVE_DOWN
	// 	|| keysym == MOVE_LEFT || keysym == MOVE_RIGHT)
		// move(data, keysym);
	return (0);
}

int	draw_frame(t_mlx *cube)
{
	cube->frame.img_width = WIDTH;
	cube->frame.img_height = HEIGHT;
	cube->frame.img = mlx_new_image(cube->mlx_ptr, WIDTH, HEIGHT);
	cube->frame.data = (int *)mlx_get_data_addr(&cube->frame.img,
		&cube->frame.bpp, &cube->frame.size_l, &cube->frame.endian);
	draw_bg(cube);
	mlx_put_image_to_window(cube->mlx_ptr, cube->win_ptr, cube->frame.img, 0, 0);
	return (0);
}