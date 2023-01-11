/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amechain <amechain@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 15:29:56 by amechain          #+#    #+#             */
/*   Updated: 2023/01/08 15:32:18 by amechain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*ptr;

	if (size != 0 && 18446744073709551615UL / size < count)
		return (NULL);
	ptr = malloc(count * size);
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, count * size);
	return (ptr);
}

void	ft_bzero(void *s, size_t n)
{
	size_t	c;
	char	*str;

	c = 0;
	str = (char *)s;
	while (c < n)
	{
		str[c] = 0;
		c++;
	}
}

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*dst;
	char	*str;

	i = 0;
	dst = NULL;
	str = (char *)s1;
	while (s1[i])
		i++;
	dst = (char *)malloc(sizeof(char) * (i + 1));
	if (dst == NULL)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		dst[i] = s1[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

size_t	ft_strlen(const char *s)
{
	size_t	c;
	char	*str;

	c = 0;
	str = (char *)s;
	while (str[c])
		c++;
	return (c);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	char	*substring;
	size_t	i;

	str = (char *)s;
	substring = NULL;
	i = 0;
	if (s == NULL)
		return (NULL);
	if (ft_strlen(s) - start < len)
		len = ft_strlen(s) - start;
	if (start >= ft_strlen(s))
		len = 0;
	substring = (char *)malloc(sizeof(char) * len + 1);
	if (substring == NULL)
		return (0);
	while (i < len && str[start] && start < ft_strlen(str))
	{
		substring[i] = str[start];
		start++;
		i++;
	}
	substring[i] = '\0';
	return (substring);
}
