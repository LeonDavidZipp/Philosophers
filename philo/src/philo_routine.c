/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 21:17:28 by lzipp             #+#    #+#             */
/*   Updated: 2024/02/05 00:38:08 by lzipp            ###   ########.fr       */
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

const void	philo_eat(t_philo *philo);
const void	philo_sleep(t_philo *philo);
const void	philo_death(t_philo *philo);

void	philo_routine(t_philo *philo, t_data *data)
{
	while (true)
	{
		think_message(get_time(), philo->id);
		philo_eat(philo);
		philo_sleep(philo);
		if (philo->must_eat_cnt > 0)
			philo->must_eat_cnt--;
	}
}

const void	philo_eat(t_philo *philo)
{
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
	eat_message(get_time(), philo->id);
	usleep(philo->ms_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

const void	philo_sleep(t_philo *philo)
{
	sleep_message(get_time(), philo->id);
	usleep(philo->ms_to_sleep);
}

const void	philo_death(t_philo *philo)
{
	death_message(get_time(), philo->id);
}
