#include <iostream>
using std::cin;
using std::cout;
using std::endl;
#include <getopt.h> // to parse long arguments.
#include <string>
using std::string;

/* doubly linked list node: */
struct node {
	string data;
	node* prev;
	node* next;
	// constructor to intialize the node's data, prev, and next pointers
	node (string s = "", node* p = NULL, node* n = NULL) : data(s), prev(p), next(n) {}
};

// This is a function to print the list in reverse if necessary
void reversePrint(node* head) {
	if (head == NULL) {
		return;
	}
	node* tail = head;
	while (tail -> next != NULL) {
		tail = tail -> next;
	}
	while (tail != NULL) {
		cout << tail -> data << endl;
		tail = tail -> prev;
	}
}

// Delete function to free up any memory not in use anymore
void listDelete(node* head) {
	node* current = head;
	while (current != NULL) {
		node* next = current -> next;
		delete current;
		current = next;
	}
}

int main(int argc, char *argv[]) {
	/* define long options */
	static int unique=0, reverse=0;
	static struct option long_opts[] = {
		{"unique",   no_argument,       &unique,   'u'},
		{"reverse",  no_argument,       &reverse,  'r'},
		{0,0,0,0} // this denotes the end of our options.
	};
	/* process options */
	char c; /* holds an option */
	int opt_index = 0;
	while ((c = getopt_long(argc, argv, "ur", long_opts, &opt_index)) != -1) {
		switch (c) {
			case 'u':
				unique = 1;
				break;
			case 'r':
				reverse = 1;
				break;
			case '?': /* this will catch unknown options. */
				return 1;
		}
	}
	/* NOTE: at this point, variables 'reverse' and 'unique' have been set
	 * according to the command line.  */
	node* head = NULL; // initializes the head of the linked list to NULL
	string line; // variable to hold the input lines
	while (getline(cin, line)) { // read lines from stdin
		node* current = head; // start at the head of the linked list
		node* prev = NULL; // intialize the previous node pointer to NULL
		node* new_node = new node(line); // create a new node with the input data
		while (current != NULL && current -> data < line) { // Find the correct position to insert the node
			prev = current;
			current = current -> next;
		}
		if (prev == NULL) { // insert at beginning
			new_node -> next = head;
			if (head != NULL) {
				head -> prev = new_node;
			}
			head = new_node;
		} else { // insert in middle or end
			new_node -> next = prev -> next;
			if (prev -> next != NULL) {
				prev -> next -> prev = new_node;
			}
			prev -> next = new_node;
			new_node -> prev = prev;
		}
	}
	if (reverse) { // if the reverse condition was approved
		reversePrint(head); // print the list in reverse order
	} else { // otherwise print the list in normal order
		node* current = head;
		while (current != NULL) {
			cout << current -> data << endl;
			current = current -> next;
		}
	}
	listDelete(head); // Delete function to be used at the end
	/* TODO: finish writing this.  Maybe use while(getline(cin,line)) or
	 * similar to read all the lines from stdin. */
	return 0;
}
