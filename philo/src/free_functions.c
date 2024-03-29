/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 14:19:39 by lzipp             #+#    #+#             */
/*   Updated: 2024/02/21 16:47:17 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	ft_free_2d_arr(void **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}

void	free_forks(t_fork **forks)
{
	int	i;

	i = -1;
	while (forks[++i])
	{
		pthread_mutex_destroy(forks[i]->mutex);
		free(forks[i]->mutex);
		free(forks[i]);
	}
	free(forks);
}

void	free_philos(t_philo **philos)
{
	int	i;

	i = -1;
	while (philos[++i])
	{
		free(philos[i]->thread);
		pthread_mutex_destroy(philos[i]->eat_mut);
		free(philos[i]->eat_mut);
		free(philos[i]);
	}
	free(philos);
}

void	free_resources(t_data *data, t_philo **philos, t_fork **forks)
{
	free_philos(philos);
	free_forks(forks);
	free(data);
}
