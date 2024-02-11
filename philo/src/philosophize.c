/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophize.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 22:02:21 by lzipp             #+#    #+#             */
/*   Updated: 2024/02/11 15:01:32 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	start_threads(t_data *data, t_philo **philos,
				t_routine *routines, pthread_mutex_t *p_mut);

void	philosophize(t_data *data, t_philo **philos,
	t_fork **forks)
{
	int					i;
	t_routine			*routines;
	pthread_mutex_t		p_mut;
	pthread_mutex_t		death_mut;

	pthread_mutex_init(&p_mut, NULL);
	pthread_mutex_init(&death_mut, NULL);
	routines = (t_routine *)ft_calloc(data->philo_cnt + 1, sizeof(t_routine));
	if (!routines || start_threads(data, philos, routines, &p_mut))
		handle_malloc_and_thread_error(data, philos, forks, routines);
	i = -1;
	while (++i < data->philo_cnt)
		pthread_join(*philos[i]->thread, NULL);
	pthread_mutex_destroy(&p_mut);
	pthread_mutex_destroy(&death_mut);
	free(routines);
}

static t_routine	*create_routines(t_data *data, t_philo **philos,
	t_fork **forks, pthread_mutex_t *p_mut)
{
	t_routine	*routines;
	int			i;

	routines = (t_routine *)ft_calloc(data->philo_cnt + 1, sizeof(t_routine));
	if (!routines)
	{
		ft_free_2d_arr((void **)philos);
		free_forks(forks);
		free(data);
		exit(1);
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

static int	start_threads(t_data *data, t_philo **philos,
	t_routine *routines, pthread_mutex_t *p_mut)
{
	int					i;
	pthread_mutex_t		*death_mut;

	death_mut = (pthread_mutex_t *)ft_calloc(1, sizeof(pthread_mutex_t));
	pthread_mutex_init(death_mut, NULL);
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
		routines[i].ms_start_time = data->ms_start_time;
		pthread_create(philos[i]->thread, NULL, philo_routine,
			(void *)&routines[i]);
	}
	pthread_mutex_destroy(death_mut);
	free(death_mut);
	return (0);
}

static void	handle_malloc_and_thread_error(t_data *data, t_philo **philos,
	t_fork **forks, t_routine *routines)
{
	printf("\033[0;31mError: malloc failed\033[0m\n");
	ft_free_2d_arr((void **)philos);
	free_forks(forks);
	free(routines);
	free(data);
	exit(1);
}
