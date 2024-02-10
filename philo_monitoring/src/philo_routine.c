/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 21:17:28 by lzipp             #+#    #+#             */
/*   Updated: 2024/02/10 13:39:36 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	philo_eat(t_philo *philo);
static void	philo_sleep(t_philo *philo);
static void	philo_death(t_philo *philo);
static bool	check_alive(t_philo *philo);

void	*philo_routine(void *philo_void)
{
	t_philo			*philo;

	philo = (t_philo *)philo_void;
	while (philo->must_eat_cnt == -1 || philo->must_eat_cnt > 0)
	{
		check_alive(philo);
		philo_think(philo);
		check_alive(philo);
		philo_eat(philo);
		check_alive(philo);
		philo_sleep(philo);
		if (philo->must_eat_cnt > 0)
			philo->must_eat_cnt--;
	}
	return (NULL);
}

static void	philo_eat(t_philo *philo)
{
	long long	ms_new_ate_at;

	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->send_mutex);
		send_data(philo->id, get_time(), 4, philo->monitor_data);
		pthread_mutex_lock(philo->right_fork);
		send_data(philo->id, get_time(), 4, philo->monitor_data);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(philo->send_mutex);
		send_data(philo->id, get_time(), 4, philo->monitor_data);
		pthread_mutex_lock(philo->left_fork);
		send_data(philo->id, get_time(), 4, philo->monitor_data);
	}
	ms_new_ate_at = get_time();
	philo->ms_last_ate_at = ms_new_ate_at + philo->ms_to_eat;
	ft_usleep(philo->ms_to_eat);
	pthread_mutex_unlock(r->philo->left_fork);
	pthread_mutex_unlock(r->philo->right_fork);
}

static void	philo_sleep(t_philo *philo)
{
	pthread_mutex_lock(philo->send_mutex);
	send_data(philo->id, get_time(), 2, philo->monitor_data);
	pthread_mutex_unlock(philo->send_mutex);
	ft_usleep(philo->ms_to_sleep);
}

static void	philo_death(t_philo *philo)
{
	pthread_mutex_lock(philo->send_mutex);
	send_data(philo->id, get_time(), 3, philo->monitor_data);
	pthread_mutex_unlock(philo->send_mutex);
	philo->some_died = true;
}

static bool	check_alive(t_routine *r, long long time)
{
	pthread_mutex_lock(r->death_mut);
	// printf("timer for id %d\n", r->philo->id);
	// printf("death timer: %lld > %lld\n", time - r->philo->ms_last_ate_at, r->philo->ms_to_die);
	// printf("-------------------\n");
	if (time - r->philo->ms_last_ate_at >= r->philo->ms_to_die)
	{
		if (*r->some_died == false)
			philo_death(r, time);
		pthread_mutex_unlock(r->death_mut);
		return (false);
	}
	if (time > 0)
		r->philo->ms_last_ate_at = time;
	pthread_mutex_unlock(r->death_mut);
	return (true);
}

/// @brief Sends data to the monitoring thread
/// @param id current philo id
/// @param ms current time in ms
/// @param activity current activity: 0 - thinking, 1 - eating,
/// 2 - sleeping, 3 - died, 4 - took a fork
void	send_data(int id, long long ms, int activity, t_monitor_data *data)
{
	data->id = id;
	data->ms_time = ms;
	data->activity = activity;
}
