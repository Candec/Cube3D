/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibanez- <jibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 01:03:26 by jibanez-          #+#    #+#             */
/*   Updated: 2022/12/19 02:27:00 by jibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

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
			if (!ft_strchr("01NSEO ", cube->map.map[i][j]))
				error("INVALID CHARACTER\n", cube);
		}
	}
}

void	validate_map(t_mlx *cube)
{
	size_t	i;
	size_t	j;

	i = -1;
	while (cube->map.map[++i])
	{
		j = -1;
		while (cube->map.map[++j])
		{
			if (ft_strchr("0NSEO", cube->map.map[i][j]))
			{
				if (!check_h(cube, i, j))
					error("MAP NOT CLOSED H", cube);
				if (!check_v(cube, i, j))
					error("MAP NOT CLOSED V", cube);
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
		if (ft_strchr("1", cube->map.map[i][k]))
			right = TRUE;
	}
	k = j;
	while (cube->map.map[i][++k] && left == FALSE)
	{
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
		if (ft_strchr("1", cube->map.map[k][j]))
			up = TRUE;
	}
	k = i;
	while (cube->map.map[++k] && down == FALSE)
	{
		if (ft_strchr("1", cube->map.map[k][j]))
			down = TRUE;
	}
	return (up && down);
}
