/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 17:49:07 by emadriga          #+#    #+#             */
/*   Updated: 2024/01/04 16:24:30 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus/push_swap.h"

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

static int	check_moves(const char *move)
{
	int			i;
	const char	*moves_allowed[] = \
	{"unknown", "pa", "pb", "sa", "sb", "rra", "rrb", "rrr", "ra", "rb", "rr"};

	i = 0;
	while (i < 11)
	{
		if (!ft_strcmp(moves_allowed[i], move))
			return (i);
		i++;
	}
	return (UKNOWN);
}

static int	read_moves(t_stack **a)
{
	char	*move;
	int		move_to;
	t_stack	*aux;

	aux = NULL;
	while (get_next_line(0, &move))
	{
		move_to = check_moves(move);
		if (move_to == UKNOWN)
			return (EINVAL);
		ft_move(move_to, a, &aux);
		free(move);
	}
	if (move[0] != '\0')
	{
		move_to = check_moves(move);
		if (move_to == UKNOWN)
			return (EINVAL);
		ft_move(move_to, a, &aux);
	}
	free(move);
	return (NO_ERROR);
}

int	main(int argc, char **argv)
{
	int			i;
	int			error;
	t_stack		*stacka;

	if (argc == 1)
		return (NO_ERROR);
	i = 0;
	error = NO_ERROR;
	stacka = NULL;
	while (error == NO_ERROR && ++i < argc)
		error = parse_nbr(argv[i], &stacka);
	if (error == NO_ERROR)
		error = read_moves(&stacka);
	if (error != NO_ERROR)
		write(2, "Error\n", 7);
	else if (!isordered(stacka))
		write(1, "KO\n", 3);
	else
		write(1, "OK\n", 3);
	ft_freestack(&stacka);
	return (error);
}
