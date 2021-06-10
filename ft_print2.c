/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkael <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 16:44:53 by bkael             #+#    #+#             */
/*   Updated: 2021/06/10 16:44:56 by bkael            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_lennum_u(unsigned long long n, int *fill, t_spec *spec, int base)
{
	int	len;

	len = 0;
	if (n == 0)
		len++;
	while (n)
	{
		len++;
		n /= base;
	}
	*fill = spec->dot_width - len;
	if (*fill < 0)
		*fill = 0;
	len += *fill;
	return (len);
}

int	ft_upx(t_spec *spec, unsigned long long nbr, int base)
{
	int	lennbr;
	int	fill;
	int	i;

	i = 0;
	lennbr = ft_lennum_u(nbr, &fill, spec, base);
	if (spec->format == 'p')
	{
		if (spec->zero && spec->width)
			write(1, "0x", 2);
		lennbr += 2;
	}
	if (!spec->minus)
		i += ft_print_width(spec, lennbr);
	if (spec->format == 'u')
		ft_putnbr_count_u(nbr, fill, spec);
	if (spec->format == 'x' || spec->format == 'X' || spec->format == 'p')
	{
		if (spec->format == 'p' && !fill && (!spec->width || !spec->zero))
			write(1, "0x", 2);
		ft_put_hex(nbr, fill, spec);
	}
	if (spec->minus)
		i += ft_print_width(spec, lennbr);
	return (i + lennbr);
}

void	ft_putnbr_count_u(unsigned int nbr, int fill, t_spec *spec)
{
	while (fill-- > 0)
		ft_putchar_count('0');
	if (nbr > 9)
		ft_putnbr_count_u(nbr / 10, fill, spec);
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
	if (nbr % 16 < 10)
		ft_putchar_count(nbr % 16 + '0');
	else if (spec->format == 'x' || spec->format == 'p')
		ft_putchar_count(nbr % 16 - 10 + 'a');
	else if (spec->format == 'X')
		ft_putchar_count(nbr % 16 - 10 + 'A');
}
