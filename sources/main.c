/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amechain <amechain@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 11:13:25 by anoukmechai       #+#    #+#             */
/*   Updated: 2023/01/08 15:05:59 by amechain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	arg_table(int ac, char **ag, t_pars	*pars)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	pars->array = ft_calloc(ac, sizeof(char *));
	if (!pars->array)
		error_parsing("Allocation failed", pars);
	while (j < ac - 1)
	{
		pars->array[j] = ft_strdup(ag[i]);
		if (!pars->array[j])
			error_parsing("Allocation failed", pars);
		j++;
		i++;
	}
	pars->array[j] = NULL;
	return (j);
}

t_pars	*init_pars(int ac, char **ag)
{
	t_pars	*pars;

	pars = ft_calloc(1, sizeof(t_pars));
	if (!pars)
		error_parsing("Allocation failed", NULL);
	pars->stash = NULL;
	pars->array = NULL;
	pars->stash = ft_calloc(5, sizeof(int));
	if (!pars->stash)
		error_parsing("Allocation failed", pars);
	if (ac - 1 == 1)
		split_arg(ag, pars);
	else
		pars->nbr_elem = arg_table(ac, ag, pars);
	return (pars);
}

int	main(int ac, char **ag)
{
	t_pack	*pack;
	t_pars	*pars;

	pack = NULL;
	pars = init_pars(ac, ag);
	if (ac - 1 == 1)
		check_parsing(pars);
	else if (ac - 1 != 4 && ac - 1 != 5)
		error_parsing("Wrong number input", pars);
	else
		check_parsing(pars);
	pack = init(pars);
	end_sim(pack);
	free_pars(pars);
	free_struct(pack);
	return (0);
}
