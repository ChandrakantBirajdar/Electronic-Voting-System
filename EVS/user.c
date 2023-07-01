#include <stdio.h>
#include "header.h"




int getCurrentdate()
{   
    time_t currentTime = time(NULL);  // Get current time
    struct tm* localTime = localtime(&currentTime);  // Convert to local time

    int day = localTime->tm_mday;  // Get day of the month
    int month = localTime->tm_mon + 1;  // Get month (January is 0)
    int year = localTime->tm_year + 1900;  // Get year (since 1900)
    // printf("%02d/%02d/%04d\n", day, month, year);  // Print in dd/mm/yyyy format
    return year;
}

void viewRequestStatus(int currentUser)
{
    struct Request request;
    
    FILE *requeststatus = fopen("RequestStatus.csv","r");
    if (requeststatus == NULL)
    {
        perror("Error in file opening\n");
    }
    else
    {
        while(fread(&request,sizeof(request),1,requeststatus))
        {
            if(request.UserId == currentUser)
            {
                printf("\nYour Request Status for VoterId is %s ",request.status);
                printf("\n");
                fclose(requeststatus);
                break;
            }
        }
        fclose(requeststatus);
    }

}


void userRegistration()
{

    struct User newuser;
    int userId=0;
    FILE *getuserId = fopen("userid.txt","r+");
    
    fscanf(getuserId,"%d",&userId);
    newuser.UserId = ++userId;
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

        int year = getCurrentdate();
        newuser.age = year - newuser.year;
        printf("Age: %d ",newuser.age);

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
        strcpy(newuser.VoterId,"");
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
    struct Request Request;

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
                if(strcmp(newuser.VoterId,"")==0)
                {
                    FILE *userRequest = fopen("VoterIdRequest.csv","a");
                    request.UserId = UserId;
                    strcpy(request.status,"Pending");
                    fwrite(&request,sizeof(request),1,userRequest);
                    printf("Successfully Requested for VoterId");
                    fclose(userRequest);

                    FILE *requeststatus = fopen("RequestStatus.csv","a");
                    Request.UserId = UserId;
                    strcpy(Request.status,"Pending");
                    fwrite(&Request,sizeof(Request),1,requeststatus);
                    fclose(requeststatus);

                    flag=1;
                    break;
                }
                else{
                    printf("Your VoterId is already generated !!!");
                }
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

    while (choice != 7)
    {
        printf("\n---------------------------------------------------------|\n");
        printf("     \033[0;32m  Logged in Successfully\033[0;32m                      \033[0;36m|\033[0;37m\n");
        printf("---------------------------------------------------------|\n");
        printf("Please select an option:  ");
        printf("\n1.Request for VoterId ");
        printf("\n2.View Request Status");
        printf("\n3.View VoterId");
        printf("\n4.View Election Schedules");
        printf("\n5.Cast Vote");
        printf("\n6.View Election Result");
        printf("\n7.Logout");
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
            viewRequestStatus(currentUser);
            break;
        case 3:
            viewVoterId(currentUser);
            break;
        case 4:
            viewElection();
            break;
        case 5:
            castVotes();
            break;
        case 6:
            viewElectionResult();
            break;
        case 7:
            break;

        default:
            printf("\033[0;31m\n");
            printf(" Invalid Data Enterd Please Enter Valid choise !!! \n");
            printf("\033[0;37m\n");
        }
    }
}
