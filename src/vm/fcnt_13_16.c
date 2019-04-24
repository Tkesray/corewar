/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fcnt_13_16.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prastoin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 13:31:01 by prastoin          #+#    #+#             */
/*   Updated: 2019/04/24 11:06:26 by prastoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

bool		lld(t_vm *game, t_process *process, int32_t param[4], uint8_t ocp)
{
	if (param[1] > 16 || param[1] <= 0)
		return (invalid(process, ocp, 13));
	if (!ft_get_value(param[0], ocp >> 6 & 0b11, process, game))
		return (invalid(process, ocp, 13));
	ft_memcpy(process->registre[param[1] - 1], process->tampon, REG_SIZE);
	dprintf(g_fd, "P%5d | lld %ld r%d\n", g_opc, conv_bin_num(process->tampon, REG_SIZE), param[1]);
	if ((conv_bin_num(process->tampon, REG_SIZE)) == 0)
		return (carry_up(process, ocp, 13));
	else
		return (carry_down(process, ocp, 13));
}

bool		lldi(t_vm *game, t_process *process, int32_t param[4], uint8_t ocp)
{
	uint8_t		op1[REG_SIZE];
	uint8_t		adr[REG_SIZE];
	int64_t	adress;

	if (param[2] > 16 || param[2] <= 0)
		return (invalid(process, ocp, 14));
	if (!ft_get_value(param[0], (ocp >> 6 & 0b11), process, game))
		return (invalid(process, ocp, 14));
	ft_memcpy(op1, process->tampon, REG_SIZE);
	if (!ft_get_value(param[1], (ocp >> 4 & 0b11), process, game))
		return (invalid(process, ocp, 14));
	bin_add(op1, process->tampon, adr);
	adress = (conv_bin_num(adr, REG_SIZE));
	while ((process->offset + adress) < 0)
		adress += MEM_SIZE;
	mem_read(game->mem, process->registre[param[2] - 1], (process->offset + adress) % MEM_SIZE, REG_SIZE);
	dprintf(g_fd, "P%5d | lldi %ld %ld r%d\n", g_opc, conv_bin_num(op1, REG_SIZE), conv_bin_num(process->tampon, REG_SIZE), param[2]);
	dprintf(g_fd, "       | -> load from %ld + %ld = %ld (with pc and mod %ld)\n", conv_bin_num(op1, REG_SIZE), conv_bin_num(process->tampon, REG_SIZE), conv_bin_num(adr, REG_SIZE), (process->offset + adress) % MEM_SIZE);
	if ((conv_bin_num(process->registre[param[2] - 1], REG_SIZE)) == 0)
		return (carry_up(process, ocp, 14));
	else
		return(carry_down(process, ocp, 14));
}

bool		lfork(t_vm *game, t_process *process, int32_t param[4], uint8_t ocp)
{
	t_process	*new_process;
	size_t		index;
	int			save;

	save = param[0];
	while (param[0] + process->offset < 0)
		param[0] += MEM_SIZE;
	index = (process - game->vec->processes);
	new_process = add_process(&game->vec);
	process = game->vec->processes + index;
	*new_process = (t_process) {
		.offset = (process->offset + param[0]) % MEM_SIZE,
		.is_alive = true,
	};
	copy_process(new_process, process);
	dprintf(g_fd, "P%5d | lfork %d (%d)\n", g_opc, save, save + process->offset);
	return (valid(process, 0b11000000, 15));
}

bool		aff(t_vm *game, t_process *process, int32_t param[4], uint8_t ocp)
{
	size_t		i;
	uint8_t		c;

	(void)game;
	if (param[0] > 16 || param[0] <= 0)
		return (invalid(process, ocp, 16));
	i = 0;
	while (i < REG_SIZE)
	{
		c = (process->registre[param[0] - 1][i] % 256);
		write(1, &c, 1);
		i++;
	}
	return (valid(process, ocp, 16));
}