/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 21:17:28 by lzipp             #+#    #+#             */
/*   Updated: 2024/02/08 17:16:35 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	philo_eat(t_routine *r);
static void	philo_sleep(t_routine *r);
static void	philo_death(t_routine *r);
static bool	check_alive(t_routine *r, long long time);

void	*philo_routine(void *r_void)
{
	t_routine	*r;

	r = (t_routine *)r_void;
	while ((r->philo->must_eat_cnt == -1 || r->philo->must_eat_cnt > 0)
		&& *r->some_died == false)
	{
		check_alive(r, get_time());
		if (*r->some_died)
			break ;
		think_message(get_time() - r->start_time, r);
		if (*r->some_died)
			break ;
		check_alive(r, get_time());
		philo_eat(r);
		if (*r->some_died)
			break ;
		philo_sleep(r);
		if (*r->some_died)
			break ;
		if (r->philo->must_eat_cnt > 0)
			r->philo->must_eat_cnt--;
	}
	return (NULL);
}

static void	philo_eat(t_routine *r)
{
	long long	ms_new_ate_at;

	ms_new_ate_at = get_time();
	check_alive(r, ms_new_ate_at);
	if (*r->some_died)
		return ;
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
	r->philo->ms_last_ate_at = ms_new_ate_at + r->philo->ms_to_eat;
	eat_message(get_time() - r->start_time, r);
	ft_usleep(r->philo->ms_to_eat);
	pthread_mutex_unlock(r->philo->left_fork);
	pthread_mutex_unlock(r->philo->right_fork);
}

static void	philo_sleep(t_routine *r)
{
	check_alive(r, get_time());
	sleep_message(get_time() - r->start_time, r);
	ft_usleep(r->philo->ms_to_sleep);
}

static void	philo_death(t_routine *r)
{
	death_message(get_time() - r->start_time, r);
	*r->some_died = true;
}

static bool	check_alive(t_routine *r, long long time)
{
	pthread_mutex_lock(r->death_mut);
	if (time - r->philo->ms_last_ate_at > r->philo->ms_to_die)
	{
		philo_death(r);
		pthread_mutex_unlock(r->death_mut);
		return (false);
	}
	if (time > 0)
		r->philo->ms_last_ate_at = time;
	pthread_mutex_unlock(r->death_mut);
	return (true);
}
