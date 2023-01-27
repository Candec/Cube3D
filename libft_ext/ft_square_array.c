/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_square_array.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibanez- <jibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 22:08:14 by jibanez-          #+#    #+#             */
/*   Updated: 2023/01/27 01:26:17 by jibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_arr_width(char ***arr)
{
	size_t	w;
	size_t	i;
	size_t	temp_w;

	w = 0;
	i = 0;
	temp_w = 0;
	while (arr[0][i++])
	{
		temp_w = ft_strlen(arr[0][i]);
		if (temp_w > w)
			w = temp_w;
	}
	return (w);
}

size_t	ft_arr_height(char ***arr)
{
	size_t	h;
	size_t	i;

	h = 0;
	i = 0;
	while (arr[0][i++])
		h++;
	return (h);
}

char	*ft_charstr(char c, size_t size)
{
	size_t	i;
	char	*str;
	char	*tmp;
	char	*c_str;

	i = -1;
	c_str = ft_malloc(sizeof(char *) + 1);
	c_str[0] = c;
	c_str[1] = '\0';
	while (++i < size)
	{
		tmp = ft_strjoin(str, c_str);
		if (str && *str)
			free(str);
		str = tmp;
	}
	return (str);
}

void	ft_square_array(char ***arr, char c)
{
	size_t	w;
	size_t	s;
	size_t	i;
	char	*str;

	if (!arr)
		return ;
	w = ft_arr_width(arr);
	i = -1;
	while (arr[0][++i])
	{
		s = 0;
		s = ft_strlen(arr[0][i]);
		if (s < w)
		{
			str = ft_strjoin(arr[0][i], ft_charstr(c, w - s));
			free (arr[0][i]);
			arr[0][i] = str;
		}
	}
}
