/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amechain <amechain@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 15:50:41 by anoukmechai       #+#    #+#             */
/*   Updated: 2022/10/28 17:23:17 by amechain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	struct_arg(t_pack *pack, int *stash, int ac)
{
	t_arg *t;

	t = pack->table;
	t = ft_calloc(1, sizeof(t_arg));
	if (!t)
		error();
	t->nbr_philos = stash[0];
	t->time_to_die = stash[1];
	t->time_to_eat = stash[2];
	t->time_to_sleep = stash[3];
	t->meal_requirmt = -1;
	if (ac - 1 == 5)
		t->meal_requirmt[4];
	t->sim_status = false;
}

t_philo **struct_philo(t_philo **philos, t_arg *table)
{
	int	i;

	i = 0;
	philos = ft_calloc((table->nbr_philos + 1), sizeof(t_philo *));
	if (!philos)
		error ();
	while (i < table->nbr_philos)
	{
		philos[i] = ft_calloc(1, sizeof(t_philo));
		if (!philos[i])
			error ();
		philos[i]->nbr_meal = 0;
		philos[i]->id = i;
		i++;
	}
	philos[i] = NULL;
	return(philos);
}

int	initialize(int *stash, int ac)
{
	t_pack	*pack;

	pack = ft_calloc(1, sizeof(t_pack));
	if (!pack)
		error();
	struct_arg(pack, stash, ac);
	pack->philos = struct_philo(pack->philos, pack->table); /* Philos use uninitialize ? */
	pack->count = 0;
	processes(pack);
}

/* Print table->dinner to see if it's = to philos */
