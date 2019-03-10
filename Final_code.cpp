#include<stdio.h>
#include<stdlib.h>
#include<math.h>

//Wall - '#'  Player - '@'  Troll - '*'

int X[3],Y[3],x,y;    // Trolls is X and Y, Player is x and y
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
{"# X #####################################################################"} };  

void troll(){
    int i,j,k=0;
    while(k<3){
	    i=X[k];
	    j=Y[k];
	    if(maze[Y[k]-1][X[k]]=='@')    Y[k]=Y[k]-1;
	    else if(maze[Y[k]+1][X[k]]=='@')    Y[k]=Y[k]+1;
	    else if(maze[Y[k]][X[k]+1]=='@')    X[k]=X[k]+1;
	    else if(maze[Y[k]][X[k]-1]=='@')    X[k]=X[k]-1;
	    else{
				int p=1,q=1,m,n;
				if(X[k]>x)   p=-1;
				if(Y[k]>y)   q=-1;
        if(abs(X[k]-x)<abs(Y[k]-y)){
				   if(maze[Y[k]][X[k]+p]==' ')  X[k]=X[k]+p;
					 else if(maze[Y[k]+q][X[k]]==' ')  Y[k]=Y[k]+q;
					 else if(maze[Y[k]][X[k]-p]==' ')  X[k]=X[k]-p;
					 else Y[k]=Y[k]-q;
				}
				else {
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
void setup(){                 
    int i,j,k=0,flag=0;
    glFlush();
    while(flag==0){                                //Setting the position of the player
	   y=rand()%23;
	   x=rand()%73;
	   if(maze[y][x]==' ') {  maze[y][x]='@';   flag=1;   }
    }
    while(k<3){                                     // Setting the position of the trolls
	flag=0;
	while(flag==0){                          
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

void game_loop(){                                    
    char ch;
    int i,j,flag=0,posx=x,posy=y;
    while(maze[y][x]!='X'&&(flag!=2)){           
      flag=0;                 //flag=0 : continue the game   flag=1 : Player wins   flag=2 : Player loses            
/*while(flag==0){             
	      ch=getch();                                 
	      posx=x;
	      posy=y;                                        
	      if(ch=='a'){   posx--;}        //Approximate part to be put in to glutSpecialFunc()
	      else if(ch=='w'){   posy--;  }
	      else if(ch=='d'){   posx++;  }
	      else if(ch=='s'){   posy++;  }       
	      else continue;     */
	      if(posx>=0 && posx<73 && posy>=0 && posy<23){ 
		      if(maze[posy][posx]==' '){
			      maze[y][x]=' ';  y=posy;   x=posx;
			      flag=1;   maze[y][x]='@';  }
		      else if(maze[posy][posx]=='X')  { flag=1;  maze[y][x]=' '; x=posx;  y=posy; }  
	      else flag=2;
		  if(flag!=2){
		         troll();             //Check if the troll has eaten the player 
		         if((x==X[0] &&y==Y[0])||(x==X[1] &&y==Y[1])||(x==X[2] &&y==Y[2]))   flag=2;
	      }
	  }
		}
      glFlush();                            //Clear the screen and display the updated maze
      for(i=0;i<23;i++){
	    for(j=0;j<73;j++){
	       printf("%c",maze[i][j]);
	    }
	    printf("\n");
      }
    }
    glFlush();                              //Clear the screen 
                                           //Display the message if the player lost or won
    if(flag==2)   printf("YOU LOSE");
    else  printf("YOU WIN");
}
int main(){
   glFlush();
   setup();
   game_loop();
   return 0;
}
