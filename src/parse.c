/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibanez- <jibanez- <jibanez-@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 17:51:05 by jibanez-          #+#    #+#             */
/*   Updated: 2023/01/09 15:38:13 by jibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	info(t_mlx *cube, char *map)
{
	int		fd;
	int		ret;
	int		flag;
	char	*line;

	fd = open(map, O_RDONLY);
	if (fd == ERROR)
		error("CAN'T OPEN THE FILE\n", cube);
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
		free(line);
		line = NULL;
	}
	close(fd);
}

void	scan_file(t_mlx *cube, char *line)
{
	if (!ft_strncmp(line, "NO", 2))
	{
		cube->map.no = malloc(sizeof(char *) * ft_strlen(line + 3));
		save_path(cube, cube->map.no, line + 3);
	}
	else if (!ft_strncmp(line, "SO", 2))
	{
		cube->map.so = malloc(sizeof(char *) * ft_strlen(line + 3));
		save_path(cube, cube->map.so, line + 3);
	}
	else if (!ft_strncmp(line, "WE", 2))
	{
		cube->map.we = malloc(sizeof(char *) * ft_strlen(line + 3));
		save_path(cube, cube->map.so, line + 3);
	}
	else if (!ft_strncmp(line, "EA", 2))
	{
		cube->map.ea = malloc(sizeof(char *) * ft_strlen(line + 3));
		save_path(cube, cube->map.ea, line + 3);
	}
	else if (!ft_strncmp(line, "F", 1))
		ft_save_rgb(&cube->map.f_rgb, line + 2);
	else if (!ft_strncmp(line, "C", 1))
		ft_save_rgb(&cube->map.c_rgb, line + 2);
}

void	save_path(t_mlx *cube, char *dir, char *path)
{
	if (!dir)
		error("MEMORY ALLOCATION ERROR\n", cube);
	ft_strncpy(dir, path, ft_strlen(path));
}

void	scan_map(t_mlx *cube, char *line)
{
	if (cube->map.width < ft_strlen(line))
		cube->map.width = ft_strlen(line);
	if (ft_add_str_to_arr(line, &cube->map.map))
		error("COULDN'T ALLOCATE MAP LINE\n", cube);
}

int	info_complete(t_mlx *cube)
{
	if (cube->map.no
		&& cube->map.so
		&& cube->map.we
		&& cube->map.ea
		&& cube->map.f_rgb.fill
		&& cube->map.c_rgb.fill)
		return (1);
	return (0);
}
