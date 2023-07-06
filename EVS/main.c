#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "header.h"



void userchoice()
{
   int choice = 0;

    char ch[10];

    while (choice != 3)
    {
        printf("\n---------------------------------------------------------|\n");
        printf("     \033[0;32m   Please select an option: \033[0;32m                      \033[0;36m|\033[0;37m\n");
        printf("---------------------------------------------------------|\n");
        printf("\n1.  User Login ");
        printf("\n2.  User Registration ");
        printf("\n3.  Back to Menu ");
        printf("\n");
        printf(" Enter The Choice: ");

        scanf("%s", ch);
        choice = atoi(ch);
        switch (choice)
        {
        case 1:
            userLogin();
            //getAllDetails();
            break;
        case 2:
            userRegistration();
            break;
        case 3:
            break;
        default:
            printf("\033[0;31m\n");
            printf(" Invalid Data Enterd Please Enter Valid choise !!! \n");
            printf("\033[0;37m\n");
        }
    }
}

void setUserId()
{
    int userid=0;

    FILE *setuserid = fopen("userid.txt","r+");
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


void setCandidateId()
{
    int candidateId=0;

    FILE *setcandidateid = fopen("candidateId.txt","r+");
    if(setcandidateid==NULL)
    {
        perror("File can't be open");
    }
    else
    {
        if(fscanf(setcandidateid,"%d",&candidateId)==EOF)
        {
            candidateId = 0;
            fprintf(setcandidateid,"%d",candidateId);
            printf("CandidateId set to 0");
        }
        fclose(setcandidateid);
    }
    fclose(setcandidateid);
}
int main()
{
    setUserId();
    setCandidateId();

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
            adminLogin();
            break;
        case 2:
            ElectorOfficerLogin();
            break;
        case 3:
            userchoice();            
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
            printf("Invalid Credentials OR Seems like you haven't registered to EVS  \n");
            printf("To login to EVS  please register to EVS\n");
            fclose(user);
        }

        fclose(user);

    }
}


void adminLogin()
{
   
    int adminId;
    char password[20];

    int Admin_ID=0;
    char Admin_Password[20];

    int present = 0;
    printf("Enter AdminId: ");
    scanf("%d",&adminId);
    printf("Enter AdminPassword: ");
    scanf("%s",password);

    FILE *admindata = fopen("AdminData.csv","r+");
     if (admindata == NULL)
    {
        perror("Error in file opening\n");
    }
    else
    {
        while(fscanf(admindata,"%d %s",&Admin_ID,Admin_Password))
        {
            if( adminId==Admin_ID  && strcmp(password,Admin_Password)==0 )
            {
                present=1;
                adminMenu();
                fclose(admindata);
                break;
            }
            break;
        }
        
        if(present==0)
        {
            printf("Invalid Credentials OR Seems like you haven't registered to EVS  \n");
            printf("To login to EVS  please register to EVS\n");
            fclose(admindata);
        }

        fclose(admindata);

    }
}


void ElectorOfficerLogin()
{
   
    int ElectorId;
    char password[20];

    int Elector_ID=0;
    char Elector_Password[20];

    int present = 0;
    printf("Enter ElectorId: ");
    scanf("%d",&ElectorId);
    printf("Enter ElectorPassword: ");
    scanf("%s",password);

    FILE *electordata = fopen("ElectorData.csv","r+");
     if (electordata == NULL)
    {
        perror("Error in file opening\n");
    }
    else
    {
        while(fscanf(electordata,"%d %s",&Elector_ID,Elector_Password))
        {
            if( ElectorId==Elector_ID && strcmp(password,Elector_Password)==0 )
            {
                present=1;
                officerMenu();
                fclose(electordata);
                break;
            }
            break;
        }

        if(present==0)
        {
            printf("Invalid Credentials OR Seems like you haven't registered to EVS  \n");
            printf("To login to EVS  please register to EVS\n");
            fclose(electordata);
        }
//hello
        fclose(electordata);

    }
}