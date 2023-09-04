/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edecoste <edecoste@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 10:22:14 by edecoste          #+#    #+#             */
/*   Updated: 2023/09/04 14:10:36 by edecoste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../philosophers.h"
#include "../include/philo.h"

int	mutex_init(t_data *data)
{
	int	i;

	i = -1;
	if (pthread_mutex_init(&data->m_pause, NULL) != 0)
		return (error_display(MUTEX), free(data->philo), free(data->m_forks), \
				free(data->forks_id), 0);
	while (++i < data->nb_philos)
	{
		if (pthread_mutex_init(&data->m_forks[i], NULL) != 0)
		{
			pthread_mutex_destroy(&data->m_pause);
			free(data->philo);
			free(data->forks_id);
			while (--i >= 0)
				pthread_mutex_destroy(&data->m_forks[i]);
			free(data->m_forks);
			return (error_display(MUTEX), 0);
		}
		data->forks_id[i] = 0;
	}
	return (1);
}

int	philo_init(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nb_philos)
	{
		data->philo[i].nb_philos = data->nb_philos;
		data->philo[i].id = i + 1;
		data->philo[i].last_meal_time = 0;
		data->philo[i].meals = 0;
		data->philo[i].dead = 0;
		data->philo[i].data = data;
		data->philo[i].l_fork = i;
		if (i == data->nb_philos - 1)
			data->philo[i].r_fork = 0;
		else
			data->philo[i].r_fork = i + 1;
	}
	return (1);
}

int	data_init(t_data *data, char **argv)
{
	data->nb_philos = ft_atoi(argv[1]);
	data->tt_die = ft_atoi(argv[2]);
	data->tt_eat = ft_atoi(argv[3]);
	data->tt_sleep = ft_atoi(argv[4]);
	if (argv[5])
		data->eat_x_times = ft_atoi(argv[5]);
	else
		data->eat_x_times = -1;
	data->philo = malloc(sizeof(t_philo) * data->nb_philos);
	if (!data->philo)
		return (error_display(MALLOC), 0);
	data->m_forks = malloc(sizeof(pthread_mutex_t) * data->nb_philos);
	if (!data->m_forks)
		return (error_display(MALLOC), free(data->philo), 0);
	data->forks_id = malloc(sizeof(int) * data->nb_philos);
	if (!data->m_forks)
		return (error_display(MALLOC), free(data->philo), free(data->m_forks), 0);
	if (!philo_init(data))
		return (0);
	if (!mutex_init(data))
		return (0);
	return (1);
}
