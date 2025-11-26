/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maleca <maleca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 15:10:34 by maleca            #+#    #+#             */
/*   Updated: 2025/11/26 15:26:11 by maleca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

int	main(int ac, char **av)
{
	t_table *table;

	if (ac < 5 || ac > 6)
		return (hdl_err(ERR_ARGS, NULL),  EXIT_FAILURE);
	if (!is_valid(ac, av))
		return (EXIT_FAILURE);
	init_table(ac, av, &table);
	printf("%d\n", (*table).
	nb_philo);
	printf("%d\n", (*table).
	time_to_die);
	printf("%d\n", (*table).
	time_to_eat);
	printf("%d\n", (*table).
	time_to_sleep);
	// printf("%d", table->min_to_eat);
	return (EXIT_SUCCESS);
}
