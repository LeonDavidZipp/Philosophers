/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 14:58:44 by lzipp             #+#    #+#             */
/*   Updated: 2024/02/04 15:02:26 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

long long	get_time(void)
{
	struct timeval		*tv;
	long long			ms;

	tv = (struct timeval *)malloc(sizeof(struct timeval));
	gettimeofday(tv, NULL);
	ms = tv->tv_sec * 1000LL + tv->tv_usec / 1000LL;
	free(tv);
	return (ms);
}
