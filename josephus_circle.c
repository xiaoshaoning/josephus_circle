/* count a list from 1 to n, and delete the m-th item, then count from 1 again,
 * and delete the m-th item again , until there is only one item left
 * output the original order of the survived item
 */

#include <stdlib.h>
#include <stdio.h>

struct node
{
    int original_number;
    int order;
    struct node * previous_node;
    struct node * next_node;
};

struct node * list_initialize(int n)
{
    struct node * first_node_pointer;
    struct node * new_node_pointer;
    struct node * current_node_pointer;
    struct node * last_node_pointer;
    int index;


    if (n == 0)
    {
        first_node_pointer = NULL;
    }
    else
    {
        for (index = 0; index < n; index++)
        {
            new_node_pointer = (struct node *) malloc(sizeof(struct node));

            if (index == 0)
            {
                first_node_pointer = new_node_pointer;
                first_node_pointer->order = 1;
                first_node_pointer->original_number = 1;
                current_node_pointer = first_node_pointer;
            }
            else
            {
                current_node_pointer->next_node = new_node_pointer;
                new_node_pointer->original_number = index + 1;
                new_node_pointer->previous_node = current_node_pointer;
                new_node_pointer->next_node = first_node_pointer;
                current_node_pointer = new_node_pointer;
            }

            if (index == n-1)
            {
                last_node_pointer = current_node_pointer;
                last_node_pointer->next_node = first_node_pointer;
                first_node_pointer->previous_node = last_node_pointer;
            }

        }
    }

    return first_node_pointer;
}

int get_survivor(struct node * first_node_pointer, int n, int m)
{
    struct node * current_node_pointer = first_node_pointer;
    struct node * previous_node_pointer;
    struct node * next_node_pointer;
    struct node * to_be_removed;

    while(current_node_pointer->next_node != current_node_pointer)
    {
        if (current_node_pointer->order != m)
        {
            current_node_pointer->next_node->order = current_node_pointer->order + 1;
            current_node_pointer = current_node_pointer->next_node;
        }
        else
        {
            to_be_removed = current_node_pointer;
            previous_node_pointer = current_node_pointer->previous_node;
            next_node_pointer = current_node_pointer->next_node;
            previous_node_pointer->next_node = next_node_pointer;
            next_node_pointer->previous_node = previous_node_pointer;
            next_node_pointer->order = 1;
            current_node_pointer = next_node_pointer;
            free(to_be_removed);
        }
    }

    return current_node_pointer->original_number;
}

int main(int argc, char ** argv)
{

    int n;
    int m;
    int survivor_order;

    struct node * first_node_pointer;

    if (argc != 3)
    {
        printf("usage: survivor n m");
        return 1;
    }

    n = atoi(argv[1]);
    m = atoi(argv[2]);

    /* build the linked list */
    first_node_pointer = list_initialize(n);

    /* get the survived node of the list */
    survivor_order = get_survivor(first_node_pointer, n, m);

    printf("the survivor is %d\n", survivor_order);

    return 0;
}
