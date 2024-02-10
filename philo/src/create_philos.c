/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 12:38:38 by lzipp             #+#    #+#             */
/*   Updated: 2024/02/10 17:08:18 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	fill_philos(t_philo **philos, t_data *data, t_fork **forks);

t_philo	**create_philos(t_data *data, t_fork **forks)
{
	t_philo			**philos;

	philos = (t_philo **)ft_calloc(data->philo_cnt + 1, sizeof(t_philo *));
	fill_philos(philos, data, forks);
	return (philos);
}

void	fill_philos(t_philo **philos, t_data *data, t_fork **forks)
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
			free_forks(forks);
			free(data);
			exit(1);
		}
		philos[i]->id = i + 1;
		philos[i]->is_dead = false;
		philos[i]->ms_to_die = data->ms_to_die;
		philos[i]->ms_to_sleep = data->ms_to_sleep;
		philos[i]->ms_to_eat = data->ms_to_eat;
		philos[i]->ms_start_time = data->ms_start_time;
		philos[i]->ms_last_ate_at = philos[i]->ms_start_time;
		philos[i]->must_eat_cnt = data->must_eat_cnt;
		philos[i]->left_fork = forks[i];
		philos[i]->right_fork = forks[(i + 1) % data->philo_cnt];
		// print all philo info
		printf("philo %d: ms_to_die %lld, ms_to_sleep %lld, ms_to_eat %lld, ms_start_time %lld, ms_last_ate_at %lld, must_eat_cnt %d\n",
			philos[i]->id, philos[i]->ms_to_die, philos[i]->ms_to_sleep, philos[i]->ms_to_eat, philos[i]->ms_start_time, philos[i]->ms_last_ate_at, philos[i]->must_eat_cnt);
	}
}
