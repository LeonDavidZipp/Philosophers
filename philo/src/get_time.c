/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 14:58:44 by lzipp             #+#    #+#             */
/*   Updated: 2024/02/05 00:36:24 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

long long	get_time(void)
{
	struct timeval		*time;
	long long			ms;

	time = (struct timeval *)malloc(sizeof(struct timeval));
	gettimeofday(time, NULL);
	ms = time->tv_sec * 1000LL + time->tv_usec / 1000LL;
	free(time);
	return (ms);
}
