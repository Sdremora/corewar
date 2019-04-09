/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnarbert <mnarbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 14:04:27 by hharvey           #+#    #+#             */
/*   Updated: 2019/04/09 11:46:16 by mnarbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdarg.h>
# include <wchar.h>
# include "ft_printf.h"
# include <math.h>
# include "get_next_line.h"
# define PI 3.14159265

typedef struct		s_fdlist
{
	char			*buf;
	int				fd;
	struct s_fdlist	*next;
}					t_fdlist;

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

typedef struct		s_point
{
	int				x;
	int				y;
}					t_point;

typedef struct		s_3point
{
	int				x;
	int				y;
	int				z;
}					t_3point;

typedef struct		s_arrnum
{
	int				*arr;
	int				size;
}					t_arrnum;

typedef struct		s_mlx
{
	void			*mlx_ptr;
	void			*win_ptr;
	void			*img_ptr;
	char			*img_data;
	int				bpp;
	int				size_line;
	int				endian;
}					t_mlx;

void				ft_arrstrprnt(char **arr);

int					ft_atoi_base(char *str, int base);
long long int		ft_atoi_long(const char *str);
void				ft_arrnumdel(t_arrnum *a);
void				ft_arrnumset(t_arrnum *arrnum, int *arr, int size);
void				ft_arrnumprint(t_arrnum arrnum);
void				ft_arrnumbblsrt(t_arrnum a);
int					ft_arrnumgetmed(t_arrnum a, int start, int end);
int					ft_arrnumissrt(t_arrnum a);
t_arrnum			*ft_arrnumdup(t_arrnum *a);
int					ft_arrnumfndposnb(t_arrnum *a, int nb);

void				*ft_memmalcpy(void *src, size_t size);

void				ft_3pntset(t_3point *p, int x, int y, int z);
t_point				ft_pntset(t_point *p, int x, int y);
t_point				ft_pntplsy(t_point t, int i);
t_point				ft_pntplsx(t_point t, int i);
t_point				ft_pnt(int x, int y);
t_point				ft_pntpls(t_point p0, t_point p1);
t_3point			ft_3pnt(int x, int y, int z);

int					ft_usage(char *fname);
int					ft_error(void);
void				*ft_memrealloc(void *src, size_t src_size, size_t new_size);

int					ft_strwrdcnt(char const *s, char c);
int					ft_lstgetnb(t_list *a);

int					ft_arrposmin(int *a, int size);
int					ft_arrposmax(int *a, int size);
int					ft_arrsum(int *arr, int nb);

int					ft_lstlen(t_list *lst);
void				ft_lstprintnb(t_list *lst);
int					ft_wcharlen(wchar_t c);
int					ft_putwchar_fd(wchar_t c, int fd);
int					ft_putnwstr_fd(wchar_t const *s, int n, int fd);
void				ft_putnstr_fd(char const *s, int n, int fd);
int					ft_get_itoa_len_uns(unsigned long long int nb, int base);
void				ft_putnbr_base(unsigned long long int nb,
					int base, int isbig);
int					ft_putwstr_fd(const wchar_t *s, int fd);
size_t				ft_strwlen(const wchar_t *s);
int					ft_putwchar(wchar_t c);
char				*ft_strjdelsnd(const char *str, char *str2);
char				*ft_strnewchr(size_t size, int c);
int					ft_strchrpos(char *str, int c);
unsigned char				*ft_itoa_base_unsgn(unsigned long long int nb,
					int base, int isbig);
char				*ft_strdelchr(char *str);
char				*ft_strjdelfst(char *str, const char *str2);

int					ft_max(int a, int b);
int					ft_min(int a, int b);
int					ft_reminder(int a, int b);

char				*ft_strndup(const char *s, size_t maxlen);
char				*ft_addr_char(char *str, char c);
int					ft_printf(const char *str, ...);
char				*ft_itoa_base(long long int nb, int base, int isbig);
char				*ft_strfreejoin(char *str1, char *str2);
char				*ft_add_char(char *str, char c);
int					ft_abs(int x);
int					ft_strnchr(const char *s1, const char *s2);
int					get_next_line(const int fd, char **line);
void				*ft_myrealloc(void *ptr, size_t size);
void				ft_swap_str(char **s1, char **s2);

char				**ft_arrstrdel(char **res);
int					ft_arrstrlen(char **str);
char				**ft_arrstradd(char **input, char *str);

char				*ft_get_wrd(char const *s, int start, int end);
void				*ft_memset(void *b, int c, size_t len);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memccpy(void *dst, void *src, int c, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);

void				*ft_memalloc(size_t size);
void				ft_memdel(void **ap);

size_t				ft_strlen(const char *str);
char				*ft_strdup(const char *s1);
char				*ft_strcpy(char *dst, const char *src);
char				*ft_strncpy(char *dst, const char *src, size_t n);
char				*ft_strcat(char *s1, const char *s2);
char				*ft_strncat(char *s1, const char *s2, size_t n);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strstr(const char *s1, const char *s2);
char				*ft_strnstr(const char *s1, const char *s2, size_t n);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_atoi(const char *str);
void				ft_strclr(char *s);

char				*ft_strnew(size_t size);
void				ft_strdel(char **as);
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
char				**ft_split_whitespaces(char *str);
char				*ft_itoa(int n);
void				ft_putchar(char c);
void				ft_putstr(char const *str);
void				ft_putendl(char const *str);
void				ft_putnbr(long long int n);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr_fd(int n, int fd);

int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_tolower(int c);
int					ft_toupper(int c);
int					ft_isnumber(char *str);

t_list				*ft_lstnew(void const *content, size_t content_size);
void				ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstadd(t_list **alst, t_list *new_lst);
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
t_list				*ft_lstfold(t_list *lst, t_list *(*f)(t_list *, t_list *));
void				ft_lstprint(t_list *lst);
t_list				*ft_lstdelsave(t_list *src_lst, t_list *del_lst,
					void (*del)(void *, size_t));

void				ft_lstdelfun(void *content, size_t size);
char				**ft_ltas(t_list *lst);
t_arrnum			*ft_ltan(t_list *lst);
int					ft_lstcontfnd(t_list *lst, t_list req, int (*f)());
t_arrnum			*ft_ltan_free(t_list *lst);

void				ft_lstsetnb(t_list *lst, int nb);

t_list				*ft_lstput(void const *content, size_t content_size);
t_list				*ft_lstfnd(t_list *lst, void *content);

int					ft_str_put(char *str, size_t index, char chr);
char				*ft_get_bits(void *data, int data_bytes_count);
void				*ft_free(int count_param, ...);
void				ft_str_reverse(char *str);
int					ft_str_indexof(const char *str, int c);
int					ft_str_n_indexof(const char *str, int len, int c);
int					ft_str_last_indexof(const char *str, int c);
int					ft_str_last_n_indexof(const char *str, int n, int c);
int					ft_str_indexof_str(const char *haystack,
										const char *needle);
void				ft_str_chrset(char *line, int c, int start, int len);
int					ft_wchar_get_utf8_size(unsigned int symbol);
int					ft_wchar_to_utf8(unsigned int symbol, char *buf);
int					ft_wchar_get_utf8_strlen(wchar_t *w_str);
int					ft_wchar_str_to_utf8(wchar_t *w_str, char **str);
char				*ft_itoa_unsize_base(size_t dec_num, int base);
void				ft_str_swap(char *str, int pos1, int pos2);
void				ft_str_toupper(char *str);
long long int		ft_atoi_long(const char *str);

#endif
