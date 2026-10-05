#include "BST.h"
#include <iostream>

int main()
{
    p_bstnode head = nullptr;

    form_binary_search_tree(head);

    print_tree_reverse_post_order(head);

    return 0;
}