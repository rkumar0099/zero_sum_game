#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


typedef struct {
    int sequeunce[5];
} Point;

typedef struct {
    int i;
    int j;
} Choice;

void initializePoint(Point* point, int size_set);
void setUpChoices(Choice* choice, int set_size);
int calcExpectedEarnings(Point* point, Choice* choice, int** earnings, double* expec_earnings, int set_size, int num_sequences, int num_choices, Point* newSetSeq);
void sortEarnings(double* expec_earnings, Point* newSetSeq, int num_earnings);
void openFile();
void outprint(int id, int x1, int x2, int x3, int x4, int x5, double earnings);


int main(void) {
    int num_choices = 10;
    int size_set = 5;
    int num_sequences = pow(size_set, size_set);
    int num_earnings = 0;
    Point point[num_sequences];
    Choice choice[num_choices];
        setUpChoices(choice, size_set);
        initializePoint(point, size_set);

        int** earnings = (int**)malloc(num_sequences*sizeof(int*));
            for(int i = 0; i < num_sequences; i++){
                earnings[i] = (int*)malloc(num_choices*sizeof(int));
            }

            double* expec_earnings = (double*)malloc((num_sequences / 2)*sizeof(double));
            Point* newSetSeq = (Point*)malloc((num_sequences/2) * sizeof(Point));
            openFile(); // initiated log file

       num_earnings = calcExpectedEarnings(point, choice, earnings, expec_earnings, size_set, num_sequences, num_choices, newSetSeq);
                free(point);
                free(choice);
                free(earnings);

                sortEarnings(expec_earnings,newSetSeq, num_earnings);
                int count = 0;
                double temp = expec_earnings[0];
                for(int i = 0; i<num_earnings; i++){
                        if((expec_earnings[i]-temp) > 0.01){
                            printf("The number of sequences that give %2f are %d\n", temp, count);
                            temp = expec_earnings[i];
                            count = 1;
                        } else{
                            count++;
                        }
                        printf("ExpEarnings: %2f\t Seq: %d %d %d %d %d\n", expec_earnings[i],
                               newSetSeq[i].sequeunce[0],newSetSeq[i].sequeunce[1],newSetSeq[i].sequeunce[2],
                               newSetSeq[i].sequeunce[3], newSetSeq[i].sequeunce[4]);
                        outprint(i+1, newSetSeq[i].sequeunce[0],newSetSeq[i].sequeunce[1],newSetSeq[i].sequeunce[2],
                                 newSetSeq[i].sequeunce[3],newSetSeq[i].sequeunce[4], expec_earnings[i]);
                }
                        printf("The number of sequences that give %2f are %d\n", temp, count);
    }

void initializePoint(Point* point, int size_set) {
    int s[5] = {-2, -1, 0, 1, 2};
    int index = 0;
    int temp = 0;
        for(int i = 0; i < size_set; i++) {
            point[index].sequeunce[0] = s[0];
            temp = s[0];
            s[0] = s[i];
            s[i] = temp;
            for(int j = 0; j < size_set; j++) {
                point[index].sequeunce[1] = s[j];
                for(int i1 = 0; i1 <size_set; i1++){
                    point[index].sequeunce[2] = s[i1];
                    for(int j1 = 0; j1<size_set; j1++){
                        point[index].sequeunce[3] = s[j1];
                            for(int k = 0; k < size_set; k++){
                            point[index].sequeunce[4] = s[k];
                            index++;
                            point[index].sequeunce[0] = s[0];
                            point[index].sequeunce[1] = s[j];
                            point[index].sequeunce[2] = s[i1];
                            point[index].sequeunce[3] = s[j1];
                    }
                }
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

int calcExpectedEarnings(Point* point, Choice* choice, int** earnings, double* expec_earnings,int size_set, int num_seq, int num_choices, Point* newSetSeq) {
    int count = 0;
    for(int i = 0; i<num_seq; i++) {
            double exp_earnings = 0;
            for(int c = 0; c < num_choices; c++){
            earnings[i][c] = (point[i].sequeunce[choice[c].j - 1] - point[i].sequeunce[choice[c].i - 1]) % size_set;
            if(earnings[i][c] == 3)
                earnings[i][c] = -2;
             else if(earnings[i][c] == 4)
                earnings[i][c] = -1;
            else if(earnings[i][c] == -3)
                    earnings[i][c] = 2;
            else if(earnings[i][c] == -4)
                earnings[i][c] = 1;
            }

            for(int c = 0; c < num_choices; c++){
               exp_earnings += (1.0/(double)(num_choices)) * (double)earnings[i][c];
            }
            exp_earnings += 0.001;

          if(exp_earnings < 0){
                expec_earnings[count] = -exp_earnings;
                for(int c = 0; c < size_set; c++)
                    newSetSeq[count].sequeunce[c] = point[i].sequeunce[c];
                    count++;
            }
    }
            return count;
}

void sortEarnings(double* expec_earnings, Point* newSetSeq, int num_earnings){
for(int i = 0; i < num_earnings-1; i++) {
	double temp = expec_earnings[i];
	Point tempPoint = newSetSeq[i];
	for(int j = num_earnings - 1; j>i; j--) {
	if(expec_earnings[j] < temp){
	expec_earnings[i] = expec_earnings[j];
	expec_earnings[j] = temp;
	temp = expec_earnings[i];
	newSetSeq[i] = newSetSeq[j];
	newSetSeq[j] = tempPoint;
	tempPoint = newSetSeq[i];
            }
        }
    }
}
void openFile(){
    FILE* f = fopen("./seq5.txt", "w");
    fclose(f);
}

void outprint(int id, int x1, int x2, int x3, int x4, int x5, double earnings){
    FILE* f = fopen("./seq5.txt", "a");
    fprintf(f, "%d.\tExpected Earnings: %2f\tSeq: %d %d %d %d %d\n",id, earnings, x1,x2,x3,x4,x5);
    fclose(f);
}
