#include "Huffman.h"

#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;

huffman::huffman(char* in_file_name, char* out_file_name) {
    in_file.open(in_file_name);
    if ( !in_file ) {
        cout << "failed to open " << in_file_name << endl;
        exit(1);
    }

    out_file.open(out_file_name, ios::out);
    if ( !in_file ) {
        cout << "failed to open " << in_file_name << endl;
        exit(1);
    }

    for (int i = 0; i < MAX_SIZE; i++) {
        node_array[i] = new huffman_node;
    }
}

void huffman::create_node_array() {
    string s;
    while ( !in_file.eof() ) {
        getline(in_file, s, '\n');
        for (int i = 0; i < s.size(); i++) {
            node_array[s[i]]->freq++;
        }
    }
    cout << "create_node_array success" << endl;
}
void huffman::create_pq() {
    create_node_array();
    for (int i = 0; i < MAX_SIZE; i++) {
        if ( node_array[i]->freq ) {
            pq.push(node_array[i]);
            //cout << (char)i << " " << node_array[i]->freq << " ";
        }
    }
    cout << "create_pq success" << endl;
}
void huffman::create_huffman_tree() {
    node_ptr min_, nmin_;
    while ( !pq.empty() ) {
        if ( pq.size()==1 ) {
            root = pq.top();
            pq.pop();
        }
        else {
            min_ = pq.top();
            pq.pop();
            nmin_ = pq.top();
            pq.pop();
            root = new huffman_node;
            root->left = min_;
            root->right = nmin_;
            root->freq = min_->freq + nmin_->freq;
            pq.push(root);
        }
    }
    cout << "create_huffman_tree success" << endl;
}
void huffman::calculate_huffman_codes() {
    queue<node_ptr> q;
    q.push(root);
    while ( !q.empty() ) {
      node_ptr tmp = q.front();
      q.pop();
      if ( tmp->left==NULL && tmp->right==NULL ) continue;
      if ( tmp->left!=NULL ) {
          tmp->left->code = tmp->code + "0";
          q.push(tmp->left);
      }
      if ( tmp->right!=NULL ) {
          tmp->right->code = tmp->code + "1";
          q.push(tmp->right);
      }
    }
    cout << "create_huffman_codes success" << endl;
}

void huffman::save_to_file() {
    ofstream out_file2;
    out_file2.open(".huffmancode");
    for (int i = 0; i < MAX_SIZE; i++) {
        if ( node_array[i]->freq ) {
            out_file2 << (char)i << " " << node_array[i]->freq  << " " << node_array[i]->code << endl;
        }
    }
    out_file2.close();
    in_file.clear();    
    in_file.seekg(0, in_file.beg);
    string s;
    while ( !in_file.eof() ) {
        getline(in_file, s,'\n');
        for (int i = 0; i < s.size(); i++) {
            out_file << node_array[s[i]]->code;
        }
        out_file << endl;
    }

    cout << "save success" << endl;
}
