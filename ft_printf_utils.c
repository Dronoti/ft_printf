/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkael <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 12:27:09 by bkael             #+#    #+#             */
/*   Updated: 2021/06/04 12:27:34 by bkael            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar_count(char c)
{
	write(1, &c, 1);
	return (1);
}

t_spec	ft_newspec(void)
{
	t_spec	new;

	new.zero = 0;
	new.width = 0;
	new.minus = 0;
	new.dot = 0;
	new.dot_width = 0;
	new.format = 0;
	return (new);
}

char	*ft_is_format(char c)
{
	char	*types;

	types = "csdiupxX%";
	return (ft_strchr(types, c));
}

char	*ft_is_flag(char c)
{
	char	*flags;

	flags = "*.0-";
	return (ft_strchr(flags, c));
}

int	ft_print_width(t_spec *spec, int length)
{
	int	i;

	i = 0;
	while (length < spec->width)
	{
		if (!spec->zero)
			i += ft_putchar_count(' ');
		else
			i += ft_putchar_count('0');
		length++;
	}
	return (i);
}
