/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strreplaceat.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 11:54:30 by emadriga          #+#    #+#             */
/*   Updated: 2021/11/13 20:55:36 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * * Returns a new string in which occurrence at index (if found) of a  \
 * * specified string in the current instance are replaced with another \
 * * specified string.
 * @param str		string to modify
 * @param oldset	string to be replaced.
 * @param newset	string to replace occurrence of oldValue at index
 * @param index		index to try replace
*/
char	*ft_strreplaceat(const char *str, char const *oldset, \
		char const *newset, size_t index)
{
	char	*out;
	char	*tmp;
	char	*strnstr;

	if (!str || !oldset || !newset)
		return (NULL);
	out = (char *)str;
	if (*oldset != '\0')
	{
		tmp = (char *)str;
		strnstr = &tmp[index];
		if (!ft_strncmp(strnstr, oldset, ft_strlen(oldset)))
		{
			out = ft_substr(tmp, 0, strnstr - tmp);
			tmp = ft_strjoin(out, newset);
			free(out);
			out = ft_strjoin(tmp, strnstr + ft_strlen(oldset));
			free(tmp);
			tmp = out;
			strnstr = ft_strnstr(tmp, oldset, ft_strlen(tmp));
		}
	}
	return (out);
}
