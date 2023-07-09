
#include "../header/header.h"


int getCurrentdate()
{
    time_t currentTime = time(NULL);                // Get current time
    struct tm *localTime = localtime(&currentTime); // Convert to local time

    int day = localTime->tm_mday;         // Get day of the month
    int month = localTime->tm_mon + 1;    // Get month (January is 0)
    int year = localTime->tm_year + 1900; // Get year (since 1900)

    //printf("%02d/%02d/%04d\n", day, month, year);  // Print in dd/mm/yyyy format
    return year;
}


int validElectionDate(int day,int month,int year){

    time_t currentTime = time(NULL);                // Get current time
    struct tm *localTime = localtime(&currentTime); // Convert to local time

    int TodayDate = localTime->tm_mday;         
    int TodayMonth = localTime->tm_mon + 1;    
    int TodayYear = localTime->tm_year + 1900;
    if(TodayYear<year){
        return 1;
    }
    if(TodayYear>year){
        return 0;
    }
    if(TodayYear == year){
        if(TodayMonth>month){
            return 0;
        }
        if(TodayMonth<month){
            return 1;
        }
        if(TodayMonth==month){
            if(TodayDate<day){
                return 1;
            }
            if(TodayDate>=day){
                return 0;
            }
        }
    }
    return 0;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------

void viewRequestStatus(int currentUser)
{
    struct Request request;

    FILE *requeststatus = fopen("RequestStatus.csv", "r");
    if (requeststatus == NULL)
    {
        perror("Error in file opening\n");
    }
    else
    {
        while (fread(&request, sizeof(request), 1, requeststatus))
        {
            if (request.UserId == currentUser)
            {
                if(strcmp(request.status,"Pending")==0){
                    printf(COLOR_BOLD"\nYour Request Status for VoterId is" COLOR_BLUE" %s ", request.status);
                    printf("\n");
                    fclose(requeststatus);
                    break;
                }else{
                    printf(COLOR_BOLD"\nYour Request Status for VoterId is" COLOR_GREEN" %s ", request.status);
                    printf("\n");
                    fclose(requeststatus);
                    break;
                }
                
            }
        }
        fclose(requeststatus);
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------

void requsetVoterId(int userId)
{
    int UserId = userId;

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

        while (fread(&newuser, sizeof(newuser), 1, userDetails))
        {
            if (newuser.UserId == UserId)
            {
                if (strcmp(newuser.VoterId, "") == 0)
                {
                    FILE *userRequest = fopen("VoterIdRequest.csv", "a");
                    request.UserId = UserId;
                    strcpy(request.status, "Pending");
                    fwrite(&request, sizeof(request), 1, userRequest);
                    printf(COLOR_GREEN COLOR_BOLD"\nSuccessfully Requested for VoterId\n"COLOR_RESET);
                    printf("\n");
                    fclose(userRequest);

                    FILE *requeststatus = fopen("RequestStatus.csv", "a");
                    Request.UserId = UserId;
                    strcpy(Request.status, "Pending");
                    fwrite(&Request, sizeof(Request), 1, requeststatus);
                    fclose(requeststatus);

                    break;
                }
                else
                {
                    printf(COLOR_RED COLOR_BOLD"\nYour VoterId is already generated !!!\n"COLOR_RESET);
                    printf("\n");
                }
            }
        }
        fclose(userDetails);
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------

void viewVoterId(int userId)
{
    struct User newUser;
    FILE *user = fopen("UserDetails.csv", "r");
    if (user == NULL)
    {
        perror("Error in file opening\n");
    }
    while (fread(&newUser, sizeof(newUser), 1, user))
    {
        if (userId == newUser.UserId)
        {
            printf(COLOR_BOLD"\nYour VoterId is " COLOR_GREEN"%s", newUser.VoterId);
            printf("\n");
            break;
        }
    }
    fclose(user);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------

void viewElectionSchedules(int userId)
{
    struct Election e;
    struct User user;

    char UserConstituency[50];
    char UserDistrict[50];

    FILE *userdetails = fopen("UserDetails.csv", "r");
    if (userdetails == NULL)
    {
        printf("Cant open UserDetails.csv file");
    }
    else
    {
        while (fread(&user, sizeof(user), 1, userdetails))
        {
            if (user.UserId == userId)
            {
                strcpy(UserConstituency, user.constituency);
                strcpy(UserDistrict, user.district);
                break;
            }
        }
        fclose(userdetails);
    }

    FILE *electionfile = fopen("election.csv", "r");
    if (electionfile == NULL)
    {
        printf("Cant open election.csv file");
    }
    else
    {

        
        printf("\n");
        printf(COLOR_BLUE COLOR_BOLD"|----------------------------------------------Election Details------------------------------------------------------|\n"COLOR_RESET);
        printf(COLOR_GREEN"%-10s%-20s%-30s%-20s%-20s%-15s\n","|","Name","ElectionDate","Voting_Time","District","Constituency"COLOR_RESET);
        printf(COLOR_BLUE"|--------------------------------------------------------------------------------------------------------------------|\n"COLOR_RESET);
        

        while (fread(&e, sizeof(e), 1, electionfile))
        {
            if ((strcmp(e.constituency, UserConstituency) == 0) && (strcmp(e.district, UserDistrict) == 0))
            {
                
                printf("%-10s%-20s%-30s%-20s%-20s%-15s\n","|",e.name, e.date, e.time, e.district, e.constituency);
                printf("|--------------------------------------------------------------------------------------------------------------------|\n");
            }
        }
        printf("\n");
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------

void vote()
{
    char electionName[50];
    struct Candidate candidate;
    struct Election election;

    int candidateId = 0;
label:
    printf(COLOR_BOLD COLOR_CYAN"\nEnter the Election Name to proceed the voting process : "COLOR_RESET);
    scanf(" %[^\n]s", electionName);

    FILE *electionfile = fopen("election.csv", "r");
    if (electionfile != NULL)
    {
        int present = 0;
        while (fread(&election, sizeof(election), 1, electionfile))
        {
            if (strcmp(election.name, electionName) == 0)
            {
                present = 1;
                FILE *candidatefile = fopen("candidate.csv", "r+");
                printf("\n");
                printf("%-10s%-20s%-20s\n","Candidate ID","Candidate Name","Party Name");

                while (fread(&candidate, sizeof(candidate), 1, candidatefile))
                {
                    if (strcmp(candidate.electname, electionName) == 0)
                    {
                        // printf("\n%d\t\t%s\t\t%s", candidate.candidateId, candidate.name, candidate.partyname);
                        printf("%-10d%-20s%-20s\n", candidate.candidateId, candidate.name, candidate.partyname);
                    }
                }
                rewind(candidatefile);
                printf("\n");
            candidatelabel:
                printf(COLOR_BOLD"\nPlease enter the CandidateId to vote for that Candidate : ");
                scanf("%d", &candidateId);

                int flag = 0;

                while (fread(&candidate, sizeof(candidate), 1, candidatefile))
                {

                    if (candidate.candidateId == candidateId)
                    {
                        flag = 1;
                        candidate.voteCount++;
                        fseek(candidatefile, -sizeof(candidate), SEEK_CUR);
                        fwrite(&candidate, sizeof(candidate), 1, candidatefile);

                        printf(COLOR_GREEN COLOR_BOLD"\nCongratulation You have Voted successfully\n"COLOR_RESET);
                        break;
                    }
                }
                if (flag == 0)
                {
                    printf(COLOR_RED COLOR_BOLD"\nPlease enter Valid candidate Id from above list\n"COLOR_RESET);
                    goto candidatelabel;
                }
                fclose(candidatefile);
                break;
            }
        }

        if (present == 0)
        {
            printf(COLOR_RED COLOR_BOLD"\nplease enter valid election name from above list of elections\n"COLOR_RESET);
            goto label;
        }
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------

void castVotes(int userId)
{

    struct User user;
    viewElectionSchedules(userId);

    FILE *userfile = fopen("UserDetails.csv", "r+");
    while (fread(&user, sizeof(user), 1, userfile))
    {
        if (user.UserId == userId)
        {
            if (strcmp(user.VoterId, "") == 0)
            {
                printf(COLOR_RED"\nYou Cant Vote as you dont have voterId\n"COLOR_RESET);
            }
            else
            {
                if (strcmp(user.Voted, "true") == 0)
                {
                    printf(COLOR_RED"\nAlready Voted\n"COLOR_RESET);
                    break;
                }
                else
                {
                    vote();
                    strcpy(user.Voted, "true");
                    fseek(userfile, -sizeof(user), SEEK_CUR);
                    fwrite(&user, sizeof(user), 1, userfile);
                    break;
                }
            }
        }
    }
    fclose(userfile);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
void viewElectionResult(int userId)
{
    int currentUser = userId;
    struct Candidate candidate;
    struct Election election;
    struct User user;

    int VoteCount[10];
    int i = 0;
    int size = 0;

    int ch = 0;
    char date[11];
    char userConstituency[30];
    char electionName[50];

    printf("\nChoose the Option to view Result\n");
    printf("\nPress 1 to See Result On basis of Date");
    printf("\nPress 2 to See Result On basis of Constituency ");
    printf("\nEnter Your Choice : ");
    scanf("%d", &ch);

    FILE *userdetails = fopen("UserDetails.csv", "r");
    while (fread(&user, sizeof(user), 1, userdetails))
    {
        if (user.UserId == currentUser)
        {
            strcpy(userConstituency, user.constituency);
            break;
        }
    }

    if (ch == 1)
    {
        printf(COLOR_BOLD"\nEnter date of Election \n");
        scanf("%s", date);
        FILE *electionfile = fopen("election.csv", "r");
        if (electionfile == NULL)
        {
            perror("Can't Open file");
        }
        else
        {
            

            printf("\n");
            printf(COLOR_BLUE COLOR_BOLD"|----------------------------------------------Election Details------------------------------------------------------|\n"COLOR_RESET);
            printf(COLOR_GREEN"%-10s%-20s%-30s%-20s%-20s%-15s\n","|","Name","ElectionDate","Voting_Time","District","Constituency"COLOR_RESET);
            printf(COLOR_BLUE"|--------------------------------------------------------------------------------------------------------------------|\n"COLOR_RESET);
            


            while (fread(&election, sizeof(election), 1, electionfile))
            {
                if (strcmp(election.date, date) == 0 && strcmp(election.constituency, userConstituency) == 0)
                {
                    strcpy(electionName, election.name);
                    // printf("%s\t%s\t%s  %s\t%s\n", election.name, election.date, election.time, election.district, election.constituency);
                    printf("%-10s%-20s%-30s%-20s%-20s%-15s\n","|",election.name, election.date, election.time, election.district, election.constituency);
                    printf("|--------------------------------------------------------------------------------------------------------------------|\n");
                }
            }
             
            fclose(electionfile);
            printf("\n");
            







            FILE *candidatefile = fopen("candidate.csv", "r");
            if (candidatefile == NULL)
            {
                perror("Can't Open file");
            }
            else
            {
                
                printf("\n");
                printf(COLOR_BLUE COLOR_BOLD"|------------------------------------------------------------Candidate Details----------------------------------------------------------------------------|\n"COLOR_RESET);
                printf("\n");
                printf(COLOR_GREEN COLOR_BOLD"%-5s%-15s%-20s%-20s%-15s%-20s%-15s%-13s\n","|","Candidate ID","Candidate Name","Election Name","Party Name","District","Constituency","Number Of Votes"COLOR_RESET);
                printf(COLOR_BLUE"|---------------------------------------------------------------------------------------------------------------------------------------------------------|\n"COLOR_RESET);



                while (fread(&candidate, sizeof(candidate), 1, candidatefile))
                {
                    if (strcmp(candidate.electname, electionName) == 0)
                    {
                        VoteCount[i++] = candidate.voteCount;
                        size++;
                    }
                }
                rewind(candidatefile);

                for (i = 0; i < size - 1; i++)
                {
                    for (int j = 0; j < size - i - 1; j++)
                    {
                        if (VoteCount[j] < VoteCount[j + 1])
                        {
                            int temp = VoteCount[j];
                            VoteCount[j] = VoteCount[j + 1];
                            VoteCount[j + 1] = temp;
                        }
                    }
                }
                int k = 0;
                while (fread(&candidate, sizeof(candidate), 1, candidatefile) && k < size)
                {
                    if (candidate.voteCount == VoteCount[k])
                    {
                        
                        printf("%-5s%-15d%-20s%-20s%-15s%-20s%-15s%-13d\n","|",candidate.candidateId, candidate.name, candidate.electname, candidate.partyname, candidate.district, candidate.constituency,candidate.voteCount);
                        printf("|---------------------------------------------------------------------------------------------------------------------------------------------------------|\n");
                        k++;
                        rewind(candidatefile);
                    }
                }

                fclose(candidatefile);
                printf("\n");
            }
        }
    }
    if (ch == 2)
    {
        char constituency[30];
        printf(COLOR_BOLD"\nEnter Constituency of Election \n");
        scanf("%s", constituency);

        FILE *electionfile = fopen("election.csv", "r");

        if (electionfile == NULL)
        {
            perror("Can't Open file");
        }
        else
        {
            printf("\n");
            printf(COLOR_BLUE COLOR_BOLD"|----------------------------------------------Election Details------------------------------------------------------|\n"COLOR_RESET);
            printf(COLOR_GREEN"%-10s%-20s%-30s%-20s%-20s%-15s\n","|","Name","ElectionDate","Voting_Time","District","Constituency"COLOR_RESET);
            printf(COLOR_BLUE"|--------------------------------------------------------------------------------------------------------------------|\n"COLOR_RESET);
            


            while (fread(&election, sizeof(election), 1, electionfile))
            {
                if (strcmp(election.constituency, constituency) == 0)
                {
                    strcpy(electionName, election.name);
                    
                    printf("%-10s%-20s%-30s%-20s%-20s%-15s\n","|",election.name, election.date, election.time, election.district, election.constituency);
                    printf("|--------------------------------------------------------------------------------------------------------------------|\n");

                }
            }
            printf("\n");
            fclose(electionfile);

            FILE *candidatefile = fopen("candidate.csv", "r");
            if (candidatefile == NULL)
            {
                perror("Can't Open file");
            }
            else
            {
               
                printf("\n");
                printf(COLOR_BLUE COLOR_BOLD"|------------------------------------------------------------Candidate Details----------------------------------------------------------------------------|\n"COLOR_RESET);
                printf("\n");
                printf(COLOR_GREEN COLOR_BOLD"%-5s%-15s%-20s%-20s%-15s%-20s%-15s%-13s\n","|","Candidate ID","Candidate Name","Election Name","Party Name","District","Constituency","Number Of Votes"COLOR_RESET);
                printf(COLOR_BLUE"|---------------------------------------------------------------------------------------------------------------------------------------------------------|\n"COLOR_RESET);

                
                
                while (fread(&candidate, sizeof(candidate), 1, candidatefile))
                {
                    if (strcmp(candidate.electname, electionName) == 0)
                    {
                        VoteCount[i++] = candidate.voteCount;
                        size++;
                    }
                }
                rewind(candidatefile);

                for (i = 0; i < size - 1; i++)
                {
                    for (int j = 0; j < size - i - 1; j++)
                    {
                        if (VoteCount[j] < VoteCount[j + 1])
                        {
                            int temp = VoteCount[j];
                            VoteCount[j] = VoteCount[j + 1];
                            VoteCount[j + 1] = temp;
                        }
                    }
                }
                int k = 0;
                while (fread(&candidate, sizeof(candidate), 1, candidatefile) && k < size)
                {
                    if (candidate.voteCount == VoteCount[k])
                    {
                        // printf("\n%d %s %s %s %s %s %d", candidate.candidateId, candidate.name, candidate.electname, candidate.partyname, candidate.district, candidate.constituency, candidate.voteCount);
                        printf("%-5s%-15d%-20s%-20s%-15s%-20s%-15s%-13d\n","|",candidate.candidateId, candidate.name, candidate.electname, candidate.partyname, candidate.district, candidate.constituency,candidate.voteCount);
                        printf("|---------------------------------------------------------------------------------------------------------------------------------------------------------|\n");
                        k++;
                        rewind(candidatefile);
                    }
                }
                printf("\n");
                fclose(candidatefile);
            }
        }
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------


void userMenu(int userId)
{
    int choice = 0;
    int currentUser = userId;
    char ch[10];

    while (choice != 7)
    {
       
        printf(COLOR_BLUE"|------------------------------------------------------------------------|\n"COLOR_RESET);
        printf(COLOR_BLUE"|"COLOR_MAGENTA COLOR_BOLD"                        Logged in Successfully                                      "COLOR_RESET COLOR_BLUE "|\n"COLOR_RESET);
        printf(COLOR_BLUE"|------------------------------------------------------------------------|\n"COLOR_RESET);
        printf(COLOR_BOLD"|Please select an option:                                                | \n"COLOR_RESET);
        printf("%-3s%-70s%-30s\n","|", " 1.  Request for VoterId","|");
        printf("%-3s%-70s%-30s\n","|", " 2.  View Request Status","|");
        printf("%-3s%-70s%-30s\n","|", " 3.  View VoterId","|");
        printf("%-3s%-70s%-30s\n","|", " 4.  View Election Schedules","|");
        printf("%-3s%-70s%-30s\n","|", " 5.  Cast Vote","|");
        printf("%-3s%-70s%-30s\n","|", " 6.  View Election Result","|");
        printf("%-3s%-70s%-30s\n","|", " 7.  Logout","|");
        printf("|------------------------------------------------------------------------|\n");
        printf("\n");
        printf(COLOR_BOLD" Enter The Choice:"COLOR_RESET);




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
            viewElectionSchedules(currentUser);
            break;
        case 5:
            castVotes(currentUser);
            break;
        case 6:
            viewElectionResult(currentUser);
             
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

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------