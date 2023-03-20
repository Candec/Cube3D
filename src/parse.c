/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibanez- <jibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 17:51:05 by jibanez-          #+#    #+#             */
/*   Updated: 2023/03/20 21:41:16 by jibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	info(t_mlx *cube, char *map)
{
	int		fd;
	int		ret;
	int		flag;
	char	*line;

	fd = open(map, O_RDONLY);
	if (fd == ERROR)
		error("CAN'T OPEN THE FILE", cube);
	ret = 1;
	flag = FALSE;
	while (ret > 0)
	{
		ret = ft_get_next_line(fd, &line);
		scan_file(cube, line);
		if (info_complete(cube))
		{
			if (ft_strchr(line, '1') && flag)
				scan_map(cube, line);
			flag = TRUE;
		}
		ft_free(line);
	}
	close(fd);
}

void	scan_file(t_mlx *cube, char *line)
{
	if (!ft_strncmp(line, "NO", 2))
	{
		cube->map.no = calloc(ft_strlen(line + 3), sizeof(char *));
		save_path(cube, cube->map.no, line + 3);
	}
	else if (!ft_strncmp(line, "SO", 2))
	{
		cube->map.so = calloc(ft_strlen(line + 3), sizeof(char *));
		save_path(cube, cube->map.so, line + 3);
	}
	else if (!ft_strncmp(line, "WE", 2))
	{
		cube->map.we = calloc(ft_strlen(line + 3), sizeof(char *));
		save_path(cube, cube->map.we, line + 3);
	}
	else if (!ft_strncmp(line, "EA", 2))
	{
		cube->map.ea = calloc(ft_strlen(line + 3), sizeof(char *));
		save_path(cube, cube->map.ea, line + 3);
	}
	else if (!ft_strncmp(line, "F", 1))
		ft_save_rgb(&cube->map.f_rgb, line + 2);
	else if (!ft_strncmp(line, "C", 1))
		ft_save_rgb(&cube->map.c_rgb, line + 2);
}

void	save_path(t_mlx *cube, char *dir, char *path)
{
	int	fd;

	if (!dir)
		error("MEMORY ALLOCATION ERROR", cube);
	fd = open(path, O_RDONLY);
	if (fd == -1)
		error("IMAGE(s) NOT FOUND", cube);
	ft_strncpy(dir, path, ft_strlen(path));
}

void	scan_map(t_mlx *cube, char *line)
{
	if (cube->map.width < ft_strlen(line))
		cube->map.width = ft_strlen(line);
	if (ft_add_str_to_arr(line, &cube->map.map))
		error("COULDN'T ALLOCATE MAP LINE", cube);
}

int	info_complete(t_mlx *cube)
{
	if (cube->map.no
		&& cube->map.so
		&& cube->map.we
		&& cube->map.ea
		&& cube->map.f_rgb.fill
		&& cube->map.c_rgb.fill)
	{
		cube->map.valid = TRUE;
		return (1);
	}
	return (0);
}
