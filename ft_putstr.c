/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamrire <yamrire@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 23:46:41 by yamrire           #+#    #+#             */
/*   Updated: 2022/01/12 13:48:24 by yamrire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int	ft_putstr(char *s)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	if (s == NULL)
	{
		ft_putstr("(null)");
		return (6);
	}
	if (s)
	{
		while (s[i] != '\0')
		{
			len += ft_putchar(s[i]);
			i++;
		}
	}
	return (len);
}
