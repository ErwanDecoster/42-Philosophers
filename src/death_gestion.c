/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_gestion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edecoste <edecoste@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 13:21:26 by edecoste          #+#    #+#             */
/*   Updated: 2023/08/30 13:21:56 by edecoste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	is_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->pause);
	if (philo->is_dead == 1)
		return (pthread_mutex_unlock(&philo->data->pause), 1);
	return (pthread_mutex_unlock(&philo->data->pause), 0);
}

int	check_death(t_philo *philo)
{
	long long	time;

	time = get_time() - philo->last_ate_time;
	if (philo->data->death_philo)
		return (0);
	if (time >= philo->data->tt_die && philo->data->death_philo == 0)
	{
		time = get_time() - philo->data->st_t;
		printf("%lld %d died\n", time, philo->id);
		philo->data->death_philo = 1;
		philo->is_dead = 1;
		return (0);
	}
	return (1);
}

static int	check_death_loop(t_data *data)
{
	int	i;

	while (1)
	{
		ft_usleep(3);
		i = -1;
		while (++i < data->nb_philos)
		{
			pthread_mutex_lock(&data->pause);
			if (data->philo->nb_ate == data->eat_x_times)
				return (pthread_mutex_unlock(&data->pause), 1);
			if (data->philo[i].last_ate_time != 0)
				if (!check_death(&data->philo[i]))
					return (pthread_mutex_unlock(&data->pause), 0);
			pthread_mutex_unlock(&data->pause);
		}
	}
}
