#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSIZE 128

//this assignment is given by Koç University

typedef struct character{
    char side[10];
    char race[15];
    char hp[3];
    char dmg[3];
}character;

typedef struct alliance{
    char side[10];
    char race[15];
    char hp[3];
    char dmg[3]; 
    int xp;
    int posx;
    int posy;
}alliance;

typedef struct horde{
    char side[10];
    char race[15];
    char hp[3];
    char dmg[3]; 
    int posx;
    int posy;
}horde;

char** load_map(int n_rows, int n_columns);

void put_single_character(char* query, char** map,int a, int b,int c);

void show_map(char** map, int a);

void show_faction(char* type, int a, int b);

void move_single_character(char* query, char** map, int a , int b, int c);

void attack(char* type, struct character* characters, char**map);

char** read_lines(int*, char*);

//global variables
character *chr;
alliance *alnc;
horde *hrd;
int rowcount;
char *type1="ALLIANCE";
char *type2="HORDE";



int main(int argc, char** argv){
        int i = 0;
        int num_lines = 0;
        char** lines = read_lines(&num_lines, argv[1]); // to read chars.txt
       	int z=0;
        int comnumline=0;
        char** comlines = read_lines(&comnumline, argv[2]);
        //printf("%s\n",comlines[0]);
	chr= malloc(sizeof(character)*num_lines*2);
        alnc= malloc(sizeof(alliance)*num_lines);
        hrd= malloc(sizeof(horde)*num_lines);
        while(i <= num_lines){
                //printf("%s\n", lines[i]);   // tokenize and operate
                char* token =strtok(lines[i],",");
                strcpy(chr[i].side, token);
                token= strtok(NULL, ",");
                strcpy(chr[i].race, token);
                token= strtok(NULL, ",");
                strcpy(chr[i].hp, token);
                token= strtok(NULL, ",");
                strcpy(chr[i].dmg, token);
                i++;
        }
        i=0;
        int numalnc=0;
        int numhrd=0;
        while(i<=num_lines){
            if(strcmp(chr[i].side,"ALLIANCE")==0){
                strcpy(alnc[numalnc].side,chr[i].side);
                strcpy(alnc[numalnc].race,chr[i].race);
                strcpy(alnc[numalnc].hp,chr[i].hp);
                strcpy(alnc[numalnc].dmg,chr[i].dmg);
                alnc[numalnc].xp=0;
                numalnc++;
            }else{
                strcpy(hrd[numhrd].side,chr[i].side);
                strcpy(hrd[numhrd].race,chr[i].race);
                strcpy(hrd[numhrd].hp,chr[i].hp);
                strcpy(hrd[numhrd].dmg,chr[i].dmg);
                numhrd++;
            }
        i++;
        }
	
	numhrd--;
        //printf("%s\n",alnc[3].race);//get the char of input
        //printf("%s\n",hrd[5].race);
        //printf("%s\n", chr[9].race); 
        char **map;
	char ** numchar;
	int k=0;
        int mapa=0;
        int mapb=0;
        //some test
        //map[2][2]='X';// asiigning values
      //  show_map(map,rowcount);
       // show_faction(type1,numalnc,numhrd);
        //show_faction(type2,numalnc,numhrd);
        //put_single_character(type2,map,2,2,3);
        //show_map(map,rowcount);
	//move_single_character(type2,map,2,3,3);
	//printf("\n");
	//show_map(map,rowcount);
        while(k<=comnumline){
            if(strstr(comlines[k],"LOADMAP")){
            char* comtoken =strtok(comlines[k],",");
            comtoken =strtok(NULL,",");
            mapa= atoi(comtoken);
            comtoken =strtok(NULL,","); 
            mapb= atoi(comtoken);
            map=load_map(mapa,mapb);
        }if(strstr(comlines[k],"SHOW,MAP")){
            show_map(map,rowcount);
            printf("\n");
        }if(strstr(comlines[k],"SHOW,ALLIANCE")){
            show_faction(type1,numalnc,numhrd);
        }if(strstr(comlines[k],"SHOW,HORDE")){
            show_faction(type2,numalnc,numhrd);
        }if(strstr(comlines[k],"ATTACK,HORDE")){
            printf("HORDES are ATTACKING\n");
        }if(strstr(comlines[k],"ATTACK,ALLIANCE")){
            printf("ALLIANCES are ATTACKING\n");
        }if(strstr(comlines[k],"MOVE,ALLIANCE")){
		printf("ALLIANCES MOVED\n");
            char* puttoken =strtok(comlines[k],",");
            puttoken =strtok(NULL,",");
            puttoken = strtok(NULL,",");
            int putc=0;
            int putcount=0;
            while(putc<(numalnc*2) && puttoken!=NULL){
               puttoken = strtok(NULL,",");
               int a = atoi(puttoken);
               puttoken = strtok(NULL,",");
               int b = atoi(puttoken);
               puttoken = strtok(NULL,",");
	       if(a<mapa && b<mapb){
                   move_single_character(type1,map,a,b,putcount);
                   putcount++;
	       }
               putc+=2; 
          
            }  
        }if(strstr(comlines[k],"MOVE,HORDE")){
		printf("HORDES MOVED\n");	
            char* puttoken =strtok(comlines[k],",");
            puttoken =strtok(NULL,",");
            puttoken = strtok(NULL,",");
            int putc=0;
            int putcount=0;
            while(putc<(numhrd*2) && puttoken!=NULL){
               puttoken = strtok(NULL,",");
               int a = atoi(puttoken);
               puttoken = strtok(NULL,",");
               int b = atoi(puttoken);
               puttoken = strtok(NULL,",");
               if(a<mapa && b<mapb){
                   move_single_character(type2,map,a,b,putcount);
                   putcount++;
               }
               putc+=2;
            } 
        }if(strstr(comlines[k],"PUT,HORDE")){
           char* puttoken =strtok(comlines[k],",");
            puttoken =strtok(NULL,",");
            puttoken = strtok(NULL,",");
            int putc=0;
            int putcount=0;
            while(putc<(numhrd*2) && puttoken!=NULL){
               puttoken = strtok(NULL,",");
               int a = atoi(puttoken);
               puttoken = strtok(NULL,",");
               int b = atoi(puttoken);
               puttoken = strtok(NULL,","); 
               put_single_character(type2,map,a,b,putcount);
               putcount++;
               putc+=2;  
            }
        }if(strstr(comlines[k],"PUT,ALLIANCE")){
            char* puttoken =strtok(comlines[k],",");
            puttoken =strtok(NULL,",");
            puttoken = strtok(NULL,",");
            int putc=0;
            int putcount=0;
            while(putc<(numalnc*2) && puttoken!=NULL){
               puttoken = strtok(NULL,",");
               int a = atoi(puttoken);
               puttoken = strtok(NULL,",");
               int b = atoi(puttoken);
               puttoken = strtok(NULL,",");
               put_single_character(type1,map,a,b,putcount);
               putcount++;
               putc+=2;
            }  
        }
        int endcheck=0;
        k++;
        int endcount;
        for(endcount=0; endcount<=numalnc; endcount++){
            int aend=0;
            if(strcmp(alnc[endcount].hp,"0")==0){
                aend++;
                if(aend==numalnc){
                    endcheck=1;
                    printf("HORDES WON");
                }
            }
        }
         for(endcount=0; endcount<=numhrd; endcount++){
            int hend=0;
            if(strcmp(hrd[endcount].hp,"0")==0){
                hend++;
                if(hend==numhrd){
                    endcheck=1;
                    printf("ALLIANCES WON");
                }
            }
        }
        if(endcheck==1){
            k=comnumline;
        }
        }
	//free(map);
        //free(chr);
        //free(alnc);
        //free(hrd);

     return 0;

}


char** load_map(int n_rows, int n_columns){

    char** gamemap;
    	rowcount=n_rows;
        gamemap = malloc(sizeof(char*)*n_rows);
        int i;
        for(i=0; i<n_columns; i++){
            gamemap[i]= malloc(sizeof(char)*n_columns);
        }
        int k;
        int j;
        for (k=0; k<n_rows; k++){
            for(j=0; j<n_columns; j++){
               gamemap[k][j]='.';
            }
        }
    
    return gamemap;

}

void put_single_character(char* query, char** map, int a, int b,int c){

        if(strcmp(query, type1)==0){
            map[a][b]=alnc[c].race[0];
            alnc[c].posx=a;
            alnc[c].posy=b;
        }else{
            map[a][b]=hrd[c].race[0];
            hrd[c].posx=a;
            hrd[c].posy=b;
        }

}

void show_map(char** map, int a) {

    int i=0;

    while(i<a){
        printf("%s\n",map[i]);
        i++;
    } 


}

void show_faction(char* type, int a , int b) {
  
    int i=0;
    if(strcmp(type, "ALLIANCE")==0){
        printf("ALLIANCE STATUS\n");
        while(i<a){
            printf("%s",alnc[i].race);
            printf(" HP: %s",alnc[i].hp);
            printf(" DMG: %s",alnc[i].dmg);
            printf(" XP: %d\n",alnc[i].xp);  
            i++;
        }
    }else{
        printf("HORDE STATUS\n");
            while(i<b){
            printf("%s",hrd[i].race);
            printf(" HP: %s",hrd[i].hp);
            printf(" DMG: %s\n",hrd[i].dmg);
            i++;
        }
    }

}


void move_single_character(char* query, char** map, int a , int b, int c){

        if(strcmp(query, type1)==0){
            map[alnc[c].posx][alnc[c].posy]='.';
            map[a][b]=alnc[c].race[0];
            alnc[c].posx=a;
            alnc[c].posy=b;
        }else{
            map[hrd[c].posx][hrd[c].posy]='.';
            map[a][b]=hrd[c].race[0];
            hrd[c].posx=a;
            hrd[c].posy=b;
        }
}

void attack(char* type, struct character* characters, char**map){
      //to do
}

char** read_lines(int* line_count, char* filename){

    char **arr_lines;
    char buf_file[BUFSIZE], buf_line[BUFSIZE];
    int num_lines = 0;

    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error opening file: %s.\n", filename);
        exit(-1);
    }

    while (fgets(buf_file, BUFSIZE, fp))
        if (!(strlen(buf_file) == BUFSIZE-1 && buf_file[BUFSIZE-2] != '\n'))
            num_lines++;

    arr_lines = (char**)malloc(num_lines * sizeof(char*));

    rewind(fp);
    num_lines = 0;
    while (!feof(fp)) {
        fscanf(fp, "%s", buf_line);
        arr_lines[num_lines] = (char*)malloc(BUFSIZE * sizeof(char));
        strcpy(arr_lines[num_lines], buf_line);
        num_lines++;
    }
    *line_count = num_lines-1;
    fclose(fp);
    return arr_lines;
}