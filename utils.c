/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/22 12:04:34 by emadriga          #+#    #+#             */
/*   Updated: 2021/09/04 13:36:11 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_freestack(t_stack **stack)
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

int	get_stack_len(t_stack *stack)
{
	int		i;

	i = 0;
	while (stack != NULL)
	{
		stack = stack->next;
		i++;
	}
	return (i);
}

/**
 * return_to_a
 * * Push every item of stack src to dts
* @param src	stack src
* @param dts	stack dts
*/
void	push_src_to_dts(t_stack **src, t_stack **dts)
{
	int		len;
	t_stack	*aux;

	len = get_stack_len(*src);
	aux = *src;
	while (aux->order != len)
	{
		ft_reverse_rotate(dts, src, STACKB);
		aux = *src;
	}
	while (len--)
		ft_push(dts, src, STACKA);
}

/**
 * get_chunk_next_item
 * * Look the next item in a stack below maxvalue of the actual chunk
 * * Return next items from top and bot with values and positions, 1st closest
 * * Return position positive from top or negative otherwise
* @param stack	stack
* @param max	maxvalue of the chunk, top value to look for  
* @param stack_len	stack_len as an argument just for preformace
*/
t_chunk_item	get_chunk_next_item(t_stack *stack, int max, int stack_len)
{
	int				i;
	t_chunk_item	first;
	t_chunk_item	last;

	i = 0;
	first.pos = -1;
	while (stack != NULL)
	{
		if (stack->order <= max && first.pos == -1)
		{
			first.nbr = stack->order;
			first.pos = i;
		}
		if (stack->order <= max && first.pos != -1)
		{
			last.nbr = stack->order;
			last.pos = (stack_len - i) * -1;
		}
		stack = stack->next;
		i++;
	}
	if (first.pos <= (last.pos * -1))
		return (first);
	return (last);
}
