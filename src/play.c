/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpereira <tpereira@42Lisboa.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 18:28:13 by jibanez-          #+#    #+#             */
/*   Updated: 2023/03/07 15:53:47 by tpereira         ###   ########.fr       */
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

void	strafe(t_mlx *c, int keysym)
{
	if (keysym == MOVE_LEFT)
	{
		if (c->player.angle > 0 && c->player.angle < PI)
		{
			c->player.pos.x -= cos(c->player.angle + PI / 2) / TILE_SIZE;
			c->player.pos.y -= sin(c->player.angle + PI / 2) / TILE_SIZE;
		}
		else
		{
			c->player.pos.x += cos(c->player.angle - PI / 2) / TILE_SIZE;
			c->player.pos.y += sin(c->player.angle - PI / 2) / TILE_SIZE;
		}
	}
	if (keysym == MOVE_RIGHT)
	{
		if (c->player.angle > 0 && c->player.angle < PI)
		{
			c->player.pos.x -= cos(c->player.angle - PI / 2) / TILE_SIZE;
			c->player.pos.y -= sin(c->player.angle - PI / 2) / TILE_SIZE;
		}
		else
		{
			c->player.pos.x += cos(c->player.angle + PI / 2) / TILE_SIZE;
			c->player.pos.y += sin(c->player.angle + PI / 2) / TILE_SIZE;
		}
	}
}

void	move_player(t_mlx *c, int keysym)
{
	double	x;
	double	y;
	int		floor_x;
	int		floor_y;

	x = c->player.pos.x;
	y = c->player.pos.y;
	if (keysym == MOVE_UP)
	{
		c->player.pos.y += (c->player.diry / TILE_SIZE) * 0.5;
		c->player.pos.x += (c->player.dirx / TILE_SIZE) * 0.5;
	}
	if (keysym == MOVE_DOWN)
	{
		c->player.pos.y -= c->player.diry / TILE_SIZE;
		c->player.pos.x -= c->player.dirx / TILE_SIZE;
	}
	strafe(c, keysym);
	floor_x = (int)floor(c->player.pos.x);
	floor_y = (int)floor(c->player.pos.y);
	if (c->map.map[floor_y][floor_x] == '1')
	{
		c->player.pos.x = x;
		c->player.pos.y = y;
	}
}

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
	if (cube->show_minimap)
	{
		draw_bg(cube);
		draw_rays_2D(cube);
		draw_map_2D(cube);
		draw_player_2D(cube);
		draw_line(cube, px, py, dx, dy, GREEN);			// show players direction
	}
	else
	{
		draw_bg(cube);
		draw_rays_2D(cube);
	}
	mlx_put_image_to_window(cube->mlx_ptr, cube->win_ptr, cube->frame.img, 0, 0);
}

void	player(t_mlx *cube, int keysym)
{
	if (keysym == MOVE_UP || keysym == MOVE_DOWN
		|| keysym == MOVE_LEFT || keysym == MOVE_RIGHT)
		move_player(cube, keysym);
	if (keysym == LOOK_LEFT)
		cube->player.angle -= 0.0174533 * 5;				// ONE DEGREE IN RADIANS * 5
	if (keysym == LOOK_RIGHT)
		cube->player.angle += 0.0174533 * 5;
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

int	mouse_move(t_mlx *cube)
{
	printf("mouse move\n");
	mlx_mouse_hide(cube->mlx_ptr, cube->win_ptr);
	printf("x: %d, y: %d\n", cube->mouse.x, cube->mouse.y);

	return (0);
}

int	draw_frame(t_mlx *cube)
{
	// int width;
	// int height;

	// width = cube->frame.img_width / 100;
	// height = cube->frame.img_height / 100;
	// // testing xpm image

	// cube->frame.img_width = WIN_WIDTH;
	// cube->frame.img_height = WIN_HEIGHT;
	// cube->frame.img = mlx_xpm_file_to_image(cube->mlx_ptr, "./assets/brick_wall.xpm", &width, &height);
	// cube->frame.data = (int *)mlx_get_data_addr(cube->frame.img, &cube->frame.bpp, &cube->frame.size_l, &cube->frame.endian);
	// mlx_put_image_to_window(cube->mlx_ptr, cube->win_ptr, cube->frame.img, 0, 0);

	// end testing xpm image


	cube->frame.img_width = WIN_WIDTH;
	cube->frame.img_height = WIN_HEIGHT;
	cube->frame.img = mlx_new_image(cube->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	cube->frame.data = (int *)mlx_get_data_addr(cube->frame.img, &cube->frame.bpp, &cube->frame.size_l, &cube->frame.endian);
	draw_loop(cube);
	return (0);
}

