/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibanez- <jibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 17:51:05 by jibanez-          #+#    #+#             */
/*   Updated: 2022/03/30 19:07:40 by jibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	ft_parse(t_mlx *cube, char *map)
{
	if (ft_file_format(map, ".cub"))
		ft_error("INCORRECT FILE FORMAT", cube);
	map_init(cube);
	map_info(cube, map);
}

void	map_init(t_mlx *cube)
{
	cube->map.height = -1;
	cube->map.width = -1;
}

void	map_info(t_mlx *cube, char *map)
{
	int		fd;
	int		ret;
	char	*line;

	fd = open(map, O_RDONLY);
	if (fd == ERROR)
		ft_error("CAN'T OPEN THE FILE\n", cube);
	ret = 1;
	while (ret > 0)
	{
		ret = ft_get_next_line(fd, &line);
		scan_file(cube, line);
		free(line);
		line = NULL;
	}
	cube->map.height++;
	close(fd);
}

void	scan_file(t_mlx *cube, char *line)
{
	if (!ft_strncmp(line, "NO", 2))
	{
		cube->map.NO = malloc(sizeof(char*) * ft_strlen(line + 2));
		save_path(cube, cube->map.NO, line + 2);
	}
	else if (!ft_strncmp(line, "SO", 2))
	{
		cube->map.SO = malloc(sizeof(char*) * ft_strlen(line + 2));
		save_path(cube, cube->map.SO, line + 2);
	}
	else if (!ft_strncmp(line, "WE", 2))
	{
		cube->map.WE = malloc(sizeof(char*) * ft_strlen(line + 2));
		save_path(cube, cube->map.WE, line + 2);
	}
	else if (!ft_strncmp(line, "EA", 2))
	{
		cube->map.EA = malloc(sizeof(char*) * ft_strlen(line + 2));
		save_path(cube, cube->map.EA, line + 2);
	}
}

void	save_path(t_mlx *cube, char *dir, char *path)
{
	if (!dir)
		ft_error("MEMORY ALLOCATION ERROR", cube);
	ft_strncpy(dir, path, ft_strlen(path));
}