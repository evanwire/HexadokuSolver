#include<stdio.h>
#include<stdlib.h>

struct node{
  int data;
  struct node* next;
};


int** convertMatrix(char**);
void freeIntMatrix(int**);
int checkSanity(int**);
void freeLL(struct node*);
void solveBoard(int**);
char** convertBackToHex(int**);
int definiteSolvable(int*);
int determineValue(int*);
int* determineIndex(int*, int, int, int*);
int checkSolved(int**);



int main(int argc, char** argv){
  
  char* file_name = argv[1];
  FILE * file = fopen(file_name, "r");

  if(file == NULL){
    printf("File %s does not exist.", file_name);
  }

  char ** matrix;

  matrix = malloc(16 * sizeof(char*));
  
  for(int i = 0; i < 16; i++){
    matrix[i] = malloc(16 * sizeof(char));
  }

  for(int i = 0; i < 16; i++){
    for(int j = 0; j < 16; j++){
      char temp;
      char disposable;
      fscanf(file, "%c%c", &temp, &disposable);
      matrix[i][j] = temp;
    }
  }

  int** m = convertMatrix(matrix);

  int sane = checkSanity(m);

  if(sane == 0){
    solveBoard(m);

  }else{
    printf("no-solution");
  }

  freeIntMatrix(m);

  for(int i = 0; i < 16; i++){
    free(matrix[i]);
  }
  free(matrix);
  fclose(file);

  return 0;
      
}


int** convertMatrix(char** matrix){
  int** result;
  
  result = malloc(16 * sizeof(int*));
  
  for(int i = 0; i < 16; i++){
    result[i] = malloc(16 * sizeof(int));
  }

  for(int i = 0; i < 16; i++){
    for(int j = 0; j < 16; j++){

      
      if(matrix[i][j] >= 48 && matrix[i][j]<= 57){
	result[i][j] = (int)matrix[i][j] - 48;
      }else if(matrix[i][j] >= 65 && matrix[i][j] <= 70){
	result[i][j] = (int)matrix[i][j] - 55;
      }else{
	result[i][j] = -1;
      }
    }
  }

  return result;
  
}

void freeIntMatrix(int** matrix){
  for(int i = 0; i < 16; i++){
    free(matrix[i]);
  }
  
  free(matrix);
}


int checkSanity(int** matrix){
  for(int i = 0; i < 16; i++){
    struct node* head = malloc(sizeof(struct node));
    head->data = matrix[i][0];
    head->next = NULL;
    for(int j = 1; j < 16; j++){
      struct node* temp = head;

      while(temp != NULL){
	if(temp->data == matrix[i][j]){
	  if(matrix[i][j] != -1){
	    return 1;
	  }
	}
	temp = temp->next;
      }

      
      struct node* temp2 = malloc(sizeof(struct node));
      temp2->data = matrix[i][j];
      temp2->next = head;
      head = temp2;
    }
    
    freeLL(head);
      
  }

  for(int i = 0; i < 16; i++){
    struct node* head = malloc(sizeof(struct node));
    head = NULL;
    for(int j = 0; j < 16; j++){
      struct node* temp = head;
      
      while(temp != NULL){
	if(temp->data == matrix[j][i]){
	  if(matrix[j][i] != -1){
	    return 1;
	  }
	}
	temp = temp->next;
      }
      
      struct node* temp2 = malloc(sizeof(struct node));
      temp2->data = matrix[j][i];
      temp2->next = head;
      head = temp2;
    }
    
    freeLL(head);
  }
  
  for(int x = 0; x < 4; x++){
    for(int y = 0; y < 4; y++){
      struct node* head = malloc(sizeof(struct node));
      head = NULL;
      
      for(int i = 0; i < 4; i++){
	for(int j = 0; j < 4; j++){
	  struct node* temp = head;
	  
	  while(temp != NULL){
	    if(temp->data == matrix[i + x * 4][j + y * 4]){
	      if(matrix[i + x * 4][j + y * 4] != -1){
		return 1;
	      }
	    }
	    temp = temp->next;
	  }
	  
	  struct node*temp2 = malloc(sizeof(struct node));
	  temp2->data = matrix[i + x * 4][j + y * 4];
	  temp2->next = head;
	  head = temp2;
	}
      }
      freeLL(head);
    }
  }
	
	  
      

  return 0;
    
}

void freeLL(struct node* head){
  while(head != NULL){
    struct node* temp = head;
    head = head->next;
    free(temp);
  }
}

void solveBoard(int** matrix){
  
  int solved = 0;
  while(solved == 0){

    int** ditto;
    ditto = malloc(16 * sizeof(int*));
    for(int i = 0; i < 16; i++){
      ditto[i] = malloc(16 * sizeof(int));
    }


    for(int i = 0; i < 16; i++){
      for(int j = 0; j < 16; j++){
	ditto[i][j] = matrix[i][j];
      }
    }


    for(int i = 0; i < 16; i++){
      for(int j = 0; j < 16; j++){
	if(ditto[i][j] == -1){
	  int possibleSolutions[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

	  for(int x = 0; x < 16; x++){
	    int value = ditto[i][x];
	    if(value != -1){
	      possibleSolutions[value] = 1;
	    }
	  }
	  
	  for(int x = 0; x < 16; x++){
	    int value = ditto[x][j];
	    if(value != -1){
	      possibleSolutions[value] = 1;
	    }
	  }

	  for(int x = 0; x < 4; x++){
	    for(int y = 0; y < 4; y++){
	      int m = (i / 4) * 4;
	      int n = (j / 4) * 4;

	      int value = ditto[m + x][n + y];
	      if(value != -1){
		possibleSolutions[value] = 1;
	      }
	    }
	  }


	  int possSol = 0;
	  for(int x = 0; x < 16; x++){
	    if(possibleSolutions[x] == 0){
	      possSol++;
	    }
	  }
	  
	  if(possSol == 1){
	    int value = -1;
	    for(int x = 0; x < 16; x++){
	      if(possibleSolutions[x] == 0){
		value = x;
	      }
	    }
	    ditto[i][j] = value;
	    int sane = checkSanity(ditto);
	    if(sane == 0){
	      continue;
	    }else{
	      printf("no-solution");
	      return;
	    }
	  }else{
	    continue;
	  }
	}
      }
      

      
      
    }

    int solved = checkSolved(ditto);
    if(solved == 0){
      char** board = convertBackToHex(ditto);
      for(int i = 0; i < 16; i++){
	for(int j = 0; j < 16; j++){
	  printf("%c\t", board[i][j]);
	}
	printf("\n");
      }
      
      return;
    }
    
    int sameBoard = 0;
    for(int i = 0; i < 16; i++){
      for(int j = 0; j < 16; j++){
	if(matrix[i][j] != ditto[i][j]){
	  sameBoard = 1;
	}
      }
    }
    
    if(sameBoard == 0){
      printf("not-solved");
      return;
    }
    
    for(int i = 0; i < 16; i++){
      for(int j = 0; j < 16; j++){
	matrix[i][j] = ditto[i][j];
      }
    }

    freeIntMatrix(ditto);
  }

  
}

int checkSolved(int** matrix){
  for(int i = 0; i < 16; i++){
    for(int j = 0; j < 16; j++){
      if(matrix[i][j] == -1){
	return 1;
      }
    }
  }
  return 0;
}

//sectionNumber represents what row/col/subgrid we are analyzing
/* 0  1  2  3    0 1 2 3  4 5 6 7  8 9 10 11  12 13 14 15
   4  5  6  7    0 1 2 3  4 5 6 7  8 9 10 11  12 13 14 15
   8  9  10 11   0 1 2 3  4 5 6 7  8 9 10 11  12 13 14 15
   12 13 14 15   0 1 2 3  4 5 6 7  8 9 10 11  12 13 14 15
                 0 1 2 3  4 5 6 7  8 9 10 11  12 13 14 15
                 0 1 2 3  4 5 6 7  8 9 10 11  12 13 14 15
*/
int* determineIndex(int* section, int type, int sectionNumber, int* temp){
  if(type == 0){
    for(int i = 0; i < 16; i++){
      if(section[i] == -1){
	temp[0] = sectionNumber;
	temp[1] = i;
	return temp;
      }
    }

  }else if(type == 1){
    for(int i = 0; i < 16; i++){
      if(section[i] == -1){
	temp[0] = i;
	temp[1] = sectionNumber;
	return temp;
      }
    }

  }else{
    for(int i = 0; i < 16; i++){
      if(section[i] == -1){
	int subRow = i % 4;
	int subCol = i - (i / 4) * 4;
	int row = subRow * (sectionNumber % 4);
	int col = subCol * (sectionNumber - (sectionNumber / 4) * 4);
	temp[0] = row;
	temp[1] = col;
	return temp;
      }
    }
  }
  return temp;
	
}

			   

int determineValue(int* section){
  int solutions[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  for(int j = 0; j < 16; j++){
    if(section[j] != -1){
      solutions[section[j]] = 1;
    }
  }
  for(int j = 0; j < 16; j++){
    if(solutions[j] == 0){
      return j;
    }
  }
  return -1;
}

int definiteSolvable(int* section){
  int openSpaces = 0;
  for(int i = 0; i < 16; i++){
    if(section[i] == -1){
      openSpaces++;
    }
  }
  return openSpaces;
}

char** convertBackToHex(int** matrix){
  char** result;
  
  result = malloc(16 * sizeof(char*));
  
  for(int i = 0; i < 16; i++){
    result[i] = malloc(16 * sizeof(char));
  }

  for(int i = 0; i < 16; i++){
    for(int j = 0; j < 16; j++){

      
      if(matrix[i][j] >= 0 && matrix[i][j]<= 9){
	result[i][j] = (char)matrix[i][j] + 48;
      }else{
	result[i][j] = (char)matrix[i][j] + 55;
      }
    }
  }

  return result;
}


/*
  char** result = convertBackToHex(matrix);
  for(int i = 0; i < 16; i++){
    for(int j = 0; j < 16; j++){
      printf("%c\t", result[i][j]);
    }
    printf("\n");
  }
*/
