#include<stdio.h>
#include<stdbool.h>
#include<ctype.h>
#include<string.h>

#define NAME_LENGTH 20
#define LAST_NAME_LENGTH 30

typedef struct information info;

// Designed for each menu options
enum MENU{ZERO, ADDS, ADDSG, RS, CSI, PSI}; // ADDS : Add student, ADDSG : Add student grades, RS : Remove student, PSI : Print student information, PSI : Print student information  CSI تغییرات
enum CHANGEINFOMENU{ZERO1, CSN, CSL, CSA, CSG, RSG}; // CSN : Change student name, CSL : Change student last name, CSA : Change student age, CSG : Change student grade, RSG : Remove student grades
enum PRINTINFOMENU{ZERO2, PLOS, SSI, PLOG, SSMC, SNFSC, SISGEU, GPA, GPACF, CS, LCYF}; //PLOS : Print List of Student, SSI : Search student information, PLOG : Print list of grades, SSMC : Show the student's missed courses, SNFSC : Show the number of failed students in a course, SISGEU : Sisplay information of all students with the grade entered by the user, Show student GPA : GPA display, GPACF : GPA display of courses in the faculty, CS : Conditional students, LCYF : List of the courses that have not yet failed

// Variables for each menu selection
typedef struct
{
  unsigned char cM; // Main menu
  unsigned char c1; // (Changing student informations) menu
  unsigned char c2; // (Print informations) menu
  unsigned char c3; 
}choice;

struct information
{
  char name[NAME_LENGTH];
  char last_name[LAST_NAME_LENGTH];
  unsigned int student_id; // The student ID is our unique code
  unsigned int student_age;
};

typedef struct
{
  bool check_grade;
  unsigned int student_id;
  float math1;
  float physic1;
  float computer_workshop;
  float basic_programming;
  float persian_lan;
  float english_lan;
  float rules;  
}grades;

typedef struct  // Temporary variables
{ 
  char new_name[NAME_LENGTH]; // The new student name that is taken from the user
  char new_last_name[LAST_NAME_LENGTH]; // The new student last name that is taken from the user
  unsigned int enter_id; // The student ID that is taken from the user
  unsigned int new_age; 
  float new_math1;
  float new_physic1;
  float new_computer_workshop;
  float new_basic_programming;
  float new_persian_lan;
  float new_english_lan;
  float new_rules;
}temp;

typedef struct
{
  bool m1;
  bool ph1;
  bool cw;
  bool bp;
  bool pl;
  bool el;
  bool r;
}check;

int getcommand()
{
  int choice;

  printf("\n");
  puts("Main menu :");
  puts("1. Add student.");
  puts("2. Add student grades");
  puts("3. Remove student.");
  puts("4. Changes in students information.");
  puts("5. Display options");
  puts("6. Exit");
  printf("\a");
  scanf("%d" , &choice);
  return choice;
}

int getcommand1()
{
  int choice;

  printf("\n");
  puts("1. Change student name.");
  puts("2. Change student last name.");
  puts("3. Change student age.");
  puts("4. Change student grades.");
  puts("5. Remove student grades.");
  puts("6. Back to main menu");
  
  scanf("%d", &choice);
  return choice;
}

int getcommand2()
{
  int choice;
  
  printf("\n");
  puts("1. Display all students information.");
  puts("2. Search student information by ID.");
  puts("3. Display just all students grades.");
  puts("4. Display the student's missed courses.");
  puts("5. Display the number of failed students in a course.");
  puts("6. Display information of all students with the grade entered by the user.");
  puts("7. GPA display by ID.");
  puts("8. GPA display of courses in the faculty.");
  puts("9. Conditional students.");
  puts("10. List of the courses that have not yet failed.");
  puts("11. Back to main menu");

  scanf("%d", &choice);
  return choice;
}

int getcommand3()
{
  int choice;

  printf("\n");
  puts("1. Change Math1 grade");
  puts("2. Change Physic1 grade");
  puts("3. Change Computer workshop grade");
  puts("4. Change Basic programming grade");
  puts("5. Change Persian language grade");
  puts("6. Change Engilish language grade");
  puts("7. Change Rules grade");
  puts("8. Back to main menu");

  scanf("%d", &choice);
  return choice;
}

int getcommand4()
{
  int choice;

  printf("\n");
  puts("1. Math1");
  puts("2. Physic1");
  puts("3. Computer workshop");
  puts("4. Basic programming");
  puts("5. Persian language");
  puts("6. Engilish language");
  puts("7. Rules");
  puts("8. Back to main menu");

  scanf("%d", &choice);
  return choice;
}

void GetStudentInfo(info* stu, grades* gstu)
{
  printf("\n");
  printf("Enter student name : ");
  scanf("%20s", stu->name);
  printf("Enter student last name : ");
  scanf("%30s", stu->last_name);
  printf("Enter student id : ");
  scanf("%u", &(stu->student_id)); 
  printf("Enter student age : ");
  scanf("%u", &(stu->student_age));

  gstu->check_grade = true;
  gstu->student_id = stu->student_id;

  printf("\n");
 
  puts("Enter student grades :");

  printf("Enter Math1 grade -----> ");
  scanf("%f", &(gstu->math1));
  printf("Enter Physic1 grade -----> ");
  scanf("%f", &(gstu->physic1));
  printf("Enter Computer workshop grade -----> ");
  scanf("%f", &(gstu->computer_workshop));
  printf("Enter Basic programming grade -----> ");
  scanf("%f", &(gstu->basic_programming));
  printf("Enter Persian language grade -----> ");
  scanf("%f", &(gstu->persian_lan));
  printf("Enter English language grade -----> ");
  scanf("%f", &(gstu->english_lan));
  printf("Enter Rules grade -----> ");
  scanf("%f", &(gstu->rules));
}

void AddStudentGrades(grades* addG)
{
  addG->check_grade = true;

  puts("Enter student grades :");

  printf("Enter Math1 grade -----> ");
  scanf("%f", &(addG->math1));
  printf("Enter Physic1 grade -----> ");
  scanf("%f", &(addG->physic1));
  printf("Enter Computer workshop grade -----> ");
  scanf("%f", &(addG->computer_workshop));
  printf("Enter Basic programming grade -----> ");
  scanf("%f", &(addG->basic_programming));
  printf("Enter Persian language grade -----> ");
  scanf("%f", &(addG->persian_lan));
  printf("Enter English language grade -----> ");
  scanf("%f", &(addG->english_lan));
  printf("Enter Rules grade -----> ");
  scanf("%f", &(addG->rules));
}

void RemoveStudent(unsigned int sid, FILE* fptr, FILE* gfptr)
{
  info Rstudent;
  grades GradesPart;
  
  fseek(fptr, sizeof(info) * (sid - 1), SEEK_SET);
  fread(&Rstudent, sizeof(info), 1, fptr);
  Rstudent.student_id = 0;
  fseek(fptr, sizeof(info) * (sid - 1), SEEK_SET);
  fwrite(&Rstudent, sizeof(info), 1, fptr);

  fseek(gfptr, sizeof(grades) * (sid - 1), SEEK_SET);
  fread(&GradesPart, sizeof(grades), 1, gfptr);
  GradesPart.check_grade = false;
  fseek(gfptr, sizeof(grades) * (sid - 1), SEEK_SET);
  fwrite(&GradesPart, sizeof(grades), 1, gfptr);

  printf("\n");
  puts("------------------------------");
  printf("\n");
  puts("Student information was removed from the list !!!");
  printf("\n");
  puts("------------------------------");
}

void ChangeStudentName(char newname[], unsigned int sid, FILE* fptr)
{
  info changeN;

  fseek(fptr, sizeof(info) * (sid - 1), SEEK_SET);
  fread(&changeN, sizeof(info), 1, fptr);
  strcpy(changeN.name, newname);
  fseek(fptr, sizeof(info) * (sid - 1), SEEK_SET);
  fwrite(&changeN, sizeof(info), 1, fptr);
}

void ChangeStudentLastName(char newlastname[], unsigned int sid, FILE* fptr)
{
  info changeL;

  fseek(fptr, sizeof(info) * (sid - 1), SEEK_SET);
  fread(&changeL, sizeof(info), 1, fptr);
  strcpy(changeL.last_name, newlastname);
  fseek(fptr, sizeof(info) * (sid - 1), SEEK_SET);
  fwrite(&changeL, sizeof(info), 1, fptr);
}

void ChangeStudentAge(unsigned int newage, unsigned int sid, FILE* fptr)
{
  info changeA;

  fseek(fptr, sizeof(info) * (sid - 1), SEEK_SET);
  fread(&changeA, sizeof(info), 1, fptr);
  changeA.student_age = newage;
  fseek(fptr, sizeof(info) * (sid - 1), SEEK_SET);
  fwrite(&changeA, sizeof(info), 1, fptr);
}

void ChangeStudentGrade(unsigned int sid, FILE* gfptr)
{
  grades changeG;
  temp neW;
  int choice;

  do
  {
    choice = getcommand3(); 
    switch (choice)
    {
      case 1:
          printf("\n");

          fseek(gfptr, sizeof(grades) * (sid - 1), SEEK_SET);
          fread(&changeG, sizeof(grades), 1, gfptr);
          printf("Enter new Math1 grade : ");
          scanf("%f", &neW.new_math1);
          changeG.math1 = neW.new_math1;
          fseek(gfptr, sizeof(grades) * (sid - 1), SEEK_SET);
          fwrite(&changeG, sizeof(grades), 1, gfptr);

          printf("\n");
      break;

      case 2:
        printf("\n");

        fseek(gfptr, sizeof(grades) * (sid - 1), SEEK_SET);
        fread(&changeG, sizeof(grades), 1, gfptr);
        printf("Enter new Physic1 grade : ");
        scanf("%f", &neW.new_physic1);
        changeG.physic1 = neW.new_physic1;
        fseek(gfptr, sizeof(grades) * (sid - 1), SEEK_SET);
        fwrite(&changeG, sizeof(grades), 1, gfptr);

        printf("\n");
      break;

      case 3:
        printf("\n");

        fseek(gfptr, sizeof(grades) * (sid - 1), SEEK_SET);
        fread(&changeG, sizeof(grades), 1, gfptr);
        printf("Enter new Computer workshop grade : ");
        scanf("%f", &neW.new_computer_workshop);
        changeG.computer_workshop = neW.new_computer_workshop;
        fseek(gfptr, sizeof(grades) * (sid - 1), SEEK_SET);
        fwrite(&changeG, sizeof(grades), 1, gfptr);

        printf("\n");
      break;

      case 4:
        printf("\n");

        fseek(gfptr, sizeof(grades) * (sid - 1), SEEK_SET);
        fread(&changeG, sizeof(grades), 1, gfptr);
        printf("Enter new Basic programming grade : ");
        scanf("%f", &neW.new_basic_programming);
        changeG.basic_programming = neW.new_basic_programming;
        fseek(gfptr, sizeof(grades) * (sid - 1), SEEK_SET);
        fwrite(&changeG, sizeof(grades), 1, gfptr);

        printf("\n");
      break;

      case 5:
          printf("\n");

          fseek(gfptr, sizeof(grades) * (sid - 1), SEEK_SET);
          fread(&changeG, sizeof(grades), 1, gfptr);
          printf("Enter new Persian language grade : ");
          scanf("%f", &neW.new_persian_lan);
          changeG.persian_lan = neW.new_persian_lan;
          fseek(gfptr, sizeof(grades) * (sid - 1), SEEK_SET);
          fwrite(&changeG, sizeof(grades), 1, gfptr);

          printf("\n");
      break;

      case 6:
          printf("\n");

          fseek(gfptr, sizeof(grades) * (sid - 1), SEEK_SET);
          fread(&changeG, sizeof(grades), 1, gfptr);
          printf("Enter new English language grade : ");
          scanf("%f", &neW.new_english_lan);
          changeG.english_lan = neW.new_english_lan;
          fseek(gfptr, sizeof(grades) * (sid - 1), SEEK_SET);
          fwrite(&changeG, sizeof(grades), 1, gfptr);

          printf("\n");
      break;

      case 7:
          printf("\n");

          fseek(gfptr, sizeof(grades) * (sid - 1), SEEK_SET);
          fread(&changeG, sizeof(grades), 1, gfptr);
          printf("Enter new Rules grade : ");
          scanf("%f", &neW.new_rules);
          changeG.rules = neW.new_rules;
          fseek(gfptr, sizeof(grades) * (sid - 1), SEEK_SET);
          fwrite(&changeG, sizeof(grades), 1, gfptr);

          printf("\n");
      break;

      default:
          puts("This is wrong number !!!");
          puts("Try again...");
      break;
    }
  }while (choice != 8);
}

void RemoveStudentGrades(unsigned int sid, FILE* gfptr)
{
  grades Rgrades;

  fseek(gfptr, sizeof(grades) * (sid - 1), SEEK_SET);
  fread(&Rgrades, sizeof(grades), 1, gfptr);
  Rgrades.check_grade = false;
  fseek(gfptr, sizeof(grades) * (sid - 1), SEEK_SET);
  fwrite(&Rgrades, sizeof(grades), 1, gfptr);

  printf("\n");
  puts("------------------------------");
  printf("\n");
  puts("Student's grades were successfully removed !!!");
  printf("\n");
  puts("------------------------------");
}

void ShowStudentInfo(info* chapI) // all students information
{
  printf("* name : %s\n", chapI->name);
  printf("* Last name : %s\n", chapI->last_name);
  printf("* Student id : %u\n", chapI->student_id);
  printf("* Student age : %u\n", chapI->student_age);

  printf("\n");
  puts("------------------------------");
  printf("\n");
}


void SearchStudentInfo(info* search)
{
  printf("\n");
  puts("------------------------------");
  printf("\n");

  printf("* name : %s\n", search->name);
  printf("* Last name : %s\n", search->last_name);
  printf("* Student id : %u\n", search->student_id);
  printf("* Student age : %u\n", search->student_age);

  printf("\n");
  puts("------------------------------");
  printf("\n");
}


void ShowGrades(grades* chapG)
{
  if (chapG->check_grade == true)
  {
    printf("Student ID : %u\n", chapG->student_id);
    printf("* lesson : math1 \t course : 3 \t grade : %.2f\n", chapG->math1);
    printf("* lesson : physic1 \t course : 3 \t grade : %.2f\n", chapG->physic1);
    printf("* lesson : computer workshop \t course : 1 \t grade : %.2f\n", chapG->computer_workshop);
    printf("* lesson : basic programming \t course : 3 \t grade : %.2f\n", chapG->basic_programming);
    printf("* lesson : persian language \t course : 3 \t grade : %.2f\n", chapG->persian_lan);
    printf("* lesson : english language \t course : 3 \t grade : %.2f\n", chapG->english_lan);
    printf("* lesson : rules \t course : 2 \t grade : %.2f\n", chapG->rules);

    printf("\n");
    puts("------------------------------");
    printf("\n");
  }
}

void ShowMissedCourses(unsigned int sid, FILE* gfptr)
{
  grades Missed;
  int counter = 0;

  fseek(gfptr, sizeof(grades) * (sid - 1), SEEK_SET);
  fread(&Missed, sizeof(grades), 1, gfptr);

  puts("------------------------------");
  printf("\n");

  printf("Student ID : %u\n", sid);
  printf("\n");

  if (Missed.math1 < 10)
  {
    printf("* math1 : failed \t grade : %.2f\n", Missed.math1);
    counter++;
  }

  if (Missed.physic1 < 10)
  {
    printf("* physic1 : failed \t grade : %.2f\n", Missed.physic1);
    counter++;
  }

  if (Missed.computer_workshop < 10)
  {
    printf("* computer workshop : failed \t grade : %.2f\n", Missed.computer_workshop);
    counter++;
  }

  if (Missed.basic_programming < 10)
  {
    printf("* basic programming : failed \t grade : %.2f\n", Missed.basic_programming);
    counter++;
  }

  if (Missed.persian_lan < 10)
  {
    printf("* persian language : failed \t grade : %.2f\n", Missed.persian_lan);
    counter++;
  }

  if (Missed.english_lan < 10)
  {
    printf("* english language : failed \t grade : %.2f\n", Missed.english_lan);
    counter++;
  }

  if (Missed.rules < 10)
  {
    printf("* rules : failed \t grade : %.2f\n", Missed.rules);
    counter++;
  }

  if (counter == 0)
  {
    puts("This student has succeeded in all subjects !!!");
  }

  printf("\n");
  puts("------------------------------");
}

void ShowStudentFailedCounter(FILE* gfptr)
{
  int choice;
  unsigned int counter = 0;
  grades temp;

  do
  {
    choice = getcommand4();

    switch (choice)
    {
      case 1:
          printf("\n");
          puts("------------------------------");
          printf("\n");

          fseek(gfptr, 0, SEEK_SET);

          while (!feof(gfptr))
          {
            fread(&temp, sizeof(grades), 1, gfptr);

            if (!feof(gfptr) && temp.math1 < 10 && temp.check_grade == true && temp.student_id != 0)
            {
              counter++;
            }
          }

          if (counter != 0)
          {
            printf("* lesson : math1 \t failed counter : %u\n", counter);
          }
          
          else
          {
            puts("No one failed in math1 !!!");
          }

          printf("\n");
          puts("------------------------------");
          printf("\n");

          counter = 0;
      break;

      case 2:
          printf("\n");
          puts("------------------------------");
          printf("\n");

          fseek(gfptr, 0, SEEK_SET);

          while (!feof(gfptr))
          {
            fread(&temp, sizeof(grades), 1, gfptr);

            if (!feof(gfptr) && temp.physic1 < 10 && temp.check_grade == true && temp.student_id != 0)
            {
              counter++;
            }
          }

          if (counter != 0)
          {
            printf("* lesson : physic1 \t failed counter : %u\n", counter);
          }
          
          else
          {
            puts("No one failed in physic1 !!!");
          }

          printf("\n");
          puts("------------------------------");
          printf("\n");

          counter = 0;
      break;

      case 3:
          printf("\n");
          puts("------------------------------");
          printf("\n");

          fseek(gfptr, 0, SEEK_SET);

          while (!feof(gfptr))
          {
            fread(&temp, sizeof(grades), 1, gfptr);

            if (!feof(gfptr) && temp.computer_workshop < 10 && temp.check_grade == true && temp.student_id != 0)
            {
              counter++;
            }
          }

          if (counter != 0)
          {
            printf("* lesson : computer_workshop \t failed counter : %u\n", counter);
          }
          
          else
          {
            puts("No one failed in computer_workshop !!!");
          }

          printf("\n");
          puts("------------------------------");
          printf("\n");

          counter = 0;
      break;

      case 4:
          printf("\n");
          puts("------------------------------");
          printf("\n");

          fseek(gfptr, 0, SEEK_SET);

          while (!feof(gfptr))
          {
            fread(&temp, sizeof(grades), 1, gfptr);

            if (!feof(gfptr) && temp.basic_programming < 10 && temp.check_grade == true && temp.student_id != 0)
            {
              counter++;
            }
          }

          if (counter != 0)
          {
            printf("* lesson : basic_programming \t failed counter : %u\n", counter);
          }
          
          else
          {
            puts("No one failed in basic_programming !!!");
          }

          printf("\n");
          puts("------------------------------");
          printf("\n");

          counter = 0;
      break;

      case 5:
          printf("\n");
          puts("------------------------------");
          printf("\n");

          fseek(gfptr, 0, SEEK_SET);

          while (!feof(gfptr))
          {
            fread(&temp, sizeof(grades), 1, gfptr);

            if (!feof(gfptr) && temp.persian_lan < 10 && temp.check_grade == true && temp.student_id != 0)
            {
              counter++;
            }
          }

          if (counter != 0)
          {
            printf("* lesson : persian_lan \t failed counter : %u\n", counter);
          }
          
          else
          {
            puts("No one failed in persian_lan !!!");
          }

          printf("\n");
          puts("------------------------------");
          printf("\n");

          counter = 0;
      break;

      case 6:
          printf("\n");
          puts("------------------------------");
          printf("\n");

          fseek(gfptr, 0, SEEK_SET);

          while (!feof(gfptr))
          {
            fread(&temp, sizeof(grades), 1, gfptr);

            if (!feof(gfptr) && temp.english_lan < 10 && temp.check_grade == true && temp.student_id != 0)
            {
              counter++;
            }
          }

          if (counter != 0)
          {
            printf("* lesson : english_lan \t failed counter : %u\n", counter);
          }
          
          else
          {
            puts("No one failed in english_lan !!!");
          }

          printf("\n");
          puts("------------------------------");
          printf("\n");

          counter = 0;
      break;

      case 7:
          printf("\n");
          puts("------------------------------");
          printf("\n");

          fseek(gfptr, 0, SEEK_SET);

          while (!feof(gfptr))
          {
            fread(&temp, sizeof(grades), 1, gfptr);

            if (!feof(gfptr) && temp.rules < 10 && temp.check_grade == true && temp.student_id != 0)
            {
              counter++;
            }
          }

          if (counter != 0)
          {
            printf("* lesson : rules \t failed counter : %u\n", counter);
          }
          
          else
          {
            puts("No one failed in rules !!!");
          }

          printf("\n");
          puts("------------------------------");
          printf("\n");

          counter = 0;
      break;

      case 8:
      break;
 
      default:
          puts("This is wrong number !!!");
          puts("Try again...");
      break;
    }
  }while (choice != 8);
}

void ShowListOfStudentWithXgrade(FILE* gfptr)
{
  int choice;
  grades temp;
  float user_grade;
  int counter = 0;

  do
  {
    choice = getcommand4();

    switch (choice)
    {
      case 1:
          printf("Enter the grade you want to find :");
          scanf("%f", &user_grade);

          printf("\n");
          puts("------------------------------");
          printf("\n");

          fseek(gfptr, 0, SEEK_SET);

          while (!feof(gfptr))
          {
            fread(&temp, sizeof(grades), 1, gfptr);
            if (!feof(gfptr) && temp.math1 == user_grade && temp.check_grade == true && temp.student_id != 0) // !feof(gfptr) : شرط روبرو باعث می شود که از تکرار ریکورد آخر جلوگیری شود
            {
              printf("* student ID : %u \t lesson : math1 \t grade : %.2f\n", temp.student_id, temp.math1);
              printf("\n");
              puts("------------------------------");
              printf("\n");

              counter++;
            }
          }  

          if (counter == 0)
          {
            puts("I can't find this grade from the list !!!");
            printf("\n");
            puts("------------------------------");
            printf("\n");
          }

          counter = 0;
      break;

      case 2:
          printf("Enter the grade you want to find :");
          scanf("%f", &user_grade);

          printf("\n");
          puts("------------------------------");
          printf("\n");

          fseek(gfptr, 0, SEEK_SET);

          while (!feof(gfptr))
          {
            fread(&temp, sizeof(grades), 1, gfptr);

            if (!feof(gfptr) && temp.physic1 == user_grade && temp.check_grade == true && temp.student_id != 0)
            {
              printf("* student ID : %u \t lesson : physic1 \t grade : %.2f\n", temp.student_id, temp.physic1);
              printf("\n");
              puts("------------------------------");
              printf("\n");

              counter++;
            }
          }

          if (counter == 0)
          {
            puts("I can't find this grade from the list !!!");
            printf("\n");
            puts("------------------------------");
            printf("\n");
          }

          counter = 0;
      break;

      case 3:
          printf("Enter the grade you want to find :");
          scanf("%f", &user_grade);

          printf("\n");
          puts("------------------------------");
          printf("\n");

          fseek(gfptr, 0, SEEK_SET);

          while (!feof(gfptr))
          {
            fread(&temp, sizeof(grades), 1, gfptr);

            if (!feof(gfptr) && temp.computer_workshop == user_grade && temp.check_grade == true && temp.student_id != 0)
            {
              printf("* student ID : %u \t lesson : computer_workshop \t grade : %.2f\n", temp.student_id, temp.computer_workshop);
              printf("\n");
              puts("------------------------------");
              printf("\n");

              counter++;
            }
          }

          if (counter == 0)
          {
            puts("I can't find this grade from the list !!!");
            printf("\n");
            puts("------------------------------");
            printf("\n");
          }

          counter = 0;
      break;

      case 4:
          printf("Enter the grade you want to find :");
          scanf("%f", &user_grade);

          printf("\n");
          puts("------------------------------");
          printf("\n");

          fseek(gfptr, 0, SEEK_SET);

          while (!feof(gfptr))
          {
            fread(&temp, sizeof(grades), 1, gfptr);

            if (!feof(gfptr) && temp.basic_programming == user_grade && temp.check_grade == true && temp.student_id != 0)
            {
              printf("* student ID : %u \t lesson : basic_programming \t grade : %.2f\n", temp.student_id, temp.basic_programming);
              printf("\n");
              puts("------------------------------");
              printf("\n");

              counter++;
            }
          }

          if (counter == 0)
          {
            puts("I can't find this grade from the list !!!");
            printf("\n");
            puts("------------------------------");
            printf("\n");
          }

          counter = 0;
      break;

      case 5:
          printf("Enter the grade you want to find :");
          scanf("%f", &user_grade);

          printf("\n");
          puts("------------------------------");
          printf("\n");

          fseek(gfptr, 0, SEEK_SET);

          while (!feof(gfptr))
          {
            fread(&temp, sizeof(grades), 1, gfptr);

            if (!feof(gfptr) && temp.persian_lan == user_grade && temp.check_grade == true && temp.student_id != 0)
            {
              printf("* student ID : %u \t lesson : persian_lan \t grade : %.2f\n", temp.student_id, temp.persian_lan);
              printf("\n");
              puts("------------------------------");
              printf("\n");

              counter++;
            }
          }

          if (counter == 0)
          {
            puts("I can't find this grade from the list !!!");
            printf("\n");
            puts("------------------------------");
            printf("\n");
          }

          counter = 0;
      break;

      case 6:
          printf("Enter the grade you want to find :");
          scanf("%f", &user_grade);

          printf("\n");
          puts("------------------------------");
          printf("\n");

          fseek(gfptr, 0, SEEK_SET);

          while (!feof(gfptr))
          {
            fread(&temp, sizeof(grades), 1, gfptr);

            if (!feof(gfptr) && temp.english_lan == user_grade && temp.check_grade == true && temp.student_id != 0)
            {
              printf("* student ID : %u \t lesson : english_lan \t grade : %.2f\n", temp.student_id, temp.english_lan);
              printf("\n");
              puts("------------------------------");
              printf("\n");

              counter++;
            }
          }

          if (counter == 0)
          {
            puts("I can't find this grade from the list !!!");
            printf("\n");
            puts("------------------------------");
            printf("\n");
          }

          counter = 0;
      break;

      case 7:
          printf("Enter the grade you want to find :");
          scanf("%f", &user_grade);

          printf("\n");
          puts("------------------------------");
          printf("\n");

          fseek(gfptr, 0, SEEK_SET);

          while (!feof(gfptr))
          {
            fread(&temp, sizeof(grades), 1, gfptr);

            if (!feof(gfptr) && temp.rules == user_grade && temp.check_grade == true && temp.student_id != 0)
            {
              printf("* student ID : %u \t lesson : rules \t grade : %.2f\n", temp.student_id, temp.rules);
              printf("\n");
              puts("------------------------------");
              printf("\n");

              counter++;
            }
          }

          if (counter == 0)
          {
            puts("I can't find this grade from the list !!!");
            printf("\n");
            puts("------------------------------");
            printf("\n");
          }

          counter = 0;
      break;

      case 8:
      break;
 
      default:
          puts("This is wrong number !!!");
          puts("Try again...");
      break;
    }
  }while (choice != 8);
}

void StudentGpa(unsigned int sid, FILE* gfptr)
{
  grades GPAS;
  float Average;

  fseek(gfptr, sizeof(grades) * (sid - 1), SEEK_SET);
  fread(&GPAS, sizeof(grades), 1, gfptr);

  if (GPAS.check_grade == true)
  { 
    Average = (GPAS.math1 + GPAS.physic1 + GPAS.computer_workshop + GPAS.basic_programming + GPAS.persian_lan + GPAS.english_lan + GPAS.rules) / 7;
    
    puts("------------------------------");
    printf("\n");
    printf("Student ID : %u \t Student GPA: %.2f\n", GPAS.student_id, Average);
    printf("\n");
    puts("------------------------------");          
  }
  else
  {
    puts("------------------------------");
    printf("\n");
    puts("student grades has been removed !!!");
    printf("\n");
    puts("------------------------------");
  }
}

void CoursesGpa(FILE* gfptr)
{
  int choice;
  grades temp;
  float sum = 0;
  float GPA;
  int counter = 0;

  do
  {
    choice = getcommand4();

    switch (choice)
    {
      case 1:
          printf("\n");
          puts("------------------------------");
          printf("\n");

          fseek(gfptr, 0, SEEK_SET);

          while (!feof(gfptr))
          {
            fread(&temp, sizeof(grades), 1, gfptr);
            if (!feof(gfptr) && temp.check_grade == true && temp.student_id != 0) // !feof(gfptr) : شرط روبرو باعث می شود که از تکرار ریکورد آخر جلوگیری شود
            {
              sum = sum + temp.math1;
              counter++;
            }
          }

          GPA = sum / counter;

          printf("* math1 GPA : %.2f\n", GPA);
          printf("\n");
          puts("------------------------------");
          printf("\n");

          if (counter == 0)
          {
            puts("I can't find this grade from the list !!!");
            puts("------------------------------");
            printf("\n");
          }

          sum = 0;
          counter = 0;
      break;

      case 2:
          printf("\n");
          puts("------------------------------");
          printf("\n");

          fseek(gfptr, 0, SEEK_SET);

          while (!feof(gfptr))
          {
            fread(&temp, sizeof(grades), 1, gfptr);
            if (!feof(gfptr) && temp.check_grade == true && temp.student_id != 0) // !feof(gfptr) : شرط روبرو باعث می شود که از تکرار ریکورد آخر جلوگیری شود
            {
              sum = sum + temp.physic1;
              counter++;
            }
          }

          GPA = sum / counter;

          printf("* physic1 GPA : %.2f\n", GPA);
          printf("\n");
          puts("------------------------------");
          printf("\n");

          if (counter == 0)
          {
            puts("I can't find this grade from the list !!!");
            puts("------------------------------");
            printf("\n");
          }

          sum = 0;
          counter = 0;
      break;

      case 3:
          printf("\n");
          puts("------------------------------");
          printf("\n");

          fseek(gfptr, 0, SEEK_SET);

          while (!feof(gfptr))
          {
            fread(&temp, sizeof(grades), 1, gfptr);
            if (!feof(gfptr) && temp.check_grade == true && temp.student_id != 0) // !feof(gfptr) : شرط روبرو باعث می شود که از تکرار ریکورد آخر جلوگیری شود
            {
              sum = sum + temp.computer_workshop;
              counter++;
            }
          }

          GPA = sum / counter;

          printf("* computer_workshop GPA : %.2f\n", GPA);
          printf("\n");
          puts("------------------------------");
          printf("\n");

          if (counter == 0)
          {
            puts("I can't find this grade from the list !!!");
            puts("------------------------------");
            printf("\n");
          }

          sum = 0;
          counter = 0;
      break;

      case 4:
          printf("\n");
          puts("------------------------------");
          printf("\n");

          fseek(gfptr, 0, SEEK_SET);

          while (!feof(gfptr))
          {
            fread(&temp, sizeof(grades), 1, gfptr);
            if (!feof(gfptr) && temp.check_grade == true && temp.student_id != 0) // !feof(gfptr) : شرط روبرو باعث می شود که از تکرار ریکورد آخر جلوگیری شود
            {
              sum = sum + temp.basic_programming;
              counter++;
            }
          }

          GPA = sum / counter;

          printf("* basic_programming GPA : %.2f\n", GPA);
          printf("\n");
          puts("------------------------------");
          printf("\n");

          if (counter == 0)
          {
            puts("I can't find this grade from the list !!!");
            puts("------------------------------");
            printf("\n");
          }

          sum = 0;
          counter = 0;
      break;

      case 5:
          printf("\n");
          puts("------------------------------");
          printf("\n");

          fseek(gfptr, 0, SEEK_SET);

          while (!feof(gfptr))
          {
            fread(&temp, sizeof(grades), 1, gfptr);
            if (!feof(gfptr) && temp.check_grade == true && temp.student_id != 0) // !feof(gfptr) : شرط روبرو باعث می شود که از تکرار ریکورد آخر جلوگیری شود
            {
              sum = sum + temp.persian_lan;
              counter++;
            }
          }

          GPA = sum / counter;

          printf("* persian language GPA : %.2f\n", GPA);
          printf("\n");
          puts("------------------------------");
          printf("\n");

          if (counter == 0)
          {
            puts("I can't find this grade from the list !!!");
            puts("------------------------------");
            printf("\n");
          }

          sum = 0;
          counter = 0;
      break;

      case 6:
          printf("\n");
          puts("------------------------------");
          printf("\n");

          fseek(gfptr, 0, SEEK_SET);

          while (!feof(gfptr))
          {
            fread(&temp, sizeof(grades), 1, gfptr);
            if (!feof(gfptr) && temp.check_grade == true && temp.student_id != 0) // !feof(gfptr) : شرط روبرو باعث می شود که از تکرار ریکورد آخر جلوگیری شود
            {
              sum = sum + temp.english_lan;
              counter++;
            }
          }

          GPA = sum / counter;

          printf("* english language GPA : %.2f\n", GPA);

          printf("\n");
          puts("------------------------------");
          printf("\n");

          if (counter == 0)
          {
            puts("I can't find this grade from the list !!!");
            puts("------------------------------");
            printf("\n");
          }

          sum = 0;
          counter = 0;
      break;

      case 7:
          printf("\n");
          puts("------------------------------");
          printf("\n");

          fseek(gfptr, 0, SEEK_SET);

          while (!feof(gfptr))
          {
            fread(&temp, sizeof(grades), 1, gfptr);
            if (!feof(gfptr) && temp.check_grade == true && temp.student_id != 0) // !feof(gfptr) : شرط روبرو باعث می شود که از تکرار ریکورد آخر جلوگیری شود
            {
              sum = sum + temp.rules;
              counter++;
            }
          }

          GPA = sum / counter;

          printf("* rules GPA : %.2f\n", GPA);
          printf("\n");
          puts("------------------------------");
          printf("\n");

          if (counter == 0)
          {
            puts("I can't find this grade from the list !!!");
            puts("------------------------------");
            printf("\n");
          }

          sum = 0;
          counter = 0;
      break;

      case 8:
      break;
 
      default:
          puts("This is wrong number !!!");
          puts("Try again...");
      break;
    }
  }while (choice != 8);
}

void Conditionalstudents(FILE* fptr, FILE* gfptr)
{
  info chap;
  grades GPA_check;
  float Average;
  int counter = 0;

  fseek(fptr, 0, SEEK_SET);
  fseek(gfptr, 0, SEEK_SET);

  printf("\n");
  puts("------------------------------");
  printf("\n");

  while (!feof(fptr) && !feof(gfptr))
  {
    fread(&chap, sizeof(info), 1, fptr);
    fread(&GPA_check, sizeof(grades), 1, gfptr);

    if (!feof(gfptr) && GPA_check.check_grade == true && GPA_check.student_id != 0)
    {
      Average = (GPA_check.math1 + GPA_check.physic1 + GPA_check.computer_workshop + GPA_check.basic_programming + GPA_check.persian_lan + GPA_check.english_lan + GPA_check.rules) / 7;
    }

    if (Average < 12 && !feof(fptr) && chap.student_id != 0 && GPA_check.check_grade == true)
    {
      printf("* name : %s\n", chap.name);
      printf("* Last name : %s\n", chap.last_name);
      printf("* Student id : %u\n", chap.student_id);
      printf("* Student age : %u\n", chap.student_age);

      printf("\n");
      puts("------------------------------");

      counter++;
    }
  }

  if (counter == 0)
  {
    puts("In this semester, no student has been put on probation.");
    printf("\n");
    puts("------------------------------");
  }
}

void NoFailedLesson(FILE* gfptr)
{
  grades no_failed;
  check check_fail;

  check_fail.m1 = true;
  check_fail.ph1 = true;
  check_fail.cw = true;
  check_fail.bp = true;
  check_fail.pl = true;
  check_fail.el = true;
  check_fail.r = true;

  fseek(gfptr, 0, SEEK_SET);

  printf("\n");
  puts("------------------------------");
  printf("\n");

  while (!feof(gfptr))
  {
    fread(&no_failed, sizeof(grades), 1, gfptr);

    if (no_failed.math1 < 10 && !feof(gfptr) && no_failed.check_grade == true)
    {
      check_fail.m1 = false;
    }

    if (no_failed.physic1 < 10 && !feof(gfptr) && no_failed.check_grade == true)
    {
      check_fail.ph1 = false;
    }

    if (no_failed.computer_workshop < 10 && !feof(gfptr) && no_failed.check_grade == true)
    {
      check_fail.cw = false;
    }

    if (no_failed.basic_programming < 10 && !feof(gfptr) && no_failed.check_grade == true)
    {
      check_fail.bp = false;
    }

    if (no_failed.persian_lan < 10 && !feof(gfptr) && no_failed.check_grade == true)
    {
      check_fail.pl = false;
    }

    if (no_failed.english_lan < 10 && !feof(gfptr) && no_failed.check_grade == true)
    {
      check_fail.el = false;
    }
    
    if (no_failed.rules < 10 && !feof(gfptr) && no_failed.check_grade == true)
    {
      check_fail.r = false;
    }
  }

  if (check_fail.m1 == true)
  {
    puts("* No one failed in math1.");
  }
  else
  {
    puts("* A student or students have failed in math1.");
  }

  if (check_fail.ph1 == true)
  {
    puts("* No one failed in physic1.");
  }
  else
  {
    puts("* A student or students have failed in physic1.");
  }

  if (check_fail.cw == true)
  {
    puts("* No one failed in computer workshop.");
  }
  else
  {
    puts("* A student or students have failed in computer workshop.");
  }

  if (check_fail.bp == true)
  {
    puts("* No one failed in basic programming.");
  }
  else
  {
    puts("* A student or students have failed in basic programming.");
  }

  if (check_fail.pl == true)
  {
    puts("* No one failed in persian language.");
  }
  else
  {
    puts("* A student or students have failed in persian language.");
  }

  if (check_fail.el == true)
  {
    puts("* No one failed in english language.");
  }
  else
  {
    puts("* A student or students have failed in english language.");
  }

  if (check_fail.r == true)
  {
    puts("* No one failed in rules");
  }
  else
  {
    puts("* A student or students have failed in rules.");
  }

  printf("\n");
  puts("------------------------------");
  printf("\n");
}
