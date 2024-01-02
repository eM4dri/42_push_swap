/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 17:49:07 by emadriga          #+#    #+#             */
/*   Updated: 2024/01/02 20:47:51 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

#define ALLOWED_MOVES "unknown pa pb sa sb ra rb rr rra rrb rrr"

enum e_moves_allowed{
	UKNOWN,
	PA,
	PB,
	SA,
	SB,
	RA,
	RB,
	RR,
	RRA,
	RRB,
	RRR
};

/**
 * * This function recieves a list of strings (pointer to pointers) and frees
 * * everything, including the main pointer. The last string must be NULL.
 * @param list		array to free
**/
void	array_str_free(char ***list)
{
	int	a;

	a = 0;
	if (*list)
	{
		while ((*list)[a])
			free((*list)[a++]);
		free((*list)[a]);
		free(*list);
	}
}



void	print_stack(t_stack *node)
{
	while (node != NULL)
	{
		printf("%d ", node->order);
		node = node->next;
	}
	printf("\n");
}

static void	ft_freestack(t_stack **stack)
{
	t_stack	*aux;

	aux = *stack;
	while (aux != NULL)
	{
		aux = aux->next;
		free(*stack);
		*stack = aux;
	}
}

static int	isordered(t_stack *stack)
{
	uint	i;

	i = 1;
	while (stack != NULL)
	{
		if (i != stack->order)
			return (0);
		stack = stack->next;
		i++;
	}
	return (1);
}

static int check_moves (const char *move, char **moves_allowed){
	int	i;
	
	i = 0;
	while (moves_allowed[i] != 0)
	{
		if (!ft_strcmp(moves_allowed[i], move))
			return i;
		i++;
	}
	return KO;
}

void	do_move(int move, t_stack **a)
{	
	t_stack	*aux;

	if (move == PA)
		push(a, &aux);
	else if (move == PB)
		push(&aux, a);
	else if (move == SA)
		swap(a);
	else if (move == SB)
		swap(&aux);
	else if (move == RA || move == RB || move == RR)
	{
		if (move == RA || move == RR)
			rotate(a);
		if (move == RB || move == RR)
			rotate(&aux);
	}
	else 
	{
		if (move == RA || move == RR)
			reverse_rotate(a);
		if (move == RB || move == RR)
			reverse_rotate(&aux);
	}
}

static  int	read_moves(t_stack **a)
{
	int		error;
	char	*move;
	char	**moves_allowed;
	int		move_to;

	error = OK;
	moves_allowed = ft_split(ALLOWED_MOVES, ' ');
	while (error == OK && get_next_line (0, &move))
	{
		move_to = check_moves (move, moves_allowed);
		if (move_to == UKNOWN)
			error = KO;
		do_move (move_to, a);
		free(move);
	}
	array_str_free(&moves_allowed);
	return error;
}

int	main(int argc, char **argv)
{
	int		i;
	t_stack	*stacka;
	int		error;

	i = 0;
	error = 0;
	stacka = NULL;
	while (++i < argc)
	{
		if (parse_nbr(argv[i], &stacka) == KO)
		{
			write(2, "Error\n", 7);
			error = EINVAL;
			break ;
		}
	}
	if (read_moves(&stacka) == KO)
	{
		write(2, "Error\n", 7);
		error = EINVAL;
	}
	if (!error)
	{
		if (!isordered(stacka))
			write(1, "KO\n", 3);
		else
			write(1, "OK\n", 3);
	}
	ft_freestack(&stacka);
	return (error);
}
