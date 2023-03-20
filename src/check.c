/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibanez- <jibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 01:03:26 by jibanez-          #+#    #+#             */
/*   Updated: 2023/03/20 22:36:18 by jibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_p(size_t i, size_t j, t_mlx *cube)
{
	if (cube->p.e != 1)
		error("WRONG NUM OF PLAYERS DETECTED\n", cube);
	cube->p.pos.x = (double)j;
	cube->p.pos.y = (double)i;
}

void	validate_chr(t_mlx *cube)
{
	size_t	i;
	size_t	j;

	i = -1;
	while (cube->map.map[++i])
	{
		j = -1;
		while (cube->map.map[++j])
		{
			if (!ft_strchr("01NSEW ", cube->map.map[i][j]))
				error("INVALID CHARACTER\n", cube);
		}
	}
	cube->map.height = i;
}

void	validate_map(t_mlx *cube)
{
	size_t	i;
	size_t	j;

	cube->p.e = 0;
	i = -1;
	while (cube->map.map[++i])
	{
		j = -1;
		while (cube->map.map[i][++j])
		{
			if (ft_strchr("0NSEW", cube->map.map[i][j]))
			{
				if (!check_h(cube, i, j))
					error("MAP NOT CLOSED", cube);
				if (!check_v(cube, i, j))
					error("MAP NOT CLOSED", cube);
			}
			if (ft_strchr("NSEW", cube->map.map[i][j]))
			{
				cube->p.e += 1;
				set_p(i, j, cube);
			}
		}
	}
}

bool	check_h(t_mlx *cube, size_t i, size_t j)
{
	bool	left;
	bool	right;
	size_t	k;

	left = FALSE;
	right = FALSE;
	k = j;
	while (cube->map.map[i][--k] && right == FALSE)
	{
		if (ft_strchr(".", cube->map.map[i][k]))
			error("MAP NOT CLOSED", cube);
		if (ft_strchr("1", cube->map.map[i][k]))
			right = TRUE;
	}
	k = j;
	while (cube->map.map[i][++k] && left == FALSE)
	{
		if (ft_strchr(".", cube->map.map[i][k]))
			error("MAP NOT CLOSED", cube);
		if (ft_strchr("1", cube->map.map[i][k]))
			left = TRUE;
	}
	return (right && left);
}

bool	check_v(t_mlx *cube, size_t i, size_t j)
{
	bool	up;
	bool	down;
	size_t	k;

	up = FALSE;
	down = FALSE;
	k = i;
	while (cube->map.map[--k] && up == FALSE)
	{
		if (ft_strchr(".", cube->map.map[k][j]))
			error("MAP NOT CLOSED", cube);
		if (ft_strchr("1", cube->map.map[k][j]))
			up = TRUE;
	}
	k = i;
	while (cube->map.map[++k] && down == FALSE)
	{
		if (ft_strchr(".", cube->map.map[k][j]))
			error("MAP NOT CLOSED", cube);
		if (ft_strchr("1", cube->map.map[k][j]))
			down = TRUE;
	}
	return (up && down);
}
