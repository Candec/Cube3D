/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpereira <tpereira@42Lisboa.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 18:28:13 by jibanez-          #+#    #+#             */
/*   Updated: 2023/02/28 09:44:34 by tpereira         ###   ########.fr       */
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

void	move_player(t_mlx *c, int keysym)
{
	double	x;
	double	y;
	int		floor_x;
	int		floor_y;

	floor_x = (int)floor(c->player.pos.x);
	floor_y = (int)floor(c->player.pos.y);
	x = c->player.pos.x;
	y = c->player.pos.y;
	if (keysym == MOVE_UP)
	{
		c->player.pos.y += c->player.diry / TILE_SIZE;
		c->player.pos.x += c->player.dirx / TILE_SIZE;
	}
	if (keysym == MOVE_DOWN)
	{
		c->player.pos.y -= c->player.diry / TILE_SIZE;
		c->player.pos.x -= c->player.dirx / TILE_SIZE;
	}
	if (keysym == MOVE_LEFT)
		c->player.pos.x -= c->player.dirx / TILE_SIZE;
	if (keysym == MOVE_RIGHT)
		c->player.pos.x += c->player.diry / TILE_SIZE;
	if (c->map.map[(int)floor(c->player.pos.y)][(int)floor(c->player.pos.x)] == '1')
	{
		c->player.pos.x = x;
		c->player.pos.y = y;
	}
}
// void	move_player(t_mlx *cube, int keysym)
// {
// 	double x;
// 	double y;

// 	x = cube->player.pos.x;
// 	y = cube->player.pos.y;
// 	if (keysym == MOVE_UP)
// 		cube->player.pos.y -= 0.1;
// 	if (keysym == MOVE_DOWN)
// 		cube->player.pos.y += 0.1;
// 	if (keysym == MOVE_LEFT)
// 		cube->player.pos.x -= 0.1;
// 	if (keysym == MOVE_RIGHT)
// 		cube->player.pos.x += 0.1;
// 	if (cube->map.map[(int)floor(cube->player.pos.y)][(int)floor(cube->player.pos.x)] == '1')
// 	{
// 		cube->player.pos.x = x;
// 		cube->player.pos.y = y;
// 	}
// }

void draw_loop(t_mlx *cube)
{
	double px;
	double py;
	double dx;
	double dy;

	px = (cube->player.pos.x * TILE_SIZE);
	py = (cube->player.pos.y * TILE_SIZE);
	dx = px + cube->player.dirx * 5;
	dy = py + cube->player.diry * 5;

	blackout(cube);
	draw_map_2D(cube);
	draw_player_2D(cube);
	// draw_rays_2D(cube, 0);
	raycaster(cube);
	mlx_put_image_to_window(cube->mlx_ptr, cube->win_ptr, cube->frame.img, 0, 0);
}

void	player(t_mlx *cube, int keysym)
{
	if (keysym == MOVE_UP || keysym == MOVE_DOWN
		|| keysym == MOVE_LEFT || keysym == MOVE_RIGHT)
		move_player(cube, keysym);
	if (keysym == LOOK_LEFT)
		cube->player.angle -= 0.1;
	if (keysym == LOOK_RIGHT)
		cube->player.angle += 0.1;
	if (keysym == M_KEY)
	{
		if (cube->show_minimap)
			cube->show_minimap = 0;
		else
			cube->show_minimap = 1;
	}
	fix_angle(&cube->player.angle);
	cube->player.dirx = cos(cube->player.angle) * 5;
	cube->player.diry = sin(cube->player.angle) * 5;
// =======
// 		cube->player.angle += 0.01;
// 	// fix_angle(&cube->player.angle);
// 	cube->player.dirx = cos(cube->player.angle);
// 	cube->player.diry = sin(cube->player.angle);
// >>>>>>> jesus2
	draw_loop(cube);
}

int	keypress(int keysym, t_mlx *cube)
{
	if (keysym == ESC)
		quit(cube);
	//printf("%d\n", keysym);
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
	draw_loop(cube);
	return (0);
}

