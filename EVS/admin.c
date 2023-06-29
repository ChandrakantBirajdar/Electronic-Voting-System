#include <stdio.h>
#include "header.h"

void viewRequest()
{
    
    struct Request request;
    char choice[10];
    
    FILE *requestfile = fopen("VoterIdRequest.csv","r");
    
    if (requestfile == NULL)
    {
        perror("Error in file opening\n");
    }
    else
    {
       
        while(fread(&request,sizeof(request),1,requestfile))
        {
           
            printf("User with UseerId %d has requested for VoterId ",request.UserId);
            printf("Do you want to approve the request? \n");
            printf("Enter your choice [y/n]: ");
            scanf("%s",choice);
            if(strcmp(choice,"y")==0 || strcmp(choice,"Y")==0)
            {
                FILE *approvedUser = fopen("ApprovedUserFile.csv","a");
                strcpy(request.status,"Approved");
                printf("Request Approved successfully \n");
                fwrite(&request,sizeof(request),1,approvedUser);
                fclose(approvedUser);
            }
            if(strcmp(choice,"n")==0 || strcmp(choice,"N")==0)
            {
                printf("Request denied successfully \n");
            }
        }

        fclose(requestfile);
        requestfile = fopen("VoterIdRequest.csv","w");
        fclose(requestfile);
    }
}



void adminMenu()
{
    int choice = 0;

    char ch[10];

    while (choice != 2)
    {
        printf("\n---------------------------------------------------------|\n");
        printf("     \033[0;32m  Admin Menu\033[0;32m                      \033[0;36m|\033[0;37m\n");
        printf("---------------------------------------------------------|\n");
        printf("Please select an option:  ");
        printf("\n1.view Request ");
        printf("\n2.Exit");
        printf("\n");
        printf(" Enter The Choice: ");

        // scanf("%d", &choice1);

        scanf("%s", ch);
        choice = atoi(ch);
        switch (choice)
        {
        case 1:
            viewRequest();
            break;
        case 2:
            break;

        default:
            printf("\033[0;31m\n");
            printf(" Invalid Choice !!!  Please Enter Valid choise !!! \n");
            printf("\033[0;37m\n");
        }
    }
}