/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpereira <tpereira@42Lisboa.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 17:51:05 by jibanez-          #+#    #+#             */
/*   Updated: 2023/03/21 23:32:03 by tpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	info(t_mlx *cube, char *map)
{
	int		fd;
	int		ret;
	int		flag;

	fd = open(map, O_RDONLY);
	if (fd == ERROR)
		error("CAN'T OPEN THE FILE", cube);
	ret = 1;
	flag = FALSE;
	while (ret > 0)
	{
		ret = ft_get_next_line(fd, &cube->line);
		scan_file(cube);
		if (info_complete(cube))
		{
			if (ft_strchr(cube->line, '1') && flag)
				scan_map(cube, cube->line);
			flag = TRUE;
		}
		ft_free(cube->line);
		if (cube->map.line_f == TRUE)
			error("CATASTROFE", cube);
	}
	close(fd);
}

void	scan_file(t_mlx *cube)
{
	cube->map.line_f = FALSE;
	if (!ft_strncmp(cube->line, "NO", 2))
	{
		cube->map.no = ft_calloc(ft_strlen(cube->line + 3), sizeof(char *));
		save_path(cube, 1);
	}
	else if (!ft_strncmp(cube->line, "SO", 2))
	{
		cube->map.so = ft_calloc(ft_strlen(cube->line + 3), sizeof(char *));
		save_path(cube, 2);
	}
	else if (!ft_strncmp(cube->line, "WE", 2))
	{
		cube->map.we = ft_calloc(ft_strlen(cube->line + 3), sizeof(char *));
		save_path(cube, 3);
	}
	else if (!ft_strncmp(cube->line, "EA", 2))
	{
		cube->map.ea = ft_calloc(ft_strlen(cube->line + 3), sizeof(char *));
		save_path(cube, 4);
	}
	else if (!ft_strncmp(cube->line, "F", 1))
		ft_save_rgb(&cube->map.f_rgb, cube->line + 2);
	else if (!ft_strncmp(cube->line, "C", 1))
		ft_save_rgb(&cube->map.c_rgb, cube->line + 2);
}

void	save_path(t_mlx *cube, int i)
{
	int		fd;
	char	*dir;

	if (i == 1)
		dir = cube->map.no;
	if (i == 2)
		dir = cube->map.so;
	if (i == 3)
		dir = cube->map.ea;
	if (i == 4)
		dir = cube->map.we;
	fd = open(cube->line + 3, O_RDONLY);
	if (fd == -1)
		cube->map.line_f = TRUE;
	close(fd);
	ft_strncpy(dir, cube->line + 3, ft_strlen(cube->line + 3));
	if (!dir)
	{
		ft_free(cube->line);
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
