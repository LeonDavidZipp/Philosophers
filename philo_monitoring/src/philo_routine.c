/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 21:17:28 by lzipp             #+#    #+#             */
/*   Updated: 2024/02/10 14:08:13 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	philo_eat(t_philo *philo);
static void	philo_sleep(t_philo *philo);
static bool	check_alive(t_philo *philo);

/// @brief Philosopher routine
/// @param philo_void philosopher struct
/// @return void*
/// @note combines eating, sleeping, thinking & dying
void	*philo_routine(void *philo_void)
{
	t_philo			*philo;

	philo = (t_philo *)philo_void;
	while ((philo->must_eat_cnt == -1 || philo->must_eat_cnt > 0)
		&& !philo->is_dead)
	{
		if (!check_alive(philo))
			break ;
		send_data(philo->id, get_time(), 0, philo->monitor_data);
		if (!check_alive(philo))
			break ;
		philo_eat(philo);
		if (!check_alive(philo))
			break ;
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
		send_data(philo->id, get_time(), 4, philo->monitor_data);
		pthread_mutex_lock(philo->right_fork);
		send_data(philo->id, get_time(), 4, philo->monitor_data);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		send_data(philo->id, get_time(), 4, philo->monitor_data);
		pthread_mutex_lock(philo->left_fork);
		send_data(philo->id, get_time(), 4, philo->monitor_data);
	}
	ms_new_ate_at = get_time();
	send_data(philo->id, get_time(), 4, philo->monitor_data);
	philo->ms_last_ate_at = ms_new_ate_at + philo->ms_to_eat;
	ft_usleep(philo->ms_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

static void	philo_sleep(t_philo *philo)
{
	send_data(philo->id, get_time(), 2, philo->monitor_data);
	ft_usleep(philo->ms_to_sleep);
}

static bool	check_alive(t_philo *philo)
{
	long long	time;

	time = get_time();
	if (time - philo->ms_last_ate_at >= philo->ms_to_die)
	{
		send_data(philo->id, get_time(), 3, philo->monitor_data);
		philo->is_dead = true;
		return (false);
	}
	return (true);
}

/// @brief Sends data to the monitoring thread
/// @param id current philo id
/// @param ms current time in ms
/// @param activity current activity: 0 - thinking, 1 - eating,
/// 2 - sleeping, 3 - died, 4 - took a fork
void	send_data(t_philo *philo, long long ms, int act, t_monitor_data *data)
{
	pthread_mutex_lock(philo->send_mutex);
	data->id = philo->id;
	data->ms_time = ms;
	data->activity = act;
	if (act == 3)
		data->some_died = true;
	pthread_mutex_unlock(philo->send_mutex);
}
