/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamrire <yamrire@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 23:48:54 by yamrire           #+#    #+#             */
/*   Updated: 2021/12/13 16:40:45 by yamrire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count_words(char const *src, char c)
{
	int	n;

	n = 0;
	while (*src == c)
		src++;
	if (*src == '\0')
		return (1);
	while (*src != '\0')
	{
		while (*src && *src != c)
			src++;
		n++;
		while (*src && *src == c)
			src++;
	}
	return (n);
}

char	**initiate_split(const char *s, char c, size_t *j, int *start)
{
	char	**tab;

	if (!s)
		return (NULL);
	tab = (char **) malloc((count_words(s, c) + 1) * sizeof(char *));
	if (!tab)
		return (tab);
	*j = 0;
	*start = -1;
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	size_t	i;
	size_t	j;
	int		start;

	tab = initiate_split (s, c, &j, &start);
	if (!tab)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		if (!s[i])
			break ;
		start = i;
		while (s[i] && s[i] != c)
			i++;
		tab[j] = ft_substr(s, start, i - start);
		if (tab[j++] == NULL)
			return (NULL);
	}
	tab[j] = NULL;
	return (tab);
}
