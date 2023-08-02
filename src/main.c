/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edecoste <edecoste@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 12:01:34 by edecoste          #+#    #+#             */
/*   Updated: 2023/08/02 17:09:41 by edecoste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	sleeping(t_philo *philo)
{
	printf("%lld %d is sleeping\n", get_time() - philo->data->start_time, philo->id);
	usleep(philo->data->tt_sleep * 1000);
	(void)philo;
	return (1);
}

int release_fork(t_philo *philo, int fork_id)
{
	// mettre pause m_fork
	philo->data->forks[fork_id - 1] = 0;
	// stop pause m_fork
	return (0);
}

int	get_fork(t_philo *philo, int fork_id)
{
	// mettre pause m_fork
	if (philo->data->forks[fork_id - 1] == 0)
	{
		philo->data->forks[fork_id - 1] = 1;
		printf("%lld %d has taken a fork\n", get_time() - philo->data->start_time, philo->id);
		// stop pause m_fork
		return (1);
	}
	// stop pause m_fork
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
		// check death ?
		if (!have_l_fork)
			have_l_fork = get_fork(philo, philo->l_fork_id);
		if (!have_r_fork)
			have_r_fork = get_fork(philo, philo->r_fork_id);
	}
	return (1);
}

int	think(t_philo *philo)
{
	// mettre pause
	// check death ?
	printf("%lld %d is thinking\n", get_time() - philo->data->start_time, philo->id);
	// stop pause
	return (1);
}

int eat(t_philo *philo)
{
	// mettre pause
	// check death ?
	if (get_forks(philo))
	{
		printf("%lld %d is eating\n", get_time() - philo->data->start_time, philo->id);
		usleep(philo->data->tt_eat * 1000);
		release_fork(philo, philo->l_fork_id);
		release_fork(philo, philo->r_fork_id);
		philo->nb_ate++;
	}
	// stop pause
	return (1);
}

void	*philo_routine(void *arg)
{
	t_philo *philo;
	
	philo = (t_philo *)arg;
	(void)philo;
	if (philo->id % 2)
		usleep(200);
	while (philo->data->eat_x_times == -1 || philo->nb_ate < philo->data->eat_x_times)
	{
		think(philo);
		eat(philo);
		sleeping(philo);
	}
	return (NULL);
}

int threads_init(t_data *data)
{
	int	i;

	i = 0;
	// mettre pause
	data->start_time = get_time();
	while (i < data->nb_philos)
	{
		if (pthread_create(&data->philo[i].thread, NULL, philo_routine, &data->philo[i]))
		{
			free(data->philo);
			ft_putendl_fd(TRHREAD_CR, 1);
			// stop pause
			return (0);
		}
		i++;
	}
	// stop pause
	// check death loop
	i = 0;
	while (i < data->nb_philos)
	{
		if (pthread_join(data->philo[i].thread, NULL))
		{
			free(data->philo);
			ft_putendl_fd(TRHREAD_CR, 1);
			return (0);
		}
		i++;
	}
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
	int	j;
	j = 0;
	while (j < data->nb_philos)
	{
		printf("Philo : %i l_fork_id : %i r_fork_id : %i\n", j, data->philo[j].l_fork_id, data->philo[j].r_fork_id);
		j++;
	}
	
	return (1);
}

int	data_init(t_data *data, int arc, char **arv)
{
	// init data struct
	data->nb_philos = ft_atoi(arv[1]);
	data->tt_die = ft_atoi(arv[2]);
	data->tt_eat = ft_atoi(arv[3]);
	data->tt_sleep = ft_atoi(arv[4]);
	data->eat_x_times = -1;
	if (arc == 6)
		data->eat_x_times = ft_atoi(arv[5]);
	// init philos 
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

int main(int arc, char **arv)
{
	t_data data;
	
	ft_bzero(&data, sizeof(t_data));
	if (arc < 5 || arc > 6)
		return (ft_putendl_fd(BAD_ARG_NB, 1), 1);
	// si tout les arc doivent etre superieure a 0
	if (!data_init(&data, arc, arv))
		return (0);
	threads_init(&data);
	free(data.philo);
	free(data.m_forks);
	free(data.forks);
	return (0);
}
