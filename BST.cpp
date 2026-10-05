#include <iostream>
#include <string>
#include <fstream>

using std::string;

#include "BST.h"

p_bstnode insert_tree_node(p_bstnode &head, int bpm, string song_s_name, string artist) // we need to pass the value of
{
    if (head == nullptr)
    {
        head = new bstnode; // memory allocaion and binding an old and a new element(old_curr = new bstnode)
        head->bpm = bpm;
        head->song_s_name = song_s_name;
        head->artist = artist;

        head->left = nullptr;
        head->right = nullptr;

        return head;
    }

    if (bpm < head->bpm)
    {
        head->left = insert_tree_node(head->left, bpm, song_s_name, artist);
    }
    else
    {
        head->right = insert_tree_node(head->right, bpm, song_s_name, artist);
    }

    return head;
}

void form_binary_search_tree(p_bstnode &head)
{
    std::ifstream file("songs.csv"); // creating a stream to read data from
    string line;                     // using to procress each line within the file using getline(file, line)

    // since a file is .csv, we need to pass the first line because it's just a header
    std::getline(file, line);

    while (std::getline(file, line)) // since getline() reeds character until '\n', once it finds it, '\n' is no longer stored in a line
    {
        // view README:
        if (line.back() == '\r')
        {                    // line.back() chaeck if the last element of a line is '\r'
            line.pop_back(); // if so, it's deleted(the only case it's not true - the last line)
        }

        int first_comma = 0;
        int second_comma = 0;
        for (int i = 0; i < line.length(); i++)
        {
            if (line[i] == ',')
            {
                if (first_comma == 0)
                {
                    first_comma = i;
                }
                else
                {
                    second_comma = i;
                }
            }
        }

        string bpm_line = line.substr(0, first_comma);                                     // std::string::substr takes the part of a string: the first argument is the begining of counting, the second one - the length of this part
        int bpm = std::stoi(bpm_line);                                                     // std::stoi() converts a string into an integer variable
        string song_s_name = line.substr(first_comma + 1, second_comma - first_comma - 1); // substractin 1 from the diffeerence between first_comma and second_comma, since second_comma doesn't belong to the  song's name
        string artist = line.substr(second_comma + 1);

        head = insert_tree_node(head, bpm, song_s_name, artist);
    }
}

int get_int()
{
    int bpm;
    std::cout << "Please enter how many beats per minute the song has: " << std::endl;
    std::cin >> bpm;
    return bpm;
}

p_bstnode insert_tree_node(p_bstnode &head, int bpm = get_int()) // during the function call, we're using int bpm as a default parameter, later in the recursive iterations it'll be clearly passed, so it'll be prefectly working
{
    if (head == nullptr)
    {
        head = new bstnode; // memory allocaion and binding an old and a new element(old_curr = new bstnode)

        head->bpm = bpm;
        std::cout << "Please enter a song's name: " << std::endl;
        std::cin >> head->song_s_name;

        std::cout << "Please enter the name of an artist: " << std::endl;
        std::cin >> head->artist;

        head->left = nullptr;
        head->right = nullptr;

        return head;
    }

    if (bpm < head->bpm)
    {
        head->left = insert_tree_node(head->left, bpm);
    }
    else
    {
        head->right = insert_tree_node(head->right, bpm);
    }

    return head;
}

void print_tree_reverse_post_order(p_bstnode head)
{
    if (head == nullptr)
    {
        return;
    }
    print_tree_reverse_post_order(head->right);
    std::cout << "The song: " << head->song_s_name << " by " << head->artist << " has " << head->bpm << " beats per minute" << std::endl;
    print_tree_reverse_post_order(head->left);
}

void delete_by_bpm(p_bstnode &head, int bpm)
{
    if (head == nullptr)
    {
        return;
    }

    if (head->bpm == bpm)
    {
        if (head->right != nullptr && head->left != nullptr)
        { // checks if there two children

            p_bstnode curr = head->left;
            p_bstnode previous_of_curr = head;

            while (curr->right != nullptr)
            { // descending to the rightmost node of the subtree, whose root is head->left
                previous_of_curr = curr;
                curr = curr->right;
            }
            // now we need to check if the current we found is not the right child of head->left
            if (curr == head->left) //  head->left == nullptr
            {
                curr->right = head->right;
            }
            else
            {
                previous_of_curr->right = curr->left; // since we're going to move this curr away from here, we're binding the right child of the previous tree node of curr with the left child of the curr
                curr->left = head->left;
                curr->right = head->right;
            }

            p_bstnode node_to_delete = head;
            head = curr; // bind the prev to curr, since it's the same as prev->next/right = curr
            delete node_to_delete;
            return;
        }
        else // one or zero children
        {
            p_bstnode curr; // a pointer that will be pointing to the subtree

            if (head->left != nullptr) // there's a left child
            {
                curr = head->left; // that's what will replace head, i.e. the node to delete
            }
            else if (head->right != nullptr) // there's a left child
            {
                curr = head->right;
            }
            else // there's no children
            {
                curr = nullptr;
            }

            p_bstnode node_to_delete = head;
            head = curr; // bind the prev to curr, since it's the same as prev->next/right = curr
            delete node_to_delete;
            return;
        }
    }

    if (bpm < head->bpm)
    {
        delete_by_bpm(head->left, bpm);
    }
    else
    {
        delete_by_bpm(head->right, bpm);
    }
}

p_bstnode find_by_song_s_name(p_bstnode head, string song_s_name)
{
    if (head == nullptr)
    {
        return nullptr;
    }

    if (head->song_s_name == song_s_name)
    {
        return head; // will return head if the root has a needed song in its fields
    }

    p_bstnode found = find_by_song_s_name(head->left, song_s_name); // checking the left subtree

    // checking if we found a needed node:
    if (found != nullptr)
    {
        return found;
    }

    return find_by_song_s_name(head->right, song_s_name); // cheching the right subtree
}

void delete_by_song_s_name(p_bstnode &head, string song_s_name)
{
    p_bstnode found = find_by_song_s_name(head, song_s_name);

    // checking whether there's such a song at all:
    if (found != nullptr)
    {
        delete_by_bpm(head, found->bpm);
        return;
    }

    std::cout << "Unfortunately there is no node you're trying to delete, please cheack if you wrote it correclty! " << std::endl;
    return;
}

void print_interval(p_bstnode head, int lower_endpoint, int upper_endpoint){
    if (head == nullptr)
    {
        return;
    }

    if (head->bpm > lower_endpoint) //checks if the current node's bpm are bigger than the lower endpoint. If so we're diving in the left subtree
    {
        print_interval(head->left, lower_endpoint, upper_endpoint);
    }

    if (head->bpm >= lower_endpoint && head->bpm <= upper_endpoint) //checks if it's within the range, if so it's being prnted
    {
        std::cout << "The song: " << head->song_s_name
                  << " by " << head->artist << " has "
                  << head->bpm << " beats per minute" << std::endl;
    }

    if (head->bpm < upper_endpoint) //The right subtree might contain values inside our interval
    {
        print_interval(head->right, lower_endpoint, upper_endpoint);
    }
}