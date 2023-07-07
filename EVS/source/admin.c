#include <stdio.h>
#include "../header/header.h"




void addElection()
{
	struct Election  e;
	char *d,*m,*y;
	int day,month,year;
	char tempdate[20]="";
	int cnt=0;

	
    printf("\n");
	printf(COLOR_BOLD"  ----------------------------------" COLOR_RESET COLOR_MAGENTA COLOR_BOLD" Add Election Details "COLOR_RESET COLOR_BOLD"-----------------------------------------------\n"COLOR_RESET);
	checkElectionName:
    printf(COLOR_BOLD"\nEnter Election Name:");
	scanf(" %[^\n]s",e.name);
    for(int i = 0 ; e.name[i]!='\0';i++){
        if(!isalpha(e.name[i]))
        {
            printf(COLOR_RED"\nIncorrect Format for election name!!\n"COLOR_RESET);
            goto checkElectionName;
        }
    }
    while(1)
	{
		printf(COLOR_BOLD"\nEnter ElectionDate:");
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
				int validDate = validElectionDate(day,month,year);
				if(validDate==1 && (isValidDate(day,month,year))&&(strlen(d)==1 || strlen(d)==2)&&(strlen(m)==1 || strlen(m)==2)&&(strlen(y)==4))
				{
					break;
				}
				else
				{
					printf(COLOR_RED"\nInvalid Date...Please Enter right date"COLOR_RESET);
				}
			}
			else
			{
				printf(COLOR_RED"\nInvalid Date...Please Enter right date"COLOR_RESET);
			}
		}
		else
		{
			printf(COLOR_RED"\nInvalid Date...Please Enter right date"COLOR_RESET);
		}
	}
    //



	strcpy(e.time,"8.00am to 5.00pm");
    checkElectionDistrictName:
	printf(COLOR_BOLD"\nEnter District:");
	scanf(" %[^\n]s",e.district);
    for(int i = 0 ; e.district[i]!='\0';i++){
        if(!isalpha(e.district[i]))
        {
            printf(COLOR_RED"\nInvalid name of election district name!!\n"COLOR_RESET);
            goto checkElectionDistrictName;
        }
    }
    checkConstituencyName:
	printf(COLOR_BOLD"\nEnter Constituency:");
	scanf(" %[^\n]s",e.constituency);
    for(int i = 0 ; e.constituency[i]!='\0';i++){
        if(!isalpha(e.constituency[i]))
        {
            printf(COLOR_RED"\nInvalid name of constituency name!!\n"COLOR_RESET);
            goto checkConstituencyName;
        }
    }
	FILE *electionfile = fopen("election.csv","a");
	if(electionfile==NULL)
	{
		printf(COLOR_RED"Cant open election.csv file"COLOR_RESET);
	}	
    else{
        fwrite(&e,sizeof(e),1,electionfile);
        fclose(electionfile);
    }
	
	fclose(electionfile);
    printf(COLOR_GREEN COLOR_BOLD"\n Election Added Successfully \n"COLOR_RESET);
    printf("\n");
}


void viewElection()
{
	struct Election  e;
	FILE *electionfile;
	electionfile=fopen("election.csv","r");
	
	if(electionfile==NULL)
	{
		printf(COLOR_RED"Cant open election.csv file"COLOR_RESET);
	}
	printf("\n");
    printf(COLOR_BLUE COLOR_BOLD"|----------------------------------------------Election Details------------------------------------------------------|\n"COLOR_RESET);
	printf(COLOR_GREEN"%-10s%-20s%-30s%-20s%-20s%-15s\n","|","Name","ElectionDate","Voting_Time","District","Constituency"COLOR_RESET);
    printf(COLOR_BLUE"|--------------------------------------------------------------------------------------------------------------------|\n"COLOR_RESET);
	while(fread(&e,sizeof(e),1,electionfile))
	{
		printf("%-10s%-20s%-30s%-20s%-20s%-15s\n","|",e.name,e.date,e.time,e.district,e.constituency);
        printf("|--------------------------------------------------------------------------------------------------------------------|\n");
	}
	fclose(electionfile);
    printf("\n");
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
        // printf("\n");
        // printf("-----------  Election Details  -----------\n");
        // printf("\n");

        printf("\n");
	    printf(COLOR_BOLD"  ----------------------------------" COLOR_RESET COLOR_MAGENTA COLOR_BOLD" Election Details "COLOR_RESET COLOR_BOLD"-----------------------------------------------\n"COLOR_RESET);

        printf(COLOR_BLUE"|-----------------------------------------------------------------------------------------|\n"COLOR_RESET);
        printf(COLOR_GREEN"%-20s%-30s%-20s%-20s\n","|Election Name","Date","District","Constituency                 "COLOR_RESET);
        printf(COLOR_BLUE"|-----------------------------------------------------------------------------------------|\n"COLOR_RESET);
        while(fread(&e,sizeof(e),1,electiondetails))
        {
            
            
            printf("%-10s%-20s%-30s%-20s%-20s%-5s\n","|",e.name,e.date,e.district,e.constituency,"");
            printf("|-----------------------------------------------------------------------------------------|\n");
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
	printf(COLOR_CYAN"\nRefer to above Election Details to Add Candidate\n"COLOR_RESET);
    
	printf("\nCandidate ID: %d",c.candidateId);
    checkCandidateFirstName:
	printf(COLOR_BOLD"\nEnter Candidate Name:");
	scanf(" %[^\n]s",c.name);
    for(int i = 0 ; c.name[i]!='\0';i++){
        if(!isalpha(c.name[i]))
        {
            printf(COLOR_RED"\nIncorrect Format for candidate name!!\n"COLOR_RESET);
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
                                        printf(COLOR_RED"\nInvalid Date...Please Enter right date"COLOR_RESET);
                                }
                        }
                        else
                        {
                                printf(COLOR_RED"\nInvalid Date...Please Enter right date"COLOR_RESET);
                        }
                }
                else
                {
                        printf(COLOR_RED"\nInvalid Date...Please Enter right date"COLOR_RESET);
                }
        }
    //
    if(isValidAge(day,month,year)>=18){

    checkElectionName:
	printf(COLOR_BOLD"\nEnter Election Name:");
	scanf(" %[^\n]s",c.electname);
    for(int i = 0 ; c.electname[i]!='\0';i++){
        if(!isalpha(c.electname[i]))
        {
            printf(COLOR_RED"\nIncorrect Format for Election name!!\n"COLOR_RESET);
            goto checkElectionName;
        }
    }

    checkPartyName:
	printf(COLOR_BOLD"\nEnter Party Name:");
	scanf(" %[^\n]s",c.partyname);
    for(int i = 0 ; c.partyname[i]!='\0';i++){
        if(!isalpha(c.partyname[i]))
        {
            printf(COLOR_RED"\nIncorrect Format for Election Party name!!\n"COLOR_RESET);
            goto checkPartyName;
        }
    }
    checkDistrictName:
	printf(COLOR_BOLD"\nEnter District:");
	scanf(" %[^\n]s",c.district);
    for(int i = 0 ; c.district[i]!='\0';i++){
        if(!isalpha(c.district[i]))
        {
            printf(COLOR_RED"\nIncorrect Format for District name!!\n"COLOR_RESET);
            goto checkDistrictName;
        }
    }
    checkConstituencyName:
	printf(COLOR_BOLD"\nEnter Constituency:");
	scanf(" %[^\n]s",c.constituency);
    for(int i = 0 ; c.constituency[i]!='\0';i++){
        if(!isalpha(c.constituency[i]))
        {
            printf(COLOR_RED"\nIncorrect Name of Constituency!!\n"COLOR_RESET);
            goto checkConstituencyName;
        }
    }
	printf(COLOR_BOLD"\nEnter Address:");
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
    			printf(COLOR_BOLD"\nEnter Phone Number:");
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
				printf(COLOR_RED"\nInavlid Phone no. Please enter proper Phone no."COLOR_RESET);
			
			}
			else
			{
				break;
			}
		}	
		while(1)
		{
    			printf(COLOR_BOLD"\nEnter Email ID:");
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
				printf(COLOR_RED"\nInvalid Email ID..Please Enter valid Email ID"COLOR_RESET);
			}
			else
			{
				break;
			}
            
		}
	}

    c.voteCount=0;

	FILE *candidatefile = fopen("candidate.csv","a");
	if(candidatefile==NULL)
	{
		printf(COLOR_RED"Cant open cadidate.csv file"COLOR_RESET);
	}
	
	fwrite(&c,sizeof(c),1,candidatefile);
    printf(COLOR_GREEN"\nSuccessfully added !!!\n"COLOR_RESET);
	fclose(candidatefile);


}


void viewCandidate()
{
        struct Candidate candidate;
        FILE *candidatefile;
        candidatefile=fopen("candidate.csv","r");

        if(candidatefile==NULL)
        {
                printf(COLOR_RED"Cant open candidate.csv file"COLOR_RESET);
        }
        //printf("\n=======================Candidate Details======================\n");


        printf("\n");
    printf(COLOR_BLUE COLOR_BOLD"|------------------------------------------------------------Candidate Details----------------------------------------------------------------------------|\n"COLOR_RESET);
    printf("\n");
	printf(COLOR_GREEN COLOR_BOLD"%-5s%-15s%-20s%-15s%-20s%-15s%-13s%-10s%-10s%-10s\n","|","Candidate ID","Candidate Name","Date of Birth","Election Name","Party Name","Constituency","Address","Phone No","Email ID"COLOR_RESET);
    printf(COLOR_BLUE"|---------------------------------------------------------------------------------------------------------------------------------------------------------|\n"COLOR_RESET);

       // printf("\nCandidate ID  Candidate Name  Date of Birth  Election Name  Party Name  District    Constituency  Address    Phone No    Email ID");
        while(fread(&candidate,sizeof(candidate),1,candidatefile)==1)
	    {
        	printf("%-5s%-15d%-20s%-15s%-20s%-15s%-13s%-10s%-10s%-10s%-10s\n"," ",candidate.candidateId,candidate.name,candidate.dob,candidate.electname,candidate.partyname,candidate.district,candidate.constituency,candidate.address,candidate.phone,candidate.email);
            printf("|---------------------------------------------------------------------------------------------------------------------------------------------------------|\n");
        }
        printf("\n");
	fclose(candidatefile);
}

void addParty()
{
	struct Party p;
	FILE *partyfile;

	
    printf("\n");
	printf(COLOR_BOLD"  ----------------------------------" COLOR_RESET COLOR_MAGENTA COLOR_BOLD" Add Party Details "COLOR_RESET COLOR_BOLD"-----------------------------------------------\n"COLOR_RESET);
    checkPartyName:
	printf("\nEnter Party Name:");
	scanf(" %[^\n]s",p.name);
    for(int i = 0 ; p.name[i]!='\0';i++){
        if(!isalpha(p.name[i]))
        {
            printf(COLOR_RED"\nIncorrect Name of Party!!\n"COLOR_RESET);
            goto checkPartyName;
        }
    }
    checkLeaderName:
	printf(COLOR_BOLD"\nEnter Leader:");
	scanf(" %[^\n]s",p.leader);
    for(int i = 0 ; p.leader[i]!='\0';i++){
        if(!isalpha(p.leader[i]))
        {
            printf(COLOR_RED"\nIncorrect Name of Leader!!\n"COLOR_RESET);
            goto checkLeaderName;
        }
    }
    checkSymbol:
	printf(COLOR_BOLD"\nEnter Symbol:");
	scanf(" %[^\n]s",p.symbol);
    for(int i = 0 ; p.symbol[i]!='\0';i++){
        if(!isalpha(p.symbol[i]))
        {
            printf(COLOR_RED"\nIncorrect Type of Symbol!!\n"COLOR_RESET);
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
     printf(COLOR_GREEN COLOR_BOLD"\n  Party Added Successfully \n"COLOR_RESET);
    printf("\n");
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
    printf("\n");
	printf(COLOR_BOLD"  ----------------------------------" COLOR_RESET COLOR_MAGENTA COLOR_BOLD" Party Details "COLOR_RESET COLOR_BOLD"-----------------------------------------------\n"COLOR_RESET);
    printf("\n");
	printf(COLOR_BLUE"|-----------------------------------------------------------------------------------------------|\n"COLOR_RESET);
	printf(COLOR_GREEN COLOR_BOLD"%-10s%-20s%-20s%-15s\n","|","Party Name","Party_Leader","Party Symbol"COLOR_RESET);
    printf(COLOR_BLUE"|-----------------------------------------------------------------------------------------------|\n"COLOR_RESET);
	while(fread(&p,sizeof(p),1,partyfile))
	{
		printf("%-10s%-20s%-20s%-15s\n","|",p.name,p.leader,p.symbol);
        printf("|-----------------------------------------------------------------------------------------------|\n");
	}
    printf("\n");
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
    printf("\n");
    while (choice != 8)
    {
    
        printf(COLOR_BLUE"|------------------------------------------------------------------------|\n"COLOR_RESET);
        printf(COLOR_BLUE"|"COLOR_MAGENTA COLOR_BOLD"                        Admin Menu                                      "COLOR_RESET COLOR_BLUE "|\n"COLOR_RESET);
        printf(COLOR_BLUE"|------------------------------------------------------------------------|\n"COLOR_RESET);
        printf(COLOR_BOLD"|Please select an option:                                                | \n"COLOR_RESET);
        printf("%-3s%-70s%-30s\n","|", " 1.  View VoterId Request from User","|");
        printf("%-3s%-70s%-30s\n","|", " 2.  Add Election Details","|");
        printf("%-3s%-70s%-30s\n","|", " 3.  View Election Details","|");
        printf("%-3s%-70s%-30s\n","|", " 4.  Add Party Details","|");
        printf("%-3s%-70s%-30s\n","|", " 5.  View Party Details","|");
        printf("%-3s%-70s%-30s\n","|", " 6.  Add Candidate Details","|");
        printf("%-3s%-70s%-30s\n","|", " 7.  View Candidate Details","|");
        printf("|   8. Exit                                                              |\n");
        printf("|------------------------------------------------------------------------|\n");
        printf("\n");
        printf(COLOR_BOLD" Enter The Choice:"COLOR_RESET);


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