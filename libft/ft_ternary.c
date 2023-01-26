/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ternary.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibanez- <jibanez- <jibanez-@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 16:24:07 by jibanez-          #+#    #+#             */
/*   Updated: 2023/01/09 15:11:41 by jibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int64_t	ft_ternary64(int flag, int64_t a, int64_t b)
{
	if (flag)
		return (a);
	return (b);
}

double ft_ternary_double(int flag, double a, double b)
{
	if (flag)
		return (a);
	return (b);
}