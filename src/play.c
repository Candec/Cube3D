/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpereira <tpereira@42Lisboa.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 18:28:13 by jibanez-          #+#    #+#             */
/*   Updated: 2023/03/17 10:16:21 by tpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

int	draw_frame(t_mlx *c)
{
	// c->img_no.img = mlx_xpm_file_to_image(c->mlx_ptr, c->map.no,
	// 		&c->img_no.img_width, &c->img_no.img_height);
	// c->img_no.data = (int *)mlx_get_data_addr(c->img_no.img, &c->img_no.bpp,
	// 		&c->img_no.size_l, &c->img_no.endian);
	// c->img_we.img = mlx_xpm_file_to_image(c->mlx_ptr, c->map.we,
	// 		&c->img_we.img_width, &c->img_we.img_height);
	// c->img_we.data = (int *)mlx_get_data_addr(c->img_we.img, &c->img_we.bpp,
	// 		&c->img_we.size_l, &c->img_we.endian);
	// c->img_ea.img = mlx_xpm_file_to_image(c->mlx_ptr, c->map.ea,
	// 		&c->img_ea.img_width, &c->img_ea.img_height);
	// c->img_ea.data = (int *)mlx_get_data_addr(c->img_ea.img, &c->img_ea.bpp,
	// 		&c->img_ea.size_l, &c->img_ea.endian);
	// c->img_so.img = mlx_xpm_file_to_image(c->mlx_ptr, c->map.so,
	// 		&c->img_so.img_width, &c->img_so.img_height);
	// c->img_so.data = (int *)mlx_get_data_addr(c->img_so.img, &c->img_so.bpp,
	// 		&c->img_so.size_l, &c->img_so.endian);
	c->frame.img_width = WIN_WIDTH;
	c->frame.img_height = WIN_HEIGHT;
	c->frame.img = mlx_new_image(c->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	c->frame.data = (int *)mlx_get_data_addr(c->frame.img,
			&c->frame.bpp, &c->frame.size_l, &c->frame.endian);
	draw_loop(c);
	return (0);
}
