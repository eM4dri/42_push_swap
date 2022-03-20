/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/22 10:57:27 by emadriga          #+#    #+#             */
/*   Updated: 2021/09/04 12:58:52 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/**
 * * Swap the first 2 elements at the top of stack. Do nothing if there
is only one or no elements).
* @param stack		stack
*/
static void	swap(t_stack **stack)
{
	t_stack	*first;
	t_stack	*second;

	if (*stack != NULL)
	{
		first = *stack;
		if (first->next != NULL)
		{
			second = first->next;
			first->next = second->next;
			second->next = first;
			*stack = second;
		}
	}
}

void	ft_swap(t_stack **a, t_stack **b, int mode)
{
	if (mode == STACKA)
		write(1, "sa\n", 3);
	else if (mode == STACKB)
		write(1, "sb\n", 3);
	else if (mode == BOTHSTACKS)
		write(1, "ss\n", 3);
	if (mode == STACKA || mode == BOTHSTACKS)
		swap(a);
	if (mode == STACKB || mode == BOTHSTACKS)
		swap(b);
}

/**
 * * Take the first element at the top of source and put it at the top of 
 destination. Do nothing if source is empty.
* @param dts	stack destination
* @param src	stack source
*/
static void	push(t_stack **dts, t_stack **src)
{
	t_stack	*src_1st_old;
	t_stack	*dts_1st_old;

	if (*src != NULL)
	{
		src_1st_old = *src;
		dts_1st_old = *dts;
		*src = src_1st_old->next;
		src_1st_old->next = dts_1st_old;
		*dts = src_1st_old;
	}
}

void	ft_push(t_stack **a, t_stack **b, int mode)
{
	if (mode == STACKA)
	{
		write(1, "pa\n", 3);
		push(a, b);
	}
	else if (mode == STACKB)
	{
		write(1, "pb\n", 3);
		push(b, a);
	}
}
