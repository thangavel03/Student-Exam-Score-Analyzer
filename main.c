#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Student Exam Score Analyzer Project
//By THANGAVEL R A


//Student details structure
typedef struct {
    int rollNumber;
    char name[50];
    float *marks;
} Student;

Student *students;
int studentCount = 0;
int maxStudents = 0;
int maxSubjects = 0;


//Adding new student details
void addStudent() {
    if (studentCount >= maxStudents) {
        printf("Student limit reached!\n");
        return;
    }
    printf("Enter Roll Number: ");
    scanf("%d", &students[studentCount].rollNumber);
    getchar();

    printf("Enter name: ");
    fgets(students[studentCount].name, 50, stdin);
    students[studentCount].name[strcspn(students[studentCount].name, "\n")] = '\0';

    students[studentCount].marks = (float *)malloc(maxSubjects * sizeof(float));
    for (int i = 0; i < maxSubjects; i++) {
        printf("Enter marks for Subject %d: ", i + 1);
        scanf("%f", &students[studentCount].marks[i]);
    }

    studentCount++;
    printf("Student Added Successfully!\n");
}

//Displaying all the students
void displayStudents() {
    if (studentCount == 0) {
        printf("No students added!\n");
        return;
    }

    printf("\nRoll Number\tName\t\tMarks\n");
    printf("----------------------------------\n");
    for (int i = 0; i < studentCount; i++) {
        printf("%d\t\t%s\t\t", students[i].rollNumber, students[i].name);

        for (int j = 0; j < maxSubjects; j++) {
            printf("%.2f ", students[i].marks[j]);
        }
        printf("\n");
    }
}

//Analysis of performance of the students in exam
void analyzePerformance() {
    if (studentCount == 0) {
        printf("No data available for analysis!\n");
        return;
    }

    float *totalMarks = (float *)calloc(maxSubjects, sizeof(float));
    float *highestMarks = (float *)calloc(maxSubjects, sizeof(float));
    float *lowestMarks = (float *)calloc(maxSubjects, sizeof(float));

    for (int i = 0; i < maxSubjects; i++) {
        highestMarks[i] = students[0].marks[i];
        lowestMarks[i] = students[0].marks[i];
    }

    for (int i = 0; i < studentCount; i++) {
        for (int j = 0; j < maxSubjects; j++) {
            totalMarks[j] += students[i].marks[j];
            if (students[i].marks[j] > highestMarks[j])
                highestMarks[j] = students[i].marks[j];
            if (students[i].marks[j] < lowestMarks[j])
                lowestMarks[j] = students[i].marks[j];
        }
    }

    printf("\nClass Performance Analysis:\n");
    for (int i = 0; i < maxSubjects; i++) {
        printf("Subject %d\n", i + 1);
        printf("Average Marks: %.2f\n", totalMarks[i] / studentCount);
        printf("Highest Marks: %.2f\n", highestMarks[i]);
        printf("Lowest Marks: %.2f\n", lowestMarks[i]);
    }

    free(totalMarks);
    free(highestMarks);
    free(lowestMarks);
}

//Searching for a particular student details
void searchStudent() {
    if (studentCount == 0) {
        printf("No students available to search!\n");
        return;
    }
    int rollNumber;
    printf("Enter Roll Number: ");
    scanf("%d", &rollNumber);

    for (int i = 0; i < studentCount; i++) {
        if (students[i].rollNumber == rollNumber) {
            printf("\nStudent Found:\n");
            printf("Roll Number: %d\n", students[i].rollNumber);
            printf("Name: %s\n", students[i].name);
            printf("Marks: ");
            for (int j = 0; j < maxSubjects; j++) {
                printf("%.2f ", students[i].marks[j]);
            }
            printf("\n");
            return;
        }
    }
    printf("Student with roll number %d not found!\n", rollNumber);
}


//The main function
int main() {
    int choice;

    printf("Enter the maximum number of Students: ");
    scanf("%d", &maxStudents);
    printf("Enter maximum number of Subjects: ");
    scanf("%d", &maxSubjects);

    students = (Student *)malloc(maxStudents * sizeof(Student));

    do {
        printf("Student Exam Score Analyzer\n");
        printf("1. Add Student\n");
        printf("2. Display All Students\n");
        printf("3. Analyze Performance\n");
        printf("4. Search Students\n");
        printf("5. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                displayStudents();
                break;
            case 3:
                analyzePerformance();
                break;
            case 4:
                searchStudent();
                break;
            case 5:
                printf("Exiting Application. Goodbye!\n");
                break;
            default:
                printf("Invalid Choice. Please try again!\n");
        }
    } while (choice != 5);

    free(students);
    return 0;
}
