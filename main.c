#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


typedef struct {
    int sequeunce[3];
} Point;

typedef struct {
    int i;
    int j;
} Choice;

void initializePoint(Point* point);
void setUpChoices(Choice* choice, int size_set);
void calcExpectedEarnings(Point* point, Choice* choice, int** earnings, double* expec_earnings, int set_size, int num_choices);
void openFile();
void outprint(int x1, int x2, int x3, double earnings);


int main(void) {
    int num_choices = 3;
    int size_set = 3;
    int num_sequences = pow(size_set, 3);
    Point* point = (Point*)malloc(num_sequences*sizeof(Point));
    Choice* choice = (Choice*)malloc(num_choices*sizeof(Choice));
             setUpChoices(choice, size_set);

        for(int i = 0; i < num_choices; i++) {
            printf("%d %d\n", choice[i].i, choice[i].j);
        }
            printf("\n");

        initializePoint(point);
        for(int i = 0; i<num_sequences; i++){
                printf("%d %d %d\n", point[i].sequeunce[0], point[i].sequeunce[1], point[i].sequeunce[2]);
        }

        int** earnings = (int**)malloc(num_sequences*sizeof(int*));
            for(int i = 0; i < num_sequences; i++){
                earnings[i] = (int*)malloc(num_choices*sizeof(int));
            }

            double* expec_earnings = (double*)malloc(num_sequences*sizeof(double));
            openFile(); // initiated log file

        calcExpectedEarnings(point, choice, earnings, expec_earnings, num_sequences, num_choices);
            for(int i = 0; i < num_sequences; i++)
                printf("%2f\n", expec_earnings[i]);
    }

void initializePoint(Point* point) {
    int s[3] = { -1, 0, 1};
    int p1, p2, p3;
    int index = 0;
    int temp = 0;
        for(int i = 0; i < 3; i++) {
            temp = s[0];
            s[0] = s[i];
            s[i] = temp;
            point[index].sequeunce[0] = s[0];
            for(int j = 0; j < 3; j++) {
                point[index].sequeunce[1] = s[j];
                for(int k = 0; k < 3; k++){
                    point[index].sequeunce[2] = s[k];
                    index++;
                    point[index].sequeunce[0] = s[0];
                    point[index].sequeunce[1] = s[j];
                }
            }
        }
        printf("Count: %d\n", index);
}

void setUpChoices(Choice* choice, int size_set){
    int index = 0;
   for(int i = 1; i<size_set; i++) {
        for(int j = i+1; j<=size_set; j++){
            choice[index].i = i;
            choice[index].j = j;
            index++;
        }
   }
}

void calcExpectedEarnings(Point* point, Choice* choice, int** earnings, double* expec_earnings, int set_size, int num_choices) {
    int count = 0;
    for(int i = 0; i<set_size; i++) {
            for(int c = 0; c < num_choices; c++){
            earnings[i][c] = (point[i].sequeunce[choice[c].j - 1] - point[i].sequeunce[choice[c].i - 1]) % 3;
           // if(earnings[i][c] == 3)
                //earnings[i][c] = -2;
             if(earnings[i][c] == 2)
                earnings[i][c] = -1;
            else if(earnings[i][c] == -2)
                earnings[i][c] = 1;
           // else if(earnings[i][c] == -4)
                //earnings[i][c] = 1;

            }
            for(int c = 0; c < num_choices; c++){
                expec_earnings[i] += (1.0/3.0) * earnings[i][c];
            }
            if(expec_earnings[i] < 0){
                outprint(point[i].sequeunce[0], point[i].sequeunce[1], point[i].sequeunce[2], expec_earnings[i]);
                count++;
            }
    }
        printf("Count: %d\n", count);
}

void openFile(){
FILE* file = fopen("./seq.txt", "w");
fclose(file);
}

void outprint(int x1, int x2, int x3, double earnings){
    FILE* f = fopen("./seq.txt", "a");
    fprintf(f, "seq: %d %d %d\texpected-earnings: %f\n", x1, x2, x3, earnings);
    fclose(f);
}
