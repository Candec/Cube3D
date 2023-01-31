/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_coord.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibanez- <jibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 00:37:58 by jibanez-          #+#    #+#             */
/*   Updated: 2023/01/31 00:39:36 by jibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_coord	ft_init_coord(double x, double y)
{
	t_coord coord;

	coord.x = x;
	coord.y = y;
	return (coord);
}