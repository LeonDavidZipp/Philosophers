/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_forks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 22:46:54 by lzipp             #+#    #+#             */
/*   Updated: 2024/02/10 15:08:19 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	handle_fork_error(t_fork **forks, t_data *data);

pthread_mutex_t	**create_forks(t_data *data)
{
	t_fork			**forks;
	int				i;

	forks = (t_fork **)ft_calloc(data->fork_cnt + 1,
			sizeof(t_fork *));
	i = -1;
	while (++i < data->fork_cnt)
	{
		forks[i] = (t_fork *)malloc(sizeof(t_fork));
		if (!forks[i])
			handle_fork_error(forks, data);
		forks[i]->id = i + 1;
		forks[i]->is_taken = false;
		forks[i]->mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
		if (!forks[i]->mutex)
			handle_fork_error(forks, data);
		pthread_mutex_init(forks[i]->mutex, NULL);
	}
	return (forks);
}

static void	handle_fork_error(t_fork **forks, t_data *data)
{
	printf("\033[0;31mError: malloc failed\033[0m\n");
	ft_free_2d_mutex_arr((pthread_mutex_t **)forks);
	free(data);
	exit(1);
}
