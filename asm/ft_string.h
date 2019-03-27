/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prastoin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 10:07:00 by prastoin          #+#    #+#             */
/*   Updated: 2019/03/27 14:31:33 by prastoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STRING_H
#define FT_STRING_H

#include <stdlib.h>
#include <unistd.h>

# define BUFF_SIZE 4096
# define CSI "\033["
# define CSI_GREEN CSI "32;01m"
# define CSI_WHITE CSI "37;01m"
# define CSI_BLUE CSI "34;01m"
# define CSI_YELLOW CSI "33;01m"
# define CSI_RED CSI "31m"
# define CSI_RESET CSI "0m"

size_t	ft_strlen(const char *str);
uint8_t	*ft_strcpy(uint8_t *dst, const uint8_t *src);
size_t	search_for(uint8_t *str, uint8_t c);
ssize_t	ft_strncmp(uint8_t *s1, char *str, size_t n);
ssize_t		ft_strcmp(const char *s1, const char *s2);
size_t		atoi_hexa(char nb[], size_t size);
void	ft_putf_fd(int fd, char *fmt, ...);
void		ft_putstr_fd(char *str, size_t fd);

#endif
