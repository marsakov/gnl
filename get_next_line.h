/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msakovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/12 16:16:15 by msakovyc          #+#    #+#             */
/*   Updated: 2018/04/12 16:16:19 by msakovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
//# include <fcntl.h>

# define BUFF_SIZE 90

typedef struct		s_list
{
	int				fd;
	int				i;
	int				content_size;
	char			*content;
	struct s_list	*next;	
} 					t_list;

int					get_next_line(const int fd, char **line);

#endif
