/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edecoste <edecoste@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 12:01:34 by edecoste          #+#    #+#             */
/*   Updated: 2023/08/30 13:24:22 by edecoste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	threads_init(t_data *data)
{
	int	i;

	i = -1;
	pthread_mutex_lock(&data->pause);
	data->st_t = get_time();
	while (++i < data->nb_philos)
	{
		if (pthread_create(&data->philo[i].thread, NULL, philo_routine, &data->philo[i]))
		{
			free(data->philo);
			ft_putendl_fd(TRHREAD_CR, 1);
			pthread_mutex_unlock(&data->pause);
			return (0);
		}
	}
	pthread_mutex_unlock(&data->pause);
	check_death_loop(data);
	i = -1;
	while (++i < data->nb_philos)
		if (pthread_join(data->philo[i].thread, NULL))
			return (free(data->philo), ft_putendl_fd(TRHREAD_CR, 1), 0);
	return (1);
}

int	philo_init(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philos)
	{
		data->philo[i].data = data;
		data->philo[i].id = i + 1;
		data->philo[i].is_dead = 0;
		data->philo[i].l_fork_id = i;
		data->philo[i].nb_ate = 0;
		if (i == 0)
			data->philo[i].l_fork_id = data->nb_philos;
		data->philo[i].r_fork_id = i + 1;
		i++;
	}
	return (1);
}

int	data_init(t_data *data, int arc, char **arv)
{
	data->nb_philos = ft_atoi(arv[1]);
	data->tt_die = ft_atoi(arv[2]);
	data->tt_eat = ft_atoi(arv[3]);
	data->tt_sleep = ft_atoi(arv[4]);
	data->eat_x_times = -1;
	data->death_philo = 0;
	if (arc == 6)
		data->eat_x_times = ft_atoi(arv[5]);
	data->philo = ft_calloc(data->nb_philos, sizeof(t_philo));
	if (!data->philo)
		return (ft_putendl_fd(MALLOC, 1), 0);
	data->m_forks = ft_calloc(data->nb_philos, sizeof(pthread_mutex_t));
	if (!data->m_forks)
		return (free(data->philo), ft_putendl_fd(MALLOC, 1), 0);
	data->forks = ft_calloc(data->nb_philos, sizeof(int));
	if (!data->forks)
		return (free(data->philo), free(data->m_forks), ft_putendl_fd(MALLOC, 1), 0);
	philo_init(data);
	return (1);
}

int	main(int arc, char **arv)
{
	t_data	data;

	ft_bzero(&data, sizeof(t_data));
	if (arc < 5 || arc > 6)
		return (ft_putendl_fd(BAD_ARG_NB, 1), 1);
	if (!check_arg(arc, arv))
		return (ft_putendl_fd(BAD_ARG, 1), 1);
	if (!data_init(&data, arc, arv))
		return (0);
	threads_init(&data);
	free(data.philo);
	free(data.m_forks);
	free(data.forks);
	return (0);
}
