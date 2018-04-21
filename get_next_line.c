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
// # include <fcntl.h>
// # include <sys/stat.h>
// # include <sys/types.h>

static void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char *temp;

	temp = (unsigned char *)b;
	while (len-- > 0)
		*temp++ = (unsigned char)c;
	return (b);
}

static void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}

static void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*temp1;
	char	*temp2;

	temp1 = (char *)dst;
	temp2 = (char *)src;
	while (n--)
		*temp1++ = *temp2++;
	return (dst);
}

static void	ft_lstadd(t_list **alst, t_list *new)
{
	if (new)
	{
		new->next = *alst;
		*alst = new;
	}
}

static t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list *list;

	list = (t_list *)malloc(sizeof(t_list));
	if (!list)
		return (NULL);
	if (!content)
	{
		list->content = NULL;
		list->content_size = 0;
	}
	else
	{
		list->content = (void *)malloc(content_size);
		if (!list->content)
			return (NULL);
		ft_memcpy(list->content, content, content_size);
		list->content_size = content_size;
	}
	list->next = NULL;
	return (list);
}

static char	*ft_strncpy(char *dst, const char *src, size_t n)
{
	char	*begin;

	begin = dst;
	while (n && *src)
	{
		*dst++ = *src++;
		--n;
	}
	while (n)
	{
		*dst++ = '\0';
		n--;
	}
	return (begin);
}

static t_list *ft_check(int fd, t_list *lst)
{
	t_list *temp;

	temp = lst;
	while (temp)
	{
		//printf("--------temp-------\n%s\n-------------------\n", lst->content);
		if (temp->fd == fd)
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}

static void	ft_zapominalka(int fd, char	*buf, t_list **temp, int counter)
{
	t_list	*elem;


	if (*temp && (*temp)->fd == fd)
	{
		(*temp)->content = ft_strncpy((*temp)->content, buf, BUFF_SIZE);
		printf("MENYAU BUF: %s\n", (*temp)->content);	
		(*temp)->i = counter;
		printf("NACHINAU TYT: %s\n", ((*temp)->content + (*temp)->i));
	}
	else
	{
		if (!(elem = (t_list*)malloc(sizeof(t_list))))
			return ;
		elem = ft_lstnew(buf, BUFF_SIZE + 1);
		elem->fd = fd;
		elem->i = counter;
		printf("CREATE NEW ELEM IN LST: fd = %d, i = %d, content = %s\n", fd, counter, buf);
		ft_lstadd(temp, elem);
	}
}

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
	return (0);
}


int		get_next_line(const int fd, char **line)
{
	char			buf[BUFF_SIZE + 1];
	int				bytes;
	static t_list	*lst = NULL;
	t_list			*temp;
	int				wrtr;
	int				count;

	t_list			*temp_print = lst;
	int				i = 0;

	// if (!lst)
	// {
	// 	if (!(lst = (t_list*)malloc(sizeof(t_list))))
	// 		return (0);
	// 	lst->content = NULL;
	// }

	// printf("|||||||||||| LST ||||||||||||\n");
	// while (temp_print)
	// {
	// 	printf("            i = %d\n%s\n", i, temp_print->content);
	// 	i++;
	// 	temp_print = temp_print->next;
	// }
	// printf("|||||||||||||||||||||||||||||\n");

	temp = ft_check(fd, lst);
	bytes = 1;
	wrtr = 0;
	count = 0;
	while (wrtr != 1)
	{
		if (!temp || temp->i == BUFF_SIZE - 1)
		{
			printf("IF\n");
			buf[BUFF_SIZE] = 0;
			bytes = read(fd, buf, BUFF_SIZE);
			if (bytes == -1)
				return (-1);
			if (bytes == 0)
				return (0);
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
	}
	// if (bytes == -1)
	// 	return (-1);
	// if (bytes == 0)
	// 	return (0);
	return (1);
}
