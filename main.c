/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhumfrey <mhumfrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 09:40:43 by mhumfrey          #+#    #+#             */
/*   Updated: 2021/05/14 14:47:27 by mhumfrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int		args_valid_n_check(t_all *all, char **args, int num_args)
{
	int i;
	int j;

	j = 0;
	while (args[++j])
	{
		i = -1;
		while(args[j][++i])
		{
			if (!is_digit(args[j][i]))
				return (wr_err("wrong argument - non-digital symbol."));
		}
	}
	if ((all->num_phils = ft_atoi(args[1])) == ULLONG_MAX
	|| (all->life_time = ft_atoi(args[2])) == ULLONG_MAX
	|| (all->eat_time = ft_atoi(args[3])) == ULLONG_MAX
	|| (all->sleep_time = ft_atoi(args[4])) == ULLONG_MAX)
		return (wr_err("long long int argument overflow."));
	if (num_args == 5)
		all->num_meals = 0;
	if (num_args == 6)
		if ((all->num_meals = ft_atoi(args[5])) == ULLONG_MAX)
			return (wr_err("long long int argument overflow."));
	return (0);
}

int		main(int ac, char **av)
{
	t_all all;

	all.death_flag = 0;
	if (ac < 5)
		return(wr_err("bad quantity of arguments - not enough."));
	if (ac > 6)
		return(wr_err("bad quantity of arguments - too much."));
	if (args_valid_n_check(&all, av, ac) == 1)
		return (1);
	if (all.num_phils < 2)
		return(wr_err("wrong number of philosophers - not enough."));
	if (all.num_phils > 200)
		return(wr_err("wrong number of philosophers - too much."));
	if (start_philo(&all))
		return (1);
	return (0);
}
