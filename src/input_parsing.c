/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 12:12:54 by lzipp             #+#    #+#             */
/*   Updated: 2024/02/04 12:24:50 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	check_arg_num(int argc, unsigned int req, unsigned int max)
{
	if (argc < req)
	{
		write(2, "Error: too few arguments\n", 26);
		return (1);
	}
	if (argc > max)
	{
		write(2, "Error: too many arguments\n", 27);
		return (1);
	}
	return (0);
}

int	ft_atoi(const char *str)
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
