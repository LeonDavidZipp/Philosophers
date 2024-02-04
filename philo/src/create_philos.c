/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 15:13:44 by lzipp             #+#    #+#             */
/*   Updated: 2024/02/05 00:16:03 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*philo_routine(void *data);
void	*ft_calloc(size_t count, size_t size);

// this will only be an example
// pthread_join, pthread_mutex_init,
// pthread_mutex_destroy, pthread_mutex_lock,
// pthread_mutex_unlock, pthread_create,
// pthread_detach

t_philo	**create_philos(t_data *data, pthread_mutex_t **forks)
{
	t_philo			**philos;
	int				i;

	philos = (t_philo **)ft_calloc(data->philo_cnt + 1, sizeof(t_philo *));
	i = -1;
	while (++i < data->philo_cnt)
	{
		philos[i] = (t_philo *)malloc(sizeof(t_philo));
		if (!philos[i])
		{
			printf("\033[0;31mError: malloc failed\033[0m\n");
			i = -1;
			while (++i < data->philo_cnt)
				free(philos[i]);
			free(philos);
			exit(1);
		}
		philos[i]->id = i + 1;
		philos[i]->ms_to_die = data->ms_to_die;
		philos[i]->ms_to_eat = data->ms_to_eat;
		philos[i]->ms_since_last_eat = 0;
		philos[i]->must_eat_cnt = data->must_eat_cnt;
	}
	return (philos);
}

void	fill_philos(t_data *data, t_philo **philos, pthread_mutex_t **forks)
{
	int	i;

	i = -1;
	while (++i < data->philo_cnt)
	{
		philos[i] = (t_philo *)malloc(sizeof(t_philo));
		if (!philos[i])
		{
			printf("\033[0;31mError: malloc failed\033[0m\n");
			ft_free_2d_arr((void **)philos);
			ft_free_2d_mutex_arr(forks);
			free(data);
			exit(1);
		}
		philos[i]->id = i + 1;
		philos[i]->ms_to_die = data->ms_to_die;
		philos[i]->ms_to_sleep = data->ms_to_sleep;
		philos[i]->ms_to_eat = data->ms_to_eat;
		philos[i]->ms_since_last_eat = 0;
		philos[i]->must_eat_cnt = data->must_eat_cnt;
		philos[i]->left_fork = forks[i];
		philos[i]->right_fork = forks[(i + 1) % data->philo_cnt];
	}
}
