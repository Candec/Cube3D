/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpereira <tpereira@42Lisboa.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 16:09:33 by jibanez-          #+#    #+#             */
/*   Updated: 2023/03/21 22:55:44 by tpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	error(char *msg, t_mlx *cube)
{
	printf("Error\n%s\n", msg);
	quit(cube);
}

void	unload(t_mlx *cube)
{
	if (cube->img_no.img)
		mlx_destroy_image(cube->mlx_ptr, &cube->img_no);
	if (cube->img_so.img)
		mlx_destroy_image(cube->mlx_ptr, &cube->img_so);
	if (cube->img_ea.img)
		mlx_destroy_image(cube->mlx_ptr, &cube->img_ea);
	if (cube->img_we.img)
		mlx_destroy_image(cube->mlx_ptr, &cube->img_we);
}

int	quit(t_mlx *cube)
{
	ft_clean_arr(cube->map.map);
	if (cube->map.no)
		ft_free(cube->map.no);
	if (cube->map.so)
		ft_free(cube->map.so);
	if (cube->map.ea)
		ft_free(cube->map.ea);
	if (cube->map.we)
		ft_free(cube->map.we);
	if (cube->win)
	{
		mlx_clear_window(cube->mlx_ptr, cube->win_ptr);
		mlx_destroy_window(cube->mlx_ptr, cube->win_ptr);
	}
	exit(EXIT_FAILURE);
	return (TRUE);
}

int	leave(t_mlx *cube)
{
	ft_clean_arr(cube->map.map);
	ft_free(cube->map.no);
	ft_free(cube->map.so);
	ft_free(cube->map.ea);
	ft_free(cube->map.we);
	if (cube->win)
	{
		mlx_clear_window(cube->mlx_ptr, cube->win_ptr);
		mlx_destroy_window(cube->mlx_ptr, cube->win_ptr);
	}
	exit(EXIT_SUCCESS);
	return (TRUE);
}
