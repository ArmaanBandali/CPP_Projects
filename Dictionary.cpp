//This code implements a basic dictionary and spell checker when given a dictionary text file
//The implementation is done using an open addressing hash table

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "cmpt_error.h"

using namespace std;

const int initial_size = 11;

class hash_table {
	private:
		struct Node {
			string word;
			string status;
		};
		int length;
		Node* p;
		Node* temp;
		int num_elements;

		void rehash() {
			temp = p;
			int current_length = length;
			length = 2 * length + 7;
			p = new Node[length];
			for (int i = 0; i < length; i++) {
				p[i].word = " ";
				p[i].status = "empty";
			}
			for (int j = 0; j < current_length; j++) {
				if (temp[j].status == "filled") {
					add(temp[j].word);
				}
			}
			delete[] temp;
			temp = nullptr;
		}
	public:
		hash_table() {
			length = initial_size;
			p = new Node[initial_size];
			for (int i = 0; i < length; i++) {
				p[i].word = "0";
				p[i].status = "empty";
			}
			temp = nullptr;
			num_elements = 0;
		}

		~hash_table() {
			delete [] p;
		}

		int hash_code(string s) {
			int a = 43;
			int result = 0;
			int j = 1;
			int b = 0;
			for (int i = 0; i < s.length(); i++) {
				b = b * a;
				if (i == 0) {
					b = 1;
				}
				result = s[i] * b;
			}
			result = result % length;
			while (p[result].status == "filled") {
				result = (result + j*j) % length;
				j++;
			}
			return result;
		}
		std::remov

		double load_factor() {
			return num_elements / length;
		}

		void add(string s) {
			if (load_factor() > 0.5) {
				rehash();
			}
			p[hash_code(s)].word = s;
			p[hash_code(s)].status = "filled";
			num_elements++;
		}

		void remove(string s) {
			int a = 43;
			int result = 0;
			int j = 1;
			int b = 0;
			for (int i = 0; i < s.length(); i++) {
				b = b * a;
				if (i == 0) {
					b = 1;
				}
				result = s[i] * b;
			}
			result = result % length;
			while (p[result].word != s) {
				result = result + j*j % length;
				j++;
			}
			p[result].status = "deleted";
			num_elements--;
		}

		bool check(string s) {
			int a = 43;
			int result = 0;
			int j = 1;
			int b = 0;
			bool contains = 0;
			for (int i = 0; i < s.length(); i++) {
				b = b * a;
				if (i == 0) {
					b = 1;
				}
				result = s[i] * b;
			}
			result = result % length;
			if (p[result].word == s && p[result].status!="deleted") {
				contains = 1;
				return contains;
			}
			while (p[result].status == "filled"||p[result].status == "deleted") {
				result = result + j*j % length;
				j++;
				if (p[result].word == s && p[result].status=="filled") {
					contains = 1;
					return contains;
				}
				if (p[result].status == "empty") {
					return contains;
				}
			}

		}

		string suggest(string s) {
			return "blank";
		}

		
};


int main() {
	string command;
	string word;
	hash_table dictionary;
	hash_table added_words;
	ifstream dict_stream;
	fstream added_stream;

	dict_stream.open("maindict.txt");
	if (dict_stream.fail()) {
		cmpt::error("Program failed to open dictionary file.");
	}
	added_stream.open("addedwords.txt");
	if (added_stream.fail()) {
		cmpt::error("Program failed to open added words file.");
	}

	while (!dict_stream.eof()) {
		dict_stream >> word;
		dictionary.add(word);
	}

	while (!added_stream.eof()) {
		added_stream >> word;
		added_words.add(word);
	}
	
	cout << "Welcome to Armaan's Spell Checker! Enter end if you wish to terminate the program"<<endl;
	cin >> command;
	while (command != "end" ) {
		cin >> word;
		if (command == "check") {
			if (dictionary.check(word)) {
				cout << endl << "Ok";
			}
			else if (added_words.check(word)) {
				cout << endl << "Ok";
			}
			else {
				cout << endl << "\"" << word << "\"" << " is not a word.";
			}
		}
		else if (command == "add") {
			if (dictionary.check(word)||added_words.check(word)) {
				cout << endl << "\"" << word << "\"" << " is already in the dictionary.";
			}
			else  {
				added_words.add(word);
				added_stream << word << endl;
				cout << endl << "\"" << word << "\"" << " has been added to the dictionary.";
			}

		}
		else if (command == "remove") {
			if (!dictionary.check(word) && !added_words.check(word)) {
				cout << endl << "\"" << word << "\"" << " is not in the dictionary.";
			}
			else if (dictionary.check(word)) {
				cout << endl << "\"" << word << "\"" << " cannot be removed from the dictionary the dictionary.";
			}
			else {
				added_words.remove(word);
				cout << endl << "\"" << word << "\"" << " has been removed from the dictionary the dictionary.";
			}

		}
		else if (command == "checkfile") {
			ifstream check_file;
			int k = 1;
			check_file.open(word);
			if (check_file.fail()) {
				cout << endl << "The file could not be opened. Please renter the \"checkfile\" command followed by the filename";
				continue;
			}
			while (!check_file.eof()) {
				check_file >> word;
				if (!(dictionary.check(word) || added_words.check(word))) {
					cout << endl << "The word \"" << word << "\" on line " << k << " is misspelled";
				}
			}
		}
		else if (command == "suggest") {
			if (dictionary.check(word) || added_words.check(word)) {
				cout << endl << "This word is already in the dictionary";
			}
			else {
				cout << endl << "Suggested words: " << dictionary.suggest(word);
			}
		}
		else {
			cout << endl << "You have entered an unknown command. Please try again";
		}

		cin >> command;
	}

	dict_stream.close();
	added_stream.close();
	return 0;
}