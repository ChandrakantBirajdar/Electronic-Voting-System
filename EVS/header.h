#pragma once
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

struct User{
    int UserId;
    char VoterId[50];
    char firstname[50];
    char lastname[50];
    char password[50];
    int day, mon, year;
    int age;
    int phoneno;
    char gender[50];
    char address[50];
    char constituency[50];
    char district[50];
};

struct Request{
    int UserId;
    char status[50];
};

void userMenu(int UserId);
void adminMenu();
void userRegistration();
void requsetVoterId(int UserId);
void viewVoterId(int userId);
void viewElectionSchedules();
void castVotes();
void viewElectionResult();
void officerMenu();
void viewVoterRequest();
void generateVoterId(int currentUserId);
void userLogin();