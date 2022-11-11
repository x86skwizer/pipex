/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamrire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 23:44:51 by yamrire           #+#    #+#             */
/*   Updated: 2022/11/11 09:46:25 by yamrire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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
