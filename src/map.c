/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpereira <tpereira@42Lisboa.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 16:08:49 by tpereira          #+#    #+#             */
/*   Updated: 2023/03/14 18:18:18 by tpereira         ###   ########.fr       */
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
		o.y = y * (TILE_SIZE / 2);
		x = 0;
		while (cube->map.map[y][x] != '\0' && x != (int)cube->map.width)
		{
			o.x = x * (TILE_SIZE / 2);
			draw_square(cube, o, (TILE_SIZE / 2), BLACK);
			if (cube->map.map[y][x] == '1')
				draw_square(cube, o, (TILE_SIZE / 2) - 1, WHITE);
			else if (cube->map.map[y][x] == '0')
				draw_square(cube, o, (TILE_SIZE / 2) - 1, BLUE);
			else if (ft_strchr("NSEW", cube->map.map[y][x]))
				draw_square(cube, o, (TILE_SIZE / 2) - 1, BLUE);
			else
				draw_square(cube, o, (TILE_SIZE / 2) - 1, GREEN);
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
		o.y = (cube->p.pos.y - 1) * (TILE_SIZE / 2) + (TILE_SIZE / 2);
		while (++x != (int)cube->map.width)
		{
			o.x = (cube->p.pos.x - 1) * (TILE_SIZE / 2) + (TILE_SIZE / 2);
			if (cube->map.map[y][x] == '0')
				draw_square(cube, o, (TILE_SIZE / 2) / 8, YELLOW);
		}
	}
}
