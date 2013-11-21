#ifndef HUFFMAN
#define HUFFMAN
typedef huffman_node* node_ptr;
struct huffman_node{
	char id;
	int freq;
	string code;
	node_ptr left,
	         right,
	         parent;
};

class Huffman{
protected:
    node_ptr node_array [MAX_SIZE];
    fstream in_file,
            out_file;
    node_ptr child,
             parent,
             root;
    char id;
    string in_file_name;

    //compare the order in the priority queue
    class compare{
        public:
        	bool operator() ( const node_ptr& c1,
        		              const node_ptr& c2 ) const
        	{ return (*c1).freq > (*c2).freq; }
    };

    //construct the file containing the char and freq
    priority_queue< node_ptr, vector<node_ptr>, compare > pq;

    void create_node_array();

public:
	//initial the object from the input and output
	hufffman( string in_file_name, string out_file_name );

	//construct the priority queue
	void create_pq();

	//construct the huffman tree
	void create_huffman_tree();

	//calculate the huffman code
	void calculate_huffman_codes();

	//save the encoded file
	void save_to_file();
};
#endif