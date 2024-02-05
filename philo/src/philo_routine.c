/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 21:17:28 by lzipp             #+#    #+#             */
/*   Updated: 2024/02/05 18:57:01 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

// philo_routine()
// {
// 	while (true)
// 	{
// 		think()
// 		{
// 			print is thinking;
// 			wait till fork_left and fork_right are available;
// 		}
// 		take_forks();
// 		eat()
// 		{
// 			print is eating;
// 			wait for ms_to_eat;
// 		}
// 		put_forks_back();
// 		sleep()
// 		{
// 			print is sleeping;
// 			wait for ms_to_sleep;
// 		}
// 		if (must_eat_cnt > 0)
// 		{
// 			must_eat_cnt--;
// 		}
// 	}
// }

static bool	check_alive(t_philo *philo, long long time, pthread_mutex_t *p_mut);
static bool	philo_eat(t_philo *philo, pthread_mutex_t *p_mut);
static bool	philo_sleep(t_philo *philo, pthread_mutex_t *p_mut);
static void	philo_death(t_philo *philo, pthread_mutex_t *p_mut);

void	philo_routine(t_philo *philo, pthread_mutex_t *p_mut)
{
	bool	is_alive;

	is_alive = true;
	while (true && (philo->must_eat_cnt == -1 || philo->must_eat_cnt > 0))
	{
		think_message(get_time(), philo->id, p_mut);
		is_alive = philo_eat(philo, p_mut);
		if (!is_alive)
			break ;
		is_alive = philo_sleep(philo, p_mut);
		if (!is_alive)
			break ;
		if (philo->must_eat_cnt > 0)
			philo->must_eat_cnt--;
	}
}

static bool	philo_eat(t_philo *philo, pthread_mutex_t *p_mut)
{
	long long	ms_new_ate_at;

	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->right_fork);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(philo->left_fork);
	}
	ms_new_ate_at = get_time();
	if (ms_new_ate_at - philo->ms_last_ate_at > philo->ms_to_die)
	{
		philo_death(philo, p_mut);
		return (false);
	}
	philo->ms_last_ate_at = ms_new_ate_at;
	eat_message(philo->ms_last_ate_at, philo->id, p_mut);
	usleep(philo->ms_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return (true);
}

static bool	philo_sleep(t_philo *philo, pthread_mutex_t *p_mut)
{
	sleep_message(get_time(), philo->id, p_mut);
	usleep(philo->ms_to_sleep);
	return (check_alive(philo, -1, p_mut));
}

static void	philo_death(t_philo *philo, pthread_mutex_t *p_mut)
{
	death_message(get_time(), philo->id, p_mut);
}

static bool	check_alive(t_philo *philo, long long time, pthread_mutex_t *p_mut)
{
	if (time == -1)
		time = get_time();
	if (time - philo->ms_last_ate_at > philo->ms_to_die)
	{
		philo_death(philo, p_mut);
		return (false);
	}
	if (time > 0)
		philo->ms_last_ate_at = time;
	return (true);
}
