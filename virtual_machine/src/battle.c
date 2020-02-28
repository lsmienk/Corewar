/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   battle.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: kpereira <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/08 12:43:00 by kpereira       #+#    #+#                */
/*   Updated: 2020/02/21 14:34:27 by lsmienk       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "corewar_vm.h"

static int		correct_cycle_to_die(int *cycle_to_die)
{
	*cycle_to_die -= 50;
	return (0);
}

static int		check(t_vm *vm, int *cycle_to_die)
{
	t_cursor	*tmp;
	t_cursor	*previous;
	static int	max_checks = 0;

	tmp = vm->cursors;
	vm->n_lives = 0;
	previous = NULL;
	while (tmp != NULL)
	{
		if (vm->n_cycles - tmp->last_live >= *cycle_to_die ||
			*cycle_to_die <= 0)
			kill_cursor(previous, &tmp, vm);
		else
		{
			previous = tmp;
			tmp = tmp->next;
		}
	}
	if (vm->n_lives_check >= NBR_LIVE || max_checks == MAX_CHECKS)
		max_checks = correct_cycle_to_die(cycle_to_die);
	else
		max_checks++;
	if (vm->n_process > 0)
		return (1);
	return (0);
}

static void		get_ops_code(t_cursor *tmp, t_vm *vm)
{
	if (vm->arena[tmp->position] > 0 && vm->arena[tmp->position] < 17)
	{
		tmp->opcode = vm->arena[tmp->position];
		get_wait_cycle(tmp);
	}
	else
	{
		tmp->opcode = 0;
		if (tmp->position < MEM_SIZE - 1)
			tmp->position++;
		else
			tmp->position = 0;
	}
}

void			execute_each_cursor(t_vm *vm, t_cursor *cursors)
{
	t_cursor	*tmp;

	tmp = cursors;
	while (tmp)
	{
		if (tmp && !tmp->opcode)
		{
			get_ops_code(tmp, vm);
			if (vm->n_cycles != 0)
				decrease_wait_cycles(tmp);
		}
		else
		{
			decrease_wait_cycles(tmp);
			if (tmp->opcode && !tmp->wait_cycles)
			{
				get_argument_types(vm, tmp);
				do_operation(tmp, vm);
				ft_bzero(tmp->arguments, sizeof(t_argument));
				tmp->position += tmp->jump;
				tmp->opcode = 0;
			}
		}
		tmp = tmp->next;
	}
}

void			thebattle(t_vm *vm)
{
	int			cycle_to_die;
	int			current_cycles;
	int			any_alive;

	cycle_to_die = CYCLE_TO_DIE;
	any_alive = 1;
	while (any_alive)
	{
		current_cycles = 0;
		while (current_cycles < cycle_to_die)
		{
			execute_each_cursor(vm, vm->cursors);
			if (vm->visu_flag == 1)
				visu_update(vm);
			current_cycles++;
			vm->n_cycles++;
			if (vm->dump_flag && vm->dump_cycle == vm->n_cycles)
			{
				display_arena(vm);
				exit(0);
			}
		}
		any_alive = check(vm, &cycle_to_die);
		vm->n_lives_check = 0;
	}
}
