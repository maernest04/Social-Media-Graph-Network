#ifndef SOCIAL_MEDIA_GRAPH_PROJECT_USER_GRAPH_H
#define SOCIAL_MEDIA_GRAPH_PROJECT_USER_GRAPH_H

#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <vector>
#include "User.h"

using namespace std;

class User_Graph {
private:
    //Unordered map with the key as the user's name
    //and the value as the pointer to the user
    unordered_map<string, User*> user_map;
    //Unordered map with the key as the pointer to the user
    //and the value being an unordered set of the user's friends
    unordered_map<User*, unordered_set<User*>> friendships_map;
    /**
     * Recursive helper function
     * @param current_user current user we are visiting
     * @param starting_user user we are recommending friends for
     * @param starting_user_interests interests of the starting user
     * @param recommended_friends vector recommended friends that will be returned
     * @param visited_users unordered set of visited users
     */
    void DFS_helper(User *current_user, User* starting_user, const unordered_set<string> starting_user_interests,
                    vector<User*>& recommended_friends, unordered_set<User*>& visited_users);

public:
    /**
     * Default constructor for a user graph
     */
    User_Graph();
    /**
     * Adds a user to the graph
     * @param user_to_add to the graph
     */
    void add_user(User *user_to_add);
    /**
     * Removes a user from the graph
     * @param user_to_remove from the grpah
     */
    void remove_user(const string user_to_remove);
    /**
     * Checks if the user exists in the unordered map
     * @param name of the user
     * @return true or false
     */
    bool has_user(const string name);





    /**
     * Adds a friend ship between 2 users
     * @param first_user_name name of the first user
     * @param second_user_name name of the second user
     */
    void add_friendship(const string first_user_name, const string second_user_name);
    /**
     * Removes a friend ship between 2 users
     * @param first_user_name name of the first user
     * @param second_user_name name of the second user
     */
    void remove_friendship(const string first_user_name, const string second_user_name);
    /**
     * Checks If a friendship exists between 2 users
     * @param first_user_name
     * @param second_user_name
     * @return
     */
    bool has_friendship(const string first_user_name, const string second_user_name);





    /**
     * Finds the user with the most posts
     * @return pointer to most active user
     */
    User* find_most_active_user();
    /**
     * Searches for all users with a specific interest
     * @param interest we are looking for
     * @return vector of users that have that interest
     */
    vector<User*> search_users_by_interest(const string interest);
    /**
     * Recommends friends for the first user based on their friends' friends
     * @param first_user_name first user
     * @param second_user_name second user
     * @return vector of pointers to mutual users
     */
    unordered_set<User*> recommend_mutual_friends(const string first_user_name);





    /**
     * Recommends friends by going through the unordered map,
     * searching for users with similar interests
     * @param user_name of the user we want to find similar interests with
     * @return vector of pointers to all users with similar interests
     */
    vector<User*> recommend_friends_normal(const string user_name);
    /**
     * Recommends friends by using depth first search with a stack
     * @param user_name of the user we want to find similar interests with
     * @return vector of pointers to all users with similar interests
     */
    vector<User*> recommend_friends_DFS_stack(const string user_name);





    /**
     * Recommends friends with similar interests by using depth first search with recursion
     * @param user_name of the user we want to find similar interests with
     * @return vector of pointers to all users with similar interests
     */
    vector<User*> recommend_friends_DFS(const string user_name);





    /**
     * Searches for the shortest path between 2 users
     * @param first_user_name
     * @param second_user_name
     * @return
     */
    vector<User*> shortest_path_between_users_BFS(string first_user_name, string second_user_name);
};


#endif //SOCIAL_MEDIA_GRAPH_PROJECT_USER_GRAPH_H
