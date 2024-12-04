#include "User_Graph.h"
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <vector>

User_Graph::User_Graph()
{

}

void User_Graph::add_user(User *user_to_add)
{
    string user_name = user_to_add->get_name();

    //Check if the user already exists
    if(user_map.find(user_name) != user_map.end())
    {
        cout << user_name << " already exists in the graph!" << endl;
        return;
    }

    //If the user doesn't exist, we can simply add it to unordered map
    user_map.emplace(user_name, user_to_add);
    friendships_map.emplace(user_to_add, unordered_set<User*>());

    cout << "The user " << user_name << " has been added to the graph." << endl;
}

void User_Graph::remove_user(const string user_to_remove)
{
    //Check if the user exists
    if(user_map.find(user_to_remove) == user_map.end())
    {
        cout << user_to_remove << " does not exist!" << endl;
        return;
    }

    User *user_to_remove_object = user_map[user_to_remove];

    //Traversing through the entire friends list to remove the user from all user's friends list
    for(auto &friendships : friendships_map)
    {
        friendships.second.erase(user_to_remove_object);
    }

    //Erase the user from the user and friendship map
    user_map.erase(user_to_remove);
    friendships_map.erase(user_to_remove_object);

    cout << "User " << user_to_remove << " has been successfully removed." << endl;
}

bool User_Graph::has_user(const string name)
{
    //Returns whether the user exists in the user unordered map
    return user_map.find(name) != user_map.end();
}










void User_Graph::add_friendship(const string first_user_name, const string second_user_name)
{
    //Checking if the first user exists in the graph
    if(!has_user(first_user_name))
    {
        cout << first_user_name << " does not exist in the graph!" << endl;
        return;
    }

    //Checking if the second user exists in the graph
    if(!has_user(second_user_name))
    {
        cout << second_user_name << " does not exist in the graph!" << endl;
        return;
    }

    //Checking if the users are the same
    if(first_user_name == second_user_name)
    {
        cout << first_user_name << " cannot be friends with themselves!" << endl;
        return;
    }

    User *first_user = user_map[first_user_name];
    User *second_user = user_map[second_user_name];

    //Check if the 2 users are friends already
    if(friendships_map[first_user].find(second_user) != friendships_map[first_user].end())
    {
        //If they are already friends, don't insert
        cout << first_user_name << " and " << second_user_name << " are already friends." << endl;
        return;
    }

    friendships_map[first_user].insert(second_user);
    friendships_map[second_user].insert(first_user);

    cout << first_user_name << " and " << second_user_name << " are now friends." << endl;
}

void User_Graph::remove_friendship(const string first_user_name, const string second_user_name)
{
    //Checking if either user exists in the graph
    if(!has_user(first_user_name))
    {
        cout << first_user_name << " does not exist in the graph!" << endl;
        return;
    }
    if(!has_user(second_user_name))
    {
        cout << second_user_name << " does not exist in the graph!" << endl;
        return;
    }

    //Removing the users from each other's friendship map
    User *first_user = user_map[first_user_name];
    User *second_user = user_map[second_user_name];

    //Check if the 2 users are not friends already
    if(friendships_map[first_user].find(second_user) == friendships_map[first_user].end())
    {
        cout << first_user_name << " and " << second_user_name << " are already not friends." << endl;
        return;
    }

    friendships_map[first_user].erase(second_user);
    friendships_map[second_user].erase(first_user);

    cout << first_user_name << " and " << second_user_name << " are no longer friends." << endl;
}

bool User_Graph::has_friendship(const string first_user_name, const string second_user_name)
{
    //Checking if either user exists in the graph
    if(!has_user(first_user_name))
    {
        cout << first_user_name << " does not exist in the graph!" << endl;
        return false;
    }
    if(!has_user(second_user_name))
    {
        cout << second_user_name << " does not exist in the graph!" << endl;
        return false;
    }

    User *first_user = user_map[first_user_name];
    User *second_user = user_map[second_user_name];

    return friendships_map[first_user].count(second_user) > 0 ? true : false;
}










User* User_Graph::find_most_active_user()
{
    //Checking if there are users to check
    if(user_map.empty())
    {
        cout << "There are no users available!" << endl;
        return nullptr;
    }

    User *most_active_user = nullptr;

    //Traversing through the user map, checking for which user has the most posts
    for(const auto &user : user_map)
    {
        if(most_active_user == nullptr ||
           user.second->get_number_of_posts() > most_active_user->get_number_of_posts())
        {
            most_active_user = user.second;
        }
    }

    return most_active_user;
}

vector<User*> User_Graph::search_users_by_interest(const string interest)
{
    //Check if the graph is empty
    if(user_map.empty())
    {
        cout << "There are no users available!" << endl;
        return {};
    }

    vector<User*> interested_users;

    //Traversing through the user map to find if they have the interest we are looking for
    for(const auto &user : user_map)
    {
        if(user.second->has_interest(interest))
        {
            interested_users.push_back(user.second);
        }
    }

    return interested_users;
}

unordered_set<User*> User_Graph::recommend_mutual_friends(const string first_user_name)
{
    //Checking if the user exists in the graph
    if(!has_user(first_user_name))
    {
        cout << first_user_name << " does not exist in the graph!" << endl;
        return {};
    }

    User *user_1 = user_map[first_user_name];

    //Putting into an unordered set for quick look up
    unordered_set<User*> recommended_mutual_friends;

    // Iterating through the user's friends
    for(const auto friend_of_user : friendships_map[user_1])
    {
        // Iterating through the user's friend's friends
        for(const auto friend_of_friend : friendships_map[friend_of_user])
        {
            // Checking if the user is already friends with that user or is the user themselves
            if(friend_of_friend != user_1 && friendships_map[user_1].count(friend_of_friend) == 0)
            {
                recommended_mutual_friends.insert(friend_of_friend);
            }
        }
    }


    return recommended_mutual_friends;
}










vector<User*> User_Graph::recommend_friends_normal(const string user_name)
{
    //Checking if the user even exists
    if(!has_user(user_name))
    {
        cout << user_name << " does not exist!" << endl;
        return {};
    }

    //Setting up resources to help with searching
    vector<User*> recommended_friends;
    unordered_set<User*> already_recommended;
    User *user = user_map[user_name];

    unordered_set<string> user_interests = user->get_interests();

    // Iterating through the user map
    for(const auto &entry : user_map)
    {
        User *potential_friend = entry.second;

        // Check if the potential friend is our current user, is already a friend, or is already recommended
        if(user == potential_friend || friendships_map[user].count(potential_friend) != 0 ||
            already_recommended.count(potential_friend) != 0)
        {
            continue;
        }

        // Iterating through the user's interests
        for(const auto &interest : user_interests)
        {
            // Checking if the potential friend has similar interests
            if (potential_friend->has_interest(interest))
            {
                recommended_friends.push_back(potential_friend);
                already_recommended.insert(potential_friend);
                break;
            }
        }
    }


    return recommended_friends;
}

vector<User*> User_Graph::recommend_friends_DFS_stack(const string user_name)
{
    //Checking if the user even exists
    if(!has_user(user_name))
    {
        cout << user_name << " does not exist!" << endl;
        return {};
    }

    //Creating our resources to find recommended friends
    User *starting_user = user_map[user_name];
    unordered_set<string> starting_user_interests = starting_user->get_interests();
    vector<User*> recommended_friends;
    unordered_set<User*> visited_users;
    stack<User*> users_to_visit;

    visited_users.insert(starting_user);

    for(const auto &friendship : friendships_map[starting_user])
    {
        users_to_visit.push(friendship);
    }


    //While we still have users to visit
    while(!users_to_visit.empty())
    {
        User *potential_friend = users_to_visit.top();
        users_to_visit.pop();

        //Checking if the potential friend has already been visited
        if(visited_users.count(potential_friend) != 0)
        {
            continue;
        }

        //Adding the potential friend to our visited user set
        visited_users.insert(potential_friend);

        //Iterating through the current user's interests
        for(const auto &interest : starting_user_interests)
        {
            if(potential_friend->has_interest(interest) && friendships_map[starting_user].count(potential_friend) == 0)
            {
                recommended_friends.push_back(potential_friend);
                break;
            }
        }

        //Iterating through the potential friend's friend list,
        //adding those users to our users to visit stack
        for(const auto &user : friendships_map[potential_friend])
        {
            users_to_visit.push(user);
        }
    }

    return recommended_friends;
}










vector<User*> User_Graph::recommend_friends_DFS(const string user_name)
{
    //Checking if the user even exists
    if(!has_user(user_name))
    {
        cout << user_name << " does not exist!" << endl;
        return {};
    }

    //Creating our resources to find recommended friends with our helper
    User *starting_user = user_map[user_name];
    unordered_set<string> starting_user_interests = starting_user->get_interests();
    vector<User*> recommended_friends;
    unordered_set<User*> visited_users;

    DFS_helper(starting_user, starting_user, starting_user_interests,
               recommended_friends, visited_users);

    return recommended_friends;
}

void User_Graph::DFS_helper(User *potential_friend, User *starting_user, const unordered_set<string> starting_user_interests,
                            vector<User*>& recommended_friends, unordered_set<User*>& visited_users)
{
    //Skip if current user has already been visited
    if(visited_users.count(potential_friend) != 0)
    {
        return;
    }

    visited_users.insert(potential_friend);

    //Traversing through the starting user's interests
    for(const auto &interest : starting_user_interests)
    {
        unordered_set<string> potential_friend_interests = potential_friend->get_interests();

        // Check if the potential friend has this interest, isn't already a friend,
        // and the potential friend is not the starting user
        if (potential_friend_interests.count(interest) > 0 &&
            friendships_map[starting_user].count(potential_friend) == 0 &&
            starting_user != potential_friend)
        {
            // Add to recommended friends if they share at least one interest
            // and stop checking further interests once a match is found
            recommended_friends.push_back(potential_friend);
            break;
        }
    }

    //Iterate over the friends of the current user and continue DFS traversal
    //Although this part doesn't use an actual stack, the behavior mimics a stack
    for(const auto &friend_to_visit : friendships_map[potential_friend])
    {
        DFS_helper(friend_to_visit, starting_user, starting_user_interests, recommended_friends, visited_users);
    }
}










vector<User*> User_Graph::shortest_path_between_users_BFS(const string first_user_name, const string second_user_name)
{
    //Checking if either user exists in the graph
    if(!has_user(first_user_name))
    {
        cout << first_user_name << " does not exist in the graph!" << endl;
        return {};
    }
    if(!has_user(second_user_name))
    {
        cout << second_user_name << " does not exist in the graph!" << endl;
        return {};
    }

    if(first_user_name == second_user_name)
    {
        cout << "Both names refer to the same user!" << endl;
        return {user_map[first_user_name]};
    }

    User *user_1 = user_map[first_user_name];
    User *user_2 = user_map[second_user_name];

    //Creating resources to help with breadth first search
    queue<pair<User*, vector<User*>>> users_to_visit;
    unordered_set<User*> visited_users;
    users_to_visit.push({user_1, {user_1}});

    //While there are still users to visit
    while(!users_to_visit.empty())
    {
        //Creating the current path we are at
        pair<User*, vector<User*>> current_path = users_to_visit.front();
        users_to_visit.pop();

        //If a path to the user
        if(current_path.first == user_2)
        {
            return current_path.second;
        }

        //If the user has already been visited, we don't do anything
        if(visited_users.count(current_path.first) == 0)
        {
            visited_users.insert(current_path.first);

            unordered_set<User*>::iterator it;

            // Iterating through all the friends of the current user
            for(const auto &friend_user : friendships_map[current_path.first])
            {
                // If the user's friend has not been visited
                if(visited_users.count(friend_user) == 0)
                {
                    vector<User*> new_path = current_path.second;
                    new_path.push_back(friend_user);
                    users_to_visit.push({friend_user, new_path});
                }
            }
        }
    }

    cout << "No possible path was found between the 2 users" << endl;
    return {};
}
