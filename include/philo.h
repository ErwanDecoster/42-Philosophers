/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edecoste <edecoste@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 13:28:52 by edecoste          #+#    #+#             */
/*   Updated: 2023/08/28 15:08:24 by edecoste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdlib.h>
# include <stdint.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>

# define BAD_ARG "Error: Bad argument, must be a number greater than 0"
# define BAD_ARG_NB "Error: Bad argument number, philo need 4 or 5 arguments"
# define MALLOC "Error: Malloc failure"
# define TRHREAD_CR "Error: pthread_create failure"
# define THR_JOIN "Error: pthread_join failure"
# define TIME_ERR "Error: gettimeofday failure"

typedef struct s_data
{
	int				nb_philos;
	int				tt_die;
	int				tt_eat;
	int				tt_sleep;
	int				eat_x_times;
	long long		start_time;
	int				death_philo;
	pthread_mutex_t	*m_forks;
	pthread_mutex_t	pause;
	int				*forks;
	struct s_philo	*philo;
}	t_data;

typedef struct s_philo
{
	t_data		*data;
	int			id;
	int			is_dead;
	int			nb_ate;
	int			last_ate_time;
	int			l_fork_id;
	int			r_fork_id;
	pthread_t	thread;
}	t_philo;

/********************************************************************* main.c */
void	childs(t_data *pipex, char **av, char **envp);

/***************************************************************** ft_bzero.c */
void	ft_bzero(void *s, size_t n);

/**************************************************************** ft_calloc.c */
void	*ft_calloc(size_t count, size_t size);

/************************************************************ ft_putendl_fd.c */
void	ft_putendl_fd(char *s, int fd);

/************************************************************* ft_putstr_fd.c */
int	ft_putstr_fd(char *s, int fd);

/****************************************************************** ft_atoi.c */
int	ft_atoi(const char *str);

/******************************************************************** utils.c */
long long	get_time(void);



#endif