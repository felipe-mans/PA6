#ifndef NETWORK_H
#define NETWORK_H
#include <string>
#include <vector>
#include "user.h"


class Network {
 public:
  Network();
  ~Network();
  int read_friends(const char *filename);
  int write_friends(const char *filename);
  void add_user(std::string username, int yr, int zipcode);
  void add_user(User new_user);
  int add_connection(std::string name1, std::string name2);
  int remove_connection(std::string name1, std::string name2);
  int get_id(std::string username);
  vector<User>* get_users();
  vector<int> shortest_path(int from, int to);
  vector<vector<int> > groups();
  vector<int> suggest_friends(int who, int& score);

 private:
 	vector<User> users;  
};


#endif
