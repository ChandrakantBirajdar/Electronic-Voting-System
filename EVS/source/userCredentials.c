#include"../header/header.h"


void userchoice()
{
   int choice = 0;

    char ch[10];

    while (choice != 3)
    {
        

        printf(COLOR_BLUE"|------------------------------------------------------------------------|\n"COLOR_RESET);
        printf(COLOR_BLUE"|"COLOR_MAGENTA COLOR_BOLD"                        Please select an option:                                     "COLOR_RESET COLOR_BLUE "|\n"COLOR_RESET);
        printf(COLOR_BLUE"|------------------------------------------------------------------------|\n"COLOR_RESET);
        printf(COLOR_BOLD"|Please select an option:                                                | \n"COLOR_RESET);
        printf("%-3s%-70s%-30s\n","|", " 1.  User Login","|");
        printf("%-3s%-70s%-30s\n","|", " 2.  User Registration","|");
        printf("%-3s%-70s%-30s\n","|", " 3.  Back to Menu","|");
        printf("|------------------------------------------------------------------------|\n");
        printf("\n");
        printf(COLOR_BOLD" Enter The Choice:"COLOR_RESET);
        scanf("%s", ch);
        choice = atoi(ch);
        switch (choice)
        {
        case 1:
            userLogin();
            
            break;
        case 2:
            userRegistration();
            break;
        case 3:
            break;
        default:
            printf("\033[0;31m\n");
            printf(" Invalid Data Enterd Please Enter Valid choise !!! \n");
            printf("\033[0;37m\n");
        }
    }
}


//
void userLogin()
{
    struct User newUser;
    int UserId;
    char password[20];

    int present = 0;
    printf("Enter UserId: ");
    scanf("%d",&UserId);
    printf("Enter Password: ");
    scanf("%s",password);

    FILE *user = fopen("UserDetails.csv","r");
     if (user == NULL)
    {
        perror("Error in file opening\n");
    }
    else
    {
        while(fread(&newUser,sizeof(newUser),1,user))
        {
            if( newUser.UserId==UserId && strcmp(newUser.password,password)==0)
            {
                present=1;
                userMenu(UserId);
                fclose(user);
            }
        }
        
        if(present==0)
        {
            printf("Invalid Credentials OR Seems like you haven't registered to EVS  \n");
            printf("To login to EVS  please register to EVS\n");
            fclose(user);
        }

        fclose(user);

    }
}


//

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
        printf(COLOR_BOLD"\nEnter First Name:");
        scanf(" %[^\n]s", newuser.firstname);
        for (int i = 0; newuser.firstname[i] != '\0'; i++)
        {
            if (!isalpha(newuser.firstname[i]))
            {
                printf(COLOR_RED"\nPlease Enter Valid First Name !!\n"COLOR_RESET);
                goto checkFirstName;
            }
        }

        //----------------------------------------

        // printf("\nEnter LastName: ");
        // scanf("%s", newuser.lastname);

        //----------------------------------------

    checkLastName:
        printf(COLOR_BOLD"\nEnter Last Name:");
        scanf(" %[^\n]s", newuser.lastname);
        for (int i = 0; newuser.lastname[i] != '\0'; i++)
        {
            if (!isalpha(newuser.lastname[i]))
            {
                printf(COLOR_RED"\nPlease Enter Valid Last Name !!\n"COLOR_RESET);
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
            printf(COLOR_BOLD"\nEnter DOB  in format   [dd/mm/yyyy]: ");
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
                         
                
                        break;
                    }
                    else
                    {
                        printf(COLOR_RED"\nInvalid Date...Please Enter right date\n"COLOR_RESET);
                    }
                }
                else
                {
                    printf(COLOR_BOLD"\nInvalid Date...Please Enter right date"COLOR_RESET);
                }
            }
            else
            {
                printf(COLOR_BOLD"\nInvalid Date...Please Enter right date"COLOR_RESET);
            }
        }
        //
        if (isValidAge(day, month, year) < 18)
        {
            printf(COLOR_RED"\nYou are not Eligible for Voting as your age is less than 18\n"COLOR_RESET);
            printf("\n");
            goto label;
        }
        int yearr = getCurrentdate();
        newuser.age = yearr - newuser.year;
        printf(COLOR_BOLD"\nAge: %d ", newuser.age);
        printf("\n");
    checkGender:
        printf(COLOR_BOLD"\nEnter Gender:");
        scanf(" %[^\n]s", newuser.gender);
        for (int i = 0; newuser.gender[i] != '\0'; i++)
        {
            if (!isalpha(newuser.gender[i]))
            {
                printf(COLOR_RED"\nPlease Enter Valid Gender !!\n"COLOR_RESET);
                goto checkGender;
            }
        }

        //----------------------------------------

        printf(COLOR_BOLD"\nEnter Passsword: ");
        scanf("%s", newuser.password);

        printf(COLOR_BOLD"\nEnter Address: ");
        scanf("%s", newuser.address);

        // printf("\nEnter Phone Number: ");
        // scanf("%d", &newuser.phoneno);

        while(1)
		{
			i=0;
			digitCount=0;
			flag1=0;
    			printf(COLOR_BOLD"\nEnter Phone Number:");
    			scanf(" %[^\n]s",newuser.phoneno);
			while(newuser.phoneno[i]!='\0')
			{
				if(isdigit(newuser.phoneno[i]))
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


        // printf("\nEnter District: ");
        // scanf("%s", newuser.district);

        //----------------------------------------

    checkDistrict:
        printf(COLOR_BOLD"\nEnter District:");
        scanf(" %[^\n]s", newuser.district);
        for (int i = 0; newuser.district[i] != '\0'; i++)
        {
            if (!isalpha(newuser.district[i]))
            {
                printf(COLOR_RED"\nPlease Enter Valid District !!\n"COLOR_RESET);
                goto checkDistrict;
            }
        }

        //----------------------------------------

        // printf("\nEnter Constituency: ");
        // scanf("%s", newuser.constituency);

        //----------------------------------------

    checkConstituency:
        printf(COLOR_BOLD"\nEnter Constituency:");
        scanf(" %[^\n]s", newuser.constituency);
        for (int i = 0; newuser.constituency[i] != '\0'; i++)
        {
            if (!isalpha(newuser.constituency[i]))
            {
                printf(COLOR_RED"\nPlease Enter Valid Constituency !!\n"COLOR_RESET);
                goto checkConstituency;
            }
        }

        //----------------------------------------

        strcpy(newuser.VoterId, "");
        fwrite(&newuser, sizeof(newuser), 1, userDetails);
        printf(COLOR_GREEN"\n Registration successfull  !!! \n"COLOR_RESET);
        
        printf("\n Your User id is "COLOR_GREEN "%d ", newuser.UserId);
        printf("\n");
    label:
        fclose(userDetails);
    }
}