//
// Created by Ahmed Hossam on 2020-09-07.
//

#include "privilege.h"

static student_t *records[MAX_RECORDS];
static char *adminCurrentPassword;
static void safer_free(void **pp);
static int get_available_index(void);
static int availableIndex = 0;


int ID_encryption(int ID)
{
    records[ID]->ID = ID + 100; //(ID+1) * 152 + 356;    //any magic numbers you can handle to encrypt the ID.
    return records[ID]->ID;
}

int ID_decryption(int ID)
{
    int originalID = ID - 100; //((ID - 356) / 152) - 1;
    return originalID;
}

static int get_available_index(void)
{
    int availabilityFlag = 0, i;
    for (i = 0; i < MAX_RECORDS && availabilityFlag == 0; ++i) {
        if(records[i] == NULL){
            availabilityFlag = 1;
            availableIndex = i;
        }
        else{
            availabilityFlag = 0;
        }
    }
    return availabilityFlag;
}

int check_user_ID_password(int ID, char *password)
{
    int returnFlag = 0;
    int originalID = ID_decryption(ID);
    //1st check if the the id in the bounders .. 2nd check if the user already exist and initialized
    if((originalID >= 0 && originalID <= MAX_RECORDS) && records[originalID] != NULL ) {
        //check if the id and password is matched
        if (records[originalID]->ID == ID && strcmp(records[originalID]->password, password) == 0) {
            returnFlag = 1;
        } else {
            returnFlag = 0;
        }
    }
    return returnFlag;
}

void set_admin_password(void)
{
    adminCurrentPassword = (char*)malloc(strlen("0000")+1);
    strcpy(adminCurrentPassword, "0000");
}

int check_admin_password(char *adminPassword)
{
    int returnFlag;
    if(strcmp(adminCurrentPassword,adminPassword) == 0)
    {
        returnFlag = 1;
    }
    else
    {
        returnFlag = 0;
    }
    return returnFlag;
}

void modify_admin_password(char *newAdminPassword)
{
    adminCurrentPassword = realloc(adminCurrentPassword, strlen(newAdminPassword)+1);
    strcpy(adminCurrentPassword, newAdminPassword);
}

int add_new_record(char *name, char *password, int degree)
{
    int addFlag, ID;
    if(get_available_index()){
        //you must allocate first to let ID_encryption access an exist user
        records[availableIndex] = (student_t*)malloc(sizeof(student_t));

        ID = ID_encryption(availableIndex);

        records[availableIndex]->name = (char*)malloc(strlen(name) + 1);
        strcpy(records[availableIndex]->name, name);

        records[availableIndex]->password = (char*)malloc(strlen(password) + 1);
        strcpy(records[availableIndex]->password, password);

        records[availableIndex]->ID = ID;

        records[availableIndex]->degree = degree;

        addFlag = 1;
    }
    else{
        addFlag = 0;
    }
    return addFlag;
}

int modify_student_name(int ID, char *name)
{
    int returnFlag;
    int originalID = ID_decryption(ID);
    //1st check if the the id in the bounders .. 2nd check if the user already exist and initialized
    if((originalID >= 0 && originalID < MAX_RECORDS) && records[originalID] != NULL ) {
        records[originalID]->name = realloc(records[originalID]->name, strlen(name) + 1);
        strcpy(records[originalID]->name, name);
        returnFlag = 1;
    }
    else
    {
        returnFlag = 0;
    }
    return returnFlag;
}

int modify_student_password(int ID, char *password)
{
    int returnFlag;
    int originalID = ID_decryption(ID);
    //1st check if the the id in the bounders .. 2nd check if the user already exist and initialized
    if((originalID >= 0 && originalID < MAX_RECORDS) && records[originalID] != NULL ) {
        records[originalID]->password = realloc(records[originalID]->password, strlen(password) + 1);
        strcpy(records[originalID]->password, password);
        returnFlag = 1;
    }
    else
    {
        returnFlag = 0;
    }
    return returnFlag;
}

int modify_student_degree(int ID, int degree)
{
    int returnFlag;
    int originalID = ID_decryption(ID);
    //1st check if the the id in the bounders .. 2nd check if the user already exist and initialized
    if((originalID >= 0 && originalID <= MAX_RECORDS) && records[originalID] != NULL ) {
        records[originalID]->degree = degree;
        returnFlag = 1;
    }
    else
    {
        returnFlag = 0;
    }
    return returnFlag;
}

int traverse_record(int ID, displayIntFptr printInt, displayStrFptr printStr)
{
    int returnFlag;
    int originalID = ID_decryption(ID);
    //1st check if the the id in the bounders .. 2nd check if the user already exist and initialized
    if((originalID >= 0 && originalID < MAX_RECORDS) && records[originalID] != NULL ) {
        (*printStr)(records[originalID]->name);
        (*printStr)(records[originalID]->password);
        (*printInt)(records[originalID]->degree);
        returnFlag = 1;
    }
    else
    {
        returnFlag = 0;
    }
    return returnFlag;
}

int remove_record(int ID)
{
    int returnFlag;
    int originalID = ID_decryption(ID);
    //1st check if the the id in the bounders .. 2nd check if the user already exist and initialized
    if((originalID >= 0 && originalID < MAX_RECORDS) && records[originalID] != NULL ) {
        safe_free(records[originalID]->name);
        safe_free(records[originalID]->password);
        safe_free(records[originalID]);
        returnFlag = 1;
    }
    else
    {
        returnFlag = 0;
    }
    return returnFlag;
}

static void safer_free(void **pp)
{
    if (pp != NULL && *pp != NULL)
    {
        free(*pp);
        *pp = NULL;
    }
}