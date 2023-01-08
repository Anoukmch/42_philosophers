/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amechain <amechain@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 15:50:41 by anoukmechai       #+#    #+#             */
/*   Updated: 2023/01/08 15:00:09 by amechain         ###   ########.fr       */
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

void	struct_arg(t_pack *pack, t_pars *pars)
{
	pack->table = ft_calloc(1, sizeof(t_arg));
	if (!pack->table)
	{
		free_pars(pars);
		error_exit("table Allocation failed", pack);
	}
	pack->table->nbr_philos = pars->stash[0];
	pack->table->time_to_die = pars->stash[1];
	pack->table->time_to_eat = pars->stash[2];
	pack->table->time_to_sleep = pars->stash[3];
	pack->table->start_time = 0;
	pack->table->meal_requirmt = -1;
	if (pars->nbr_elem == 5)
		pack->table->meal_requirmt = pars->stash[4];
	pack->table->sim_stop = false;
	pack->table->mutex = ft_calloc(pack->table->nbr_philos,
			sizeof(pthread_mutex_t));
	if (!pack->table->mutex)
	{
		free_pars(pars);
		error_exit("table Allocation failed", pack);
	}
}

void	struct_philo(t_pack *pack)
{
	int		i;

	i = 0;
	pack->philos = ft_calloc((pack->table->nbr_philos + 1), sizeof(t_philo *));
	if (!pack->philos)
		error_exit("philos Allocation failed", pack);
	while (i < pack->table->nbr_philos)
		pack->philos[i++] = NULL;
	i = 0;
	while (i < pack->table->nbr_philos)
	{
		pack->philos[i] = ft_calloc(1, sizeof(t_philo));
		if (!pack->philos[i])
			error_exit("philos [i] Allocation failed", pack);
		pack->philos[i]->nbr_meal = 0;
		pack->philos[i]->id = i;
		pack->philos[i]->table = pack->table;
		assign_forks(pack->philos[i]);
		i++;
	}
	pack->philos[i] = NULL;
}

t_pack	*init(t_pars *pars)
{
	t_pack	*pack;

	pack = ft_calloc(1, sizeof(t_pack));
	if (!pack)
		error_parsing("pack Allocation failed", pars);
	pack->table = NULL;
	pack->philos = NULL;
	struct_arg(pack, pars);
	struct_philo(pack);
	init_mutex(pack);
	init_thread(pack);
	return (pack);
}
