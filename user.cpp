#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "user.h"

using std::vector;
using std::string;
using namespace std;

User::User(string full_name, int user_id, int user_bday, int zipcode) {
	name = full_name;
	id = user_id;
	bday = user_bday;
	zip = zipcode;
}

User::~User() {
	
}

void User::add_friend(int user_id) {
	bool exists = false;
	for (int i=0; i < friends.size(); i++) {
		exists = (friends[i] == user_id);
	}
	if (!exists)
		friends.push_back(user_id);
}

void User::delete_friend (int user_id) {
	for (int i=0; i < friends.size(); i++){
		if (friends[i] == user_id)
			friends.erase(friends.begin() + i);
	}
}

string User::get_name() {
	return name;
}

int User::get_userID() {
	return id;
}

int User::get_bday()  {
	return bday;
}

int User::get_zip() {
	return zip;
}

vector<int>* User::get_friends() {
	return &friends;
}
