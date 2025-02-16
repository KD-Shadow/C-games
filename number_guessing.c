#include<stdio.h>
#include<time.h>
#include<stdlib.h>

int main(){
 int random,guess,guessno=0;
 srand(time(NULL));
 printf("Welcome to the number guessing Game\n");
 random=rand()%100+1; //random number generation
do{
printf("Please Enter your Guess(1-100): ");
scanf("%d",&guess);
guessno++;
if(guess<random){
 printf("Guess Larger Number!\n");
}else if(guess>random){
 printf("Guess Smaller Number!!\n");
}else{
 printf("Congrats!! You Have successfully guessed the Number\nYou took %d guesses.\n",guessno);
}
}while(guess!=random);
printf("\nThanks for playing. Hope you enjoyed! -_-\n");
printf("\nMade by Kushal Dhungana\n");
return 0;
}
