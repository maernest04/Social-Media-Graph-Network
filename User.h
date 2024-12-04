#ifndef SOCIAL_MEDIA_GRAPH_PROJECT_USER_H
#define SOCIAL_MEDIA_GRAPH_PROJECT_USER_H

#include <iostream>
#include <vector>
#include <iterator>
#include <unordered_set>

using namespace std;

class User {
private:
    unordered_set<string> interests;
    string name;
    int number_of_posts;
public:
    /**
     * User constructor function
     * @param name of the user
     * @param age of the user
     * @param number_of_posts of the user
     */
    User(string name, int number_of_posts);



    //Setters and utility
    /**
     * Changes name of the user
     * @param new_name new name we want to change it to
     */
    void change_name(string new_name);
    /**
     * Adds an interest for the user
     * @param interest to be added
     */
    void add_interest(string interest);
    /**
     * Checks if the user has the interest
     * @param interest we are trying to find
     * @return true or false
     */
    bool has_interest(string interest);
    /**
     * Prints out all of the user's information
     */
    void print_user_info() const;



    //Getters
    /**
     * @return a vector of the user's insterests
     */
    unordered_set<string> get_interests() const;
    /**
     * @return the user's name
     */
    string get_name() const;
    /**
     * @return the user's number of posts
     */
    int get_number_of_posts() const;
};


#endif //SOCIAL_MEDIA_GRAPH_PROJECT_USER_H
