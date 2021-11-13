#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string>

using namespace std;

#define POPULATION 1000
#define MUTATION .01
#define ELITISM .1

int size;
string input;
typedef struct{
  string gene;
  int fit;
} people;
people genome[POPULATION];

int random(int, int);

int fitness(const string);

void sort();

people crossover(people, people);

int main(void){
    getline (cin, input);
    int i, j, generation = 0;
    size = input.length();
    srand (time(0));

    for (i = 0; i < POPULATION; i++){
        string chromosome = "";
        for (j = 0; j < size; j++)
            chromosome += (char)(32 + (rand() % 95));
        genome[i].gene = chromosome;
        genome[i].fit = fitness(genome[i].gene);
    }

    sort();

    while (genome[0].fit){
      people new_gen[POPULATION];
      for (i = 0; i < POPULATION*ELITISM; i++)
          new_gen[i] = genome[i];
      for ( ; i < POPULATION; i++){
          int p1 = random(0, POPULATION*.5),
              p2 = random(0, POPULATION*.5);
          new_gen[i] = crossover(genome[p1], genome[p2]);
      }

      for (i = 0; i < POPULATION; i++)
        genome[i] = new_gen[i];
      sort();
      if (generation % 100 == 0)
          cout<<"Gen "<<generation<<": "<<genome[0].gene<<" Fitness: "<<genome[0].fit<<endl;
      generation++;
    }

    cout<<endl<<"Gen "<<generation<<": "<<genome[0].gene<<" Fitness: "<<genome[0].fit<<endl;

    return 0;
}

int random(int low, int high){
    return low + (rand() % (high - low + 1));
}

int fitness(const string genome){
    int score = 0, i, temp;
    for (i = 0; i < size; i++){
        temp = (int)genome[i] - (int)input[i];
        score += abs(temp);
    }
    return score;
}

void sort(){
    int i, j;
    for (i = 0; i < POPULATION; i++)
        for (j = i + 1; j < POPULATION; j++)
            if (genome[i].fit > genome[j].fit){
                people temp;
                temp = genome[i];
                genome[i] = genome[j];
                genome[j] = temp;
            }
}

people crossover(people parent1, people parent2){
    int i, p = 50 - (49*MUTATION), r;
    people child;
    string chromosome = "";
    for (i = 0; i < size; i++){
        r = random(1, 100);
        if (r <= MUTATION*100)
            chromosome += (char)random(32, 126);
        else if (r < p)
            chromosome += parent1.gene[i];
        else
            chromosome += parent2.gene[i];
    }
    child.gene = chromosome;
    child.fit = fitness(child.gene);
    return child;
}
