/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edecoste <edecoste@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 12:01:34 by edecoste          #+#    #+#             */
/*   Updated: 2023/08/29 17:48:21 by edecoste         ###   ########.fr       */
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

int	sleeping(t_philo *philo)
{
	long long	actual_time;

	actual_time = get_time() - philo->data->start_time;
	if (philo->data->death_philo == 0)
	{
		printf("%lld %d is sleeping\n", actual_time, philo->id);
		usleep(philo->data->tt_sleep * 1000);
	}
	return (1);
}

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
	actual_time = get_time() - philo->data->start_time;
	if (philo->data->forks[fork_id - 1] == 0)
	{
		philo->data->forks[fork_id - 1] = 1;
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
		if (!have_r_fork)
			have_r_fork = get_fork(philo, philo->r_fork_id);
	}
	return (1);
}

int	think(t_philo *philo)
{
	long long	actual_time;

	pthread_mutex_lock(&philo->data->pause);
	actual_time = get_time() - philo->data->start_time;
	if (philo->data->death_philo == 0)
		printf("%lld %d is thinking\n", actual_time, philo->id);
	pthread_mutex_unlock(&philo->data->pause);
	return (1);
}

int	eat(t_philo *philo)
{
	long long	time;

	get_forks(philo);
	if (is_death(philo) == 0)
	{
		pthread_mutex_lock(&philo->data->pause);
		time = get_time();
		printf("%lld %d is eating\n", time - philo->data->start_time, philo->id);
		philo->last_ate_time = time;
		philo->nb_ate++;
		pthread_mutex_unlock(&philo->data->pause);
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
	pthread_mutex_lock(&philo->data->pause);
	philo->last_ate_time = get_time();
	pthread_mutex_unlock(&philo->data->pause);
	if (philo->id % 2)
		usleep(200);
	while (philo->data->eat_x_times == -1 || philo->nb_ate < philo->data->eat_x_times)
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

int	check_death(t_philo *philo)
{
	long long	time;

	time = get_time() - philo->last_ate_time;
	if (philo->data->death_philo)
		return (0);
	if (time >= philo->data->tt_die && philo->data->death_philo == 0)
	{
		time = get_time() - philo->data->start_time;
		printf("%lld %d died\n", time, philo->id);
		philo->data->death_philo = 1;
		philo->is_dead = 1;
		return (0);
	}
	return (1);
}

void	ft_usleep(long long waiting)
{
	long long	time;

	time = get_time();
	while ((get_time() - time) < waiting)
		usleep(100);
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

int	threads_init(t_data *data)
{
	int	i;

	i = -1;
	pthread_mutex_lock(&data->pause);
	data->start_time = get_time();
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

int	check_arg(int arc, char **arv)
{
	int	i;

	i = 1;
	while (i < arc)
	{
		if (ft_atoi(arv[i]) <= 0)
			return (0);
		i++;
	}
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
