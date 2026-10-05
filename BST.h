#include <iostream>
#include <string>


struct bstnode{
    int bpm; //the key we'll be sorting according to
    std::string song_s_name;
    std::string artist; 

    bstnode * left;
    bstnode * right;
};

typedef bstnode * p_bstnode;

p_bstnode insert_tree_node(p_bstnode &head, int bpm, std::string song_s_name, std::string artist); //just inserts a tree node
void form_binary_search_tree(p_bstnode & head); //using it to now if there should be an another tree node inserted

int get_int(); //using it to pass bpm to the function
p_bstnode insert_tree_node(p_bstnode & head, int bpm); //using a reference to modify the tree itself

void print_tree_reverse_post_order(p_bstnode head);

void delete_by_bpm(p_bstnode &head, int bpm);

p_bstnode find_by_song_s_name(p_bstnode head, std::string song_s_name);
void delete_by_song_s_name(p_bstnode & head, std::string song_s_name);

void print_interval(p_bstnode head, int lower_endpoint = get_int(), int upper_endpoint = get_int());
// lower/upper endpoint - початок/кінць інтервалу
