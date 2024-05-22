#include <stdio.h>
#include <stdlib.h>
#include <math.h>




// Struct for students
typedef struct{
    char studentName[10];
    double subjectA;
    double subjectB;
    int total;
} student;




// Part A: Ascending order for Subject A
void ascendingOrder(student studentInfo[], int n){
    for(int i=1; i<n; i++){
        for(int j=0; j<n-i; j++){
            // Comparing current and next student's Subject A score
            if(studentInfo[j].subjectA > studentInfo[j+1].subjectA){
                student temp = studentInfo[j];
                studentInfo[j] = studentInfo[j+1];
                studentInfo[j+1] = temp;
            }
        }
    }
}




// Part B: Average score
double averageScore(double score[], int n){
    double sum = 0;
    for(int i=0; i<n; i++){
        sum += score[i];
    }
    return sum/n;
}




// Part B: Standard deviation
double standardDeviation(double score[], int n){
    double avg = averageScore(score, n);
    double squared = 0;
    double result = 0;
    // Summation (score - avg)^2 / size
    for(int i=0; i<n; i++){
        squared += (score[i]-avg)*(score[i]-avg);
    }
    result = sqrt(squared/n);
    return result;
}




// Display student information
void displayStudent(student studentInfo[], int total){
    printf("Student\tNo.\tA\tB\n");
    for(int i=1; i<total; i++){
        printf("%s\t%d\t%0.2lf\t%0.2lf\n", studentInfo[i].studentName, studentInfo[i].total,
        studentInfo[i].subjectA, studentInfo[i].subjectB);
    }
}




// Writing in file
void writeFile(FILE *ptr, student studentInfo[], int n){
    fprintf(ptr, "Student\tNo.\tA\tB\n");
    for(int i=1; i<n; i++){
        fprintf(ptr, "%s\t%d\t%0.2lf\t%0.2lf\n", studentInfo[i].studentName, studentInfo[i].total,
        studentInfo[i].subjectA, studentInfo[i].subjectB);
    }
}




int main(){
    FILE *ptr = NULL;
    int size = 8;
    student studentInfo[size];
    char str[100];
    int count = 0;
    char userInput;


    // Reading the file
    ptr = fopen("lab1.txt", "r");
    while(fgets(str, 100, ptr) != NULL){
        // Looking for Name, student #, subject A, subject B
        sscanf(str, "%s\t%d\t%lf\t%lf\n", studentInfo[count].studentName, &studentInfo[count].total,
        &studentInfo[count].subjectA, &studentInfo[count].subjectB);
        count++;
    }
    fclose(ptr);
    displayStudent(studentInfo, count);




    // User Interface
    while(userInput != 'e'){
        printf("Please enter a command (enter h for help): ");
        scanf("%c", &userInput);


        if(userInput == 'h'){


            // If user entered "h"
            printf("a/1 to obtain all the students that got diploma");
            printf("\nb/2 to arrange subject A in ascending order");
            printf("\nc/3 to calculate the average and standard deviation");
            printf("\nd/4 to save all the above results in an output file");
            printf("\ne to exit\n");


        } else if(userInput == 'a' || userInput == '1'){


            // If user entered "a" or "1"
            printf("\nAll the students that got diploma");
            printf("\nStudent\tNo.\tA\tB\n");
            for(int i=0; i<count; i++){
                // Students get a diploma if both their grades are >= 50
                if(studentInfo[i].subjectA >= 50 && studentInfo[i].subjectB >= 50){
                    printf("%s\t%d\t%0.2lf\t%0.2lf\n", studentInfo[i].studentName, studentInfo[i].total, studentInfo[i].subjectA, studentInfo[i].subjectB);
                }
            }


        } else if(userInput == 'b' || userInput == '2'){


            // If user entered "b" or "2"
            ascendingOrder(studentInfo, count);
            printf("\nSubject A in ascending order \n");
            displayStudent(studentInfo, count);


        } else if(userInput == 'c' || userInput == '3'){


            // If user entered "c" or "3"
            double AScore[size];
            double BScore[size];
            for(int i=0; i<size; i++){
                AScore[i] = studentInfo[i].subjectA;
                BScore[i] = studentInfo[i].subjectB;
            }
            double avgA = averageScore(AScore, size);
            double avgB = averageScore(BScore, size);
            double devA = standardDeviation(AScore,count);
            double devB = standardDeviation(BScore,count);


            printf("\nAverage of Subject A: %0.2lf \n", avgA);
            printf("\nAverage of Subject B: %0.2lf \n", avgB);
            printf("\nStandard Deviation of Subject A: %0.2lf \n", devA);
            printf("\nStandard Deviation of Subject B: %0.2lf \n", devB);


        } else if(userInput == 'd' || userInput == '4'){
           
            // If user entered "d" or "4"


            // Writing the file
            ptr = fopen("output.txt", "w");
            writeFile(ptr, studentInfo, size);


            // Save all the above results in output file
            printf("\nAll the students that got diploma");
            printf("\nStudent\tNo.\tA\tB\n");
            fprintf(ptr, "\nAll the students that got diploma");
            fprintf(ptr, "\nStudent\tNo.\tA\tB\n");
            for(int i=0; i<count; i++){
                if(studentInfo[i].subjectA >= 50 && studentInfo[i].subjectB >= 50){
                    printf("%s\t%d\t%0.2lf\t%0.2lf\n", studentInfo[i].studentName, studentInfo[i].total, studentInfo[i].subjectA, studentInfo[i].subjectB);
                    fprintf(ptr, "%s\t %d\t%0.2lf\t%0.2lf\n", studentInfo[i].studentName, studentInfo[i].total, studentInfo[i].subjectA, studentInfo[i].subjectB);
                }
            }


            ascendingOrder(studentInfo, count);
            printf("\nSubject A in ascending order \n");
            fprintf(ptr, "\nSubject A in ascending order \n");
            displayStudent(studentInfo, count);
            writeFile(ptr, studentInfo, size);


            double AScore[size];
            double BScore[size];
            for(int i=0; i<size; i++){
                AScore[i] = studentInfo[i].subjectA;
                BScore[i] = studentInfo[i].subjectB;
            }


            double avgA = averageScore(AScore, size);
            double avgB = averageScore(BScore, size);
            double devA = standardDeviation(AScore,count);
            double devB = standardDeviation(BScore,count);


            printf("\nAverage of Subject A: %0.2lf \n", avgA);
            printf("\nAverage of Subject B: %0.2lf \n", avgB);
            fprintf(ptr, "\nAverage of Subject A: %0.2lf \n", avgA);
            fprintf(ptr, "\nAverage of Subject B: %0.2lf \n", avgB);


            printf("\nStandard Deviation of Subject A: %0.2lf \n", devA);
            printf("\nStandard Deviation of Subject B: %0.2lf \n", devB);
            fprintf(ptr, "\nStandard Deviation of Subject A: %0.2lf \n", devA);
            fprintf(ptr, "\nStandard Deviation of Subject B: %0.2lf \n", devB);
            fclose(ptr);


        } else if(userInput == 'e'){
            // If user entered "e"
            exit(0);
        } else{
            // Restart when given a random input
            continue;
        }
       
    }


    return 0;
}
