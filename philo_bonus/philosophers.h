/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhumfrey <mhumfrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 09:54:51 by mhumfrey          #+#    #+#             */
/*   Updated: 2021/06/23 04:37:56 by mhumfrey         ###   ########.fr       */
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
# include <signal.h>
# include <sys/time.h>

typedef struct s_semaphores
{
	sem_t			*forks;
	sem_t			*checkd;
	sem_t			*write_semaphore;
}					t_semaphores;

typedef struct s_arguments
{
	long			number_of_philosophers;
	long			life_time;
	long			eat_time;
	long			sleep_time;
	long			number_of_meals;
	int				death_flag;
}					t_arguments;

typedef struct s_philosophers
{
	int				philo_id;
	long			start;
	long			last;
	t_semaphores	*semaphore;
	t_arguments		*arguments;
	pid_t			*pid;
	pthread_t		philosopher;
}					t_philosophers;

typedef struct s_matrix
{
	long			time;
	pid_t			*pid;
	t_semaphores	*semaphore;
	t_arguments		*arguments;
	t_philosophers	*philosophers;
}					t_matrix;

int			main(int ac, char **av);
void		philosopher_eats(t_philosophers *philo);
void		philosopher_sleeps(t_philosophers *philo);
void		philosopher_thinks(t_philosophers *philo);
int			philosopher_full(t_philosophers *philo, int *i);
void		*check_death(void *philosopher);
int			validate_args(char **args);
int			initialize_args(t_matrix *matrix, char **av, int ac);
int			initialize_sems(t_matrix *matrix);
int			initialize_philos(t_matrix *matrix);
void		processes(t_philosophers *philosopher);
void		wait_loop(t_matrix *matrix);
int			start_philosopher(t_matrix *matrix);
long long	long_atoi(const char *str);
int			is_digit(char c);
int			out_error(char *err);
int			ft_strlen(char *str);
void		free_all(t_matrix *matrix);
long		time_fix(void);
void		sleep_fix(long wait_time);

#endif
