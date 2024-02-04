/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 15:13:44 by lzipp             #+#    #+#             */
/*   Updated: 2024/02/04 15:20:25 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void *philo_routine(void *data);

// this will only be an example
// pthread_join, pthread_mutex_init,
// pthread_mutex_destroy, pthread_mutex_lock,
// pthread_mutex_unlock, pthread_create,
// pthread_detach

pthread_t	**init_philos(t_data *data)
{
	pthread_t	**philos;
	int			i;

	philos = (pthread_t *)malloc(sizeof(pthread_t) * data->philo_cnt);
	i = 0;
	while (i < data->philo_cnt)
	{
		pthread_create(philos[i], NULL, &philo_routine, (void *)data);
		i++;
	}
	return (philos);
}

void	*philo_routine(void *data)
{
	t_data	*philo;

	philo = (t_data *)data;
	while (1)
	{
		;// do something
	}
	return (NULL);
}
