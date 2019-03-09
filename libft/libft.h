/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshvets <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 16:31:50 by mshvets           #+#    #+#             */
/*   Updated: 2018/11/28 19:14:27 by mshvets          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H

# define LIBFT_H
# define BUFF_SIZE 32

# include <unistd.h>
# include <stdlib.h>
# include <string.h>

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

typedef struct      s_fdlst
{
    int             fd;
    char            *str;
    struct s_fdlst  *next;
}                   t_fdlst;

void				*ft_memset(void *buf, int ch, size_t count);
void				ft_bzero(void *buf, size_t count);
void				*ft_memcpy(void *destptr, const void *srcptr, size_t count);
void				*ft_memccpy(void *destptr, const void *srcptr,
						int ch, size_t count);
void				*ft_memmove(void *destptr, const void *srcptr, size_t n);
void				*ft_memchr(const void *buf, int ch, size_t count);
int					ft_memcmp(const void *ptr1, const void *ptr2, size_t count);
size_t				ft_strlen(const char *strptr);
char				*ft_strdup(const char *strptr);
char				*ft_strcpy(char *destptr, const char *srcptr);
char				*ft_strncpy(char *destptr, const char *srcptr, size_t n);
char				*ft_strcat(char *destptr, const char *srcptr);
char				*ft_strncat(char *destptr, const char *srcptr, size_t n);
size_t				ft_strlcat(char *destptr, const char *srcptr, size_t size);
char				*ft_strchr(const char *strptr, int ch);
char				*ft_strrchr(const char *strptr, int ch);
char				*ft_strstr(const char *str, const char *to_find);
char				*ft_strnstr(const char *str, const char *to_find, size_t n);
int					ft_strcmp(const char *str1, const char *str2);
int					ft_strncmp(const char *str1, const char *str2, size_t n);
int					ft_atoi(const char *strptr);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);
void				*ft_memalloc(size_t size);
void				ft_memdel(void **ap);
char				*ft_strnew(size_t size);
void				ft_strdel(char **as);
void				ft_strclr(char *s);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s);
char				**ft_strsplit(char const *s, char c);
char				*ft_itoa(int n);
void				ft_putchar(char c);
void				ft_putstr(char const *s);
void				ft_putendl(char const *s);
void				ft_putnbr(int n);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr_fd(int n, int fd);
t_list				*ft_lstnew(void const *content, size_t content_size);
void				ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
void				ft_lstaddr(t_list **alst, t_list *new);
int					ft_isspace(char c);
size_t				ft_cntwrd(const char *str, char c);
void				ft_srtwrd(char **tab);
int					ft_numlen(int n, int base);
long int			ft_pow(int nb, unsigned int power);
char				*ft_strupcase(char *str);
char				*ft_strlowcase(char *str);
char				*ft_itoa_base(int n, int base);
int                 ft_sqtr(int nb);
int                 get_next_line(const int fd, char **line);

#endif
