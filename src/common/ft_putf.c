/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putf_fd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-jesu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 15:31:33 by dde-jesu          #+#    #+#             */
/*   Updated: 2019/05/23 12:49:45 by prastoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

void			char_fd(size_t fd, uint8_t c, size_t padd)
{
	size_t	i;
	char	sp;

	sp = ' ';
	i = -1;
	if (padd > 0)
		while (++i < padd - 1)
			write(fd, &sp, 1);
	write(fd, &c, 1);
}

static void		str_fd(char *str, size_t fd, size_t padd)
{
	ssize_t i;

	i = 0;
	if (padd > 0)
	{
		while (i < (ssize_t)(padd - ft_strlen(str)))
		{
			char_fd(fd, ' ', 0);
			i++;
		}
	}
	i = -1;
	while (str[++i])
		write(fd, str + i, 1);
}

void			str_hexa_fd(char *str, size_t fd, size_t padd)
{
	ssize_t i;

	i = 0;
	if (padd > 0)
	{
		while (i < (ssize_t)(padd - ft_strlen(str)))
		{
			char_fd(fd, '0', 0);
			i++;
		}
	}
	i = -1;
	while (str[++i])
		write(fd, str + i, 1);
}

void			ft_putnbr_fd(size_t fd, intmax_t nb)
{
	if (nb < 0)
	{
		char_fd(fd, '-', 0);
		nb = -nb;
	}
	if (nb > 9)
	{
		ft_putnbr_fd(fd, nb / 10);
		ft_putnbr_fd(fd, nb % 10);
	}
	else
		char_fd(fd, nb + '0', 0);
}

void			ft_putf_va(int fd, char *fmt, va_list args, size_t padd)
{
	char		*l_fmt;

	l_fmt = fmt;
	while ((fmt = ft_strchr(fmt, '%')) && *++fmt)
	{
		padd = 0;
		write(fd, l_fmt, fmt - l_fmt - 1);
		if (*fmt >= '0' && *fmt <= '9')
		{
			padd = ft_atoi(fmt);
			fmt += nb_len(padd);
		}
		if (*fmt == '%')
			char_fd('%', fd, padd);
		else if (*fmt == 's')
			str_fd(va_arg(args, char *), fd, padd);
		else if (*fmt == 'c')
			char_fd(fd, (char)va_arg(args, int), padd);
		else if (*fmt == 'x' || *fmt == 'X')
			handle_hexa(fd, args, padd, fmt);
		else
			handle_dlu(fd, args, padd, fmt);
		l_fmt = ++fmt;
	}
	str_fd(l_fmt, fd, 0);
}
