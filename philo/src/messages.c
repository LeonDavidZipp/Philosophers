/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 13:59:31 by lzipp             #+#    #+#             */
/*   Updated: 2024/02/18 18:24:27 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	fork_message(long long ms, t_routine *r)
{
	bool	some_died;

	pthread_mutex_lock(r->p_mut);
	pthread_mutex_lock(r->death_mut);
	some_died = *r->some_died;
	pthread_mutex_unlock(r->death_mut);
	if (some_died)
	{
		pthread_mutex_unlock(r->p_mut);
		return ;
	}
	printf("\033[0;36m");
	printf("%lld %d has taken a fork", ms, r->philo->id);
	printf("\033[0m\n");
	pthread_mutex_unlock(r->p_mut);
}

void	eat_message(long long ms, t_routine *r)
{
	bool	some_died;

	pthread_mutex_lock(r->p_mut);
	pthread_mutex_lock(r->death_mut);
	some_died = *r->some_died;
	pthread_mutex_unlock(r->death_mut);
	if (some_died)
	{
		pthread_mutex_unlock(r->p_mut);
		return ;
	}
	printf("\033[0;32m");
	printf("%lld %d is eating", ms, r->philo->id);
	printf("\033[0m\n");
	pthread_mutex_unlock(r->p_mut);
}

void	sleep_message(long long ms, t_routine *r)
{
	bool	some_died;

	pthread_mutex_lock(r->p_mut);
	pthread_mutex_lock(r->death_mut);
	some_died = *r->some_died;
	pthread_mutex_unlock(r->death_mut);
	if (some_died)
	{
		pthread_mutex_unlock(r->p_mut);
		return ;
	}
	printf("\033[0;35m");
	printf("%lld %d is sleeping", ms, r->philo->id);
	printf("\033[0m\n");
	pthread_mutex_unlock(r->p_mut);
}

void	think_message(long long ms, t_routine *r)
{
	bool	some_died;

	pthread_mutex_lock(r->p_mut);
	pthread_mutex_lock(r->death_mut);
	some_died = *r->some_died;
	pthread_mutex_unlock(r->death_mut);
	if (some_died)
	{
		pthread_mutex_unlock(r->p_mut);
		return ;
	}
	printf("\033[0;33m");
	printf("%lld %d is thinking", ms, r->philo->id);
	printf("\033[0m\n");
	pthread_mutex_unlock(r->p_mut);
}

void	death_message(long long ms, t_routine *r)
{
	bool	some_died;

	some_died = *r->some_died;
	if (some_died)
		return ;
	// pthread_mutex_lock(r->p_mut);
	printf("\033[0;31m");
	printf("%lld %d died", ms, r->philo->id);
	printf("\033[0m\n");
	// pthread_mutex_unlock(r->p_mut);
}
