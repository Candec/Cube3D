/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpereira <tpereira@42Lisboa.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 16:08:49 by tpereira          #+#    #+#             */
/*   Updated: 2023/01/20 17:37:09 by tpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	print_map(t_mlx *cube)
{
	int	x;
	int	y;

	y = 0;
	while (y != (int)cube->map.width)
	{
		x = 0;
		while (x != (int)cube->map.height)
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
	print_map(cube);
	while (y != (int)cube->map.width)
	{
		x = 0;
		while (x != (int)cube->map.height)
		{
			if (cube->map.map[y][x] == '1')
				draw_square(cube, x * 32, y * 32, 32, WHITE);
			else if (cube->map.map[y][x] == '0')
				draw_square(cube, x * 32, y * 32, 32, BLACK);
			else if (cube->map.map[y][x] == 'N' || cube->map.map[y][x] == 'S' 
				|| cube->map.map[y][x] == 'E' || cube->map.map[y][x] == 'W')
			{
				printf("Player\n");
				draw_square(cube, x * 32, y * 32, 32, YELLOW);
			}
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(cube->mlx_ptr, cube->win_ptr, cube->frame.img, 0, 0);
}