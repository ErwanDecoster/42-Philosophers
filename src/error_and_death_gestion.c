/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_and_death_gestion.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edecoste <edecoste@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 15:02:58 by edecoste          #+#    #+#             */
/*   Updated: 2023/09/04 16:46:02 by edecoste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	error_check(int argc, char **argv)
{
	int	nbr;
	int	i;
	int	j;

	if (argc != 5 && argc != 6)
		return (putendl_fd(BAD_ARG_NB, 1), 1);
	i = 0;
	while (++i < argc)
	{
		j = -1;
		while (argv[i][++j])
			if (argv[i][j] < 48 || argv[i][j] > 57)
				return (putendl_fd(BAD_ARG, 1), 1);
		nbr = ft_atoi(argv[i]);
		if (nbr <= 0)
			return (putendl_fd(BAD_ARG, 1), 1);
	}
	return (0);
}

static int	check_death(t_philo *philo)
{
	long long	time;

	time = get_time() - philo->last_meal_time;
	if (philo->data->death == 1)
		return (0);
	if (time >= philo->data->tt_die && philo->data->death == 0)
	{
		time = get_time() - philo->data->start_time;
		printf("%lld %d died\n", time, philo->id);
		philo->data->death = 1;
		philo->dead = 1;
		return (0);
	}
	return (1);
}

int	death_check_loop(t_data *data)
{
	int	i;

	while (1)
	{
		ft_usleep(3);
		i = -1;
		while (++i < data->nb_philos)
		{
			pthread_mutex_lock(&data->m_pause);
			if (data->philo->meals == data->eat_x_times)
				return (pthread_mutex_unlock(&data->m_pause), 1);
			if (data->philo[i].last_meal_time != 0)
				if (!check_death(&data->philo[i]))
					return (pthread_mutex_unlock(&data->m_pause), 0);
			pthread_mutex_unlock(&data->m_pause);
		}
	}
}
