/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpereira <tpereira@42Lisboa.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 15:28:31 by tpereira          #+#    #+#             */
/*   Updated: 2023/03/21 22:46:34 by tpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_player_dir(t_mlx *cube, char c)
{
	if (c == 'N')
		cube->p.angle = PI3 + 0.00001;
	else if (c == 'S')
		cube->p.angle = PI2 + 0.00001;
	else if (c == 'E')
		cube->p.angle = PII + 0.00001;
	else if (c == 'W')
		cube->p.angle = PI + 0.00001;
	else
		cube->p.angle = PI3 + 0.00001;
	cube->p.dirx = cos(cube->p.angle) * 5;
	cube->p.diry = sin(cube->p.angle) * 5;
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
				cube->p.pos.x = j;
				cube->p.pos.y = i;
				cube->p.fov = 1;
				init_player_dir(cube, cube->map.map[i][j]);
				return ;
			}
		}
	}
}
