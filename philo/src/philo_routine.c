/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 21:17:28 by lzipp             #+#    #+#             */
/*   Updated: 2024/02/06 21:53:42 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static bool	check_alive(t_philo *philo, long long time, pthread_mutex_t *p_mut);
static bool	philo_eat(t_routine *routine);
static bool	philo_sleep(t_philo *philo, pthread_mutex_t *p_mut);
static void	philo_death(t_routine *routine);

bool	philo_routine(t_routine *routine)
{
	bool	is_alive;

	is_alive = true;
	while (routine->philo->must_eat_cnt == -1
		|| routine->philo->must_eat_cnt > 0)
	{
		think_message(get_time(), routine->philo->id, routine->p_mut);
		is_alive = philo_eat(routine);
		if (!is_alive)
			break ;
		is_alive = philo_sleep(routine->philo, routine->p_mut);
		if (!is_alive)
			break ;
		if (routine->philo->must_eat_cnt > 0)
			routine->philo->must_eat_cnt--;
	}
	routine->some_died = !is_alive;
}

static bool	philo_eat(t_routine *routine)
{
	long long	ms_new_ate_at;

	if (routine->philo->id % 2 == 0)
	{
		pthread_mutex_lock(routine->philo->left_fork);
		pthread_mutex_lock(routine->philo->right_fork);
	}
	else
	{
		pthread_mutex_lock(routine->philo->right_fork);
		pthread_mutex_lock(routine->philo->left_fork);
	}
	ms_new_ate_at = get_time();
	if (ms_new_ate_at - routine->philo->ms_last_ate_at > routine->philo->ms_to_die)
	{
		philo_death(routine);
		return (false);
	}
	routine->philo->ms_last_ate_at = ms_new_ate_at;
	eat_message(routine->philo->ms_last_ate_at, routine->philo->id, routine->p_mut);
	usleep(routine->philo->ms_to_eat);
	pthread_mutex_unlock(routine->philo->left_fork);
	pthread_mutex_unlock(routine->philo->right_fork);
	return (true);
}

static bool	philo_sleep(t_routine *routine)
{
	sleep_message(get_time(), routine->philo->id, routine->p_mut);
	usleep(routine->philo->ms_to_sleep);
	return (check_alive(routine, -1));
}

static void	philo_death(t_routine *routine)
{
	death_message(get_time(), routine->philo->id, routine->p_mut);
	pthread_mutex_lock(routine->death_mut);
	routine->some_died = true;
	pthread_mutex_unlock(routine->death_mut);
}

static bool	check_alive(t_routine *routine, long long time)
{
	if (time == -1)
		time = get_time();
	if (time - routine->philo->ms_last_ate_at > routine->philo->ms_to_die)
	{
		philo_death(routine);
		return (false);
	}
	if (time > 0)
		routine->philo->ms_last_ate_at = time;
	return (true);
}
