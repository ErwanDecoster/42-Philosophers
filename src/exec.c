/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edecoste <edecoste@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 13:15:53 by edecoste          #+#    #+#             */
/*   Updated: 2023/09/04 14:06:49 by edecoste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../philosophers.h"
#include "../include/philo.h"

static int	check_death(t_philo *philo)
{
	long long	time;

	time = get_time() - philo->last_meal_time;
	if (philo->data->death == 1)
		return (0);
	if (time >= philo->data->tt_die && philo->data->death == 0)
	{
		printf("%lld %d died\n", (get_time() - philo->data->start_time), philo->id);
		philo->data->death = 1;
		philo->dead = 1;
		return (0);
	}
	return (1);
}

static int	death_check_loop(t_data *data)
{
	int	i;

	while (1)
	{
		ft_usleep(3);
		i = -1;
		while (++i < data->nb_philos)
		{
			pthread_mutex_lock(&data->m_pause);
			if (data->philo->meals == data->eat_x_times)
			{
				pthread_mutex_unlock(&data->m_pause);
				return (1);
			}
			if (data->philo[i].last_meal_time != 0)
			{
				if (!check_death(&data->philo[i]))
				{
					pthread_mutex_unlock(&data->m_pause);
					return (0);
				}
			}
			pthread_mutex_unlock(&data->m_pause);
		}
	}
}

int	threads_init(t_data *data)
{
	int	i;

	i = -1;
	pthread_mutex_lock(&data->m_pause);
	while (++i < data->nb_philos)
	{
		if (pthread_create(&data->philo[i].thread, NULL, philo_routine, \
			&data->philo[i]) != 0)
			return (free(data->philo), error_display(TRHREAD_CR), \
					pthread_mutex_unlock(&data->m_pause), 0);
	}
	data->start_time = get_time();
	pthread_mutex_unlock(&data->m_pause);
	i = -1;
	death_check_loop(data);
	while (++i < data->nb_philos)
	{
		if (pthread_join(data->philo[i].thread, NULL) != 0)
			return (free(data->philo), error_display(THR_JOIN), 0);
	}
	return (1);
}

void	*philo_routine(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->data->m_pause);
	pthread_mutex_unlock(&philo->data->m_pause);
	pthread_mutex_lock(&philo->data->m_pause);
	philo->last_meal_time = get_time();
	pthread_mutex_unlock(&philo->data->m_pause);
	if (philo->id % 2 != 0)
		usleep(20000);
	action(philo, philo->data);
	return (NULL);
}
