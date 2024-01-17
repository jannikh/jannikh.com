#include <cstdlib>
#include <iostream>
#include <conio.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Math.h>

#include <string.h>
#include <Windows.h>

#define MAXIMUM_X 1000
#define MAXIMUM_Y 1000
#define MAXIMUM_Z 1000

#define BASIC_COLOR FOREGROUND_INTENSITY|BACKGROUND_INTENSITY|BACKGROUND_BLUE|BACKGROUND_GREEN|BACKGROUND_RED
HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);

using namespace std;

char w [MAXIMUM_X][MAXIMUM_Y][MAXIMUM_Z];
char ans;
char viewdir;
char viewang;
int posx;
int posy;
int posz;
int height;
int width;
bool enter;
bool enter2;
int mark;
int steps=10;
char s[47][189][2];

int diff (int wert_a, int wert_b) {
    if (wert_a-wert_b<0)
        return wert_b-wert_a;
    else
        return wert_a-wert_b;
}

void cr_dot(int xx, int yy, int zz, char chr) {
    w[xx][yy][zz]=chr;
}

void cr_cube(int minx, int maxx, int miny, int maxy, int minz, int maxz, char chr) {
    int i;
    int j;
    int k;
    for (i=minx; i<=maxx; i++) {
        for (j=miny; j<=maxy; j++) {
            for (k=minz; k<=maxz; k++) {
                w[i][j][k]=chr;
            }
        }
    }
}

void cr_tower (int posx, int posy, int height) {
    int i;
    for (i=0; i<=height; i++) {
        if (i>499)
            w[posx][posy][i]=219;
        else if (i>249)
            w[posx][posy][i]=178;
        else if (i<127)
            w[posx][posy][i]=177;
        else
            w[posx][posy][i]=176;
    }
}

/*void cr_world (float dif, int start_h) {
    int i;
    int j;
    int k;
    int h;
    for (i=0; i<MAXIMUM_X; i++) {
        for (j=0; j<MAXIMUM_Y; j++) {
            if (i==0 && j==0)
                srand (time(NULL));
                h=start_h+-10+rand()%20;
            cr_tower(i, j, h);
        }
    }
}*/

int distance (int posx, int posy, int posz) {
    int i;
    if (viewang==4) {
        for (i=posz; i>0; i--) {
            if (w[posx][posy][i]!=' ')
                return posz-i;
        }
    } if (viewang==0) {
        for (i=posz; i<MAXIMUM_Z; i++) {
            if (w[posx][posy][i]!=' ')
                return i-posz;
        }
    } if (viewdir==0) {
        for (i=posy; i<MAXIMUM_Y; i++) {
            if (w[posx][i][posz]!=' ')
                return i-posy;
        }
    } if (viewang==4) {
        for (i=posy; i>0; i--) {
            if (w[posx][i][posz]!=' ')
                return posy-i;
        }
    } if (viewang==2) {
        for (i=posx; i<MAXIMUM_X; i++) {
            if (w[i][posy][posz]!=' ')
                return i-posx;
        }
    } if (viewang==6) {
        for (i=posx; i>0; i--) {
            if (w[i][posy][posz]!=' ')
                return posx-i;
        }
    }
}

void give (int posx, int posy, int posz, int a, int b, char ccc, int color) {
    char cx;
    SetConsoleTextAttribute(hcon, color);
    if (mark==0 || distance(posx, posy, posz)<=height/10)
        cx=ccc;
    else {
        int ww;
        int hh;
        ww=width*(atan(0.5/distance(posx, posy, posz)-0.5)/(3.14159265358979323846/4))+0.5;
        hh=height*(atan(0.5/distance(posx, posy, posz)-0.5)/(3.14159265358979323846/4))+0.5;
        if (a==width-ww) {
            if (b==height-hh) {
                if (mark==1)
                    cx=218;
                else
                    cx=201;
            } else if (b==height+hh) {
                if (mark==1)
                    cx=192;
                else
                    cx=200;
            } else if (mark==1)
                cx=179;
        } else if (a==width+ww) {
            if (b==height-hh) {
                if (mark==1)
                    cx=191;
                else
                    cx=187;
            } else if (b==height+hh) {
                if (mark==1)
                    cx=217;
                else
                    cx=188;
            } else if (mark==1)
                cx=179;
        } else if (b==height-hh && mark==1)
            cx=196;
    }
    //s[a][b][0]=cx;
    //s[a][b][1]=color;
    printf("%c", cx);
    //printf("-%i.%i,%i:%i;", a, b, ccc, color);
    //SetConsoleTextAttribute(hcon, 15);
    //printf("%c", s[a][b][0]);
}

void print (int posx, int posy, int posz, int a, int b, char origin) {
    if (origin==' ')
        give(posx, posy, posz, a, b, 32, 0);
    else if (origin=='h')
        give(posx, posy, posz, a, b, 178, 116);
    else if (origin=='s')
        give(posx, posy, posz, a, b, 177, 120);
    else if (origin=='e')
        give(posx, posy, posz, a, b, 177, 100);
    else if (origin=='g')
        give(posx, posy, posz, a, b, 176, 162);
    else if (origin=='a')
        give(posx, posy, posz, a, b, 32, 0);
    else if (origin=='w')
        give(posx, posy, posz, a, b, 126, 155);
    else if (origin=='l')
        give(posx, posy, posz, a, b, 197, 206);
    else if (origin=='n')
        give(posx, posy, posz, a, b, 176, 251);
    else if (origin=='d')
        give(posx, posy, posz, a, b, 177, 230);
    else if (origin=='b')
        give(posx, posy, posz, a, b, 32, 128);
    else
        give(posx, posy, posz, a, b, origin, 15);
}

void givem (char ccc, int color) {
    SetConsoleTextAttribute(hcon, color);
    printf("%c%c%c%c%c%c%c%c%c%c", ccc, ccc, ccc, ccc, ccc, ccc, ccc, ccc, ccc, ccc);
    SetConsoleTextAttribute(hcon, 15);
}

void viewm (char origin) {
    if (origin==' ')
        givem(32, 0);
    else if (origin=='h')
        givem(178, 116);
    else if (origin=='s')
        givem(177, 120);
    else if (origin=='e')
        givem(177, 100);
    else if (origin=='g')
        givem(176, 162);
    else if (origin=='a')
        givem(32, 0);
    else if (origin=='w')
        givem(126, 155);
    else if (origin=='l')
        givem(197, 206);
    else if (origin=='n')
        givem(176, 251);
    else if (origin=='d')
        givem(177, 230);
    else if (origin=='b')
        givem(32, 128);
    else
        givem(origin, 15);
}

void viewhf (int posx, int posy, int posz, bool invert) {
    int a;
    int b;
    int c;
    int asc;
    int ascone;
    int asctwo;
    int asctre;
    for (a=1; a<=height; a++) {
        for (b=1; b<=width; b++) {
            for(c=0; c<=MAXIMUM_X; c++) {
                if (invert) {
                    ascone=posx-c;
                    asctwo=posy+c-((1+2*c)*(width-b)/width);
                    asctre=posz-c+((1+2*c)*(height-a)/height);
                } else {
                    ascone=posx+c;
                    asctwo=posy-c+((1+2*c)*(width-b)/width);
                    asctre=posz-c+((1+2*c)*(height-a)/height);
                    //printf("(%i,%i,%i)\n", ascone, asctwo, asctre);
                }
                if (ascone<0 || ascone>=MAXIMUM_X || asctwo<0 || asctwo>=MAXIMUM_Y || asctre<0 || asctre>=MAXIMUM_Z) {
                    //printf("(%i,%i,%i)", ascone, asctwo, asctre);
                    if (c==MAXIMUM_X) {
                        print(posx, posy, posz, a, b, ' ');
                        break;
                    } else
                        goto nexxtv90;
                }
                //printf("=%i", asctre);
                asc=w[ascone][asctwo][asctre];
                    //printf("___%3i,%3i,%3i  ", ascone, asctwo, asctre);
                if (asc!=0 && asc!=32) {
                    //printf("___%3i,%3i,%3i      ", ascone, asctwo, asctre);
                    print(posx, posy, posz, a, b, asc);
                    break;
                }
nexxtv90:;
            }
        }
        if (enter)
            printf("\n");
    }
}

void viewvf (int posx, int posy, int posz, bool invert) {
    int a, b, c, asc, ascone, asctwo, asctre;
    for (a=1; a<=height; a++) { for (b=1; b<=width; b++) { for(c=0; c<=MAXIMUM_X; c++) { if (invert) {
                    ascone=posx-c+((1+2*c)*(width-b)/width);
                    asctwo=posy-c;
                    asctre=posz-c+((1+2*c)*(height-a)/height);
                } else {
                    ascone=posx+c-((1+2*c)*(width-b)/width);
                    asctwo=posy+c;
                    asctre=posz-c+((1+2*c)*(height-a)/height);
                } if (ascone<0 || ascone>=MAXIMUM_X || asctwo<0 || asctwo>=MAXIMUM_Y || asctre<0 || asctre>=MAXIMUM_Z) {
                    if (c==MAXIMUM_X) { print(posx, posy, posz, a, b, ' '); break; } else goto nexxtv90; }
                asc=w[ascone][asctwo][asctre]; if (asc!=0 && asc!=32) { print(posx, posy, posz, a, b, asc); break; }
nexxtv90:; } } if (enter) printf("\n"); } }

void viewhu (int posx, int posy, int posz, bool invert) {
    int a, b, c, asc, ascone, asctwo, asctre;
    for (a=1; a<=height; a++) { for (b=1; b<=width; b++) { for(c=0; c<=MAXIMUM_X; c++) { if (invert) {
                    ascone=posx-c+((1+2*c)*(height-a)/height);
                    asctwo=posy+c-((1+2*c)*(width-b)/width);
                    asctre=posz+c;
                } else {
                    ascone=posx+c-((1+2*c)*(height-a)/height);
                    asctwo=posy-c+((1+2*c)*(width-b)/width);
                    asctre=posz+c;
                } if (ascone<0 || ascone>=MAXIMUM_X || asctwo<0 || asctwo>=MAXIMUM_Y || asctre<0 || asctre>=MAXIMUM_Z) {
                    if (c==MAXIMUM_X) { print(posx, posy, posz, a, b, ' '); break; } else goto nexxtv90; }
                asc=w[ascone][asctwo][asctre]; if (asc!=0 && asc!=32) { print(posx, posy, posz, a, b, asc); break; }
nexxtv90:; } } if (enter) printf("\n"); } }

void viewvu (int posx, int posy, int posz, bool invert) {
    int a, b, c, asc, ascone, asctwo, asctre;
    for (a=1; a<=height; a++) { for (b=1; b<=width; b++) { for(c=0; c<=MAXIMUM_X; c++) { if (invert) {
                    ascone=posx-c+((1+2*c)*(width-b)/width);
                    asctwo=posy-c+((1+2*c)*(height-a)/height);
                    asctre=posz+c;
                } else {
                    ascone=posx+c-((1+2*c)*(width-b)/width);
                    asctwo=posy+c-((1+2*c)*(height-a)/height);
                    asctre=posz+c;
                } if (ascone<0 || ascone>=MAXIMUM_X || asctwo<0 || asctwo>=MAXIMUM_Y || asctre<0 || asctre>=MAXIMUM_Z) {
                    if (c==MAXIMUM_X) { print(posx, posy, posz, a, b, ' '); break; } else goto nexxtv90; }
                asc=w[ascone][asctwo][asctre]; if (asc!=0 && asc!=32) { print(posx, posy, posz, a, b, asc); break; }
nexxtv90:; } } if (enter) printf("\n"); } }

void viewhd (int posx, int posy, int posz, bool invert) {
    int a, b, c, asc, ascone, asctwo, asctre;
    for (a=1; a<=height; a++) { for (b=1; b<=width; b++) { for(c=0; c<=MAXIMUM_X; c++) { if (invert) {
                    ascone=posx+c-((1+2*c)*(height-a)/height);
                    asctwo=posy+c-((1+2*c)*(width-b)/width);
                    asctre=posz-c;
                } else {
                    ascone=posx-c+((1+2*c)*(height-a)/height);
                    asctwo=posy-c+((1+2*c)*(width-b)/width);
                    asctre=posz-c;
                } if (ascone<0 || ascone>=MAXIMUM_X || asctwo<0 || asctwo>=MAXIMUM_Y || asctre<0 || asctre>=MAXIMUM_Z) {
                    if (c==MAXIMUM_X) { print(posx, posy, posz, a, b, ' '); break; } else goto nexxtv90; }
                asc=w[ascone][asctwo][asctre]; if (asc!=0 && asc!=32) { print(posx, posy, posz, a, b, asc); break; }
nexxtv90:; } } if (enter) printf("\n"); } }

void viewvd (int posx, int posy, int posz, bool invert) {
    int a, b, c, asc, ascone, asctwo, asctre;
    for (a=1; a<=height; a++) { for (b=1; b<=width; b++) { for(c=0; c<=MAXIMUM_X; c++) { if (invert) {
                    ascone=posx-c+((1+2*c)*(width-b)/width);
                    asctwo=posy+c-((1+2*c)*(height-a)/height);
                    asctre=posz-c;
                } else {
                    ascone=posx+c-((1+2*c)*(width-b)/width);
                    asctwo=posy-c+((1+2*c)*(height-a)/height);
                    asctre=posz-c;
                } if (ascone<0 || ascone>=MAXIMUM_X || asctwo<0 || asctwo>=MAXIMUM_Y || asctre<0 || asctre>=MAXIMUM_Z) {
                    if (c==MAXIMUM_X) { print(posx, posy, posz, a, b, ' '); break; } else goto nexxtv90; }
                asc=w[ascone][asctwo][asctre]; if (asc!=0 && asc!=32) { print(posx, posy, posz, a, b, asc); break; }
nexxtv90:; } } if (enter) printf("\n"); } }

void view90 (int posx, int posy, int posz) {
         if (viewang==2 && viewdir==2) viewhf (posx, posy, posz, false);
    else if (viewang==2 && viewdir==6) viewhf (posx, posy, posz, true);
    else if (viewang==2 && viewdir==0) viewvf (posx, posy, posz, false);
    else if (viewang==2 && viewdir==4) viewvf (posx, posy, posz, true);
    
    else if (viewang==0 && viewdir==2) viewhu (posx, posy, posz, false);
    else if (viewang==0 && viewdir==6) viewhu (posx, posy, posz, true);
    else if (viewang==0 && viewdir==0) viewvu (posx, posy, posz, false);
    else if (viewang==0 && viewdir==4) viewvu (posx, posy, posz, true);
    
    else if (viewang==4 && viewdir==2) viewhd (posx, posy, posz, false);
    else if (viewang==4 && viewdir==6) viewhd (posx, posy, posz, true);
    else if (viewang==4 && viewdir==0) viewvd (posx, posy, posz, false);
    else if (viewang==4 && viewdir==4) viewvd (posx, posy, posz, true);
}

void move (char dir, int steps) {
    if (dir=='x') {
        //if (posx+steps>=0 && posx+steps<MAXIMUM_X)
            posx+=steps;
    } else if (dir=='y') {
        //if (posy+steps>=0 && posy+steps<MAXIMUM_Y)
            posy+=steps;
    } else {
        //if (posz+steps>=0 && posz+steps<MAXIMUM_Z)
            posz+=steps;
    }
}

void walk (char direction, int steps) {
    int dir;
    switch (direction) {
        case 'b':
            steps=0-steps;
        case 'f':
            if (viewang==0)
                move ('z', steps);
            else if (viewang==4)
                move ('z', -steps);
            else if (viewdir==0)
                move ('y', steps);
            else if (viewdir==2)
                move ('x', steps);
            else if (viewdir==4)
                move ('y', -steps);
            else if (viewdir==6)
                move ('x', -steps);
            break;
        case 'l':
            steps=0-steps;
        case 'r':
            if (viewdir==0)
                move ('x', steps);
            else if (viewdir==2)
                move ('y', -steps);
            else if (viewdir==4)
                move ('x', -steps);
            else if (viewdir==6)
                move ('y', steps);
            break;
        case 'u':
            steps=0-steps;
        case 'd':
            if (viewang==2)
                move ('z', -steps);
            else {
                if (viewang==4)
                    steps=0-steps;
                if (viewdir==0)
                    move ('y', steps);
                else if (viewdir==2)
                    move ('x', steps);
                else if (viewdir==4)
                    move ('y', -steps);
                else if (viewdir==6)
                    move ('x', -steps);
            }
    }
}

int min (int val1, int val2) {
    if (val1<val2)
        return val1;
    else
        return val2;
}

float max (float val1, float val2) {
    if (val1>val2)
        return val1;
    else
        return val2;
}

int he (int posx, int posy) {
    int i;
    for (i=MAXIMUM_Z-1; i>=0; i++) {
        if (w[posx][posy][i]!=' ')
            return i;
    }
}

void cr_random_world (int h_av, int bergsum, int h_meer) {
    int i;
    int j;
    int k;
    int bergs;
    int x;
    int y;
    int h;
    int rh;
    int rv;
    float e;
    int ph;
    system("CLS");
    printf("Neue Karte wird erstellt. Dies kann einen Moment dauern . . .");
//Schritt 1:
    for (i=0; i<MAXIMUM_X; i++) {
        for (j=0; j<=MAXIMUM_Y; j++){
            w [i][j][0]='b';
            for (k=1; k<=h_av; k++)
                w[i][j][k]='e';
            for (k=h_av; k<MAXIMUM_Z; k++)
                w[i][j][k]=' ';
        }
    }
    printf("\nSchritt 1/5: Kartenbereich wurde erzeugt.");
//Schritt 2:
    bergs=0;
schritt2:
    //system("CLS");
    //printf("Neue Karte wird erstellt. Dies kann einen Moment dauern . . ."
    //"\nSchritt 1/5: Kartenbereich wurde erzeugt."
    //"\nSchritt 2/5: Berge %i von %i erzeugt.", bergs, bergsum);
    srand (time(NULL));
    x=rand()%MAXIMUM_X;
    srand (time(NULL));
    y=rand()%MAXIMUM_Y;
    srand (time(NULL));
    h=rand()%(min(MAXIMUM_Z-he(x, y)-1, bergsum-bergs) - max(-he(x, y)+3, bergs-bergsum)) + max(-he(x, y)+3, bergs-bergsum);
    srand (time(NULL));
    rh=rand()%MAXIMUM_X/2;
    srand (time(NULL));
    rv=rand()%MAXIMUM_Y/2;
    for (i=max(0, x-rh); i<min(MAXIMUM_X, x+rh+1); i++) {
        for (j=max(0, y-rv); j<(MAXIMUM_Y, y+rv+1); j++) {
            e=sqrt(pow(i/rh, 2)+pow(j/rv, 2));
            if (e<=1) {
                ph=2*h*pow(e, 3)-3*h*e*e+h;
                for (k=he(x, y)-1; k<=he(x, y)+ph; k++) {
                    if (i>=0 && i<MAXIMUM_X && j>=0 && j<MAXIMUM_Y && k>=0 && k<MAXIMUM_Z)
                        w[i][j][k]='e';
                }
            }
        }
    }
    bergs+=fabs(h);
    printf("\nBerg wurde erzeugt: x: %i, y: %i, he: %i, h: %i, rh: %i, rv: %i", x, y, he(x, y), h, rh, rv);
    if (bergs<bergsum)
        goto schritt2;
    printf("\nSchritt 2/5: Landschaft wurde gestaltet.");
    getch();
    system("CLS");
}

float funct (float v1, float v2, float v3, float v5, int x, int y) {
    return max(pow(2*3.14159265358979323846, -1/2)*pow(2.71828182845904, -1/2*pow(v1*((x/100-5)*v5+v2), 2))+pow(2*3.14159265358979323846, -1/2)*pow(2.71828182845904, -1/2*pow(v1*((y/100-5)+v3), 2))-0.4, 0);
}

void cr_world (void) {
    int x, y;
    float z1;
    for (x=0; x<MAXIMUM_X; x++) {
        for (y=0; y<MAXIMUM_Y; y++) {
            w[x][y][0]='b';
            z1=100*(sin((x/100-5)+3.14159265358979323846/2)-
            pow((sin((x/100-5)+3.14159265358979323846/2)*
            sin((y/100-5)+3.14159265358979323846/2)), 3)/2+
            
            sin((y/100-5)+3.14159265358979323846/2)-
            pow((sin((x/100-5)+3.14159265358979323846/2)*
            sin((y/100-5)+3.14159265358979323846/2)), 3)/2+
            
            (y/100-5)/4+(x/100-5)/5+
            (50-pow(y/100-5, 2)-pow(x/100-5, 2))/25-
            
            funct(1, 0, 0, 3.5, x, y)+5*
            funct(1, -3, -3, 1, x, y)+5*
            funct(1, -3, 3, 1, x, y)+5*
            funct(0.5, -5, -5, 1, x, y)+5*
            funct(0.5, -5, 5, 1, x, y)+5*
            funct(0.8, 0, 0, 1, x, y)-2*
            funct(2, 0, 0, 1, x, y)+4);
            
            printf("%i | %i: %i\n", x, y, z1);
        }
    }
}

void showcolor (int color1, int color2) {
    SetConsoleTextAttribute(hcon,color1|color2);
    printf("Color %i / %i\n", color1, color2);
}

void showcolor2 (int color1) {
    SetConsoleTextAttribute(hcon,color1);
    printf(" %3i %c%c%c%c ", color1, 176, 177, 178, 219);
}

void consoletest (void) {
    int i;
    int j;
    for (i=0; i<256; i++) {
        showcolor2(i);
        if (i%16==15)
            printf("\n");
    }
}

void cr_input(void) {
    char inp[1000][100];
    char txt[100][100];
    int ii;
    int jj;
    int num[6];
    
    ii=0;
    char str[1000];
    FILE * file;
    file = fopen("structinput.txt" , "r");
    if (file) {
        while (fscanf(file, "%s", str)!=EOF) {
            strcpy(inp[ii], str);
            //printf("%i:::%s:::%s;;;\n", ii, str, inp[ii]);
            ii++;
        }
        fclose(file);
    }
    printf("\n\n");
    for (ii=0; ii<1000; ii++) {
        //printf("%s\n", ii, inp[ii]);
        for (jj=0; jj<100; jj++) {
            if (inp[ii][jj] == '@')
               inp[ii][jj]=' ';
            //else if (inp[ii][jj] == '{')
               //inp[ii][jj]='\b';
            //else if (inp[ii][jj] == '}')
               //inp[ii][jj]='\t';
        }
        if (inp[ii][0]=='q') {
            for (jj=0; jj<6; jj++) {
                str[0]=inp[ii][4*jj+2];
                str[1]=inp[ii][4*jj+3];
                str[2]=inp[ii][4*jj+4];
                str[3]='\0';
                num[jj] = atoi(str);
            }
            cr_cube(num[0], num[1], num[2], num[3], num[4], num[5], inp[ii][26]);
        }
        else if (inp[ii][0]=='s') {
            if (inp[ii][3]!='{')
                printf("\n");
            for (jj=3; jj<strlen(inp[ii])-1; jj++) {
                if (inp[ii][jj]=='{')
                    printf("\b");
                else if (inp[ii][jj]=='}')
                    printf("\t");
                else
                    printf("%c", inp[ii][jj]);
            }
        }
        else if (inp[ii][0]=='j') {
            str[0]=inp[ii][2];
            str[1]=inp[ii][3];
            str[2]=inp[ii][4];
            str[3]='\0';
            steps = atoi(str);
        }
        else if (inp[ii][0]=='p') {
            str[0]=inp[ii][2];
            str[1]=inp[ii][3];
            str[2]=inp[ii][4];
            str[3]='\0';
            posx = atoi(str);
            str[0]=inp[ii][6];
            str[1]=inp[ii][7];
            str[2]=inp[ii][8];
            str[3]='\0';
            posy = atoi(str);
            str[0]=inp[ii][10];
            str[1]=inp[ii][11];
            str[2]=inp[ii][12];
            str[3]='\0';
            posz = atoi(str);
        }
        if (!strcmp(inp[ii], "END"))
            break;
    }
    //system("PAUSE");
}

int main(int argc, char *argv[])
{
    printf("Activate Fullscreen? (Only available on Windows Vista or later) (Y/N)\n\t(M for manual activation in case automatic one does not work)");
start:
    ans=getch();
    if (ans=='n') {
        enter=false; enter2=false; width=80; height=23;
    } else if (ans=='j' || ans=='y') {
        system("CLS");
        printf("Window is being maximized automatically.\nPlease leave the window focused and wait a few seconds.\nIf problems occur, please restart the program and activate fullscreen manually.\n\n\n");
        system("start \"\" \"sendfullscreenkeys.exe\"");
        system("WMIC");
        enter=true; enter2=true; width=189; height=47;
    } else if (ans=='m') {
        system("CLS");
        printf("Please maximize the window and then enter \"exit\" (confirm with Enter).\n\n");
        system("WMIC");
        enter=true; enter2=true; width=189; height=47;
    } else
        goto start;
    //system("CLS");
    //consoletest();
    //getch();
    system("CLS");
    printf("Standard-World is loading. Please wait");
    goto skipp;
reloadmatrix:
    system("CLS");
    printf("The world is being reloaded now.\nStructures and variables are going to be overwritten.\nPlease wait");
    printf("");
skipp:
    /*srand (time(NULL));
    printf("%i%i", rand()%10000, rand()%10000);
    SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | 8 );
    printf("%i%i", rand()%10000, rand()%10000);
    SetConsoleTextAttribute (hcon,FOREGROUND_BLUE|BASIC_COLOR);
    printf("%i%i", rand()%10000, rand()%10000);
    SetConsoleTextAttribute (hcon,FOREGROUND_BLUE|FOREGROUND_GREEN|BASIC_COLOR);
    printf("%i%i", rand()%10000, rand()%10000);*/
    posx=500;
    posy=500;
    posz=100;
    viewdir=2;
    viewang=2;
    ////cr_cube (0, 999, 0, 999, 0, 332, ' ');
    printf(" .");
    ////cr_cube (0, 999, 0, 999, 333, 665, ' ');
    printf(" .");
    ////cr_cube (0, 999, 0, 999, 666, 999, ' ');
    printf(" .");
    
    mark=0;
    cr_input();
    //cr_world();
    /*cr_cube(900, 999, 900, 999, 0, 999, 'h');
    cr_cube(800, 899, 900, 999, 0, 999, 's');
    cr_cube(700, 799, 900, 999, 0, 999, 'e');
    cr_cube(600, 699, 900, 999, 0, 999, 'g');
    cr_cube(500, 599, 900, 999, 0, 999, 'a');
    cr_cube(400, 499, 900, 999, 0, 999, 'w');
    cr_cube(300, 399, 900, 999, 0, 999, 'l');
    cr_cube(200, 299, 900, 999, 0, 999, 'n');
    cr_cube(100, 199, 900, 999, 0, 999, 'd');
    cr_cube(0, 99, 900, 999, 0, 999, 'b');*/
/*
    cr_cube(0, 999, 0, 999, 0, 0, 'b');
    cr_cube(0, 999, 0, 999, 1, 98, 'e');
    cr_cube(0, 483, 0, 999, 99, 99, 'n');
    cr_cube(520, 530, 520, 530, 100, 110, 's');
    cr_cube(520, 530, 510, 519, 100, 110, 'h');
    cr_cube(485, 490, 0, 999, 95, 99, 'w');
    cr_cube(500, 510, 510, 520, 96, 96, 'l');
    cr_cube(492, 999, 0, 999, 99, 99, 'g');
    cr_cube(484, 484, 0, 999, 99, 99, 'd');
    cr_cube(491, 491, 0, 999, 99, 99, 'd');
    cr_cube(500, 510, 510, 520, 97, 99, ' ');
*/
agn:
    system("CLS");
    view90(posx, posy, posz);
    SetConsoleTextAttribute(hcon, 15);
    printf("Coordinates: %i (x), %i (y), %i (z) | %i (Direction), %i (Angle)%sCompass: ", posx, posy, posz, viewdir/2, viewang/2, (!enter2) ? "\n" : " | ");
    SetConsoleTextAttribute(hcon, 139);
    if (viewdir==0)
        printf("W ");
    else if (viewdir==2)
        printf("N ");
    else if (viewdir==4)
        printf("E ");
    else
        printf("S ");
    SetConsoleTextAttribute(hcon, 121);
    if (viewdir==0)
        printf("  N  ");
    else if (viewdir==2)
        printf("  E  ");
    else if (viewdir==4)
        printf("  S  ");
    else
        printf("  W  ");
    SetConsoleTextAttribute(hcon, 139);
    if (viewdir==0)
        printf(" E");
    else if (viewdir==2)
        printf(" S");
    else if (viewdir==4)
        printf(" W");
    else
        printf(" N");
    SetConsoleTextAttribute(hcon, 15);
    printf("   Esc: Menu");
    ans=getch();
    switch (ans) {
        case 'w':
            walk ('f', 1);
            break;
        case 'W':
            walk ('f', steps);
            break;
        case 'a':
            walk ('l', 1);
            break;
        case 'A':
            walk ('l', steps);
            break;
        case 's':
            walk ('b', 1);
            break;
        case 'S':
            walk ('b', steps);
            break;
        case 'd':
            walk ('r', 1);
            break;
        case 'D':
            walk ('r', steps);
            break;
        case 'q':
            walk ('u', 1);
            break;
        case 'Q':
            walk ('u', steps);
            break;
        case 'e':
            walk ('d', 1);
            break;
        case 'E':
            walk ('d', steps);
            break;
        case 'i':
            if (viewang>0)
                viewang-=2;
            break;
        case 'I':
            viewang=0;
            break;
        case 'k':
            if (viewang<4)
                viewang+=2;
            break;
        case 'K':
            viewang=4;
            break;
        case 'L':
        case 'l':
            viewdir+=2;
            if (viewdir>6)
                viewdir=0;
            break;
        case 'J':
        case 'j':
            viewdir-=2;
            if (viewdir<0)
                viewdir=6;
            break;
        case 27:
pausemenu:
            system("CLS");
            printf("\n\n\n\n\t\t\tP: Change position manually");                    
            printf("\n\n\t\t\tQ: Create rectangular prism");
            printf("\n\n\t\t\tS: Show controls");
            printf("\n\n\t\t\tJ: Change jumping length (now %i)", steps);
            if (enter2)
                printf("\n\n\t\t\tV: Deactivate Fullscreen mode\n\t\t\t   Shift+V: Deactivate Fullscreen but leave window big\n");
            else
                printf("\n\n\t\t\tV: Activate Fullscreen mode\n\t\t\t   Shift+V: Activate Fullscreen mode manually\n");
            printf("\n\n\t\t\tF: Continue program");
            printf("\n\n\t\t\tR: Edit structinput file and restart program");
            printf("\n\n\t\t\tE: Exit / Quit program\n");
            ans=getch();
            if (ans=='e')
                goto exit;
            else if (ans=='v') {
                if (enter2) {
                    system("start \"\" \"minwindow.exe\"");
                    enter2=false; width=80; height=23;
                    goto pausemenu;
                } else {
                    if (!enter) {
                        system("CLS");
                        printf("Window is being maximized automatically.\nPlease leave the window focused and wait a few seconds.\nIf problems occur, please restart the program and activate fullscreen manually.\n\n\n");
                        system("start \"\" \"sendfullscreenkeys.exe\"");
                        system("WMIC");
                    } else
                        system("start \"\" \"maxwindow.exe\"");
                    enter=true; enter2=true; width=189; height=47;
                    goto pausemenu;
                }
            } else if (ans=='V') {
                if (enter2) {
                    enter2=false; width=80; height=23;
                    goto pausemenu;
                } else {
                    system("CLS");
                    printf("Please maximize the window and then enter \"exit\" (confirm with Enter).\n\n");
                    system("WMIC");
                    enter=true; enter2=true; width=189; height=47;
                    goto pausemenu;
                }
            } else if (ans=='f' || ans==27)
                break;
            else if (ans=='r') {
                system("CLS");
                printf("\n\n\tWould you rather ...");
                if(sizeof(void*)==4)
                    printf("\n\n\t- Use the command-prompt to edit the structure input file [press 'C']");
                printf("\n\n\t- Use standard notepad to edit the file [press 'N']");
                printf("\n\n\t- Use your own editor to edit structinput.txt and restart manually ['M']");
                ans=getch();
                if (ans=='c') {
                    if(sizeof(void*)!=4)
                        system("notepad structinput.txt");
                    else
                        system("edit structinput.txt");
                    system("CLS");
                }
                else if (ans=='n'){
                    system("notepad structinput.txt");
                    system("CLS");
                } else if (ans=='m'){
                    system("CLS");
                    printf("\n\n\n\n\n\t\tGo ahead. Have fun. See you later :)\n\n\tPlease press any key when you are done with editing the input file\n\tand want to restart the matrix.");
                    getch();
                } else
                    goto pausemenu;
                goto reloadmatrix;
            } else if (ans=='s') {
                system("CLS");
                printf("\n       W:   Go 1 Step in direction you're looking in");
                printf("\n       A:   Go 1 Step to the left");
                printf("\n       S:   Go 1 Step opposite to the direction you're looking in");
                printf("\n       D:   Go 1 Step to the right");
                printf("\n\n Shift+W: Jump %i Steps in direction you're looking in (Jumping length)", steps);
                printf("\n Shift+A: Jump %i Steps to the left (Jumping length)", steps);
                printf("\n Shift+S: Jump %i Steps opposite to the direction you're looking in (Jumping length)", steps);
                printf("\n Shift+D: Jump %i Steps to the right (Jumping length)", steps);
                printf("\n\n       I: Change viewing angle by 90 degrees up");
                printf("\n       K: Change viewing angle by 90 degrees down");
                printf("\n       J: Change viewing angle by 90 degrees to the left");
                printf("\n       L: Change viewing angle by 90 degrees to the right");
                printf("\n\n Shift+I: look up");
                printf("\n Shift+K: look down");
                printf("\n\n N: y+; E: x+; S: y-; W: x-; oben: z+; unten: z-\n\n\n");
                system("PAUSE");
                goto pausemenu;
            } else if (ans=='j') {
                system("CLS");
                printf("\nChange jumping length:\n\nOld value: %i\nNew Value: ", steps);
                scanf("%i", &steps);
                goto pausemenu;
            } else if (ans=='p') {
                system("CLS");
                printf("\nChange Position:\n\nOld values: %i (x); %i (y); %i (z)\n\nNew values:\nx: ", posx, posy, posz);
                scanf("%i", &posx);
                printf("y: ");
                scanf("%i", &posy);
                printf("z: ");
                scanf("%i", &posz);
                goto pausemenu;
            } else if (ans=='q') {
                system("CLS");
/*
                printf("Show standard map for better orientation? (Y/N)");
                ans=getch();
                system("CLS");
                if (ans=='j' || ans=='y') {
                    printf("minx|maxx|miny|maxy|minz|maxz|Material\n"
                        "  0, 999,   0, 999,   0,   0, solid\n"
                        "  0, 999,   0, 999,   1,  98, Earth\n"
                        "  0, 483,   0, 999,  99,  99, Snow\n"
                        "520, 530, 520, 530, 100, 110, Stone\n"
                        "520, 530, 510, 519, 100, 110, Wood\n"
                        "485, 490,   0, 999,  95,  99, Water\n"
                        "500, 510, 510, 520,  96,  96, Lava\n"
                        "492, 999,   0, 999,  99,  99, Grass\n"
                        "484, 484,   0, 999,  99,  99, Sand\n"
                        "491, 491,   0, 999,  99,  99, Sand\n"
                        "500, 510, 510, 520,  97,  99, ' '\n\n\n");
                }
*/
                printf("Create new rectangle prism (Input values between 0 and 999 (including 0 and 999) only!):\n\n");
                printf("Minimum-x: ");
                int m1, m2, m3, m4, m5, m6;
                char mx;
                scanf("%i", &m1);
                printf("Maximum-x: ");
                scanf("%i", &m2);
                printf("Mindest-y: ");
                scanf("%i", &m3);
                printf("Maximum-y: ");
                scanf("%i", &m4);
                printf("Minimum-z: ");
                scanf("%i", &m5);
                printf("Maximum-z: ");
                scanf("%i", &m6);
                system("CLS");
                printf("Enter material:\nFor a predefined material please enter the corresponding value.\nWhen other character is inserted, it will be displayed as such.\n\n");
                printf("Values of materials:\n");
                viewm(' ');
                printf(" [ ] Air\n");
                viewm('h');
                printf(" [h] Wood\n");
                viewm('s');
                printf(" [s] Stone\n");
                viewm('e');
                printf(" [e] Earth\n");
                viewm('g');
                printf(" [g] Grass\n");
                viewm('w');
                printf(" [w] Water\n");
                viewm('l');
                printf(" [l] Lava\n");
                viewm('n');
                printf(" [n] Snow\n");
                viewm('d');
                printf(" [d] Sand\n");
                viewm('b');
                printf(" [b] Solid\n");
                printf("\nPlease press correlating key: ");
                mx=getch();
                system("CLS");
                printf("Prism gets created. This could last a moment...");
                cr_cube(m1, m2, m3, m4, m5, m6, mx);
                printf("\n\nCreating of rectangle prism finished.\n");
                system("PAUSE");
                goto pausemenu;
            } else
                goto pausemenu;
            break;
        
    }
    goto agn;
exit:
    return EXIT_SUCCESS;
}
