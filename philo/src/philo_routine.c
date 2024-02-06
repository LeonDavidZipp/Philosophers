/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 21:17:28 by lzipp             #+#    #+#             */
/*   Updated: 2024/02/06 22:36:56 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	check_alive(t_routine *r, long long time);
static void	philo_eat(t_routine *r);
static void	philo_sleep(t_routine *r);
static void	philo_death(t_routine *r);

bool	philo_routine(t_routine *r)
{
	bool	is_alive;

	is_alive = true;
	while ((r->philo->must_eat_cnt == -1
			|| r->philo->must_eat_cnt > 0) && *r->some_died == false)
	{
		check_alive(r, -1);
		if (*r->some_died)
			break ;
		think_message(get_time(), r->philo->id, r->p_mut);
		philo_eat(r);
		if (*r->some_died)
			break ;
		philo_sleep(r);
		if (*r->some_died)
			break ;
		if (r->philo->must_eat_cnt > 0)
			r->philo->must_eat_cnt--;
	}
}

static void	philo_eat(t_routine *r)
{
	long long	ms_new_ate_at;

	if (r->philo->id % 2 == 0)
	{
		pthread_mutex_lock(r->philo->left_fork);
		pthread_mutex_lock(r->philo->right_fork);
	}
	else
	{
		pthread_mutex_lock(r->philo->right_fork);
		pthread_mutex_lock(r->philo->left_fork);
	}
	ms_new_ate_at = get_time();
	check_alive(r, ms_new_ate_at);
	eat_message(r->philo->ms_last_ate_at, r->philo->id, r->p_mut);
	r->philo->ms_last_ate_at = ms_new_ate_at + r->philo->ms_to_eat;
	usleep(r->philo->ms_to_eat);
	pthread_mutex_unlock(r->philo->left_fork);
	pthread_mutex_unlock(r->philo->right_fork);
}

static void	philo_sleep(t_routine *r)
{
	sleep_message(get_time(), r->philo->id, r->p_mut);
	usleep(r->philo->ms_to_sleep);
	return (check_alive(r, -1));
}

static void	philo_death(t_routine *r)
{
	death_message(get_time(), r->philo->id, r->p_mut);
	pthread_mutex_lock(r->death_mut);
	r->some_died = true;
	pthread_mutex_unlock(r->death_mut);
}

static void	check_alive(t_routine *r, long long time)
{
	if (time == -1)
		time = get_time();
	if (time - r->philo->ms_last_ate_at > r->philo->ms_to_die)
		philo_death(r);
	if (time > 0)
		r->philo->ms_last_ate_at = time;
}
