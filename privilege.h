//
// Created by Ahmed Hossam on 2020-09-07.
//

#ifndef PRIVILEGE_H
#define PRIVILEGE_H

#include <stdlib.h>
#include <string.h>
#include "student_struct_configration.h"
#define MAX_RECORDS 10

#define safe_free(p) (safer_free((void**)(&p)))

typedef void (*displayIntFptr)(const int val);
typedef void (*displayStrFptr)(const char *string);
typedef void (*dataBaseFptr)(student_t *records[] ,char *adminPassword);


int ID_encryption(int ID);
/*
*  description: encrypt the ID of the student.
*  return: the encrypted ID.
*/

int ID_decryption(int ID);
/*
*  description: decrypt the ID of the student.
*  return: the decrypted ID of the student.
*/

void database_handle(dataBaseFptr Fptr);
/*
 *  description: the system uses this function to access static variables to store and load them.
 *  return: void.
 */

int check_user_ID_password(int ID, char *password);
/*
 *  description: check if the entered ID and password are correct.
 *  return: 1 if correct, 0 if wrong.
 */

void set_admin_password(void);
/*
 *  description: set the first password for admin.
 *  return: void.
 */

int check_admin_password(char *adminPassword);
/*
 *  description: check if the entered password is correct or not.
 *  return: 1 if correct, 0 if wrong.
 */

void modify_admin_password(char *newAdminPassword);
/*
 *  description: modify the admin password.
 *  return: void.
 */

int add_new_record(char *name, char *password, int degree);
/*
 *  description: add new record.
 *  return: 1 if adding is done, 0 if adding is undone.
 */

int modify_student_name(int ID, char *name);
/*
 *  description: modify the name.
 *  return: 1 if modifying is done, 0 if modifying is undone.
 */

int modify_student_password(int ID, char *password);
/*
 *  description: modify the password.
 *  return: 1 if modifying is done, 0 if modifying is undone.
 */

int modify_student_degree(int ID, int degree);
/*
 *  description: modify the degree.
 *  return: 1 if modifying is done, 0 if modifying is undone.
 */

int traverse_record(int ID, displayIntFptr printInt, displayStrFptr printStr);
/*
 *  description: view info about record.
 *  return: 1 if id is exist, 0 if id doesn't exist.
 */

int remove_record(int ID);
/*
 *  description: remove the record.
 *  return: 1 if id is exist, 0 if id doesn't exist.
 */


#endif //PRIVILEGE_H
