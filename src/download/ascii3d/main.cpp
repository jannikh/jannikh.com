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
int air;
int aircol;

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
    printf("%c", cx);
}

void print (int posx, int posy, int posz, int a, int b, char origin) {
    if (origin==' ')
        give(posx, posy, posz, a, b, air, aircol);
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
        give(posx, posy, posz, a, b, 176, 247);
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
                }
                if (ascone<0 || ascone>=MAXIMUM_X || asctwo<0 || asctwo>=MAXIMUM_Y || asctre<0 || asctre>=MAXIMUM_Z) {
                    if (c==MAXIMUM_X) {
                        print(posx, posy, posz, a, b, ' ');
                        break;
                    } else
                        goto nexxtv90;
                }
                asc=w[ascone][asctwo][asctre];
                if (asc!=0 && asc!=32) {
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
    if (dir=='x')
        posx+=steps;
    else if (dir=='y')
        posy+=steps;
    else
        posz+=steps;
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
            ii++;
        }
        fclose(file);
    }
    printf("\n\n");
    for (ii=0; ii<1000; ii++) {
        for (jj=0; jj<100; jj++) {
            if (inp[ii][jj] == '@')
               inp[ii][jj]=' ';
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
        else if (inp[ii][0]=='a') {
            str[0]=inp[ii][2];
            str[1]=inp[ii][3];
            str[2]=inp[ii][4];
            str[3]='\0';
            air = atoi(str);
            str[0]=inp[ii][6];
            str[1]=inp[ii][7];
            str[2]=inp[ii][8];
            str[3]='\0';
            aircol = atoi(str);
        }
        else if (inp[ii][0]=='v') {
            str[0]=inp[ii][2];
            str[1]='\0';
            viewdir = atoi(str)*2;
            str[0]=inp[ii][4];
            str[1]='\0';
            viewang = atoi(str)*2;
        }
        if (!strcmp(inp[ii], "END"))
            break;
    }
}

int main(int argc, char *argv[])
{
    printf("Activate Fullscreen? (Only available on Windows Vista or later) (Y/N)\n\t(M for manual activation in case automatic one does not work)");
start:
    ans=getch();
    if (ans=='n') {
        enter=false; enter2=false; width=80; height=24;
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
    system("CLS");
    printf("Standard-World is loading. Please wait");
    posx=500;
    posy=500;
    posz=100;
    viewdir=2;
    viewang=2;
    air=32;
    aircol=0;
    goto skipp;
reloadmatrix:
    system("CLS");
    printf("The world is being reloaded now.\nStructures and variables are going to be overwritten.\nPlease wait");
    printf("");
skipp:
    ////cr_cube (0, 999, 0, 999, 0, 332, ' ');
    printf(" .");
    ////cr_cube (0, 999, 0, 999, 333, 665, ' ');
    printf(" .");
    ////cr_cube (0, 999, 0, 999, 666, 999, ' ');
    printf(" .");
    
    mark=0;
    cr_input();
agn:
    system("CLS");
    view90(posx, posy, posz);
    SetConsoleTextAttribute(hcon, 7);
    printf("Coordinates: ");
    if (viewang == 2 && viewdir == 6)
        SetConsoleTextAttribute(hcon, 2);
    else if (viewang == 2 && viewdir == 2)
        SetConsoleTextAttribute(hcon, 4);
    else
        SetConsoleTextAttribute(hcon, 7);
    printf("x");
    SetConsoleTextAttribute(hcon, 15);
    printf(" %i  ", posx);
    if (viewang == 2 && viewdir == 4)
        SetConsoleTextAttribute(hcon, 2);
    else if (viewang == 2 && viewdir == 0)
        SetConsoleTextAttribute(hcon, 4);
    else
        SetConsoleTextAttribute(hcon, 7);
    printf("y");
    SetConsoleTextAttribute(hcon, 15);
    printf(" %i  ", posy);
    if (viewang == 0)
        SetConsoleTextAttribute(hcon, 2);
    else if (viewang == 4)
        SetConsoleTextAttribute(hcon, 4);
    else
        SetConsoleTextAttribute(hcon, 7);
    printf("z");
    SetConsoleTextAttribute(hcon, 15);
    printf(" %i ", posz);
    SetConsoleTextAttribute(hcon, 8);
    printf(" Direction: ");
    SetConsoleTextAttribute(hcon, 7);
    printf("%i", viewdir/2);
    SetConsoleTextAttribute(hcon, 8);
    printf("  Angle: ");
    SetConsoleTextAttribute(hcon, 7);
    printf("%i", viewang/2);
    printf("  ");
    //printf(" %s", (!enter2) ? " " : " ");
    SetConsoleTextAttribute(hcon, 15);
    //printf("Compass: ");
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
                    enter2=false; width=80; height=24;
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
                    enter2=false; width=80; height=24;
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
                printf("\n\n Shift+W: Jump %i Steps (Jumping length) in direction you're looking in", steps);
                printf("\n Shift+A: Jump %i Steps (Jumping length) to the left", steps);
                printf("\n Shift+S: Jump %i Steps (Jumping length) opposite to dir. you're looking in", steps);
                printf("\n Shift+D: Jump %i Steps (Jumping length) to the right", steps);
                printf("\n\n       I: Change viewing angle by 90 degrees up");
                printf("\n       K: Change viewing angle by 90 degrees down");
                printf("\n       J: Change viewing angle by 90 degrees to the left");
                printf("\n       L: Change viewing angle by 90 degrees to the right");
                printf("\n\n Shift+I: look up");
                printf("\n Shift+K: look down");
                printf("\n\n N: y+; E: x+; S: y-; W: x-; up: z+; down: z-\n\n\n");
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
                printf("Create new prism (Input values between 0 and 999 (including 0 and 999) only!):\n\n");
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
