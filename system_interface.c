//
// Created by Ahmed Hossam on 2020-09-07.
//

#include "system_interface.h"

static void printf_str(const char *str);
static void printf_int(const int intger);

static int systemMode;
static int adminFunction;
static int userFunction;

void system_init(void){
    set_admin_password();
    printf("welcome to admin record system\n");
}

void system_run(void){
    printf("enter the mode you need\n");
    printf("1-admin mode\n");
    printf("2-user mode\n");

    scanf("%d", &systemMode);

    while (systemMode != ADMIN_MODE && systemMode != USER_MODE){
        printf("you entered a wrong number, try again\n");
        scanf("%d", &systemMode);
    }
    switch (systemMode) {
        case ADMIN_MODE:
            admin_mode();
            break;
        case USER_MODE:
            user_mode();
            break;
        default:
            break;
    }
}

void admin_mode(void){
    char adminPassword[MAX_LENGTH];

    printf("you entered the admin mode\n");
    printf("enter admin password\n");

    fflush(stdin);
    gets(adminPassword);
    admin_login(adminPassword);

    admin_menu();
    admin_action();
}

void admin_login(char *adminPassword){
    while (!check_admin_password(adminPassword)){
        printf("you entered a wrong password\n");
        printf("enter it again\n");
        fflush(stdin);
        gets(adminPassword);
    }
}

void admin_menu(void){
    printf("enter the number of operation you need\n");
    printf("1-Change admin password.\n");
    printf("2-Add new student.\n");
    printf("3-Edit student name.\n");
    printf("4-Edit student password.\n");
    printf("5-Edit student degree.\n");
    printf("6-View student info.\n");
    printf("7-Remove student.\n");
    printf("8-Return to main menu\n");
}

void admin_action(void){
    char adminPassword[MAX_LENGTH];
    char studentName[MAX_LENGTH];
    char studentPassword[MAX_LENGTH];
    int studentDegree;
    int studentID;

    scanf("%d", &adminFunction);
    while (!(adminFunction >= 1 && adminFunction <= 8)){
        printf("you entered invalid number, enter it again\n");
        scanf("%d", &adminFunction);
    }
    switch (adminFunction) {
        case 1:
            printf("enter the new password\n");
            fflush(stdin);
            scanf("%s", adminPassword);
            modify_admin_password(adminPassword);
            printf("password changed successfully\n");
            break;
        case 2:
            printf("enter student name\n");
            fflush(stdin);
            gets(studentName);
            printf("enter student password\n");
            fflush(stdin);
            gets(studentPassword);
            printf("enter student degree\n");
            scanf("%d", &studentDegree);
            if (add_new_record(studentName, studentPassword, studentDegree)){
                printf("student is added successfully\n");
            }
            else{
                printf("there is no capacity for this student\n");
            }
            break;
        case 3:
            printf("enter student name\n");
            fflush(stdin);
            gets(studentName);
            printf("enter student ID\n");
            scanf("%d", &studentID);
            if (modify_student_name(studentID, studentName)){
                printf("name has been changed successfully\n");
            }
            else{
                printf("you entered invalid ID\n");
            }
            break;
        case 4:
            printf("enter student password\n");
            fflush(stdin);
            gets(studentPassword);
            printf("enter student ID\n");
            scanf("%d", &studentID);
            if (modify_student_password(studentID, studentPassword)){
                printf("password has been changed successfully\n");
            }
            else{
                printf("you entered invalid ID\n");
            }
            break;
        case 5:
            printf("enter student degree\n");
            scanf("%d", &studentDegree);
            printf("enter student ID\n");
            scanf("%d", &studentID);
            if (modify_student_degree(studentID, studentDegree)){
                printf("degree has been changed successfully\n");
            }
            else{
                printf("you entered invalid ID\n");
            }
            break;
        case 6:
            printf("enter student ID\n");
            scanf("%d", &studentID);
            if(!traverse_record(studentID, printf_int, printf_str)){
                printf("you entered invalid ID\n");
            }
            break;
        case 7:
            printf("enter student ID\n");
            scanf("%d", &studentID);
            if (remove_record(studentID)){
                printf("student removed successfully\n");
            }
            else{
                printf("you entered invalid ID\n");
            }
            break;
        case 8:
            system_run();
            break;
        default:
            break;
    }
    admin_menu();
    admin_action();
}


void user_mode(void){
    int userID;
    char userPassword[MAX_LENGTH];

    printf("you entered the user mode\n");
    printf("enter your ID\n");
    scanf("%d", &userID);

    printf("enter your password\n");
    fflush(stdin);
    gets(userPassword);

    user_login(&userID, userPassword);

    user_menu();
    user_action(userID);
}

void user_login(int *ID, char *userPassword){
    while (!check_user_ID_password(*ID, userPassword)){
        printf("user and password didn't matched\n");
        printf("enter ID again\n");
        scanf("%d", ID);
        printf("enter password again\n");
        fflush(stdin);
        gets(userPassword);
    }
}

void user_menu(void){
    printf("Enter the number of operation you need:\n");
    printf("1-View your info.\n");
    printf("2-Change your password.\n");
    printf("3-Return to main menu.\n");
}

void user_action(int ID){
    char studentPassword[MAX_LENGTH];

    scanf("%d", &userFunction);
    while (!(userFunction >= 1 && userFunction <= 3)){
        printf("you entered invalid number, enter it again\n");
        scanf("%d", &userFunction);
    }
    switch (userFunction) {
        case 1:
            traverse_record(ID, printf_int, printf_str);
            break;
        case 2:
            printf("enter your new password");
            fflush(stdin);
            gets(studentPassword);
            modify_student_password(ID, studentPassword);
            break;
        case 3:
            system_run();
            break;
        default:
            break;
    }
    user_menu();
    user_action(ID);
}

static void printf_str(const char *str){
    printf("%s\n",str);
}
static void printf_int(const int intger){
    printf("%d\n",intger);
}