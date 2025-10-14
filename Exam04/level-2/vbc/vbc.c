#include "vbc.h"

node *new_node(node n)
{
    node *ret = calloc(1, sizeof(node));
    if (!ret)
        return NULL;
    *ret = n;
    return ret;
}

void destroy_tree(node *n)
{
    if (!n)
        return;
    if (n->type != VAL)
    {
        destroy_tree(n->l);
        destroy_tree(n->r);
    }
    free(n);
}

void unexpected(char c)
{
    if (c)
        printf("Unexpected token '%c'\n", c);
    else
        printf("Unexpected end of input\n");
}


node *parse_primary(char **s)
{
    node *res;
    node tmp;
    
    if (**s == '(')
    {
        (*s)++;
        res = parse_addition(s);
        if (!res || **s != ')')
        {
            destroy_tree(res);
            unexpected(**s);
            return NULL;
        } 
        (*s)++;
        return res;
    }
    if (isdigit(**s))
    {
        tmp.type = VAL;
        tmp.val = **s - '0';
        tmp.l = NULL;
        tmp.r = NULL;
        res = new_node(tmp);
        (*s)++;
        return res;
    }
    unexpected(**s);
    return NULL;
}

node *parse_multiplication(char **s)
{
    node *left;
    node *right;
    node tmp;

    left = parse_primary(s);
    if (!left)
        return NULL;
    while (**s == '*')
    {
        (*s)++;
        right = parse_primary(s);
        if (!right)
        {
            destroy_tree(left);
            return NULL;
        }
        tmp.type = MULTI;
        tmp.l = left;
        tmp.r = right;
        tmp.val = 0;
        left = new_node(tmp);
        if (!left)
        {
            destroy_tree(right);
            return NULL;
        }
    }
    return left;
}

node *parse_addition(char **s)
{
    node *left;
    node *right;
    node tmp;
    
    left = parse_multiplication(s);
    if (!left)
        return NULL;
    while (**s == '+')
    {
        (*s)++;
        right = parse_multiplication(s);
        if (!right)
        {
            destroy_tree(left);
            return NULL;
        }
        tmp.type = ADD;
        tmp.l = left;
        tmp.r = right;
        tmp.val = 0;
        left = new_node(tmp);
        if (!left)
        {
            destroy_tree(right);
            return NULL;
        }
    }
    return left;
}

node *parse_expression(char **s)
{
    node *ret = parse_addition(s);

    if (!ret)
        return NULL;
    else if (**s)
    {
        destroy_tree(ret);
        unexpected(**s);
        return NULL;
    }
    return ret;
}

int eval_tree(node *tree)
{
    switch (tree->type)
    {
        case ADD:
            return eval_tree(tree->l) + eval_tree(tree->r);

        case MULTI:
            return eval_tree(tree->l) * eval_tree(tree->r);

        case VAL:
            return tree->val;
    }
    return 0;
}

int main(int argc, char **argv)
{
    if (argc != 2)
        return 1;

    char *input = argv[1];
    node *tree = parse_expression(&input);
    if (!tree)
        return 1;
    printf("%d\n", eval_tree(tree));
    destroy_tree(tree);
    return 0;
}
