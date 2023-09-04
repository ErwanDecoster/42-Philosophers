/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edecoste <edecoste@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 11:04:29 by edecoste          #+#    #+#             */
/*   Updated: 2023/09/04 14:09:50 by edecoste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../philosophers.h"
#include "../include/philo.h"

void	release_forks(t_philo *philo, int fork)
{
	pthread_mutex_lock(&philo->data->m_forks[fork]);
	philo->data->forks_id[fork] = 0;
	pthread_mutex_unlock(&philo->data->m_forks[fork]);
}

int	think(t_philo *philo)
{
	long long	time;

	pthread_mutex_lock(&philo->data->m_pause);
	time = get_time() - philo->data->start_time;
	if (philo->data->death == 0)
		printf("%lld %d is thinking\n", time, philo->id);
	pthread_mutex_unlock(&philo->data->m_pause);
	return (1);
}

int	sleeping(t_philo *philo)
{
	long long	time;

	pthread_mutex_lock(&philo->data->m_pause);
	time = get_time() - philo->data->start_time;
	if (philo->data->death == 0)
		printf("%lld %d is sleeping\n", time, philo->id);
	pthread_mutex_unlock(&philo->data->m_pause);
	usleep(philo->data->tt_sleep * 1000);
	return (1);
}

int	eat(t_philo *philo)
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
		usleep(philo->data->tt_eat * 1000);
	}
	release_forks(philo, philo->l_fork);
	release_forks(philo, philo->r_fork);
	return (1);
}

void	action(t_philo *philo, t_data *data)
{
	while (philo->meals != data->eat_x_times)
	{
		think(philo);
		if (is_dead(philo) == 1)
			return ;
		eat(philo);
		if (philo->meals == data->eat_x_times)
			break ;
		sleeping(philo);
	}
	if (philo->meals == data->eat_x_times)
	{
		pthread_mutex_lock(&philo->data->m_pause);
		printf("Philo %d is done eating\n", philo->id);
		pthread_mutex_unlock(&philo->data->m_pause);
	}
}
