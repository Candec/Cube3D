/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpereira <tpereira@42Lisboa.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 18:28:13 by jibanez-          #+#    #+#             */
/*   Updated: 2023/03/08 14:09:12 by tpereira         ###   ########.fr       */
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
		if (c->p.angle > 0 && c->p.angle < PI)
		{
			c->p.pos.x -= cos(c->p.angle + PI / 2) / TILE_SIZE;
			c->p.pos.y -= sin(c->p.angle + PI / 2) / TILE_SIZE;
		}
		else
		{
			c->p.pos.x += cos(c->p.angle - PI / 2) / TILE_SIZE;
			c->p.pos.y += sin(c->p.angle - PI / 2) / TILE_SIZE;
		}
	}
	if (keysym == MOVE_RIGHT)
	{
		if (c->p.angle > 0 && c->p.angle < PI)
		{
			c->p.pos.x -= cos(c->p.angle - PI / 2) / TILE_SIZE;
			c->p.pos.y -= sin(c->p.angle - PI / 2) / TILE_SIZE;
		}
		else
		{
			c->p.pos.x += cos(c->p.angle + PI / 2) / TILE_SIZE;
			c->p.pos.y += sin(c->p.angle + PI / 2) / TILE_SIZE;
		}
	}
}

void	move_player(t_mlx *c, int keysym)
{
	double	x;
	double	y;
	int		floor_x;
	int		floor_y;

	x = c->p.pos.x;
	y = c->p.pos.y;
	if (keysym == MOVE_UP)
	{
		c->p.pos.y += (c->p.diry / TILE_SIZE) * 0.5;
		c->p.pos.x += (c->p.dirx / TILE_SIZE) * 0.5;
	}
	if (keysym == MOVE_DOWN)
	{
		c->p.pos.y -= c->p.diry / TILE_SIZE;
		c->p.pos.x -= c->p.dirx / TILE_SIZE;
	}
	strafe(c, keysym);
	floor_x = (int)floor(c->p.pos.x);
	floor_y = (int)floor(c->p.pos.y);
	if (c->map.map[floor_y][floor_x] == '1')
	{
		c->p.pos.x = x;
		c->p.pos.y = y;
	}
}

void draw_loop(t_mlx *c)
{
	t_coord p;
	t_coord d;

	p.x = (c->p.pos.x * TILE_SIZE);
	p.y = (c->p.pos.y * TILE_SIZE);
	d.x = p.x + c->p.dirx * 5;
	d.y = p.y + c->p.diry * 5;

	blackout(c);
	draw_bg(c);
	if (c->show_minimap)
	{
		draw_rays_2d(c);
		draw_map_2D(c);
		draw_player_2D(c);
		draw_line(c, p, d, GREEN);			// show players direction
	}
	else
		draw_rays_2d(c);
	mlx_put_image_to_window(c->mlx_ptr, c->win_ptr, c->frame.img, 0, 0);
}

void	player(t_mlx *cube, int keysym)
{
	if (keysym == MOVE_UP || keysym == MOVE_DOWN
		|| keysym == MOVE_LEFT || keysym == MOVE_RIGHT)
		move_player(cube, keysym);
	if (keysym == LOOK_LEFT)
		cube->p.angle -= 0.0174533 * 5;				// ONE DEGREE IN RADIANS * 5
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

