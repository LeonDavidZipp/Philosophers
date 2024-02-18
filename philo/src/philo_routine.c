/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 21:17:28 by lzipp             #+#    #+#             */
/*   Updated: 2024/02/18 20:46:27 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	philo_eat(t_routine *r);
static void	philo_sleep(t_routine *r);
static bool	philo_take_forks(t_routine *r);
static bool	check_alive(t_routine *r);

void	*philo_routine(void *r_void)
{
	t_routine	*r;

	r = (t_routine *)r_void;
	if (r->philo->id % 2 == 0)
		ft_usleep(10);
	while ((r->philo->must_eat_cnt == -1 || r->philo->must_eat_cnt > 0)
		&& r->philo->is_dead == false)
	{
		if (!check_alive(r))
			return (NULL);
		think_message(get_time() - r->ms_start_time, r);
		if (!philo_take_forks(r))
			return (NULL);
		// if (!check_alive(r))
		// {
		// 	pthread_mutex_unlock(r->philo->left_fork->mutex);
		// 	pthread_mutex_unlock(r->philo->right_fork->mutex);
		// 	return (NULL);
		// }
		philo_eat(r);
		if (!check_alive(r))
			return (NULL);
		philo_sleep(r);
	}
	return (NULL);
}

static bool	philo_take_forks(t_routine *r)
{
	if (!check_alive(r))
		return (false);
	pthread_mutex_lock(r->philo->left_fork->mutex);
	if (!check_alive(r))
	{
		pthread_mutex_unlock(r->philo->left_fork->mutex);
		return (false);
	}
	fork_message(get_time() - r->ms_start_time, r);
	pthread_mutex_lock(r->philo->right_fork->mutex);
	if (!check_alive(r))
	{
		pthread_mutex_unlock(r->philo->left_fork->mutex);
		pthread_mutex_unlock(r->philo->right_fork->mutex);
		return (false);
	}
	fork_message(get_time() - r->ms_start_time, r);
	return (true);
}

static void	philo_eat(t_routine *r)
{
	long long	ms_new_ate_at;

	ms_new_ate_at = get_time();
	r->philo->ms_last_ate_at = ms_new_ate_at;
	eat_message(ms_new_ate_at - r->ms_start_time, r);
	if (r->philo->must_eat_cnt > 0)
		r->philo->must_eat_cnt--;
	ft_usleep(r->philo->ms_to_eat);
	pthread_mutex_unlock(r->philo->left_fork->mutex);
	pthread_mutex_unlock(r->philo->right_fork->mutex);
}

static void	philo_sleep(t_routine *r)
{
	// sleep_message(get_time() - r->ms_start_time, r);
	// ft_usleep(r->philo->ms_to_sleep);
	long long start_time = get_time();
	long long end_time = start_time + r->philo->ms_to_sleep;
	long long time;

	sleep_message(start_time - r->ms_start_time, r);
	time = get_time();
	while (time < end_time)
	{
		if (!check_alive(r))
			break;
		ft_usleep(1); // sleep for a very short time
		time = get_time();
	}
}

// static bool	check_alive(t_routine *r)
// {
// 	long long	time;

// 	time = get_time();
// 	pthread_mutex_lock(r->death_mut);
// 	if (time - r->philo->ms_last_ate_at >= r->philo->ms_to_die)
// 		r->philo->is_dead = true;
// 	if (r->philo->is_dead == true && *r->some_died == false)
// 	{
// 		death_message(time - r->ms_start_time, r);
// 		*r->some_died = true;
// 		pthread_mutex_unlock(r->death_mut);
// 		return (false);
// 	}
// 	pthread_mutex_unlock(r->death_mut);
// 	return (true);
// }

static bool	check_alive(t_routine *r)
{
	long long	time;

	time = get_time();
	pthread_mutex_lock(r->p_mut);
	pthread_mutex_lock(r->death_mut);
	if (time - r->philo->ms_last_ate_at >= r->philo->ms_to_die)
		r->philo->is_dead = true;
	if (*r->some_died == true)
	{
		pthread_mutex_unlock(r->death_mut);
		pthread_mutex_unlock(r->p_mut);
		return (false);
	}
	if (r->philo->is_dead == true && *r->some_died == false)
	{
		death_message(time - r->ms_start_time, r);
		*r->some_died = true;
		pthread_mutex_unlock(r->death_mut);
		pthread_mutex_unlock(r->p_mut);
		return (false);
	}
	pthread_mutex_unlock(r->death_mut);
	pthread_mutex_unlock(r->p_mut);
	return (true);
}
