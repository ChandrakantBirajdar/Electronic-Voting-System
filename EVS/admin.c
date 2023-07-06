#include <stdio.h>
#include "header.h"

void addElection()
{
	struct Election  e;
	char *d,*m,*y;
	int day,month,year;
	char tempdate[20]="";
	int cnt=0;

	printf("\n--------------------Add Election Details---------------------");
	checkElectionName:
    printf("\nEnter Election Name:");
	scanf(" %[^\n]s",e.name);
    for(int i = 0 ; e.name[i]!='\0';i++){
        if(!isalpha(e.name[i]))
        {
            printf("\nIncorrect Format for election name!!\n");
            goto checkElectionName;
        }
    }
    
    //
    while(1)
	{
		printf("\nEnter ElectionDate:");
		scanf(" %[^\n]s",e.date);
		strcpy(tempdate,e.date);
		if(strlen(tempdate)==8 || strlen(tempdate)==9 || strlen(tempdate)==10)
		{
			cnt=0;
			for(int i=0;tempdate[i]!='\0';i++)
			{
				if(tempdate[i]=='/')
					cnt++;
			}
			if(cnt==2)
			{
				d=strtok(tempdate,"/");
				m=strtok(NULL,"/");
				y=strtok(NULL,"/");
				day=atoi(d);
				month=atoi(m);
				year=atoi(y);
				
				if((isValidDate(day,month,year))&&(strlen(d)==1 || strlen(d)==2)&&(strlen(m)==1 || strlen(m)==2)&&(strlen(y)==4))
				{
					break;
				}
				else
				{
					printf("\nInvalid Date...Please Enter right date");
				}
			}
			else
			{
				printf("\nInvalid Date...Please Enter right date");
			}
		}
		else
		{
			printf("\nInvalid Date...Please Enter right date");
		}
	}
    //



	strcpy(e.time,"8.00am to 5.00pm");
    checkElectionDistrictName:
	printf("\nEnter District:");
	scanf(" %[^\n]s",e.district);
    for(int i = 0 ; e.district[i]!='\0';i++){
        if(!isalpha(e.district[i]))
        {
            printf("\nInvalid name of election district name!!\n");
            goto checkElectionDistrictName;
        }
    }
    checkConstituencyName:
	printf("\nEnter Constituency:");
	scanf(" %[^\n]s",e.constituency);
    for(int i = 0 ; e.constituency[i]!='\0';i++){
        if(!isalpha(e.constituency[i]))
        {
            printf("\nInvalid name of constituency name!!\n");
            goto checkConstituencyName;
        }
    }
	FILE *electionfile = fopen("election.csv","a");
	if(electionfile==NULL)
	{
		printf("Cant open election.csv file");
	}	
    else{
        fwrite(&e,sizeof(e),1,electionfile);
        fclose(electionfile);
    }
	
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
	while(fread(&e,sizeof(e),1,electionfile))
	{
		printf("%s\t%s\t%s  %s\t%s\n",e.name,e.date,e.time,e.district,e.constituency);
	}
	fclose(electionfile);
}


void addCandidate()
{
	struct Candidate c;
    struct Election e;
    int candidateId=0;
    char *d,*m,*y;
    int day,month,year;
    char tempdate[20]="";
	int cnt=0;
	int flag=0;
	int flag1=0;
	int flag2=0;
	int id=0;
	int i=0;
	int digitCount=0;
    FILE *electiondetails = fopen("election.csv","r");

    if(electiondetails==NULL)
    {
        perror("Unable to open file");
    }
    else
    {
        printf("-----------  Election Details  -----------\n");
        printf("\n");
        printf("\n");
        printf("Election Name           Date           District           Constituency    \n");
        while(fread(&e,sizeof(e),1,electiondetails))
        {
            
            printf("\n");
            printf("%s           %s           %s           %s",e.name,e.date,e.district,e.constituency);
        }
    }
    
    FILE *candidateIdfile = fopen("candidateId.txt","r+");
    
    fscanf(candidateIdfile,"%d",&candidateId);
    c.candidateId = ++candidateId;
    fclose(candidateIdfile);

    candidateIdfile = fopen("candidateId.txt","w");
    fprintf(candidateIdfile,"%d",candidateId);
    fclose(candidateIdfile);
    printf("\n");
	printf("\nRefer to above Election Details to Add Candidate\n");
    
	printf("\nCandidate ID: %d",c.candidateId);
    checkCandidateFirstName:
	printf("\nEnter Candidate Name:");
	scanf(" %[^\n]s",c.name);
    for(int i = 0 ; c.name[i]!='\0';i++){
        if(!isalpha(c.name[i]))
        {
            printf("\nIncorrect Format for candidate name!!\n");
            goto checkCandidateFirstName;
        }
    }
	// printf("\nEnter Date of Birth:");
	// scanf(" %[^\n]s",c.dob);
    //
    while(1)
        {
                printf("\nEnter Date of Birth:");
        	scanf(" %[^\n]s",c.dob);
                strcpy(tempdate,c.dob);
                if(strlen(tempdate)==8 || strlen(tempdate)==9 || strlen(tempdate)==10)
                {
                        cnt=0;
                        for(int i=0;tempdate[i]!='\0';i++)
                        {
                                if(tempdate[i]=='/')
                                        cnt++;
                        }
                        if(cnt==2)
                        {
                                d=strtok(tempdate,"/");
                                m=strtok(NULL,"/");
                                y=strtok(NULL,"/");
                                day=atoi(d);
                                month=atoi(m);
                                year=atoi(y);

                                if((isValidDate(day,month,year))&&(strlen(d)==1 || strlen(d)==2)&&(strlen(m)==1 || strlen(m)==2)&&(strlen(y)==4))
                                {
                                        break;
                                }
                                else
                                {
                                        printf("\nInvalid Date...Please Enter right date");
                                }
                        }
                        else
                        {
                                printf("\nInvalid Date...Please Enter right date");
                        }
                }
                else
                {
                        printf("\nInvalid Date...Please Enter right date");
                }
        }
    //
    if(isValidAge(day,month,year)>=18){

    checkElectionName:
	printf("\nEnter Election Name:");
	scanf(" %[^\n]s",c.electname);
    for(int i = 0 ; c.electname[i]!='\0';i++){
        if(!isalpha(c.electname[i]))
        {
            printf("\nIncorrect Format for Election name!!\n");
            goto checkElectionName;
        }
    }
    checkPartyName:
	printf("\nEnter Party Name:");
	scanf(" %[^\n]s",c.partyname);
    for(int i = 0 ; c.partyname[i]!='\0';i++){
        if(!isalpha(c.partyname[i]))
        {
            printf("\nIncorrect Format for Election Party name!!\n");
            goto checkPartyName;
        }
    }
    checkDistrictName:
	printf("\nEnter District:");
	scanf(" %[^\n]s",c.district);
    for(int i = 0 ; c.district[i]!='\0';i++){
        if(!isalpha(c.district[i]))
        {
            printf("\nIncorrect Format for District name!!\n");
            goto checkDistrictName;
        }
    }
    checkConstituencyName:
	printf("\nEnter Constituency:");
	scanf(" %[^\n]s",c.constituency);
    for(int i = 0 ; c.constituency[i]!='\0';i++){
        if(!isalpha(c.constituency[i]))
        {
            printf("\nIncorrect Name of Constituency!!\n");
            goto checkConstituencyName;
        }
    }
	printf("\nEnter Address:");
	scanf(" %[^\n]s",c.address);

	// printf("\nEnter Phone No.:");
	// scanf(" %[^\n]s",c.phone);
	// printf("\nEnter Email ID:");
	// scanf(" %[^\n]s",c.email);
    while(1)
		{
			i=0;
			digitCount=0;
			flag1=0;
    			printf("\nEnter Phone Number:");
    			scanf(" %[^\n]s",c.phone);
			while(c.phone[i]!='\0')
			{
				if(isdigit(c.phone[i]))
				{
					digitCount++;
				}
				else
				{
					flag1=1;
					break;
				}	
				i++;
			}
			if(digitCount!=10 || flag1==1)
			{
				printf("\nInavlid Phone no. Please enter proper Phone no.");
			
			}
			else
			{
				break;
			}
		}	
		while(1)
		{
    			printf("\nEnter Email ID:");
    			scanf(" %[^\n]s",c.email);
			flag2=0;
			int length=strlen(c.email);
			int atIndex=-1;
			int dotIndex=-1;
			if(length<5)
			{
				flag2=1;
			}
			if(flag2==0)
			{
				for(i=0; i<length; i++)
				{
					if(c.email[i]=='@')
					{
						atIndex=i;
					}
					else if(c.email[i]=='.')
					{
						dotIndex=i;
					}
				}	
				//Check if '@' and '.' are present and in valid position
				if(atIndex==-1 || dotIndex==-1 || atIndex>dotIndex)
				{
					flag2=1;
				}
			
				//Check if '@' and '.' are not the first or last characters
				if(atIndex==0 || dotIndex==0 || atIndex==length-1 || dotIndex==length-1)
				{
					flag2=1;
				}

			}
			if(flag2==1)
			{
				printf("\nInvalid Email ID..Please Enter valid Email ID");
			}
			else
			{
				break;
			}
            printf("\nSuccessfully added !!!\n");
		}
	}

    c.voteCount=0;

	FILE *candidatefile = fopen("candidate.csv","a");
	if(candidatefile==NULL)
	{
		printf("Cant open cadidate.csv file");
	}
	
	fwrite(&c,sizeof(c),1,candidatefile);
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
    checkPartyName:
	printf("\nEnter Party Name:");
	scanf(" %[^\n]s",p.name);
    for(int i = 0 ; p.name[i]!='\0';i++){
        if(!isalpha(p.name[i]))
        {
            printf("\nIncorrect Name of Party!!\n");
            goto checkPartyName;
        }
    }
    checkLeaderName:
	printf("\nEnter Leader:");
	scanf(" %[^\n]s",p.leader);
    for(int i = 0 ; p.leader[i]!='\0';i++){
        if(!isalpha(p.leader[i]))
        {
            printf("\nIncorrect Name of Leader!!\n");
            goto checkLeaderName;
        }
    }
    checkSymbol:
	printf("\nEnter Symbol:");
	scanf(" %[^\n]s",p.symbol);
    for(int i = 0 ; p.symbol[i]!='\0';i++){
        if(!isalpha(p.symbol[i]))
        {
            printf("\nIncorrect Type of Symbol!!\n");
            goto checkSymbol;
        }
    }
	partyfile=fopen("party.csv","a");
	if(partyfile==NULL)
	{
		printf("Cant open partyfile.csv file");
	}

	fwrite(&p,sizeof(p),1,partyfile);
//	fprintf(partyfile,"%s   %s   %s\n",p.name,p.leader,p.symbol);
	fclose(partyfile);
}

// struct Party *head_party,*current_party=NULL;

// void viewParty()
// {
// 	struct Party p;
// 	FILE *partyfile;
// 	partyfile=fopen("party.csv","r");
//     current_party=head_party;
//     printf("\n=======================Party Details======================\n");
	
// 	printf("\nParty Name      Party Leader    Party Symbol\n");
// 	while(current_party!=NULL){
//         printf("%s%20s%15s\n",current_party->name,current_party->leader,current_party->symbol);
//        current_party=current_party->next;
//     }
// 	fclose(partyfile);
// }

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
	while(fread(&p,sizeof(p),1,partyfile))
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
            printf("\nDo you want to approve the request? \n");
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
        printf("\nPress 2 to Add Election Details");
        printf("\nPress 3 to View Election Details");
        printf("\nPress 4 to Add Party Details");
        printf("\nPress 5 to View Party Details");
        printf("\nPress 6 to Add Candidate Details");
        printf("\nPress 7 to View Candidate Details");
        printf("\nPress 8.Exit");
        printf("\n");
        printf(" Enter The Choice: ");


        scanf("%s", ch);
        choice = atoi(ch);
        switch (choice)
        {
        case 1:
            viewRequest();
            break;
        case 2:
            addElection();
            break;
        case 3:
            viewElection();  
            break;
        case 4:
            addParty();
            break;
        case 5:
            viewParty();
            break;
        case 6:
            addCandidate();
            break;
        case 7:
            viewCandidate();
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