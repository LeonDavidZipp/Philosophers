/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_forks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 22:46:54 by lzipp             #+#    #+#             */
/*   Updated: 2024/02/04 23:03:52 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

pthread_mutex_t	**create_forks(t_data *data)
{
	pthread_mutex_t	**forks;
	int				i;

	forks = (pthread_mutex_t **)ft_calloc(data->fork_cnt + 1,
			sizeof(pthread_mutex_t *));
	i = -1;
	while (++i < data->fork_cnt)
	{
		forks[i] = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
		if (!forks[i])
		{
			printf("\033[0;31mError: malloc failed\033[0m\n");
			ft_free_2d_mutex_arr((void **)forks);
			free(data);
			exit(1);
		}
		pthread_mutex_init(forks[i], NULL);
	}
	return (forks);
}
