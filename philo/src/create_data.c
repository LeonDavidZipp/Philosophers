/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 12:12:54 by lzipp             #+#    #+#             */
/*   Updated: 2024/02/06 12:57:21 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int		ft_atoi(const char *str);
static void		fill_data(t_data *data, int argc, char **argv);

t_data	*create_data(int argc, char **argv)
{
	t_data	*data;

	if (argc != 5 && argc != 6)
	{
		printf("\033[0;31mUsage: ./philo nr_of_philos t_to_die t_to_eat");
		printf(" t_to_sleep [nr_must_eat]\033[0m\n");
		exit(1);
	}
	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
	{
		printf("\033[0;31mError: malloc failed\033[0m\n");
		exit(1);
	}
	fill_data(data, argc, argv);
	return (data);
}

static void	fill_data(t_data *data, int argc, char **argv)
{
	data->philo_cnt = ft_atoi(argv[1]);
	data->fork_cnt = data->philo_cnt;
	data->ms_to_die = ft_atoi(argv[2]);
	data->ms_to_eat = ft_atoi(argv[3]);
	data->ms_to_sleep = ft_atoi(argv[4]);
	data->must_eat_cnt = -1;
	if (argc == 6)
		data->must_eat_cnt = ft_atoi(argv[5]);
	if (data->philo_cnt < 1 || data->ms_to_die < 1 || data->ms_to_eat < 1
		|| data->ms_to_sleep < 1 || (argc == 6 && data->must_eat_cnt < 1))
	{
		printf("\033[0;31mError: invalid arguments\033[0m\n");
		free(data);
		exit(1);
	}
	data->start_time = get_time();
}

static int	ft_atoi(const char *str)
{
	int		i;
	int		sign;
	int		result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == ' ' || str[i] == '\f' || str[i] == '\n'
		|| str[i] == '\r' || str[i] == '\t' || str[i] == '\v')
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			break ;
		result = (result * 10) + (str[i] - '0');
		i++;
	}
	return ((result * sign));
}
