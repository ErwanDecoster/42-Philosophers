/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edecoste <edecoste@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 13:17:19 by edecoste          #+#    #+#             */
/*   Updated: 2023/08/31 14:21:17 by edecoste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	sleeping(t_philo *philo)
{
	long long	actual_time;

	actual_time = get_time() - philo->data->st_t;
	if (philo->data->death_philo == 0)
	{
		printf("%lld %d is sleeping\n", actual_time, philo->id);
		usleep(philo->data->tt_sleep * 1000);
	}
	return (1);
}

int	think(t_philo *philo)
{
	long long	actual_time;

	pthread_mutex_lock(&philo->data->m_pause);
	actual_time = get_time() - philo->data->st_t;
	if (philo->data->death_philo == 0)
		printf("%lld %d is thinking\n", actual_time, philo->id);
	pthread_mutex_unlock(&philo->data->m_pause);
	return (1);
}

int	eat(t_philo *philo)
{
	long long	time;

	get_forks(philo);
	if (is_death(philo) == 0)
	{
		pthread_mutex_lock(&philo->data->m_pause);
		time = get_time();
		if (philo->data->death_philo == 0)
			printf("%lld %d is eating\n", time - philo->data->st_t, philo->id);
		philo->last_ate_time = time;
		philo->nb_ate++;
		pthread_mutex_unlock(&philo->data->m_pause);
		usleep(philo->data->tt_eat * 1000);
	}
	release_fork(philo, philo->l_fork_id);
	release_fork(philo, philo->r_fork_id);
	return (1);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->data->m_pause);
	philo->last_ate_time = get_time();
	pthread_mutex_unlock(&philo->data->m_pause);
	if (philo->id % 2)
		usleep(200);
	while (philo->data->eat_x_times == -1 || \
		philo->nb_ate < philo->data->eat_x_times)
	{
		think(philo);
		if (is_death(philo))
			return (NULL);
		if (philo->data->death_philo)
			return (NULL);
		eat(philo);
		sleeping(philo);
	}
	return (NULL);
}
