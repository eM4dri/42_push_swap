/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 17:49:07 by emadriga          #+#    #+#             */
/*   Updated: 2024/01/02 16:38:04 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	print_stack(t_stack *node)
{
	while (node != NULL)
	{
		printf("%d ", node->order);
		node = node->next;
	}
	printf("\n");
}

static int	isordered(t_stack *stack)
{
	__u_int	i;

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

void	default_order(t_stack **stack_a, t_stack **stack_b)
{
	t_stack_extended	a;
	t_stack_extended	b;

	a.s = stack_a;
	b.s = stack_b;
	longest_rally_orderer(&a, &b);
	less_moves_to_order(&a, &b);
}

static void	do_rotate(t_stack **stack)
{
	int		stack_len;
	t_stack	*aux;

	aux = NULL;
	stack_len = get_stack_len(*stack);
	if (stack_len == 2)
		ft_swap(stack, &aux, STACKA);
	else if (stack_len == 3)
		order3(stack, STACKA);
	else if (stack_len <= 5)
		order5(stack, &aux);
	else
		default_order(stack, &aux);
	ft_freestack(&aux);
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
		if (!parse_nbr(argv[i], &stacka))
		{
			write(2, "Error\n", 7);
			error = EINVAL;
			break ;
		}
	}
	if (!error && !isordered(stacka))
		do_rotate(&stacka);
	ft_freestack(&stacka);
	return (error);
}
