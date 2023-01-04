/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukmechain <anoukmechain@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 15:50:41 by anoukmechai       #+#    #+#             */
/*   Updated: 2023/01/04 10:27:13 by anoukmechai      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	init_thread(t_pack *pack)
{
	int	i;

	i = 0;
	pack->table->start_time = get_time_in_ms() + (pack->table->nbr_philos * 20);
	while (i < pack->table->nbr_philos)
	{
		if (pthread_create(&pack->philos[i]->thread,
				NULL, philos_routine, pack->philos[i]) != 0)
			error_exit("pthread_create fail", pack);
		i++;
	}
	if (pack->table->nbr_philos > 1)
	{
		if (pthread_create(&pack->table->supervisor,
				NULL, supervisor_routine, pack) != 0)
			error_exit("pthread_create fail", pack);
	}
}

void	init_mutex(t_pack *pack)
{
	int	i;

	i = 0;
	while (i < pack->table->nbr_philos)
	{
		if (pthread_mutex_init(&pack->table->mutex[i], NULL) != 0)
			error_exit("pthread_mutex_init fail", pack);
		if (pthread_mutex_init(&pack->philos[i]->lock_var, NULL) != 0)
			error_exit("pthread_mutex_init fail", pack);
		i++;
	}
	if (pthread_mutex_init(&pack->table->lock_msg, NULL) != 0)
		error_exit("pthread_mutex_init fail", pack);
	if (pthread_mutex_init(&pack->table->lock_sim, NULL) != 0)
		error_exit("pthread_mutex_init fail", pack);
}

t_arg	*struct_arg(t_pack *pack, t_pars *pars)
{
	t_arg	*table;

	table = ft_calloc(1, sizeof(t_arg));
	if (!table)
		error_exit("table Allocation failed", pack);
	table->nbr_philos = pars->stash[0];
	table->time_to_die = pars->stash[1];
	table->time_to_eat = pars->stash[2];
	table->time_to_sleep = pars->stash[3];
	table->start_time = 0;
	table->meal_requirmt = -1;
	if (pars->nbr_elem == 5)
		table->meal_requirmt = pars->stash[4];
	table->sim_stop = false;
	table->mutex = ft_calloc(table->nbr_philos, sizeof(pthread_mutex_t));
	if (!table->mutex)
		error_exit("table Allocation failed", pack);
	return (table);
}

t_philo	**struct_philo(t_pack *pack)
{
	int		i;
	t_philo	**philos;

	i = 0;
	philos = ft_calloc((pack->table->nbr_philos + 1), sizeof(t_philo *));
	if (!philos)
		error_exit("philos Allocation failed", pack);
	while (i < pack->table->nbr_philos)
		philos[i++] = NULL;
	i = 0;
	while (i < pack->table->nbr_philos)
	{
		philos[i] = ft_calloc(1, sizeof(t_philo));
		if (!philos[i])
			error_exit("philos [i] Allocation failed", pack);
		philos[i]->nbr_meal = 0;
		philos[i]->id = i;
		philos[i]->table = pack->table;
		assign_forks(philos[i]);
		i++;
	}
	philos[i] = NULL;
	return (philos);
}

t_pack	*init(t_pars *pars)
{
	t_pack	*pack;

	pack = ft_calloc(1, sizeof(t_pack));
	if (!pack)
		error_exit("pack Allocation failed", NULL);
	pack->table = NULL;
	pack->philos = NULL;
	pack->table = struct_arg(pack, pars);
	pack->philos = struct_philo(pack);
	init_mutex(pack);
	init_thread(pack);
	return (pack);
}
