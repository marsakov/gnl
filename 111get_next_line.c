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

static void	ft_zapominalka(int fd, char	*buf, t_list **temp, int counter)
{
	t_list	*elem;

	if (!(elem = (t_list*)malloc(sizeof(t_list))))
		return ;
	if (*temp && (*temp)->fd == fd)
	{
		(*temp)->content = ft_strncpy((*temp)->content, buf, BUFF_SIZE);
		printf("MENYAU BUF: %s\n", (*temp)->content);	
		(*temp)->i = counter;
		printf("NACHINAU TYT: %s\n", ((*temp)->content + (*temp)->i));
	}
	else
	{
		elem = ft_lstnew(buf, BUFF_SIZE);
		elem->fd = fd;
		elem->i = counter;
		printf("CREATE NEW ELEM IN LST: fd = %d, i = %d, content = %s\n", fd, counter, buf);
		ft_lstadd(temp, elem);
	}
}

static int	ft_check(int fd, t_list **temp, char **line)
{
	int 	i;

	i = 0;
	while (temp && *temp && (*temp)->content)
	{
		printf("--------temp-------\n%s\n-------------------\n", *temp);
		if ((*temp)->fd == fd)
		{
			i = (*temp)->i;
			break ;
		}
		*temp = (*temp)->next;
	}
	if (i)
	{
		while (i < (*temp)->content_size && (*temp)->content[i] != '\n')
			i++;
		if (!(*line = (char *)malloc(sizeof(char) * (i - (*temp)->i + 1))))
			return (0);
		*line = ft_strncpy(*line, (*temp)->content, i - (*temp)->i);
		(*line)[i - (*temp)->i] = 0;
		if (((*temp)->content[i] == '\n' && !(*temp)->content[i + 1]) || !(*temp)->content[i])
			ft_bzero((*temp)->content, BUFF_SIZE);
		if ((*line)[i - (*temp)->i - 1] == '\n')
			return (1);
		(*temp)->i = i;
		return (i);
	}
	return (0);
}

static int	ft_writer(char	*buf, char **line, int bytes, t_list **temp, int fd)
{
	int		i;
	int		counter;

	i = 0;
	counter = 0;
	if (*temp)
		counter = (*temp)->i;
	while ((*line)[i])
		i++;
	while (counter < BUFF_SIZE && buf[counter] != '\n')
	{
		(*line)[i] = (char)malloc(sizeof(char));
		(*line)[i++] = buf[counter++];
	}
	if (counter < bytes)
		ft_zapominalka(fd, buf, temp, counter);
	if (buf[counter] == '\n' || counter == bytes)
	{
		(*line)[i++] = 0;
		return (1);
	}
	return (0);
}


int		get_next_line(const int fd, char **line)
{
	char			buf[BUFF_SIZE];
	int				bytes;
	static t_list	*lst = NULL;
	t_list			*temp;
	int				wrtr;

	printf("get_next_line\n");
	if (!lst)
	{
		if (!(lst = (t_list*)malloc(sizeof(t_list))))
			return (0);
		lst->content = NULL;
	}
	temp = lst;
	bytes = 1;
	wrtr = 0;
	if (ft_check(fd, &temp, line) != 1)
	{
		printf("ft_check != 1\n");
		while (wrtr != 1)
		{
			bytes = read(fd, buf, BUFF_SIZE);
			printf("||||||||||||BUF||||||||||||\n%s\n||||||||||||||||||||||||\n", buf);
			wrtr = ft_writer(buf, line, bytes, &temp, fd);
			printf("ft_writer\n");
		}
	}
	if (bytes == -1)
		return (-1);
	if (bytes == 0)
		return (0);
	return (1);
}




