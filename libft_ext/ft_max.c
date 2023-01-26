/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_max.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibanez- <jibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 16:40:25 by jibanez-          #+#    #+#             */
/*   Updated: 2022/03/28 16:40:26 by jibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_max(int args, ...)
{
	int			i;
	int			max_value;
	int			current;
	va_list		valist;

	va_start(valist, args);
	i = -1;
	max_value = INT_MAX;
	while (++i < args)
	{
		current = va_arg(valist, int);
		if (max_value < current || max_value == INT_MAX)
			max_value = current;
	}
	va_end(valist);
	return (max_value);
}
