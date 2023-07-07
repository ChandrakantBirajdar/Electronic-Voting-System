#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "header/header.h"



// void userchoice()
// {
//    int choice = 0;

//     char ch[10];

//     while (choice != 3)
//     {
        

//         printf(COLOR_BLUE"|------------------------------------------------------------------------|\n"COLOR_RESET);
//         printf(COLOR_BLUE"|"COLOR_MAGENTA COLOR_BOLD"                        Please select an option:                                     "COLOR_RESET COLOR_BLUE "|\n"COLOR_RESET);
//         printf(COLOR_BLUE"|------------------------------------------------------------------------|\n"COLOR_RESET);
//         printf(COLOR_BOLD"|Please select an option:                                                | \n"COLOR_RESET);
//         printf("%-3s%-70s%-30s\n","|", " 1.  User Login","|");
//         printf("%-3s%-70s%-30s\n","|", " 2.  User Registration","|");
//         printf("%-3s%-70s%-30s\n","|", " 3.  Back to Menu","|");
//         printf("|------------------------------------------------------------------------|\n");
//         printf("\n");
//         printf(COLOR_BOLD" Enter The Choice:"COLOR_RESET);
//         scanf("%s", ch);
//         choice = atoi(ch);
//         switch (choice)
//         {
//         case 1:
//             userLogin();
            
//             break;
//         case 2:
//             userRegistration();
//             break;
//         case 3:
//             break;
//         default:
//             printf("\033[0;31m\n");
//             printf(" Invalid Data Enterd Please Enter Valid choise !!! \n");
//             printf("\033[0;37m\n");
//         }
//     }
// }

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
    printf("\n");
    printf( COLOR_BOLD"|--------------------------------------"COLOR_RESET COLOR_YELLOW"Welcome To Electonic Voting System" COLOR_RESET COLOR_BOLD "-------------------------------------------------|\n"COLOR_RESET);
    printf("\n");

    while (choice != 4)
    {
        
        printf(COLOR_BLUE"|------------------------------------------------------------------------|\n"COLOR_RESET);
        printf(COLOR_BLUE"|"COLOR_CYAN COLOR_BOLD"                        Electronic Voting Machine                       "COLOR_RESET COLOR_BLUE "|\n"COLOR_RESET);
        printf(COLOR_BLUE"|------------------------------------------------------------------------|\n"COLOR_RESET);
        printf(COLOR_BOLD"|Please select an option:                                                | \n"COLOR_RESET);
        printf("%-3s%-70s%-30s\n","|", " 1.  Administrator","|");
        printf("%-3s%-70s%-30s\n","|", " 2.  Electoral Officier","|");
        printf("%-3s%-70s%-30s\n","|", " 3.  User","|");
        printf("|   4. Exit                                                              |\n");
        printf("|------------------------------------------------------------------------|\n");
        printf("\n");
        printf(COLOR_BOLD" Enter The Choice:"COLOR_RESET);


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

// void userLogin()
// {
//     struct User newUser;
//     int UserId;
//     char password[20];

//     int present = 0;
//     printf("Enter UserId: ");
//     scanf("%d",&UserId);
//     printf("Enter Password: ");
//     scanf("%s",password);

//     FILE *user = fopen("UserDetails.csv","r");
//      if (user == NULL)
//     {
//         perror("Error in file opening\n");
//     }
//     else
//     {
//         while(fread(&newUser,sizeof(newUser),1,user))
//         {
//             if( newUser.UserId==UserId && strcmp(newUser.password,password)==0)
//             {
//                 present=1;
//                 userMenu(UserId);
//                 fclose(user);
//             }
//         }
        
//         if(present==0)
//         {
//             printf("Invalid Credentials OR Seems like you haven't registered to EVS  \n");
//             printf("To login to EVS  please register to EVS\n");
//             fclose(user);
//         }

//         fclose(user);

//     }
// }




// void userLogin()
// {
//     struct User newUser;
//     int UserId;
//     char password[20];

//     int present = 0;
//     printf("Enter UserId: ");
//     scanf("%d",&UserId);
//     printf("Enter Password: ");
//     scanf("%s",password);

//     FILE *user = fopen("UserDetails.csv","r");
//      if (user == NULL)
//     {
//         perror("Error in file opening\n");
//     }
//     else
//     {
//         while(fread(&newUser,sizeof(newUser),1,user))
//         {
//             if( newUser.UserId==UserId && strcmp(newUser.password,password)==0)
//             {
//                 present=1;
//                 userMenu(UserId);
//                 fclose(user);
//             }
//         }
        
//         if(present==0)
//         {
//             printf("Invalid Credentials OR Seems like you haven't registered to EVS  \n");
//             printf("To login to EVS  please register to EVS\n");
//             fclose(user);
//         }

//         fclose(user);

//     }
// }


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
                printf(COLOR_GREEN COLOR_BOLD"\nlogin Succussfull...\n"COLOR_RESET);
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
                printf(COLOR_GREEN COLOR_BOLD"\nlogin Succussfull...\n"COLOR_RESET);
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

        fclose(electordata);

    }
}