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

    while (std::getline(file, line)) //since getline() reeds character until '\n', once it finds it, '\n' is no longer stored in a line
    {
         //view README:
        if(line.back() == '\r'){ //line.back() chaeck if the last element of a line is '\r'
            line.pop_back(); //if so, it's deleted(the only case it's not true - the last line)
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

int get_bpm()
{
    int bpm;
    std::cout << "Please enter how many beats per minute the song has: " << std::endl;
    std::cin >> bpm;
    return bpm;
}

p_bstnode insert_tree_node(p_bstnode &head, int bpm = get_bpm()) // during the function call, we're using int bpm as a default parameter, later in the recursive iterations it'll be clearly passed, so it'll be prefectly working
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
    ;
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