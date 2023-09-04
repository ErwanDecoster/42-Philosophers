/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edecoste <edecoste@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 14:32:10 by edecoste          #+#    #+#             */
/*   Updated: 2023/09/04 14:06:49 by edecoste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../philosophers.h"
#include "../include/philo.h"

int	ft_atoi(const char *str)
{
	size_t			i;
	int				sign;
	long long int	output;

	i = 0;
	output = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -sign;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (output != ((output * 10 + (sign * (str[i] - '0'))) / 10))
			return ((int)((sign + 1) / 2 / -1));
		output = output * 10 + ((str[i] - '0') * sign);
		i++;
	}
	return ((int)output);
}

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*str;
	size_t			i;

	str = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		str[i] = 0;
		i++;
	}
}

void	ft_usleep(long long waiting)
{
	long long	time;

	time = get_time();
	while ((get_time() - time) < waiting)
		usleep(100);
}
