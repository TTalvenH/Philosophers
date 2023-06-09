/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_int.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttalvenh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 13:31:05 by ttalvenh          #+#    #+#             */
/*   Updated: 2023/06/28 15:51:53 by ttalvenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	check_max_min(int i, int next_digit)
{
	if (i >= 0)
	{
		if (i > INT_MAX / 10
			|| (i == INT_MAX / 10 && next_digit > INT_MAX % 10))
			return (1);
	}
	else
	{
		if (i < INT_MIN / 10
			|| (i == INT_MIN / 10 && - next_digit < INT_MIN % -10))
			return (1);
	}
	return (0);
}

int	parse_int(char *str, t_data *var)
{
	int	i;
	int	sign;

	i = 0;
	sign = 1;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
		if (!*str)
			error(NULL, var);
	}
	while (*str != '\0')
	{
		if (!(*str >= '0' && *str <= '9') || check_max_min(i, *str - '0'))
			error(NULL, var);
		i = i * 10 + (*str - '0') * sign;
		str++;
	}
	return (i);
}
