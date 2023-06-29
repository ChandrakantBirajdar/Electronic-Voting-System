#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "header.h"

void userLogin();
void setUserId();



void setUserId()
{
    int userid=0;

    
    FILE *setuserid = fopen("userid.txt","a+");
    if(setuserid==NULL)
    {
        perror("File can't be open");
    }
    else
    {
        if(fscanf(setuserid,"%d",&userid)==EOF)
        {
            userid = 0;
            fprintf(setuserid,"%d",userid);
            printf("Userid set to 0");
        }
        fclose(setuserid);
    }
    fclose(setuserid);
}
int main()
{
    setUserId();

    int choice = 0;

    char ch[10];

    while (choice != 4)
    {
        printf("\n---------------------------------------------------------|\n");
        printf("     \033[0;32m  Electronic Voting Machine\033[0;32m                      \033[0;36m|\033[0;37m\n");
        printf("---------------------------------------------------------|\n");
        printf("     Please select an option:  ");
        printf("\n1.  Administrator ");
        printf("\n2.  Electoral Officier ");
        printf("\n3.  User ");
        printf("\n4.  Exit");
        printf("\n");
        printf(" Enter The Choice: ");

        // scanf("%d", &choice1);

        scanf("%s", ch);
        choice = atoi(ch);
        switch (choice)
        {
        case 1:
            adminMenu();
            break;
        case 2:
            officerMenu();
            break;
        case 3:
            userLogin();            
            break;
        case 4:
            break;

        default:
            printf("\033[0;31m\n");
            printf(" Invalid Data Enterd Please Enter Valid choise !!! \n");
            printf("\033[0;37m\n");
        }
    }

    return 0;
}

void userLogin()
{
    struct User newUser;
    int UserId;
    char password[20];

    int present = 0;
    printf("Enter UserId: ");
    scanf("%d",&UserId);
    printf("Enter Password: ");
    scanf("%s",password);

    FILE *user = fopen("UserDetails.csv","r");
     if (user == NULL)
    {
        perror("Error in file opening\n");
    }
    else
    {
        while(fread(&newUser,sizeof(newUser),1,user))
        {
            if( newUser.UserId==UserId && strcmp(newUser.password,password)==0)
            {
                present=1;
                userMenu(UserId);
                fclose(user);
            }
        }
        
        if(present==0)
        {
            printf("Seems like you haven't registered to EVS \n");
            printf("To login to EVS  please register to EVS\n");
            userRegistration();
            fclose(user);
        }

        fclose(user);

    }
}