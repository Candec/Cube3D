/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_save_rgb.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibanez- <jibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 00:42:36 by jibanez-          #+#    #+#             */
/*   Updated: 2023/01/27 01:13:39 by jibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_save_rgb(t_rgb *rgb, char *rgb_code)
{
	char	**rgb_decoded;

	rgb_decoded = ft_split(rgb_code, ',');
	if (rgb_decoded[0] && rgb_decoded[1] && rgb_decoded[2])
	{
		rgb->r = ft_atoi(rgb_decoded[0]);
		rgb->g = ft_atoi(rgb_decoded[1]);
		rgb->b = ft_atoi(rgb_decoded[2]);
	}
	if ((rgb->r < 0 || rgb->r > 255)
		|| (rgb->g < 0 || rgb->g > 255)
		|| (rgb->b < 0 || rgb->b > 255))
	{
		write(1, "RGB VALUES ARE INCORRECT, RESETING VALUES\n", 43);
		rgb->r = 42;
		rgb->g = 42;
		rgb->b = 42;
	}
	ft_clean_arr(rgb_decoded);
	rgb_decoded = NULL;
	rgb->int_rgb = ft_encode_rgb(rgb->r, rgb->g, rgb->b);
	rgb->fill = TRUE;
}
