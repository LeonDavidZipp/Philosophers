/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 13:59:31 by lzipp             #+#    #+#             */
/*   Updated: 2024/02/04 14:14:39 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


// timestamp_in_ms X has taken a fork
// ◦ timestamp_in_ms X is eating
// ◦ timestamp_in_ms X is sleeping
// ◦ timestamp_in_ms X is thinking
// ◦ timestamp_in_ms X died
#include "../inc/philo.h"

void	fork_message(long long ms, int id)
{
	printf("\033[0;34m");
	printf("%lld %d has taken a fork", ms, id);
	printf("\033[0m\n");
}

void	eat_message(long long ms, int id)
{
	printf("\033[0;32m");
	printf("%lld %d is eating", ms, id);
	printf("\033[0m\n");
}

void	sleep_message(long long ms, int id)
{
	printf("\033[0;34m");
	printf("%lld %d is sleeping", ms, id);
	printf("\033[0m\n");
}

void	think_message(long long ms, int id)
{
	printf("\033[0;34m");
	printf("%lld %d is thinking", ms, id);
	printf("\033[0m\n");
}

void	death_message(long long ms, int id)
{
	printf("\033[0;31m");
	printf("%lld %d died", ms, id);
	printf("\033[0m\n");
}
