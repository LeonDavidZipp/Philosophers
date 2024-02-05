/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 12:48:08 by lzipp             #+#    #+#             */
/*   Updated: 2024/02/05 11:26:04 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	main(int argc, char **argv)
{
	t_data				*data;
	t_data				**philos;
	pthread_mutex_t		*print_mutex;

	data = create_data(argc, argv);
	print_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(print_mutex, NULL);
	philos = init_philos(data);
	start_simulation(data);
	cleanup(data);
	pthread_mutex_destroy(print_mutex);
	return (0);
}
