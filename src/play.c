/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpereira <tpereira@42Lisboa.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 18:28:13 by jibanez-          #+#    #+#             */
/*   Updated: 2023/03/16 16:09:04 by tpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	start_mlx_and_window(t_mlx *c)
{
	bool	err;

	err = TRUE;
	c->mlx_ptr = mlx_init();
	if (!c->mlx_ptr)
		err = FALSE;
	c->win_ptr = mlx_new_window(c->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "Cub3d");
	if (!c->win_ptr)
		err = FALSE;
	if (!err)
		error("COULDN'T CREATE WINDOW\n", c);
	c->win = TRUE;
}

void	draw_loop(t_mlx *c)
{
	t_coord	p;
	t_coord	d;

	p.x = (c->p.pos.x * (TILE_SIZE / 2));
	p.y = (c->p.pos.y * (TILE_SIZE / 2));
	d.x = p.x + c->p.dirx * 5;
	d.y = p.y + c->p.diry * 5;
	blackout(c);
	draw_bg(c);
	if (c->show_minimap)
	{
		draw_rays_2d(c);
		draw_map_2d(c);
		draw_player_2d(c);
		draw_line(c, p, d, RED);
	}
	else
		draw_rays_2d(c);
	mlx_put_image_to_window(c->mlx_ptr, c->win_ptr, c->frame.img, 0, 0);
	//mlx_put_image_to_window(c->mlx_ptr, c->win_ptr, c->img_no.img, 0, 0);
}

void	player(t_mlx *cube, int keysym)
{
	move_player(cube, keysym);
	if (keysym == LOOK_LEFT)
		cube->p.angle -= 0.0174533 * 5;
	if (keysym == LOOK_RIGHT)
		cube->p.angle += 0.0174533 * 5;
	if (keysym == M_KEY)
	{
		if (cube->show_minimap)
			cube->show_minimap = 0;
		else
			cube->show_minimap = 1;
	}
	fix_angle(&cube->p.angle);
	cube->p.dirx = cos(cube->p.angle) * 5;
	cube->p.diry = sin(cube->p.angle) * 5;
	draw_loop(cube);
}

int	keypress(int keysym, t_mlx *cube)
{
	if (keysym == ESC)
		quit(cube);
	player(cube, keysym);
	return (0);
}

int get_pixel_from_image(t_img * img, int x, int y) {
	if (!img)
		return 0xff000000;
	if (x < 0 || y < 0 || x >= img->img_width || y >= img->img_height)
		return 0xff000000;
	return ((int)(*(img->data + (y * img->img_width)) + x));
}

int	draw_frame(t_mlx *cube)
{
	// testing textures here
	cube->img_no.img = mlx_xpm_file_to_image(cube->mlx_ptr, "./assets/brick.xpm", &cube->img_no.img_width, &cube->img_no.img_height);
	cube->img_no.data = (int *)mlx_get_data_addr(cube->img_no.img, &cube->img_no.bpp, &cube->img_no.size_l, &cube->img_no.endian);
	cube->img_we.img = mlx_xpm_file_to_image(cube->mlx_ptr, "./assets/brick.xpm", &cube->img_we.img_width, &cube->img_we.img_height);
	cube->img_we.data = (int *)mlx_get_data_addr(cube->img_we.img, &cube->img_we.bpp, &cube->img_we.size_l, &cube->img_we.endian);
	cube->img_ea.img = mlx_xpm_file_to_image(cube->mlx_ptr, "./assets/brick.xpm", &cube->img_ea.img_width, &cube->img_ea.img_height);
	cube->img_ea.data = (int *)mlx_get_data_addr(cube->img_ea.img, &cube->img_ea.bpp, &cube->img_ea.size_l, &cube->img_ea.endian);
	cube->img_so.img = mlx_xpm_file_to_image(cube->mlx_ptr, "./assets/brick.xpm", &cube->img_so.img_width, &cube->img_so.img_height);
	cube->img_so.data = (int *)mlx_get_data_addr(cube->img_so.img, &cube->img_so.bpp, &cube->img_so.size_l, &cube->img_so.endian);
	

	// end of testing textures

	
	cube->frame.img_width = WIN_WIDTH;
	cube->frame.img_height = WIN_HEIGHT;
	cube->frame.img = mlx_new_image(cube->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	cube->frame.data = (int *)mlx_get_data_addr(cube->frame.img,
			&cube->frame.bpp, &cube->frame.size_l, &cube->frame.endian);
	draw_loop(cube);
	// mlx_put_image_to_window(cube->mlx_ptr, cube->win_ptr, cube->img_no.img, 0, 0);
	// mlx_put_image_to_window(cube->mlx_ptr, cube->win_ptr, cube->img_we.img, 100, 0);
	// mlx_put_image_to_window(cube->mlx_ptr, cube->win_ptr, cube->img_ea.img, 200, 0);
	// mlx_put_image_to_window(cube->mlx_ptr, cube->win_ptr, cube->img_so.img, 300, 0);
	return (0);
}
