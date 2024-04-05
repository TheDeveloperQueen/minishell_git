/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ritavasques <ritavasques@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 10:40:12 by rivasque          #+#    #+#             */
/*   Updated: 2024/04/05 18:12:37 by ritavasques      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <fcntl.h>
# include <stdarg.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}		t_list;

typedef struct s_llist
{
	struct s_llist	*next;
	char			*name;
	char			*value;
}					t_llist;

int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_str_isdigit(char *str);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
size_t	ft_strlen(const char *str);
void	*ft_memset(void *dest, int c, size_t count);
void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t count);
int		ft_tolower(int c);
int		ft_toupper(int c);
size_t	ft_strlcpy(char *dest, char *src, size_t size);
size_t	ft_strlcat(char *dest, char *src, size_t size);
char	*ft_strchr(const char *str, int c);
char	*ft_strrchr(const char *str, int c);
int		ft_atoi(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t count);
int		ft_memcmp(const void *buffer1, const void *buffer2, size_t count);
char	*ft_strnstr(const char *str, const char *to_find, size_t len);
void	*ft_memchr(const void *s, int c, size_t n);
char	*ft_strdup(char *str);
void	*ft_calloc(size_t number, size_t size);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
void	*ft_memmove(void *dest, const void *src, size_t count);
char	*ft_itoa(int n);
char	**ft_split(char const *s, char c);
int		ft_line_length(int fd);
char	*get_next_line(int fd);
int		ft_line_count(char **file);
int		ft_putchar(char c);
int		ft_putstr(char *str);
int		ft_putnbr(long n);
int		ft_printf(const char *str, ...);
int		array_len(char **array);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstadd_back(t_list **list, t_list *new);
void	print_list(t_list *lst, char *delimiter);
int		ft_strict_atoi(const char *str, int *flag);
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_swap(int	*a, int	*b);
int		ft_str_is_numeric(char *str);
char	*ft_strcpy(char *dest, char *src);
int		ft_strcmp(char *s1, char *s2);
int		ft_strchr_int(char *str, int c);
char	*ft_strjoin_buff(char *add_read, char *str_buff);
int		ft_charfind(char *str, char c);
void	ft_del_lst(t_list **lst);
int		ft_absolute(int nb);
void	ft_error(void);
char	*ft_get_empty_str(void);
char	*ft_strjoin_char(char *s1, char *s2, char c);
void	ft_delete_lst(t_list *lst);
void	ft_delete_llst(t_llist *lst);
int		ft_llstsize(t_llist *lst);
t_llist	*lst_add_new(void *name, void *value);
void	lst_add_back(t_llist **llst, t_llist *new);
t_llist	*llist_cpy(t_llist *llst);
int		only_space(char *str);

#endif