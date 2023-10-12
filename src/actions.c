/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edecoste <edecoste@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 11:04:29 by edecoste          #+#    #+#             */
/*   Updated: 2023/10/12 15:45:36 by edecoste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	release_fork(t_philo *philo, int fork)
{
	pthread_mutex_lock(&philo->data->m_forks[fork]);
	philo->data->forks_id[fork] = 0;
	pthread_mutex_unlock(&philo->data->m_forks[fork]);
}

static int	think(t_philo *philo)
{
	long long	time;

	pthread_mutex_lock(&philo->data->m_pause);
	time = get_time() - philo->data->start_time;
	if (philo->data->death == 0)
		printf("%lld %d is thinking\n", time, philo->id);
	pthread_mutex_unlock(&philo->data->m_pause);
	return (1);
}

static int	sleeping(t_philo *philo)
{
	long long	time;

	pthread_mutex_lock(&philo->data->m_pause);
	time = get_time() - philo->data->start_time;
	if (philo->data->death == 0)
		printf("%lld %d is sleeping\n", time, philo->id);
	pthread_mutex_unlock(&philo->data->m_pause);
	ft_usleep(philo->data->tt_sleep, philo);
	return (1);
}

static int	eat(t_philo *philo)
{
	long long	time;

	get_forks(philo);
	if (is_dead(philo) == 0)
	{
		pthread_mutex_lock(&philo->data->m_pause);
		time = get_time() - philo->data->start_time;
		printf("%lld %d is eating\n", time, philo->id);
		philo->last_meal_time = get_time();
		philo->meals++;
		pthread_mutex_unlock(&philo->data->m_pause);
		ft_usleep(philo->data->tt_eat, philo);
	}
	release_fork(philo, philo->l_fork_id);
	release_fork(philo, philo->r_fork_id);
	return (1);
}

void	*philo_routine(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->data->m_pause);
	philo->last_meal_time = get_time();
	pthread_mutex_unlock(&philo->data->m_pause);
	if (philo->id % 2 != 0)
		usleep(20000);
	while (philo->meals != philo->data->eat_x_times)
	{
		think(philo);
		if (is_dead(philo) == 1)
			return (NULL);
		eat(philo);
		if (philo->meals == philo->data->eat_x_times)
			break ;
		sleeping(philo);
	}
	if (philo->meals == philo->data->eat_x_times)
	{
		pthread_mutex_lock(&philo->data->m_pause);
		printf("Philo %d is done eating\n", philo->id);
		pthread_mutex_unlock(&philo->data->m_pause);
	}
	return (NULL);
}
