#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char name[256];
    int registration_number;
    int grades[5];
} student;

void get_students(student *students, int n)
{
    for (int i = 0; i < n; ++i)
    {
        printf("Name of student %d: ", i);
        scanf("%s", &students[i].name);
        printf("Registration number of student %d: ", i);
        scanf("%d", &students[i].registration_number);
        printf("Grades of student %d: ", i);
        scanf("%d %d %d %d %d", &students[i].grades[0], &students[i].grades[1], &students[i].grades[2], &students[i].grades[3], &students[i].grades[4]);
        printf("\n");
    }
}

float get_average(student s)
{
    return (s.grades[0] + s.grades[1] + s.grades[2] + s.grades[3] + s.grades[4]) * 1.0 / 5;
}

void sort(student *students, int n)
{
    int change = 1;
    while (change != 0)
    {
        change = 0;
        for (int i = 0; i < n - 1; ++i)
            if (get_average(students[i]) < get_average(students[i + 1]))
            {
                student aux;
                aux = students[i + 1];
                students[i + 1] = students[i];
                students[i] = aux;
                change = 1;
            }
            else if (get_average(students[i]) == get_average(students[i + 1]) && strcmp(students[i].name, students[i + 1].name) > 0)
                {
                    student aux;
                    aux = students[i + 1];
                    students[i + 1] = students[i];
                    students[i] = aux;
                    change = 0;
                }
    }
}

void print_students(student *students, int n)
{
    for (int i = 0; i < n; ++i)
    {
        printf("Name of student %d: %s\n", i, students[i].name);
        printf("Registration number of student %d: %d\n", i, students[i].registration_number);
        printf("Grades of student %d: %d %d %d %d %d\n\n", i, students[i].grades[0], students[i].grades[1], students[i].grades[2], students[i].grades[3], students[i].grades[4]);
    }
}

int main()
{
    int n;
    printf("Give the number of students: ");
    scanf("%d", &n);
    student *students = malloc(n * sizeof(student));
    get_students(students, n);
    sort(students, n);
    printf("Students after sorting:\n");
    print_students(students, n);
}
