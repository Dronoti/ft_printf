/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkael <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 19:19:05 by bkael             #+#    #+#             */
/*   Updated: 2021/06/14 12:12:56 by bkael            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

typedef struct s_spec
{
	int	zero;
	int	width;
	int	minus;
	int	dot;
	int	dot_width;
	int	format;
}				t_spec;

int		ft_printf(const char *format, ...);
int		ft_putchar_count(char c);
t_spec	ft_newspec(void);
int		ft_check_spec(const char *f, int i, t_spec *spec, va_list *ap);
char	*ft_is_format(char c);
int		ft_print_width(t_spec *spec, int length);
void	ft_dot(t_spec *spec, va_list *ap);
int		ft_print_format(t_spec *spec, va_list *ap);
int		ft_char(t_spec *spec, char c);
int		ft_string(t_spec *spec, char *str);
int		ft_strlen(const char *s);
int		ft_number(t_spec *spec, int nbr);
int		ft_lennum(int nbr, int *fill, t_spec *spec);
int		ft_lennum_u(unsigned long long n, int *fill, t_spec *spec, int base);
void	ft_putnbr_count(int nbr, int fill, t_spec *spec);
int		ft_upx(t_spec *spec, unsigned long long nbr, int base);
void	ft_putnbr_count_u(unsigned int nbr, int fill, t_spec *spec);
void	ft_put_hex(unsigned long long nbr, int fill, t_spec *spec);

#endif