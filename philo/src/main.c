/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 12:48:08 by lzipp             #+#    #+#             */
/*   Updated: 2024/02/05 19:07:12 by lzipp            ###   ########.fr       */
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

void	philosophize(t_data *data, t_data **philos)
{
	int	i;

	i = -1;
	while (++i < data->philo_cnt)
	{
		philos[i]->start_time = data->start_time;
		philos[i]->p_mut = data->p_mut;
		philos[i]->id = i + 1;
		philos[i]->thread = (pthread_t *)malloc(sizeof(pthread_t));
		pthread_create(philos[i]->thread, NULL, philo_routine, philos[i]);
	}
}
