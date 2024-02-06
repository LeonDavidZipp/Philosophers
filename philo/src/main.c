/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 12:48:08 by lzipp             #+#    #+#             */
/*   Updated: 2024/02/06 20:57:20 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	start_threads(t_data *data, t_philo **philos,
				t_routine *routines, pthread_mutex_t *p_mut);
static void	philosophize(t_data *data, t_philo **philos,
				pthread_mutex_t **forks);

int	main(int argc, char **argv)
{
	t_data				*data;
	t_philo				**philos;
	pthread_mutex_t		**forks;

	data = create_data(argc, argv);
	forks = create_forks(data);
	philos = create_philos(data, forks);
	philosophize(data, philos, forks);
	cleanup(data, forks, philos);
	return (0);
}

// static void	philosophize(t_data *data, t_philo **philos,
// 	pthread_mutex_t **forks, pthread_mutex_t *p_mut)
// {
// 	int					i;
// 	t_routine			*routines;
// 	pthread_mutex_t		p_mut;

// 	pthread_mutex_init(&p_mut, NULL);
// 	i = -1;
// 	while (++i < data->philo_cnt)
// 	{
// 		philos[i]->thread = (pthread_t *)malloc(sizeof(pthread_t));
// 		routine = (t_routine *)malloc(sizeof(t_routine));
// 		if (!philos[i]->thread || !routine)
// 		{
// 			printf("\033[0;31mError: malloc failed\033[0m\n");
// 			ft_free_2d_arr((void **)philos);
// 			ft_free_2d_mutex_arr(forks);
// 			free(data);
// 			exit(1);
// 		}
// 		routine->philo = philos[i];
// 		routine->p_mut = p_mut;
// 		pthread_create(philos[i]->thread, NULL, philo_routine, philos[i]);
// 		free(routine);
// 	pthread_mutex_destroy(&p_mut);
// 	}
// }

static void	philosophize(t_data *data, t_philo **philos,
	pthread_mutex_t **forks)
{
	int					i;
	int					is_alive;
	t_routine			*routines;
	pthread_mutex_t		p_mut;

	pthread_mutex_init(&p_mut, NULL);
	routines = (t_routine *)ft_calloc(data->philo_cnt + 1, sizeof(t_routine));
	i = -1;
	if (start_threads(data, philos, routines, &p_mut))
	{
		printf("\033[0;31mError: malloc failed\033[0m\n");
		ft_free_2d_arr((void **)philos);
		ft_free_2d_mutex_arr(forks);
		free(data);
		exit(1);
	}
	while (++i < data->philo_cnt)
		pthread_join(philos[i]->thread, &is_alive);
	pthread_mutex_destroy(&p_mut);
}

static int	start_threads(t_data *data, t_philo **philos,
	t_routine *routines, pthread_mutex_t *p_mut)
{
	int					i;
	pthread_mutex_t		*death_mut;

	death_mut = (pthread_mutex_t *)ft_calloc(1, sizeof(pthread_mutex_t));
	if (!death_mut)
		return (1);
	i = -1;
	while (++i < data->philo_cnt)
	{
		philos[i]->thread = (pthread_t *)malloc(sizeof(pthread_t));
		if (!philos[i]->thread)
			return (1);
		routines[i].philo = philos[i];
		routines[i].p_mut = p_mut;
		routines[i].some_died = &data->some_died;
		routines[i].death_mut = death_mut;
		pthread_create(philos[i]->thread, NULL, philo_routine, &routines[i]);
		// pthread_create(philos[i]->thread, NULL, philo_routine, (void *)&routines[i]);
	}
	return (0);
}
