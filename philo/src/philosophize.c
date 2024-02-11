/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophize.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 22:02:21 by lzipp             #+#    #+#             */
/*   Updated: 2024/02/11 18:09:27 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static t_routine	*create_routines(t_data *data, t_philo **philos,
						pthread_mutex_t *p_mut, pthread_mutex_t *death_mut);
static bool			start_threads(t_data *data, t_philo **philos,
						t_routine *routines);
static void			handle_thread_error(t_data *data, t_philo **philos,
						t_fork **forks, t_routine *routines);

void	philosophize(t_data *data, t_philo **philos,
	t_fork **forks)
{
	int					i;
	t_routine			*routines;
	pthread_mutex_t		p_mut;
	pthread_mutex_t		death_mut;

	pthread_mutex_init(&p_mut, NULL);
	pthread_mutex_init(&death_mut, NULL);
	routines = create_routines(data, philos, &p_mut, &death_mut);
	if (!routines)
	{
		free_resources(data, philos, forks);
		exit(1);
	}
	if (!start_threads(data, philos, routines))
		handle_thread_error(data, philos, forks, routines);
	i = -1;
	while (++i < data->philo_cnt)
		pthread_join(*philos[i]->thread, NULL);
	pthread_mutex_destroy(&p_mut);
	pthread_mutex_destroy(&death_mut);
	free(routines);
}

static t_routine	*create_routines(t_data *data, t_philo **philos,
	pthread_mutex_t *p_mut, pthread_mutex_t *death_mut)
{
	t_routine	*routines;
	int			i;

	routines = (t_routine *)ft_calloc(data->philo_cnt + 1, sizeof(t_routine));
	if (!routines)
	{
		printf("\033[0;31mError: malloc failed\033[0m\n");
		return (NULL);
	}
	i = -1;
	while (++i < data->philo_cnt)
	{
		routines[i].philo = philos[i];
		routines[i].p_mut = p_mut;
		routines[i].some_died = &data->some_died;
		routines[i].death_mut = death_mut;
		routines[i].ms_start_time = data->ms_start_time;
	}
	return (routines);
}

static bool	start_threads(t_data *data, t_philo **philos,
	t_routine *routines)
{
	int					i;

	i = -1;
	while (++i < data->philo_cnt)
	{
		philos[i]->thread = (pthread_t *)malloc(sizeof(pthread_t));
		if (!philos[i]->thread)
			return (false);
		pthread_create(philos[i]->thread, NULL, philo_routine,
			(void *)&routines[i]);
	}
	return (true);
}

static void	handle_thread_error(t_data *data, t_philo **philos,
	t_fork **forks, t_routine *routines)
{
	printf("\033[0;31mError: malloc failed\033[0m\n");
	free_resources(data, philos, forks);
	free(routines);
	exit(1);
}
