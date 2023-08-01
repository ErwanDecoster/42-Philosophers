/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edecoste <edecoste@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 12:01:34 by edecoste          #+#    #+#             */
/*   Updated: 2023/08/01 17:29:33 by edecoste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*philo_routine(void *arg)
{
	t_philo *philo;
	
	philo = (t_philo *)arg;
	(void)philo;
	ft_putendl_fd("cc", 1);
	return (0);
}

int threads_init(t_data *data)
{
	int	i;

	i = 0;
	// mettre pause
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
	data->start_time = get_time();
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
		data->philo[i].l_fork = 0;
		data->philo[i].r_fork = 1;
		i++;
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
	if (arc == 6)
		data->eat_x_times = ft_atoi(arv[5]);
	// init philos 
	data->philo = ft_calloc(data->nb_philos, sizeof(t_philo));
	if (!data->philo)
		return (ft_putendl_fd(MALLOC, 1), 1);
	philo_init(data);
	return (0);
}

int main(int arc, char **arv)
{
	t_data data;
	
	ft_bzero(&data, sizeof(t_data));
	if (arc < 5 || arc > 6)
		return (ft_putendl_fd(BAD_ARG_NB, 1), 1);
	if (data_init(&data, arc, arv))
		return (0);
	threads_init(&data);
	free(data.philo);
	return (0);
}
