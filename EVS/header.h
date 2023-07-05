#pragma once
#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include<time.h>

struct User{
    int UserId;
    char firstname[50];
    char lastname[50];
    char password[50];
    int day, mon, year;
    char dob[11];
    int age;
    int phoneno;
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

void getAllDetails();
int isLeapYear(int year);
int isValidDate(int day,int month,int year);
int isValidAge(int birth_day,int birth_month,int birth_year);   

void userLogin();
void userchoice();
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