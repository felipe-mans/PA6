#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include <sstream>
#include "network.h"
#include "user.h"

void print_menu() {
	cout << endl;
	cout << "Please select any of the following options." << endl;
	cout << "Enter command number followed by parameters" << endl;
	cout << "Option 1: Add a user (1 Full Name birth_year zipcode)" << endl;
	cout << "Option 2: Add friend connection (2 Username Username)" << endl;
	cout << "Option 3: Remove friend connection (3 Username Username)" << endl;
	cout << "Option 4: Print users (4)" << endl;
	cout << "Option 5: List friends (5 Username)" << endl;
	cout << "Option 6: Write to file (6 filename)" << endl;
	cout << "Option 7: Shortest path (7 Username Username)" << endl;
	cout << "Option 8: Disjoint sets (8)" << endl;
	cout << "Option 9: Friend suggestions (9 Username)" << endl;
	cout << "Enter 0 to quit" << endl;
	cout << endl;
}

int main(int argc, char *argv[]) {
	Network social_net;
	std::string filename = argv[1];
	int read_file = social_net.read_friends(filename.c_str());
	if (read_file == -1){
		cout << "Error opening file. Try again" << endl;
		return 0;
	}
	print_menu();
	int option;
	cin >> option;
	while (option < 10 && option > 0) {
		if (option == 1){
			std::string full_name, first, last;
			int birth_year, zipcode;
			cin >> first >> last >> birth_year >> zipcode;
			full_name = first + " " + last;
			social_net.add_user(full_name, birth_year, zipcode);
		}
		else if (option == 2) {
			std::string user1, user2, first1, last1, first2, last2;
			cin >> first1 >> last1 >> first2 >> last2;
			user1 = first1 + " " + last1;
			user2 = first2 + " " + last2;
			int result = social_net.add_connection(user1, user2);
			if (result == -1) {
				cout << "Error: Invalid user combination" << endl;
			}
		}
		else if (option == 3) {
			std::string user1, user2, first1, last1, first2, last2;
			cin >> first1 >> last1 >> first2 >> last2;
			user1 = first1 + " " + last1;
			user2 = first2 + " " + last2;
			int result = social_net.remove_connection(user1, user2);
			if (result == -1) {
				cout << "Error: Invalid user combination" << endl;
			}
		}
		else if (option == 4) {
			cout << left << setw(7) << "ID"; 
			cout << setw(20) << "Name";
			cout << setw(10) << "Year";
			cout << setw(10) << "Zip" << endl;
			cout << "===================================================" << endl;
			for (int i = 0; i < social_net.get_users()->size(); i++){
				User curr = social_net.get_users()->at(i);
				int a = curr.get_userID();
				stringstream ss;
				ss << a;
				std::string ID = ss.str() + ".";
				cout << left << setw(7) << ID;
				cout << setw(20) << curr.get_name();
				cout << setw(10) << curr.get_bday();
				cout << setw(10) << curr.get_zip() << endl;	
			}

		}
		else if (option == 5) {
			std::string first, last, full_name;
			cin >> first >> last;
			full_name = first + " " + last;
			cout << left << setw(7) << "ID";
			cout << setw(20) << "Name"; 
			cout << setw(10) << "Year";
			cout << setw(10) << "Zip" << endl;
			cout << "===================================================" << endl;
			int curr_id = social_net.get_id(full_name);
			if (curr_id == -1) {
				cout << "User does not exist" << endl;
			}
			else {
				User curr = social_net.get_users()->at(curr_id);
				int num_friends = curr.get_friends()->size();
				for (int i=0; i < num_friends; i++) {
					User amigo = social_net.get_users()->at(curr.get_friends()->at(i));
					int a = amigo.get_userID();
					stringstream ss;
					ss << a;
					std::string ID = ss.str() + ".";
					cout << left << setw(7) << ID;
					cout << setw(20) << amigo.get_name();
					cout << setw(10) << amigo.get_bday();
					cout << setw(10) << amigo.get_zip() << endl;
				}
			}
		}
		else if (option == 6) {
			std::string filename2;
			cin >> filename2;
			int write_to_file = social_net.write_friends(filename2.c_str());
			if (write_to_file == -1)
				cout << "Error: Could not write to file" << endl;
		}
		else if (option == 7) {
			std::string first1, first2, last1, last2;
			cin >> first1 >> last1 >> first2 >> last2;
			std::string user1, user2;
			user1 = first1 + " " + last1;
			user2 = first2 + " " + last2;
			int from = social_net.get_id(user1);
			int to = social_net.get_id(user2);
			vector<int> result = social_net.shortest_path(from, to);
			int distance = result.size();
			if (distance == 0)
				cout << "None" << endl;
			else {
				cout << "Distance: " << distance << endl;
				for (int i=result.size()-1; i >= 0; i--) {
					cout << social_net.get_users()->at(result[i]).get_name() << " -> ";
				}
				cout << user2 << endl;
			}
		}
		else if (option == 8) {
			vector<vector<int> > disjoint_sets = social_net.groups();
			for (int i=0; i < disjoint_sets.size(); i++) {
				cout << "Set " << i+1 << " => ";
				int tempID = disjoint_sets[i][0];
				cout << social_net.get_users()->at(tempID).get_name();
				for (int j=1; j < disjoint_sets[i].size(); j++) {
					int userID = disjoint_sets[i][j];
					cout << ", " << social_net.get_users()->at(userID).get_name();
				}
				cout << endl;
			}
		}
		else if (option == 9) {
			std::string first, last, full_name;
			cin >> first >> last;
			full_name = first + " " + last;
			int score;
			int tempID = social_net.get_id(full_name);
			vector<int> result = social_net.suggest_friends(tempID, score);
			if (score == 0)
				cout << "None" << endl;
			else {
				cout << "The suggested friend(s) is/are:" << endl;
				for (int i=0; i < result.size(); i++) {
					int userID = result[i];
					std::string username;
					username = social_net.get_users()->at(userID).get_name();
					cout << "\t" << username << "\tScore: " << score << endl;
				}
			}
		}
		else {
			return 0;
		}
		print_menu();
		cin >> option;
	}
	return 0;
}
