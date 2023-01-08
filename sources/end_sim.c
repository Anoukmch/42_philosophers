/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_sim.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amechain <amechain@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 10:06:58 by anoukmechai       #+#    #+#             */
/*   Updated: 2023/01/08 12:37:29 by amechain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	simulation_must_stop(t_philo *philos)
{
	pthread_mutex_lock(&philos->table->lock_sim);
	if (philos->table->sim_stop == true)
	{
		pthread_mutex_unlock(&philos->table->lock_sim);
		return (1);
	}
	pthread_mutex_unlock(&philos->table->lock_sim);
	return (0);
}

void	kill_mutx(t_pack *pack)
{
	int	i;

	i = 0;
	while (i < pack->table->nbr_philos)
	{
		pthread_mutex_destroy(&pack->table->mutex[i]);
		pthread_mutex_destroy(&pack->philos[i]->lock_var);
		i++;
	}
	pthread_mutex_destroy(&pack->table->lock_msg);
	pthread_mutex_destroy(&pack->table->lock_sim);
}

void	end_sim(t_pack *pack)
{
	int	i;

	i = 0;
	while (i < pack->table->nbr_philos)
	{
		if (pthread_join(pack->philos[i]->thread, NULL) != 0)
			error_exit("pthread_join error", pack);
		i++;
	}
	if (pack->table->nbr_philos > 1)
	{
		if (pthread_join(pack->table->supervisor, NULL) != 0)
			error_exit("pthread_join error", pack);
	}
	kill_mutx(pack);
}
