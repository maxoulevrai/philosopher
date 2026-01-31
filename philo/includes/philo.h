/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 18:53:30 by maleca            #+#    #+#             */
/*   Updated: 2026/01/31 20:54:37 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <sys/time.h>

# define MAX_PHILO 200
# define ERR_ARGS "args error\n"
# define ERR_DIGITS "digits error\n"
# define ERR_MAX_COUNT "max count error\n"
# define ERR_MALLOC "malloc error\n"
# define ERR_INIT "init error\n"
# define ERR_MALLOC_PHILO "malloc philo error\n"
# define ERR_PHILO_TRHD "philo thread error\n"
# define ERR_UNDERTAKER_TRHD "undertaker thread error\n"
# define ERR_MUTEX "mutex init error\n"

typedef enum {FALSE, TRUE} t_bool;

typedef struct s_philo	t_philo;

typedef struct s_table
{
	time_t			start;
	int				stop;
	int				nb_philo;
	int				satiety;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	time_t			min_to_eat;
	pthread_t		undertaker_tid;
	pthread_mutex_t	*fork_locks;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	stop_lock;
	pthread_mutex_t	satiety_lock;
	pthread_mutex_t	last_ate_lock;
	t_philo			**philo;
}		t_table;

typedef struct s_philo
{
	int				idx;
	pthread_t		philo_tid;

	unsigned int	forks[2];
	unsigned int	times_ate;
	time_t			last_ate;
	t_table			*table;
}		t_philo;

/* INIT */

t_table	*init(int ac, char **av, t_table *table);

/* PARSING */

t_bool	is_valid(int ac, char **av);
int		positive_atoi(const char *nptr);

/* ROUTINE */

void	multi_thread(t_table *table);
void	*mims_routine(void *arg);
void	*start(void *arg);
void	*undertaker_routine(void *arg);
void	end_simulation(char *err_msg, t_table *table);

/* TIME */

time_t	get_current_time(void);
time_t	sim_time(t_table *table);
void	thread_sleep(time_t sleep_time, t_table *table);

/* ERR */

void	print_status(t_philo *philo, char *status);
void	free_philo(t_table *table);
void	free_locks(t_table *table);

/* UTILS */

void	msg_err(char *err_msg);

#endif