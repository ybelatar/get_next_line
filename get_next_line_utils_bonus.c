/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelatar <ybelatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 18:55:34 by ybelatar          #+#    #+#             */
/*   Updated: 2023/11/14 19:55:05 by ybelatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	add_cell(t_list **plist, char *buffer)
{
	t_list	*new;
	t_list	*last;

	last = ft_lstlast(*plist);
	new = malloc(sizeof(t_list));
	if (!new)
		return ;
	if (!last)
		*plist = new;
	else
		last->next = new;
	new->content = buffer;
	new->next = NULL;
}

int	list_to_len(t_list *list)
{
	int	i;
	int	length;

	if (!list)
		return (0);
	length = 0;
	while (list)
	{
		i = 0;
		while (list->content[i])
		{
			if (list->content[i] == '\n')
				return (length + 1);
			length++;
			i++;
		}
		list = list->next;
	}
	return (length);
}

void	list_into_string(t_list *list, char *str)
{
	int	i;
	int	j;

	if (!list)
		return ;
	j = 0;
	while (list)
	{
		i = 0;
		while (list->content[i])
		{
			if (list->content[i] == '\n')
			{
				str[j++] = '\n';
				str[j] = 0;
				return ;
			}
			str[j++] = list->content[i++];
		}
		list = list->next;
	}
	str[j] = 0;
}

void	free_and_new(t_list **plist, t_list *new, char **buffer)
{
	t_list	*tmp;

	if (!plist || !(*plist))
		return ;
	while (*plist)
	{
		tmp = (*plist)->next;
		free((*plist)->content);
		free(*plist);
		*plist = tmp;
	}
	*plist = NULL;
	if (new->content && *new->content)
		*plist = new;
	else
	{
		free(*buffer);
		free(new);
	}
}
