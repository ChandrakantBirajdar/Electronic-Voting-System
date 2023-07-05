#include <stdio.h>
#include "header.h"

void getAllDetails()
{
    struct User newuser;

    FILE * allDetails = fopen("UserDetails.csv", "r");
    if (allDetails == NULL)
    {
        perror("Error in file opening\n");
    }
    else
    {
        while (fread(&newuser, sizeof(newuser), 1, allDetails))
        {
            
                printf("\nUser=%d \tDay=%d \tMon=%d \tYeaar=%d \tDOB=%s",newuser.UserId,newuser.day,newuser.mon,newuser.year,newuser.dob);
                printf("\n");
        }
        fclose(allDetails);
    }
}

int getCurrentdate()
{
    time_t currentTime = time(NULL);                // Get current time
    struct tm *localTime = localtime(&currentTime); // Convert to local time

    int day = localTime->tm_mday;         // Get day of the month
    int month = localTime->tm_mon + 1;    // Get month (January is 0)
    int year = localTime->tm_year + 1900; // Get year (since 1900)
    // printf("%02d/%02d/%04d\n", day, month, year);  // Print in dd/mm/yyyy format
    return year;
}

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
                printf("\nYour Request Status for VoterId is %s ", request.status);
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
    struct User newuser;
    int userId = 0;
    FILE *getuserId = fopen("userid.txt", "r+");

    fscanf(getuserId, "%d", &userId);
    newuser.UserId = ++userId;
    fclose(getuserId);

    getuserId = fopen("userid.txt", "w");
    rewind(getuserId);
    fprintf(getuserId, "%d", userId);
    fclose(getuserId);

    FILE *userDetails = fopen("UserDetails.csv", "a");
    if (userDetails == NULL)
    {
        perror("Error in file opening\n");
    }
    else
    {

    checkFirstName:
        printf("\nEnter First Name:");
        scanf(" %[^\n]s", newuser.firstname);
        for (int i = 0; newuser.firstname[i] != '\0'; i++)
        {
            if (!isalpha(newuser.firstname[i]))
            {
                printf("\nPlease Enter Valid First Name !!\n");
                goto checkFirstName;
            }
        }

        //----------------------------------------

        // printf("\nEnter LastName: ");
        // scanf("%s", newuser.lastname);

        //----------------------------------------

    checkLastName:
        printf("\nEnter Last Name:");
        scanf(" %[^\n]s", newuser.lastname);
        for (int i = 0; newuser.lastname[i] != '\0'; i++)
        {
            if (!isalpha(newuser.lastname[i]))
            {
                printf("\nPlease Enter Valid Last Name !!\n");
                goto checkLastName;
            }
        }

        //----------------------------------------

        // printf("\nEnter DOB  in format   [dd/mm/yyyy]: ");
        // scanf("\n%d/%d/%d", &newuser.day, &newuser.mon, &newuser.year);

        // int year = getCurrentdate();
        // newuser.age = year - newuser.year;
        // printf("\nAge: %d ", newuser.age);
        // printf("\n");
        // if (newuser.age < 18)
        // {
        //     printf("\nYou are not Eligible for Voting as your age is less than 18");
        //     goto label;
        // }
        // printf("\nEnter Gender: ");
        // scanf("%s", newuser.gender);

        //----------------------------------------
            // char *dd=(char *)malloc(sizeof(char));
            // char *mm=(char *)malloc(sizeof(char));
            // char *yy=(char *)malloc(sizeof(char));
           
        while (1)
        {
            printf("\nEnter DOB  in format   [dd/mm/yyyy]: ");
            scanf("\n%d/%d/%d", &newuser.day, &newuser.mon, &newuser.year);
            sprintf(newuser.dob,"%d/%d/%d",newuser.day,newuser.mon,newuser.year);
           
            //printf("%s",d)
            //scanf(" %[^\n]s", newuser.dob);
            
            strcpy(tempdate, newuser.dob);
            if (strlen(tempdate) == 8 || strlen(tempdate) == 9 || strlen(tempdate) == 10)
            {
                cnt = 0;
                for (int i = 0; tempdate[i] != '\0'; i++)
                {
                    if (tempdate[i] == '/')
                        cnt++;
                }
                if (cnt == 2)
                {
                    d = strtok(tempdate, "/");
                    m = strtok(NULL, "/");
                    y = strtok(NULL, "/");
                    day = atoi(d);
                   // newuser.day=day;

                    month = atoi(m);

                   // newuser.mon=month;

                    year = atoi(y);

                  //  newuser.year=year;

                    if ((isValidDate(day, month, year)) && (strlen(d) == 1 || strlen(d) == 2) && (strlen(m) == 1 || strlen(m) == 2) && (strlen(y) == 4))
                    {
                         printf("\nday=%d",newuser.day);
                printf("\nmon=%d",newuser.mon);
                printf("\nyer=%d",newuser.year);
                
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
        if (isValidAge(day, month, year) < 18)
        {
            printf("\nYou are not Eligible for Voting as your age is less than 18");
            goto label;
        }
    checkGender:
        printf("\nEnter Gender:");
        scanf(" %[^\n]s", newuser.gender);
        for (int i = 0; newuser.gender[i] != '\0'; i++)
        {
            if (!isalpha(newuser.gender[i]))
            {
                printf("\nPlease Enter Valid Gender !!\n");
                goto checkGender;
            }
        }

        //----------------------------------------

        printf("\nEnter Passsword: ");
        scanf("%s", newuser.password);

        printf("\nEnter Address: ");
        scanf("%s", newuser.address);

        printf("\nEnter Phone Number: ");
        scanf("%d", &newuser.phoneno);

        // printf("\nEnter District: ");
        // scanf("%s", newuser.district);

        //----------------------------------------

    checkDistrict:
        printf("\nEnter District:");
        scanf(" %[^\n]s", newuser.district);
        for (int i = 0; newuser.district[i] != '\0'; i++)
        {
            if (!isalpha(newuser.district[i]))
            {
                printf("\nPlease Enter Valid District !!\n");
                goto checkDistrict;
            }
        }

        //----------------------------------------

        // printf("\nEnter Constituency: ");
        // scanf("%s", newuser.constituency);

        //----------------------------------------

    checkConstituency:
        printf("\nEnter Constituency:");
        scanf(" %[^\n]s", newuser.constituency);
        for (int i = 0; newuser.constituency[i] != '\0'; i++)
        {
            if (!isalpha(newuser.constituency[i]))
            {
                printf("\nPlease Enter Valid Constituency !!\n");
                goto checkConstituency;
            }
        }

        //----------------------------------------

        strcpy(newuser.VoterId, "");
        fwrite(&newuser, sizeof(newuser), 1, userDetails);
        printf("\n Registration successfull  !!! ");
        printf("\n Your User id is %d ", newuser.UserId);
    label:
        fclose(userDetails);
    }
}

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
                    printf("Successfully Requested for VoterId");
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
                    printf("Your VoterId is already generated !!!");
                }
            }
        }
        fclose(userDetails);
    }
}
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
            printf("\nYour VoterId is %s", newUser.VoterId);
            break;
        }
    }
    fclose(user);
}

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

        printf("\n=======================Election Details======================\n");
        printf("\nName\tElectionDate\tVoting Time\t   District\tConstituency\n");

        while (fread(&e, sizeof(e), 1, electionfile))
        {
            if ((strcmp(e.constituency, UserConstituency) == 0) && (strcmp(e.district, UserDistrict) == 0))
            {
                printf("%s\t%s\t%s  %s\t%s\n", e.name, e.date, e.time, e.district, e.constituency);
            }
        }
    }
}
void vote()
{
    char electionName[50];
    struct Candidate candidate;
    struct Election election;

    int candidateId = 0;
label:
    printf("\nEnter the Election Name to proceed the voting process : ");
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
                printf("\nCandidate ID\t\tCandidate Name\t\tParty Name\n");

                while (fread(&candidate, sizeof(candidate), 1, candidatefile))
                {
                    if (strcmp(candidate.electname, electionName) == 0)
                    {
                        printf("\n%d\t\t%s\t\t%s", candidate.candidateId, candidate.name, candidate.partyname);
                    }
                }
                rewind(candidatefile);
            candidatelabel:
                printf("\nPlease enter the CandidateId to vote for that Candidate : ");
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

                        printf("Congratulation You have Voted successfully");
                        break;
                    }
                }
                if (flag == 0)
                {
                    printf("\nPlease enter Valid candidate Id from above list\n");
                    goto candidatelabel;
                }
                fclose(candidatefile);
                break;
            }
        }

        if (present == 0)
        {
            printf("\nplease enter valid election name from above list of elections");
            goto label;
        }
    }
}
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
                printf("You Cant Vote as you dont have voterId\n");
            }
            else
            {
                if (strcmp(user.Voted, "true") == 0)
                {
                    printf("Already Voted");
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
        printf("\nEnter date of Election \n");
        scanf("%s", date);
        FILE *electionfile = fopen("election.csv", "r");
        if (electionfile == NULL)
        {
            perror("Can't Open file");
        }
        else
        {
            printf("\n=======================Election Details======================\n");
            printf("\nName\tElectionDate\tVoting Time\t   District\tConstituency\n");

            while (fread(&election, sizeof(election), 1, electionfile))
            {
                if (strcmp(election.date, date) == 0 && strcmp(election.constituency, userConstituency) == 0)
                {
                    strcpy(electionName, election.name);
                    printf("%s\t%s\t%s  %s\t%s\n", election.name, election.date, election.time, election.district, election.constituency);
                }
            }
            fclose(electionfile);

            FILE *candidatefile = fopen("candidate.csv", "r");
            if (candidatefile == NULL)
            {
                perror("Can't Open file");
            }
            else
            {
                printf("\n=======================Candidate Details======================\n");
                printf("\nCandidate ID  Candidate Name   Election Name  Party Name  District    Constituency  Number Of Votes");
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
                        printf("\n%d %s %s %s %s %s %d", candidate.candidateId, candidate.name, candidate.electname, candidate.partyname, candidate.district, candidate.constituency, candidate.voteCount);
                        k++;
                        rewind(candidatefile);
                    }
                }

                fclose(candidatefile);
            }
        }
    }
    if (ch == 2)
    {
        char constituency[30];
        printf("\nEnter Constituency of Election \n");
        scanf("%s", constituency);

        FILE *electionfile = fopen("election.csv", "r");

        if (electionfile == NULL)
        {
            perror("Can't Open file");
        }
        else
        {
            printf("\n=======================Election Details======================\n");
            printf("\nName\tElectionDate\tVoting Time\t   District\tConstituency\n");

            while (fread(&election, sizeof(election), 1, electionfile))
            {
                if (strcmp(election.constituency, constituency) == 0)
                {
                    strcpy(electionName, election.name);
                    printf("%s\t%s\t%s  %s\t%s\n", election.name, election.date, election.time, election.district, election.constituency);
                }
            }
            fclose(electionfile);

            FILE *candidatefile = fopen("candidate.csv", "r");
            if (candidatefile == NULL)
            {
                perror("Can't Open file");
            }
            else
            {
                // printf("\n=======================Candidate Details======================\n");
                // printf("\nCandidate ID  Candidate Name   Election Name  Party Name  District    Constituency  Number Of Votes");
                // while (fread(&candidate, sizeof(candidate), 1, candidatefile))
                // {
                //     if (strcmp(candidate.electname, electionName) == 0)
                //     {
                //         printf("\n%d %s %s %s %s %s %d", candidate.candidateId, candidate.name, candidate.electname, candidate.partyname, candidate.district, candidate.constituency, candidate.voteCount);
                //     }
                // }
                // fclose(candidatefile);
                printf("\n=======================Candidate Details======================\n");
                printf("\nCandidate ID  Candidate Name   Election Name  Party Name  District    Constituency  Number Of Votes");
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
                        printf("\n%d %s %s %s %s %s %d", candidate.candidateId, candidate.name, candidate.electname, candidate.partyname, candidate.district, candidate.constituency, candidate.voteCount);
                        k++;
                        rewind(candidatefile);
                    }
                }

                fclose(candidatefile);
            }
        }
    }
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
