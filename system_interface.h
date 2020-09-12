//
// Created by Ahmed Hossam on 2020-09-07.
//

#ifndef SYSTEM_H
#define SYSTEM_H

#include <stdio.h>
#include <stdlib.h>
#include "privilege.h"

#define ADMIN_MODE 1
#define USER_MODE 2


#define MAX_LENGTH 50

void system_init(void);
/*
 *  description: initialize the whole system and set the default admin password.
 *  return: void.
 */

void system_run(void);
/*
 *  description: begin the system and choose the mode.
 *  return: void.
 */

void admin_mode(void);
/*
 *  description: begin the admin mode and choose the function.
 *  return: void.
 */

void admin_login(char *adminPassword);
/*
 *  description: check if admin entered a correct password.
 *  return: void.
 */

void admin_menu(void);
/*
 *  description: print the functionality of the admin.
 *  return: void.
 */

void admin_action(void);
/*
 *  description: select and invoke the functionality you choose.
 *  return: void.
 */





void user_mode(void);
/*
 *  description: begin the user mode and choose the function.
 *  return: void.
 */

void user_login(int *ID, char *userPassword);
/*
 *  description: check if user entered a correct ID and password.
 *  return: void.
 */

void user_menu(void);
/*
 *  description: print the functionality of the user.
 *  return: void.
 */

void user_action(int ID);
/*
 *  description: select and invoke the functionality you choose.
 *  return: void.
 */

#endif //RECORDS_SYSTEM_H
