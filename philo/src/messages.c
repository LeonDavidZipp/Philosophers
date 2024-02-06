/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 13:59:31 by lzipp             #+#    #+#             */
/*   Updated: 2024/02/06 13:29:55 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	fork_message(long long ms, int id, pthread_mutex_t p_mut)
{
	pthread_mutex_lock(&p_mut);
	printf("\033[0;34m");
	printf("%lld %d has taken a fork", ms, id);
	printf("\033[0m\n");
	pthread_mutex_unlock(&p_mut);
}

void	eat_message(long long ms, int id, pthread_mutex_t p_mut)
{
	pthread_mutex_lock(&p_mut);
	printf("\033[0;32m");
	printf("%lld %d is eating", ms, id);
	printf("\033[0m\n");
	pthread_mutex_unlock(&p_mut);
}

void	sleep_message(long long ms, int id, pthread_mutex_t p_mut)
{
	pthread_mutex_lock(&p_mut);
	printf("\033[0;34m");
	printf("%lld %d is sleeping", ms, id);
	printf("\033[0m\n");
	pthread_mutex_unlock(&p_mut);
}

void	think_message(long long ms, int id, pthread_mutex_t p_mut)
{
	pthread_mutex_lock(&p_mut);
	printf("\033[0;34m");
	printf("%lld %d is thinking", ms, id);
	printf("\033[0m\n");
	pthread_mutex_unlock(&p_mut);
}

void	death_message(long long ms, int id, pthread_mutex_t p_mut)
{
	pthread_mutex_lock(&p_mut);
	printf("\033[0;31m");
	printf("%lld %d died", ms, id);
	printf("\033[0m\n");
	pthread_mutex_unlock(&p_mut);
}
