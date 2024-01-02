/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   longest_rally.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 20:32:12 by emadriga          #+#    #+#             */
/*   Updated: 2024/01/02 15:08:05 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_stack *next_node(const t_stack *first, const t_stack *current)
{
	if (current->next != NULL)
		return current->next;
	else
		return (t_stack *)first;
}

/**
* * Get longest rally of numbers ordered starting on current node of the stack
* Using 1st pivot we eval if next node is bigger populate our counter
* With 2nd pivot we can adjust longest unnecesary jumps
* It's not perfect solution since a brute force could find better results than this 2 pivots solutions
* @param first first node of a stack
* @param current current node of a stack
*/
static __u_int rally_ordered(const t_stack *first, const t_stack *current)
{
	t_stack	*n;
	__u_int	rally;
	__u_int	pivot;

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
	return rally;
}

__u_int *get_rally_items(const t_stack *first, const t_stack *current, const __u_int	max_rally){
	__u_int	*rally_items;
	int		i;
	t_stack	*n;
	__u_int	pivot;

	pivot = current->order;
	rally_items = (__u_int *) malloc((max_rally + 1) * sizeof(__u_int));
	if (rally_items == NULL)
		return NULL;
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
	return rally_items;
}

__u_int *get_longest_rally_orderer(const t_stack *first){
	t_stack	*current;
	__u_int	rally;
	__u_int	max_rally;
	t_stack	*max_rally_node;

	max_rally = 0;
	current = (t_stack *)first;
	while (current != NULL)
	{
		rally = rally_ordered(first, current);
		if (max_rally < rally){
			max_rally = rally;
			max_rally_node = current;
		}
		current = current->next;
	}
	return get_rally_items(first, max_rally_node, max_rally + 1);
}

__u_int get_rally_length(__u_int *rally_items){
	__u_int	len;

	len = 0;
	while (rally_items[len] != 0)
		len++;
	return len;
}

void leave_rally(t_stack_extended *a, t_stack_extended *b, __u_int *rally_items){
	const __u_int	len_rally = get_rally_length(rally_items);
	int				i;

	while (a->len != len_rally)
	{
		i = 0;
		while (rally_items[i] != 0 && (*a->s)->order != rally_items[i])
			i++;
		if (rally_items[i] == 0){
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
void longest_rally_orderer(t_stack_extended *a, t_stack_extended *b){
	__u_int	*rally_items;

	a->len = get_stack_len(*a->s);
	b->len = 0;
	rally_items = get_longest_rally_orderer(*a->s);
	if (rally_items == NULL)
		return ; //! ERROR
	leave_rally(a, b, rally_items);
	free(rally_items);
}
