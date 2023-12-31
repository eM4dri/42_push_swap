#include "push_swap.h"

typedef struct s_rally_utils
{
	int	min;
	int	max;
	int rally;
}t_rally_utils;

static void init_rally(t_stack **node, t_rally_utils *u, const t_stack *first, const t_stack *current){
	u->rally = 0;
	u->min = current->order;
	u->max = current->order;
	if (current->next != NULL)
		*node = current->next;
	else
		*node = (t_stack *)first;
}

int is_rally_item(const t_stack	*n, t_rally_utils *u)
{
	if (u->max > n->order && n->order > u->min)
		u->max = n->order;
	else if (n->order > u->max)
	{
		if (u->max > u->min)
			u->min = u->max;
		u->max = n->order;
	}
	else
		return FALSE;
	return TRUE;
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
	t_stack			*n;
	t_rally_utils	u;

	init_rally(&n, &u, first, current);
	while (n != current)
	{
		if (is_rally_item(n, &u) == TRUE)
			u.rally++;
		n = n->next;
		if (n == NULL)
			n = (t_stack *)first;
	}
	return u.rally;
}

size_t *get_rally_items(const t_stack *first, const t_stack *current, const int	max_rally){
	size_t			*rally_items;
	int				i;
	t_stack			*n;
	t_rally_utils	u;

	init_rally(&n, &u, first, current);
	rally_items = malloc(max_rally * sizeof(int));
	if (rally_items == NULL)
		return NULL;
	i = 0;
	rally_items[i] = current->order;
	rally_items[max_rally] = 0;
	while (n != current)
	{
		if (is_rally_item(n, &u) == TRUE)
			rally_items[++i] = n->order;
		n = n->next;
		if (n == NULL)
			n = (t_stack *)first;
	}
	i = 0;
	while (rally_items[i] != 0)
	// while (i++ < (int)max_rally)
		printf("%ld ",rally_items[i++]);
	printf("\n");
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
	t_stack			*last_rotated;

	last_rotated = NULL;
	while (get_stack_len(*a) != (int)len_rally)
	{
		i = 0;
		while (rally_items[i] != 0 && (*a)->order != (int)rally_items[i])
			i++;
		if (rally_items[i] == 0)
			ft_push(a, b, STACKB);
		else {
			i = 0;
			while (rally_items[i] != 0 && (*a)->next->order != (int)rally_items[i])
				i++;
			if (rally_items[i] != 0 && (*a)->next->order < (*a)->order)
				ft_swap(a, b, STACKA);
			else
			{
				if (last_rotated != NULL && last_rotated->order > (*a)->order)
				{
					last_rotated = NULL;
					ft_reverse_rotate(a, b, STACKA);
				}
				else
				{
					last_rotated = (*a);
					ft_rotate(a, b, STACKA);
				}
			}
		}
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
