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

void initializePoint(Point* point, int set_size);
void setUpChoices(Choice* choice, int set_size);
int calcExpectedEarnings(Point* point, Choice* choice, int** earnings, double* expec_earnings, int set_size, int num_seq, int num_choices);
void openFile();
void outprint(int id, int x1, int x2, int x3, double earnings);

int main(void) {
    int num_choices = 3;
    int set_size = 3;
    int num_sequences = pow(set_size, 3);
    Point* point = (Point*)malloc(num_sequences*sizeof(Point));
    Choice* choice = (Choice*)malloc(num_choices*sizeof(Choice));
        setUpChoices(choice, set_size);
        initializePoint(point, set_size);

        int** earnings = (int**)malloc(num_sequences*sizeof(int*));
            for(int i = 0; i < num_sequences; i++){
                earnings[i] = (int*)malloc(num_choices*sizeof(int));
            }

            double* expec_earnings = (double*)malloc((num_sequences/2)*sizeof(double));
            openFile(); // initiated log file

       int num_earnings = calcExpectedEarnings(point, choice, earnings, expec_earnings, set_size, num_sequences, num_choices);
           for(int i = 0; i < num_earnings; i++)
                printf("%2f\n", expec_earnings[i]);
    }

void initializePoint(Point* point, int set_size) {
    int s[3] = { -1, 0, 1};
    int index = 0;
    int temp = 0;
        for(int i = 0; i < set_size; i++) {
            temp = s[0];
            s[0] = s[i];
            s[i] = temp;
            point[index].sequeunce[0] = s[0];
            for(int j = 0; j < set_size; j++) {
                point[index].sequeunce[1] = s[j];
                for(int k = 0; k < set_size; k++){
                    point[index].sequeunce[2] = s[k];
                    index++;
                    point[index].sequeunce[0] = s[0];
                    point[index].sequeunce[1] = s[j];
                }
            }
        }
}

void setUpChoices(Choice* choice, int set_size){
    int index = 0;
   for(int i = 1; i<set_size; i++) {
        for(int j = i+1; j<=set_size; j++){
            choice[index].i = i;
            choice[index].j = j;
            index++;
        }
   }
}

int calcExpectedEarnings(Point* point, Choice* choice, int** earnings, double* expec_earnings, int set_size, int num_seq, int num_choices) {
    int count = 0;
    for(int i = 0; i<num_seq; i++) {
            double exp_earnings = 0.0;
            for(int c = 0; c < num_choices; c++){
            earnings[i][c] = (point[i].sequeunce[choice[c].j - 1] - point[i].sequeunce[choice[c].i - 1]) % set_size;
             if(earnings[i][c] == 2)
                earnings[i][c] = -1;
            else if(earnings[i][c] == -2)
                earnings[i][c] = 1;
            }
            for(int c = 0; c < num_choices; c++){
                exp_earnings += (1.0/(double)(num_choices)) * earnings[i][c];
            }
            exp_earnings += 0.001;
            if(exp_earnings < 0){
                expec_earnings[count] = exp_earnings - 0.001;
                expec_earnings[count] = -expec_earnings[count];
                outprint(count + 1, point[i].sequeunce[0], point[i].sequeunce[1], point[i].sequeunce[2], expec_earnings[count]);
                count++;
            }
    }
    return count;
}

void openFile(){
FILE* file = fopen("./seq.txt", "w");
fclose(file);
}

void outprint(int id, int x1, int x2, int x3, double earnings){
    FILE* f = fopen("./seq.txt", "a");
    fprintf(f, "%d.\tExpectedEarnings: %2f\t Seq: %d %d %d\n", id, earnings, x1,x2,x3);
    fclose(f);
}
