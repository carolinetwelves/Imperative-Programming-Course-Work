/*****************
    Student Name 	= Caroline Twelves
    Student Number	= 101301400
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <time.h>
#include <ctype.h>
#include "a2_nodes.h"
#include "a2_functions.h"

// Your solution goes here

/*
   Function that creates a new user and adds it to a sorted (ascending order) linked list at
   the proper sorted location. Return the head of the list.
*/
user_t *add_user(user_t *users, const char *username, const char *password)
{
    /*
        check user name doesnt already exist
        -> if it does error message and list remains unchanged
        user added to right position *after password*
        change to lowercase
    */

    // create new node
    user_t *new_user = (user_t *)malloc(sizeof(user_t));
    assert(new_user != NULL);

    // give the user properties
    strcpy(new_user->username, username);
    strcpy(new_user->password, password);
    new_user->next = NULL;
    new_user->friends = NULL;
    new_user->posts = NULL;

    if (users == NULL)
    {
        users = new_user;
    }

    // if its the first user alphabetically, put in first place
    else if (strcmp(username, users->username) < 0)
    {
        new_user->next = users;
        users = new_user;
    }

    else
    {
        user_t *curr = users;
        // loop through the list until alphabetical order
        while (curr->next != NULL && strcmp(curr->username, username) < 0)
        {
            curr = curr->next;
        }

        if (curr == NULL)
        {
            curr = new_user;
            return users;
        }

        // insert node
        new_user->next = curr->next;
        curr->next = new_user;
    }

    return users;
}

/*
   Function that searches if the user is available in the database
   Return a pointer to the user if found and NULL if not found.
*/
user_t *find_user(user_t *users, const char *username)
{
    assert(users != NULL);
    user_t *curr = users;

    // go through all users (breaking if at end of them)
    while (curr != NULL)
    {
        // when user found return user
        if (strcmp(username, curr->username) == 0)
        {
            return curr;
        }

        // cycle through linked list
        curr = curr->next;
    }

    return NULL;
}

/*
   Function that creates a new friend's node.
   Return the newly created node.
*/
friend_t *create_friend(user_t *users, const char *username)
{
    // make new friend
    friend_t *new_friend = (friend_t *)malloc(sizeof(friend_t));
    user_t *find_friend = find_user(users, username);
    assert(new_friend != NULL);
    new_friend->next = NULL;
    new_friend->posts = &find_friend->posts;

    // copy username passed into friends username variable
    strcpy(new_friend->username, username);

    return new_friend;
}

/*
   Function that links a friend to a user. The friend's name should be added into
   a sorted (ascending order) linked list.
*/
void add_friend(user_t *user, const char *friend)
{
    assert(user != NULL);
    friend_t *new_friend = create_friend(user, friend);

    // if user has no friends yet put at start of linked list
    if (user->friends == NULL)
    {
        user->friends = new_friend;
    }

    // new friend is first alphabetically -> insert into linked list
    else if (strcmp(friend, user->friends->username) < 0)
    {
        new_friend->next = user->friends;
        user->friends = new_friend;
    }

    else
    {
        friend_t *curr = user->friends;

        // loop through linked list until find alphabetical placement of new friend or end of list
        while (curr->next != NULL && strcmp(friend, curr->next->username) > 0)
        {
            curr = curr->next;
        }

        // if friend was last alphabetically place in last pos
        if (curr->next == NULL)
        {
            curr->next = new_friend;
            return;
        }

        // insert node
        new_friend->next = curr->next;
        curr->next = new_friend;
    }
}

/*
   Function that removes a friend from a user's friend list.
   Return true of the friend was deleted and false otherwise.
*/
_Bool delete_friend(user_t *user, char *friend_name)
{
    assert(user != NULL);

    friend_t *curr = user->friends;
    friend_t *previous;

    // if the friend is first in linked list, delete node
    if (strcmp(curr->username, friend_name) == 0)
    {
        user->friends = curr->next;
        free(curr);
        return true;
    }

    // loop through list of friends until friend is found
    while (strcmp(curr->username, friend_name) != 0)
    {
        // condition to break if end of linked list is reached: return false
        if (curr == NULL)
        {
            return false;
        }
        previous = curr;
        curr = curr->next;
    }

    // repoint pointers and free deleted node
    previous->next = curr->next;
    free(curr);
    return true;
}

user_t *find_friend(user_t *users, user_t *user, char *friend_name)
{
    assert(user != NULL);

    friend_t *curr = user->friends;

    // loop through list of friends until friend is found
    while (strcmp(user->username, friend_name) != 0)
    {
        // condition to break if end of linked list is reached: return false
        if (curr == NULL)
        {
            return NULL;
        }
        curr = curr->next;
    }

    return find_user(users, friend_name);
}

/*
   Function that creates a new user's post.
   Return the newly created post.
*/
post_t *create_post(const char *text)
{
    // create post and make sure it was done right
    post_t *new_post = (post_t *)malloc(sizeof(post_t));
    assert(new_post != NULL);

    // initialize variables of post
    new_post->next = NULL;
    strcpy(new_post->content, text);

    return new_post;
}

/*
   Function that adds a post to a user's timeline following a stack.
*/
void add_post(user_t *user, const char *text)
{
    assert(user != NULL);
    post_t *new_post = create_post(text);

    // add post to start of post list (stack method)
    new_post->next = user->posts;
    user->posts = new_post;

    return;
}

/*
   Function that removes a post from a user's list of posts.
   Return true if the post was deleted and false otherwise.
*/
_Bool delete_post(user_t *user)
{
    assert(user != NULL);

    // if there are no posts to delete, retrun false
    if (user->posts == NULL)
    {
        return false;
    }

    post_t *remove = user->posts;

    // remove first (last) post in stack and free it
    user->posts = remove->next;
    free(remove);
    return true;
}

/*
   Function that  displays a specific user's posts (All posts)
*/
void display_all_user_posts(user_t *user)
{
    assert(user != NULL);

    post_t *curr = user->posts;
    int counter = 1;

    // print out username
    printf("-----------------------------------------------------------------------\n"
           "\t\t\t%s's posts\n-----------------------------------------------------------------------\n",
           user->username);

    // print all posts
    while (curr != NULL)
    {
        printf("%d. %s\n\n", counter, curr->content);

        curr = curr->next;
        counter++;
    }

    return;
}

/*
   Function that displays a specific user's friends (All friends)
*/
void display_user_friends(user_t *user)
{
    assert(user != NULL);

    friend_t *curr = user->friends;
    int counter = 1;

    // loop through all user friends and display each one
    while (curr != NULL)
    {
        // display friend place in list and name
        printf("%d- %s\n", counter, curr->username);

        counter++;
        curr = curr->next;
    }

    return;
}

/*
   Function that displays "number" of posts for a given user.
   After displaying "number" posts, it prompts if you want to display
   more posts.
   If there are no more post or the user types “n” or “N”, the function returns.
*/
void display_posts_by_n(user_t *users, int number)
{
    assert(users != NULL);
    post_t *curr = users->posts;

    // initialize & declare variables
    _Bool display_more = true;
    char more_posts;
    int post_num = 1;

    // display users name
    printf("-----------------------------------------------------------------------\n"
           "\t\t\t%s's posts\n-----------------------------------------------------------------------\n",
           users->username);

    // loop until condition breaks (is false)
    while (display_more)
    {
        // print all posts
        for (int i = 1; i <= number; i++)
        {
            // display post and post number
            printf("%d. %s\n\n", post_num, curr->content);

            // if at end of posts, return
            if (curr->next == NULL)
            {
                return;
            }

            post_num++;
            curr = curr->next;
        }

        // get user input if they want to display more posts
        printf("Would you like to display more posts by %s? (y/n): ", users->username);
        scanf(" %c", &more_posts);

        // if they don't, break from loop
        if (more_posts == 'n' || more_posts == 'N')
        {
            display_more = false;
        }
    }

    return;
}

/*
   Function that free all users from the database before quitting the application.
*/
void teardown(user_t *users)
{
    assert(users != NULL);

    user_t *pop_u;
    friend_t *pop_f;
    post_t *pop_p;

    // go through complete user list
    while (users != NULL)
    {
        // free all users friends
        while (users->friends != NULL)
        {
            pop_f = users->friends;
            users->friends = pop_f->next;
            free(pop_f);
        }

        // free all users posts
        while (users->posts != NULL)
        {
            pop_p = users->posts;
            users->posts = pop_p->next;
            free(pop_p);
        }

        // check that is not last user (cause condition needs to check against)
        if (users->next != NULL)
        {
            pop_u = users;
            users = pop_u->next;
            free(pop_u);
        }
        else
        {
            break;
        }
    }

    // free last user and return
    free(users);
    return;
}

/*
   Function that prints the main menu with a list of options for the user to choose from
*/
void print_main_menu()
{
    printf(
        "\n\n***********************************************\n"
        "\t\t MAIN MENU:\n"
        "***********************************************\n"
        "1. Register a new user\n"
        "2. Login with existing user's information\n"
        "3. Exit\n\n");
}

/*
   Function that prints the user menu with a list of options for the user to choose from
*/
void print_user_menu(const char *username)
{
    printf("***********************************************\n"
           "\t\tWelcome %s\n"
           "***********************************************\n"
           "1. Manage profile (change password)\n"
           "2. Manage posts (add/remove)\n"
           "3. Manage friends (add/remove)\n"
           "4. Display a friends's posts\n"
           "5. Exit\n\n",
           username);
}

/*
   Function that converts a string to lowercase
*/
void convert_to_lowercase(char *word)
{
    int len = strlen(word);
    char *walker = word;

    // walk through each char and convert to lowercase
    for (int i = 0; i < len; i++)
    {
        *walker = tolower(*walker);
        walker++;
    }
}

/*
   ******** DONT MODIFY THIS FUNCTION ********
   Function that reads users from the text file.
   IMPORTANT: This function shouldn't be modified and used as is
   ******** DONT MODIFY THIS FUNCTION ********
*/
user_t *read_CSV_and_create_users(FILE *file, int num_users)
{
    srand(time(NULL));
    user_t *users = NULL;
    char buffer[500];
    fgets(buffer, sizeof(buffer), file); // Read and discard the header line
    int count = 0;
    for (int i = 0; i < num_users; i++)
    {
        fgets(buffer, sizeof(buffer), file);
        buffer[strcspn(buffer, "\r\n")] = 0; // Remove newline characters

        char *token = strtok(buffer, ",");
        char *token2 = strtok(NULL, ",");
        users = add_user(users, token, token2);
        char *username = token;

        token = strtok(NULL, ",");

        user_t *current_user = users;
        for (; current_user != NULL && strcmp(current_user->username, username) != 0; current_user = current_user->next)
            ;

        while (token != NULL && strcmp(token, ",") != 0 && count < 3)
        {
            if (strcmp(token, " ") != 0)
            {
                add_friend(current_user, token);
            }
            token = strtok(NULL, ",");
            count++;
        }
        count = 0;

        // token = strtok(NULL, ",");
        while (token != NULL && strcmp(token, ",") != 0)
        {
            add_post(current_user, token);
            token = strtok(NULL, ",");
        }
    }
    return users;
}
