/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkael <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 14:37:26 by bkael             #+#    #+#             */
/*   Updated: 2021/06/14 14:37:29 by bkael            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	ft_putnbr_count(int nbr, int fill, t_spec *spec)
{
	if (nbr == -2147483648 && !spec->zero)
	{
		write(1, "-", 1);
		while (fill-- > 0)
			ft_putchar_count('0');
		write(1, "2147483648", 10);
	}
	if (nbr < 0 && nbr != -2147483648)
	{
		nbr *= -1;
		write(1, "-", 1);
	}
	while (fill-- > 0)
		ft_putchar_count('0');
	if (nbr == -2147483648)
		return ;
	if (nbr > 9)
		ft_putnbr_count(nbr / 10, fill, spec);
	if (!(nbr == 0 && spec->dot && spec->dot_width >= 0))
		ft_putchar_count(nbr % 10 + '0');
}

void	ft_putnbr_count_u(unsigned int nbr, int fill, t_spec *spec)
{
	while (fill-- > 0)
		ft_putchar_count('0');
	if (nbr > 9)
		ft_putnbr_count_u(nbr / 10, fill, spec);
	if (!(nbr == 0 && spec->dot && spec->dot_width >= 0))
		ft_putchar_count(nbr % 10 + '0');
}

void	ft_put_hex(unsigned long long nbr, int fill, t_spec *spec)
{
	int	flag;

	flag = 0;
	while (fill-- > 0)
	{
		if (spec->format == 'p' && !flag)
			flag += write(1, "0x", 2);
		ft_putchar_count('0');
	}
	if (nbr > 15)
		ft_put_hex(nbr / 16, fill, spec);
	if (!(nbr == 0 && spec->dot && spec->dot_width >= 0))
	{
		if (nbr % 16 < 10)
			ft_putchar_count(nbr % 16 + '0');
		else if (spec->format == 'x' || spec->format == 'p')
			ft_putchar_count(nbr % 16 - 10 + 'a');
		else if (spec->format == 'X')
			ft_putchar_count(nbr % 16 - 10 + 'A');
	}
}

int	ft_lennum_u(unsigned long long n, int *fill, t_spec *spec, int base)
{
	int	len;
	int	nbr;

	len = 0;
	nbr = n;
	if (n == 0)
		len++;
	while (n)
	{
		len++;
		n /= base;
	}
	if (nbr == 0 && spec->dot)
		len = 0;
	*fill = spec->dot_width - len;
	if (*fill < 0)
		*fill = 0;
	len += *fill;
	return (len);
}
