/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 12:48:08 by lzipp             #+#    #+#             */
/*   Updated: 2024/02/05 18:54:37 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	main(int argc, char **argv)
{
	t_data				*data;
	t_data				**philos;
	pthread_mutex_t		*p_mut;

	data = create_data(argc, argv);
	p_mut = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(p_mut, NULL);
	philos = init_philos(data);
	start_simulation(data);
	cleanup(data);
	pthread_mutex_destroy(p_mut);
	return (0);
}
