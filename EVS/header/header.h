#pragma once
#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include<time.h>

#define COLOR_RESET "\033[0m"
#define COLOR_BOLD "\033[1m"
#define COLOR_RED "\033[31m"
#define COLOR_GREEN "\033[32m"
#define COLOR_YELLOW "\033[33m"
#define COLOR_BLUE "\033[34m"
#define COLOR_MAGENTA "\033[35m"
#define COLOR_CYAN "\033[36m"





struct User{
    int UserId;
    char firstname[50];
    char lastname[50];
    char password[50];
    int day, mon, year;
    char dob[11];
    int age;
    char phoneno[50];
    char gender[50];
    char address[50];
    char constituency[50];
    char district[50];
    char VoterId[50];
    char Voted[10];
};

struct Request{
    int UserId;
    char status[50];
};

struct Election  {
    char name[20];
	char date[20];
	char time[25];
	char district[20];
	char constituency[20];
};


struct Party {
	char name[20];
	char leader[20];
	char symbol[20];
};


struct Candidate {
	int candidateId;
	char name[20];
	char dob[11];
	char electname[20];
	char partyname[20];
	char district[20];
	char constituency[20];
	char address[20];
	char phone[20];
	char email[20];
    int voteCount;
};
int getCurrentdate();
void updateBatchId(int batchId);
int getBatchId();
void getAllDetails();
int isLeapYear(int year);
int isValidDate(int day,int month,int year);
int isValidAge(int birth_day,int birth_month,int birth_year);   

// void userLogin();
// void userchoice();
 void setUserId();
void adminLogin();
void ElectorOfficerLogin();

void addElection();
void addParty();
void addCandidate();
void viewElection();
void viewParty();
void viewCandidate();



void userMenu(int UserId);
void adminMenu();
void userRegistration();
void requsetVoterId(int UserId);
void viewVoterId(int userId);
// void viewElectionSchedules();
void viewElectionSchedules(int userId);
void castVotes(int currentUser);
void viewElectionResult(int currentUser);
void officerMenu();
void viewVoterRequest();
void generateVoterId(int currentUserId);
void userLogin();
void userchoice();
int validElectionDate(int day,int month,int year);