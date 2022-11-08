/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamrire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 23:39:11 by yamrire           #+#    #+#             */
/*   Updated: 2022/02/27 23:42:34 by yamrire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	num;

	num = 0;
	while (str && str[num] != '\0')
		num++;
	return (num);
}

char	*ft_strchr(char *str, int c)
{
	int		num;

	num = 0;
	while (str[num] && str[num] != (char)c)
		num++;
	if (str[num] == (char)c)
		return (&str[num]);
	return (NULL);
}

char	*ft_strdup(const char *src)
{
	char			*ptr;
	unsigned int	num;

	num = 0;
	ptr = (char *) malloc((ft_strlen(src) + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	while (src[num] != '\0')
	{
		ptr[num] = src[num];
		num++;
	}
	ptr[num] = '\0';
	return (ptr);
}

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
