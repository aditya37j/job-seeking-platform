#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

char generateRandomChar()
{
    return 'a' + rand() % 26; 
}

int generate_random_number()
{
    return 100 + rand() % 901; 
}

void generate_unique_id(char *id) {
    char letter = generateRandomChar();
    int number = generate_random_number();
    
    sprintf(id, "%c%d", letter, number);
}


void generateRandomPassword(char password[])
{
    for (int i = 0; i < 5; i++)
      {
        password[i] = generateRandomChar();
    }
    password[5] = '\0'; 
}

typedef struct
{
    char id[7];
    char password[6];
    char name[100];
    char email[100];
    char bachelors[100];
    char masters[100];
    char certification[100];
    char skillstr[100];
    int experience;
    char bio[1000];
    
}Seeker;

void registerUser(FILE *file, Seeker user)
{
    fprintf(file, "%s,%s,%s,%s,%s,%s,%s,%s,%d,%s\n", user.id, user.password, user.name, user.email,user.bachelors,user.masters,user.certification,user.skillstr,user.experience,user.bio);

  
}

typedef struct
{
    char id[7];
    char password[6];
    char companyName[100];
    char jobname[100];
    int workExperience;
    char location[100];
    int ctc;
} Recruiter;

void registerRecruiter(FILE *file, Recruiter recruiter)
{
    fprintf(file, "%s,%s,%s,%s,%d,%s,%d\n", recruiter.id, recruiter.password,recruiter.companyName,recruiter.jobname, recruiter.workExperience, recruiter.location,recruiter.ctc);
}



typedef struct
{
char id[7];
char password[6];
char name[100];
char jobname[100];
int workExperience;
char location[100];
int ctc;
char compconst[1000];

}seekerreq;

typedef struct
{
char id[7];
char password[6];
char companyname[1000];
char bachelors[100];
char masters[100];
char certification[100];
char skillstr[100];

int experience;
char compconst[100];

}recruiterexp;

typedef struct
{
char recruiterid[7];
Seeker seekers[10];
int numseekers;

}recruiterfinal;
recruiterfinal recruiterData[100];

typedef struct
{
  char seekerid[7];
  Recruiter recruiters[10];
  int numrecruiters;
}seekerfinal;
seekerfinal seekerData[100];

int bioreader(char* paragraph)
{
  // printf("BIOOO-%s",paragraph);
  // printf("COPIED-%s",localstr);
  char localstr[1000];
  strcpy(localstr,paragraph);
    //printf("BIOOO-%s",paragraph);
  //printf("COPIED-%s",localstr);
  int score = 0;
 char* token = strtok(localstr, " .,:;!?\n");
 char arr[40][20] = {"creative", "diligent", 
"dependable","energetic","results-oriented","strategic","ambitious",
 
"collaborative","honest","organized","innovative","inquisitive","upbeat","deadline-driven"
 ,"confident","methodical","communicative","optimistic","passionate","self-reliant","analytical","independent",
 "flexible","level-headed","quick-thinking","artistic","openminded","decisive","progressive","conscientious",
 
"bold","transparent","responsive","loyal","consistent","enthusiastic",
"People-person","Empathetic"};
 while (token != NULL) 
 {
   
 for (int i = 0; i < 40; i++)
   {
     // printf("INSIDE THE LOOP ");
 if (strcmp(token,arr[i]) == 0)
 {
 score++;
 }
 }
 token = strtok(NULL, " .,:;!?\n");
 }
 if(score>10){
 score=10;
 }
 return score;
}

void store_seeker_data(seekerfinal seekerData[], int numSeekers)
{
    FILE *outputFile = fopen("seeker_data.csv", "a+");
    if (outputFile == NULL) 
    {
        printf("Error opening output file.\n");
        return;
    }

    
    for (int i = 0; i < numSeekers; i++) {
        seekerfinal currentSeeker = seekerData[i];
 
        for (int j = 0; j < currentSeeker.numrecruiters; j++) 
        {
            Recruiter currentrecruiter = currentSeeker.recruiters[j];
            fprintf(outputFile, "%s,%s,%s,%s,%s,%d,%s,%d\n",
                    currentSeeker.seekerid,
                    currentrecruiter.id,
                    currentrecruiter.password,
                    currentrecruiter.companyName,
                    currentrecruiter.jobname,
                    currentrecruiter.workExperience,
                    currentrecruiter.location,
                    currentrecruiter.ctc);
        }
    }

    fclose(outputFile);
}


void store_recruiter_data(recruiterfinal recruiterData[], int numRecruiters)
{
    FILE *outputFile = fopen("recruiter_data.csv", "a+");
    if (outputFile == NULL) 
    {
        printf("Error opening output file.\n");
        return;
    }

    
    for (int i = 0; i < numRecruiters; i++) {
        recruiterfinal currentRecruiter = recruiterData[i];

        for (int j = 0; j < currentRecruiter.numseekers; j++) {
            Seeker currentseeker = currentRecruiter.seekers[j];
            fprintf(outputFile, "%s,%s,%s,%s,%s,%s,%s,%s,%s,%d,%s\n",
                    currentRecruiter.recruiterid,
                    currentseeker.id,
                    currentseeker.password,
                    currentseeker.name,
                    currentseeker.email,
                    currentseeker.bachelors,
                    currentseeker.masters,
                    currentseeker.certification,
                    currentseeker.skillstr,
                    currentseeker.experience,
                    currentseeker.bio);
        }
    }

    fclose(outputFile);
}

void store_fieldsseeker(seekerreq seeker, Recruiter recruiter, seekerfinal seekerData[], int numSeekers) 
{
    int index = -1;
    
    for (int i = 0; i < numSeekers; i++) 
    {
        if (strcmp(seekerData[i].seekerid, seeker.id) == 0) 
        {
            index = i;
            break;
        }
    }

    
    if (index == -1)
    {
       
      index = numSeekers;
   
     
      strcpy(seekerData[index].seekerid, seeker.id);
        seekerData[index].numrecruiters = 0;
        (numSeekers)++;
        
    }
  if (seekerData[index].numrecruiters < 100) 
    { 
      seekerfinal  currentseeker= seekerData[index];
      seekerData[index].recruiters[currentseeker.numrecruiters];
      strcpy(seekerData[index].recruiters[currentseeker.numrecruiters].id,recruiter.id);
      
      strcpy(seekerData[index].recruiters[currentseeker.numrecruiters].password,recruiter.password);
    
      strcpy(seekerData[index].recruiters[currentseeker.numrecruiters].companyName,recruiter.companyName);
      strcpy(seekerData[index].recruiters[currentseeker.numrecruiters].jobname,recruiter.jobname);
      
seekerData[index].recruiters[currentseeker.numrecruiters].workExperience=recruiter.workExperience;  
      
strcpy(seekerData[index].recruiters[currentseeker.numrecruiters].location,recruiter.location);
      seekerData[index].recruiters[currentseeker.numrecruiters].ctc=recruiter.ctc;

      seekerData[index].numrecruiters++;
          
}
    
    else 
    {
        printf("Maximum number of seekers reached for recruiter ID: %s\n", seeker.id);
    }
  
  store_seeker_data(seekerData,numSeekers);
}


void store_fields(recruiterexp recruiter, Seeker seeker, recruiterfinal recruiterData[], int numRecruiters) 
{
    int index = -1;
    
    for (int i = 0; i < numRecruiters; i++) 
    {
        if (strcmp(recruiterData[i].recruiterid, recruiter.id) == 0) 
        {
            index = i;
            break;
        }
    }

    
    if (index == -1)
    {
       
      index = numRecruiters;
      strcpy(recruiterData[index].recruiterid, recruiter.id);
        recruiterData[index].numseekers = 0;
        (numRecruiters)++;
        
    }
  if (recruiterData[index].numseekers < 100) 
    { 
      recruiterfinal  currentrecruiter= recruiterData[index];
      recruiterData[index].seekers[currentrecruiter.numseekers];
      strcpy(recruiterData[index].seekers[currentrecruiter.numseekers].id,seeker.id);
      strcpy(recruiterData[index].seekers[currentrecruiter.numseekers].password,seeker.password);
      strcpy(recruiterData[index].seekers[currentrecruiter.numseekers].name,seeker.name);
      strcpy(recruiterData[index].seekers[currentrecruiter.numseekers].email,seeker.email);
      
strcpy(recruiterData[index].seekers[currentrecruiter.numseekers].bachelors,seeker.bachelors);

strcpy(recruiterData[index].seekers[currentrecruiter.numseekers].masters,seeker.masters);

strcpy(recruiterData[index].seekers[currentrecruiter.numseekers].certification,seeker.certification);

strcpy(recruiterData[index].seekers[currentrecruiter.numseekers].skillstr,seeker.skillstr);
           
      recruiterData[index].seekers[currentrecruiter.numseekers].experience=seeker.experience;

      strcpy(recruiterData[index].seekers[currentrecruiter.numseekers].bio,seeker.bio);
      recruiterData[index].numseekers++;
           
}
    
    else 
    {
        printf("Maximum number of seekers reached for recruiter ID: %s\n", recruiter.id);
    }
  
  store_recruiter_data(recruiterData,numRecruiters);
}


void loginSeeker(seekerreq login)
{
  FILE *fieldfile=fopen("seeker_fields","a+");
  
  fprintf(fieldfile,"%s,%s,%s,%s,%d,%s,%d,%s\n",login.id,login.password,login.name,login.jobname,login.workExperience,login.location,login.ctc,login.compconst);
fclose(fieldfile);
}

void loginrecruiter(recruiterexp login)
{
  FILE *expfile=fopen("recruiter_exp","a+");
  fprintf(expfile,"%s,%s,%s,%s,%s,%s,%s,%d,%s\n",login.id,login.password,login.companyname,login.bachelors,login.masters,login.certification,login.skillstr,login.experience,login.compconst);
fclose(expfile);
}


void find_seeker()
{
 
  FILE *recruitersFile = fopen("recruiter_exp","r");
   FILE *file;
    file = fopen("seekers1.csv", "r");
    if (file == NULL || recruitersFile== NULL)
    {
        printf("Error opening file.\n");
        
    }
Seeker seeker;
recruiterexp recruiter;
  

  int numRecruiters=0;
  
   while (fscanf(recruitersFile,"%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%d,%[^\n]\n", recruiter.id,recruiter.password,recruiter.companyname,recruiter.bachelors,recruiter.masters,recruiter.certification,recruiter.skillstr,&recruiter.experience,recruiter.compconst)==9)
     
  {
    
    char skills[4][20];

  sscanf(recruiter.skillstr,"%s %s %s %s",skills[0],skills[1],skills[2],skills[3]);
    fseek(file,0,SEEK_SET);
char line[1000];
    int lineNo=0;
    while (fgets(line,1000,file))
      {
        float score=0;
        float total=0;
        //printf("LINE-%s\n",line);
       lineNo++;
         char fields[10][1000];
         int i = 0;
         char* token = strtok(line, ",");
          while( token != NULL ) 
          {
            strcpy(fields[i++], token);
            
            token = strtok(NULL, ",");
            
          }
          for ( int j=0; j< i; j++ )
            { 
              
              if (strcmp(fields[j],recruiter.compconst)==0)
              {
                
                for (int j=0;j<i;j++)
                  {

                  
                    printf("%s\n",fields[j]);
                    
                  }
                strcpy(seeker.id,fields[0]);
                strcpy(seeker.password,fields[1]);
                strcpy(seeker.name,fields[2]);
                strcpy(seeker.email,fields[3]);
                strcpy(seeker.bachelors,fields[4]);
                strcpy(seeker.masters,fields[5]);
                strcpy(seeker.certification,fields[6]);
                strcpy(seeker.skillstr,fields[7]);
                seeker.experience= atoi(fields[8]);
                strcpy(seeker.bio,fields[9]);
                    
                char skillseeker[4][20];
                sscanf(fields[7],"%s %s %s %s",skillseeker[0],skillseeker[1],skillseeker[2],skillseeker[3]);
                char skillrecruiter[4][20];
                sscanf(recruiter.skillstr,"%s %s %s %s",skillrecruiter[0],skillrecruiter[1],skillrecruiter[2],skillrecruiter[3]);
                for (int i=0;i<4;i++)
                  {
                    for (int j=0;j<4;j++)
                      {
                        if (strcmp(skillseeker[j],skillrecruiter[i])==0)
                        {
                          
                          if (i==0) score=score+4;
                          else if (i==1) score=score+3;
                          else if (i==2) score=score+2;
                          else if (i==3) score=score+1;
                          
                          
                        }
                        
                      } 
                  }total=total+9;
                
                 if (strcmp(recruiter.bachelors,"n")==0 && strlen(seeker.bachelors)>1)
                {
                  score=score+3;
                  
                    }
               
                 if(strcmp(seeker.bachelors,"n")==0 && strlen(recruiter.bachelors)>1)
                {
                  score=score-3;
                  
                }
                if (strcmp(recruiter.bachelors,seeker.bachelors)==0)
                {
                  if (strcmp(recruiter.bachelors,"n")==0 && strcmp(seeker.bachelors,"n")==0)
                  {
                    score+=0;
                  } 
                  else{
                  score=score+5;}
                }
                
                total=total+5;

                if (strcmp(recruiter.masters,"n")==0 && strlen(seeker.masters)>1)
                {
                  score=score+15;
                  
                }
                
                 if(strcmp(seeker.masters,"n")==0 && strlen(recruiter.masters)>1)
                {
                  score=score-12;
                  
                }
                if (strcmp(recruiter.masters,seeker.masters)==0)
                {
                  if (strcmp(recruiter.masters,"n")==0 && strcmp(seeker.masters,"n")==0)
                  {
                    score+=0;
                  } 
                  else{
                  score=score+10;}
                }
                
                total=total+10;
                if (seeker.experience>=recruiter.experience)
                {
                  score=score+5;
                  if(seeker.experience-recruiter.experience>=4 && seeker.experience-recruiter.experience<=8)
                  {
                    score=score+2;
                  
                  }
                  if(seeker.experience-recruiter.experience>=9 && seeker.experience-recruiter.experience<=13)
                  {
                    score=score+5;
                    
                  }
                }
                  total=total+5;
                
                if   
                (strcmp(seeker.certification,recruiter.certification)==0)
                {
                  score=score+5;
                  
                }
                total=total+5;
                //printf("BIO BEFORE CALLING: %s\n",seeker.bio);
                score=score+bioreader(seeker.bio);
                total=total+5;
                
              
                printf("score== %f\n",score);
                printf("total== %f\n",total);
                if (((score/total)*100) >=70)
                {
                  
                  store_fields(recruiter, seeker, recruiterData,     numRecruiters);
                  printf("accepted\n");
                }
                
              }
            
          }

    }

}
  fclose(file);
}


void find_recruiter()
{
  
  FILE *seekersFile = fopen("seeker_fields","r");
   FILE *file = fopen("recruiters.csv", "r");
    if (file == NULL || seekersFile==NULL)
    {
        printf("Error opening file.\n");
        
    }
seekerreq seeker;
  Recruiter recruiter;

  int numSeekers=0;
  while (fscanf(seekersFile,"%[^,],%[^,],%[^,],%[^,],%d,%[^,],%d,%[^\n]\n",seeker.id,seeker.password,seeker.name,seeker.jobname,&seeker.workExperience,seeker.location,&seeker.ctc,seeker.compconst)==8)
      {
        
 // printf("%d seeker id-%s %s\n",seeker.ctc,seeker.id,seeker.location);
        fseek(file,0,SEEK_SET);
char line[1000];
    int lineNo=0;
    while (fgets(line,1000,file))
      {
        
        float score=0;
        float total=0;
       lineNo++;
         char fields[10][20];
         int i = 0;
         char* token = strtok(line, ",");
          while( token != NULL ) 
          {
            strcpy(fields[i++], token);
            
            token = strtok(NULL, ",");
            
           
          }
          for ( int j=0; j< i; j++ )
            { 
              
              if (strcmp(fields[j],seeker.compconst)==0)
              {
                
                for (int j=0;j<i;j++)
                  {
                    printf("%s\n",fields[j]);
                    
                  }
                strcpy(recruiter.id,fields[0]);
                strcpy(recruiter.password,fields[1]);
                strcpy(recruiter.companyName,fields[2]);
                strcpy(recruiter.jobname,fields[3]);
                recruiter.workExperience = atoi(fields[4]);
                strcpy(recruiter.location,fields[5]);
                recruiter.ctc= atoi(fields[6]);

                if (atoi(fields[4])>=seeker.workExperience)
                {
                  score=score-2;
                }
                if (seeker.workExperience>=recruiter.workExperience)
                {score=score+5;
                  if(seeker.workExperience-recruiter.workExperience>=4 && seeker.workExperience-recruiter.workExperience<=8)
                  {
                    score=score+2;
                  
                  }
                  if(seeker.workExperience-recruiter.workExperience>=9 && seeker.workExperience-recruiter.workExperience<=13)
                  {
                    score=score-2;
                    
                  }
                }
                  total=total+5;
                if (strcmp(seeker.jobname,recruiter.jobname)==0)
                {
                  score=score+5;
                }total=total+5;
                
                if (strcmp(seeker.location,fields[5])==0)
                {
                  score=score+5;
                }total=total+5;
                if (atoi(fields[6])>=seeker.ctc)
                {
                  score=score+5;
                  
                }
                else if (atoi(fields[6])<=seeker.ctc)
                 {
                   score=score-2;
                 }
                  total=total+5;
                printf("score==%f\n",score);
                printf("total== %f\n",total);
                float perc;
                perc=((score)/(total));
                printf("perc== %f\n",perc);
                if ((perc*100)>=50)
                {
                  printf("accepted\n");
                  store_fieldsseeker(seeker,recruiter,seekerData,numSeekers);
                }
}
}
}
      }
  fclose(file);
}



void printRecruiterData(const char recruiterID[]) 
{
    FILE *file = fopen("recruiter_data.csv", "r");
    if (file == NULL) 
    {
        printf("Error opening the file.\n");
        return;
    }

    char line[10000];
    int found = 0;

    while (fgets(line, sizeof(line), file))
      {
        // char* id = strtok(line, ",");
        if (strstr(line, recruiterID)!= NULL) 
        {
            found = 1;
            printf("Recruiter Data: %s\n", line);
        }
    }

    fclose(file);

    if (!found)
    {
        printf("Recruiter ID not found.\n");
    }
}

void printSeekerData(const char seekerID[]) 
{
    FILE *file = fopen("seeker_data.csv", "r");
    if (file == NULL) 
    {
        printf("Error opening the file.\n");
        return;
    }

    char line[10000];
    int found = 0;

    while (fgets(line, sizeof(line), file))
      {
        // char* id = strtok(line, ",");
        if (strstr(line, seekerID)!= NULL) 
        {
            found = 1;
            printf("Seeker Data: %s\n", line);
        }
    }

    fclose(file);

    if (!found)
    {
        printf("Seeker ID not found.\n");
    }
}


int main() 
{
  // printf("HALLO THERE\n ");
srand(time(NULL)); 
    FILE *file;
    file = fopen("seekers1.csv", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return 0;
    }

   char unique_id[5];
  char password[6];
  printf("REGISTER THE RECRUITERS: \n");
    FILE *file2 = fopen("recruiters.csv", "a+");
    if (file2 == NULL)
    {
        printf("Error opening the file.\n");
        return 1;
    }
    
    int numRecruiters;
    printf("Enter the number of recruiters to register: ");
    scanf("%d", &numRecruiters);
    
    Recruiter recruiter;
    fseek(file2, 0, SEEK_END);
    
  
  
    for (int i =0 ; i < numRecruiters; i++)
      {
        srand(time(NULL)); 
       
        generate_unique_id(recruiter.id);
        generateRandomPassword(recruiter.password);
        
        printf("\nRecruiter ID: %s\n", recruiter.id);
        printf("Recruiter password: %s\n",recruiter.password);
        printf("Enter Company Name: ");
        scanf(" %[^\n]", recruiter.companyName);
        
        printf("Enter Job Name: ");
        scanf("%s", recruiter.jobname);
        getchar();
        printf("Enter Work Experience expected: ");
        scanf("%d",&recruiter.workExperience);
        
        
  
        printf("Enter Location of the company: ");
        scanf(" %[^\n]", recruiter.location);
     

        printf("Enter the ctc: ");
  
        scanf("%d",&recruiter.ctc);
        
        registerRecruiter(file2, recruiter);
    }

    
    fclose(file2);
    


printf("REGISTER THE SEEKERS: \n");    

    FILE *file1 = fopen("seekers1.csv", "a+");
    if (file1 == NULL)
    {
        printf("Error opening the file.\n");
        return 1;
    }
    
    int numInputs;
    printf("Enter the number of seekers to register: ");
    scanf("%d", &numInputs);
    
    Seeker user;
    
    
    for (int i = 0; i < numInputs; i++) 
    {
      srand(time(NULL)); 
   
       generateRandomPassword(user.password);
        generate_unique_id(user.id);
        printf("\nUser ID: %s\n", user.id); 
        printf("Password: %s \n", user.password);
        printf("Enter name: ");
        scanf(" %[^\n]", user.name);
      
        printf("Enter your email: ");
        getchar();
        scanf("%[^\n]",user.email);
        scanf("%[^\n]",user.email);
      
        printf("Enter bachelors degree(enter n if no degree): ");
        scanf(" %[^\n]", user.bachelors);
        printf("Enter masters degree(enter n if no degree): ");
        scanf(" %[^\n]", user.masters);
        printf("Enter certification : ");
        scanf(" %[^\n]",user.certification);
        printf("Please enter four known skills: ");
        char skillseeker[4][20];
        for (int i=0;i<4;i++)
          {
            scanf("%s",skillseeker[i]);
          }
        sprintf(user.skillstr,"%s %s %s %s",skillseeker[0],skillseeker[1],skillseeker[2],skillseeker[3]);
        printf("Enter the work experience: ");
        scanf("%d",&user.experience);
      
        printf("Enter the bio: ");
      getchar();
        scanf("%[^\n]",user.bio);
        scanf("%[^\n]",user.bio);
        
        registerUser(file1, user);
    }
    
    
    
    fclose(file1);

  
   char fresh;char user1;char nextopt;char check;
  printf("REGISTERED USER?\n");
  printf("ENTER 'Y' IF YES AND 'N' IF NO.\n");
  scanf("%c",&fresh);
  scanf("%c",&fresh);
  printf("ENTER 'S' IF JOB SEEKER AND ENTER 'A' IF JOB ACQUISTIONER.\n");
  scanf("%c",&user1);
  scanf("%c",&user1); 
  fresh=toupper(fresh);
  user1=toupper(user1);
  printf("Would u like to add criteria or search for jobs?\n");
  printf("If criteria enter 'C' else enter 'J'.\n");
  scanf("%c",&nextopt);
  scanf("%c",&nextopt);
  nextopt=toupper(nextopt);

  if (fresh=='Y')
  {
    if (user1=='S')
    {
      if (nextopt=='C')
      {
            char userID[7];
            char userPassword[6];
            printf("Enter your User ID:");
          
            scanf("%s",userID);
            printf("Enter your Password:");
        
            scanf("%s",userPassword);

            FILE *seekersFile = fopen("seekers1.csv", "r");
            if (seekersFile == NULL)
            {
                printf("Error opening the file.\n");
                return 1;
            }
      
      Seeker currentUser;
      int find=0;
fseek(seekersFile,0,SEEK_SET);
      while (fscanf(seekersFile, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%d,%[^\n]\n",currentUser.id,currentUser.password,currentUser.name,currentUser.email,currentUser.bachelors,currentUser.masters,currentUser.certification,currentUser.skillstr,&currentUser.experience,currentUser.bio)== 10)
            {    

               
              
                if (strcmp(currentUser.id,userID)==0 &&     strcmp(currentUser.password,userPassword) == 0)
                {
                   
                    find = 1;
                    break;
                }
            }
      seekerreq login;
      
      if (find==1)
      {
        strcpy(login.id,currentUser.id);
        strcpy(login.password,userPassword);
        strcpy(login.name,currentUser.name);
        printf("\nUser ID: %s\n",login.id);
        printf("Password: %s\n",login.password);
        printf("User Name: %s\n",login.name);
        getchar();
        printf("Enter the jobname you are looking for: ");
        scanf("%[^\n]",login.jobname);
      printf("Enter the work experience to search for: ");
      scanf("%d",&login.workExperience);
      printf("Enter the preferred work location: ");
          getchar();
      scanf("%[^\n]",login.location);
        printf("Enter the ctc expectations: ");
         getchar(); 
        scanf("%d",&login.ctc);
        printf("Enter the compulsory constraint: ");
        scanf("%s",login.compconst);
        loginSeeker(login);


        printf("Would you like to check for matches?\n");
        printf("Enter 'Y' if yes and 'N' if no.\n");
        scanf("%c",&check);
        scanf("%c",&check);
        check=toupper(check);
        if (check=='Y')
        {
          find_recruiter();
          printSeekerData(userID);
        }
      }
      else
      {
        printf("Invalid Username or Password");
      }  
        fclose(seekersFile);


    }
      else
      {
      char seekerid[7];
        
        printf("Enter the seeker id: ");
        scanf("%s",seekerid);
        find_recruiter();
        printSeekerData(seekerid);
      }
    }
    else
    {
      if (nextopt=='C')
      {
      char userID[7];
      char userPassword[7];
      char check;
            printf("Enter your User ID: ");
            scanf("%s",userID);


      getchar();
            printf("Enter your Password: ");
            scanf("%s",userPassword);
getchar();
            FILE *recruitersFile = fopen("recruiters.csv", "r");
            if (recruitersFile == NULL)
            {
                printf("Error opening the file.\n");
                return 1;
            }
          Recruiter currentUser;
      int find=0;
      
      fseek(recruitersFile,0,SEEK_SET);
      
      while (fscanf(recruitersFile, "%[^,],%[^,],%[^,],%[^,], %d,%[^,],%d\n", currentUser.id, currentUser.password, currentUser.companyName,  currentUser.jobname, &currentUser.workExperience,currentUser.location,&currentUser.ctc) == 7)
            {
                if (strcmp(currentUser.id,userID)==0 &&     strcmp(currentUser.password,userPassword) == 0)
                {
                    find = 1;
                    break;
                }
            }
      recruiterexp login;
      
      if (find==1)
      {
        strcpy(login.id,currentUser.id);
        strcpy(login.password,userPassword);
        strcpy(login.companyname,currentUser. companyName);
         printf("\nUser ID: %s\n",login.id);
        printf("Password: %s\n",login.password);
        printf("Company Name: %s\n",login.companyname);
        
        printf("Enter bachelors degree(enter n if no degree): ");
      
        scanf("%[^\n]",login.bachelors);
        printf("Enter masters degree(enter n if no degree): ");
        getchar();
        scanf("%[^\n]",login.masters);
        printf("Enter certification needed: ");
          getchar();
        scanf("%[^\n]",login.certification);
        printf("Enter the minimum experience needed: ");
        scanf("%d",&login.experience);
        printf("Enter compulsory constraint: ");
        scanf("%s",login.compconst);
        printf("Enter four skills of your choice in order: ");
        char skills[4][20];
        for (int i=0;i<4;i++)
          {
            scanf("%s",skills[i]);
          }
        sprintf(login.skillstr,"%s %s %s %s",skills[0],skills[1],skills[2],skills[3]);
        loginrecruiter(login);
        
         printf("Would you like to check for matches?\n");
        printf("Enter 'Y' if yes and 'N' if no.");
        scanf("%c",&check);
        scanf("%c",&check);
        check=toupper(check);
        if (check=='Y')
        {
          
          find_seeker();
          printRecruiterData(userID);
        }
      }
    else
      {
        printf("Invalid Username or Password");
      }  
      fclose(recruitersFile);
    }
      else
      {
       char recruiterid[7];
        find_seeker();
        printf("Enter the recruiter id: ");
        scanf("%s",recruiterid);
        printRecruiterData(recruiterid);
       
      }
}
  }
else
  {
    if (user1=='A')
    {
      printf("Enter the details of new recruiter: \n");
      srand(time(NULL)); 
      
      generate_unique_id(recruiter.id);
      generateRandomPassword(recruiter.password);
        
        printf("\nUser ID: %s\n", recruiter.id); 
        printf("Password: %s \n",recruiter.password);
        printf("Enter company name: ");
        scanf(" %[^\n]", recruiter.companyName);        
        printf("Enter Job Name: ");
        scanf(" %s", recruiter.jobname);
        printf("Enter work experience: ");
        scanf(" %d", &recruiter.workExperience);
        printf("Enter location: ");
        scanf(" %[^\n]",recruiter.location);
        printf("Enter ctc: ");
        scanf("%d",&recruiter.ctc);
       registerRecruiter(file2, recruiter);
    
      
    }
    
    else
    {
      printf("Enter the details of new seeker: \n");
      generate_unique_id(user.id);
      generateRandomPassword(user.password);
        
        printf("\nUser ID: %s\n", user.id); 
        printf("Password: %s \n",user.password);
        printf("Enter name: ");
        scanf(" %[^\n]", user.name);        
        printf("Enter bachelors degree(enter n if no degree): ");
        scanf(" %[^\n]", user.bachelors);
        printf("Enter masters degree(enter n if no degree): ");
        scanf(" %[^\n]", user.masters);
        printf("Enter certification : ");
        scanf(" %[^\n]",user.certification);
     
      printf("Enter experience: ");
      scanf("%d",&user.experience);
      getchar();
       printf("Enter bio: ");
       scanf("%[^\n]",user.bio);
      
      registerUser(file1, user);
     
    }
    
  }

    return 0;
}

  

