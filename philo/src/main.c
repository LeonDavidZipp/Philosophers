/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 12:48:08 by lzipp             #+#    #+#             */
/*   Updated: 2024/02/05 20:44:25 by lzipp            ###   ########.fr       */
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

void	philosophize(t_data *data, t_philo **philos, pthread_mutex_t **forks,
	pthread_mutex_t *p_mut)
{
	int			i;
	t_routine	*routine;

	i = -1;
	while (++i < data->philo_cnt)
	{
		philos[i]->thread = (pthread_t *)ft_calloc(data->philo_cnt + 1,
				sizeof(pthread_t));
		routine = (t_routine *)malloc(sizeof(t_routine));
		if (!philos[i]->thread || !routine)
		{
			printf("\033[0;31mError: malloc failed\033[0m\n");
			ft_free_2d_arr((void **)philos);
			ft_free_2d_mutex_arr(forks);
			free(data);
			exit(1);
		}
		routine->philo = philos[i];
		routine->p_mut = p_mut;
		pthread_create(philos[i]->thread, NULL, philo_routine, philos[i]);
	}
}
{
	int			i;
	t_routine	*routine;

	i = -1;
	while (++i < data->philo_cnt)
	{
		philos[i]->thread = (pthread_t *)ft_calloc(data->philo_cnt + 1,
				sizeof(pthread_t));
		routine = (t_routine *)malloc(sizeof(t_routine));
		if (!philos[i]->thread || !routine)
		{
			printf("\033[0;31mError: malloc failed\033[0m\n");
			ft_free_2d_arr((void **)philos);
			ft_free_2d_mutex_arr(forks);
			free(data);
			exit(1);
		}
		routine->philo = philos[i];
		routine->p_mut = p_mut;
		pthread_create(philos[i]->thread, NULL, philo_routine, philos[i]);
	}
}
