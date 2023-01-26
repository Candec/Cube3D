/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibanez- <jibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 10:48:14 by jibanez-          #+#    #+#             */
/*   Updated: 2022/03/28 16:38:58 by jibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"


static char	*strjoin_gnl(char const *s1, char const *s2)
{
	char	*ret;
	size_t	size1;
	size_t	size2;

	if (!s2)
		return (NULL);
	if (!s1)
		size1 = 0;
	else
		size1 = ft_strlen(s1);
	size2 = ft_strlen(s2);
	if (!ft_set64((int64_t *)&ret, (int64_t)ft_malloc(size1 + size2 + 1)))
		return (NULL);
	ft_memcpy(ret, s1, size1);
	ft_memcpy(ret + size1, s2, size2 + 1);
	return (ret);
}

static char	*rem_line(char **saved)
{
	size_t	end;
	char	*ret;
	char	*temp;

	if (!*saved)
		return (ft_substr("", 0, 0));
	if (ft_strchr(*saved, '\n'))
		end = ft_strchr(*saved, '\n') - *saved;
	else
		end = (size_t) - 1;
	ret = ft_substr(*saved, 0, end);
	if (end != (size_t) - 1)
		temp = ft_substr(*saved, end + 1, (size_t) - 1);
	else
		temp = NULL;
	ft_free(*saved);
	*saved = temp;
	return (ret);
}

static int	get_line(int fd, char **saved, char **line)
{
	char	*buff;
	int64_t	aux;
	char	*temp;

	aux = 1;
	while ((!saved[fd] || !ft_strchr(saved[fd], '\n')) && aux)
	{
		buff = ft_malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (ft_set64((int64_t *)&aux, (int64_t)read(fd, buff, BUFFER_SIZE)) > 0)
		{
			buff[aux] = '\0';
			temp = strjoin_gnl(saved[fd], buff);
			ft_free(saved[fd]);
			saved[fd] = temp;
		}
		else if (aux == -1)
		{
			ft_free(buff);
			*line = NULL;
			return (-1);
		}
		ft_free(buff);
	}
	*line = rem_line(&(saved[fd]));
	return ((saved[fd] && ft_strlen(saved[fd]) != 0) || aux);
}

int	ft_get_next_line(int fd, char **line)
{
	static char	*saved[FD_MAX_COUNT];

	if (fd < 0 || fd == 1 || fd == 2 || fd >= FD_MAX_COUNT || !line)
		return (-1);
	return (get_line(fd, saved, line));
}