/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prastoin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 09:48:27 by prastoin          #+#    #+#             */
/*   Updated: 2019/06/05 10:35:52 by prastoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include "common.h"

# define FLAG_N_MSG "Choose the player's number"
# define FLAG_D_MSG "Dump memory on 0 at N cycle"
# define FLAG_V_MSG "Enabled Verbose mod"

# define V_FILE "verbose"

typedef struct	s_datan
{
	size_t	num;
	char	*name;
}				t_datan;

typedef struct	s_flags
{
	t_datan	*num;
	int		dump_c;
	bool	verbose;
}				t_flags;

typedef struct	s_process
{
	uint8_t	actual_opcode;
	bool	carry;
	ssize_t	offset;
	bool	has_read;
	size_t	cycle_to_do;
	uint8_t	registre[REG_NUMBER][REG_SIZE];
	uint8_t	tampon[REG_SIZE];
	size_t	last_cycle_live;
	bool	is_alive;
	bool	said_live;
}				t_process;

typedef struct	s_vec
{
	size_t		len;
	size_t		capacity;
	t_process	processes[];
}				t_vec;

typedef struct	s_champ
{
# ifndef __wasm__

	char	name[PROG_NAME_LENGTH];
	char	comment[COMMENT_LENGTH];
	char	prog[CHAMP_MAX_SIZE];
	size_t	size;
# endif

	int		fd;
}				t_champ;

typedef struct	s_vm
{
	uintmax_t	cycle;
	intmax_t	i_to_die;
	intmax_t	cycle_to_die;
	size_t		nbr_live;
	t_champ		champ[MAX_PLAYERS];
	size_t		last_champ_alive;
	size_t		nbr_champ;
	size_t		check;
	t_vec		*vec;
	size_t		c_pc;
	t_flags		flags;
	t_write		v;
	uint8_t		mem[MEM_SIZE];
}				t_vm;

t_vm			init_vm(void);
bool			ft_check_ocp(uint8_t ocp, uint8_t opcode);
bool			ft_get_value(ssize_t nbr, uint8_t type, t_process *processes,
	t_vm *vm);
bool			ft_get_value_mod(ssize_t nbr, uint8_t type, t_process *process,
	t_vm *vm);
void			mem_write(uint8_t mem[MEM_SIZE], const uint8_t *value,
	ssize_t offset, size_t size);
void			mem_read(const uint8_t mem[MEM_SIZE], uint8_t str[],
	ssize_t offset, size_t size);
void			mem_write_one(uint8_t mem[MEM_SIZE], uint8_t c, ssize_t offset);
void			mem_write_int(uint8_t mem[MEM_SIZE], size_t nb, size_t len,
	ssize_t offset);
bool			ft_play(t_vm *vm);
t_vec			*create_process(size_t capacity);
t_process		*add_process(t_vec **list);

bool			carry_down(t_vm *vm, t_process *process, uint8_t ocp, int opcd);
bool			carry_up(t_vm *vm, t_process *process, uint8_t ocp, int opcode);
bool			invalid(t_vm *vm, t_process *process, uint8_t ocp, int opcode);
bool			valid(t_vm *vm, t_process *process, uint8_t ocp, int opcode);

bool			ft_pass(t_vm *vm, t_process *process);
bool			read_opcode(t_vm *vm, t_process *process);

/*
** bin_operand
*/
bool			bin_add(uint8_t op1[REG_SIZE], uint8_t op2[REG_SIZE],
	uint8_t res[REG_SIZE]);
bool			bin_sub(uint8_t op1[REG_SIZE], uint8_t op2[REG_SIZE],
	uint8_t res[REG_SIZE]);
void			bin_and(uint8_t op1[REG_SIZE], uint8_t op2[REG_SIZE],
	uint8_t res[REG_SIZE]);
void			bin_or(uint8_t op1[REG_SIZE], uint8_t op2[REG_SIZE],
	uint8_t res[REG_SIZE]);
void			bin_xor(uint8_t op1[REG_SIZE], uint8_t op2[REG_SIZE],
	uint8_t res[REG_SIZE]);
intmax_t		conv_bin_num(uint8_t *mem, size_t len);
void			conv_int_to_bin(size_t nbr, uint8_t op[REG_SIZE]);
void			copy_process(t_process *dest, t_process *src);

/*
** op.c
*/

typedef	bool	(*t_core_fcnt)(t_vm *, t_process *, int32_t *, uint8_t);

bool			live(t_vm *vm, t_process *prc, int32_t param[4], uint8_t ocp);
bool			ld(t_vm *vm, t_process *prc, int32_t param[4], uint8_t ocp);
bool			st(t_vm *vm, t_process *prc, int32_t param[4], uint8_t ocp);
bool			add(t_vm *vm, t_process *prc, int32_t param[4], uint8_t ocp);
bool			sub(t_vm *vm, t_process *prc, int32_t param[4], uint8_t ocp);
bool			ft_and(t_vm *vm, t_process *prc, int32_t param[4], uint8_t ocp);
bool			ft_or(t_vm *vm, t_process *prc, int32_t param[4], uint8_t ocp);
bool			ft_xor(t_vm *vm, t_process *prc, int32_t param[4], uint8_t ocp);
bool			zjmp(t_vm *vm, t_process *prc, int32_t param[4], uint8_t ocp);
bool			ldi(t_vm *vm, t_process *prc, int32_t param[4], uint8_t ocp);
bool			sti(t_vm *vm, t_process *prc, int32_t param[4], uint8_t ocp);
bool			ft_fork(t_vm *vm, t_process *prc, int32_t param[4], uint8_t oc);
bool			lld(t_vm *vm, t_process *prc, int32_t param[4], uint8_t ocp);
bool			lldi(t_vm *vm, t_process *prc, int32_t param[4], uint8_t ocp);
bool			lfork(t_vm *vm, t_process *prc, int32_t param[4], uint8_t ocp);
bool			aff(t_vm *vm, t_process *prc, int32_t param[4], uint8_t ocp);

/*
** aff_fcnt_vm.c
*/

void			print_a(t_vm *vm, uint8_t op1[REG_SIZE],
	uint8_t tampon[REG_SIZE], int32_t param);
void			print_b(t_vm *vm, t_process *process, uint8_t adr[REG_SIZE],
	int64_t adress);
void			affsti(t_vm *vm, uint8_t op1[REG_SIZE], t_process *process,
	int32_t param[4]);
void			affldi(t_vm *vm, uint8_t op1[REG_SIZE], t_process *process,
	int32_t param[4]);

/*
** exec_vm.c
*/

bool			ft_winner(t_champ champ[MAX_PLAYERS], t_vm *vm);
bool			cycle_decremente_die(t_vm *vm);
void			kill_player(t_vm *vm);
bool			kill_process(t_vm *vm, size_t dead);
bool			vm_cycle_to_die(t_vm *vm);

/*
 ** vm_aff.c
*/

void			dump_mem(t_vm *vm);
void			affstart_verbose(t_vm *vm);

/*
 ** play.c
*/

bool			david_needs_to_work(t_vm *vm);

extern t_core_fcnt g_fcnt[17];

void			ft_dump_mem(t_vm vm, bool ex);

/*
** Hooks
*/
void			hook_process_adv(t_vm *vm, t_process *process, size_t diff);
void			hook_process_jump(t_vm *vm, t_process *process, uint32_t param,
	size_t offset);
void			hook_process_spawn(t_process *process, t_process *parent,
	size_t offset);
void			hook_process_live(t_vm *vm, t_process *process, size_t player);
void			hook_process_die(t_vm *vm, t_process *process);
bool			hook_cycle_end(t_vm *vm);
void			hook_process_read_opcode(t_process *process, uint8_t opcode);
void			hook_process_memory_write(t_process *process, size_t offset,
	size_t size);
void			hook_cycle_to_die(t_vm *vm, size_t value);
void			hook_win(t_vm *vm, size_t player);
#endif
