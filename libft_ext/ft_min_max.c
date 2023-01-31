/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_min.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibanez- <jibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 17:52:22 by jibanez-          #+#    #+#             */
/*   Updated: 2023/01/30 17:55:18 by jibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_double_min(double a, double b)
{
	return (ft_ternary_double(a < b, a, b));
}

double	ft_double_max(double a, double b)
{
	return (ft_ternary_double(a > b, a, b));
}