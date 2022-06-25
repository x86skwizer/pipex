/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamrire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 01:50:45 by yamrire           #+#    #+#             */
/*   Updated: 2022/06/25 06:20:20 by yamrire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftprintf.h"

int	gethex(char c)
{
	if (c == 'X')
		return (1);
	return (0);
}

int	handle_print_cases(const char *str, int i, va_list *format)
{
	int				len;

	len = 0;
	if (str[i] == 'c')
		len = ft_putchar(va_arg(*format, int));
	else if (str[i] == 's')
		len = ft_putstr(va_arg(*format, char *));
	else if (str[i] == 'd' || str[i] == 'i')
		len = ft_putnbr(va_arg(*format, int), &len);
	else if (str[i] == 'u')
		ft_nbr_base(va_arg(*format, unsigned int), 10, 1, &len);
	else if (str[i] == 'x' || str[i] == 'X')
		ft_nbr_base(va_arg(*format, unsigned int), 16, gethex(str[i]), &len);
	else if (str[i] == '%')
		len = ft_putchar('%');
	else if (str[i] == 'p')
	{
		len = ft_putstr("0x");
		ft_nbr_base(va_arg(*format, unsigned long long), 16, 0, &len);
	}
	else
		len = ft_putchar(str[i]);
	return (len);
}

int	ft_printf(const char *str, ...)
{
	int		i;
	int		len;
	va_list	format;

	va_start(format, str);
	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			i++;
			len += handle_print_cases(str, i, &format);
		}
		else
			len += ft_putchar(str[i]);
		i++;
	}
	va_end(format);
	return (len);
}
