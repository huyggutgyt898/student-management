#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <conio.h>

// Ðinh nghia cau truc ngay thang nam
struct date {
    int day;
    int month;
    int year;
};

// Ðinh nghia cau truc sinh vien
struct student {
    int id;
    char name[100];
    struct date dateOfBirth;
    int yearOld;
    char sex[10];
    float SubjectOneScore;
    float SubJectTwoScore;
    float SubjectThreeScore;
    float averageScore;
    char academicPerformance[10];
    char classCode[100];
    struct student* next;
};

typedef struct student SD;

// Khai bao nguyên mau ham
SD* studentInput();
void studentOutput(SD *sd);
void deleteLineBreak(char x[]);
float averageScore(SD *sd);
void ageCalculation(SD *sd);
void Classification(SD *sd);
void studentListInput(SD **head);
void studentListOutput(SD *head);
float findMax_averageScore(SD *head);
SD* findMin_yearOld(SD *head);
void listOfExcellentStudents(SD *head);
int findStudentByName(SD *head, char name[]);
void exportStudentListByClass(SD *head, char Class[]);
void chuyenDoi(char x[]);
void deleteStudentByID(SD **head, int id);
void SortStudentsBy_GPA(SD **head);
void SortStudentsBy_name(SD **head);
void enterAnyKey();
void importStudentListFromFile(SD **head);
void ExportStudentListToFile(SD *head);
void freeList(SD **head);

int main() {
    SD* head = NULL;
    int choice;

    do {
        printf("\n-----------MENU-----------\n");
        printf("\n0- THOAT CHUONG TRINH");
        printf("\n1- NHAP DANH SACH SINH VIEN");
        printf("\n2- HIEN THI DANH SACH SINH VIEN");
        printf("\n3- TIM DIEM TRUNG BINH CAO NHAT");
        printf("\n4- TIM SINH VIEN TRE TUOI NHAT");
        printf("\n5- XUAT DANH SACH THEO LOP");
        printf("\n6- DANH SACH SINH VIEN GIOI");
        printf("\n7- SAP XEP THEO DIEM TRUNG BINH");
        printf("\n8- SAP XEP THEO TEN");
        printf("\n9- TIM SINH VIEN THEO TEN");
        printf("\n10- XOA SINH VIEN THEO ID");
        printf("\n11- NHAP TU FILE");
        printf("\n12- XUAT RA FILE");
        printf("\nLUA CHON: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                studentListInput(&head);
                enterAnyKey();
                break;
            case 2:
                studentListOutput(head);
                enterAnyKey();
                break;
            case 3: {
                float max = findMax_averageScore(head);
                printf("\nDIEM TRUNG BINH CAO NHAT LA: %.2f", max);
                enterAnyKey();
                break;
            }
            case 4: {
                SD* youngest = findMin_yearOld(head);
                if (youngest != NULL) {
                    printf("\nSINH VIEN TRE TUOI NHAT LA:");
                    studentOutput(youngest);
                } else {
                    printf("\nDANH SACH RONG!");
                }
                enterAnyKey();
                break;
            }
            case 5: {
                char Class[100];
                printf("\nNHAP TEN LOP CAN XUAT: ");
                getchar();
                fgets(Class, sizeof(Class), stdin);
                deleteLineBreak(Class);
                exportStudentListByClass(head, Class);
                enterAnyKey();
                break;
            }
            case 6:
                listOfExcellentStudents(head);
                enterAnyKey();
                break;
            case 7:
                SortStudentsBy_GPA(&head);
                printf("\nDA SAP XEP THEO DIEM TRUNG BINH!");
                enterAnyKey();
                break;
            case 8:
                SortStudentsBy_name(&head);
                printf("\nDA SAP XEP THEO TEN!");
                enterAnyKey();
                break;
            case 9: {
                char name[100];
                printf("\nNHAP TEN CAN TIM: ");
                getchar();
                fgets(name, sizeof(name), stdin);
                deleteLineBreak(name);
                if (!findStudentByName(head, name)) {
                    printf("\nKHONG TIM THAY SINH VIEN!");
                }
                enterAnyKey();
                break;
            }
            case 10: {
                int id;
                printf("\nNHAP ID CAN XOA: ");
                scanf("%d", &id);
                deleteStudentByID(&head, id);
                enterAnyKey();
                break;
            }
            case 11:
                importStudentListFromFile(&head);
                enterAnyKey();
                break;
            case 12:
                ExportStudentListToFile(head);
                enterAnyKey();
                break;
            case 0:
                freeList(&head);
                printf("\nDA THOAT CHUONG TRINH!");
                break;
            default:
                printf("\nLUA CHON KHONG HOP LE!");
                enterAnyKey();
                break;
        }
    } while(choice != 0);

    return 0;
}

void deleteLineBreak(char x[]) {
    size_t len = strlen(x);
    if (x[len-1] == '\n') {
        x[len-1] = '\0';
    }
}

SD* studentInput() {
    SD* sd = (SD*)malloc(sizeof(SD));

    printf("\nID: ");
    scanf("%d", &sd->id);

    printf("\nHO TEN: ");
    getchar();
    fgets(sd->name, sizeof(sd->name), stdin);
    deleteLineBreak(sd->name);

    printf("\nGIOI TINH: ");
    fgets(sd->sex, sizeof(sd->sex), stdin);
    deleteLineBreak(sd->sex);

    printf("\nNGAY SINH (dd mm yyyy): ");
    scanf("%d %d %d", &sd->dateOfBirth.day, &sd->dateOfBirth.month, &sd->dateOfBirth.year);
    ageCalculation(sd);

    printf("\nDIEM MON 1: ");
    scanf("%f", &sd->SubjectOneScore);

    printf("\nDIEM MON 2: ");
    scanf("%f", &sd->SubJectTwoScore);

    printf("\nDIEM MON 3: ");
    scanf("%f", &sd->SubjectThreeScore);

    sd->averageScore = averageScore(sd);
    Classification(sd);

    printf("\nMA LOP: ");
    getchar();
    fgets(sd->classCode, sizeof(sd->classCode), stdin);
    deleteLineBreak(sd->classCode);

    sd->next = NULL;
    return sd;
}

void studentOutput(SD *sd) {
    printf("+-------+----------------------+----------+----------------+----------+--------+--------+--------+----------------+-----------------+-----------------+\n");
    printf("| %-5s | %-20s | %-8s | %-14s | %-8s | %-6s | %-6s | %-6s | %-14s | %-15s | %-15s |\n",
        "ID", "TEN", "GIOI TINH", "NGAY SINH", "TUOI", "MON 1", "MON 2", "MON 3", "DIEM TB", "XEP LOAI", "LOP");
    printf("+-------+----------------------+----------+----------------+----------+--------+--------+--------+----------------+-----------------+-----------------+\n");
    printf("| %-5d | %-20s | %-8s | %02d/%02d/%04d     | %-8d | %-6.2f | %-6.2f | %-6.2f | %-14.2f | %-15s | %-15s |\n",
        sd->id, sd->name, sd->sex,
        sd->dateOfBirth.day, sd->dateOfBirth.month, sd->dateOfBirth.year,
        sd->yearOld, sd->SubjectOneScore, sd->SubJectTwoScore, sd->SubjectThreeScore,
        sd->averageScore, sd->academicPerformance, sd->classCode);
    printf("+-------+----------------------+----------+----------------+----------+--------+--------+--------+----------------+-----------------+-----------------+\n");
}

float averageScore(SD *sd) {
    return (sd->SubjectOneScore + sd->SubJectTwoScore + sd->SubjectThreeScore) / 3;
}

void ageCalculation(SD *sd) {
    time_t now = time(NULL);
    struct tm *local = localtime(&now);
    int currentYear = local->tm_year + 1900;
    sd->yearOld = currentYear - sd->dateOfBirth.year;
}

void Classification(SD *sd) {
    float avg = sd->averageScore;
    if (avg >= 9) strcpy(sd->academicPerformance, "XUAT SAC");
    else if (avg >= 8) strcpy(sd->academicPerformance, "GIOI");
    else if (avg >= 6.5) strcpy(sd->academicPerformance, "KHA");
    else if (avg >= 5) strcpy(sd->academicPerformance, "TRUNG BINH");
    else strcpy(sd->academicPerformance, "YEU");
}

void studentListInput(SD **head) {
    int n;
    printf("\nNHAP SO LUONG SINH VIEN: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("\nNHAP THONG TIN SINH VIEN THU %d", i + 1);
        SD *newStudent = studentInput();

        if (*head == NULL) {
            *head = newStudent;
        } else {
            SD *current = *head;
            while (current->next != NULL) {
                current = current->next;
            }
            current->next = newStudent;
        }
    }
}

void studentListOutput(SD *head) {
    if (head == NULL) {
        printf("\nDANH SACH RONG!");
        return;
    }

    SD *current = head;
    while (current != NULL) {
        studentOutput(current);
        current = current->next;
    }
}

float findMax_averageScore(SD *head) {
    if (head == NULL) return 0;

    float max = head->averageScore;
    SD *current = head->next;

    while (current != NULL) {
        if (current->averageScore > max) max = current->averageScore;
        current = current->next;
    }
    return max;
}

SD* findMin_yearOld(SD *head) {
    if (head == NULL) return NULL;

    SD *minNode = head;
    SD *current = head->next;

    while (current != NULL) {
        if (current->yearOld < minNode->yearOld) minNode = current;
        current = current->next;
    }
    return minNode;
}

void listOfExcellentStudents(SD *head) {
    if (head == NULL) {
        printf("\nDANH SACH RONG!");
        return;
    }

    SD *current = head;
    int count = 0;

    while (current != NULL) {
        if (strcmp(current->academicPerformance, "GIOI") == 0 || strcmp(current->academicPerformance, "XUAT SAC") == 0) {
            studentOutput(current);
            count++;
        }
        current = current->next;
    }

    if (count == 0) printf("\nKHONG CO SINH VIEN GIOI!");
}

int findStudentByName(SD *head, char name[]) {
    if (head == NULL) return 0;

    SD *current = head;
    int found = 0;
    char tempName[100], tempSearch[100];
    strcpy(tempSearch, name);
    chuyenDoi(tempSearch);

    while (current != NULL) {
        strcpy(tempName, current->name);
        chuyenDoi(tempName);

        if (strstr(tempName, tempSearch) != NULL) {
            studentOutput(current);
            found = 1;
        }
        current = current->next;
    }
    return found;
}

void exportStudentListByClass(SD *head, char Class[]) {
    if (head == NULL) {
        printf("\nDANH SACH RONG!");
        return;
    }

    SD *current = head;
    int count = 0;

    while (current != NULL) {
        if (strcmp(current->classCode, Class) == 0) {
            studentOutput(current);
            count++;
        }
        current = current->next;
    }

    if (count == 0) printf("\nKHONG CO SINH VIEN TRONG LOP %s", Class);
}

void chuyenDoi(char x[]) {
    for (int i = 0; x[i] != '\0'; i++) {
        if (x[i] >= 'A' && x[i] <= 'Z') x[i] += 32;
    }
}

void deleteStudentByID(SD **head, int id) {
    if (*head == NULL) {
        printf("\nDANH SACH RONG!");
        return;
    }

    SD *current = *head, *prev = NULL;

    while (current != NULL && current->id != id) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("\nKHONG TIM THAY ID %d!", id);
        return;
    }

    if (prev == NULL) *head = current->next;
    else prev->next = current->next;

    free(current);
    printf("\nDA XOA SINH VIEN CO ID %d!", id);
}

void SortStudentsBy_GPA(SD **head) {
    if (*head == NULL || (*head)->next == NULL) return;

    SD *sorted = NULL;
    SD *current = *head;

    while (current != NULL) {
        SD *next = current->next;

        if (sorted == NULL || current->averageScore >= sorted->averageScore) {
            current->next = sorted;
            sorted = current;
        } else {
            SD *temp = sorted;
            while (temp->next != NULL && temp->next->averageScore > current->averageScore) {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }
        current = next;
    }
    *head = sorted;
}

void SortStudentsBy_name(SD **head) {
    if (*head == NULL || (*head)->next == NULL) return;

    SD *sorted = NULL;
    SD *current = *head;

    while (current != NULL) {
        SD *next = current->next;

        if (sorted == NULL || strcmp(current->name, sorted->name) <= 0) {
            current->next = sorted;
            sorted = current;
        } else {
            SD *temp = sorted;
            while (temp->next != NULL && strcmp(current->name, temp->next->name) > 0) {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }
        current = next;
    }
    *head = sorted;
}

void enterAnyKey() {
    printf("\nNHAN PHIM BAT KY DE TIEP TUC...");
    getch();
}

void importStudentListFromFile(SD **head) {
    FILE *f = fopen("students.txt", "r");
    if (f == NULL) {
        printf("\nKHONG MO DUOC FILE!");
        return;
    }

    while (!feof(f)) {
        SD *newStudent = (SD*)malloc(sizeof(SD));
        if (fscanf(f, "%d\n", &newStudent->id) != 1) {
            free(newStudent);
            break;
        }

        fgets(newStudent->name, 100, f);
        deleteLineBreak(newStudent->name);

        fgets(newStudent->sex, 10, f);
        deleteLineBreak(newStudent->sex);

        fscanf(f, "%d %d %d\n", &newStudent->dateOfBirth.day, &newStudent->dateOfBirth.month, &newStudent->dateOfBirth.year);
        ageCalculation(newStudent);

        fscanf(f, "%f %f %f\n", &newStudent->SubjectOneScore, &newStudent->SubJectTwoScore, &newStudent->SubjectThreeScore);
        newStudent->averageScore = averageScore(newStudent);
        Classification(newStudent);

        fgets(newStudent->classCode, 100, f);
        deleteLineBreak(newStudent->classCode);

        newStudent->next = NULL;

        if (*head == NULL) {
            *head = newStudent;
        } else {
            SD *current = *head;
            while (current->next != NULL) current = current->next;
            current->next = newStudent;
        }
    }

    fclose(f);
    printf("\nDA NHAP DU LIEU TU FILE!");
}

void ExportStudentListToFile(SD *head) {
    if (head == NULL) {
        printf("\nDANH SACH RONG!");
        return;
    }

    FILE *f = fopen("students_output.txt", "w");
    if (f == NULL) {
        printf("\nKHONG TAO DUOC FILE!");
        return;
    }

    SD *current = head;
    while (current != NULL) {
        fprintf(f, "%d\n%s\n%s\n%d %d %d\n%.2f %.2f %.2f\n%s\n",
                current->id,
                current->name,
                current->sex,
                current->dateOfBirth.day, current->dateOfBirth.month, current->dateOfBirth.year,
                current->SubjectOneScore, current->SubJectTwoScore, current->SubjectThreeScore,
                current->classCode);
        current = current->next;
    }

    fclose(f);
    printf("\nDA XUAT DU LIEU RA FILE!");
}

void freeList(SD **head) {
    SD *current = *head;
    while (current != NULL) {
        SD *temp = current;
        current = current->next;
        free(temp);
    }
    *head = NULL;
}
