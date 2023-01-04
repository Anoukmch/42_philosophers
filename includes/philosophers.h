/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukmechain <anoukmechain@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 13:50:23 by anoukmechai       #+#    #+#             */
/*   Updated: 2023/01/04 10:40:16 by anoukmechai      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdbool.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h> 

# include "../includes/libs/libs.h"

typedef struct s_pars
{
	int		*stash;
	char	**array;
	int		nbr_elem;

}				t_pars;

typedef struct s_arg
{
	int				nbr_philos;
	time_t			start_time;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	int				meal_requirmt;
	pthread_t		supervisor;
	bool			sim_stop;
	pthread_mutex_t	lock_msg;
	pthread_mutex_t	*mutex;
	pthread_mutex_t	lock_sim;

}				t_arg;

typedef struct s_philo
{
	pthread_t			thread;
	time_t				last_meal;
	int					nbr_meal;
	int					id;
	pthread_mutex_t		lock_var;
	t_arg				*table;
	unsigned int		fork[2];

}				t_philo;

typedef struct s_pack
{
	t_arg	*table;
	t_philo	**philos;

}				t_pack;

// END_SIM //
void	end_sim(t_pack *pack);
void	kill_mutx(t_pack *pack);
int		simulation_must_stop(t_philo *philos);

// ERROR_FREE //
void	error_exit(char *str, t_pack *pack);
void	error_parsing(char *str, t_pars *pars);
void	free_array(char **array);
void	free_struct(t_pack *pack);
void	free_pars(t_pars *pars);

// INIT //
void	init_thread(t_pack *pack);
void	init_mutex(t_pack *pack);
t_arg	*struct_arg(t_pack *pack, t_pars *pars);
t_philo	**struct_philo(t_pack *pack);
t_pack	*init(t_pars *pars);

// PARSING //
void	split_arg(char **ag, t_pars *pars);
int		is_negative(int i, int nb, t_pars *pars);
void	check_parsing(t_pars *pars);

// PHILOSOPHERS //
void	think_routine(t_philo *philos, int print);
void	sleep_routine(t_philo *philos);
void	eat_routine(t_philo *philos);
void	*philos_routine(void *data);

// SUPERVISOR //
int		is_dead(t_pack *pack, t_philo *philos);
void	*supervisor_routine(void *data);

// UTILS //
void	sync_thread(time_t start_time);
time_t	get_time_in_ms(void);
void	print_message(t_philo *philos, int id, char *message);
void	sleep_time(time_t sleep_time, t_philo *philos);
void	assign_forks(t_philo *philos);

// ONE PHILOS //
void	*one_philosopher(t_philo *philos);

#endif