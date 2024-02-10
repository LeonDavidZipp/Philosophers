/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 14:19:39 by lzipp             #+#    #+#             */
/*   Updated: 2024/02/10 14:58:43 by lzipp            ###   ########.fr       */
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

void	ft_free_2d_mutex_arr(pthread_mutex_t **arr)
{
	int			i;

	i = -1;
	while (arr[++i])
	{
		pthread_mutex_destroy(arr[i]);
		free(arr[i]);
	}
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
		free(philos[i]);
	}
	free(philos);
}

void	free_resources(t_data *data, t_philo **philos, pthread_mutex_t **forks)
{
	free_philos(philos);
	ft_free_2d_mutex_arr(forks);
	free(data);
}
