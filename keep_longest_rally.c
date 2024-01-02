/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keep_longest_rally.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 20:32:12 by emadriga          #+#    #+#             */
/*   Updated: 2024/01/02 17:01:49 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static uint	get_rally_length(uint *rally_items)
{
	uint	len;

	len = 0;
	while (rally_items[len] != 0)
		len++;
	return (len);
}

void	leave_rally(
	t_stack_extended *a,
	t_stack_extended *b,
	uint *rally_items
)
{
	const uint	len_rally = get_rally_length(rally_items);
	int			i;

	while (a->len != len_rally)
	{
		i = 0;
		while (rally_items[i] != 0 && (*a->s)->order != rally_items[i])
			i++;
		if (rally_items[i] == 0)
		{
			push_ext(a, b, STACKB);
		}
		else
			ft_rotate(a->s, b->s, STACKA);
	}
}

/**
* * Leave on stack A the longest posible rally moving everything to B
* It isn't the longest raw, just a polished one
* @param first first node of a stack
*/
void	keep_longest_rally(t_stack_extended *a, t_stack_extended *b)
{
	uint	*rally_items;

	a->len = get_stack_len(*a->s);
	b->len = 0;
	rally_items = get_longest_rally(*a->s);
	if (rally_items == NULL)
		return ;
	leave_rally(a, b, rally_items);
	free(rally_items);
}
