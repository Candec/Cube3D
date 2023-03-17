/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_min_max.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpereira <tpereira@42Lisboa.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 17:52:22 by jibanez-          #+#    #+#             */
/*   Updated: 2023/03/17 10:23:09 by tpereira         ###   ########.fr       */
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
