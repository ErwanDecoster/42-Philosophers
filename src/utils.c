/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edecoste <edecoste@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 17:20:56 by edecoste          #+#    #+#             */
/*   Updated: 2023/08/30 13:24:25 by edecoste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

long long	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) != 0)
	{
		ft_putendl_fd(TIME_ERR, 1);
		return (-1);
	}
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	ft_usleep(long long waiting)
{
	long long	time;

	time = get_time();
	while ((get_time() - time) < waiting)
		usleep(100);
}

int	check_arg(int arc, char **arv)
{
	int	i;

	i = 1;
	while (i < arc)
	{
		if (ft_atoi(arv[i]) <= 0)
			return (0);
		i++;
	}
	return (1);
}
