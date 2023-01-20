/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpereira <tpereira@42Lisboa.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 16:24:26 by tpereira          #+#    #+#             */
/*   Updated: 2023/01/20 16:27:28 by tpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	my_mlx_pixel_put(t_mlx *game, int x, int y, int color)
{
	char	*dst;

	if (x < game->width && y < game->height && x > 0 && y > 0)
	{
		dst = game->img.addr + (y * game->img.line_length + x
				* (game->img.bpp / 8));
		*(unsigned int *)dst = color;
	}
}

void	set_iso(t_info *info, t_fdf *data)
{
	if (data->iso)
	{
		isometric(&info->x, &info->y, info->z, data);
		isometric(&info->x1, &info->y1, info->z1, data);
	}
}

void	set_pos(t_info *info, t_fdf *data)
{
	info->x += data->pos_x;
	info->y += data->pos_y;
	info->x1 += data->pos_x;
	info->y1 += data->pos_y;
}

void	bresenham(int coord[], float x1, float y1, t_mlx *game)
{
	t_info	info;

	info.x = coord[0];
	info.y = coord[1];
	info.z = game->z_matrix[(int)info.y][(int)info.x] * game->elevation;
	info.z1 = game->z_matrix[(int)y1][(int)x1] * game->elevation;
	info.x *= game->zoom;
	info.y *= game->zoom;
	info.x1 = x1 * game->zoom;
	info.y1 = y1 * game->zoom;
	game->color = set_color(info);
	set_iso(&info, game);
	set_pos(&info, game);
	set_step(&info);
	while ((int)(info.x - info.x1) || (int)(info.y - info.y1))
	{
		my_mlx_pixel_put(game, info.x, info.y + 1, game->color);
		info.x += info.x_step;
		info.y += info.y_step;
	}
}

void	draw(t_mlx *game)
{
	int	x;
	int	y;
	int	coord[2];

	//blackout(game);
	y = 0;
	while (y < game->height)
	{
		x = 0;
		while (x < game->width)
		{
			coord[1] = y;
			coord[0] = x;
			if (y < game->height - 1)
				bresenham(coord, x, y + 1, game);
			if (x < game->width - 1)
				bresenham(coord, x + 1, y, game);
			else
				break ;
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.ptr, 0, 0);
}