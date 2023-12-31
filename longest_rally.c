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
static size_t rally_ordered(const t_stack *first, const t_stack *current)
{
	t_stack	*n;
	size_t	rally;
	int		pivot;

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

size_t *get_rally_items(const t_stack *first, const t_stack *current, const int	max_rally){
	size_t	*rally_items;
	int		i;
	t_stack	*n;
	int		pivot;

	pivot = current->order;
	rally_items = malloc(max_rally * sizeof(int));
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

size_t *get_longest_rally_orderer(const t_stack *first){
	t_stack	*current;
	size_t	rally;
	size_t	max_rally;
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
	printf("%d is the longest rally with %ld\n", max_rally_node->order, max_rally);
	return get_rally_items(first, max_rally_node, max_rally + 1);
}

size_t get_rally_length(size_t *rally_items){
	size_t	len;

	len = 0;
	while (rally_items[len] != 0)
		len++;
	return len;
}

void leave_rally(t_stack **a, t_stack **b, size_t *rally_items){
	const size_t	len_rally = get_rally_length(rally_items);
	int				i;

	while (get_stack_len(*a) != (int)len_rally)
	{
		i = 0;
		while (rally_items[i] != 0 && (*a)->order != (int)rally_items[i])
			i++;
		if (rally_items[i] == 0)
			ft_push(a, b, STACKB);
		else
			ft_rotate(a, b, STACKA);
	}
}

/**
* * Leave on stack A the longest posible rally moving everything to B
* It isn't the longest raw, just a polished one
* @param first first node of a stack
*/
void longest_rally_orderer(t_stack **a, t_stack **b){
	size_t		*rally_items;
	// t_stack		*node;

	rally_items = get_longest_rally_orderer(*a);
	if (rally_items == NULL)
		return ; //! ERROR
	leave_rally(a, b, rally_items);
	print_stack(*a);
	printf("\n\n");
	free(rally_items);
	// t_stack	*current;
	// size_t	rally;
	// size_t	max_rally;
	// t_stack	*max_rally_node;
	// (void)b;

	// max_rally = 0;
	// current = *a;
	// while (current != NULL)
	// {
	// 	rally = rally_ordered(*a, current);
	// 	if (max_rally < rally){
	// 		max_rally = rally;
	// 		max_rally_node = current;
	// 	}
	// 	// printf("N %d\tR%ld\n", current->order, rally);
	// 	current = current->next;
	// }
	// printf("%d is the longest rally with %ld\n", max_rally_node->order, max_rally);
	// get_rally_items(*a, max_rally_node, (int)max_rally);
}
