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

void	info(t_mlx *c, char *map)
{
	int		fd;
	int		ret;
	int		flag;

	fd = open(map, O_RDONLY);
	if (fd == ERROR)
		error("CAN'T OPEN THE FILE", c);
	ret = 1;
	flag = FALSE;
	while (ret > 0)
	{
		ret = ft_get_next_line(fd, &c->line);
		scan_file(c);
		if (info_complete(c))
		{
			if (ft_strchr(c->line, '1') && flag)
				scan_map(c, c->line);
			flag = TRUE;
		}
		ft_free(c->line);
	}
	close(fd);
}

void	scan_file(t_mlx *c)
{
	if (!ft_strncmp(c->line, "NO", 2))
	{
		c->map.no = ft_calloc(ft_strlen(c->line + 3), sizeof(char *));
		save_path(c, c->map.no);
	}
	else if (!ft_strncmp(c->line, "SO", 2))
	{
		c->map.so = ft_calloc(ft_strlen(c->line + 3), sizeof(char *));
		save_path(c, c->map.so);
	}
	else if (!ft_strncmp(c->line, "WE", 2))
	{
		c->map.we = ft_calloc(ft_strlen(c->line + 3), sizeof(char *));
		save_path(c, c->map.we);
	}
	else if (!ft_strncmp(c->line, "EA", 2))
	{
		c->map.ea = ft_calloc(ft_strlen(c->line + 3), sizeof(char *));
		save_path(c, c->map.ea);
	}
	else if (!ft_strncmp(c->line, "F", 1))
		ft_save_rgb(&c->map.f_rgb, c->line + 2);
	else if (!ft_strncmp(c->line, "C", 1))
		ft_save_rgb(&c->map.c_rgb, c->line + 2);
}

void	save_path(t_mlx *c, char *dir)
{
	int		fd;
	char	*tmp;

	tmp = c->line + 3;
	fd = open(tmp, O_RDONLY);
	close(fd);
	if (fd == -1)
		c->map.line_f = TRUE;
	else
		ft_strncpy(dir, tmp, ft_strlen(tmp));
	if (!dir)
		error("MEMORY ALLOCATION ERROR", c);
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
