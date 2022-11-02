/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amechain <amechain@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 11:13:25 by anoukmechai       #+#    #+#             */
/*   Updated: 2022/10/28 17:23:03 by amechain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* gcc -pthread main.c */

#include <pthread.h>
#include <sys/time.h>

typedef struct s_arg
{
	int				nbr_philos;
	time_t			start_time;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	int				meal_requirmt;
	pthread_t		supervisor;
	bool			sim_status;
	pthread_mutex_t	sim_status_protect;
}               t_arg;

typedef struct s_philo
{
	pthread_t	thread;
	time_t		last_meal;
	int			nbr_meal;
    int			id;
	pthread_mutex_t	mutex;
	int	msgs;

}               t_philo;

typedef struct s_pack
{
	t_arg 	*table;
	t_philo **philos;
	int count;

}				t_pack;

void	error_msg(char *err)
{
	perror(err);
	freeing();
	exit (1);
}

char	**split_arg(char **ag)
{
	char	**array;
	int		nbr_string;

	array = ft_split(ag, &nbr_string); /* Modifier split */
	if (!array)
		return (error("Allocation failed"));
	if (nbr_string - 1 != 4 || nbr_string - 1 != 5)
		return (error("Wrong number input"));
	return (array);
}

void	is_negative(int i, int nb, int ac)
{
	if (i == 1 && nb <= 0)
		error("Wrong input : not enough philosophers");
	else if (ac - 1 == 4 && i != 1 && nb < 0)
		error("Wrong input : time data cannot be negative");
	else if (ac - 1 == 5)
	{
		if (i != 1 && i != ac - 1 && nb < 0)
			error("Wrong input : time data cannot be negative");
		else if (i == ac - 1 && nb <= 0)
			error("Wrong input : wrong meal requirement");
	}
}

int	*check_parsing(int ac, char **ag)
{
	int nb;
	int i;
	int j;
	int	*stash;

	i = 1;
	j = 0;
	stash = ft_calloc(ac - 1, sizeof(int));
	while (++i < ac)
	{
		if (!check_digit || ag[i])
			error();
		nb = ft_atoi(ag[i]); /* Long long atoi */
		if (nb > INT_MAX)
			error("Wrong input : not an integer");
		is_negative(i, nb, ac);
		stash[j++] = nb;
	}
	return (stash);
}

int main(int ac, char **ag)
{
	char	**array;
	int		*stash;

	if (ac - 1 == 1)
		array = split_arg(ag);
	else if (ac - 1 != 4 || ac - 1 != 5)
		error("Wrong number input");
	if (array)
		stash = check_parsing(ac, array);
	else
		stash = check_parsing(ac, ag);
	initialize(stash, ac);
}
