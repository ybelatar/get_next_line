/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelatar <ybelatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 05:55:35 by ybelatar          #+#    #+#             */
/*   Updated: 2023/11/15 23:20:21 by ybelatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	refresh(t_list **plist)
{
	int		i;
	int		j;
	char	*buffer;
	t_list	*last;
	t_list	*new;

	buffer = malloc(BUFFER_SIZE + 1);
	new = malloc(sizeof(t_list));
	if (!new || !buffer)
	{
		free(buffer);
		return ;
	}
	last = ft_lstlast(*plist);
	i = 0;
	j = 0;
	while (last->content[i] && last->content[i] != '\n')
		i++;
	while (last->content[i] && last->content[++i])
		buffer[j++] = last->content[i];
	buffer[j] = 0;
	new->content = buffer;
	new->next = NULL;
	free_and_new(plist, new, &buffer);
}

int	newline_detector(t_list *list)
{
	int	i;

	if (!list)
		return (0);
	while (list)
	{
		i = 0;
		while (list->content[i] && i < BUFFER_SIZE)
		{
			if (list->content[i] == '\n')
				return (1);
			i++;
		}
		list = list->next;
	}
	return (0);
}

void	file_to_list(t_list **plist, int fd)
{
	int		len_read;
	char	*buffer;

	while (!newline_detector(*plist))
	{
		buffer = malloc(BUFFER_SIZE + 1);
		if (!buffer)
			return ;
		len_read = read(fd, buffer, BUFFER_SIZE);
		if (len_read == 0)
		{
			free(buffer);
			return ;
		}
		buffer[len_read] = 0;
		add_cell(plist, buffer);
	}
}

char	*list_to_str(t_list *list)
{
	char	*res;
	int		length;

	if (!list)
		return (NULL);
	length = list_to_len(list);
	res = malloc(length + 1);
	if (!res)
		return (NULL);
	list_into_string(list, res);
	return (res);
}

char	*get_next_line(int fd)
{
	static t_list	*list;
	char			*str;

	if (BUFFER_SIZE <= 0 || fd < 0 || read(fd, 0, 0) < 0)
		return (NULL);
	file_to_list(&list, fd);
	if (!list)
		return (NULL);
	str = list_to_str(list);
	refresh(&list);
	return (str);
}

/*# include<unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return(i);
}

int	main(void)
{
	char *str;
	int fd;
	int i;

	fd = open("texte", O_RDONLY);
	while (str = get_next_line(fd))
	{
		i = ft_strlen(str);
		write(1, str, i);
		free(str);
	}
	close(fd);
}*/