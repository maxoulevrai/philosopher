/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maleca <maleca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 18:53:30 by maleca            #+#    #+#             */
/*   Updated: 2025/11/27 21:33:47 by maleca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>

# define true 1
# define false 0
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


typedef struct s_table
{
	int			nb_philo;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			min_to_eat;
	pthread_t	*philo_tid;
	pthread_t	*undertaker_tid;
	pthread_mutex_t	*fork;
}		t_table;
typedef int bool;


void	init_table(int ac, char **av, t_table **table);
void	msg_err(char *err_msg);
void	hdl_err(char *err_msg, t_table *table);
bool	is_valid(int ac, char **av);
int		positive_atoi(const char *nptr);
void	*philo_routine(void *arg);
void	*undertaker_routine(void *arg);


#endif