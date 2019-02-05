//Complete and fully functional!!!
#include <iostream>
#include <fstream>
#include <iomanip>


using namespace std;

const int NO_PIECE = 5;
const int WHITE_PAWN = 1;
const int WHITE_KING = 2;
const int RED_PAWN = 3;
const int RED_KING = 4;
const int ELEMENTS = 8;
const int WHITEPLAYER = 1;
const int REDPLAYER = 2;
const int MAX_PIECES = 24;

int checkerBoard[ELEMENTS][ELEMENTS] = {0};
int xArray[MAX_PIECES] = {0};
int yArray[MAX_PIECES] = {0};
int xJumpArray[MAX_PIECES] = {0};
int yJumpArray[MAX_PIECES] = {0};
int availableMoves[MAX_PIECES] = {0};
int availableJumps[MAX_PIECES] = {0};
int squareNumber = 0;
int endSquareNumber = 0;
int player = 1;
int numMoves=4;
int numJumps=0;
bool canMove=false;
bool canJump=false;

void InitializeBoard(int CHECKERBOARD[ELEMENTS][ELEMENTS]);
void DisplayBoard(int CHECKERBOARD[ELEMENTS][ELEMENTS]);
void MakeMove(int CMCheckersBoard[ELEMENTS][ELEMENTS]);
void DisplayMoves(int CMCheckersBoard[ELEMENTS][ELEMENTS], int xLocArray[MAX_PIECES], int yLocArray[MAX_PIECES], int xJumpArray[MAX_PIECES], int yJumpArray[MAX_PIECES]);
void ChangePawntoKing(int CMCheckersBoard[ELEMENTS][ELEMENTS]);
int CountMoveSquares(int CMCheckersBoard[ELEMENTS][ELEMENTS], int player, int xLocArray[MAX_PIECES], int yLocArray[MAX_PIECES]);
int CountJumpSquares(int CMCheckersBoard[ELEMENTS][ELEMENTS], int player, int xLocArray[MAX_PIECES], int yLocArray[MAX_PIECES]);
bool IsMoveSquare(int CMCheckersBoard[ELEMENTS][ELEMENTS], int player, int xindex, int yindex);
bool IsJumpSquare(int CMCheckersBoard[ELEMENTS][ELEMENTS], int player, int xindex, int yindex);
bool CheckSelectedPiece(int CMCheckersBoard[ELEMENTS][ELEMENTS], int player, int xLocArray[MAX_PIECES], int yLocArray[MAX_PIECES], int xJumpArray[MAX_PIECES], int yJumpArray[MAX_PIECES]);
bool CheckEndSpot(int CMCheckersBoard[ELEMENTS][ELEMENTS], int player, int xLocArray[MAX_PIECES], int yLocArray[MAX_PIECES], int xJumpArray[MAX_PIECES], int yJumpArray[MAX_PIECES]);
bool CheckWin(int CMCheckersBoard[ELEMENTS][ELEMENTS], int xLocArray[MAX_PIECES], int yLocArray[MAX_PIECES]);

int main()
{
	InitializeBoard(checkerBoard);
	while (!CheckWin(checkerBoard, xArray, yArray))
	{
		ChangePawntoKing(checkerBoard);
		DisplayBoard(checkerBoard);
		if (player==WHITEPLAYER)
		{
			cout<<endl<<endl<<"It's white's turn.";
		}
		else if (player==REDPLAYER)
		{
			cout<<endl<<endl<<"It's red's turn.";
		}
		DisplayMoves(checkerBoard, xArray, yArray, xJumpArray, yJumpArray);
		while ((!CheckSelectedPiece(checkerBoard, player, xArray, yArray, xJumpArray, yJumpArray)))
		{
			cin.clear();
			cin.sync();
		}
		while ((!CheckEndSpot(checkerBoard, player, xArray, yArray, xJumpArray, yJumpArray)))
		{
			cin.clear();
			cin.sync();
			while ((!CheckSelectedPiece(checkerBoard, player, xArray, yArray, xJumpArray, yJumpArray)))
			{
			cin.clear();
			cin.sync();
			}
		}
		MakeMove(checkerBoard);
		cout<<endl<<endl<<"Your turn is over.";
	}
	return 0;
}

void InitializeBoard(int CHECKERBOARD[ELEMENTS][ELEMENTS])
{
	int i=0;
	int j=0;
	for (i=0;i<ELEMENTS;i++)
	{
		for (j=0;j<ELEMENTS;j++)
		{
			if ((i==0||i==2) && j%2==0)
			{
				CHECKERBOARD[i][j]=WHITE_PAWN;
			}
			else if (i==1 && j%2==1)
			{
				CHECKERBOARD[i][j]=WHITE_PAWN;
			}
			else if ((i==5||i==7) && j%2==1)
			{
				CHECKERBOARD[i][j]=RED_PAWN;
			}
			else if (i==6 && j%2==0)
			{
				CHECKERBOARD[i][j]=RED_PAWN;
			}
			else
			{
				CHECKERBOARD[i][j]=NO_PIECE;
			}
		}
	}
}
void DisplayBoard(int CHECKERBOARD[ELEMENTS][ELEMENTS])
{
	int i=0;
	int j=0;
	int count=0;
	for (i=0;i<ELEMENTS;i++)
	{
		for (j=0;j<ELEMENTS;j++)
		{
			if (count%ELEMENTS==0)
			{
				cout<<endl;
			}
			if (CHECKERBOARD[i][j]==WHITE_PAWN)
			{
				cout<<fixed<<setw(4)<<"WP";
			}
			else if (CHECKERBOARD[i][j]==WHITE_KING)
			{
				cout<<fixed<<setw(4)<<"WK";
			}
			else if (CHECKERBOARD[i][j]==RED_PAWN)
			{
				cout<<fixed<<setw(4)<<"RP";
			}
			else if (CHECKERBOARD[i][j]==RED_KING)
			{
				cout<<fixed<<setw(4)<<"RK";
			}
			else if (CHECKERBOARD[i][j]==NO_PIECE)
			{
				cout<<fixed<<setw(4)<<count;
			}
			count++;
		}
	}
}
int CountMoveSquares( int CMCheckersBoard[ELEMENTS][ELEMENTS], int player, int xLocArray[], int yLocArray[])
{
	int yindex=0;
	int xindex=0;
	int i=0;
	int numMove=0;
	for (i=0;i<MAX_PIECES;i++)
	{
		xLocArray[i]=-1;
		yLocArray[i]=-1;
	}
	i=0;
	for (yindex=0;yindex<ELEMENTS;yindex++)
	{
		for (xindex=0;xindex<ELEMENTS;xindex++)
		{
			if (IsMoveSquare(CMCheckersBoard, player, xindex, yindex)==true)
			{
				numMove++;
				xLocArray[i]=xindex;
				yLocArray[i]=yindex;
				i++;
			}
		}
	}
	return numMove;
}	
bool IsMoveSquare(int CMCheckersBoard[ELEMENTS][ELEMENTS], int player, int xindex, int yindex)
{
	if (player==WHITEPLAYER)
	{
		if (CMCheckersBoard[xindex][yindex]==WHITE_PAWN)
		{
			if (xindex==7)
			{
				return false;
			}
			if (yindex==0 && CMCheckersBoard[xindex+1][yindex+1]==NO_PIECE)
			{
				return true;
			}
			else if (yindex==7 && CMCheckersBoard[xindex+1][yindex-1]==NO_PIECE)
			{
				return true;
			}
			else if ((CMCheckersBoard[xindex+1][yindex+1]==NO_PIECE || CMCheckersBoard[xindex+1][yindex-1]==NO_PIECE)&&(yindex!=0 && yindex!=7))
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else if (CMCheckersBoard[xindex][yindex]==WHITE_KING)
		{
			if ((xindex==7 && yindex==0 && CMCheckersBoard[xindex-1][yindex+1]==NO_PIECE) || (xindex==7 && yindex==7 && CMCheckersBoard[xindex-1][yindex-1]==NO_PIECE) || (xindex==0 && yindex==0 && CMCheckersBoard[xindex+1][yindex+1]==NO_PIECE) || (xindex==0 && yindex==7 && CMCheckersBoard[xindex-1][yindex+1]==NO_PIECE))
			{
				return true;
			}
			else if (yindex==0 && (CMCheckersBoard[xindex+1][yindex+1]==NO_PIECE || CMCheckersBoard[xindex-1][yindex+1]==NO_PIECE)&&xindex!=0&&xindex!=7)
			{
				return true;
			}
			else if (yindex==7 && (CMCheckersBoard[xindex+1][yindex-1]==NO_PIECE || CMCheckersBoard[xindex-1][yindex-1])&&yindex!=0&&yindex!=7)
			{
				return true;
			}
			else if (xindex==0 && (CMCheckersBoard[xindex+1][yindex+1]==NO_PIECE || CMCheckersBoard[xindex+1][yindex-1]==NO_PIECE)&&yindex!=0&&yindex!=7)
			{
				return true;
			}
			else if (xindex==7 && (CMCheckersBoard[xindex-1][yindex+1]==NO_PIECE || CMCheckersBoard[xindex-1][yindex-1])&&xindex!=0&&xindex!=7)
			{
				return true;
			}
			else if ((CMCheckersBoard[xindex+1][yindex+1]==NO_PIECE || CMCheckersBoard[xindex+1][yindex-1]==NO_PIECE || CMCheckersBoard[xindex-1][yindex+1]==NO_PIECE || CMCheckersBoard[xindex-1][yindex-1]==NO_PIECE) && yindex!=0 && yindex!=7 && xindex!=0&&xindex!=7)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}
	if (player==REDPLAYER)
	{
		if (CMCheckersBoard[xindex][yindex]==RED_PAWN)
		{
			if (xindex==0)
			{
				return false;
			}
			if (yindex==0 && CMCheckersBoard[xindex-1][yindex+1]==NO_PIECE)
			{
				return true;
			}
			else if (yindex==7 && CMCheckersBoard[xindex-1][yindex-1]==NO_PIECE)
			{
				return true;
			}
			else if ((CMCheckersBoard[xindex-1][yindex+1]==NO_PIECE || CMCheckersBoard[xindex-1][yindex-1]==NO_PIECE) && (yindex!=0 && yindex!=7))
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else if (CMCheckersBoard[xindex][yindex]==RED_KING)
		{
			if ((xindex==7 && yindex==0 && CMCheckersBoard[xindex-1][yindex+1]==NO_PIECE) || (xindex==7 && yindex==7 && CMCheckersBoard[xindex-1][yindex-1]==NO_PIECE) || (xindex==0 && yindex==0 && CMCheckersBoard[xindex+1][yindex+1]==NO_PIECE) || (xindex==0 && yindex==7 && CMCheckersBoard[xindex-1][yindex+1]==NO_PIECE))
			{
				return true;
			}
			else if (yindex==0 && (CMCheckersBoard[xindex+1][yindex+1]==NO_PIECE || CMCheckersBoard[xindex-1][yindex+1]==NO_PIECE)&&xindex!=0&&xindex!=7)
			{
				return true;
			}
			else if (yindex==7 && (CMCheckersBoard[xindex+1][yindex-1]==NO_PIECE || CMCheckersBoard[xindex-1][yindex-1])&&yindex!=0&&yindex!=7)
			{
				return true;
			}
			else if (xindex==0 && (CMCheckersBoard[xindex+1][yindex+1]==NO_PIECE || CMCheckersBoard[xindex+1][yindex-1]==NO_PIECE)&&yindex!=0&&yindex!=7)
			{
				return true;
			}
			else if (xindex==7 && (CMCheckersBoard[xindex-1][yindex+1]==NO_PIECE || CMCheckersBoard[xindex-1][yindex-1])&&xindex!=0&&xindex!=7)
			{
				return true;
			}
			else if ((CMCheckersBoard[xindex+1][yindex+1]==NO_PIECE || CMCheckersBoard[xindex+1][yindex-1]==NO_PIECE || CMCheckersBoard[xindex-1][yindex+1]==NO_PIECE || CMCheckersBoard[xindex-1][yindex-1]==NO_PIECE) && yindex!=0 && yindex!=7 && xindex!=0&&xindex!=7)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}
}
int CountJumpSquares( int CMCheckersBoard[ELEMENTS][ELEMENTS], int player, int xLocArray[], int yLocArray[])
{
	int yindex=0;
	int xindex=0;
	int i=0;
	int numJump=0;
	for (i=0;i<MAX_PIECES;i++)
	{
		xLocArray[i]=-1;
		yLocArray[i]=-1;
	}
	i=0;
	for (yindex=0;yindex<ELEMENTS;yindex++)
	{
		for (xindex=0;xindex<ELEMENTS;xindex++)
		{
			if (IsJumpSquare(CMCheckersBoard, player, xindex, yindex)==true)
			{
				numJump++;
				xLocArray[i]=xindex;
				yLocArray[i]=yindex;
				i++;
			}
		}
	}
	return numJump;
}	
bool IsJumpSquare(int CMCheckersBoard[ELEMENTS][ELEMENTS], int player, int xindex, int yindex)
{
	if (player==WHITEPLAYER)
	{
		if (CMCheckersBoard[xindex][yindex]==WHITE_PAWN)
		{
			if (xindex==6 || xindex==7)
			{
				return false;
			}
			else if ((yindex==0 || yindex==1) && (CMCheckersBoard[xindex+1][yindex+1]==RED_PAWN||CMCheckersBoard[xindex+1][yindex+1]==RED_KING) && CMCheckersBoard[xindex+2][yindex+2]==NO_PIECE)
			{
				return true;
			}
			else if ((yindex==7 || yindex==6) && (CMCheckersBoard[xindex+1][yindex-1]==RED_PAWN||CMCheckersBoard[xindex+1][yindex-1]==RED_KING) && CMCheckersBoard[xindex+2][yindex-2]==NO_PIECE)
			{
				return true;
			}
			else if ((((CMCheckersBoard[xindex+1][yindex-1]==RED_PAWN||CMCheckersBoard[xindex+1][yindex-1]==RED_KING)&& (CMCheckersBoard[xindex+2][yindex-2]==NO_PIECE))||((CMCheckersBoard[xindex+1][yindex+1]==RED_PAWN||CMCheckersBoard[xindex+1][yindex+1]==RED_KING)&& CMCheckersBoard[xindex+2][yindex+2]==NO_PIECE))&&yindex!=0 && yindex!=7 && yindex!=1 && yindex!=6)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else if (CMCheckersBoard[xindex][yindex]==WHITE_KING)
		{
			if (((yindex==0 || yindex==1) && (xindex==0 || xindex==1) && (CMCheckersBoard[xindex+1][yindex+1]==RED_PAWN||CMCheckersBoard[xindex+1][yindex+1]==RED_KING) && CMCheckersBoard[xindex+2][yindex+2]==NO_PIECE)||((yindex==0 || yindex==1) && (xindex==7 || xindex==6) && (CMCheckersBoard[xindex-1][yindex+1]==RED_PAWN||CMCheckersBoard[xindex-1][yindex+1]==RED_KING) && CMCheckersBoard[xindex-2][yindex+2]==NO_PIECE))
			{
				return true;
			}
			else if (((yindex==7 || yindex==6) && (xindex==0 ||xindex==1) && (CMCheckersBoard[xindex+1][yindex-1]==RED_PAWN||CMCheckersBoard[xindex+1][yindex-1]==RED_KING) && CMCheckersBoard[xindex+2][yindex-2]==NO_PIECE)||((yindex==7 || yindex==6) && (xindex==7 || xindex==6) && (CMCheckersBoard[xindex-1][yindex-1]==RED_PAWN||CMCheckersBoard[xindex-1][yindex-1]==RED_KING) && CMCheckersBoard[xindex-2][yindex-2]==NO_PIECE))
			{
				return true;
			}
			else if ((xindex==0 || xindex==1) && yindex!=0 && yindex!=7 && yindex!=1 && yindex!=6 && (((CMCheckersBoard[xindex+1][yindex-1]==RED_PAWN||CMCheckersBoard[xindex+1][yindex-1]==RED_KING) && CMCheckersBoard[xindex+2][yindex-2]==NO_PIECE)||((CMCheckersBoard[xindex+1][yindex+1]==RED_PAWN||CMCheckersBoard[xindex+1][yindex+1]==RED_KING) && CMCheckersBoard[xindex+2][yindex+2]==NO_PIECE)))
			{
				return true;
			}
			else if ((xindex==7 || xindex==6) && yindex!=0 && yindex!=7 && yindex!=1 && yindex!=6 && (((CMCheckersBoard[xindex-1][yindex-1]==RED_PAWN||CMCheckersBoard[xindex-1][yindex-1]==RED_KING) && CMCheckersBoard[xindex-2][yindex-2]==NO_PIECE)||((CMCheckersBoard[xindex-1][yindex+1]==RED_PAWN||CMCheckersBoard[xindex-1][yindex+1]==RED_KING) && CMCheckersBoard[xindex-2][yindex+2]==NO_PIECE)))
			{
				return true;
			}
			else if ((yindex==0 || yindex==1) && xindex!=0 && xindex!=7 && xindex!=1 && xindex!=6 && (((CMCheckersBoard[xindex-1][yindex+1]==RED_PAWN||CMCheckersBoard[xindex-1][yindex+1]==RED_KING) && CMCheckersBoard[xindex-2][yindex+2]==NO_PIECE)||((CMCheckersBoard[xindex+1][yindex+1]==RED_PAWN||CMCheckersBoard[xindex+1][yindex+1]==RED_KING) && CMCheckersBoard[xindex+2][yindex+2]==NO_PIECE)))
			{
				return true;
			}
			else if ((yindex==7 || yindex==6) && xindex!=0 && xindex!=7 && xindex!=1 && xindex!=6 && (((CMCheckersBoard[xindex+1][yindex-1]==RED_PAWN||CMCheckersBoard[xindex+1][yindex-1]==RED_KING) && CMCheckersBoard[xindex+2][yindex-2]==NO_PIECE)||((CMCheckersBoard[xindex-1][yindex-1]==RED_PAWN||CMCheckersBoard[xindex-1][yindex-1]==RED_KING) && CMCheckersBoard[xindex-2][yindex-2]==NO_PIECE)))
			{
				return true;
			}
			else if (xindex!=0 && xindex!=7 && xindex!=1 && xindex!=6 && yindex!=0 && yindex!=7 && yindex!=1 && yindex!=6 && (((CMCheckersBoard[xindex+1][yindex-1]==RED_PAWN||CMCheckersBoard[xindex+1][yindex-1]==RED_KING) && CMCheckersBoard[xindex+2][yindex-2]==NO_PIECE)||((CMCheckersBoard[xindex+1][yindex+1]==RED_PAWN||CMCheckersBoard[xindex+1][yindex+1]==RED_KING) && CMCheckersBoard[xindex+2][yindex+2]==NO_PIECE)||((CMCheckersBoard[xindex-1][yindex+1]==RED_PAWN||CMCheckersBoard[xindex-1][yindex+1]==RED_KING) && CMCheckersBoard[xindex-2][yindex+2]==NO_PIECE)||((CMCheckersBoard[xindex-1][yindex-1]==RED_PAWN||CMCheckersBoard[xindex-1][yindex-1]==RED_KING) && CMCheckersBoard[xindex-2][yindex-2]==NO_PIECE)))
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}
	else if (player==REDPLAYER)
	{
		if (CMCheckersBoard[xindex][yindex]==RED_PAWN)
		{
			if (xindex==1 || xindex==0)
			{
				return false;
			}
			else if ((yindex==0 || yindex==1) && (CMCheckersBoard[xindex-1][yindex+1]==WHITE_PAWN||CMCheckersBoard[xindex-1][yindex+1]==WHITE_KING) && CMCheckersBoard[xindex-2][yindex+2]==NO_PIECE)
			{
				return true;
			}
			else if ((yindex==7 || yindex==6) && (CMCheckersBoard[xindex-1][yindex-1]==WHITE_PAWN||CMCheckersBoard[xindex-1][yindex-1]==WHITE_KING) && CMCheckersBoard[xindex-2][yindex-2]==NO_PIECE)
			{
				return true;
			}
			else if ((((CMCheckersBoard[xindex-1][yindex+1]==WHITE_PAWN||CMCheckersBoard[xindex-1][yindex+1]==WHITE_KING)&& (CMCheckersBoard[xindex-2][yindex+2]==NO_PIECE))||((CMCheckersBoard[xindex-1][yindex-1]==WHITE_PAWN||CMCheckersBoard[xindex-1][yindex-1]==WHITE_KING)&& CMCheckersBoard[xindex-2][yindex-2]==NO_PIECE))&&yindex!=0 && yindex!=7 && yindex!=6 && yindex!=1)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else if (CMCheckersBoard[xindex][yindex]==RED_KING)
		{
			if ((yindex==0 && (CMCheckersBoard[xindex+1][yindex+1]==WHITE_PAWN||CMCheckersBoard[xindex+1][yindex+1]==WHITE_KING) && CMCheckersBoard[xindex+2][yindex+2]==NO_PIECE && xindex!=6 && xindex!=7)||(yindex==0 && (CMCheckersBoard[xindex-1][yindex+1]==WHITE_PAWN||CMCheckersBoard[xindex-1][yindex+1]==WHITE_KING) && CMCheckersBoard[xindex-2][yindex+2]==NO_PIECE&&yindex!=1&&yindex!=0))
			{
				return true;
			}
			else if ((yindex==7 && (CMCheckersBoard[xindex+1][yindex-1]==WHITE_PAWN||CMCheckersBoard[xindex+1][yindex-1]==WHITE_KING) && CMCheckersBoard[xindex+2][yindex-2]==NO_PIECE && xindex!=6 && xindex!=7)||(yindex==7 && (CMCheckersBoard[xindex-1][yindex-1]==WHITE_PAWN||CMCheckersBoard[xindex-1][yindex-1]==WHITE_KING) && CMCheckersBoard[xindex-2][yindex-2]==NO_PIECE&&yindex!=1&&yindex!=0))
			{
				return true;
			}
			else if (((CMCheckersBoard[xindex+1][yindex-1]==WHITE_PAWN||CMCheckersBoard[xindex+1][yindex-1]==WHITE_KING)&& (CMCheckersBoard[xindex+2][yindex-2]==NO_PIECE)&&xindex!=6&&xindex!=7&&yindex!=1)||((CMCheckersBoard[xindex+1][yindex+1]==WHITE_PAWN||CMCheckersBoard[xindex+1][yindex+1]==WHITE_KING)&& CMCheckersBoard[xindex+2][yindex+2]==NO_PIECE&&xindex!=6&&xindex!=7&&yindex!=6)||((CMCheckersBoard[xindex-1][yindex-1]==WHITE_PAWN||CMCheckersBoard[xindex-1][yindex-1]==WHITE_KING)&& (CMCheckersBoard[xindex-2][yindex-2]==NO_PIECE)&&xindex!=0&&xindex!=1&&yindex!=1)||((CMCheckersBoard[xindex-1][yindex+1]==WHITE_PAWN||CMCheckersBoard[xindex-1][yindex+1]==WHITE_KING)&& (CMCheckersBoard[xindex-2][yindex+2]==NO_PIECE)&&xindex!=1&&xindex!=0&&yindex!=6)&&yindex!=7&&yindex!=0)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}
}
bool CheckSelectedPiece(int CMCheckersBoard[ELEMENTS][ELEMENTS], int player, int xLocArray[MAX_PIECES], int yLocArray[MAX_PIECES], int xJumpArray[MAX_PIECES], int yJumpArray[MAX_PIECES])
{
	int xPosition=0;
	int yPosition=0;
	int i=0;
	int k=0;
	canMove=false;
	canJump=false;

	cout<<endl<<"Please select a piece to move: ";
	while((!(cin>>squareNumber))||(squareNumber<0)||(squareNumber>63))
	{
			if (squareNumber<0 || squareNumber>63)
			{
				cerr<<endl<<"You selected a square outside the board. Select a different piece.";
				return false;
			}
			else
			{
				cerr<<endl<<"You did not enter an integer.";
				return false;
			}
	}
	xPosition= squareNumber/ELEMENTS;
	yPosition= squareNumber%ELEMENTS;
	if (player==WHITEPLAYER)
	{
		if (CMCheckersBoard[xPosition][yPosition]==NO_PIECE||CMCheckersBoard[xPosition][yPosition]==3||CMCheckersBoard[xPosition][yPosition]==4)
		{
			cerr<<endl<<"You have selected either a blank space or an opponent's piece.";
			return false;
		}
	}
	if (player==REDPLAYER)
	{
		if (CMCheckersBoard[xPosition][yPosition]==NO_PIECE||CMCheckersBoard[xPosition][yPosition]==1||CMCheckersBoard[xPosition][yPosition]==2)
		{
			cerr<<endl<<"You have selected either a blank space or an opponent's piece.";
			return false;
		}
	}
	while (i<=MAX_PIECES)
	{
		if (xLocArray[i]==-1)
		{
			break;
		}
		else if (xPosition==xLocArray[i] && yPosition==yLocArray[i])
		{
			canMove=true;
			break;
		}
		i++;
	}
	while (k<=MAX_PIECES)
	{
		if (xJumpArray[k]==-1)
		{
			break;
		}
		else if (xPosition==xJumpArray[k] && yPosition==yJumpArray[k])
		{
			canJump=true;
			break;
		}
		k++;
	}
	if (canMove && !canJump && numJumps!=0 )
	{
		cerr<<endl<<"You have selected a piece that can't jump when another piece can. Please select a different piece that can jump.";
		return false;
	}
	else if (!canMove && !canJump)
	{
		cerr<<endl<<"You have selected a piece that can't move. Please select a different piece.";
		return false;
	}
	else
	{
		return true;
	}
}
bool CheckEndSpot(int CMCheckersBoard[ELEMENTS][ELEMENTS], int player, int xLocArray[MAX_PIECES], int yLocArray[MAX_PIECES], int xJumpArray[MAX_PIECES], int yJumpArray[MAX_PIECES])
{
	int xPositionFrom=0;
	int yPositionFrom=0;
	int xPositionTo=0;
	int yPositionTo=0;
	int i=0;
	int k=0;

	xPositionFrom= squareNumber/ELEMENTS;
	yPositionFrom= squareNumber%ELEMENTS;
	cout<<endl<<"Please select a space to move to: ";
	while((!(cin>>endSquareNumber))||(endSquareNumber<0)||(endSquareNumber>63)||(!(CMCheckersBoard[endSquareNumber/ELEMENTS][endSquareNumber%ELEMENTS]==NO_PIECE)))
	{
			if (endSquareNumber<0 || endSquareNumber>63)
			{
				cerr<<endl<<"You selected a square outside the board. Select a different space to move to after you reselect a piece to move.";
				return false;
			}
			else if (!(CMCheckersBoard[endSquareNumber/ELEMENTS][endSquareNumber%ELEMENTS]==NO_PIECE))
			{
				cerr<<endl<<"You selected a square that is currently occupied. Select a different space to move to after you reselect a piece to move.";
				return false;
			}
			else
			{
				cerr<<endl<<"You did not enter an integer. Select a different space to move to after you reselect a piece to move.";
				return false;
			}
	}
	xPositionTo= endSquareNumber/ELEMENTS;
	yPositionTo= endSquareNumber%ELEMENTS;
	if (canJump==true)
	{
		if (player==WHITEPLAYER)
		{
			if (CMCheckersBoard[xPositionFrom][yPositionFrom]==WHITE_PAWN)
			{
				if (yPositionTo==yPositionFrom-2 && xPositionTo==xPositionFrom+2 && CMCheckersBoard[xPositionFrom+1][yPositionFrom-1]==3 || CMCheckersBoard[xPositionFrom+1][yPositionFrom-1]==4)
				{
					CMCheckersBoard[xPositionFrom+1][yPositionFrom-1]=NO_PIECE;
					return true;
				}
				else if (yPositionTo==yPositionFrom+2 && xPositionTo==xPositionFrom+2 && CMCheckersBoard[xPositionFrom+1][yPositionFrom+1]==3 || CMCheckersBoard[xPositionFrom+1][yPositionFrom+1]==4)
				{
					CMCheckersBoard[xPositionFrom+1][yPositionFrom+1]=NO_PIECE;
					return true;
				}
				else
				{
					cerr<<endl<<"The selected piece can jump, but you have selected an illegal space to move to. Please reselect a piece to move.";
					return false;
				}
			}
			if (CMCheckersBoard[xPositionFrom][yPositionFrom]==WHITE_KING)
			{
				if (yPositionTo==yPositionFrom+2 && xPositionTo==xPositionFrom-2 && CMCheckersBoard[xPositionFrom-1][yPositionFrom+1]==3 || CMCheckersBoard[xPositionFrom-1][yPositionFrom+1]==4)
				{
					CMCheckersBoard[xPositionFrom-1][yPositionFrom+1]=NO_PIECE;
					return true;
				}
				else if (yPositionTo==yPositionFrom+2 && xPositionTo==xPositionFrom+2 && CMCheckersBoard[xPositionFrom+1][yPositionFrom+1]==3 || CMCheckersBoard[xPositionFrom+1][yPositionFrom+1]==4)
				{
					CMCheckersBoard[xPositionFrom+1][yPositionFrom+1]=NO_PIECE;
					return true;
				}
				else if (yPositionTo==yPositionFrom-2 && xPositionTo==xPositionFrom-2 && CMCheckersBoard[xPositionFrom-1][yPositionFrom-1]==3 || CMCheckersBoard[xPositionFrom-1][yPositionFrom-1]==4)
				{
					CMCheckersBoard[xPositionFrom-1][yPositionFrom-1]=NO_PIECE;
					return true;
				}
				else if (yPositionTo==yPositionFrom-2 && xPositionTo==xPositionFrom+2 && CMCheckersBoard[xPositionFrom+1][yPositionFrom-1]==3 || CMCheckersBoard[xPositionFrom+1][yPositionFrom-1]==4)
				{
					CMCheckersBoard[xPositionFrom+1][yPositionFrom-1]=NO_PIECE;
					return true;
				}
				else
				{
					cerr<<endl<<"The selected piece can jump, but you have selected an illegal space to move to. Please reselect a piece to move.";
					return false;
				}
			}
		}
		else if (player==REDPLAYER)
		{
			if (CMCheckersBoard[xPositionFrom][yPositionFrom]==RED_PAWN)
			{
				if (yPositionTo==yPositionFrom-2 && xPositionTo==xPositionFrom-2 && CMCheckersBoard[xPositionFrom-1][yPositionFrom-1]==1 || CMCheckersBoard[xPositionFrom-1][yPositionFrom-1]==2)
				{
					CMCheckersBoard[xPositionFrom-1][yPositionFrom-1]=NO_PIECE;
					return true;
				}
				else if (yPositionTo==yPositionFrom+2 && xPositionTo==xPositionFrom-2 && CMCheckersBoard[xPositionFrom-1][yPositionFrom+1]==1 || CMCheckersBoard[xPositionFrom-1][yPositionFrom+1]==2)
				{
					CMCheckersBoard[xPositionFrom-1][yPositionFrom+1]=NO_PIECE;
					return true;
				}
				else
				{
					cerr<<endl<<"The selected piece can jump, but you have selected an illegal space to move to. Please reselect a piece to move.";
					return false;
				}
			}
			if (CMCheckersBoard[xPositionFrom][yPositionFrom]==RED_KING)
			{
				if (yPositionTo==yPositionFrom+2 && xPositionTo==xPositionFrom-2 && CMCheckersBoard[xPositionFrom-1][yPositionFrom+1]==1 || CMCheckersBoard[xPositionFrom-1][yPositionFrom+1]==2)
				{
					CMCheckersBoard[xPositionFrom-1][yPositionFrom+1]=NO_PIECE;
					return true;
				}
				else if (yPositionTo==yPositionFrom+2 && xPositionTo==xPositionFrom+2 && CMCheckersBoard[xPositionFrom+1][yPositionFrom+1]==1 || CMCheckersBoard[xPositionFrom+1][yPositionFrom+1]==2)
				{
					CMCheckersBoard[xPositionFrom+1][yPositionFrom+1]=NO_PIECE;
					return true;
				}
				else if (yPositionTo==yPositionFrom-2 && xPositionTo==xPositionFrom-2 && CMCheckersBoard[xPositionFrom-1][yPositionFrom-1]==1 || CMCheckersBoard[xPositionFrom-1][yPositionFrom-1]==2)
				{
					CMCheckersBoard[xPositionFrom-1][yPositionFrom-1]=NO_PIECE;
					return true;
				}
				else if (yPositionTo==yPositionFrom-2 && xPositionTo==xPositionFrom+2 && CMCheckersBoard[xPositionFrom+1][yPositionFrom-1]==1 || CMCheckersBoard[xPositionFrom+1][yPositionFrom-1]==2)
				{
					CMCheckersBoard[xPositionFrom+1][yPositionFrom-1]=NO_PIECE;
					return true;
				}
				else
				{
					cerr<<endl<<"The selected piece can jump, but you have selected an illegal space to move to. Please reselect a piece to move.";
					return false;
				}
			}
		}
	}
	if (canMove==true && canJump==false)
	{
		if (player==WHITEPLAYER)
		{
			if (CMCheckersBoard[xPositionFrom][yPositionFrom]==WHITE_PAWN)
			{
				if (yPositionTo==yPositionFrom-1 && xPositionTo==xPositionFrom+1 && CMCheckersBoard[xPositionFrom+1][yPositionFrom-1]==NO_PIECE)
				{
					return true;
				}
				else if (yPositionTo==yPositionFrom+1 && xPositionTo==xPositionFrom+1 && CMCheckersBoard[xPositionFrom+1][yPositionFrom+1]==NO_PIECE)
				{
					return true;
				}
				else
				{
					cerr<<endl<<"The selected piece can move, but you have selected an illegal space to move to. Please reselect a piece to move.";
					return false;
				}
			}
			if (CMCheckersBoard[xPositionFrom][yPositionFrom]==WHITE_KING)
			{
				if (yPositionTo==yPositionFrom-1 && xPositionTo==xPositionFrom+1 && CMCheckersBoard[xPositionFrom+1][yPositionFrom-1]==NO_PIECE)
				{
					return true;
				}
				else if (yPositionTo==yPositionFrom+1 && xPositionTo==xPositionFrom+1 && CMCheckersBoard[xPositionFrom+1][yPositionFrom+1]==NO_PIECE)
				{
					return true;
				}
				else if (yPositionTo==yPositionFrom+1 && xPositionTo==xPositionFrom-1 && CMCheckersBoard[xPositionFrom-1][yPositionFrom+1]==NO_PIECE)
				{
					return true;
				}
				else if (yPositionTo==yPositionFrom-1 && xPositionTo==xPositionFrom-1 && CMCheckersBoard[xPositionFrom-1][yPositionFrom-1]==NO_PIECE)
				{
					return true;
				}
				else
				{
					cerr<<endl<<"The selected piece can move, but you have selected an illegal space to move to. Please reselect a piece to move.";
					return false;
				}
			}
		}
		else if (player==REDPLAYER)
		{
			if (CMCheckersBoard[xPositionFrom][yPositionFrom]==RED_PAWN)
			{
				if (yPositionTo==yPositionFrom-1 && xPositionTo==xPositionFrom-1 && CMCheckersBoard[xPositionFrom-1][yPositionFrom-1]==NO_PIECE)
				{
					return true;
				}
				else if (yPositionTo==yPositionFrom+1 && xPositionTo==xPositionFrom-1 && CMCheckersBoard[xPositionFrom-1][yPositionFrom+1]==NO_PIECE)
				{
					return true;
				}
				else
				{
					cerr<<endl<<"The selected piece can move, but you have selected an illegal space to move to. Please reselect a piece to move.";
					return false;
				}
			}
			if (CMCheckersBoard[xPositionFrom][yPositionFrom]==RED_KING)
			{
				if (yPositionTo==yPositionFrom-1 && xPositionTo==xPositionFrom+1 && CMCheckersBoard[xPositionFrom+1][yPositionFrom-1]==NO_PIECE)
				{
					return true;
				}
				else if (yPositionTo==yPositionFrom+1 && xPositionTo==xPositionFrom+1 && CMCheckersBoard[xPositionFrom+1][yPositionFrom+1]==NO_PIECE)
				{
					return true;
				}
				else if (yPositionTo==yPositionFrom+1 && xPositionTo==xPositionFrom-1 && CMCheckersBoard[xPositionFrom-1][yPositionFrom+1]==NO_PIECE)
				{
					return true;
				}
				else if (yPositionTo==yPositionFrom-1 && xPositionTo==xPositionFrom-1 && CMCheckersBoard[xPositionFrom-1][yPositionFrom-1]==NO_PIECE)
				{
					return true;
				}
				else
				{
					cerr<<endl<<"The selected piece can move, but you have selected an illegal space to move to. Please reselect a piece to move.";
					return false;
				}
			}
		}
	}
}
void MakeMove(int CMCheckersBoard[ELEMENTS][ELEMENTS])
{
	int xPositionFrom= 0;
	int yPositionFrom= 0;
	int xPositionTo= 0;
	int yPositionTo= 0;

	xPositionFrom= squareNumber/ELEMENTS;
	yPositionFrom= squareNumber%ELEMENTS;
	xPositionTo= endSquareNumber/ELEMENTS;
	yPositionTo= endSquareNumber%ELEMENTS;
	CMCheckersBoard[xPositionTo][yPositionTo]= CMCheckersBoard[xPositionFrom][yPositionFrom];
	CMCheckersBoard[xPositionFrom][yPositionFrom]=NO_PIECE;
}
bool CheckWin(int CMCheckersBoard[ELEMENTS][ELEMENTS], int xLocArray[MAX_PIECES], int yLocArray[MAX_PIECES])
{
	if (player==REDPLAYER)
		{
			player=WHITEPLAYER;
		}
	else
		{
			player=REDPLAYER;
		}
	numMoves=CountMoveSquares(checkerBoard, player, xArray, yArray);
	numJumps=CountJumpSquares(checkerBoard, player, xJumpArray, yJumpArray);
	if (numMoves==0 && numJumps==0)
	{
		DisplayBoard(CMCheckersBoard);
		if (player==REDPLAYER)
		{
			cout<<endl<<"White Player wins! Congratulations!";
		}
		else
		{
			cout<<endl<<"Red Player wins! Congratulations!";
		}
		return true;
	}
	else
	{
		return false;
	}
}
void DisplayMoves(int CMCheckersBoard[ELEMENTS][ELEMENTS], int xLocArray[MAX_PIECES], int yLocArray[MAX_PIECES], int xJumpArray[MAX_PIECES], int yJumpArray[MAX_PIECES])
{
	int i=0;
	int availableSquare=0;

	cout<<endl<<"Pieces in these squares can move: ";
	for (i=0;i<MAX_PIECES;i++)
	{
		if (xLocArray[i]==-1 || yLocArray[i]==-1)
		{
			break;
		}
		else
		{
			availableSquare=(ELEMENTS*xLocArray[i]+yLocArray[i]);
			cout<<availableSquare<<" ";
		}
	}
	i=0;
	cout<<endl<<"Pieces in these squares can jump: ";
	for (i=0;i<MAX_PIECES;i++)
	{
		if (xJumpArray[i]==-1 || yJumpArray[i]==-1)
		{
			break;
		}
		else
		{
			availableSquare=(ELEMENTS*xJumpArray[i]+yJumpArray[i]);
			cout<<availableSquare<<" ";
		}
	}
}
void ChangePawntoKing(int CMCheckersBoard[ELEMENTS][ELEMENTS])
{
	int i=0;
	for (i=0;i<ELEMENTS;i++)
	{
		if (CMCheckersBoard[0][i]==RED_PAWN)
		{
			CMCheckersBoard[0][i]=RED_KING;
		}
		if (CMCheckersBoard[7][i]==WHITE_PAWN)
		{
			CMCheckersBoard[7][i]=WHITE_KING;
		}
	}
}
