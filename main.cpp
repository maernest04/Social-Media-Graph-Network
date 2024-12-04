#include <iostream>
#include "User.h"
#include "User_Graph.h"

using namespace std;

int main() {

    //Creating the User_Graph object
    User_Graph graph;

    // Create 10 users with different number of posts and interests
    User* user_1 = new User("Alice", 32);
    user_1->add_interest("Music");
    user_1->add_interest("Traveling");
    user_1->add_interest("Photography");

    User* user_2 = new User("Bob", 10);
    user_2->add_interest("Gaming");
    user_2->add_interest("Music");
    user_2->add_interest("Sports");

    User* user_3 = new User("Charlie", 3);
    user_3->add_interest("Photography");
    user_3->add_interest("Cooking");

    User* user_4 = new User("Diana", 93);
    user_4->add_interest("Traveling");
    user_4->add_interest("Gaming");

    User* user_5 = new User("Eve", 44);
    user_5->add_interest("Reading");

    User* user_6 = new User("Frank", 7);
    user_6->add_interest("Music");
    user_6->add_interest("Sports");
    user_6->add_interest("Cooking");

    User* user_7 = new User("Grace", 80);
    user_7->add_interest("Cooking");
    user_7->add_interest("Music");

    User* user_8 = new User("Hank", 51);
    user_8->add_interest("Traveling");
    user_8->add_interest("Photography");

    User* user_9 = new User("Ivy", 33);
    user_9->add_interest("Gaming");
    user_9->add_interest("Traveling");

    User* user_10 = new User("Jack", 36);
    user_10->add_interest("Sports");
    user_10->add_interest("Reading");
    user_10->add_interest("Photography");

    user_1->print_user_info();
    user_7->print_user_info();

    cout << endl;

    //Adding users to the graph
    graph.add_user(user_1);
    graph.add_user(user_2);
    graph.add_user(user_3);
    graph.add_user(user_4);
    graph.add_user(user_5);
    graph.add_user(user_6);
    graph.add_user(user_7);
    graph.add_user(user_8);
    graph.add_user(user_9);
    graph.add_user(user_10);

    cout << endl;





    //Testing for users that already exist
    graph.add_user(user_4);
    graph.add_user(user_9);

    cout << endl;





    //Testing if the user exists in the graph
    string result = "";

    graph.remove_user("Frank");

    result = graph.has_user("Frank") ? "Frank exists in the graph." : "Frank doesn't exist in the graph";
    cout << result << endl;

    graph.add_user(user_6);

    result = graph.has_user("Frank") ? "Frank exists in the graph." : "Frank doesn't exist in the graph";
    cout << result << endl;

    cout << endl;

    //Adding friendships
    graph.add_friendship("Alice", "Bob");
    graph.add_friendship("Alice", "Diana");
    graph.add_friendship("Bob", "Charlie");
    graph.add_friendship("Diana", "Eve");
    graph.add_friendship("Frank", "Grace");
    graph.add_friendship("Hank", "Ivy");
    graph.add_friendship("Jack", "Alice");
    graph.add_friendship("Eve", "Bob");
    graph.add_friendship("Hank", "Charlie");
    graph.add_friendship("Ivy", "Grace");
    graph.add_friendship("Frank", "Diana");
    graph.add_friendship("Grace", "Eve");
    graph.add_friendship("Eve", "Ivy");
    graph.add_friendship("Jack", "Hank");

    cout << endl;





    //Testing for friendships that already exist
    graph.add_friendship("Grace", "Frank");
    graph.add_friendship("Diana", "Eve");

    cout << endl;





    //Testing for friendships with users that don't exist
    graph.add_friendship("Frank", "Frank");
    graph.add_friendship("Ethan", "Frank");
    graph.add_friendship("Frank", "Joe");

    cout << endl;





    //Testing for friendship removal
    graph.remove_friendship("Diana", "Eve");
    result = graph.has_friendship("Diana", "Eve")
             ? "This friendship exists." : "This friendship doesn't exist.";
    cout << result << endl;

    graph.add_friendship("Diana", "Eve");
    result = graph.has_friendship("Diana", "Eve")
             ? "This friendship exists." : "This friendship doesn't exist.";
    cout << result << endl;

    graph.remove_friendship("Ivy", "Charlie");

    cout << endl;





    //Testing finding most active user
    User *most_active_user = graph.find_most_active_user();
    most_active_user->print_user_info();





    //Testing finding users by interest
    vector<User*> users_interested_in_sports = graph.search_users_by_interest("Sports");

    cout << "Users interested in sports include: ";
    for(auto &user : users_interested_in_sports)
    {
        cout << user->get_name() << " ";
    }

    cout << endl;

    vector<User*> users_interested_in_music = graph.search_users_by_interest("Music");

    cout << "Users interested in music include: ";
    for(auto &user : users_interested_in_music)
    {
        cout << user->get_name() << " ";
    }

    cout << endl;

    cout << endl;





    //Testing for mutual friendship
    unordered_set<User*> mutual_friendship = graph.recommend_mutual_friends("Hank");

    cout << "Recommended friends through Hank's mutual friends include ";
    for(auto &mutual_user : mutual_friendship)
    {
        cout << mutual_user->get_name() << " ";
    }

    cout << endl;

    cout << endl;





    //Testing the recommend friends through mutual friendships
    vector<User*> mutual_recommended_friends = graph.recommend_friends_normal("Bob");

    cout << "Recommended friends through mutual friends for Bob are ";
    for(auto &friend_user : mutual_recommended_friends)
    {
        cout << friend_user->get_name() << " ";
    }

    cout << endl;

    mutual_recommended_friends = graph.recommend_friends_normal("Charlie");

    cout << "Recommended friends through mutual friends for Charlie are ";
    for(auto &friend_user : mutual_recommended_friends)
    {
        cout << friend_user->get_name() << " ";
    }

    cout << endl;

    cout << endl;





    //Testing the recommend friends with similar interest through normal map iteration
    vector<User*> normal_recommended_friends = graph.recommend_friends_normal("Frank");

    cout << "Recommended friends for Frank with similar interest through normal map iteration include ";
    for(auto &friend_user : normal_recommended_friends)
    {
        cout << friend_user->get_name() << " ";
    }

    cout << endl;

    normal_recommended_friends = graph.recommend_friends_normal("Bob");

    cout << "Recommended friends for Bob with similar interest through normal map iteration include ";
    for(auto &friend_user : normal_recommended_friends)
    {
        cout << friend_user->get_name() << " ";
    }

    cout << endl;

    normal_recommended_friends = graph.recommend_friends_normal("Ivy");

    cout << "Recommended friends for Ivy with similar interest through normal map iteration include ";
    for(auto &friend_user : normal_recommended_friends)
    {
        cout << friend_user->get_name() << " ";
    }

    cout << endl;

    cout << endl;





    //Testing the recommend friends with similar interest through a DFS with a stack
    vector<User*> DFS_stack_recommended_friends = graph.recommend_friends_DFS_stack("Frank");

    cout << "Recommended friends for Frank with similar interest through DFS with a stack include ";
    for(auto &friend_user : DFS_stack_recommended_friends)
    {
        cout << friend_user->get_name() << " ";
    }

    cout << endl;

    DFS_stack_recommended_friends = graph.recommend_friends_DFS_stack("Bob");

    cout << "Recommended friends for Bob with similar interest through DFS with a stack include ";
    for(auto &friend_user : DFS_stack_recommended_friends)
    {
        cout << friend_user->get_name() << " ";
    }

    cout << endl;

    DFS_stack_recommended_friends = graph.recommend_friends_DFS_stack("Jack");

    cout << "Recommended friends for Jack with similar interest through DFS with a stack include ";
    for(auto &friend_user : DFS_stack_recommended_friends)
    {
        cout << friend_user->get_name() << " ";
    }

    cout << endl;

    cout << endl;





    //Testing the recommend friends with similar interest through a DFS with recursion
    vector<User*> DFS_recursive_recommended_friends = graph.recommend_friends_DFS("Frank");

    cout << "Recommended friends for Frank with similar interest through DFS with recursion include ";
    for(auto &friend_user : DFS_recursive_recommended_friends)
    {
        cout << friend_user->get_name() << " ";
    }

    cout << endl;

    DFS_recursive_recommended_friends = graph.recommend_friends_DFS("Bob");

    cout << "Recommended friends for Bob with similar interest through DFS with recursion include ";
    for(auto &friend_user : DFS_recursive_recommended_friends)
    {
        cout << friend_user->get_name() << " ";
    }

    cout << endl;

    DFS_recursive_recommended_friends = graph.recommend_friends_DFS("Ivy");

    cout << "Recommended friends for Ivy with similar interest through DFS with recursion include ";
    for(auto &friend_user : DFS_recursive_recommended_friends)
    {
        cout << friend_user->get_name() << " ";
    }

    cout << endl;

    return 0;
}
