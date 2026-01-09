/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maleca <maleca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 17:02:55 by maleca            #+#    #+#             */
/*   Updated: 2026/01/09 15:43:11 by maleca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "includes/philo.h"

void	*routine2(void *arg)
{

}


void	*routine1(void *arg)
{

}

int	main(void)
{
	pthread_mutex_t test_lock;
	pthread_t	tid1;
	pthread_t	tid2;

	pthread_mutex_init(&test_lock, NULL);
	

}