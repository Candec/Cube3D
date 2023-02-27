/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpereira <tpereira@42Lisboa.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 14:27:33 by tpereira          #+#    #+#             */
/*   Updated: 2023/02/27 11:39:52 by tpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

float	deg_to_rad(float deg)
{
	return (deg * (M_PI / 180));
}

void	fix_angle(float *angle)
{
	if (*angle < 0)
		*angle += (2 * M_PI);
	else if (*angle >= 2 * M_PI)
		*angle -= (2 * M_PI);
}