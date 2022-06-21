/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamrire <yamrire@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 00:16:47 by yamrire           #+#    #+#             */
/*   Updated: 2021/12/07 16:55:37 by yamrire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len1;
	size_t	len;
	size_t	count1;
	size_t	count2;
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	str = (char *) malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	len1 = ft_strlen(s1);
	count1 = 0;
	while (count1 < len1)
	{
		str[count1] = s1[count1];
		count1++;
	}
	count2 = 0;
	while (count1 < len)
		str[count1++] = s2[count2++];
	str[count1] = '\0';
	return (str);
}
