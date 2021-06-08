/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkael <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 08:01:02 by bkael             #+#    #+#             */
/*   Updated: 2021/06/08 08:01:08 by bkael            ###   ########.fr       */
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

int	ft_putstr_count(char *str, int length)
{
	int	i;

	i = 0;
	while (str[i] && i < length)
		i += ft_putchar_count(str[i]);
	return (i);
}

int	ft_string(t_spec *spec, char *str)
{
	int	i;
	int	length;

	i = 0;
	if (!str)
		str = "(null)";
	length = ft_strlen(str);
	if (spec->dot && (spec->dot_width < length))
		length = spec->dot_width;
	if (!spec->minus)
		i += ft_print_width(spec, length);
	i += ft_putstr_count(str, length);
	if (spec->minus)
		i += ft_print_width(spec, length);
	return (i);
}

int	ft_lennum(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len++;
	while (n)
	{
		len++;
		n /= 10;
	}
	return (len);
}

int	ft_number(t_spec *spec, int nbr)
{
	int	lennbr;
	int	fill;
	int	i;

	lennbr = ft_lennum(nbr);
	if (nbr > 0)
		fill = spec->dot_width - lennbr;
	else
		fill = spec->dot_width - lennbr + 1;
	if (fill < 0)
		fill = 0;
	lennbr += fill;
	if (!spec->minus)
		i += ft_print_width(spec, lennbr);
	i += ft_putnbr_count(nbr, fill, spec);
	if (spec->minus)
		i += ft_print_width(spec, lennbr);
	return (i);
}
