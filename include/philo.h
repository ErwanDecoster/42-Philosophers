/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edecoste <edecoste@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 13:28:52 by edecoste          #+#    #+#             */
/*   Updated: 2023/09/04 14:05:50 by edecoste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

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
# define MUTEX "Error: mutex_init failure"

typedef struct s_data
{
	int				nb_philos;
	int				tt_die;
	int				tt_eat;
	int				tt_sleep;
	int				death;
	int				eat_x_times;
	long long		start_time;
	pthread_mutex_t	m_pause;
	pthread_mutex_t	*m_forks;
	int				*forks_id;
	struct s_philo	*philo;
}				t_data;

typedef struct s_philo
{
	t_data			*data;
	int				nb_philos;
	int				id;
	long long		last_meal_time;
	int				meals;
	int				dead;
	pthread_t		thread;
	int				l_fork;
	int				r_fork;
}				t_philo;

/*	main.c	*/
int			main(int argc, char **argv);

/*	actions	*/
void		action(t_philo *philo, t_data *data);
int			think(t_philo *philo);

/*	errors.c	*/
int			error_check(int argc, char **argv);
void		error_display(char *msg);

/*	exec.c	*/
int			threads_init(t_data *data);
void		*philo_routine(void *arg);

/*	init.c	*/
int			data_init(t_data *data, char **argv);

/*	lib.c	*/
int			ft_atoi(const char *str);
int			ft_isdigit(int c);
void		ft_bzero(void *s, size_t n);
void		ft_usleep(long long waiting);

/*	utils.c	*/
int			get_forks(t_philo *philo);
int			is_dead(t_philo *philo);
long long	get_time(void);
void		destroy_mutexes(t_data *data);

#endif