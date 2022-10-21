/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backup.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukmechain <anoukmechain@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 11:28:18 by anoukmechai       #+#    #+#             */
/*   Updated: 2022/10/21 11:28:20 by anoukmechai      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

t_philo **struct_arg(t_arg *table, int *stash, int ac)
{	
	table = ft_calloc(1, sizeof(t_arg));
	if (!table)
		error();
	table->nbr_philos = stash[0];
	table->time_to_die = stash[1];
	table->time_to_eat = stash[2];
	table->time_to_sleep = stash[3];
	table->meal_requirmt = -1;
	if (ac - 1 == 5)
		table->meal_requirmt[4];
	table->sim_status = false;
	table->dinner = (**t_philo)ft_calloc((table->nbr_philos + 1), sizeof(t_philo *));
	if (!table->dinner)
		error ();
	return (table->dinner);
}

void struct_philo(t_philo **philos, t_arg *table)
{
	int	i;

	i = 0;
	while (i < table->nbr_philos)
	{
		philos[i] = (t_philo)ft_calloc(1, sizeof(t_philo));
		if (!philos[i])
			error ();
		philos[i]->nbr_meal = 0;
		philos[i]->id = i;
		i++;
	}
	philos[i] = NULL;
}

int	initialize(int *stash, int ac)
{
	t_arg *table;
	t_philo **philos;
	
	philos = struct_arg(table, stash, ac);
	struct_philo(philos, table);
	
}

/* Print table->dinner to see if it's = to philos */