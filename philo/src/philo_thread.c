/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 15:13:44 by lzipp             #+#    #+#             */
/*   Updated: 2024/02/04 20:40:38 by lzipp            ###   ########.fr       */
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

t_philo	**create_philos(t_data *data)
{
	t_philo			**philos;
	int				i;

	philos = (t_philo *)ft_calloc(data->philo_cnt + 1, sizeof(t_philo));
	i = -1;
	while (++i < data->philo_cnt)
	{
		philos[i] = (t_philo *)malloc(sizeof(t_philo));
		if (!philos[i])
		{
			write(2, "Error: malloc failed\n", 21);
			i = -1;
			while (++i < data->philo_cnt)
				free(philos[i]);
			free(philos);
			exit(1);
		}
		philos[i]->id = i;
		philos[i]->ms_to_die = data->ms_to_die;
		philos[i]->ms_to_eat = data->ms_to_eat;
		philos[i]->ms_since_last_eat = 0;
		philos[i]->must_eat_cnt = data->must_eat_cnt;
	}
	return (philos);
}

pthread_t	**init_philos(t_data *data)
{
	pthread_t	**philos;
	int			i;

	philos = (pthread_t *)ft_calloc(data->philo_cnt, sizeof(pthread_t));
	i = -1;
	while (++i < data->philo_cnt)
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

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;
	char	*cptr;
	size_t	total;

	total = count * size;
	if ((count != 0 && total / count != size)
		|| (size != 0 && total / size != count))
		return (NULL);
	ptr = (void *)malloc(total);
	if (!ptr)
		return (NULL);
	cptr = (char *)ptr;
	while (total > 0)
	{
		*cptr = 0;
		cptr++;
		total--;
	}
	return (ptr);
}
