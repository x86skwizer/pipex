/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamrire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 23:46:41 by yamrire           #+#    #+#             */
/*   Updated: 2022/06/25 06:20:05 by yamrire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftprintf.h"

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
