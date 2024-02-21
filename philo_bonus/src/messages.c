/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 13:59:31 by lzipp             #+#    #+#             */
/*   Updated: 2024/02/21 18:31:20 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	fork_message(long long ms, int id)
{
	printf("\033[0;36m");
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
	printf("\033[0;35m");
	printf("%lld %d is sleeping", ms, id);
	printf("\033[0m\n");
}

void	think_message(long long ms, int id)
{
	printf("\033[0;33m");
	printf("%lld %d is thinking", ms, id);
	printf("\033[0m\n");
}

void	death_message(long long ms, int id)
{
	printf("\033[0;31m");
	printf("%lld %d died", ms, id);
	printf("\033[0m\n");
}
