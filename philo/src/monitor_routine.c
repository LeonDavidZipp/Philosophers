/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 17:44:33 by lzipp             #+#    #+#             */
/*   Updated: 2024/02/21 13:04:11 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static bool		monitor_death(t_m_routine *r);
static bool		monitor_all_ate(t_m_routine *r);

void	*monitor_routine(void *r_void)
{
	t_m_routine	*r;

	r = (t_m_routine *)r_void;
	while (true)
	{
		if (!monitor_death(r))
			return (NULL);
		if (monitor_all_ate(r))
			return (NULL);
	}
	return (NULL);
}

static bool	monitor_death(t_m_routine *r)
{
	int				i;
	long long		time;

	i = -1;
	while (++i < r->philo_cnt)
	{
		pthread_mutex_lock(r->p_mut);
		pthread_mutex_lock(r->death_mut);
		time = get_time();
		if (time - r->philos[i]->ms_last_ate_at >= r->philos[i]->ms_to_die)
		{
			*r->some_died = true;
			death_message(time - r->philos[i]->ms_start_time, r->philos[i]->id);
			pthread_mutex_unlock(r->p_mut);
			pthread_mutex_unlock(r->death_mut);
			return (false);
		}
		pthread_mutex_unlock(r->p_mut);
		pthread_mutex_unlock(r->death_mut);
	}
	return (true);
}

static bool	monitor_all_ate(t_m_routine *r)
{
	int	i;

	if (r->philos[0]->must_eat_cnt == -1)
		return (false);
	i = -1;
	while (++i < r->philo_cnt)
	{
		pthread_mutex_lock(r->philos[i]->eat_mut);
		if (r->philos[i]->must_eat_cnt > 0)
		{
			pthread_mutex_unlock(r->philos[i]->eat_mut);
			return (false);
		}
		pthread_mutex_unlock(r->philos[i]->eat_mut);
	}
	return (true);
}
