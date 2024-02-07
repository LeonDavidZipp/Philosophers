/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 21:17:28 by lzipp             #+#    #+#             */
/*   Updated: 2024/02/07 18:29:36 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static bool	check_alive(t_routine *r, long long time);
static void	philo_eat(t_routine *r);
static void	philo_sleep(t_routine *r);
static void	philo_death(t_routine *r);

void	*philo_routine(void *r_void)
{
	t_routine	*r;
	bool		is_alive;

	is_alive = true;
	r = (t_routine *)r_void;
	while ((r->philo->must_eat_cnt == -1 || r->philo->must_eat_cnt > 0)
		&& *r->some_died == false)
	{
		is_alive = check_alive(r, get_time());
		if (*r->some_died)
			break ;
		think_message(get_time(), r->philo->id, r->p_mut);
		if (*r->some_died)
			break ;
		philo_eat(r);
		if (*r->some_died)
			break ;
		philo_sleep(r);
		if (*r->some_died)
			break ;
		if (r->philo->must_eat_cnt > 0)
			r->philo->must_eat_cnt--;
	}
	return (NULL);
}

static bool	check_alive(t_routine *r, long long time)
{
	if (time - r->philo->ms_last_ate_at > r->philo->ms_to_die)
	{
		philo_death(r);
		return (false);
	}
	if (time > 0)
		r->philo->ms_last_ate_at = time;
	return (true);
}
