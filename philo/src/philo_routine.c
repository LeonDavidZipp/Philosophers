/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 21:17:28 by lzipp             #+#    #+#             */
/*   Updated: 2024/02/10 16:30:24 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	philo_eat(t_routine *r);
static void	philo_sleep(t_routine *r);
static bool	check_alive(t_routine *r);

void	*philo_routine(void *r_void)
{
	t_routine	*r;

	r = (t_routine *)r_void;
	while ((r->philo->must_eat_cnt == -1 || r->philo->must_eat_cnt > 0)
		&& *r->some_died == false && r->philo->is_dead == false)
	{
		if (!check_alive(r))
			break ;
		think_message(get_time() - r->start_time, r);
		if (!check_alive(r))
			break ;
		philo_eat(r);
		if (!check_alive(r))
			break ;
		philo_sleep(r);
	}
	return (NULL);
}

static void	philo_eat(t_routine *r)
{
	long long	ms_new_ate_at;

	if (r->philo->id % 2 == 0)
	{
		pthread_mutex_lock(r->philo->left_fork->mutex);
		fork_message(get_time() - r->start_time, r);
		pthread_mutex_lock(r->philo->right_fork->mutex);
		fork_message(get_time() - r->start_time, r);
	}
	else
	{
		pthread_mutex_lock(r->philo->right_fork->mutex);
		fork_message(get_time() - r->start_time, r);
		pthread_mutex_lock(r->philo->left_fork->mutex);
		fork_message(get_time() - r->start_time, r);
	}
	ms_new_ate_at = get_time();
	r->philo->ms_last_ate_at = ms_new_ate_at + r->philo->ms_to_eat;
	eat_message(ms_new_ate_at - r->start_time, r);
	if (r->philo->must_eat_cnt > 0)
		r->philo->must_eat_cnt--;
	ft_usleep(r->philo->ms_to_eat);
	pthread_mutex_unlock(r->philo->left_fork->mutex);
	pthread_mutex_unlock(r->philo->right_fork->mutex);
}

static void	philo_sleep(t_routine *r)
{
	sleep_message(get_time() - r->start_time, r);
	ft_usleep(r->philo->ms_to_sleep);
}

static bool	check_alive(t_routine *r)
{
	long long	time;

	time = get_time();
	pthread_mutex_lock(r->death_mut);
	if (time - r->philo->ms_last_ate_at >= r->philo->ms_to_die)
		r->philo->is_dead = true;
	if (r->philo->is_dead == true && *r->some_died == false)
	{
		*r->some_died = true;
		pthread_mutex_unlock(r->death_mut);
		return (false);
	}
	pthread_mutex_unlock(r->death_mut);
	return (true);
}
