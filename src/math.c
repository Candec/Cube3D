/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpereira <tpereira@42Lisboa.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 14:27:33 by tpereira          #+#    #+#             */
/*   Updated: 2023/03/01 14:07:47 by tpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

float	deg_to_rad(float deg)
{
	return (deg * (PI / 180));
}

void	fix_angle(float *angle)
{
	if (*angle < 0)
		*angle += ((PII));
	else if (*angle >= (PII))
		*angle -= ((PII));
}