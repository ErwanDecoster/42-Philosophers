/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edecoste <edecoste@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 10:13:10 by edecoste          #+#    #+#             */
/*   Updated: 2023/10/12 16:06:44 by edecoste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	mutex_init(t_data *data)
{
	int	i;

	i = -1;
	if (pthread_mutex_init(&data->m_pause, NULL) != 0)
		return (putendl_fd(MUTEX, 2), free(data->philo), free(data->m_forks), \
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
			return (putendl_fd(MUTEX, 1), 0);
		}
		data->forks_id[i] = 0;
	}
	return (1);
}

static int	philo_init(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nb_philos)
	{
		data->philo[i].id = i + 1;
		data->philo[i].last_meal_time = 0;
		data->philo[i].meals = 0;
		data->philo[i].dead = 0;
		data->philo[i].data = data;
		data->philo[i].l_fork_id = i;
		if (i == data->nb_philos - 1)
			data->philo[i].r_fork_id = 0;
		else
			data->philo[i].r_fork_id = i + 1;
	}
	return (1);
}

static int	data_init(t_data *data, char **argv)
{
	data->nb_philos = ft_atoi(argv[1]);
	data->tt_die = ft_atoi(argv[2]);
	data->tt_eat = ft_atoi(argv[3]);
	data->tt_sleep = ft_atoi(argv[4]);
	data->eat_x_times = -1;
	if (argv[5])
		data->eat_x_times = ft_atoi(argv[5]);
	data->philo = malloc(sizeof(t_philo) * data->nb_philos);
	if (!data->philo)
		return (putendl_fd(MALLOC, 1), 0);
	data->m_forks = malloc(sizeof(pthread_mutex_t) * data->nb_philos);
	if (!data->m_forks)
		return (putendl_fd(MALLOC, 1), free(data->philo), 0);
	data->forks_id = malloc(sizeof(int) * data->nb_philos);
	if (!data->forks_id)
		return (putendl_fd(MALLOC, 1), free(data->philo), \
			free(data->m_forks), 0);
	if (!philo_init(data))
		return (0);
	if (!mutex_init(data))
		return (0);
	return (1);
}

static int	threads_init(t_data *data)
{
	int	i;

	i = -1;
	pthread_mutex_lock(&data->m_pause);
	while (++i < data->nb_philos)
		if (pthread_create(&data->philo[i].thread, NULL, philo_routine, \
			&data->philo[i]) != 0)
			return (putendl_fd(TRHREAD_CR, 1), \
					pthread_mutex_unlock(&data->m_pause), 0);
	data->start_time = get_time();
	pthread_mutex_unlock(&data->m_pause);
	i = -1;
	death_check_loop(data);
	while (++i < data->nb_philos)
		if (pthread_join(data->philo[i].thread, NULL) != 0)
			return (putendl_fd(THR_JOIN, 1), 0);
	return (1);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (error_check(argc, argv))
		return (1);
	ft_bzero(&data, sizeof(t_data));
	if (!data_init(&data, argv))
		return (1);
	threads_init(&data);
	destroy_mutexes(&data);
	return (free(data.philo), free(data.m_forks), free(data.forks_id), 0);
}
