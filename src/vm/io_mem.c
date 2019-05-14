/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_io.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prastoin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 15:15:12 by prastoin          #+#    #+#             */
/*   Updated: 2019/05/14 14:19:25 by prastoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		mem_read(const uint8_t mem[MEM_SIZE], uint8_t *dst,
		ssize_t offset, size_t n)
{
	size_t i;

	while (offset < 0)
		offset += MEM_SIZE;
	offset %= MEM_SIZE;
	i = 0;
	while (i < n)
	{
		(dst)[i] = mem[(offset + i) % MEM_SIZE];
		i++;
	}
}

void		mem_write(uint8_t mem[MEM_SIZE], const uint8_t *src,
		ssize_t offset, size_t n)
{
	size_t i;

	while (offset < 0)
		offset += MEM_SIZE;
	offset %= MEM_SIZE;
	i = 0;
	while (i < n)
	{
		mem[(offset + i) % MEM_SIZE] = (src)[i];
		i++;
	}
}

void		mem_write_one(uint8_t mem[MEM_SIZE], uint8_t c,
		ssize_t offset)
{
	mem_write(mem, &c, offset, 1);
}

void		mem_write_int(uint8_t mem[MEM_SIZE], size_t nb, size_t len,
		ssize_t offset)
{
	while (len != 0)
	{
		len--;
		mem_write_one(mem, (nb >> (len * 8)) & 0xFF, offset);
	}
}
