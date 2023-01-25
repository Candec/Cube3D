/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpereira <tpereira@42Lisboa.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 16:08:49 by tpereira          #+#    #+#             */
/*   Updated: 2023/01/25 08:32:43 by tpereira         ###   ########.fr       */
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
			else if (cube->map.map[y][x] == ' ')
				draw_square(cube, (xo), (yo), 30, GREEN);
			else if (cube->map.map[y][x] == '0')
				draw_square(cube, (xo), (yo), 30, BLUE);
			else if (cube->map.map[y][x] == 'N' || cube->map.map[y][x] == 'S' 
					|| cube->map.map[y][x] == 'E' || cube->map.map[y][x] == 'W')
			{
				draw_square(cube, (xo), (yo), 30, BLUE);
			}
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
		yo = cube->player.posy * 32;
		x = 0;
		while (x != (int)cube->map.width)
		{
			xo = cube->player.posx * 32;
			if (cube->map.map[y][x] != '1' && cube->map.map[y][x] != ' ')
				draw_square(cube, xo + 0.5, yo + 0.5, 8, YELLOW);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(cube->mlx_ptr, cube->win_ptr, cube->frame.img, 0, 0);
}