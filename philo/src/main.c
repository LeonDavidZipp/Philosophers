/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 12:48:08 by lzipp             #+#    #+#             */
/*   Updated: 2024/02/06 22:02:44 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	start_threads(t_data *data, t_philo **philos,
				t_routine *routines, pthread_mutex_t *p_mut);
static void	philosophize(t_data *data, t_philo **philos,
				pthread_mutex_t **forks);

int	main(int argc, char **argv)
{
	t_data				*data;
	t_philo				**philos;
	pthread_mutex_t		**forks;

	data = create_data(argc, argv);
	forks = create_forks(data);
	philos = create_philos(data, forks);
	philosophize(data, philos, forks);
	cleanup(data, forks, philos);
	return (0);
}
