/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukmechain <anoukmechain@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 10:10:48 by anoukmechai       #+#    #+#             */
/*   Updated: 2023/01/04 10:39:45 by anoukmechai      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

long long	ft_atoilong(char *s)
{
	unsigned long long	res;
	int					sign;
	int					c;

	c = 0;
	sign = 1;
	res = 0;
	while ((s[c] >= '\t' && s[c] <= '\r') || (s[c] == ' '))
		c++;
	if (s[c] == '-')
	{
		sign = -1;
		c++;
	}
	else if (s[c] == '+')
		c++;
	while (s[c] >= '0' && s[c] <= '9')
		res = (res * 10) + (s[c++] - '0');
	return (res * sign);
}

void	split_arg(char **ag, t_pars *pars)
{
	int		nbr_string;

	nbr_string = 0;
	pars->array = ft_split(ag[1], ' ');
	if (!pars->array)
		error_parsing("Allocation failed", pars);
	while (pars->array[nbr_string])
		nbr_string++;
	if (nbr_string != 4 && nbr_string != 5)
		error_parsing("Wrong input number", pars);
	else
		pars->nbr_elem = nbr_string;
}

int	is_negative(int i, int nb, t_pars *pars)
{
	if (i == 0 && (nb <= 0 || nb > 250))
		error_parsing("Wrong input : philosophers number", pars);
	else if (pars->nbr_elem == 4 && i != 0 && nb < 0)
		error_parsing("Wrong input : negative time data", pars);
	else if (pars->nbr_elem == 5)
	{
		if (i != 1 && i != pars->nbr_elem - 1 && nb < 0)
			error_parsing("Wrong input : negative time data ", pars);
		else if (i == pars->nbr_elem - 1 && nb <= 0)
			error_parsing("Wrong input : wrong meal requirement", pars);
	}
	return (0);
}

int	isonlydigit(char *ag)
{
	int	i;

	i = 0;
	while (ag[i])
	{
		if (ag[i] == '+' || ag[i] == '-')
			i++;
		if (ag[i] < '0' || ag[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

void	check_parsing(t_pars *pars)
{
	long long	nb;
	int			i;
	int			j;

	i = 0;
	j = 0;
	while (i < pars->nbr_elem)
	{
		if (isonlydigit(pars->array[i]))
			error_parsing("Wrong input : non digit input", pars);
		nb = ft_atoilong(pars->array[i]);
		if ((nb > INT_MAX) || nb < INT_MIN)
			error_parsing("Wrong input : not an integer", pars);
		is_negative(i, (int)nb, pars);
		pars->stash[j++] = (int)nb;
		i++;
	}
}
