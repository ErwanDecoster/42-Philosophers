/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edecoste <edecoste@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 10:25:24 by edecoste          #+#    #+#             */
/*   Updated: 2023/09/04 14:07:40 by edecoste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../philosophers.h"
#include "../include/philo.h"

void	error_display(char *msg)
{
	printf("%s\n", msg);
	return ;
}

int	error_check(int argc, char **argv)
{
	int	nbr;
	int	i;
	int	j;

	if (argc != 5 && argc != 6)
		return (error_display("Error: Wrong number of arguments"), 1);
	i = 0;
	while (++i < argc)
	{
		j = -1;
		while (argv[i][++j])
		{
			if (!ft_isdigit(argv[i][j]))
				return (error_display(BAD_ARG), 1);
		}
		nbr = ft_atoi(argv[i]);
		if (nbr <= 0)
		{
			error_display("Error: Bad argument, must be a positive number");
			return (1);
		}
	}
	return (0);
}
