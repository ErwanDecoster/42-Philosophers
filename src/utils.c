/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edecoste <edecoste@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 10:20:45 by edecoste          #+#    #+#             */
/*   Updated: 2023/09/04 14:07:40 by edecoste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../philosophers.h"
#include "../include/philo.h"

static int	check_fork(t_philo *philo, int fork)
{
	long long	time;

	pthread_mutex_lock(&philo->data->m_forks[fork]);
	if (philo->data->forks_id[fork] == 0)
	{
		philo->data->forks_id[fork] = 1;
		time = get_time() - philo->data->start_time;
		printf("%lld %d has taken a fork\n", time, philo->id);
		pthread_mutex_unlock(&philo->data->m_forks[fork]);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->m_forks[fork]);
	return (0);
}

int	get_forks(t_philo *philo)
{
	int	left;
	int	right;

	left = 0;
	right = 0;
	while (left == 0 || right == 0)
	{
		if (is_dead(philo) == 1)
			return (0);
		if (left == 0)
			left = check_fork(philo, philo->l_fork);
		if (right == 0)
			right = check_fork(philo, philo->r_fork);
		usleep(500);
	}
	return (1);
}

int	is_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->m_pause);
	if (philo->data->death == 1)
	{
		pthread_mutex_unlock(&philo->data->m_pause);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->m_pause);
	return (0);
}

long long	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) != 0)
	{
		error_display(TIME_ERR);
		return (-1);
	}
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	destroy_mutexes(t_data *data)
{
	int	i;

	i = 0;
	while (++i < data->nb_philos)
		pthread_mutex_destroy(&data->m_forks[i]);
	pthread_mutex_destroy(&data->m_pause);
}
