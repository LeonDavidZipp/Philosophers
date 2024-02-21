/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophize.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 22:02:21 by lzipp             #+#    #+#             */
/*   Updated: 2024/02/21 16:33:53 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static t_p_routine	*create_philo_routines(t_data *data, t_philo **philos,
						pthread_mutex_t *p_mut, pthread_mutex_t *death_mut);
static void			create_monitor_routine(t_m_routine *r, t_data *data,
						t_philo **philos);
static bool			start_threads(t_data *data, t_philo **philos,
						t_p_routine *routines);
static void			handle_thread_error(t_data *data, t_philo **philos,
						t_fork **forks, t_p_routine *routines);

void	philosophize(t_data *data, t_philo **philos, t_fork **forks)
{
	t_p_routine			*philo_routines;
	t_m_routine			monit_routine;
	pthread_mutex_t		p_mut;
	pthread_mutex_t		death_mut;
	pthread_t			monitor_thread;

	philo_cnt = ft_null_terminated_arr_len((void **)philos);
	pthread_mutex_init(&p_mut, NULL);
	pthread_mutex_init(&death_mut, NULL);
	philo_routines = create_philo_routines(data, philos, &p_mut, &death_mut);
	create_monitor_routine(&monit_routine, data, philos);
	monit_routine.p_mut = &p_mut;
	monit_routine.death_mut = &death_mut;
	if (!philo_routines)
		return (free(philo_routines));
	if (!start_threads(data, philos, philo_routines))
		handle_thread_error(data, philos, forks, philo_routines);
	pthread_create(&monitor_thread, NULL, monitor_routine, &monit_routine);
	while (--data->philo_cnt >= 0)
		pthread_join(*philos[data->philo_cnt]->thread, NULL);
	pthread_join(monitor_thread, NULL);
	pthread_mutex_destroy(&p_mut);
	pthread_mutex_destroy(&death_mut);
	free(philo_routines);
}

static t_p_routine	*create_philo_routines(t_data *data, t_philo **philos,
	pthread_mutex_t *p_mut, pthread_mutex_t *death_mut)
{
	t_p_routine	*routines;
	int			i;

	routines = (t_p_routine *)ft_calloc(data->philo_cnt + 1,
			sizeof(t_p_routine));
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
		routines[i].philo_cnt = data->philo_cnt;
	}
	return (routines);
}

static void	create_monitor_routine(t_m_routine *r, t_data *data,
				t_philo **philos)
{
	r->ms_start_time = data->ms_start_time;
	r->philo_cnt = data->philo_cnt;
	r->philos = philos;
	r->some_died = &data->some_died;
}

static bool	start_threads(t_data *data, t_philo **philos,
	t_p_routine *routines)
{
	int					i;

	i = -1;
	while (++i < philo_cnt)
	{
		philos[i]->thread = (pthread_t *)malloc(sizeof(pthread_t));
		if (!philos[i]->thread)
			return (false);
		pthread_create(philos[i]->thread, NULL, philo_routine,
			(void *)&routines[i]);
		printf("thread created\n");
		printf("philo %d started\n", i + 1);
		printf("----------------\n");
	}
	return (true);
}

static void	handle_thread_error(t_data *data, t_philo **philos,
	t_fork **forks, t_p_routine *routines)
{
	printf("\033[0;31mError: malloc failed\033[0m\n");
	free_resources(data, philos, forks);
	free(routines);
	exit(1);
}
