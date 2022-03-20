/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   order100.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/29 18:38:56 by emadriga          #+#    #+#             */
/*   Updated: 2021/09/04 13:44:49 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/**
 * get_stack_stats
 * * Get stats of your stack referenced with the actual chunk
 * * Return 1st, 2nd, last, min and max of stack above a minimun value
* @param stack	stack
* @param min	minvalue of the chunk, minimun value to look for 
*/
static t_stack_stats	get_stack_stats(t_stack *stack, int min)
{
	t_stack_stats	result;

	result.first = stack->order;
	result.second = stack->next->order;
	result.min = min;
	result.max = 0;
	while (stack != NULL)
	{
		if (result.max < stack->order)
			result.max = stack->order;
		if (result.min > stack->order && result.min > min)
			result.min = stack->order;
		if (result.min == min && result.min < stack->order)
			result.min = stack->order;
		result.last = stack->order;
		stack = stack->next;
	}
	return (result);
}

/**
 * get_stackb_move
 * * Eval if stackb has to move and how
 * * Return 0 don't 1 rotate -1 reverse
* @param s	stack stats
* @param nbr	next nbr to add
*/
static int	get_stackb_move(t_stack_stats s, int nbr)
{
	if (s.first > nbr && s.first > s.second)
	{
		if (s.last == s.min && s.first == s.max && s.last > nbr)
			return (0);
		return (1);
	}
	else if (s.first > nbr && s.second == s.max)
		return (1);
	else if (s.first < nbr && s.last < nbr && s.last > s.first)
		return (-1);
	return (0);
}

/**
 * move_stacks
 * * Prepare stack b for next chunk polishing current order
* @param a	stack a
* @param b	stack b
* @param c	chunk
*/
static int	move_stacks(t_stack **a, t_stack **b, t_chunk c)
{
	int	b_moves;

	b_moves = get_stackb_move(get_stack_stats(*b, c.sizes.min), c.item.nbr);
	if (b_moves > 0 && c.item.pos > 0)
		ft_rotate(a, b, BOTHSTACKS);
	else if (b_moves < 0 && c.item.pos < 0)
		ft_reverse_rotate(a, b, BOTHSTACKS);
	else
	{
		if (c.item.pos > 0)
			ft_rotate(a, b, STACKA);
		else if (c.item.pos < 0)
			ft_reverse_rotate(a, b, STACKA);
		if (b_moves > 0)
			ft_rotate(a, b, STACKB);
		else if (b_moves < 0 )
			ft_reverse_rotate(a, b, STACKB);
		else if (c.item.pos == 0)
			return (0);
	}
	return (1);
}

/**
 * prepareb_nextchunk
 * * Prepare stack b for next chunk polishing current order
* @param a	stack a
* @param b	stack b
* @param chunk	chunk
*/
static void	prepareb_nextchunk(t_stack **a, t_stack **b, t_chunk *chunk)
{
	int		len_a;
	t_stack	*aux;

	len_a = get_stack_len(*a);
	while (1)
	{
		aux = *b;
		if (aux->order >= chunk->sizes.min)
			break ;
		if (chunk->item.pos != 0)
		{
			ft_reverse_rotate(a, b, BOTHSTACKS);
			chunk->item = get_chunk_next_item(*a, chunk->sizes.max, len_a);
		}
		else
			ft_reverse_rotate(a, b, STACKB);
	}
}

/**
 * prepare_pushb
 * * Prepare stack b to receive push 
* @param a	stack a
* @param b	stack b
* @param chunk	chunk
*/
void	prepare_pushb(t_stack **a, t_stack **b, t_chunk *chunk)
{
	if (get_stack_len(*b) > 2)
	{
		prepareb_nextchunk(a, b, chunk);
		while (1)
		{
			if (!move_stacks(a, b, *chunk))
				break ;
			chunk->item.pos -= (chunk->item.pos > 0);
			chunk->item.pos += (chunk->item.pos < 0);
		}
	}
	else
	{
		while (chunk->item.pos > 0 && chunk->item.pos--)
			ft_rotate(a, b, STACKA);
		while (chunk->item.pos < 0 && chunk->item.pos++)
			ft_reverse_rotate(a, b, STACKA);
	}
}
