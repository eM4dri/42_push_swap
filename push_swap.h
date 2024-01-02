/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/22 12:04:17 by emadriga          #+#    #+#             */
/*   Updated: 2024/01/02 10:54:49 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
# include	<stdlib.h>
# include	<unistd.h>
# include	<errno.h>
# include	<stdio.h>
# define MAX_INT 2147483647
# define __u_int unsigned int

enum e_move_stack{
	STACKA,
	STACKB,
	BOTHSTACKS
};

enum e_moves_mode{
	NONE,
	M2FD,
	M2LD,
	M2FA_M2LB,
	M2LA_M2FB
};

typedef struct s_chunk_size
{
	int	min;
	int	mid;
	int	max;
	int	size;
}t_chunk_sizes;
typedef struct s_stack
{
	int				nbr;
	__u_int			pos;
	__u_int			order;
	__u_int			m2fa;
	__u_int			m2la;
	__u_int			m2fb;
	__u_int			m2lb;
	__u_int			total_moves;
	short			moves_mode;
	struct s_stack	*next;
}t_stack;
typedef struct s_stack_extended
{
	t_stack	**s;
	size_t	len;
}t_stack_extended;
typedef struct s_chunk_item
{
	int	nbr;
	int	pos;
}t_chunk_item;
typedef struct s_stack_chunk_stats
{
	int	min;
	int	max;
	int	first;
	int	second;
	int	last;
}t_stack_stats;
typedef struct s_chunk
{
	t_chunk_item	item;
	t_chunk_sizes	sizes;
}t_chunk;

int				parse_nbr(char *s_nbr, t_stack **stack);
void			ft_swap(t_stack **a, t_stack **b, int mode);
void			ft_push(t_stack **a, t_stack **b, int mode);
void			push_ext(t_stack_extended *a, t_stack_extended *b, int mode);
void			ft_rotate(t_stack **a, t_stack **b, int mode);
void			ft_reverse_rotate(t_stack **a, t_stack **b, int mode);
void			print_stack(t_stack *node);
void			ft_freestack(t_stack **stack);
int				get_stack_len(t_stack *stack);
void			order3(t_stack **stack, int mode);
void			order5(t_stack **a, t_stack **b);
int				ft_isspace(char c);
int				ft_isdigit(int c);
int				ft_atoi(const char *str);
void			longest_rally_orderer(t_stack_extended *a, t_stack_extended *b);
void			less_moves_to_order(t_stack_extended *a, t_stack_extended *b);
void			move_node_to_a(t_stack **a, t_stack **b, t_stack *n);
#endif
