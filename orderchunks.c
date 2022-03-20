/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   orderchunks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 17:49:03 by emadriga          #+#    #+#             */
/*   Updated: 2021/09/04 17:49:04 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/**
 * * Get sizes of your stack for an element regarding the number of chunks
 * * Return size, min, mid and max of the chunk of a stack's element
* @param item	Next item in the stack
* @param stack_len	Len of stack
* @param tot_chunks	Number of chunks
*/
static int	get_chunk_size_by_stacklen(int item, int stack_len, int tot_chunks)
{
	int	size;

	size = 0;
	if (stack_len == 100)
	{
		if (item < 51)
			size = 20;
		else if (item < 91)
			size = 15;
		else if (item < 101)
			size = 10;
	}
	else if (stack_len == 500)
	{
		if (item < 251)
			size = 50;
		else if (item < 401)
			size = 25;
		else if (item < 501)
			size = 20;
	}
	else
		size = stack_len / tot_chunks;
	return (size);
}

/**
 * * Get sizes of your stack for an element regarding the number of chunks
 * * Return size, min, mid and max of the chunk of a stack's element
* @param item	Next item in the stack
* @param stack_len	Len of stack
* @param tot_chunks	Number of chunks
*/
static t_chunk_sizes	get_chunk_sizes(int item, int stack_len, int tot_chunks)
{
	t_chunk_sizes	chunk;

	chunk.size = get_chunk_size_by_stacklen(item, stack_len, tot_chunks);
	chunk.max = (1 + item / chunk.size) * chunk.size;
	chunk.min = chunk.max - chunk.size;
	chunk.mid = chunk.size + (chunk.max - chunk.size) / 2;
	return (chunk);
}

/**
 * * Order asc using N chunks 
* @param a	stack 1
* @param b	stack 2
* @param tot_chunks	Number of chunks
*/
void	order_with_chunks(t_stack **a, t_stack **b, int tot_chunks)
{
	int		b_len;
	int		maxstack_len;
	t_chunk	c;

	maxstack_len = get_stack_len(*a);
	b_len = 0;
	while (b_len < maxstack_len)
	{
		c.sizes = get_chunk_sizes(b_len, maxstack_len, tot_chunks);
		c.item = get_chunk_next_item(*a, c.sizes.max, maxstack_len - b_len);
		prepare_pushb(a, b, &c);
		ft_push(a, b, STACKB);
		if (++b_len == 3)
			reverseorder3(b, STACKB);
	}
	push_src_to_dts(b, a);
}
