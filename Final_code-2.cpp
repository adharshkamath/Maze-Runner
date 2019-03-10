#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

int X[3],Y[3],x,y;    // Track the positions of 3 trolls and the player
char maze[24][74]={
{"#########################################################################"},
{"#   #               #               #           #                   #   #"},
{"#   #   #########   #   #####   #########   #####   #####   #####   #   #"},
{"#               #       #   #           #           #   #   #       #   #"},
{"#########   #   #########   #########   #####   #   #   #   #########   #"},
{"#       #   #               #           #   #   #   #   #           #   #"},
{"#   #   #############   #   #   #########   #####   #   #########   #   #"},
{"#   #               #   #   #       #           #           #       #   #"},
{"#   #############   #####   #####   #   #####   #########   #   #####   #"},
{"#           #       #   #       #   #       #           #   #           #"},
{"#   #####   #####   #   #####   #   #########   #   #   #   #############"},
{"#       #       #   #   #       #       #       #   #   #       #       #"},
{"#############   #   #   #   #########   #   #####   #   #####   #####   #"},
{"#           #   #           #       #   #       #   #       #           #"},
{"#   #####   #   #########   #####   #   #####   #####   #############   #"},
{"#   #       #           #           #       #   #   #               #   #"},
{"#   #   #########   #   #####   #########   #   #   #############   #   #"},
{"#   #           #   #   #   #   #           #               #   #       #"},
{"#   #########   #   #   #   #####   #########   #########   #   #########"},
{"#   #       #   #   #           #           #   #       #               #"},
{"#   #   #####   #####   #####   #########   #####   #   #########   #   #"},
{"#   #                   #           #               #               #   #"},
{"# X #####################################################################"} };   //Hardcoded maze

void troll(){
    int i,j,k=0;
    while(k<3){
	    i=X[k];
	    j=Y[k];
            //Check if the troll is next to the player
	    if(maze[Y[k]-1][X[k]]=='@')    Y[k]=Y[k]-1;
	    else if(maze[Y[k]+1][X[k]]=='@')    Y[k]=Y[k]+1;
	    else if(maze[Y[k]][X[k]+1]=='@')    X[k]=X[k]+1;
	    else if(maze[Y[k]][X[k]-1]=='@')    X[k]=X[k]-1;
	    else{
		int p=1,q=1,m,n;
                //Assign p and q values to in according to the position(left, top, bottom, right) of the troll w.r.t. player
		if(X[k]>x)   p=-1;
		if(Y[k]>y)   q=-1;
                //Check if the troll and the player are in same line
                if(X[k]==x){     if(maze[Y[k]+q][X[k]]==' ')  Y[k]=Y[k]+q; }   
                else if(Y[k]==y){     if(maze[Y[k]][X[k]+p]==' ')  X[k]=X[k]+p; } 
                //Check in which direction is the troll near to the player
                else if(abs(X[k]-x)<abs(Y[k]-y)){   
                       /* If the troll is near to the player in x-direction, first see if the troll could be moved to that position.
                       If no, then try in y-direction. If both does not satisify, then find for x and y direction in opposite side. 
                       */
			if(maze[Y[k]][X[k]+p]==' ')  X[k]=X[k]+p;   //Check for the most feasible move
			else if(maze[Y[k]+q][X[k]]==' ')  Y[k]=Y[k]+q;
			else if(maze[Y[k]][X[k]-p]==' ')  X[k]=X[k]-p;
			else Y[k]=Y[k]-q;
		}
		else {
                       /* If the troll is near to the player in y-direction, first see if the troll could be moved to that position.
                       If no, then try in x-direction. If both does not satisify, then find for x and y direction in opposite side. 
                       */
		    if(maze[Y[k]+q][X[k]]==' ') Y[k]=Y[k]+q; 
		    else if(maze[Y[k]][X[k]+p]==' ')  X[k]=X[k]+p;
		    else if(maze[Y[k]-q][X[k]]==' ')  Y[k]=Y[k]-q; 
		    else X[k]=X[k]-p;
		}
	  } 
	  maze[Y[k]][X[k]]='*';
	  maze[j][i]=' ';
	  k++;
    }
}
void setup(){                         //Function to set the position of the player and trolls for the first time
    int i,j,k=0,flag=0;
    system("clear");
    while(flag==0){                                  //Set the postion of the player in random
	   y=rand()%23;
	   x=rand()%73;
	   if(maze[y][x]==' ') {  maze[y][x]='@';   flag=1;   }
    }
    while(k<3){                                      //Now trolls turn :P
	flag=0;
	while(flag==0){                                  //Set the postion of the trolls in random
		Y[k]=rand()%23;
		X[k]=rand()%73;
		if(maze[Y[k]][X[k]]==' ') {  maze[Y[k]][X[k]]='*';   flag=1;   }
	}
	k++;
    }
    for(i=0;i<23;i++){                       //Display the maze after fixing the position of player and trolls
	  for(j=0;j<73;j++){
	    printf("%c",maze[i][j]);
	  }
	  printf("\n");
    }
}
void game_loop(){                                      //Function to start the real game :)
    char ch;
    int i,j,flag=0,posx=x,posy=y;
    while(maze[y][x]!='X'&&(flag!=2)){                 //To run the game till the player wins or loses
      flag=0;                                          //To check if the player has won or not
	                                                   // flag=1  WIN,   flag=2  LOSE, flag=0 CONTINUE the game
	  while(flag==0){
	      ch=getchar();                                  //Take the users response for the player's move
	      posx=x;
	      posy=y;
	      if(ch=='a'){   posx--;}
	      else if(ch=='w'){   posy--;  }
	      else if(ch=='d'){   posx++;  }
	      else if(ch=='s'){   posy++;  }
	      else continue;
	      if(posx>=0 && posx<73 && posy>=0 && posy<23){  //Check if the move was a valid one
		      if(maze[posy][posx]==' '){
			      maze[y][x]=' ';  y=posy;   x=posx;
			      flag=1;   maze[y][x]='@';  }
		      else if(maze[posy][posx]=='X')  { flag=1;  maze[y][x]=' '; x=posx;  y=posy; }
	      else flag=2;
		  if(flag!=2){
		         troll();
				                                //Check if the troll has eaten the player :P
		         if((x==X[0] &&y==Y[0])||(x==X[1] &&y==Y[1])||(x==X[2] &&y==Y[2]))   flag=2;
	      }
	  }
		}
      system("clear");                            //Clear the screen and display the updated maze
      for(i=0;i<23;i++){
	    for(j=0;j<73;j++){
	       printf("%c",maze[i][j]);
	    }
	    printf("\n");
      }
    }
    system("clear");                              //Clear the screen 
    //Display the message if the player lost or won
    if(flag==2)   printf("YOU LOSE\n");
    else  printf("YOU WIN\n");
}
int main(){
   char c;
   system("clear");
   srand(time(0));                         //Make random() function return new value each time it is called
   printf("\n\t\t\t\t\t\t       Are you ready for the MAZE RUN ???\n");
   printf("\n\t\t\t\t\t\t   Moves :  a-left   d-right   w-up   s-down\n");
   printf("\n\t\t\t\t\t\t           Press any key to start\t");
   c=getchar();
   system("clear");             
   setup();
   game_loop();
   c=getchar();
   return 0;
}
