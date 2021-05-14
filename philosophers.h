/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhumfrey <mhumfrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 09:54:51 by mhumfrey          #+#    #+#             */
/*   Updated: 2021/05/14 13:48:25 by mhumfrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <limits.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <semaphore.h>
# include <sys/time.h>

typedef struct			s_all
{
	int death_flag;
	unsigned long long	num_phils;
	unsigned long long	life_time;
	unsigned long long	eat_time;
	unsigned long long	sleep_time;
	unsigned long long	num_meals;
	unsigned int		id;
	int					full;
	sem_t				*s_status;
	pthread_t			thread;
	long long			start_time;
	long long			last_meal;
	pthread_mutex_t		*m_forks;
	pthread_mutex_t		m_died;
	pthread_mutex_t		m_print;
}						t_all;


int				wr_err(char *err);
int				ft_strlen(char *str);
int				is_digit(char c);
int				args_valid_n_check(t_all *all, char **args, int num_args);
long long int	ft_atoi(const char *str);

#endif
