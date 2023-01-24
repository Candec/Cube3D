/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpereira <tpereira@42Lisboa.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 16:08:49 by tpereira          #+#    #+#             */
/*   Updated: 2023/01/24 13:20:37 by tpereira         ###   ########.fr       */
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

	y = 0;
	blackout(cube);
	print_map(cube);
	while (y != (int)cube->map.height)
	{
		x = 0;
		while (cube->map.map[y][x] != '\0' && x != (int)cube->map.width)
		{
			if (cube->map.map[y][x] == '1')
				draw_square(cube, x * 32, y * 32, 32, WHITE);
			else if (cube->map.map[y][x] == ' ')
				draw_square(cube, x * 32, y * 32, 32, GREEN);
			else if (cube->map.map[y][x] == '0')
				draw_square(cube, x * 32, y * 32, 32, BLUE);
			else if (cube->map.map[y][x] == 'N' || cube->map.map[y][x] == 'S' 
				|| cube->map.map[y][x] == 'E' || cube->map.map[y][x] == 'W')
			{
				cube->player.posx = x;
				cube->player.posy = y;
				//draw_square(cube, x * 32, y * 32, 32, YELLOW);
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

	y = 0;
	//blackout(cube);
	while (y != (int)cube->map.height)
	{
		x = 0;
		while (x != (int)cube->map.width)
		{
			if (cube->map.map[y][x] != '1' && cube->map.map[y][x] != ' ')
			{
				if (cube->player.posx == x && cube->player.posy == y)
					draw_square(cube, (x * 32) + 12, (y * 32) + 12, 8, YELLOW);
			}
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(cube->mlx_ptr, cube->win_ptr, cube->frame.img, 0, 0);
}