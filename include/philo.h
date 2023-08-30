/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edecoste <edecoste@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 13:28:52 by edecoste          #+#    #+#             */
/*   Updated: 2023/08/30 14:57:28 by edecoste         ###   ########.fr       */
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
	long long		st_t;
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
	long long	last_ate_time;
	int			l_fork_id;
	int			r_fork_id;
	pthread_t	thread;
}	t_philo;


/****************************************************************** ft_atoi.c */
int			ft_atoi(const char *str);

/************************************************************** libft_utils.c */
void		ft_bzero(void *s, size_t n);
void		*ft_calloc(size_t count, size_t size);
void		ft_putendl_fd(char *s, int fd);
int			ft_putstr_fd(char *s, int fd);

/******************************************************************** utils.c */
long long	get_time(void);
void		ft_usleep(long long waiting);
int			check_arg(int arc, char **arv);

/********************************************************************* main.c */
int			threads_init(t_data *data);
int			philo_init(t_data *data);
int			data_init(t_data *data, int arc, char **arv);
int			main(int arc, char **arv);

/****************************************************************** actions.c */
int			sleeping(t_philo *philo);
int			think(t_philo *philo);
int			eat(t_philo *philo);
void		*philo_routine(void *arg);

/************************************************************* fork_gestion.c */
int			release_fork(t_philo *philo, int fork_id);
int			get_fork(t_philo *philo, int fork_id);
int			get_forks(t_philo *philo);

/************************************************************* fork_gestion.c */
int			is_death(t_philo *philo);
int			check_death(t_philo *philo);
static int	check_death_loop(t_data *data);

#endif