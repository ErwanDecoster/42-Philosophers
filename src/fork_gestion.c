/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_gestion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edecoste <edecoste@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 13:18:45 by edecoste          #+#    #+#             */
/*   Updated: 2023/08/30 13:21:58 by edecoste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	release_fork(t_philo *philo, int fork_id)
{
	pthread_mutex_lock(&philo->data->m_forks[fork_id - 1]);
	philo->data->forks[fork_id - 1] = 0;
	pthread_mutex_unlock(&philo->data->m_forks[fork_id - 1]);
	return (0);
}

int	get_fork(t_philo *philo, int fork_id)
{
	long long	actual_time;

	pthread_mutex_lock(&philo->data->m_forks[fork_id - 1]);
	actual_time = get_time() - philo->data->st_t;
	if (philo->data->forks[fork_id - 1] == 0)
	{
		philo->data->forks[fork_id - 1] = 1;
		if (philo->data->death_philo == 0)
			printf("%lld %d has taken a fork\n", actual_time, philo->id);
		pthread_mutex_unlock(&philo->data->m_forks[fork_id - 1]);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->m_forks[fork_id - 1]);
	return (0);
}

int	get_forks(t_philo *philo)
{
	int	have_l_fork;
	int	have_r_fork;

	have_l_fork = 0;
	have_r_fork = 0;
	while (!have_l_fork || !have_r_fork)
	{
		if (is_death(philo))
			return (0);
		if (!have_l_fork)
			have_l_fork = get_fork(philo, philo->l_fork_id);
		if (is_death(philo))
			return (0);
		if (!have_r_fork)
			have_r_fork = get_fork(philo, philo->r_fork_id);
	}
	return (1);
}
