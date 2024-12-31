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
    user_t *user_head = read_CSV_and_create_users(csv_file, 50);

    fclose(csv_file);


    // intitializing and declaring variables
    _Bool exit = false;
    int user_choice = -1;

    while (!exit)
    {
        // welcome message and menu
        print_menu();

        // user input
        printf("Enter your choice: ");
        scanf("%d", &user_choice);

        // user input possibilities
        switch (user_choice)
        {
        // 1. Register a new user
        case 1:
        {
            const char name[50];
            const char pass[50];

            // get new user info
            printf("Enter a username: ");
            scanf("%s", name);
            printf("Enter an up to 15 characters password: ");
            scanf("%15s", pass);

            // add the user in alphabetical order to the users
            user_head = add_user(user_head, name, pass);

            printf("\n\n**** User Added! ****\n");

            break;
        }

        // update the users password
        case 2:
        {
            const char name[50];
            const char pass[50];

            // get username
            printf("Enter a username to update their password: ");
            scanf("%s", name);

            // make sure user exists and get user location
            user_t *update_user = find_user(user_head, name);

            // if user does not exist
            if (update_user == NULL)
            {
                printf("--------------------------------\n\t\t\tUser not found.\n--------------------------------\n\n");
                break;
            }

            // get current password
            printf("Enter the password: ");
            scanf("%s", pass);

            // check current password is right
            if (strcmp(pass, update_user->password) != 0)
            {
                printf("\nIncorrect passsword.\n");
                break;
            }

            // get new password and update
            printf("Enter a new password. up to 15 characters: ");
            scanf("%s", update_user->password);

            break;
        }

        // manages a users posts
        case 3:
        {
            const char name[50];
            const char post_text[250];
            int post_choice = -1;
            _Bool managing_posts = true;
            _Bool removed;

            // get username
            printf("Enter a username to manage their posts: ");
            scanf("%s", name);

            // get location of username
            user_t *update_user = find_user(user_head, name);

            // if username doesn't exist
            if (update_user == NULL)
            {
                printf("--------------------------------\n\t\t\tUser not found.\n--------------------------------\n\n");
                break;
            }

            while (managing_posts)
            {
                // print menu for managing posts
                printf("--------------------------------\n\t\t\tManaging %s's posts\n--------------------------------\n\n", name);
                if (update_user->posts == NULL)
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
                    add_post(user_head, post_text);

                    // display posts and post menu displayed
                    display_all_user_posts(user_head);
                    break;

                // remove post
                case 2:

                    removed = delete_post(user_head);

                    if (removed)
                    {
                        display_all_user_posts(user_head);
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

        // manage users friends
        case 4:
        {
            const char name[50];
            char friend_name[50];
            int friend_choice = -1;
            _Bool success;
            _Bool friends = true;

            // get username
            printf("Enter a username to update their friends: ");
            scanf("%s", name);

            // get location of username

            user_t *update_user = find_user(user_head, name);

            // if username doesn't exist
            if (update_user == NULL)
            {
                printf("--------------------------------\n\t\t\tUser not found.\n--------------------------------\n\n");
                break;
            }

            // print menu for managing posts
            printf("--------------------------------\n\t\t\tManaging %s's friends\n--------------------------------\n\n", name);

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

                    // add friend;
                    add_friend(update_user, friend_name);

                    printf("\nFriend added to the list.\n\n");
                    break;

                // delete friend
                case 2:
                    display_user_friends(update_user);

                    // get friends name
                    printf("Enter a new friend's name to delete: ");
                    scanf("%s", friend_name);

                    // printf("List of %s's friends: \n", update_user);
                    success = delete_friend(update_user, friend_name);

                    if (success)
                    {
                        printf("Updated list of %s's friends: \n", update_user);
                        display_user_friends(update_user);
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

        // Display all posts from a given user
        case 5:
        {
            const char name[50];

            // get username
            printf("Enter a username to display their posts: ");
            scanf("%s", name);

            // get location of username
            user_t *update_user = find_user(user_head, name);

            // if username doesn't exist
            if (update_user == NULL)
            {
                printf("--------------------------------\n\t\t\tUser not found.\n--------------------------------\n\n");
                break;
            }

            if (update_user->posts == NULL)
            {
                printf("%s has no friends to delete.\n\n", update_user->username);
                break;
            }

            display_posts_by_n(update_user, 3);

            break;
        }

        case 6:

            teardown(user_head);
            printf("Goodbye!! Have a nice day");
            exit = true;
            break;

        default:

            printf("Invalid choice. Please try again.\n");
            break;
        }
    }
}