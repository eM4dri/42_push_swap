/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 17:49:07 by emadriga          #+#    #+#             */
/*   Updated: 2021/09/11 13:55:33 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	isordered(t_stack *stack)
{
	int	i;

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
	else if (stack_len == 100 || stack_len == 500)
		order_with_chunks(stack, &aux, 5);
	else
		orderbydefault(stack, &aux);
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
			write(1, "Error\n", 7);
			error = EINVAL;
			break ;
		}
	}
	if (!error && !isordered(stacka))
		do_rotate(&stacka);
	ft_freestack(&stacka);
	return (error);
}
