/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelatar <ybelatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 05:55:31 by ybelatar          #+#    #+#             */
/*   Updated: 2023/11/14 18:49:55 by ybelatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}					t_list;

t_list				*ft_lstlast(t_list *lst);
void				add_cell(t_list **plist, char *buffer);
int					list_to_len(t_list *list);
void				list_into_string(t_list *list, char *str);
void				free_and_new(t_list **plist, t_list *new, char **buffer);
void				refresh(t_list **plist);
int					newline_detector(t_list *list);
void				file_to_list(t_list **plist, int fd);
char				*list_to_str(t_list *list);
char				*get_next_line(int fd);

#endif
