/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpereira <tpereira@42Lisboa.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 18:53:27 by tpereira          #+#    #+#             */
/*   Updated: 2023/03/21 21:52:48 by tpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_shortest_ray(t_raycast *ray)
{
	ray[0] = ray[2];
	ray[0].offset = (ray[2].pos.y - (int)ray[2].pos.y) * ray[2].tex.img_height;
	if (ray[1].dist < ray[2].dist)
	{
		ray[0] = ray[1];
		ray[0].offset = (ray[1].pos.x - (int)ray[1].pos.x)
			* ray[2].tex.img_width;
	}
}

static int	set_i(t_mlx *c)
{
	int	i;

	i = 0;
	if (!c->map.map)
		return (i);
	else
		while (c->map.map[++i])
			;
	return (i);
}

int	ft_add_str_to_arr(char *str, t_mlx *c)
{
	int		i;
	int		j;
	char	**new_arr;
	char	*n_str;

	i = -1;
	j = -1;
	n_str = ft_calloc((ft_strlen(str) + 1), sizeof(char));
	if (!n_str)
		return (1);
	ft_strcpy(n_str, str);
	i = set_i(c);
	new_arr = ft_calloc((i + 2), sizeof(char *));
	if (!new_arr)
		return (1);
	while (++j < i)
		new_arr[j] = ft_strdup(c->map.map[j]);
	new_arr[i] = n_str;
	new_arr[i + 1] = NULL;
	if (c->map.map)
		ft_clean_arr(c->map.map);
	c->map.map = new_arr;
	return (0);
}
