/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamrire <yamrire@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 23:44:51 by yamrire           #+#    #+#             */
/*   Updated: 2022/01/15 22:14:49 by yamrire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int	ft_putnbr(long n, int *len)
{
	if (n < 0)
	{
		n *= -1;
		*len += ft_putchar('-');
	}
	if (n)
	{
		if (n / 10)
			ft_putnbr (n / 10, len);
		*len += ft_putchar (n % 10 + '0');
	}
	else
		*len += ft_putchar('0');
	return (*len);
}
