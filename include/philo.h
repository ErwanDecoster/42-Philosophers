/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edecoste <edecoste@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 13:28:52 by edecoste          #+#    #+#             */
/*   Updated: 2023/08/01 17:22:34 by edecoste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

/* to write, read, close, access, pipe, dup, dup2, execve, fork */
# include <unistd.h>
//# include <sys/types.h>
# include <sys/uio.h>
/* malloc, free, exit */
# include <stdlib.h>
/* open, unlink */
# include <fcntl.h>
/* waitpid, wait */
# include <sys/wait.h>
/* strerror */
# include <string.h>
/*to perror*/
# include <stdint.h>
# include <errno.h>


# include <pthread.h>
# include <sys/time.h>


# define BAD_ARG "Error: Bad argument, must be a number"
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
	struct s_philo	*philo;
}	t_data;

typedef struct s_philo
{
	t_data		*data;
	int			id;
	int			is_dead;
	int			l_fork;
	int			r_fork;
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