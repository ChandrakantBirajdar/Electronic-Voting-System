#include <stdio.h>
#include "header.h"


void addElection()
{
	struct Election  e;
	FILE *electionfile;

	printf("\n--------------------Add Election Details---------------------");
	printf("\nEnter Name:");
	scanf(" %[^\n]s",e.name);
	printf("\nEnter ElectionDate:");
	scanf(" %[^\n]s",e.date);
	strcat(e.time,"8.00am to 5.00pm");
	printf("\nEnter District:");
	scanf("  %[^\n]s",e.district);
	printf("\nEnter Constituency:");
	scanf(" %[^\n]s",e.constituency);

	electionfile=fopen("election.csv","a+");
	if(electionfile==NULL)
	{
		printf("Cant open election.csv file");
	}	

	fwrite(&e,sizeof(e),1,electionfile);
	
//	fprintf(electionfile,"%s   %s   %s   %s   %s\n",e.name,e.date,e.time,e.district,e.constituency);
	fclose(electionfile);
}


void viewElection()
{
	struct Election  e;
	FILE *electionfile;
	electionfile=fopen("election.csv","r");
	
	if(electionfile==NULL)
	{
		printf("Cant open election.csv file");
	}
	printf("\n=======================Election Details======================\n");
	printf("\nName\tElectionDate\tVoting Time\t   District\tConstituency\n");
	while(fread(&e,sizeof(e),1,electionfile)==1)
	{
//		fread(&e,sizeof(e),1,electionfile);
		printf("%s\t%s\t%s  %s\t%s\n",e.name,e.date,e.time,e.district,e.constituency);
	}
	fclose(electionfile);
}


void addCandidate()
{
	struct Candidate c;
    FILE *candidatefile;

    int candidateId=0;
    FILE *candidateIdfile = fopen("candidateId.txt","r+");
    
    fscanf(candidateIdfile,"%d",&candidateId);
    c.candidateId = ++candidateId;
    fclose(candidateIdfile);

    candidateIdfile = fopen("userid.txt","w");
    // rewind(candidateIdfile);
    fprintf(candidateIdfile,"%d",candidateId);
    fclose(candidateIdfile);

	printf("\n----------------------Add Candidate Details---------------------\n");
    
	printf("\nCandidate ID: %d",c.candidateId);
	// scanf("%d",&c. candidateId);
	printf("\nEnter Candidate Name:");
	scanf(" %[^\n]s",c.name);
	printf("\nEnter Date of Birth:");
	scanf(" %[^\n]s",c.dob);
	printf("\nEnter Election Name:");
	scanf(" %[^\n]s",c.electname);
	printf("\nEnter Party Name:");
	scanf(" %[^\n]s",c.partyname);
	printf("\nEnter District:");
	scanf(" %[^\n]s",c.district);
	printf("\nEnter Constituency:");
	scanf(" %[^\n]s",c.constituency);
	printf("\nEnter Address:");
	scanf(" %[^\n]s",c.address);
	printf("\nEnter Phone No.:");
	scanf(" %[^\n]s",c.phone);
	printf("\nEnter Email ID:");
	scanf(" %[^\n]s",c.email);

	candidatefile = fopen("candidate.csv","a");
	if(candidatefile==NULL)
	{
		printf("Cant open cadidate.csv file");
	}
	
	fwrite(&c,sizeof(c),1,candidatefile);

//	fprintf(candidatefile,"%d   %s   %s    %s    %s    %s    %s    %s    %s    %s\n",c. candidateId,c.name,c.dob,c.electname,c.partyname,c.district,c.constituency,c.address,c.phone,c.email);	
	fclose(candidatefile);
}


void viewCandidate()
{
        struct Candidate candidate;
        FILE *candidatefile;
        candidatefile=fopen("candidate.csv","r");

        if(candidatefile==NULL)
        {
                printf("Cant open candidate.csv file");
        }
        printf("\n=======================Candidate Details======================\n");
        printf("\nCandidate ID  Candidate Name  Date of Birth  Election Name  Party Name  District    Constituency  Address    Phone No    Email ID");
        while(fread(&candidate,sizeof(candidate),1,candidatefile)==1)
	{
        	printf("\n%d %15s %20s %9s %15s %13s %12s %12s %12s %13s",candidate. candidateId,candidate.name,candidate.dob,candidate.electname,candidate.partyname,candidate.district,candidate.constituency,candidate.address,candidate.phone,candidate.email);
        }
	fclose(candidatefile);
}

void addParty()
{
	struct Party p;
	FILE *partyfile;

	printf("\n---------------------Add Party Details--------------------");
	printf("\nEnter Party Name:");
	scanf(" %[^\n]s",p.name);
	printf("\nEnter Leader:");
	scanf(" %[^\n]s",p.leader);
	printf("\nEnter Symbol:");
	scanf(" %[^\n]s",p.symbol);

	partyfile=fopen("party.csv","a");
	if(partyfile==NULL)
	{
		printf("Cant open partyfile.csv file");
	}

	fwrite(&p,sizeof(p),1,partyfile);
//	fprintf(partyfile,"%s   %s   %s\n",p.name,p.leader,p.symbol);
	fclose(partyfile);
}

void viewParty()
{
	struct Party p;
	FILE *partyfile;
	partyfile=fopen("party.csv","r");
	
	if(partyfile==NULL)
	{
		printf("Cant open election.csv file");
	}
	printf("\n=======================Party Details======================\n");
	
	printf("\nParty Name      Party Leader    Party Symbol\n");
	while(fread(&p,sizeof(p),1,partyfile)==1)
	{
		printf("%s%20s%15s\n",p.name,p.leader,p.symbol);
	}
	fclose(partyfile);
}


void viewRequest()
{

    struct Request request;
    struct Request Request;
    char choice[10];
    
   
    FILE *requeststatus = fopen("RequestStatus.csv", "r+");
    FILE *requestfile = fopen("VoterIdRequest.csv", "r");

    if (requestfile == NULL)
    {
        perror("Error in file opening\n");
    }
    else
    {

        while (fread(&request, sizeof(request), 1, requestfile))
        {

            printf("User with UseerId %d has requested for VoterId ", request.UserId);
            printf("Do you want to approve the request? \n");
            printf("Enter your choice [y/n]: ");

            scanf("%s", choice);
            if (strcmp(choice, "y") == 0 || strcmp(choice, "Y") == 0)
            {
                

                while (fread(&Request, sizeof(Request), 1, requeststatus))
                {
                    if (request.UserId == Request.UserId)
                    {
                        strcpy(Request.status, "Approved");
                        fseek(requeststatus, -sizeof(Request), SEEK_CUR);
                        fwrite(&Request, sizeof(Request), 1, requeststatus);
                        break;
                    }
                }

                FILE *approvedUser = fopen("ApprovedUserFile.csv", "a");
                strcpy(request.status, "Approved");

                printf("Request Approved successfully \n");
                fwrite(&request, sizeof(request), 1, approvedUser);
                fclose(approvedUser);
            }
            if (strcmp(choice, "n") == 0 || strcmp(choice, "N") == 0)
            {
                int present=0;
                while (fread(&Request, sizeof(Request), 1, requeststatus))
                {
                    if (request.UserId == Request.UserId)
                    {
                        strcpy(request.status, "Rejected");
                        fseek(requeststatus, -sizeof(Request), SEEK_CUR);
                        fwrite(&Request, sizeof(Request), 1, requeststatus);
                        present =1;
                        printf("Request denied successfully \n");
                        break;
                    }
                }
                if(present==0)
                {
                    printf("xyz \n");
                }
                
            }
        }

        fclose(requestfile);
        requestfile = fopen("VoterIdRequest.csv", "w");
        fclose(requestfile);
    }
}

void adminMenu()
{
    int choice = 0;

    char ch[10];

    while (choice != 8)
    {
        printf("\n---------------------------------------------------------|\n");
        printf("     \033[0;32m  Admin Menu\033[0;32m                      \033[0;36m|\033[0;37m\n");
        printf("---------------------------------------------------------|\n");
        printf("Please select an option:  ");
        printf("\nPress 1 to View VoterId Request from User");
        printf("\nPress 2 to Add Candidate Details");
        printf("\nPress 3 to View Candidate Details");
        printf("\nPress 4 to Add Party Details");
        printf("\nPress 5 to View Party Details");
        printf("\nPress 6 to Add Election Details");
        printf("\nPress 7 to View Election Details");
        printf("\nPress 8.Exit");
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
            addCandidate();
            break;
        case 3:
            viewCandidate();
            break;
        case 4:
            addParty();
            break;
        case 5:
            viewParty();
            break;
        case 6:
            addElection();
            break;
        case 7:
            viewElection();
            break;
        case 8:
            break;

        default:
            printf("\033[0;31m\n");
            printf(" Invalid Choice !!!  Please Enter Valid choise !!! \n");
            printf("\033[0;37m\n");
        }
    }
}