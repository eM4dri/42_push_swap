/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keep_longest_rally.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 20:32:12 by emadriga          #+#    #+#             */
/*   Updated: 2024/01/02 16:46:54 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static t_stack	*next_node(const t_stack *first, const t_stack *current)
{
	if (current->next != NULL)
		return (current->next);
	else
		return ((t_stack *)first);
}

/**
* * Get longest rally of numbers ordered starting on current node of the stack
* Using 1st pivot we eval if next node is bigger populate our counter
* With 2nd pivot we can adjust longest unnecesary jumps
* It's not perfect solution since a brute force could find better results than
* this 2 pivots solutions
* @param first first node of a stack
* @param current current node of a stack
*/
static uint	rally_ordered(const t_stack *first, const t_stack *current)
{
	t_stack	*n;
	uint	rally;
	uint	pivot;

	rally = 0;
	pivot = current->order;
	n = next_node(first, current);
	while (n != current)
	{
		if (n->order > pivot)
		{
			pivot = n->order;
			rally++;
		}
		n = next_node(first, n);
	}
	return (rally);
}

static uint	*get_rally_items(
						const t_stack *first,
						const t_stack *current,
						const uint max_rally
)
{
	uint	*rally_items;
	int		i;
	t_stack	*n;
	uint	pivot;

	pivot = current->order;
	rally_items = (uint *) malloc((max_rally + 1) * sizeof(uint));
	if (rally_items == NULL)
		return (NULL);
	i = 0;
	rally_items[i] = current->order;
	rally_items[max_rally] = 0;
	n = next_node(first, current);
	while (n != current)
	{
		if (n->order > pivot)
		{
			pivot = n->order;
			rally_items[++i] = n->order;
		}
		n = next_node(first, n);
	}
	return (rally_items);
}

uint	*get_longest_rally(const t_stack *first)
{
	t_stack	*current;
	uint	rally;
	uint	max_rally;
	t_stack	*max_rally_node;

	max_rally = 0;
	current = (t_stack *)first;
	max_rally_node = current;
	while (current != NULL)
	{
		rally = rally_ordered(first, current);
		if (max_rally < rally)
		{
			max_rally = rally;
			max_rally_node = current;
		}
		current = current->next;
	}
	return (get_rally_items(first, max_rally_node, max_rally + 1));
}
