#ifndef MISCELLANEOUS_H
#define MISCELLANEOUS_H
#include<string>
using namespace std;
int file2num(string);
string piece2char(int);
void setupinit (void);
int rank2num(string);
void ManagEnPass(int,int,int,int,int);
void Castle(int,int,int,int,int);
string chfile(int);
string chrank(int);
void Promote(int,int,int);

bool bounds (int, int);
string whitemoves(int, int);
string checkwhite(int, int);
string blackmoves(int,int);
string checkblack(int, int);


#endif // MISCELLANEOUS_H
