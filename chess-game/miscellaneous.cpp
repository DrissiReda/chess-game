#include "miscellaneous.h"
#include<string>
#include<iostream>
using namespace std;
// set each piece and pawn values as constant integers
const int pawn = 100;
const int knight = 300;
const int bishop = 305;
const int rook = 500;
const int queen = 900;
const int king = 20000;

// this is the board it will contain the pieces and pawns
// the first array is for files, the second array is ranks
// ie board[file][rank];
int board[8][8];



// boolean containers for castling start all with true and become false if castling to their direction becomes broken in the game
// wkside is white kingside castling
// wqside is whites and queenside castling etc....
// If position is loaded from FEN, castling true or false is set according to FEN position
bool wkside;
bool wqside;
bool bkside;
bool bqside;
bool wksideC = !true;
bool wqsideC = !true;
bool bksideC = !true;
bool bqsideC = !true;
bool enpassW[8] = {0};
bool enpassB[8] = {0};
int Capt=0;
int Previ=0;
bool UndoC=false;
//onmove is a number that's odd when it is white to move and  even when it is black to move
int onmove = 1;
bool promote=0;
const int setupboard[8][8] = { rook, knight, bishop, queen, king, bishop, knight, rook, pawn, pawn,pawn,pawn,pawn,pawn,pawn, pawn, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                               0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -pawn, -pawn, -pawn, -pawn, -pawn, -pawn, -pawn, -pawn, -rook, -knight, -bishop, -queen, -king, -bishop, -knight, -rook
                             };

//Mettre a la situation initiale
void setupinit (void)
{

    int a;
    int b;

    onmove = 1;

    wkside = true;
    wqside = true;
    bkside = true;
    bqside = true;
    wksideC = !true;
    wqsideC = !true;
    bksideC = !true;
    bqsideC = !true;



    for (a = 0; a < 8; a++)
    {
        for (b = 0; b < 8; b++)
        {
            board[a][b] = setupboard[a][b];
        }
    }
}

bool bounds (int a, int b) //verifier que la case existe
{
    if ((a >= 0) && (a <= 7) && (b >= 0) && (b <= 7))
    {
        return true;
    }
    else
    {
        return false;
    }
}

string chfile(int x)  //takes an integer 0-7 and returns ascii character or one character string of file "a" to "h"
{
    string cho;
    switch(x)
    {
    case 0:
        cho = "a";
        break;
    case 1:
        cho = "b";
        break;
    case 2:
        cho = "c";
        break;
    case 3:
        cho = "d";
        break;
    case 4:
        cho = "e";
        break;
    case 5:
        cho = "f";
        break;
    case 6:
        cho = "g";
        break;
    case 7:
        cho = "h";
        break;

    }
    return cho;
}

string chrank(int x)  //takes an integer (x) 0-7 and returns ascii "1" to '8" Usually to represent rank on the chessboard
{
    string cho;
    switch(x)
    {
    case 0:
        cho = "1";
        break;
    case 1:
        cho = "2";
        break;
    case 2:
        cho = "3";
        break;
    case 3:
        cho = "4";
        break;
    case 4:
        cho = "5";
        break;
    case 5:
        cho = "6";
        break;
    case 6:
        cho = "7";
        break;
    case 7:
        cho = "8";
        break;

    }
    return cho;
}
void ManagEnPass(int a,int b,int c,int d,int onmove)
{
    if(abs(board[b][a]) == pawn)
    {
        if(onmove%2)
        {
            if (b==6 && d==4) // if it creates an en passant case
            {
                enpassW[a]=true;
            }

            if (enpassW[a]) //if it cancelled its own en passant case
            {
                enpassW[a]=false;
            }
            if (enpassB[c]) // if it takes an en passant pawn
            {
                if (board[d][c+1] == pawn) //make sure there is still a pawn
                    board[d][c+1]=0;  // Take that pawn
                Previ=-pawn;
                Capt=pawn; // help undo
                board[d][c]=-pawn;
            }
        }
        else
        {
            if (b==1 && d==3) // if it creates an en passant case
            {
                enpassB[a]=true;
            }

            if (enpassB[a]) //if it cancelled its own en passant case
            {
                enpassB[a]=false;
            }
            if (enpassW[c]) // if it takes an en passant pawn
            {
                if (board[d][c-1] == -pawn) //make sure there is still a pawn
                    board[d][c-1]=0;  // Take that pawn
                Previ=pawn;
                Capt=-pawn;  // help undo
                board[d][c]=pawn;
            }
        }
    }
}
int findking(int M)
{
    if(M%2)
        for(int i=0; i<8; i++)
            for(int j=0; j<8; j++)
            {
                if(board[i][j] == king)
                    return i*10+j;
            }
    else
        for(int i=0; i<8; i++)
            for(int j=0; j<8; j++)
            {
                if(board[i][j] == -king)
                    return i*8+j;
            }
}
int file2num(string f1)
{
    int aa;
    switch (f1[0])
    {
    case 'a':
        aa = 0;
        break;
    case 'b':
        aa = 1;
        break;
    case 'c':
        aa = 2;
        break;
    case 'd':
        aa = 3;
        break;
    case 'e':
        aa = 4;
        break;
    case 'f':
        aa = 5;
        break;
    case 'g':
        aa = 6;
        break;
    case 'h':
        aa = 7;
        break;
    }
    return aa;
}

int rank2num(string f1)
{
    int aa;
    switch (f1[0])
    {
    case '1':
        aa = 0;
        break;
    case '2':
        aa = 1;
        break;
    case '3':
        aa = 2;
        break;
    case '4':
        aa = 3;
        break;
    case '5':
        aa = 4;
        break;
    case '6':
        aa = 5;
        break;
    case '7':
        aa = 6;
        break;
    case '8':
        aa = 7;
        break;
    }
    return aa;
}
void Promote(int C, int D,int M)
{
    promote =1;
    cout<<"Choose a promotion (Q)ueen (K)night (B)ishop (R)ook"
            <<endl;
    char SwitchingChar;
    cin >> SwitchingChar;
    switch (SwitchingChar)
    {
    case 'Q' :
    {
        board[D][C]= (1-2*(M%2))*queen;
        break;
    }
    case 'K' :
    {
        board[D][C]= (1-2*(M%2))*knight;
        break;
    }
    case 'B' :
    {
        board[D][C]= (1-2*(M%2))*bishop;
        break;
    }
    case 'R' :
    {
        board[D][C]= (1-2*(M%2))*rook;
        break;
    }
    }
}
void Castle(int a,int b,int c,int d,int onmove)
{
    if(abs(board[b][a])== king )
    {

        if( (c-a) == 2)
        {
            if(onmove%2)
            {
                board[7][5] = -rook;
                board[7][7] = 0;
                bkside = false;
                bqside=false;
                Capt=-king;
                bksideC=true;

            }
            else
            {
                board[0][5] = rook;
                board[0][7] = 0;
                wkside = false;
                wqside=false;
                Capt= king;
                wksideC=true;
            }
        }
        if ((c-a) == -2)
        {
            if(onmove%2)
            {
                board[7][3] = -rook;
                board[7][0] = 0;
                bqside = false;
                bkside=false;
                Capt= -king;
                bqsideC=true;

            }
            else
            {
                board[0][3] = rook;
                board[0][0] = 0;
                wqside = false;
                wkside=false;
                Capt= king;
                wqsideC=true;
            }
        }
    }
}
string whitemoves(int a,int b)
{
    string allmoves;
    int fromSQa[218];
    int fromSQb[218];
    int toSQa[218];
    int toSQb[218];


    int c = 0;
    int d = 0;
    int e = 0;
    int f = 0;
    int z = 0;


    switch (board[a][b])
    {

    case queen:
    {
        for (e = -1; e <= 1; e++)
        {
            for (f = -1; f <= 1; f++)
            {
                c = a + e;
                d = b + f;
                if (!(f == 0 && e == 0))
                {
                    do
                    {
                        if (bounds(c, d))
                        {

                            if (board[c][d] == 0)
                            {
                                fromSQa[z] = a;
                                fromSQb[z] = b;
                                toSQa[z] = c;
                                toSQb[z] = d;
                                z = z + 1;
                            }
                            if (board[c][d] < 0)
                            {
                                fromSQa[z] = a;
                                fromSQb[z] = b;
                                toSQa[z] = c;
                                toSQb[z] = d;

                                z = z + 1;
                                break;
                            }
                            if (board[c][d] > 0) break;
                            c = c + e;
                            d = d + f;
                        }
                    }
                    while (!(bounds(c, d) == false));

                }

            }
        }
        case rook:
            for (e = -1; e <= 1; e++)
            {
                for (f = -1; f <= 1; f++)
                {
                    c = a + e;
                    d = b + f;
                    if (abs(e)+abs(f) == 1)
                    {
                        do
                        {
                            if (bounds(c, d))
                            {

                                if (board[c][d] == 0)
                                {
                                    fromSQa[z] = a;
                                    fromSQb[z] = b;
                                    toSQa[z] = c;
                                    toSQb[z] = d;
                                    z = z + 1;
                                }
                                if (board[c][d] < 0)
                                {
                                    fromSQa[z] = a;
                                    fromSQb[z] = b;
                                    toSQa[z] = c;
                                    toSQb[z] = d;

                                    z = z + 1;
                                    break;
                                }
                                if (board[c][d] > 0) break;
                                c = c + e;
                                d = d + f;
                            }
                        }
                        while (!(bounds(c, d) == false));

                    }

                }
            }
            break;
        case bishop:
            for (e = -1; e <= 1; e++)
            {
                for (f = -1; f <= 1; f++)
                {
                    c = a + e;
                    d = b + f;
                    if (abs(e)+abs(f) == 2)
                    {
                        do
                        {
                            if (bounds(c, d))
                            {

                                if (board[c][d] == 0)
                                {
                                    fromSQa[z] = a;
                                    fromSQb[z] = b;
                                    toSQa[z] = c;
                                    toSQb[z] = d;
                                    z = z + 1;
                                }
                                if (board[c][d] < 0)
                                {
                                    fromSQa[z] = a;
                                    fromSQb[z] = b;
                                    toSQa[z] = c;
                                    toSQb[z] = d;

                                    z = z + 1;
                                    break;
                                }
                                if (board[c][d] > 0) break;

                            }
                            c = c + e;
                            d = d + f;
                        }
                        while (!(bounds(c, d) == false));
                    }
                }
            }
            break;
        case knight:
            for(e=-2; e<=2; e+=1)
            {
                for(f=-2; f<=2; f+=1)
                {
                    c = a + e;
                    d = b + f;
                    if(abs(e) + abs(f) == 3)
                    {
                        if(bounds(c,d))
                        {
                            if(board[c][d]<=0)
                            {
                                fromSQa[z]=a;
                                fromSQb[z]=b;
                                toSQa[z]=c;
                                toSQb[z]=d;
                                z+=1;
                            }
                        }
                    }
                }
            }
            break;
        case pawn:
//white pawn attack left and forward
            c = a + 1;
            d = b - 1;
            if (bounds(c, d))
            {
//bounds checks if the square is on the board, if not go to next move direction for pawn.

                if (board[c][d] < 0 || enpassW[c])
                {
//if diagonal square attacked contains a piece valued less than zero then capture is possible,
//or square is the en passant square from previous move.
                    fromSQa[z] = a;
                    fromSQb[z] = b;
                    toSQa[z] = c;
                    toSQb[z] = d;
                    z = z + 1;
                }
            }
//white pawn attack right and forward
            c = a + 1;
            d = b + 1;
            if (bounds(c, d))
            {

                if (board[c][d] < 0)
                {
                    fromSQa[z] = a;
                    fromSQb[z] = b;
                    toSQa[z] = c;
                    toSQb[z] = d;
                    z = z + 1;
                }
            }
//check if one square forward is unoccupied and add it to the movelist
            if (a == 1)
            {
                c = 2;
                d = b;
                if (bounds(c, d))
                {

                    if (board[c][d] == 0)
                    {
                        fromSQa[z] = a;
                        fromSQb[z] = b;
                        toSQa[z] = c;
                        toSQb[z] = d;
                        z = z + 1;
                        c = 3;
                        d = b;
//another square forward if the pawn is on it's starting rank
                        if (bounds(c, d))
                        {

                            if (board[c][d] == 0)
                            {
                                fromSQa[z] = a;
                                fromSQb[z] = b;
                                toSQa[z] = c;
                                toSQb[z] = d;
                                z = z + 1;
                            }
                        }
                    }
                }
            }
            else   //pawn is not on starting rank
            {
                c = a + 1;
                d = b;
                if (bounds(c, d))
                {
                    if (board[c][d] == 0)
                    {
                        fromSQa[z] = a;
                        fromSQb[z] = b;
                        toSQa[z] = c;
                        toSQb[z] = d;
                        z = z + 1;
                    }
                }
            }

            break;
        case king:
            for (e = -1; e <= 1; e++)
            {
                for (f = -1; f <= 1; f++)
                {
                    if (!(e == 0 && f == 0))
                    {
                        c = a + e;
                        d = b + f;

                        if (bounds(c, d))   //checks if coordinates exist on the board
                        {

                            if (board[c][d] <= 0 && checkwhite(c, d).empty())
                            {
                                fromSQa[z] = a;
                                fromSQb[z] = b;
                                toSQa[z] = c;
                                toSQb[z] = d;
                                z = z + 1;
                            }
                        }
                    }
                }
            }
//castleKingSide
            if (wkside && a == 0 && b == 4 && board[0][7] == rook && board[0][6] == 0 && board[0][5] == 0)
            {
                if (checkwhite(0, 4).empty() && checkwhite(0, 5).empty() && checkwhite(0, 6).empty())
                {
                    fromSQa[z] = 0;
                    fromSQb[z] = 4;
                    toSQa[z] = 0;
                    toSQb[z] = 6;
                    z = z + 1;
                }
            }

//castleQueenSide
            if (wqside == true && a == 0 && b == 4 && board[0][0] == rook
                    && board[0][1] == 0 && board[0][2] == 0 && board[0][3] == 0)
            {
                if (checkwhite(0, 4).empty() && checkwhite(0, 3).empty() && checkwhite(0, 2).empty())
                {
                    fromSQa[z] = 0;
                    fromSQb[z] = 4;
                    toSQa[z] = 0;
                    toSQb[z] = 2;
                    z = z + 1;
                }
            }
        } // close switch

    }
//now all moves are checked to see if they leave the white king in check and if they do they are discarded from the list
    int i;
    int captured;
    int wksqa, wksqb;
    string addmove;

    if(board[a][b] == king)
    {
        wksqa = a;
        wksqb = b;
        goto kingfound;
    }
kingfound:
    bool epcapture;
    epcapture = false;

    i = 0;
    for(i = 0; i < z; i++)
    {
        a = fromSQa[i];
        b = fromSQb[i];
        c = toSQa[i];
        d = toSQb[i];

//perform the move
        captured = board[c][d];
        board[c][d] = board[a][b];
        board[a][b] = 0;

        if(board[c][d] == pawn && (b != d) && (captured == 0) && bounds((c - 1), d))
        {
            board[c-1][d] = 0;
            epcapture = true;
        }

//if the king is the piece moving wksqa and wksqb won't contain the coordinates of the king! c and d will
        if(board[c][d] == king)
        {
            if(checkwhite(c, d).empty())
            {
//add move to list, otherwise discard move (do nothing)
                addmove = chfile(b) + chrank(a) + chfile(d) + chrank(c); //convert coordinates to ascii
                allmoves = allmoves + addmove; //add to the movelist
            }
        }
        else
        {
//if the king is not the piece moving then the king is in the coordinates wksqa and wksqb,
//and we check that square for check, if it is check it is not added to the movelist (allmoves)
            if(checkwhite(wksqa, wksqb).empty())
            {
//add move to list, otherwise discard move (do nothing)
                if(!(board[c][d] == pawn && (c == 7)))
                {
// if the move is not a pawn progressed to the 8th rank, then add move to the list, otherwise,
//pawn promotions and underpromotions must be added to the move list (each)
                    addmove = chfile(b) + chrank(a) + chfile(d) + chrank(c); //convert coordinates to ascii
                    allmoves = allmoves + addmove; //add to the movelist
                }
                else
                {

                    addmove = chfile(b) + chrank(a) + chfile(d)+ chrank(c);
//promotion is 4 characters the file the pawn starts on followed by the rank and file moving to (if capturing will
//be different) followed by either q for promote to queen, r for rook, n for knight and b for bishop.
                    allmoves = allmoves + addmove; //add to the movelist

                }
            }
        }
//undo the move
        board[a][b] = board[c][d];
        board[c][d] = captured;

        if (epcapture == true)
        {
            board[c-1][d] = -pawn;
            epcapture = false;

        }

    }
    return allmoves;
}

string checkwhite(int ksqa, int ksqb)
{
    int checklista[16];
    int checklistb[16];
    int a, b, c, d, e, f, g, num, xa, xb;
    int repl;
    num = 0;
    string freturn;
    a = ksqa;
    b = ksqb;

    for (e = -2; e < 3; e++)
    {
        for (f = -2; f < 3; f++)
        {

            if ((abs(e) + abs(f)) == 3)  // check for black knight giving check
            {
                c = a + e;
                d = b + f;
                if (bounds(c, d))
                {

                    if (board[c][d] == -knight )
                    {
                        checklista[num] = c;
                        checklistb[num++] = d;
                    }
                }
            } // end check for black knight
            if ((abs(e) == 1 || abs(f) == 1) && abs(e) + abs(f) <= 2) //check for black king giving check
            {
                c = a + e;
                d = b + f;
                if (bounds(c, d))
                {

                    if (board[c][d] == -king )
                    {
                        checklista[num] = c;
                        checklistb[num++] = d;
                    }
                }
            } // end check for black king

            g = abs(e) + abs(f);
            if (g == 1) // check for queen and rook
            {
                c = a + e;
                d = b + f;
                while (bounds(c, d))
                {
//rook or queen (vertical/horizontal)
                    if (board[c][d] == -queen || board[c][d] == -rook)
                    {
                        checklista[num] = c;
                        checklistb[num++] = d;
                        num++;
                    }
                    if (board[c][d] != 0) break;

                    c = c + e;
                    d = d + f;
                }
            }
//bishop or queen (diagonally)
            if (g == 2 && abs(e) == 1)
            {
                c = a + e;
                d = b + f;
                while (bounds(c, d))
                {

                    if (board[c][d] == -queen || board[c][d] == -bishop)
                    {
                        checklista[num] = c;
                        checklistb[num] = d;
                        num = num + 1;
                    }
                    if (board[c][d] != 0) break;

                    c = c + e;
                    d = d + f;
                }
            }
        }
    }

//black pawns deliver check
    c = a + 1;
    d = b + 1;

    if (bounds(c, d))
    {

        if (board[c][d] == -pawn)
        {
            checklista[num] = c;
            checklistb[num] = d;
            num++;
        }
    }

    c = a + 1;
    d = b - 1;
    if (bounds(c, d))
    {

        if (board[c][d] == -pawn)
        {
            checklista[num] = c;
            checklistb[num] = d;
            num++;
        }
    }

    string aa, bb, cc, dd;

    switch (num)
    {
    case 0:
        freturn.clear();
        break;
    case 1:

        aa = chfile(ksqb);
        bb = chrank(ksqa);
        xa = checklista[0];
        xb = checklistb[0];
        cc = chfile(xb);
        dd = chrank(xa);
        freturn = aa + bb + cc + dd;

        break;
    default:
        aa = chfile(ksqb);
        bb = chrank(ksqa);
        xa = checklista[0];
        xb = checklistb[0];
        cc = chfile(xb);
        dd = chrank(xa);
        freturn = aa + bb + cc + dd;
        xa = checklista[1];
        xb = checklistb[1];
        cc = chfile(xb);
        dd = chrank(xa);
        freturn = freturn + cc + dd;
        break;

    }
    return freturn;
}

string checkblack(int ksqa, int ksqb)
{
    int checklista[16];
    int checklistb[16];
    int a, b, c, d, e, f, g, num, xa, xb;
    num = 0;
    string freturn;

    a = ksqa;
    b = ksqb;

    for (e = -2; e < 3; e++)
    {
        for (f = -2; f < 3; f++)
        {

            if ((abs(e) + abs(f)) == 3)  // check for white knight giving check
            {
                c = a + e;
                d = b + f;
                if (bounds(c, d))
                {

                    if (board[c][d] == knight )
                    {
                        checklista[num] = c;
                        checklistb[num++] = d;
                    }
                }
            } // end check for black knight
            if ((abs(e) == 1 || abs(f) == 1) && abs(e) + abs(f) <= 2) //check for black king giving check
            {
                c = a + e;
                d = b + f;
                if (bounds(c, d))
                {

                    if (board[c][d] == king )
                    {
                        checklista[num] = c;
                        checklistb[num++] = d;
                    }
                }
            } // end check for black king

            g = abs(e) + abs(f);
            if (g == 1) // check for queen and rook
            {
                c = a + e;
                d = b + f;
                while (bounds(c, d))
                {
//rook or queen (vertical/horizontal)
                    if (board[c][d] == queen || board[c][d] == rook)
                    {
                        checklista[num] = c;
                        checklistb[num++] = d;
                        num++;
                    }
                    if (board[c][d] != 0) break;

                    c = c + e;
                    d = d + f;
                }
            }
//bishop or queen (diagonally)
            if (g == 2 && abs(e) == 1)
            {
                c = a + e;
                d = b + f;
                while (bounds(c, d))
                {

                    if (board[c][d] == queen || board[c][d] == bishop)
                    {
                        checklista[num] = c;
                        checklistb[num] = d;
                        num = num + 1;
                    }
                    if (board[c][d] != 0) break;

                    c = c + e;
                    d = d + f;
                }
            }
        }
    }

//white pawns deliver check
    c = a - 1;
    d = b + 1;

    if (bounds(c, d))
    {

        if (board[c][d] == pawn)
        {
            checklista[num] = c;
            checklistb[num] = d;
            num++;
        }
    }

    c = a - 1;
    d = b - 1;
    if (bounds(c, d))
    {

        if (board[c][d] == pawn)
        {
            checklista[num] = c;
            checklistb[num] = d;
            num++;
        }
    }

    string aa, bb, cc, dd;

    switch (num)
    {
    case 0:
        freturn.clear();
        break;
    case 1:

        aa = chfile(ksqb);
        bb = chrank(ksqa);
        xa = checklista[0];
        xb = checklistb[0];
        cc = chfile(xb);
        dd = chrank(xa);
        freturn = aa + bb + cc + dd;

        break;
    default:
        aa = chfile(ksqb);
        bb = chrank(ksqa);
        xa = checklista[0];
        xb = checklistb[0];
        cc = chfile(xb);
        dd = chrank(xa);
        freturn = aa + bb + cc + dd;
        xa = checklista[1];
        xb = checklistb[1];
        cc = chfile(xb);
        dd = chrank(xa);
        freturn = freturn + cc + dd;
        break;

    }
    return freturn;
}
string blackmoves(int a,int b)
{
    string allmoves;
    int fromSQa[218];
    int fromSQb[218];
    int toSQa[218];
    int toSQb[218];


    int c = 0;
    int d = 0;
    int e = 0;
    int f = 0;
    int z = 0;
    switch (board[a][b])
    {
    case -queen: //generate animal moves for black queen (found on square where rank is a, file is b.)

    {
        for (e = -1; e <= 1; e++)
        {
            for (f = -1; f <= 1; f++)
            {
                c = a + e;
                d = b + f;
                if (!(e == 0 && f == 0))
                {
                    do
                    {
                        if (bounds(c, d))
                        {

                            if (board[c][d] == 0)
                            {
                                fromSQa[z] = a;
                                fromSQb[z] = b;
                                toSQa[z] = c;
                                toSQb[z] = d;
                                z = z + 1;
                            }
                            if (board[c][d] > 0)
                            {
                                fromSQa[z] = a;
                                fromSQb[z] = b;
                                toSQa[z] = c;
                                toSQb[z] = d;

                                z = z + 1;
                                break;
                            }
                            if (board[c][d] < 0) break;
                            c = c + e;
                            d = d + f;
                        }
                    }
                    while (!(bounds(c, d) == false));

                }

            }
        }

        break;

        case -rook:
            for (e = -1; e <= 1; e++)
            {
                for (f = -1; f <= 1; f++)
                {
                    c = a + e;
                    d = b + f;
                    if (abs(e)+abs(f) == 1)
                    {
                        do
                        {
                            if (bounds(c, d))
                            {

                                if (board[c][d] == 0)
                                {
                                    fromSQa[z] = a;
                                    fromSQb[z] = b;
                                    toSQa[z] = c;
                                    toSQb[z] = d;
                                    z = z + 1;
                                }
                                if (board[c][d] > 0)
                                {
                                    fromSQa[z] = a;
                                    fromSQb[z] = b;
                                    toSQa[z] = c;
                                    toSQb[z] = d;

                                    z = z + 1;
                                    break;
                                }
                                if (board[c][d] < 0) break;
                                c = c + e;
                                d = d + f;
                            }
                        }
                        while (!(bounds(c, d) == false));

                    }

                }
            }
            break;
        case -bishop:
            for (e = -1; e <= 1; e++)
            {
                for (f = -1; f <= 1; f++)
                {
                    c = a + e;
                    d = b + f;
                    if (abs(e)+abs(f) == 2)
                    {
                        do
                        {
                            if (bounds(c, d))
                            {

                                if (board[c][d] == 0)
                                {
                                    fromSQa[z] = a;
                                    fromSQb[z] = b;
                                    toSQa[z] = c;
                                    toSQb[z] = d;
                                    z = z + 1;
                                }
                                if (board[c][d] > 0)
                                {
                                    fromSQa[z] = a; //toSQa[18]
                                    fromSQb[z] = b;
                                    toSQa[z] = c;
                                    toSQb[z] = d;

                                    z = z + 1;
                                    break;
                                }
                                if (board[c][d] < 0) break;

                            }
                            c = c + e;
                            d = d + f;
                        }
                        while (bounds(c, d));
                    }
                }
            }
            break;
        case -knight:
            for(e=-2; e<=2; e+=1)
            {
                for(f=-2; f<=2; f+=1)
                {
                    c = a + e;
                    d = b + f;
                    if(abs(e) + abs(f) == 3)
                    {
                        if(bounds(c,d))
                        {
                            if(board[c][d]>=0)
                            {
                                fromSQa[z]=a;
                                fromSQb[z]=b;
                                toSQa[z]=c;
                                toSQb[z]=d;
                                z+=1;
                            }
                        }
                    }
                }
            }
            break;
        case -pawn:
//white pawn attack left and forward (forward from blacks perspective)
            c = a - 1;
            d = b + 1;
            if (bounds(c, d))
            {

                if (board[c][d] > 0 || enpassB[c])
                {
//if diagonal square attacked contains a piece valued more than zero
//then capture is possible, or square is the en passant square from previous move.
                    fromSQa[z] = a;
                    fromSQb[z] = b;
                    toSQa[z] = c;
                    toSQb[z] = d;
                    z = z + 1;
                }
            }
//white pawn attack right and forward
            c = a - 1;
            d = b - 1;
            if (bounds(c, d))
            {

                if (board[c][d] > 0)
                {
                    fromSQa[z] = a;
                    fromSQb[z] = b;
                    toSQa[z] = c;
                    toSQb[z] = d;
                    z = z + 1;
                }
            }
//check if one square forward is unoccupied and add it to the movelist
            if (a == 6)
            {
                c = 5;
                d = b;
                if (bounds(c, d))
                {

                    if (board[c][d] == 0)
                    {
                        fromSQa[z] = a;
                        fromSQb[z] = b;
                        toSQa[z] = c;
                        toSQb[z] = d;
                        z = z + 1;
//decrement the file for c, d (coordinates for move to testing)
                        c = 4;
                        d = b;
//another square forward if the pawn is on it's starting rank
                        if (bounds(c, d))
                        {

                            if (board[c][d] == 0)
                            {
                                fromSQa[z] = a;
                                fromSQb[z] = b;
                                toSQa[z] = c;
                                toSQb[z] = d;
                                z = z + 1;
                            }
                        }
                    }
                }
            }
            else   //pawn is not on starting rank
            {
                c = a - 1;
                d = b;
                if (bounds(c, d))
                {
                    if (board[c][d] == 0)
                    {
                        fromSQa[z] = a;
                        fromSQb[z] = b;
                        toSQa[z] = c;
                        toSQb[z] = d;
                        z = z + 1;
                    }
                }
            }

            break;
        case -king:
            for (e = -1; e <= 1; e++)
            {
                for (f = -1; f <= 1; f++)
                {
                    if (!(e == 0 && f == 0))
                    {
                        c = a + e;
                        d = b + f;

                        if (bounds(c, d))   //checks if coordinates exist on the board
                        {

                            if (board[c][d] >= 0 && checkblack(c, d).empty())
                            {
                                fromSQa[z] = a;
                                fromSQb[z] = b;
                                toSQa[z] = c;
                                toSQb[z] = d;
                                z = z + 1;
                            }
                        }
                    }
                }
            }
//castleKingSide
            if (bkside && a == 7 && b == 4 && board[7][7] == -rook && board[7][6] == 0 && board[7][5] == 0)
            {
                if (checkblack(7, 4).empty() && checkblack(7, 5).empty() && checkblack(7, 6).empty())
                {
                    fromSQa[z] = 7;
                    fromSQb[z] = 4;
                    toSQa[z] = 7;
                    toSQb[z] = 6;
                    z = z + 1;
                }
            }

//castleQueenSide
            if (bqside == true && a == 7 && b == 4 && board[7][0] == -rook &&
                    board[7][1] == 0 && board[7][2] == 0 && board[7][3] == 0)
            {
                if (checkblack(7, 4).empty() && checkblack(7, 3).empty() && checkblack(7, 2).empty())
                {
                    fromSQa[z] = 7;
                    fromSQb[z] = 4;
                    toSQa[z] = 7;
                    toSQb[z] = 2;
                    z = z + 1;
                }
            }
        } // close switch

    }
//now all moves are checked to see if they leave the white king in check and if they do they are discarded from the list
    int i;
    int captured;
    int bksqa, bksqb;
    string addmove;

    for(a = 0; a <= 7; a++)
    {
        for(b = 0; b <= 7; b++)
        {
            if(board[a][b] == -king)
            {
                bksqa = a;
                bksqb = b;
                goto kingfound;
            }
        }
    }
kingfound:

    bool epcapture;
    epcapture = false;

    for(i = 0; i < z; i++)
    {
        a = fromSQa[i];
        b = fromSQb[i];
        c = toSQa[i];
        d = toSQb[i];
        if(!bounds(a, b) || !bounds(c, d))
        {

        }
//perform the move
        captured = board[c][d];
        board[c][d] = board[a][b];
        board[a][b] = 0;

        if(board[c][d] == -pawn && (b != d) && (captured == 0) && bounds((c + 1), d))
        {
            board[c+1][d] = 0;
            epcapture = true;
        }

//if the king is the piece moving wksqa and wksqb won't contain the coordinates of the king! c and d will
        if(board[c][d] == -king)
        {
            if(checkblack(c, d).empty())
            {
//add move to list, otherwise discard move (do nothing)
                addmove = chfile(b) + chrank(a) + chfile(d) + chrank(c); //convert coordinates to ascii
                allmoves = allmoves + addmove; //add to the movelist
            }
        }
        else
        {
//if the king is not the piece moving then the king is in the coordinates wksqa and wksqb,
//and we check that square for check, if it is check it is not added to the movelist (allmoves)
            string p2;
            p2 = checkblack(bksqa, bksqb);
            if(checkblack(bksqa, bksqb).empty())
            {
//add move to list, otherwise discard move (do nothing)
                if(!(board[c][d] == -pawn && (c == 0)))
                {
// if the move is not a pawn progressed to the 8th rank, then add move to the list
//, otherwise, pawn promotions and underpromotions must be added to the move list (each)
                    addmove = chfile(b) + chrank(a) + chfile(d) + chrank(c); //convert coordinates to ascii
                    allmoves = allmoves + addmove; //add to the movelist
                }
                else
                {

                    addmove = chfile(b) + chrank(a) + chfile(d) + chrank(c) ;
//promotion is 4 characters the file the pawn starts on followed by the rank and file
//moving to (if capturing will be different) followed by either q for promote to queen, r for rook, n for knight and b for bishop.
                    allmoves = allmoves + addmove; //add to the movelist

                }
            }
        }
//undo the move
        board[a][b] = board[c][d];
        board[c][d] = captured;

        if (epcapture == true)
        {
            board[c+1][d] = -pawn;
            epcapture = false;

        }

    }
    return allmoves;
}

