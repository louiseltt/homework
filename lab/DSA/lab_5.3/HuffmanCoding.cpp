#include <iostream>
#include "Huffman.h"
#include <cstdlib>
using namespace std;    
int main(int argc, char *argv[])
{
    if ( argc != 3 ) {
        cout << "Usage: \n \t huffmancoding inputfile outputfile" << endl;
        exit(1);
    }
    huffman h(argv[1], argv[2]);
    h.create_pq();
    h.create_huffman_tree();
    h.calculate_huffman_codes();
    h.save_to_file();
    cout << endl;
    return 0;
}
