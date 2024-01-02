/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/22 10:57:27 by emadriga          #+#    #+#             */
/*   Updated: 2024/01/02 20:41:15 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/**
 * * Swap the first 2 elements at the top of stack. Do nothing if there
is only one or no elements).
* @param stack		stack
*/
void	swap(t_stack **stack)
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

/**
 * * Take the first element at the top of source and put it at the top of
 destination. Do nothing if source is empty.
* @param dts	stack destination
* @param src	stack source
*/
void	push(t_stack **dts, t_stack **src)
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

/**
 * reverse_rotate
 * * Shift down all elements of stack a by 1. The last element
becomes the first one
* @param stack		stack
*/
void	reverse_rotate(t_stack **stack)
{
	t_stack	*first;
	t_stack	*old_last;
	t_stack	*new_last;

	if (*stack != NULL)
	{
		new_last = *stack;
		if (new_last->next != NULL)
		{
			old_last = new_last->next;
			while (old_last->next != NULL)
			{
				old_last = old_last->next;
				new_last = new_last->next;
			}
			first = *stack;
			*stack = old_last;
			old_last->next = first;
			new_last->next = NULL;
		}
	}
}

/**
 * rotate
 * * Shift up all elements of stack a by 1. The first element becomes
the last one.
* @param stack		stack
*/
void	rotate(t_stack **stack)
{
	t_stack	*first;
	t_stack	*aux;

	if (*stack != NULL)
	{
		first = *stack;
		if (first->next != NULL)
		{
			aux = *stack;
			*stack = aux->next;
			while (aux->next != NULL)
			{
				aux = aux->next;
			}
			first->next = NULL;
			aux->next = first;
		}
	}
}