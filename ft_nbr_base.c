/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbr_base.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamrire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 18:25:16 by yamrire           #+#    #+#             */
/*   Updated: 2022/06/25 06:20:27 by yamrire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftprintf.h"

int	ft_nbr_base(unsigned long long n, int base, int which, int *len)
{
	char	*ptr_base;

	if (which)
		ptr_base = "0123456789ABCDEF";
	else
		ptr_base = "0123456789abcdef";
	if (n / base)
		ft_nbr_base (n / base, base, which, len);
	*len += ft_putchar (ptr_base[n % base]);
	return (*len);
}
