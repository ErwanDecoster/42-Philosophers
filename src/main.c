/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edecoste <edecoste@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 10:13:10 by edecoste          #+#    #+#             */
/*   Updated: 2023/09/04 14:07:40 by edecoste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../philosophers.h"
#include "../include/philo.h"

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
	free(data.philo);
	free(data.m_forks);
	free(data.forks_id);
	return (0);
}
