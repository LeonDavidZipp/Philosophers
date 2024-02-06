/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 12:48:08 by lzipp             #+#    #+#             */
/*   Updated: 2024/02/06 13:28:40 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	main(int argc, char **argv)
{
	t_data				*data;
	t_data				**philos;

	data = create_data(argc, argv);
	philos = init_philos(data);
	start_simulation(data);
	cleanup(data);
	return (0);
}

static void	philosophize(t_data *data, t_philo **philos,
	pthread_mutex_t **forks, pthread_mutex_t *p_mut)
{
	int					i;
	t_routine			*routines;
	pthread_mutex_t		p_mut;

	pthread_mutex_init(&p_mut, NULL);
	i = -1;
	while (++i < data->philo_cnt)
	{
		philos[i]->thread = (pthread_t *)malloc(sizeof(pthread_t));
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
		free(routine);
	pthread_mutex_destroy(&p_mut);
	}
}

static void	philosophize(t_data *data, t_philo **philos,
	pthread_mutex_t **forks)
{
	int					i;
	t_routine			*routines;
	pthread_mutex_t		p_mut;

	pthread_mutex_init(&p_mut, NULL);
	i = -1;
	while (++i < data->philo_cnt)
	{
		philos[i]->thread = (pthread_t *)malloc(sizeof(pthread_t));
		if (!philos[i]->thread)
		{
			printf("\033[0;31mError: malloc failed\033[0m\n");
			ft_free_2d_arr((void **)philos);
			ft_free_2d_mutex_arr(forks);
			free(data);
			exit(1);
		}
		routines[i].philo = philos[i];
		routines[i].p_mut = p_mut;
		pthread_create(philos[i]->thread, NULL, philo_routine, &routines[i]);
	pthread_mutex_destroy(&p_mut);
	}
}
