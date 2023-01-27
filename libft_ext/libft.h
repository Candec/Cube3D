/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibanez- <jibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 15:48:17 by jibanez-          #+#    #+#             */
/*   Updated: 2023/01/27 01:13:31 by jibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

/*
**Libraries
*/
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <stdint.h>
# include <stddef.h>
# include <stdarg.h>
# include <fcntl.h>
# include <stdbool.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 128
# endif

# ifndef FD_MAX_COUNT
#  define FD_MAX_COUNT 4096
# endif

# ifndef ASCII_OFFSET_NUM
#  define ASCII_OFFSET_NUM 48
# endif

# ifndef TRUE
#  define TRUE 1
# endif

# ifndef FALSE
#  define FALSE 0
# endif

# ifndef ERROR
#  define ERROR -1
# endif

# define SPC ' '

# define FD_EOF 0

typedef unsigned char	t_uc;

typedef struct s_rgb
{
	bool	fill;
	int		r;
	int		g;
	int		b;
	int		int_rgb;
}				t_rgb;

/*
**First half
*/
int				ft_atoi(const char *str);
void			ft_bzero(void *s, size_t n);
void			*ft_calloc(size_t nmemb, size_t size);
int				ft_isalnum(int c);
int				ft_isalpha(int c);
int				ft_isascii(int c);
int				ft_isdigit(int c);
int				ft_isprint(int c);
void			*ft_memccpy(void *dest, const void *src, int c, size_t n);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
void			*ft_memcpy(void *dest, const void *src, size_t n);
void			*ft_memmove(void *dest, const void *src, size_t n);
void			*ft_memset(void *s, int c, size_t n);
char			**ft_split(char const *s, char c);
char			*ft_strncpy(char *dest, char *src, unsigned int n);
char			*ft_strchr(const char *s, int c);
char			*ft_strdup(const char *src);
size_t			ft_strlen(const char *s);
size_t			ft_strlcpy(char *dest, const char *src, size_t size);
size_t			ft_strlcat(char *dst, const char *src, size_t size);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strnstr(const char *a, const char *b, size_t len);
char			*ft_strrchr(const char *s, int c);
int				ft_tolower(int c);
int				ft_toupper(int c);

/*
**Second half
*/
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strtrim(char const *s1, char const *set);
char			*ft_itoa(int n);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char const *s, int fd);
void			ft_putendl_fd(char const *s, int fd);
void			ft_putnbr_fd(int n, int fd);

/*
**Bonus from the exercise
*/
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

t_list			*ft_lstnew(void *content);
void			ft_lstadd_front(t_list **lst, t_list *new);
int				ft_lstsize(t_list *lst);
t_list			*ft_lstlast(t_list *lst);
void			ft_lstadd_back(t_list **lst, t_list *new);
void			ft_lstdelone(t_list *lst, void (*del)(void*));
void			ft_lstclear(t_list **lst, void (*del)(void*));
void			ft_lstiter(t_list *lst, void (*f)(void *));
t_list			*ft_lstmap(t_list *l, void *(*f)(void *), void (*d)(void *));

/*
**42 projects
*/
int				ft_get_next_line(int fd, char **line);

/*
**Extras
*/
char			*ft_strrev(char *s);
ssize_t			ft_ispositive(int n);
int				ft_isspace(char a);
char			*ft_strcpy(char *dest, char const *src, int start, int last);
int				ft_numlen(int_fast64_t value, int base);
int				ft_abs(int n);
int				ft_strcmp(char *s1, char *s2);
void			ft_strtoupper(char *str);
int				ft_max(int args, ...);
int				ft_isnumber(char *str);
int				ft_file_format(char *file, char *file_format);
void			ft_clean_arr(char **arr);
int64_t			ft_ternary64(int flag, int64_t a, int64_t b);
double			ft_ternary_double(int flag, double a, double b);
int8_t			ft_set8(int8_t *a, int8_t b);
int16_t			ft_set16(int16_t *a, int16_t b);
int32_t			ft_set32(int32_t *a, int32_t b);
int64_t			ft_set64(int64_t *a, int64_t b);
void			ft_free(void *pt);
void			*ft_malloc(size_t size);
void			ft_print_arr(char **arr);
int				ft_add_str_to_arr(char *str, char ***arr);
void			ft_save_rgb(t_rgb *rgb, char *rgb_code);
int				ft_encode_rgb(uint8_t red, uint8_t green, uint8_t blue);
void			ft_square_array(char ***arr, char c);
char			*ft_charstr(char c, size_t size);
size_t			ft_arr_height(char ***arr);
size_t			ft_arr_width(char ***arr);

#endif
