/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibanez- <jibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 17:51:05 by jibanez-          #+#    #+#             */
/*   Updated: 2022/03/29 15:43:52 by jibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	ft_parse(t_mlx *cube, char *map)
{
	map_init(cube);
	map_size(cube, map);
}

void	map_init(t_mlx *cube)
{
	cube->map.height = -1;
	cube->map.width = -1;
}

void	map_size(t_mlx *cube, char *map)
{
	// int		n;
	int		fd;
	int		ret;
	char	*line;

	fd = open(map, O_RDONLY);
	// if (fd == ERROR)
	// 	handle_error(cube, "CAN'T OPEN THE FILE\n", FALSE);
	ret = 1;
	while (ret > 0)
	{
		ret = ft_get_next_line(fd, &line);
		printf("%s", line);
		// if (cube->map.height == -1)
		// 	cube->map.width = ft_strlen(line);
		// n = ft_strlen(line);
		// cube->map.height++;
		// if (cube->map.width != n)
		// 	handle_error(cube, "DIMENSION NOT CORRECT\n", FALSE);
		free(line);
		line = NULL;
	}
	cube->map.height++;
	close(fd);
}