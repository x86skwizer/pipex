/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftprintf.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamrire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 14:03:27 by yamrire           #+#    #+#             */
/*   Updated: 2022/06/25 06:21:11 by yamrire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTPRINTF_H
# define FTPRINTF_H

# include <stdarg.h>
# include <unistd.h>

int	ft_putchar(char c);
int	ft_putnbr(long n, int *len);
int	ft_putstr(char *s);
int	ft_printf(const char *str, ...);
int	ft_nbr_base(unsigned long long n, int base, int which, int *len);

#endif
