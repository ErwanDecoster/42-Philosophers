/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edecoste <edecoste@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 14:52:24 by edecoste          #+#    #+#             */
/*   Updated: 2023/08/30 14:55:47 by edecoste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (++i < n + 1)
		((char *) s)[i - 1] = '\0';
}

void	*ft_calloc(size_t count, size_t size)
{
	void		*res;

	if (size > 0 && count > SIZE_MAX / size)
		return (NULL);
	res = malloc(count * size);
	if (res)
	{
		ft_bzero(res, count * size);
		return (res);
	}
	return (NULL);
}

int	ft_putstr_fd(char *s, int fd)
{
	size_t	i;
	int		rt_val;

	i = 0;
	rt_val = 0;
	if (!s)
		i = ft_putstr_fd("(null)", fd);
	else
	{
		while (s[i])
			i++;
		rt_val = write(fd, s, i);
		if (rt_val == -1)
			return (rt_val);
	}
	return (i);
}

void	ft_putendl_fd(char *s, int fd)
{
	ft_putstr_fd(s, fd);
	write(fd, "\n", 1);
}
