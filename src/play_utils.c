/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpereira <tpereira@42Lisboa.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 14:27:04 by tpereira          #+#    #+#             */
/*   Updated: 2023/03/08 14:40:26 by tpereira         ###   ########.fr       */
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

void	strafe_left(t_mlx *c, int keysym)
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
}

void	strafe_right(t_mlx *c, int keysym)
{
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
	t_coord	tmp;
	int		floor_x;
	int		floor_y;

	tmp.x = c->p.pos.x;
	tmp.y = c->p.pos.y;
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
	strafe_left(c, keysym);
	strafe_right(c, keysym);
	floor_x = (int)floor(c->p.pos.x);
	floor_y = (int)floor(c->p.pos.y);
	if (c->map.map[floor_y][floor_x] == '1')
	{
		c->p.pos.x = tmp.x;
		c->p.pos.y = tmp.y;
	}
}