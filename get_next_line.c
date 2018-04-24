/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msakovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/12 15:22:21 by msakovyc          #+#    #+#             */
/*   Updated: 2018/04/12 15:22:24 by msakovyc         ###   ########.fr       */
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

<<<<<<< HEAD
	temp = ft_check(fd, *lst);
	if (temp && temp->fd == fd)
=======

	if (*temp && (*temp)->fd == fd)
>>>>>>> 3e70d45b5d30f9553ecc4bd8fa7b0e4116fa88a2
	{
		temp->content = ft_strncpy(temp->content, buf, BUFF_SIZE);
		temp->i = counter;
	}
	else
	{
		if (!(elem = (t_list*)malloc(sizeof(t_list))))
			return ;
		elem = ft_lstnew(buf, BUFF_SIZE + 1);
		elem->fd = fd;
		elem->i = counter;
		ft_lstadd(lst, elem);
	}
}

<<<<<<< HEAD
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
=======
static int	ft_writer(char **line, int bytes, t_list **temp, int *i)
{
	while (*i + (*temp)->i < BUFF_SIZE && (*temp)->content[*i + (*temp)->i] != '\n')
	{
		//printf("content[%d] = %c\n", *i + (*temp)->i, (*temp)->content[*i + (*temp)->i]);
		(*line)[*i] = (char)malloc(sizeof(char));
		(*line)[*i] = (*temp)->content[*i + (*temp)->i];
		(*i)++;
	}
	//printf("%d\n", *i);
	(*line)[*i] = 0;
	//printf("%d\n", (*temp)->i);
	(*temp)->i += *i;
	//printf("%d\n", (*temp)->i);
	//printf("BUF = %s\n", (*temp)->content);
	//printf("\nZAKONCHIL ZAPIS | counter = %d\n\n", *i + (*temp)->i);
	//printf("poslednii simvol: (%c)\n", (*temp)->content[*i + (*temp)->i]);
	if ((*temp)->content[(*temp)->i] == '\n')
	{
		//printf("writer: VERNU 1\n");
		return (1);
	}
	//printf("\nVERNU 0\n\n");
	//printf("%d\n", (*temp)->i);
	//printf("%d\n", (*temp)->i);
>>>>>>> 3e70d45b5d30f9553ecc4bd8fa7b0e4116fa88a2
	return (0);
}

int		get_next_line(const int fd, char **line)
{
	char			buf[BUFF_SIZE + 1];
	int				bytes;
	static t_list	*lst = NULL;
	t_list			*temp;
	int				wrtr;
<<<<<<< HEAD
	int				i;
=======
	int				count;
>>>>>>> 3e70d45b5d30f9553ecc4bd8fa7b0e4116fa88a2

	i = 0;
	temp = ft_check(fd, lst);
	if (line && *line)
		ft_bzero(*line, ft_strlen(*line));
	wrtr = 0;
<<<<<<< HEAD
	while (wrtr == 0)
=======
	count = 0;
	while (wrtr != 1)
>>>>>>> 3e70d45b5d30f9553ecc4bd8fa7b0e4116fa88a2
	{
		if (!temp || temp->i >= BUFF_SIZE)
		{
<<<<<<< HEAD
=======
			printf("IF\n");
			buf[BUFF_SIZE] = 0;
>>>>>>> 3e70d45b5d30f9553ecc4bd8fa7b0e4116fa88a2
			bytes = read(fd, buf, BUFF_SIZE);
			buf[bytes] = 0;
			if (bytes == -1)
				return (-1);
			if (bytes == 0)
			{
				if (i)
					return (1);
				return (0);
<<<<<<< HEAD
			}
			ft_zapominalka(fd, buf, &lst, 0);
			if (!temp)
				temp = lst;
		}
		wrtr = ft_writer(line, &temp);
		i++;
=======
			//printf("||||||||||||BUF||||||||||||\n%s\n||||||||||||||||||||||||\n", buf);
			ft_zapominalka(fd, buf, &temp, 0);
			count = 0;
			if (!lst)
			{
				printf("!TEMP: \n");
				ft_lstadd(&lst, temp);
				//lst = temp;
				printf("|||||||||||| LST ||||||||||||\n");
				while (temp_print)
				{
					printf("            i = %d\n%s\n", i, temp_print->content);
					temp_print = temp_print->next;
				}
				printf("|||||||||||||||||||||||||||||\n");

			}
		}
		wrtr = ft_writer(line, bytes, &temp, &count);
>>>>>>> 3e70d45b5d30f9553ecc4bd8fa7b0e4116fa88a2
	}
	return (1);
}
 