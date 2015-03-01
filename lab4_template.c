/*
  CPSC 223C
  Spring 2015
  CSU Fullerton

  Lab 4: variable arguments

  Authors: Kevin Wortman (kwortman@csu.fullerton.edu) (REPLACE THIS
  WITH YOUR NAMES AND CSUF EMAIL ADDRESSES)

*/ 

#include <assert.h>
#include <stdio.h> 
#include <stdlib.h>
#include <stdarg.h>



/* sorts array in to an ordered list of numbers */
void sort(int *arr, int num){
	int temp;
   for (int i = 0; i < num; i++)
    {
        for (int j = 0; j < (num - i - 1); j++)
        {
            if (arr[j] > arr[j + 1])
            {
                temp = *(arr+j);
                *(arr+j) = *(arr+j + 1);
                *(arr+j + 1) = temp;
            }
        }
    }
}


/* num is the number of variable arguments, all of type int. Compute
   and return the median of the variable arguments. Recall that in the
   case of an even number of arguments, you need to take the mean of
   the two arguments closest to the middle, which is why the return
   type is double. */
double median(int num, ...);

/* num is the number of variable arguments, all of type int. Compute
   and return the mode of the variable arguments. Recall that the mode
   is the most frequently-ocurring value. If there are multiple values
   tied for the same number of occurences, return the lesser of the
   tied values.
 */
int mode(int num, ...);

double median(int num, ...) {
  /* This function definition is obviously incorrect and needs to be
     replaced. */

  float median = 0;
  va_list list;
  va_start(list, num);
  
  int *arr;
  arr  = calloc(num, sizeof(int) );

  
  for(int j=0; j<num; j++){
    *(arr + j) = va_arg(list, int);
  }

   va_end(list);

   sort(arr,num);

   float total=0.0;
   for(int i = 0; i <=num; i++ ){
     total += *(arr+i);
   }
  

    if(num  == 1) {
      //printf("test1\n");
      median =  *(arr);

    }
    else if(num == 2){
      //printf("test2\n");

      median = total/2;
      
    }
    else if(num%2 == 0) {
      // printf("test3\n");
      int x  =  *(arr+(num/2));
     
      int y = *(arr+(num/2)-1);
    
      float diff = (x-y);
      if(diff == 1){
	median = y +0.5;
      }
      else if(diff == 2){
	median = y +1;
      }
      else{
	median = y +(diff/2);
      }
    }
    else{
      //      printf("test4\n");
       median = *(arr+(num/2));

    }

    
   free(arr);
  
  return median;
}

int mode(int num, ...) {
  /* This function definition is obviously incorrect and needs to be
     replaced. */

  va_list list;
  va_start(list, num);
  
  int *arr;
  arr  = calloc(num, sizeof(int) );

  for(int j=0; j<num; j++){
    *(arr + j) = va_arg(list, int);
  }
  va_end(list);
  

  sort(arr,num);

  int count1 = 1;
  int count2 = 1;
  int tempCount = 0;
  int mode =  *(arr+0) ;
  int tempMode = *(arr+0);
  
  for(int i = 0; i < num; i++){
    if(*(arr+i) != tempMode){
      if(count1 < tempCount){
	mode = tempMode;
	count1 = tempCount;
      }
      if(count1 == tempCount){
	count2++;
      }
      	tempMode = *(arr+i);
	tempCount = 0;
    }
    tempCount++;

  }
  
  if(count1 < tempCount){
    mode = tempMode;
    count1 = tempCount;
  }

  //printf("%d test\n",count2);
  if((num/count2) == 2){
    mode = 0;
  }

  free(arr);
  
  return mode;
}

int main() {

  /* MEDIAN */

  /* one argument */
  assert(median(1, 1) == 1);

  /* special case: even number of arguments */
  assert(median(2, 1, 2) == 1.5);

  /* straightforward three-argument cases */
  assert(median(3, 1, 2, 3) == 2);
  assert(median(3, 3, 2, 1) == 2);
  assert(median(3, 3, 3, 3) == 3);

  /* straightforward four-argument cases */
  assert(median(6, 9, -10, -1, 8, 3, 5) == 4);
  assert(median(7, 5, 6, 4, 1, 2, 3, 7) == 4);

  /* TODO: you should add at least two more test cases for your
     median() function here. */
  assert(median(10, 5, -3, -10, 1, 9, 3, 11, 2, 4, 10) == 3.5); /* special case : large numbe of arguments and even number of arguments */
  assert(median(5, -3, -24, 1, 9, 3, 11) == 1); /* straight forward five-argument cases */

  /* MODE */

  /* straightforward cases */
  assert(mode(1, 1) == 1);
  assert(mode(3, 2, 1, 1) == 1);
  assert(mode(7, 1, 1, 1, 2, 2, 2, 2) == 2);

  /* special case: tie */
  assert(mode(6, 3, 3, 3, 2, 2, 2) == 2);
  assert(mode(6, 2, 3, 2, 3, 2, 3) == 2);

  /* TODO: you should add at least two more test cases for your mode()
     function here. */
  assert(mode(10, 3, 5, 5, 2, 7, 7, 8, 8, 10, 10) == 5); /* special case: three way tie */
  assert(mode(6, 1, 1, 2, 2, 3, 3) == 0); /* no mode */
  
  printf("Everything Checks Out!\n");

  return 0;
}
