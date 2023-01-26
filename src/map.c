/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpereira <tpereira@42Lisboa.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 16:08:49 by tpereira          #+#    #+#             */
/*   Updated: 2023/01/26 22:32:18 by tpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	print_map(t_mlx *cube)
{
	int	x;
	int	y;

	y = 0;
	while (y != (int)cube->map.height)
	{
		x = 0;
		while (cube->map.map[y][x] != '\0' && x != (int)cube->map.width)
		{
			printf("%c", cube->map.map[y][x]);
			x++;
		}
		printf("\n");
		y++;
	}
}

void	draw_map_2D(t_mlx *cube)
{
	int	x;
	int	y;
	int xo;
	int yo;

	y = 0;
	blackout(cube);
	print_map(cube);
	while (y != (int)cube->map.height)
	{
		yo = y * 32;
		x = 0;
		while (cube->map.map[y][x] != '\0' && x != (int)cube->map.width)
		{
			xo = x * 32;
			if (cube->map.map[y][x] == '1')
				draw_square(cube, (xo), (yo), 30, WHITE);
			else if (cube->map.map[y][x] == '0')
				draw_square(cube, (xo), (yo), 30, BLUE);
			else if (ft_strchr("NSEW", cube->map.map[y][x]))
				draw_square(cube, (xo), (yo), 30, BLUE);
			else
				draw_square(cube, (xo), (yo), 30, GREEN);
			x++;
		}
		y++;
	}
	draw_player_2D(cube);
}

void	draw_player_2D(t_mlx *cube)
{
	int	x;
	int	y;
	double xo;
	double yo;

	y = 0;
	while (y != (int)cube->map.height)
	{
		x = 0;
		yo = cube->player.posy * 32;
		while (x != (int)cube->map.width)
		{
			xo = cube->player.posx * 32;
			if (cube->map.map[y][x] == '0')
			{
				printf("x: %d, y: %d, cos(angle): %f, sin(angle): %f, angle: %f\n", x, y, cos(cube->player.angle), sin(cube->player.angle), cube->player.angle);
				draw_square(cube, xo, yo, 8, YELLOW);
				printf("dirx = %f, diry = %f\n", cube->player.dirx, cube->player.diry);
				//draw_square(cube, xo + 4 + cube->player.dirx * 3, yo + 4 + cube->player.diry * 3, 8, RED);
				draw_line(cube, xo + 4, yo + 4, xo + 4 + cube->player.dirx * 15, yo + 4 + cube->player.diry * 15, RED);
			}
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(cube->mlx_ptr, cube->win_ptr, cube->frame.img, 0, 0);
}
