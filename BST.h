//This is a linked-list implementation of a binary search tree with basic functions
//Does not use recursion

#include "cmpt_error.h"
#include <iostream>
#include <string>

using namespace std;


class BST {
private:
	struct Node {
		string value;
		Node* left;
		Node* right;
	};

	Node* root;
	class stack {
		public:
			struct stackNode {
				Node* tree_node;
				stackNode* next;
			};
			stackNode* top;

			bool is_stack_empty() {
				return top == nullptr;
			}

			Node* pop() {
				stackNode* temp = top;
				Node* temp2 = top->tree_node;
				top = top->next;
				delete temp;
				return temp2;
			}

			void push(Node* TNode) {
				top = new stackNode{ TNode, top };
			}

			stack() : top{ nullptr } {}; //constructor
			~stack() { //destructor
				while (!(is_stack_empty())) { 
					pop();
				}
			}
		};
	class queue {
		public:
			struct queueNode {
				Node* tree_node;
				queueNode* next;
			};
			queueNode* front;
			queueNode* back;

			bool is_queue_empty() {
				return front == nullptr;
			}

			queue() : front{ nullptr }, back{ nullptr } {};
			~queue() {
				while (!is_queue_empty()) {
					dequeue();
				}
			}

			void enqueue(Node* TNode) {
				queueNode* temp;
				if (is_queue_empty()) {
					front = new queueNode{ TNode, nullptr };
					back = front;
				}
				else {
					temp=new queueNode{ TNode,nullptr };
					back->next = temp;
					back = temp;
				}
			}

			Node* dequeue() {
				queueNode* temp = front;
				Node* temp2 = front->tree_node;
				front = front->next;
				delete temp;
				return temp2;
			}

			int queue_size() {
				int i = 0;
				queueNode* temp = front;
				while (temp != nullptr) {
					i++;
					temp = temp->next;
				}
				return i;
			}
	};

public:
	//Pre-condition:
	//	none
	//Post-condition:
	//	returns true if T is empty
	bool is_empty() const {
		return root == nullptr;
	}

	// Pre-condition:
	//    none
	// Post-condition:
	//    constructs a new empty BST
	// Constraints:
	//    O(1) performance
	BST() : root{ nullptr } {};

	// Pre-condition:
	//    none
	// Post-condition:
	//    deletes all the nodes in this BST
	// Constraints:
	//    O(n) performance
	~BST() {
		if (is_empty()) { //returns if T is already empty
			cout << "Tree has been deleted";
			return;
		}
		stack pre_stack;
		stack post_order_stack;
		Node* temp;
		pre_stack.push(root);
		while (!pre_stack.is_stack_empty()) {
			temp = pre_stack.pop();
			post_order_stack.push(temp);
			if (temp->left != nullptr) {
				pre_stack.push(temp->left);
			}
			if (temp->right != nullptr) {
				pre_stack.push(temp->right);
			}
		}
		while (!post_order_stack.is_stack_empty()) {
			delete post_order_stack.pop();
		}
		return;
	}

	// Pre-condition:
	//    none
	// Post-condition:
	//    returns the number of string in this tree (i.e. n)
	// Constraints:
	//    worst-case O(n) performance; does not use recursion!
	int size() const {
		int s = 0;
		if (is_empty()) { //if T is empty
			return s;
		}
		if (root->left == nullptr && root->right == nullptr) { //if T only contains one node
			s = 1;
			return s;
		}
		stack pre_stack;
		Node* temp;
		pre_stack.push(root);
		while (!pre_stack.is_stack_empty()) {
			temp = pre_stack.pop();
			s++;
			if (temp->right != nullptr) {
				pre_stack.push(temp->right);
			}
			if (temp->left != nullptr) {
				pre_stack.push(temp->left);
			}
		}
		return s;
	}

	// Pre-condition:
	//    none
	// Post-condition:
	//    returns the height of this tree
	// Constraints:
	//    worst-case O(n) performance; does not use recursion!
	// Note:
	//    The height of a BST is the number of links in the longest
	//    root-to-leaf path in the tree. An empty tree is height 0,
	//    and a tree with a single node is also height 0.
	int height() const {
		int h = 0;
		if (is_empty() || (root->left == nullptr && root->right == nullptr)) { //if T is empty or only contains one node
			return h;
		}
		queue q;
		q.enqueue(root);
		while (true) {
			int num_nodes = q.queue_size();
			if (num_nodes == 0) {
				break;
			}
			else {
				h++;
			}
			while (num_nodes > 0)
			{
				Node* temp = q.front->tree_node;
				q.dequeue();
				if (temp->left != nullptr)
					q.enqueue(temp->left);
				if (temp->right != nullptr)
					q.enqueue(temp->right);
				num_nodes--;
			}
		}
		h--;
		return h;
	}

	// Pre-condition:
	//    none
	// Post-condition:
	//    returns true if s is in this tree, and false otherwise
	// Constraints:
	//    worst-case O(h) performance; does not use recursion!
	bool contains(const string& s) const {
		if (is_empty()) { //if T is empty it does not contain s
			return false;
		}
		Node* searcher = root;
		while (searcher != nullptr) {
			if (s == searcher->value) {
				return true;
			}
			else if (stoi(s) < stoi(searcher->value)) {
				searcher = searcher->left;
			}
			else {
				searcher = searcher->right;
			}
		}
		if (searcher == nullptr) {
			return false;
		}
	}

	// Pre-condition:
	//    none
	// Post-condition:
	//    T'.contains(s)
	// Constraints:
	//    worst-case O(h) performance; does not use recursion!
	// Note:
	//    If s is already in T, then insert(s) does nothing.
	void insert(const string& s) {
		Node* temp = root;
		if (is_empty()) {    //case for empty T 
			root = new Node{ s, nullptr, nullptr };
			return;
		}
		if (contains(s)) {
			cout << "Value already exists in T";
			return;
		}
		do {
			if (stoi(s) < stoi(temp->value)) {
				if (temp->left == nullptr) {
					temp->left = new Node{ s, nullptr, nullptr };
					return;
				}
				else {
					temp = temp->left;
				}
			}
			else if (stoi(s) > stoi(temp->value)) {
				if (temp->right == nullptr) {
					temp->right = new Node{ s, nullptr, nullptr };
					return;
				}
				else {
					temp = temp->right;
				}
			}
		} while (true);
		return;
	}

	// Pre-condition:
	//    none
	// Post-condition:
	//    !T'.contains(s)
	// Constraints:
	//    worst-case O(h) performance; does not use recursion!
	// Note:
	//    If s is not in T, then remove(s) does nothing.
	void remove(const string& s) {
		if (!contains(s)) {
			return;
		}
		Node* to_be_deleted=nullptr;
		Node* parent_right=nullptr;
		Node* parent_left=nullptr;
		Node* searcher = root;
		Node* in_order_next;
		Node* parent=nullptr;
		while (searcher != nullptr) {
			if (s == searcher->value) {
				to_be_deleted=searcher;
				break;
			}
			else if (stoi(s) < stoi(searcher->value)) {
				parent_left = searcher;
				searcher = searcher->left;
			}
			else {
				parent_right = searcher;
				searcher = searcher->right;
			}
		}
		if (to_be_deleted->left == nullptr && to_be_deleted->right == nullptr) { //Case 1: Node to be deleted is external
			if (to_be_deleted == root) {
				root = nullptr;
				delete to_be_deleted;
				return;
			}
			if (parent_right->right == to_be_deleted) {
				parent_right->right = nullptr;
				delete to_be_deleted;
				return;
			}
			else if (parent_left->left == to_be_deleted) {
				parent_left->left = nullptr;
				delete to_be_deleted;
				return;
			}
			delete to_be_deleted;
			return;
		}
		else if (to_be_deleted->left == nullptr || to_be_deleted->right == nullptr) { //Case 2: Node to be deleted has one child
			if (to_be_deleted == root) {
				if (root->left != nullptr) {
					root = root->left;
					delete to_be_deleted;
					return;
				}
				else if (root->right != nullptr) {
					root = root->right;
					delete to_be_deleted;
					return;
				}
			}
			else if (parent_right->right == to_be_deleted) {
				if (to_be_deleted->left != nullptr) {
					parent_right->right = parent_right->right->left;
					delete to_be_deleted;
					return;
				}
				else if (to_be_deleted->right != nullptr) {
					parent_right->right = parent_right->right->right;
					delete to_be_deleted;
					return;
				}
			}
			else if (parent_left->left == to_be_deleted) {
				if (to_be_deleted->left != nullptr) {
					parent_left->left = parent_left->left->left;
					delete to_be_deleted;
					return;
				}
				else if (to_be_deleted->right != nullptr) {
					parent_left->left = parent_left->left->right;
					delete to_be_deleted;
					return;
				}
			}
		}
		else { //Case 3: Node to be deleted has three children
			in_order_next = to_be_deleted->left;
			while (in_order_next->right != nullptr) {
				parent = in_order_next;
				in_order_next = in_order_next->right;
			}
			if (parent == nullptr) {
				to_be_deleted->value = in_order_next->value;
				to_be_deleted->left = in_order_next->left;
				delete in_order_next;
				return;
			}
			else {
				to_be_deleted->value = in_order_next->value;
				parent->right = in_order_next->left;
				delete in_order_next;
				return;
			}
		}
		return;
	}

	// Pre-condition:
	//    none
	// Post-condition:
	//    prints all the strings in T to cout in pre-order order
	// Constraints:
	//    worst-case O(n) performance; does not use recursion!
	void print_preorder() const {
		if (is_empty()) {
			cout << "Tree is empty.";
		}
		stack pre_stack;
		Node* temp;
		pre_stack.push(root);
		while (!pre_stack.is_stack_empty()) {
			temp = pre_stack.pop();
			cout << temp->value << "    ";
			if (temp->right != nullptr) {
				pre_stack.push(temp->right);
			}
			if (temp->left != nullptr) {
				pre_stack.push(temp->left);
			}
		}
		cout << endl;
	}

	// Pre-condition:
	//    none
	// Post-condition:
	//    prints all the strings in T to cout in in-order order
	//    (i.e. alphabetical order)
	// Constraints:
	//    worst-case O(n) performance; does not use recursion!
	void print_inorder() const {
		if (is_empty()) {
			cout << "Tree is empty."<<endl;
		}
		stack in_order_stack;
		Node* temp = root;
		Node* temp2;

		while (temp != nullptr) {
			in_order_stack.push(temp);
			temp = temp->left;
		}
		while (!in_order_stack.is_stack_empty()) {
			temp2 = in_order_stack.pop();
			cout << temp2->value << "   ";
			if (temp2->right != nullptr) {
				temp = temp2->right;
			}
			while (temp != nullptr) {
				in_order_stack.push(temp);
				temp = temp->left;
			}
		}
		cout << endl;
	}

	// Pre-condition:
	//    none
	// Post-condition:
	//    prints all the strings in T to cout in post-order order
	// Constraints:
	//    worst-case O(n) performance; does not use recursion!
	void print_postorder() const {
		if (is_empty()) {
			cout << "Tree is empty.";
		}
		stack pre_stack;
		stack post_order_stack;
		Node* temp;
		pre_stack.push(root);
		while (!pre_stack.is_stack_empty()) {
			temp = pre_stack.pop();
			post_order_stack.push(temp);
			if (temp->left != nullptr) {
				pre_stack.push(temp->left);
			}
			if (temp->right != nullptr) {
				pre_stack.push(temp->right);
			}
		}
		while (!post_order_stack.is_stack_empty()) {
			temp = post_order_stack.pop();
			cout << temp->value << "   ";
		}
		cout << endl;
	}


}; // class BST
