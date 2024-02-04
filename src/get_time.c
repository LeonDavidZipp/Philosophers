/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 14:58:44 by lzipp             #+#    #+#             */
/*   Updated: 2024/02/04 14:59:05 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

long long	get_time(void)
{
	struct timeval		*tv;
	long long			ms;

	gettimeofday(tv, NULL);
	ms = tv->tv_sec * 1000LL + tv->tv_usec / 1000LL;
	free(tv);
	return (ms);
}
