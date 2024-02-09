/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring_thread.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 18:33:49 by lzipp             #+#    #+#             */
/*   Updated: 2024/02/09 18:35:16 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*monitoring_routine(void *r_void)
{
	t_routine	*r;

	r = (t_routine *)r_void;
	while (*r->some_died == false)
	{
		pthread_mutex_lock(r->death_mut);
		if (get_time() - r->philo->last_ate_at > r->philo->time_to_die)
		{
			philo_death(r, get_time() - r->start_time);
			*r->some_died = true;
		}
		pthread_mutex_unlock(r->death_mut);
	}
	return (NULL);
}
