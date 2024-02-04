/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 12:48:08 by lzipp             #+#    #+#             */
/*   Updated: 2024/02/04 22:23:09 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	main(int argc, char **argv)
{
	t_data				*data;
	t_data				**philos;
	pthread_mutex_t		*mutex;

	data = create_data(argc, argv);
	mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	mutex = init_mutex(data);
	philos = init_philos(data);
	start_simulation(data);
	cleanup(data);
	return (0);
}
