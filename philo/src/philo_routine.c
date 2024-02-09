/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 21:17:28 by lzipp             #+#    #+#             */
/*   Updated: 2024/02/09 16:29:46 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	philo_eat(t_routine *r);
static void	philo_sleep(t_routine *r);
static void	philo_death(t_routine *r, long long time);
static bool	check_alive(t_routine *r, long long time);

void	*philo_routine(void *r_void)
{
	t_routine	*r;

	r = (t_routine *)r_void;
	while ((r->philo->must_eat_cnt == -1 || r->philo->must_eat_cnt > 0)
		&& *r->some_died == false)
	{
		if (!check_alive(r, get_time()))
			break ;
		think_message(get_time() - r->start_time, r);
		if (!check_alive(r, get_time()))
			break ;
		philo_eat(r);
		if (!check_alive(r, get_time()))
			break ;
		philo_sleep(r);
		if (r->philo->must_eat_cnt > 0)
			r->philo->must_eat_cnt--;
	}
	return (NULL);
}

static void	philo_eat(t_routine *r)
{
	long long	ms_new_ate_at;

	if (r->philo->id % 2 == 0)
	{
		pthread_mutex_lock(r->philo->left_fork);
		fork_message(get_time() - r->start_time, r);
		pthread_mutex_lock(r->philo->right_fork);
		fork_message(get_time() - r->start_time, r);
	}
	else
	{
		pthread_mutex_lock(r->philo->right_fork);
		fork_message(get_time() - r->start_time, r);
		pthread_mutex_lock(r->philo->left_fork);
		fork_message(get_time() - r->start_time, r);
	}
	ms_new_ate_at = get_time();
	r->philo->ms_last_ate_at = ms_new_ate_at + r->philo->ms_to_eat;
	eat_message(ms_new_ate_at - r->start_time, r);
	ft_usleep(r->philo->ms_to_eat);
	pthread_mutex_unlock(r->philo->left_fork);
	pthread_mutex_unlock(r->philo->right_fork);
}

static void	philo_sleep(t_routine *r)
{
	sleep_message(get_time() - r->start_time, r);
	ft_usleep(r->philo->ms_to_sleep);
}

static void	philo_death(t_routine *r, long long time)
{
	death_message(time - r->start_time, r);
	*r->some_died = true;
}

static bool	check_alive(t_routine *r, long long time)
{
	pthread_mutex_lock(r->death_mut);
	if (time - r->philo->ms_last_ate_at > r->philo->ms_to_die)
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
