/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkael <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 19:16:36 by bkael             #+#    #+#             */
/*   Updated: 2021/06/10 12:28:48 by bkael            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_format(t_spec *spec, va_list *ap)
{
	int	i;

	i = 0;
	if ((spec->minus == 1 || spec->dot) && (spec->format != '%'))
		spec->zero = 0;
	if (spec->format == 'c')
		i = ft_char(spec, va_arg(*ap, int));
	else if (spec->format == 's')
		i = ft_string(spec, va_arg(*ap, char *));
	else if (spec->format == '%')
		i = ft_char(spec, '%');
	else if (spec->format == 'd' || spec->format == 'i')
		i = ft_number(spec, va_arg(*ap, int));
	else if (spec->format == 'p')
		i = ft_upx(spec, va_arg(*ap, unsigned long long), 16);
	else if (spec->format == 'x' || spec->format == 'X')
		i = ft_upx(spec, va_arg(*ap, unsigned int), 16);
	else if (spec->format == 'u')
		i = ft_upx(spec, va_arg(*ap, unsigned int), 10);
	return (i);
}

void	ft_dot(t_spec *spec, va_list *ap)
{
	spec->width = va_arg(*ap, int);
	if (spec->width < 0)
	{
		spec->width *= -1;
		spec->minus = 1;
	}
}

int	ft_check_spec(const char *f, int i, t_spec *spec, va_list *ap)
{
	while (f[i] || ft_isdigit(f[i]) || ft_is_format(f[i]) || ft_is_flag(f[i]))
	{
		if (f[i] == '-')
			spec->minus = 1;
		else if (f[i] == '0' && spec->width == 0 && spec->dot == 0)
			spec->zero = 1;
		else if (f[i] == '.')
			spec->dot = 1;
		else if (f[i] == '*' && spec->dot)
			spec->dot_width = va_arg(*ap, int);
		else if (f[i] == '*' && !spec->dot)
			ft_dot(spec, ap);
		else if (ft_isdigit(f[i]) && !spec->dot)
			spec->width = spec->width * 10 + (f[i] - '0');
		else if (ft_isdigit(f[i]) && spec->dot)
			spec->dot_width = spec->dot_width * 10 + (f[i] - '0');
		else if (ft_is_format(f[i]))
		{
			spec->format = f[i];
			return (i);
		}
		i++;
	}
	return (i);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		count;
	int		i;
	t_spec	spec;

	if (!format)
		return (0);
	va_start(ap, format);
	i = 0;
	count = 0;
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1])
		{
			spec = ft_newspec();
			i = ft_check_spec(format, ++i, &spec, &ap);
			count += ft_print_format(&spec, &ap);
		}
		else
			count += ft_putchar_count(format[i]);
		i++;
	}
	va_end(ap);
	return (count);
}
