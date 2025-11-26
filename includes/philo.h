/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maleca <maleca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 18:53:30 by maleca            #+#    #+#             */
/*   Updated: 2025/11/25 16:10:03 by maleca           ###   ########.fr       */
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
# define ERR_ARGS "args error"
# define ERR_DIGITS "digits error"
# define ERR_MAX_COUNT "max count error"
# define ERR_MALLOC "malloc error"

typedef struct s_table
{
	int	nb_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	min_to_eat;

}		t_table;
typedef int bool;


void	init_table(int ac, char **av, t_table **table);
void	hdl_err(char *err_msg, char *arg);
bool	is_valid(int ac, char **av);
int		positive_atoi(const char *nptr);

#endif