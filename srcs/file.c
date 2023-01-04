#include "minirt.h"

// static int invalid_double(char *number)
// {
//     int dot_count;

//     if (number == NULL || ft_strlen(number) <= 0)
//         return (1);
//     while (ft_isdigit(*number) || *number == '.' || \
//     *number == '+' || *number == '-')
//     {
//         if (*number == '.')
//             ++dot_count;
//         ++number;
//     }
//     if (*number != '\0' || dot_count > 1)
//         return (1);
//     return (0);
// }

// static int invalid_vec(char *vec)
// {
//     int i;
//     char **e;

//     e = ft_split(vec, ',');
//     if (e == NULL)
//         return (1);
//     i = 0;
//     while (e[i])
//     {
//         if (invalid_double(e[i]))
//         {
//             free_strs(e);
//             return (1);
//         }
//         ++i;
//     }
//     if (i != 3)
//     {
//         free_strs(e);
//         return (1);
//     }
//     free_strs(e);
//     return (0);
// }

// void invalid_compo_num(t_compo *head)
// {

// }

// void invalid_form(t_compo *head)
// {
//     t_compo *cur;

//     cur = head->next;
//     while (cur)
//     {

//     }
// }

void extension_check(char* filename)
{
    char *temp;

    temp = ft_strnstr(filename, ".rt", ft_strlen(filename));
    if (temp == NULL || ft_strlen(temp) > 3)
        exit_err("Invalid filename extension.");
}

int open_file(char *filename)
{
    int fd;

    fd = open(filename, O_RDONLY);
    if (fd < 0)
        exit_err("Can not open file.");
    return (fd);
}

void init_compo(t_compo *compo, int fd)
{
    char *buf;
    char **split_line;

    compo_list_init(compo);
    while (1)
    {
        buf = get_next_line(fd);
        if (buf)
        {
            split_line = ft_split(buf, ' ');
            if (compo_add(compo, split_line))
            {
                free(buf);
                compo_clear(compo);
                close(fd);
                exit_err("Can not open file.");
            }
            free(buf);
        }
        else
            break ;
    }
}