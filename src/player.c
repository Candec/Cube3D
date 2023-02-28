/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpereira <tpereira@42Lisboa.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 15:28:31 by tpereira          #+#    #+#             */
/*   Updated: 2023/02/28 09:40:11 by tpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	init_player_dir(t_mlx *cube, char c)
{
	if (c == 'N')
		cube->player.angle = (3 * M_PI) / 2;
	else if (c == 'S')
		cube->player.angle = M_PI / 2;
	else if (c == 'E')
		cube->player.angle = 2 * M_PI;
	else if (c == 'W')
		cube->player.angle = M_PI;
	else
		cube->player.angle = M_PI;
	cube->player.dirx = cos(cube->player.angle); // times 0.5
	cube->player.diry = sin(cube->player.angle);
}

void	init_player(t_mlx *cube)
{
	int	i;
	int	j;

	i = -1;
	while (++i < (int)cube->map.height)
	{
		j = -1;
		while (++j < (int)cube->map.width)
		{
			if (ft_strchr("NSEW", cube->map.map[i][j]))
			{
				if (cube->map.map[i][j] == '\0')
					break ;
// <<<<<<< HEAD
// 				cube->player.posx = j + 0.4f;
// 				cube->player.posy = i + 0.4f;
// 				cube->player.angle = 1.5;
// 				cube->player.fov = 0.66;
// 				cube->player.dirx = cos(cube->player.angle) * 5;
// 				cube->player.diry = sin(cube->player.angle) * 5;
// =======
				//printf("c = %c\n\n", cube->map.map[i][j]);
				cube->player.pos.x = j + 0.4;
				cube->player.pos.y = i + 0.4;
				cube->player.angle = 1.5;
				cube->player.fov = 0.66;
				cube->player.dirx = cos(cube->player.angle); // times 0.5
				cube->player.diry = sin(cube->player.angle);
				init_player_dir(cube, cube->map.map[i][j]);
				return ;
			}
		}
	}
}
