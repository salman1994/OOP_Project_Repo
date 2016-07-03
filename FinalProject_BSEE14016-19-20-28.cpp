#include <iostream>		//input or output functions
#include <string.h>		//string functions
#include <stdlib.h>     //alpha to integer

using namespace std;

class pieces
{
	private:
		char symbol;
		int colour;
		
	public:
		pieces();
		pieces(int, char); //overloaded constructor
		int get_colour();
		char get_symbol();
		void move(pieces * board[][8], int oldrow, int oldcolm, int newrow, int newcolm, int colour);
		virtual bool ifpossible(pieces * board[][8], int oldrow, int oldcolm, int newrow, int newcolm, int colour) = 0;
};

class pawn :public pieces
{
public:
	pawn(int, char);
	bool ifpossible(pieces * board[][8], int oldrow, int oldcolm, int newrow, int newcolm, int colour);
};

class rook :public pieces
{
public:
	rook(int, char);
	bool ifpossible(pieces * board[][8], int oldrow, int oldcolm, int newrow, int newcolm, int colour);
};

class knight :public pieces
{
public:
	knight(int, char);
	bool ifpossible(pieces * board[][8], int oldrow, int oldcolm, int newrow, int newcolm, int colour);
};

class bishop :public pieces
{
public:
	bishop(int, char);
	bool ifpossible(pieces * board[][8], int oldrow, int oldcolm, int newrow, int newcolm, int colour);
};

class queen :public pieces
{
public:
	queen(int, char);
	bool ifpossible(pieces * board[][8], int oldrow, int oldcolm, int newrow, int newcolm, int colour);
};

class king :public pieces
{
public:
	king(int, char);
	bool ifpossible(pieces * board[][8], int oldrow, int oldcolm, int newrow, int newcolm, int colour);
};

//NON-MEMBER FUNCTIONS

int determine_row(char row_ch);
void print2(pieces*);
void input_getter(char *, int&, int&, int&, int&, int&);
bool r_c_checker(int, int, int, int);

pieces::pieces(){}

pieces::pieces(int c, char s)
{
	colour = c;
	symbol = s;
}

int pieces::get_colour()
{
	return colour;
}

char pieces::get_symbol()
{
	return symbol;
}

void pieces::move(pieces * board[][8], int oldrow, int oldcolm, int newrow, int newcolm, int colour)
{
	swap(board[oldrow][oldcolm], board[newrow][newcolm]);
	board[oldrow][oldcolm] = NULL;
}


pawn::pawn(int c, char s) :pieces(c, s){}

bool pawn::ifpossible(pieces * board[][8], int oldrow, int oldcolm, int newrow, int newcolm, int colour)
{
	int flag = 0;
	if (((colour == 2) && (oldrow == 6) && (((oldrow - newrow == 1) || (oldrow - newrow == 2)))) || ((colour == 1) && (oldrow == 1) && (((newrow - oldrow == 1) || (newrow - oldrow == 2)))) || ((colour == 1) && (newrow - oldrow == 1)) || ((colour == 2) && (oldrow - newrow == 1)))
	{
		if ((newcolm == oldcolm) && (board[newrow][newcolm] == NULL))	//move
		{
			flag = 1;
		}
		else if (((newcolm - oldcolm == 1) || (oldcolm - newcolm == 1)) && (board[newrow][newcolm] != NULL))	//attack
		{
			flag = 1;
		}
	}

	if (flag == 0)
		return false;
	else
		return true;
}


rook::rook(int c, char s) :pieces(c, s){}

bool rook::ifpossible(pieces * board[][8], int oldrow, int oldcolm, int newrow, int newcolm, int colour)
{
	int flag = 1;
	if (newcolm == oldcolm)
	{
		if ((oldrow - newrow)>0)
		{
			for (int i = oldrow - 1; i>newrow; i--)
			{
				if (board[i][oldcolm] != NULL)
					flag = 0;
			}
		}
		if ((newrow - oldrow)>0)
		{
			for (int i = oldrow + 1; i<newrow; i++)
			{
				if (board[i][oldcolm] != NULL)
					flag = 0;
			}
		}
	}
	else if (newrow == oldrow)
	{
		if ((oldcolm - newcolm)>0)
		{
			for (int i = oldcolm - 1; i>newcolm; i--)
			{
				if (board[oldrow][i] != NULL)
					flag = 0;
			}
		}
		if ((newrow - oldrow)>0)
		{
			for (int i = oldcolm + 1; i<newcolm; i++)
			{
				if (board[oldrow][i] != NULL)
					flag = 0;
			}
		}
	}
	else
		flag = 0;
	if (flag == 1)
		return true;
	else
		return false;
}


knight::knight(int c, char s) :pieces(c, s){}

bool knight::ifpossible(pieces * board[][8], int oldrow, int oldcolm, int newrow, int newcolm, int colour)
{
	int p1 = 0, p2 = 0, flag = 0;

	if (board[newrow][newcolm] != NULL)
	{
		p1 = board[oldrow][oldcolm]->get_colour();
		p2 = board[newrow][newcolm]->get_colour();
		flag = 1;
	}
	if ((oldcolm == newcolm + 1) || (oldcolm == newcolm - 1))
	{
		if ((oldrow == newrow + 2) || (oldrow == newrow - 2))
		{
			if (p1 != p2 && flag == 1)
				board[newrow][newcolm] = NULL;
			return true;
		}
	}
	if ((oldcolm == newcolm + 2) || (oldcolm == newcolm - 2))
	{
		if ((oldrow == newrow + 1) || (oldrow == newrow - 1))
		{
			if (p1 != p2 && flag == 1)
				board[newrow][newcolm] = NULL;
			return true;
		}
	}
	return false;
}


class chess
{
private:
	pieces* board[8][8];
	
public:
	chess();
	chess(pawn &P1, pawn &P2, pawn &P3, pawn &P4, pawn &P5, pawn &P6, pawn &P7, pawn &P8, rook &R1, rook &R2, knight &KN1, knight &KN2, bishop &B1, bishop &B2, queen &Q, king &K, pawn &p1, pawn &p2, pawn &p3, pawn &p4, pawn &p5, pawn &p6, pawn &p7, pawn &p8, rook &r1, rook &r2, knight &kn1, knight &kn2, bishop &b1, bishop &b2, queen &q, king &k);

	void print();
	void game();
};

chess::chess(){}

chess::chess(pawn &P1, pawn &P2, pawn &P3, pawn &P4, pawn &P5, pawn &P6, pawn &P7, pawn &P8, rook &R1, rook &R2, knight &KN1, knight &KN2, bishop &B1, bishop &B2, queen &Q, king &K, pawn &p1, pawn &p2, pawn &p3, pawn &p4, pawn &p5, pawn &p6, pawn &p7, pawn &p8, rook &r1, rook &r2, knight &kn1, knight &kn2, bishop &b1, bishop &b2, queen &q, king &k)
{
	for (int i = 2; i<6; i++)
	{
		for (int j = 0; j<8; j++)
		{
			board[i][j] = NULL;
		}
	}
	
//Player 1 Pieces
	board[0][0] = &R1; board[0][1] = &R2; board[0][2] = &B1; board[0][3] = &B2; board[0][4] = &KN1; board[0][5] = &KN2; board[0][6] = &Q; board[0][7] = &K;
	board[1][0] = &P1; board[1][1] = &P2; board[1][2] = &P3; board[1][3] = &P4; board[1][4] = &P5; board[1][5] = &P6; board[1][6] = &P7; board[1][7] = &P8;

//Player 2 Pieces
	board[7][0] = &r1; board[7][1] = &r2; board[7][2] = &b1; board[7][3] = &b2; board[7][4] = &kn1; board[7][5] = &kn2; board[7][6] = &q; board[7][7] = &k;
	board[6][0] = &p1; board[6][1] = &p2; board[6][2] = &p3; board[6][3] = &p4; board[6][4] = &p5; board[6][5] = &p6; board[6][6] = &p7; board[6][7] = &p8;
}


void chess::print()
{	
	cout << "\nInput Format:	*******     b2,c2     *******\n\n";
	cout << "\t  b2:	Initial Place\n\t  c2:	Final Place\n\n";
	cout << "Player 1 has pieces marked with Upper-Cased letters.\nPlayer 2 has pieces marked with Lower-Cased letters.\n\n";
	cout << endl;

	cout << "      1"; cout << "     2"; cout << "     3"; cout << "     4"; cout << "     5"; cout << "     6"; cout << "     7"; cout << "     8"; cout << "   " << endl;
	cout << "   *************************************************" << endl;
	cout << "   *     |     |     |     |     |     |     |     *" << endl;
	cout << " a *  "; print2(board[0][0]); cout << "  |  "; print2(board[0][1]); cout << "  |  "; print2(board[0][2]); cout << "  |  "; print2(board[0][3]); cout << "  |  "; print2(board[0][4]); cout << "  |  "; print2(board[0][5]); cout << "  |  "; print2(board[0][6]); cout << "  |  "; print2(board[0][7]); cout << "  *" << endl;
	cout << "   *     |     |     |     |     |     |     |     *" << endl;
	cout << "   *************************************************\t"; cout <<"Player 1" << endl;
	cout << "   *     |     |     |     |     |     |     |     *" << endl;
	cout << " b *  "; print2(board[1][0]);	cout << "  |  "; print2(board[1][1]); cout << "  |  "; print2(board[1][2]); cout << "  |  "; print2(board[1][3]); cout << "  |  "; print2(board[1][4]); cout << "  |  "; print2(board[1][5]); cout << "  |  "; print2(board[1][6]); cout << "  |  "; print2(board[1][7]); cout << "  *" << endl;
	cout << "   *     |     |     |     |     |     |     |     *" << endl;
	cout << "   *************************************************" << endl;
	cout << "   *     |     |     |     |     |     |     |     *" << endl;
	cout << " c *  "; print2(board[2][0]); cout << "  |  "; print2(board[2][1]); cout << "  |  "; print2(board[2][2]); cout << "  |  "; print2(board[2][3]); cout << "  |  "; print2(board[2][4]); cout << "  |  "; print2(board[2][5]); cout << "  |  "; print2(board[2][6]); cout << "  |  "; print2(board[2][7]); cout << "  *" << endl;
	cout << "   *     |     |     |     |     |     |     |     *" << endl;
	cout << "   *************************************************" << endl;
	cout << "   *     |     |     |     |     |     |     |     *" << endl;
	cout << " d *  "; print2(board[3][0]); cout << "  |  "; print2(board[3][1]); cout << "  |  "; print2(board[3][2]); cout << "  |  "; print2(board[3][3]); cout << "  |  "; print2(board[3][4]); cout << "  |  "; print2(board[3][5]); cout << "  |  "; print2(board[3][6]); cout << "  |  "; print2(board[3][7]); cout << "  *" << endl;
	cout << "   *     |     |     |     |     |     |     |     *" << endl;
	cout << "   *************************************************" << endl;
	cout << "   *     |     |     |     |     |     |     |     *" << endl;
	cout << " e *  "; print2(board[4][0]); cout << "  |  "; print2(board[4][1]); cout << "  |  "; print2(board[4][2]); cout << "  |  "; print2(board[4][3]); cout << "  |  "; print2(board[4][4]); cout << "  |  "; print2(board[4][5]); cout << "  |  "; print2(board[4][6]); cout << "  |  "; print2(board[4][7]); cout << "  *" << endl;
	cout << "   *     |     |     |     |     |     |     |     *" << endl;
	cout << "   *************************************************" << endl;
	cout << "   *     |     |     |     |     |     |     |     *" << endl;
	cout << " f *  "; print2(board[5][0]); cout << "  |  "; print2(board[5][1]); cout << "  |  "; print2(board[5][2]); cout << "  |  "; print2(board[5][3]); cout << "  |  "; print2(board[5][4]); cout << "  |  "; print2(board[5][5]); cout << "  |  "; print2(board[5][6]); cout << "  |  "; print2(board[5][7]); cout << "  *" << endl;
	cout << "   *     |     |     |     |     |     |     |     *" << endl;
	cout << "   *************************************************" << endl;
	cout << "   *     |     |     |     |     |     |     |     *" << endl;
	cout << " g *  "; print2(board[6][0]); cout << "  |  "; print2(board[6][1]); cout << "  |  "; print2(board[6][2]); cout << "  |  "; print2(board[6][3]); cout << "  |  "; print2(board[6][4]); cout << "  |  "; print2(board[6][5]); cout << "  |  "; print2(board[6][6]); cout << "  |  "; print2(board[6][7]); cout << "  *" << endl;
	cout << "   *     |     |     |     |     |     |     |     *" << endl;
	cout << "   *************************************************\t"; cout << "Player 2" << endl;
	cout << "   *     |     |     |     |     |     |     |     *" << endl;
	cout << " h *  "; print2(board[7][0]); cout << "  |  "; print2(board[7][1]); cout << "  |  "; print2(board[7][2]); cout << "  |  "; print2(board[7][3]); cout << "  |  "; print2(board[7][4]); cout << "  |  "; print2(board[7][5]); cout << "  |  "; print2(board[7][6]); cout << "  |  "; print2(board[7][7]); cout << "  *" << endl;
	cout << "   *     |     |     |     |     |     |     |     *" << endl;
	cout << "   *************************************************" << endl;
}

void chess::game()
{

	pawn P1(1, 'P'), P2(1, 'P'), P3(1, 'P'), P4(1, 'P'), P5(1, 'P'), P6(1, 'P'), P7(1, 'P'), P8(1, 'P');
	rook R1(1, 'R'), R2(1, 'R');
	knight KN1(1, 'N'), KN2(1, 'N');
	bishop B1(1, 'B'), B2(1, 'B');
	queen Q(1, 'Q');
	king K(1, 'K');

	pawn p1(2, 'p'), p2(2, 'p'), p3(2, 'p'), p4(2, 'p'), p5(2, 'p'), p6(2, 'p'), p7(2, 'p'), p8(2, 'p');
	rook r1(2, 'r'), r2(2, 'r');
	knight kn1(2, 'n'), kn2(2, 'n');
	bishop b1(2, 'b'), b2(2, 'b');
	queen q(2, 'q');
	king k(2, 'k');

	char input[30];
	int oldrow, oldcolm, newrow, newcolm, inputcheck = 1;

	for (int i = 2; i<6; i++)
	{
		for (int j = 0; j<8; j++)
		{
			board[i][j] = NULL;
		}
	}

//Sorting the pieces
	board[0][0] = &R1; board[0][1] = &KN1; board[0][2] = &B1; board[0][3] = &K; board[0][4] = &Q; board[0][5] = &B2; board[0][6] = &KN2; board[0][7] = &R2;
	board[1][0] = &P1; board[1][1] = &P2; board[1][2] = &P3; board[1][3] = &P4; board[1][4] = &P5; board[1][5] = &P6; board[1][6] = &P7; board[1][7] = &P8;

	board[7][0] = &r1; board[7][1] = &kn1; board[7][2] = &b1; board[7][3] = &q; board[7][4] = &k; board[7][5] = &b2; board[7][6] = &kn2; board[7][7] = &r2;
	board[6][0] = &p1; board[6][1] = &p2; board[6][2] = &p3; board[6][3] = &p4; board[6][4] = &p5; board[6][5] = &p6; board[6][6] = &p7; board[6][7] = &p8;

	cout << "\n*********    W E L C O M E   T O   O O P   C H E S S    ********\n\n";
	cout << "Programmer 1:\tF A S E E H      T A U Q E E R\nStudent ID:\tB S E E 1 4 0 1 6\n\n";
	cout << "Programmer 2:\tS H A R O Z E     S O H A I L     A R C H E R\nStudent ID:\tB S E E 1 4 0 1 9\n\n";
	cout << "Programmer 2:\tA M M A R     Y O U N A S\nStudent ID:\tB S E E 1 4 0 2 0\n\n";
	cout << "Programmer 2:\tS A L M A N     A S I M     B A J W A\nStudent ID:\tB S E E 1 4 0 2 8\n\n";

	print();

	cout << endl;
	int num = 2, turn = 1;
	cout << "PLAYER " << turn << " MOVE: ";
	cin.getline(input, 29);
	
	while (strcmp(input, "end") != 0)
	{
		input_getter(input, oldrow, oldcolm, newrow, newcolm, inputcheck);
		
		if (inputcheck == 1)
		{
			if (board[oldrow][oldcolm] != NULL)               // CHECK WHETHER THE PIECE YOU WANT TO MOVE IS AT THE SPECIFIED PLACE
			{
				if (board[oldrow][oldcolm]->get_colour() == turn)  //CHECK WHETHER IT IS YOUR TURN OR NOT
				{
					if (r_c_checker(oldrow, oldcolm, newrow, newcolm))  //CHECK WHETHER YOUR MOVE IS WITHIN BOUND OF BOARD
					{
						if ((board[oldrow][oldcolm]->ifpossible(board, oldrow, oldcolm, newrow, newcolm, turn))) //CHECK WHETHER TOUR PIECE AT THE SPECIFIED LOCATION CAN HAVE THIS MOVE
						{
							board[oldrow][oldcolm]->move(board, oldrow, oldcolm, newrow, newcolm, turn);
							num++;
							cout << endl << endl;
							system("cls");
							print();
						}
						else
							cout << "Move not Possible:\n";
					}
					else
					{
						cout << "oldRow : " << oldrow << endl;
						cout << "newRow : " << newrow << endl;
						cout << "oldCol : " << oldcolm << endl;
						cout << "newCol : " << newcolm << endl;
						cout<< (r_c_checker(oldrow, oldcolm, newrow, newcolm));
						cout << "Out of bound of Board:  Yes";
					}
				}
				else
					cout << "You cannot access pieces of other Player\n" << endl;
			}
			else
				cout << "No Piece at that Place\n";
		}
		else
			cout << "INVALID INPUT\n";
			
		cout << endl;
		turn = (num % 2) + 1;
		cout << "PLAYER " << turn << " MOVE: ";	
		cin.getline(input, 29);
	}
}

//NON-MEMBER FUNCTIONS IMPLEMENTATION

int determine_row(char row_ch)
{
	if (row_ch == 'a')
		return 1;

	if (row_ch == 'b')
		return 2;

	if (row_ch == 'c')
		return 3;
		
	if (row_ch == 'd')
		return 4;

	if (row_ch == 'e')
		return 5;

	if (row_ch == 'f')
		return 6;

	if (row_ch == 'g')
		return 7;

	if (row_ch == 'h')
		return 8;
		
	else
		return 0;
}

bool r_c_checker(int oldrow, int oldcolm, int newrow, int newcolm)
{
	if ((oldrow <= 7 && oldrow >= 0) && (oldcolm <= 7 && oldcolm >= 0) && (newrow <= 7 && newrow >= 0) && (newcolm <= 7 && newcolm >= 0))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void print2(pieces * ptr)
{
	if (ptr == NULL)
		cout << " ";

	else
		cout << ptr->get_symbol();
}

void input_getter(char input[], int & fromrow, int& fromcolm, int & torow, int& tocolm, int& check)
{
	check = 1;
	int a = (strlen(input));

	if (strlen(input) != 5)
		check = 0;
		
	else
	{
		char r1, r2;
		char c1[1];
		char c2[1];
		c2[0] = input[4];
		tocolm = atoi(c2);	
		r1 = input[0];
		c1[0] = input[1];
		fromcolm = atoi(c1);
		r2 = input[3];
		fromrow = determine_row(r1);
		torow = determine_row(r2);
		fromrow--;
		fromcolm--;
		torow--;
		tocolm--;
	}
}

int main()
{	
	chess x;
	x.game();        //FUNCTION THAT RUNS THE GAME	
	cout << endl << endl;
}
