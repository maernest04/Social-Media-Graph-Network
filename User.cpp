#include "User.h"
#include <vector>
#include <iterator>
#include <string>

User::User(string name, int number_of_posts)
{
    this->name = name;
    this->number_of_posts = number_of_posts;
}

void User::change_name(string new_name)
{
    this->name = new_name;
}

void User::add_interest(string interest)
{
    if(interests.count(interest) > 0)
    {
        cout << "This user already has this interest!" << endl;
        return;
    }

    interests.insert(interest);

    cout << interest << " has been added to " << get_name() << "'s interests." << endl;
}

void User::remove_interest(string interest)
{
    if(interests.count(interest) == 0)
    {
        cout << "This user already does not have this interest!" << endl;
        return;
    }

    interests.erase(interest);

    cout << interest << " has been removed from " << get_name() << "'s interests." << endl;
}

bool User::has_interest(const string interest)
{
    return interests.find(interest) != interests.end();
}

void User::print_user_info() const
{
    //Displaying all of the user's info
    vector<string>::iterator it;
    cout << "Name: " << name << ", Number of posts: " << number_of_posts << ", Interests: ";

    //Using an iterator, we display all of the users' interests
    for(auto it = interests.begin(); it != interests.end(); it++)
    {
        cout << *it << " ";
    }

    cout << endl;
}

unordered_set<string> User::get_interests() const
{
    return interests;
}

string User::get_name() const
{
    return name;
}

int User::get_number_of_posts() const
{
    return number_of_posts;
}
