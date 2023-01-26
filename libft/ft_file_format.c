/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_file_format.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibanez- <jibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 16:02:29 by jibanez-          #+#    #+#             */
/*   Updated: 2022/03/30 16:22:36 by jibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_file_format(char *file, char *file_format)
{
	char *dot;

	dot = ft_strrchr(file, '.');
	if (dot != NULL && !ft_strcmp(dot, file_format))
		return (0);
	return (1);
}