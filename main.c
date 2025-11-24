/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maleca <maleca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 15:10:34 by maleca            #+#    #+#             */
/*   Updated: 2025/11/24 17:59:55 by maleca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

int	main(int ac, char **av)
{
	t_table *table;

	if (ac < 5 || ac > 6)
		return (msg(STR_ERR_ARGS),NULL ,  EXIT_FAILURE);
	if (!is_valid(av))
		return (EXIT_FAILURE);
	init_table(ac, av, table);
	table = (ac, av);

}