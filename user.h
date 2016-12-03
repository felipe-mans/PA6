#ifndef USER_H
#define USER_H
#include <string>
#include <vector>

using std::vector;
using std::string;
using namespace std;

class User {
 public:
 	User(string full_name, int user_id, int user_bday, int zipcode);
 	~User();
 	void add_friend(int user_id);
 	void delete_friend(int user_id);
 	string get_name();
 	int get_userID();
 	int get_bday();
 	int get_zip();
 	vector<int>* get_friends();
 	int depth;
 	int predecessor;
 	int member;
 	int score;


 private:
 	string name;
 	int id;
 	int bday;
 	int zip;
 	vector<int> friends;
};


#endif
