/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophize.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 22:02:21 by lzipp             #+#    #+#             */
/*   Updated: 2024/02/10 17:10:47 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	start_threads(int philo_cnt, t_philo **philos,
				t_routine *routines, pthread_mutex_t *p_mut);

void	philosophize(t_philo **philos, t_fork **forks)
{
	int					i;
	int					philo_cnt;
	t_routine			*routines;
	pthread_mutex_t		p_mut;

	philo_cnt = ft_null_terminated_arr_len((void **)philos);
	pthread_mutex_init(&p_mut, NULL);
	routines = (t_routine *)ft_calloc(philo_cnt + 1, sizeof(t_routine));
	if (!routines || start_threads(philo_cnt, philos, routines, &p_mut))
	{
		printf("\033[0;31mError: malloc failed\033[0m\n");
		ft_free_2d_arr((void **)philos);
		free_forks(forks);
		free(routines);
		exit(1);
	}
	i = -1;
	while (++i < philo_cnt)
		pthread_join(*philos[i]->thread, NULL);
	pthread_mutex_destroy(&p_mut);
	free(routines);
}

static int	start_threads(int philo_cnt, t_philo **philos,
	t_routine *routines, pthread_mutex_t *p_mut)
{
	int					i;
	pthread_mutex_t		*death_mut;

	death_mut = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (!death_mut)
		return (1);
	pthread_mutex_init(death_mut, NULL);
	i = -1;
	while (++i < philo_cnt)
	{
		philos[i]->thread = (pthread_t *)malloc(sizeof(pthread_t));
		if (!philos[i]->thread)
			return (1);
		routines[i].philo = philos[i];
		printf("philo assigned\n");
		routines[i].p_mut = p_mut;
		printf("mutex inited\n");
		routines[i].some_died = false;
		printf("some died assigned\n");
		routines[i].death_mut = death_mut;
		printf("death mut assigned\n");
		routines[i].start_time = philos[0]->ms_start_time;
		printf("start time assigned\n");
		pthread_create(philos[i]->thread, NULL, philo_routine,
			(void *)&routines[i]);
		printf("thread created\n");
		printf("philo %d started\n", i + 1);
		printf("----------------\n");
	}
	pthread_mutex_destroy(death_mut);
	free(death_mut);
	return (0);
}
