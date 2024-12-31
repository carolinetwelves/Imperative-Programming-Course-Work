/********* main.c ********
    Student Name 	= Caroline Twelves
    Student Number	= 101301400
*/

// Includes go here
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>
#include "a2_nodes.h"
#include "a2_functions.h"

int main()
{

    FILE *csv_file = fopen("user_details.csv", "r");
    if (csv_file == NULL)
    {
        perror("Error opening the CSV file");
        return 1;
    }
    // Parse CSV data and create users
    user_t *users = read_CSV_and_create_users(csv_file, 50);

    fclose(csv_file);

    // welcome message to the interface (only shown once)
    printf("***********************************************\n"
           "\tWelcome to Text-Based Facebook\n"
           "***********************************************\n");

    // intitializing and declaring variables
    _Bool exit = false;
    int main_choice = -1;
    int user_choice = -1;

    while (!exit)
    {
        // welcome message and menu
        print_main_menu();

        // user input
        printf("Enter your choice: ");
        scanf("%d", &main_choice);

        // user input possibilities
        switch (main_choice)
        {
        // 1. Register a new user
        case 1:
        {
            char name[50];
            const char pass[50];
            _Bool user_doesnt_exist;

            // get new user info
            printf("Enter a username: ");
            scanf("%s", name);
            convert_to_lowercase(name); // convert to all lowercase

            // check to see if user already exists
            user_doesnt_exist = find_user(users, name);
            if (user_doesnt_exist)
            {
                printf("Username already taken");
                break;
            }

            printf("Enter an up to 15 characters password: ");
            scanf("%15s", pass);

            // check that password meets length requirements
            while (strlen(pass) < 8)
            {
                printf("Password is too short. \nPlease enter one thats at least 8 characters long: ");
                scanf("%15s", pass);
            }

            // add the user in alphabetical order to the users
            users = add_user(users, name, pass);

            printf("\n\n**** User Added! ****\n");

            break;
        }

        // 2. login with existing user's information
        case 2:
        {
            char name[50];
            const char pass[50];
            user_t *curr_user;

            // get username
            printf("Enter your username: ");
            scanf("%s", name);
            convert_to_lowercase(name);

            // make sure user exists and get user location
            curr_user = find_user(users, name);

            // get user password
            printf("Enter your password: ");
            scanf("%s", pass);

            // check current password is right
            if (curr_user == NULL || strcmp(pass, curr_user->password) != 0)
            {
                printf("\nIncorrect username or passsword.\n");
                break;
            }

            print_user_menu(name);

            // user input
            printf("Enter your choice: ");
            scanf("%d", &user_choice);

            switch (user_choice)
            {
            // 1. Manage profile (change password)
            case 1:
            {
                // get new password and update
                printf("Enter a new password. up to 15 characters: ");
                scanf("%s", curr_user->password);

                break;
            }

            // 2. Manage posts (add/remove)
            case 2:
            {
                const char post_text[250];
                int post_choice = -1;
                _Bool managing_posts = true;
                _Bool removed;

                while (managing_posts)
                {
                    // print menu for managing posts
                    printf("--------------------------------\n\t\t\tManaging %s's posts\n--------------------------------\n\n", name);
                    if (curr_user->posts == NULL)
                    {
                        printf("Note: No posts available for %s\n", name);
                    }
                    printf("1. Add a new post\n2. Remove a post\n3. Return to main menu\nEnter your choice: ");
                    scanf("%d", &post_choice);

                    // manage posts
                    switch (post_choice)
                    {
                    // add new post
                    case 1:
                        // get post content
                        printf("Enter your post content: ");
                        scanf(" %[^\n]s", post_text);

                        // add post
                        add_post(users, post_text);

                        // display posts and post menu displayed
                        display_all_user_posts(users);
                        break;

                    // remove post
                    case 2:

                        removed = delete_post(users);

                        if (removed)
                        {
                            display_all_user_posts(users);
                        }

                        else
                        {
                            printf("\n%s has no posts.\n");
                        }

                        break;

                    // return to main menu
                    case 3:

                        managing_posts = false;
                        break;

                    default:

                        printf("Invalid input.");
                        break;
                    }

                    // incase invalid input next time
                    post_choice = -1;
                }

                break;
            }

            // 3. Manage friends (add/remove)
            case 3:
            {
                char friend_name[50];
                user_t *find_friend;
                int friend_choice = -1;
                _Bool success;
                _Bool friends = true;

                // print menu for managing posts
                printf("-------------------------------------------\n\tManaging %s's friends\n-------------------------------------------\n\n", name);

                while (friends)
                {
                    printf("1. Add a new friend\n2. Remove a friend\n3. Return to main menu\nEnter your choice: ");
                    scanf("%d", &friend_choice);

                    switch (friend_choice)
                    {
                    // add new friend
                    case 1:
                        // get post content
                        printf("Enter a new friends name: ");
                        scanf("%s", friend_name);
                        convert_to_lowercase(friend_name);

                        find_friend = find_user(users, friend_name);

                        if (find_friend == NULL)
                        {
                            printf("--------------------------------\n\t\tFriend not found.\n--------------------------------\n\n");
                            break;
                        }

                        // add friend;
                        add_friend(curr_user, friend_name);

                        printf("\nFriend added to the list.\n\n");
                        break;

                    // delete friend
                    case 2:
                        display_user_friends(curr_user);

                        // get friends name
                        printf("Enter a new friend's name to delete: ");
                        scanf("%s", friend_name);
                        convert_to_lowercase(friend_name);

                        // printf("List of %s's friends: \n", curr_user);
                        success = delete_friend(curr_user, friend_name);

                        if (success)
                        {
                            printf("Updated list of %s's friends: \n", curr_user);
                            display_user_friends(curr_user);
                        }

                        else
                        {
                            printf("Invalid friend's name");
                        }
                        break;

                    // Return to main menu
                    case 3:
                        friends = false;
                        break;

                        // incorrect input
                    default:
                        printf("Incorrect input. Try again.");
                        break;
                    }

                    // incase invalid input next time
                    friend_choice = -1;
                }

                break;
            }

            // 4. Display a friend's posts
            case 4:
            {
                char friend_name[50];
                user_t *user_friend;

                // get username
                printf("Enter the name of the friend who's posts you wish to display: ");
                scanf("%s", friend_name);
                convert_to_lowercase(friend_name);

                // get location of username
                user_friend = find_friend(users, curr_user, friend_name);

                // if username doesn't exist
                if (user_friend == NULL)
                {
                    printf("--------------------------------\n\t\tFriend not found.\n--------------------------------\n\n");
                    break;
                }

                if (user_friend->posts == NULL)
                {
                    printf("%s has no friends to delete.\n\n", curr_user->username);
                    break;
                }

                display_posts_by_n(user_friend, 3);
                break;
            }

            // 5. Exit
            case 5:
            {
                teardown(users);
                printf("Goodbye!! Have a nice day");
                exit = true;
                break;
            }

            default:
            {
                printf("Invalid choice. Please try again.\n");
                break;
            }
            }
            break;
        }

        // 3. exit and tear down the program
        case 3:

            teardown(users);
            printf("Goodbye!! Have a nice day");
            exit = true;
            break;

        default:

            printf("Invalid choice. Please try again.\n");
            break;
        }
    }
}