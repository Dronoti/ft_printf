/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkael <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 16:44:53 by bkael             #+#    #+#             */
/*   Updated: 2021/06/08 16:44:56 by bkael            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr_count(int nbr, int fill, t_spec *spec)
{
	int	i;

	i = 0;
	if (nbr == -2147483648)
	{
		write(1, "-", 1);
		while (fill-- > 0)
			i += ft_putchar_count('0');
		write(1, "2147483648", 10);
		return (i + 11);
	}
	if (nbr < 0)
	{
		nbr = -nbr;
		write(1, "-", 1);
		i++;
	}
	while (fill-- > 0)
		i += ft_putchar_count('0');
	if (nbr > 9)
		ft_putnbr_count(nbr / 10, fill, spec);
	i += ft_putchar_count(nbr % 10 + '0');
	return (i);
}
