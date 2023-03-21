/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpereira <tpereira@42Lisboa.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 17:51:05 by jibanez-          #+#    #+#             */
/*   Updated: 2023/03/21 23:07:47 by tpereira         ###   ########.fr       */
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
		printf("info -> line: %p\n", &line);
		ret = ft_get_next_line(fd, &line);
		printf("info -> line: %p\n", &line);
		scan_file(cube, line);
		if (info_complete(cube))
		{
			if (ft_strchr(line, '1') && flag)
				scan_map(cube, line);
			flag = TRUE;
		}
		ft_free(line);
		if (cube->map.line_f == TRUE)
			error("CATASTROFE", cube);
	}
	close(fd);
}

void	scan_file(t_mlx *cube, char *line)
{
	cube->map.line_f = FALSE;
	printf("scan -> line: %p\n", &line);
	if (!ft_strncmp(line, "NO", 2))
	{
		cube->map.no = ft_calloc(ft_strlen(line + 3), sizeof(char *));
		printf("if -> line: %p\n", &line);
		save_path(cube, cube->map.no, line);
	}
	else if (!ft_strncmp(line, "SO", 2))
	{
		cube->map.so = ft_calloc(ft_strlen(line + 3), sizeof(char *));
		save_path(cube, cube->map.so, line);
	}
	else if (!ft_strncmp(line, "WE", 2))
	{
		cube->map.we = ft_calloc(ft_strlen(line + 3), sizeof(char *));
		save_path(cube, cube->map.we, line);
	}
	else if (!ft_strncmp(line, "EA", 2))
	{
		cube->map.ea = ft_calloc(ft_strlen(line + 3), sizeof(char *));
		save_path(cube, cube->map.ea, line);
	}
	else if (!ft_strncmp(line, "F", 1))
		ft_save_rgb(&cube->map.f_rgb, line + 2);
	else if (!ft_strncmp(line, "C", 1))
		ft_save_rgb(&cube->map.c_rgb, line + 2);
}

void	save_path(t_mlx *cube, char *dir, char *path)
{
	int	fd;
	char *tmp;

	tmp = path + 3;
	fd = open(tmp, O_RDONLY);
	close(fd);
	if (fd == -1)
		cube->map.line_f = TRUE;
	ft_strncpy(dir, path + 3, ft_strlen(path + 3));
	if (!dir)
	{
		ft_free(path);
		error("MEMORY ALLOCATION ERROR", cube);
	}
}

void	scan_map(t_mlx *cube, char *line)
{
	if (cube->map.width < ft_strlen(line))
		cube->map.width = ft_strlen(line);
	if (ft_add_str_to_arr(line, cube))
	{
		ft_free(line);
		error("COULDN'T ALLOCATE MAP LINE", cube);
	}
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
