/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fcnt_01_04.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prastoin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 13:22:08 by prastoin          #+#    #+#             */
/*   Updated: 2019/04/22 15:29:20 by prastoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

bool		live(t_vm *game, t_process *process, int32_t param[4], uint8_t ocp)
{
	int32_t		player;

	(void)ocp;
	player = (int32_t)param[0];
	player = -player;
	printf("live de %zu\n", player);
	process->said_live = true;
	if (player >= 1 && player <= MAX_PLAYERS)
	{
		if (game->live[player - 1])
		{
			game->said_live[player - 1] = true;
			game->champ[player - 1].last_cycle_live = game->cycle;
		}
	}
	game->nbr_live++;
	return (valid(process, 0b1000, 1));
}

bool		ld(t_vm *game, t_process *process, int32_t param[4], uint8_t ocp)
{
	if (param[1] >= 16 || param[1] < 0)
		return (carry_down(process, ocp, 2));
	if (!ft_get_value_mod(param[0], ocp >> 6 & 0b11, process, game))
		return (carry_down(process, ocp, 2));
	ft_memcpy(process->registre[param[1]], process->tampon, REG_SIZE);
	return (carry_up(process, ocp, 2));
}

bool		st(t_vm *game, t_process *process, int32_t param[4], uint8_t ocp)
{
	if (param[0] >= 16 || param[0] < 0)
		return (carry_down(process, ocp, 3));
	if ((ocp >> 4 & 0b11) == OCP_REG)
	{
		if (param[1] >= 16)
			return (invalid(process, ocp, 3));
		else
			ft_memcpy(process->registre[param[1]],
					process->registre[param[0]], REG_SIZE);
	}
	else
	{
		mem_write(game->mem, process->registre[param[0]], (process->offset + (param[1] % IDX_MOD)), REG_SIZE);
	}
	ft_dump_process(process);
	return (valid(process, ocp, 3));
}

bool		add(t_vm *game, t_process *process, int32_t param[4], uint8_t ocp)
{
	uint8_t op1[REG_SIZE];

	if (param[2] >= 16 || param[2] < 0)
		return (carry_down(process, ocp, 4));
	if (!(ft_get_value_mod(param[0], (ocp >> 6 & 0b11), process, game)))
		return (carry_down(process, ocp, 4));
	ft_memcpy(op1, process->tampon, REG_SIZE);
	if (!(ft_get_value_mod(param[1], (ocp >> 4 & 0b11), process, game)))
		return (carry_down(process, ocp, 4));
	if (!(bin_add(op1, process->tampon, process->registre[param[2]])))
		return (carry_down(process, ocp, 4));
	return (carry_up(process, ocp, 4));
}
