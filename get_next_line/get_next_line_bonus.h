/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunchoi <seunchoi@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 13:35:51 by seunchoi          #+#    #+#             */
/*   Updated: 2022/02/10 13:35:54 by seunchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# include <stdlib.h>
# include <unistd.h>

typedef struct s_list
{
	struct s_list	*prev;
	struct s_list	*next;
	char			*backup;
	int				fd;
}t_list;

char	*ft_dupjoin(char const *s1, char const *s2);
char	*get_ret(char *backup);
char	*read_line(char *backup, int fd);
char	*new_backup(char **backup, size_t len);
char	*get_next_line(int fd);
size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*ft_strchr(const char *s, int c);
t_list	*get_node(t_list *head, int fd);
char	*del_node(t_list **node);

#endif
