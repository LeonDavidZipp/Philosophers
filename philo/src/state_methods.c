/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_methods.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 21:17:28 by lzipp             #+#    #+#             */
/*   Updated: 2024/02/04 22:01:48 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	philo_think(t_philo *philo)
{
	think_message(get_time(), philo->id);
	pthread_mutex_lock(mutex);
}

void	philo_eat(t_philo *philo, pthread_mutex_t *mutex)
{
	eat_message(get_time(), philo->id);
	usleep(philo->ms_to_eat);
}

void	philo_sleep(t_philo *philo)
{
	sleep_message(get_time(), philo->id);
	usleep(philo->ms_to_sleep);
}

void	philo_death(void)
{
	death_message(get_time(), id);
}

