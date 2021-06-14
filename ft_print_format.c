/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkael <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 08:01:02 by bkael             #+#    #+#             */
/*   Updated: 2021/06/14 08:01:08 by bkael            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_char(t_spec *spec, char c)
{
	int	i;

	i = 0;
	if (!spec->minus)
		i += ft_print_width(spec, 1);
	i += ft_putchar_count(c);
	if (spec->minus)
		i += ft_print_width(spec, 1);
	return (i);
}

int	ft_string(t_spec *spec, char *str)
{
	int	i;
	int	start;
	int	length;

	i = 0;
	start = 0;
	if (!str)
		str = "(null)";
	length = ft_strlen(str);
	if (spec->dot && spec->dot_width >= 0 && (spec->dot_width < length))
		length = spec->dot_width;
	if (!spec->minus)
		i += ft_print_width(spec, length);
	while (str[start] && start < length)
		start += ft_putchar_count(str[start]);
	i += start;
	if (spec->minus)
		i += ft_print_width(spec, length);
	return (i);
}

int	ft_number(t_spec *spec, int nbr)
{
	int	lennbr;
	int	fill;
	int	i;

	i = 0;
	lennbr = ft_lennum(nbr, &fill, spec);
	if (nbr == -2147483648 && !spec->dot && spec->zero)
		write(1, "-", 1);
	if (nbr < 0 && !spec->dot && nbr != -2147483648 && spec->zero)
	{
		nbr *= -1;
		ft_putchar_count('-');
	}
	if (!spec->minus)
		i += ft_print_width(spec, lennbr);
	if (nbr == -2147483648 && !spec->dot && spec->zero)
		write(1, "2147483648", 10);
	ft_putnbr_count(nbr, fill, spec);
	if (spec->minus)
		i += ft_print_width(spec, lennbr);
	return (i + lennbr);
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
