/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 10:54:00 by user42            #+#    #+#             */
/*   Updated: 2021/12/14 17:51:19 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <stdlib.h>
# include <stdint.h>
# include <wchar.h>

# define BUFFER_SIZE	4096
# define FD_MAX			128

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
	struct s_list	*prev;
}				t_list;

typedef struct s_file
{
	char	*path;
	int		fd;
}				t_file;

/*
** for fiddling with float/double bits
*/

typedef union u_dbit
{
	double	d;
	int64_t	i;
}				t_dbit;

/*
** Memory
*/

void			*ft_memset(void *b, int c, size_t n);
void			ft_bzero(void *s, size_t n);
void			*ft_memchr(const void *s, int c, size_t n);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			*ft_memccpy(void *dst, const void *src, int c, size_t n);
void			*ft_memmove(void *dst, const void *src, size_t len);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
void			ft_memswap(void *a, void *b, void *temp, size_t len);
void			*ft_calloc(size_t count, size_t size);
void			*ft_realloc(void *ptr, size_t len, size_t newlen);

/*
** is functions
*/

int				ft_isalpha(char c);
int				ft_isuppercase(int c);
int				ft_islowercase(int c);
int				ft_isdigit(char c);
int				ft_isalnum(char c);
int				ft_isascii(int c);
int				ft_isprint(char c);
int				ft_tolower(char c);
int				ft_toupper(char c);
int				ft_isspace(char c);
int				ft_iswspace(char c);
int				ft_isin(char c, const char *set);
int				ft_isnumber(char *str);
int				ft_isfloat(char *str);

/*
** Math
*/

int				ft_ishigher(int a, int b);
int				ft_islower(int a, int b);
double			ft_pow(double d, int power);
intmax_t		ft_abs(intmax_t n);
double			ft_absd(double d);
int				ft_atoi(const char *str);
int				ft_getnbrlen(int n);
int				ft_getnbrlen_us(intmax_t n);
double			ft_atof(char *str);

/*
** Int Array Operations
*/

int				ft_tabint(int *tab, int n, int size);
void			ft_swap(int *a, int *b);

/*
** String Operations
*/

size_t			ft_strlen(const char *s);
char			*ft_strchr(const char *s, int c);
int				ft_strwchr(const char *s, int c);
size_t			ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t			ft_strlcpy(char *dst, const char *src, size_t dstsize);
char			*ft_strncpy(char *dst, const char *src, int n);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strnstr(const char *haystack, const char *needle,
					size_t len);
char			*ft_strrchr(const char *s, int c);
int				ft_strcheck_each(char *str, int (*f)(char));
char			*ft_strinsert(const char *dst, const char *src, size_t pos);
char			*ft_strextract(const char *dst, size_t start, size_t len);

/*
** Arg Operations
*/

int				ft_argcheck_each(char **args, int (*f)(char));
int				ft_argcount(char **args);
void			ft_freeargs(char **args);

/*
** Colors!
*/

int				make_argb(int a, int r, int g, int b);
int				argb_to_a(int argb);
int				argb_to_r(int argb);
int				argb_to_g(int argb);
int				argb_to_b(int argb);
int				str_to_rgb(char *str);

/*
** Malloc String Operations
*/

char			*ft_strdup(const char *s1);
char			*ft_strndup(const char *src, size_t len);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strtrim(char const *s1, char const *set);
char			*ft_strjoin(const char *s1, const char *s2);
char			**ft_split(char const *s, char c);
char			**ft_splitset(char const *s, char *set);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char			*strfill(char *str, int minlen, char c);

/*
** itoa and helper functions
*/

char			*ft_itoa(int n);
char			*ft_itoa_abs(intmax_t n);
char			*ft_itoa_base(int n, char *base_to);
char			*ft_uitoa_base(uintmax_t n, char *base_to);
char			*ft_uitoa_base_ptr(uintptr_t n, char *base_to);
int				ft_check_base(char *base, int base_len);

/*
** Outputting to fd
*/

void			ft_putstr_fd(char *s, int fd);
void			ft_putendl_fd(char *s, int fd);
void			ft_putnbr_fd(int n, int fd);
void			ft_putchar_fd(char c, int fd);

/*
** Reading Files
*/

int				filecheck(char *path);
int				check_file_extension(char *path, char *extension);
int				get_next_line(int fd, char **line);

/*
** Lists
*/

t_list			*ft_lstnew(void *content);
void			ft_lstadd_front(t_list **alst, t_list *new);
void			ft_lstadd_back(t_list **alst, t_list *new);
t_list			*ft_lstlast(t_list *lst);
int				ft_lstsize(t_list *lst);
void			ft_lstdelone(t_list **begin, t_list *lst, void (*del)());
void			ft_lstclear(t_list **lst, void (*del)());
t_list			*ft_lstmap(t_list *lst, void *(*f)(void *),
					void (*del)(void *));
void			ft_lstiter(t_list *lst, void (*f)(void *));
void			ft_lstsortif(t_list **begin, int (*cmp)());
void			ft_lstswapone(t_list **begin, t_list *lst);
void			ft_putlst(t_list *lst);

/*
** Wide characters
*/

int				ft_wctomb(char *pmb, wchar_t wc);
int				ft_wclen(wchar_t wc);
size_t			ft_wcslen(wchar_t *wcs);

#endif
