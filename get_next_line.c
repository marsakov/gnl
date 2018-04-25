/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msakovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/12 15:22:21 by msakovyc          #+#    #+#             */
/*   Updated: 2018/04/25 18:48:02 by msakovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static t_list *ft_check(int fd, t_list *lst)
{
	t_list *temp;

	temp = lst;
	while (temp)
	{
		if (temp->fd == fd)
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}

static void	ft_zapominalka(int fd, char	*buf, t_list **lst, int counter)
{
	t_list	*elem;
	t_list	*temp;

	temp = ft_check(fd, *lst);
	if (temp && temp->fd == fd)
	{
		temp->content = ft_strncpy(temp->content, buf, BUFF_SIZE);
		temp->i = counter;
	}
	else
	{
		elem = ft_lstnew(buf, BUFF_SIZE + 1);
		elem->fd = fd;
		elem->i = counter;
		ft_lstadd(lst, elem);
	}
}

static int	ft_writer(char **line, t_list **temp)
{
	int i;
	int tmp;
	char *p;

	i = 0;
	p = *line;
	tmp = (*temp)->i;
	while ((*temp)->i < BUFF_SIZE && (*temp)->content[(*temp)->i] != '\n' && (*temp)->content[(*temp)->i] != 0)
	{
		(*temp)->i++;
		i++;
	}
	*line = ft_strnjoin(*line, ((*temp)->content + tmp), i);
	if (p && *p)
		free(p);
	if ((*temp)->i != BUFF_SIZE)
	{
		if ((*temp)->content[(*temp)->i] == 0)
			(*temp)->i = BUFF_SIZE;
		else if ((*temp)->content[(*temp)->i] == '\n')
			(*temp)->i++;
		return (1);
	}
	return (0);
}

int		get_next_line(const int fd, char **line)
{
	char			*buf;
	int				bytes;
	static t_list	*lst = NULL;
	t_list			*temp;
	int				wrtr;
	int				i;

	i = 0;
	if (!(buf = (char*)malloc(sizeof(char) * (BUFF_SIZE + 1))))
		return (0);
	temp = ft_check(fd, lst);
	if (line && *line)
		*line = 0;
	wrtr = 0;
	while (wrtr == 0)
	{
		if (!temp || temp->i >= BUFF_SIZE)
		{
			bytes = read(fd, buf, BUFF_SIZE);
			buf[bytes] = 0;
			if (bytes == -1)
				return (-1);
			if (bytes == 0)
			{
				if (i)
					return (1);
				return (0);
			}
			ft_zapominalka(fd, buf, &lst, 0);
			if (!temp)
				temp = lst;
		}
		wrtr = ft_writer(line, &temp);
		i++;
	}
	return (1);
}
 
