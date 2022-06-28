/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamrire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 02:43:37 by yamrire           #+#    #+#             */
/*   Updated: 2022/06/28 03:31:58 by yamrire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	num;

	if (!s)
		return (NULL);
	if (len > ft_strlen(s))
	{
		len = ft_strlen(s);
		str = (char *) malloc((len + 1) * sizeof(char));
	}
	else
		str = (char *) malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	num = 0;
	while (num < len && start < ft_strlen(s))
	{
		str[num] = s[start + num];
		num++;
	}
	str[num] = '\0';
	return (str);
}
