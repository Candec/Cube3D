/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibanez- <jibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 17:51:05 by jibanez-          #+#    #+#             */
/*   Updated: 2022/04/06 13:11:34 by jibanez-         ###   ########.fr       */
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
	cube->map.height = 0;
	cube->map.width = 0;
	cube->map.C_rgb.r = -1;
	cube->map.C_rgb.g = -1;
	cube->map.C_rgb.b = -1;
	cube->map.C_rgb.fill = FALSE;
	cube->map.F_rgb.r = -1;
	cube->map.F_rgb.g = -1;
	cube->map.F_rgb.b = -1;
	cube->map.F_rgb.fill = FALSE;
	cube->map.map = ft_calloc(sizeof(char **), 0);
}

void	map_info(t_mlx *cube, char *map)
{
	int		fd;
	int		ret;
	int		flag;
	char	*line;

	fd = open(map, O_RDONLY);
	if (fd == ERROR)
		ft_error("CAN'T OPEN THE FILE\n", cube);
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
	print_arr(cube->map.map);
	close(fd);
}

void	scan_file(t_mlx *cube, char *line)
{
	if (!ft_strncmp(line, "NO", 2))
	{
		cube->map.NO = malloc(sizeof(char *) * ft_strlen(line + 3));
		save_path(cube, cube->map.NO, line + 3);
	}
	else if (!ft_strncmp(line, "SO", 2))
	{
		cube->map.SO = malloc(sizeof(char *) * ft_strlen(line + 3));
		save_path(cube, cube->map.SO, line + 3);
	}
	else if (!ft_strncmp(line, "WE", 2))
	{
		cube->map.WE = malloc(sizeof(char *) * ft_strlen(line + 3));
		save_path(cube, cube->map.WE, line + 3);
	}
	else if (!ft_strncmp(line, "EA", 2))
	{
		cube->map.EA = malloc(sizeof(char *) * ft_strlen(line + 3));
		save_path(cube, cube->map.EA, line + 3);
	}
	else if (!ft_strncmp(line, "F", 1))
		save_rgb(&cube->map.F_rgb, line + 2);
	else if (!ft_strncmp(line, "C", 1))
		save_rgb(&cube->map.C_rgb, line + 2);
}

void	save_path(t_mlx *cube, char *dir, char *path)
{
	if (!dir)
		ft_error("MEMORY ALLOCATION ERROR", cube);
	ft_strncpy(dir, path, ft_strlen(path));
}

void	save_rgb(t_rgb *rgb, char *rgb_code)
{
	char	**rgb_decoded;

	rgb_decoded = ft_split(rgb_code, ',');
	rgb->r = ft_atoi(rgb_decoded[0]);
	rgb->g = ft_atoi(rgb_decoded[1]);
	rgb->b = ft_atoi(rgb_decoded[2]);

	if ((rgb->r < 0 || rgb->r > 255)
		|| (rgb->g < 0 || rgb->g > 255)
		|| (rgb->b < 0 || rgb->b > 255))
	{
		write(1, "RGB VALUES ARE INCORRECT, RESETING VALUES\n", 43);
		rgb->r = 42;
		rgb->g = 42;
		rgb->b = 42;
	}
	rgb->fill = TRUE;
}

void	scan_map(t_mlx *cube, char *line)
{
	if (cube->map.width < ft_strlen(line))
		cube->map.width = ft_strlen(line);
	if (!ft_add_str_to_arr(cube->map.map, line))
		ft_error("COULDN'T ALLOCATE MAP LINE", cube);
}

int	ft_char_is_valid(char c)
{
	if (c == '0' || c == '1' || c == SPC || c == '\n'
		|| c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (0);
	return (1);
}

int	ft_frmtrx(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	while (--i + 1)
		free(str[i]);
	free(str);
	return (0);
}

char	**ft_arr_strdup(char **from, char **to)
{
	int	i;

	i = 0;
	while (from && from[i])
	{
		to[i] = ft_strdup(from[i]);
		if (!to[i])
		{
			ft_clean_arr(to);
			free(to);
			return (NULL);
		}
		i++;
	}
	return (to);
}

char	**ft_add_str_to_arr(char **arr, char *str)
{
	char	**tmp;
	int		i;

	i = 0;
	while (arr && arr[i])
		i++;
	if (str)
		i++;
	tmp = malloc(sizeof(char *) * (i + 1));
	if (!tmp)
		return (NULL);
	tmp[i] = NULL;
	if (str)
	{
		tmp[i - 1] = ft_strdup(str);
		if (!tmp[i - 1])
		{
			free(tmp);
			return (NULL);
		}
	}
	return (ft_arr_strdup(arr, tmp));
}

void	ft_clean_arr(char **arr)
{
	int	i;

	i = 0;
	if (arr != NULL)
	{
		while (arr[i] != NULL)
			free(arr[i++]);
	}
	free(arr);
	arr = NULL;
}

int	info_complete(t_mlx *cube)
{
	if (!cube->map.NO || !cube->map.SO || !cube->map.WE || !cube->map.EA)
		return (1);
	if (cube->map.F_rgb.fill && cube->map.C_rgb.fill)
		return (1);
	return (0);
}

void	print_arr(char **arr)
{
	size_t	i;

	i = 0;
	
	while (arr[i])
	{
		printf("%s\n", arr[i]);
		i++;
	}
}