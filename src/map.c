/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpereira <tpereira@42Lisboa.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 16:08:49 by tpereira          #+#    #+#             */
/*   Updated: 2023/03/08 14:16:08 by tpereira         ###   ########.fr       */
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

void	draw_map_2d(t_mlx *cube)
{
	int		x;
	int		y;
	t_coord	o;

	y = 0;
	while (y != (int)cube->map.height)
	{
		o.y = y * TILE_SIZE;
		x = 0;
		while (cube->map.map[y][x] != '\0' && x != (int)cube->map.width)
		{
			o.x = x * TILE_SIZE;
			draw_square(cube, o, TILE_SIZE, BLACK);
			if (cube->map.map[y][x] == '1')
				draw_square(cube, o, TILE_SIZE - 1, WHITE);
			else if (cube->map.map[y][x] == '0')
				draw_square(cube, o, TILE_SIZE - 1, BLUE);
			else if (ft_strchr("NSEW", cube->map.map[y][x]))
				draw_square(cube, o, TILE_SIZE - 1, BLUE);
			else
				draw_square(cube, o, TILE_SIZE - 1, GREEN);
			x++;
		}
		y++;
	}
}

void	draw_player_2d(t_mlx *cube)
{
	int		x;
	int		y;
	t_coord	o;

	y = -1;
	while (++y != (int)cube->map.height)
	{
		x = -1;
		o.y = (cube->p.pos.y - 1) * TILE_SIZE + TILE_SIZE;
		while (++x != (int)cube->map.width)
		{
			o.x = (cube->p.pos.x - 1) * TILE_SIZE + TILE_SIZE;
			if (cube->map.map[y][x] == '0')
				draw_square(cube, o, TILE_SIZE / 4, YELLOW);
		}
	}
}
