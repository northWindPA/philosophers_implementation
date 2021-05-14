/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhumfrey <mhumfrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 09:51:08 by mhumfrey          #+#    #+#             */
/*   Updated: 2021/05/14 13:47:38 by mhumfrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long long int	ft_atoi(const char *str)
{
	unsigned long long int	result;
	int						sign;

	sign = 1;
	result = 0;
	while (*str != 0 && (*str == ' '
			|| *str == '\n' || *str == '\t' ||
			*str == '\v' || *str == '\f' || *str == '\r'))
		++str;
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		++str;
	while (*str != '\0' && *str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - 48);
		++str;
	}
	if (result > ULLONG_MAX && sign == -1)
		return (ULLONG_MAX);
	else if (result > ULLONG_MAX && sign == 1)
		return (-ULLONG_MAX);
	return (result * sign);
}

int		ft_strlen(char *str)
{
	int i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i])
		i++;
	return (i);
}

int		wr_err(char *err)
{
	write (2, "Warning!\n", 9);
	write (2, "Error: ", 7);
	write (2, err, ft_strlen(err));
	write (2, "\n", 1);
	return (1);
}

int		is_digit(char c)
{
	return ('0' <= c && c <= '9');
}
