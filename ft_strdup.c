/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamrire <yamrire@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 00:12:27 by yamrire           #+#    #+#             */
/*   Updated: 2021/12/07 16:53:17 by yamrire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
