#include "minirt.h"

static int invalid_double(char *number)
{
    int dot_count;

    dot_count = 0;
    if (number == NULL || ft_strlen(number) <= 0)
        return (1);
    while (ft_isdigit(*number) || *number == '.' || \
    *number == '+' || *number == '-')
    {
        if (*number == '.')
            ++dot_count;
        ++number;
    }
    if (*number != '\0' || dot_count > 1)
        return (1);
    return (0);
}

static int invalid_vec(char *vec)
{
    int i;
    char **e;

    e = ft_split(vec, ',');
    if (e == NULL)
        return (1);
    i = 0;
    while (e[i])
    {
        if (e[i][0] == '\0' || invalid_double(e[i]))
        {
            free_strs(e);
            return (1);
        }
        ++i;
    }
    if (i != 3)
    {
        free_strs(e);
        return (1);
    }
    free_strs(e);
    return (0);
}

// void invalid_compo_num(t_compo *head)
// {
// }

void check_a(t_compo *head, char **split)
{
    int i;

    i = 0;
    while (split[i])
        ++i;

    if (i != 3 || invalid_double(split[1]) || invalid_vec(split[2]))
        exit_compo_clear(head, "Invalid file form.");
}

void check_c(t_compo *head, char **split)
{
    int i;

    i = 0;
    while (split[i])
        ++i;
    if (i != 4)
        exit_compo_clear(head, "Invalid file form.");
    if (invalid_vec(split[1]))
        exit_compo_clear(head, "Invalid file form.");
    if (invalid_vec(split[2]))
        exit_compo_clear(head, "Invalid file form.");
    if (invalid_double(split[3]))
        exit_compo_clear(head, "Invalid file form.");
}

void check_l_sp(t_compo *head, char **split)
{
    int i;

    i = 0;
    while (split[i])
        ++i;
    if (i != 4)
        exit_compo_clear(head, "Invalid file form.");
    if (invalid_vec(split[1]))
        exit_compo_clear(head, "Invalid file form.");
    if (invalid_double(split[2]))
        exit_compo_clear(head, "Invalid file form.");
    if (invalid_vec(split[3]))
        exit_compo_clear(head, "Invalid file form.");
}

void check_pl(t_compo *head, char **split)
{
    int i;

    i = 0;
    while (split[i])
        ++i;
    if (i != 4)
        exit_compo_clear(head, "Invalid file form.");
    if (invalid_vec(split[1]))
        exit_compo_clear(head, "Invalid file form.");
    if (invalid_vec(split[2]))
        exit_compo_clear(head, "Invalid file form.");
    if (invalid_vec(split[3]))
        exit_compo_clear(head, "Invalid file form.");
}

void check_cy(t_compo *head, char **split)
{
    int i;

    i = 0;
    while (split[i])
        ++i;
    if (i != 6)
        exit_compo_clear(head, "Invalid file form.");
    if (invalid_vec(split[1]))
        exit_compo_clear(head, "Invalid file form.");
    if (invalid_vec(split[2]))
        exit_compo_clear(head, "Invalid file form.");
    if (invalid_double(split[3]))
        exit_compo_clear(head, "Invalid file form.");
    if (invalid_double(split[4]))
        exit_compo_clear(head, "Invalid file form.");
    if (invalid_vec(split[5]))
        exit_compo_clear(head, "Invalid file form.");
}

void invalid_form(t_compo *head)
{
    t_compo *cur;

    cur = head->next;
    while (cur)
    {
        if (!ft_strcmp(cur->split_line[0], "A"))
            check_a(head, cur->split_line);
        else if (!ft_strcmp(cur->split_line[0], "C"))
            check_c(head, cur->split_line);
        else if (!ft_strcmp(cur->split_line[0], "L"))
            check_l_sp(head, cur->split_line);
        else if (!ft_strcmp(cur->split_line[0], "sp"))
            check_l_sp(head, cur->split_line);
        else if (!ft_strcmp(cur->split_line[0], "pl"))
            check_pl(head, cur->split_line);
        else if (!ft_strcmp(cur->split_line[0], "cy"))
            check_cy(head, cur->split_line);
        else
            exit_compo_clear(head, "Invalid file form.");
        cur = cur->next;
    }
}

void extension_check(char* filename)
{
    char *temp;

    temp = ft_strnstr(filename, ".rt", ft_strlen(filename));
    if (temp == NULL || ft_strlen(temp) > 3)
        exit_err("Invalid filename extension.");
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