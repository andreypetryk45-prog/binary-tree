Since I've tried just to use getline() to get the value of a file, by reading it by line, it didn't work as I thought it would because as I later found out, .csv adds after each line not only '\0', i.e. the end of a line, but also '\r'.  
To remember: every .csv file ends with '\r' and '\n', except for the very last line, which look the next way: '\r\n'. '\r' returns a carriage(cursor) to the beginning of a current line, \\n' changes a line, i.e. we changes the current line to the next; 
That's why my file reading didn't work:
![The example of why it doesn't work and should be rewritten](the_problem_of_csv_file.png)


```cpp
    {
        if (prev == nullptr) // it's a root that needs to be deleted
        {
        }
        else
        {

            // THE CURRENT IS TO THE LEFT OF THE PREVIOUS NODE
            if (prev->bpm > bpm)
            {
                if (head->left != nullptr && head->right != nullptr) // there're both children
                {
                    prev->left = head->right; // binding the previous node(the one before the one we want to delete) to the right child of the current node tree, since it's bigger than the left one
                    (head->right)->left = head->left;

                    delete head;

                    return;
                }

                if (head->right != nullptr && head->left == nullptr) // there's only a right child
                {
                    prev->left = head->right; // binding the previous node(the one before the one we want to delete) to the right child of the current node tree, since it's bigger than the left one

                    delete head;
                    return;
                }

                if (head->right == nullptr && head->left != nullptr)
                {                            // there's only a left child
                    prev->left = head->left; // binding the previous node(the one before the one we want to delete) to the right child of the current node tree, since it's bigger than the left one

                    delete head;
                    return;
                }

                if (head->right == nullptr && head->left == nullptr)
                { // both don't have any child
                    prev->left = nullptr;
                    delete head;

                    return;
                }
            }
            // THE CURRENT IS TO THE RIGHT OF THE PREVIOUS NODE
            if (prev->bpm < bpm) // then the current elemnt is the left child of the previous one:
            {
                if (head->left != nullptr && head->right != nullptr) // there're both children
                {
                    // prev->right = head->right; // binding the previous node(the one before the one we want to delete) to the right child of the current node tree, since it's bigger than the left one

                    p_bstnode curr = head->left;
                    p_bstnode prev_1 = curr;

                    while (curr->right != nullptr)
                    {
                        prev_1 = curr;
                        curr = curr->right;
                    }

                    prev_1->right = nullptr;

                    prev->left = curr;
                    curr->left = head->left;
                    curr->right = head->right;

                    delete head;

                    return;
                }

                if (head->right != nullptr && head->left == nullptr) // there's only a right child
                {
                    prev->right = head->right; // binding the previous node(the one before the one we want to delete) to the right child of the current node tree, since it's bigger than the left one

                    delete head;
                    return;
                }

                if (head->right == nullptr && head->left != nullptr)
                {                             // there's only a left child
                    prev->right = head->left; // binding the previous node(the one before the one we want to delete) to the right child of the current node tree, since it's bigger than the left one

                    delete head;
                    return;
                }

                if (head->right == nullptr && head->left == nullptr)
                { // both don't have any child
                    prev->right = nullptr;
                    delete head;

                    return;
                }
            }
        }
```