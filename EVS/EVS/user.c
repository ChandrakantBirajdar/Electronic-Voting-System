#include <stdio.h>
#include "header.h"

void userRegistration()
{

    struct User newuser;
    int userId=0;
    FILE *getuserId = fopen("userid.txt","r+");
    
    fscanf(getuserId,"%d",&userId);
    newuser.UserId = ++userId;
    printf("userid afterincrementing %d ",newuser.UserId);
    fclose(getuserId);

    getuserId = fopen("userid.txt","w");
    rewind(getuserId);
    fprintf(getuserId,"%d",userId);
    fclose(getuserId);

    FILE *userDetails = fopen("UserDetails.csv", "a");
    if (userDetails == NULL)
    {
        perror("Error in file opening\n");
    }
    else
    {
        
        printf("Enter FirstName: ");
        scanf("%s", newuser.firstname);
        printf("Enter LastName: ");
        scanf("%s", newuser.lastname);
        printf("Enter DOB  in format   [dd/mm/yyyy]: ");
        scanf("%d/%d/%d", &newuser.day, &newuser.mon, &newuser.year) ;
        printf("Enter Age: ");
        scanf("%d", &newuser.age);
        if(newuser.age<18)
        {
            printf("You are not Eligible for Voting as your age is less than 18");
            goto label;
        }
        printf("Enter Gender: ");
        scanf("%s", newuser.gender);
        printf("Enter Passsword: ");
        scanf("%s", newuser.password);
        printf("Enter Address: ");
        scanf("%s", newuser.address);
        printf("Enter Phone Number: ");
        scanf("%d", &newuser.phoneno);
        printf("Enter District: ");
        scanf("%s", newuser.district);
        printf("Enter Constituency: ");
        scanf("%s", newuser.constituency);
        fwrite(&newuser, sizeof(newuser), 1, userDetails);
        printf("registration successfull ");
        printf("User id = %d ", newuser.UserId);
        label:
        fclose(userDetails);
        
    }
}
void requsetVoterId(int userId)
{
    int UserId = userId;
    int flag=0;
    struct User newuser;
    struct Request request;

    FILE *userDetails = fopen("UserDetails.csv", "r");
    if (userDetails == NULL)
    {
        perror("Error in file opening\n");
    }
    else
    {

        while(fread(&newuser,sizeof(newuser),1,userDetails))
        {
            if(newuser.UserId==UserId)
            {
               
                FILE *userRequest = fopen("VoterIdRequest.csv","a");
                request.UserId = UserId;
                strcpy(request.status,"");
                fwrite(&request,sizeof(request),1,userRequest);
                printf("Successfully Requested for VoterId");
                fclose(userRequest);
                flag=1;
                break;
            }
        }
        if(flag==0)
        {
            printf("please register to get VoterId\n");
        }
        fclose(userDetails);
    }

  
}
void viewVoterId(int userId)
{
    struct User newUser;
    FILE *user = fopen("UserDetails.csv","r");
    if (user == NULL)
    {
        perror("Error in file opening\n");
    }
    while (fread(&newUser,sizeof(newUser),1,user))
    {
        if(userId==newUser.UserId)
        {
            printf("\nYour VoterId is %s",newUser.VoterId);
            break;
        }
    }
    fclose(user);
    
}
void viewElectionSchedules()
{
}
void castVotes()
{
}
void viewElectionResult()
{
}

void userMenu(int userId)
{
    int choice = 0;
    int currentUser = userId;
    char ch[10];

    while (choice != 6)
    {
        printf("\n---------------------------------------------------------|\n");
        printf("     \033[0;32m  Logged in Successfully\033[0;32m                      \033[0;36m|\033[0;37m\n");
        printf("---------------------------------------------------------|\n");
        printf("Please select an option:  ");
        printf("\n1.Request for VoterId ");
        printf("\n2.View VoterId");
        printf("\n3.View Election Schedules");
        printf("\n4.Cast Vote");
        printf("\n5.View Election Result");
        printf("\n6.Exit");
        printf("\n");
        printf(" Enter The Choice: ");

        // scanf("%d", &choice1);

        scanf("%s", ch);
        choice = atoi(ch);
        switch (choice)
        {
       
        case 1:
            requsetVoterId(currentUser);
            break;
        case 2:
            viewVoterId(currentUser);
            break;
        case 3:
            viewElectionSchedules();
            break;
        case 4:
            castVotes();
            break;
        case 5:
            viewElectionResult();
            break;
        case 6:
            break;

        default:
            printf("\033[0;31m\n");
            printf(" Invalid Data Enterd Please Enter Valid choise !!! \n");
            printf("\033[0;37m\n");
        }
    }
}
