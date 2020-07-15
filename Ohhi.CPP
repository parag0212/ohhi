#include<process.h>
#include<graphics.h>
#include<fstream.h>
#include<stdlib.h>
#include<conio.h>
#include<stdio.h>
#include<dos.h>

union REGS in,out;

int callmouse()
{
	in.x.ax=1;
	int86(51,&in,&out);
	return 1;
}

void mouseposi(int &xpos,int &ypos,int &click)
{
	in.x.ax=3;
	int86(51,&in,&out);
	click=out.x.bx;
	xpos=out.x.cx;
	ypos=out.x.dx;
}

int mousehide()
{
	in.x.ax=2;
	int86(51,&in,&out);
	return 1;
}

void setposi(int &xpos, int&ypos)
{
	in.x.ax=4;
	in.x.cx=xpos;
	in.x.dx=ypos;
	int86(51,&in,&out);
}

class BOARD
{
	int A[6][6];
    public:
    BOARD();
    int board_fill(int);
    int check_row_cons(int);
    int check_column_cons(int);
    int equal_blocks_row(int);
    int check_same_row(int);
    int check_same_col(int);
    int check1D(int *,int *,int);
    void copy(int,int[],int);
    friend void change(int,int);
    void displayboard();
}B;

BOARD::BOARD()
{
	int B[6][6];
	fstream f("solution.txt",ios::in|ios::binary);
	f.seekp(random(5)*sizeof(B));
	randomize();
	f.read((char*)&B,sizeof(B));
	int i,j,c=0;
	for(i=0;i<6;i++)
	for(j=0;j<6;j++)
		A[i][j]=0;
	for(i=random(6),j=random(6);c<=20;i=random(6),j=random(6),c++)
		A[i][j]=B[i][j];   //randomly placing the tiles
	f.close();
}
int BOARD::check_same_col(int size)
{
	int i,j,p[6],q[6];
    for(i=0;i<size;i++)
    {
	for(j=i+1;j<size;j++)
	{
		copy(i,p,size);
		copy(j,q,size);
	    if(check1D(p,q,size))
	    return 0;
	}
    }
    return 1;
}
void BOARD::copy(int k,int p[],int size)
{
    for(int i=0;i<size;i++)
	p[i]=A[i][k];
}
int BOARD::check1D(int a[],int b[],int n)
{

	int i,c=0;
    for(i=0;i<n;i++)
    {
	if(a[i]==b[i]||a[i]==b[i]+2||a[i]==b[i]-2)
	c++;
	else
	return 0;
    }
    return 1;
}




int BOARD::board_fill(int size)
{
	int i,j;
	for(i=0;i<size;i++)
    {
	for(j=0;j<size;j++)
	{
		if(A[i][j]==0)  //condition for empty tile
	    return 0;
	}
    }
    return 1;
}

int BOARD::check_row_cons(int n)
{

	int c=0,i,j;
    for(i=0;i<n;i++)
    {
	c=0;
	for(j=0;j<n-1;j++)
	{
	//condition for same consecutive elements
	if(A[i][j]==A[i][j+1]||A[i][j]==A[i][j+1]+2||A[i][j]==A[i][j+1]-2)
	    c++;
	    else
	    c=0;
	}
	printf("%d\n",c);
	if(c>1)
	return 0;
    }
    return 1;
}

int BOARD::check_column_cons(int size)
{
	int i,j,c=0;
	for(j=0;j<size;j++)
	{
	c=0;
	for(i=0;i<size-1;i++)
	{
		//condition for same consecutive elements
	    if(A[i][j]==A[i+1][j]||A[i][j]==A[i+1][j]+2||A[i][j]==A[i+1][j]-2)
	    c++;
	    else
	    c=0;
	 }
     if(c>1)
     return 0;
   }
   return 1;
}

int BOARD::equal_blocks_row(int size)
{
  int i,j,r=0,b=0;
  for(i=0;i<size;i++)
  {
	for(j=0;j<size;j++)
	if(A[i][j]==1||A[i][j]==3)
		r++; //counting red
	else
		b++; //counting blue
  }
	if(r!=b)
    return 0;
    else
    return 1;
}
int BOARD::check_same_row(int size)
{
	int i,j;
    for(i=0;i<size;i++)
    {
	for(j=i+1;j<size;j++)
	{
		if(check1D(A[i],A[j],size))
	    return 0;
	}
    }
    return 1;
}

void BOARD::displayboard()
{
	int i,j,p,q;
	for(j=30,p=0; j<=400; j=j+65,p++)
	for(i=100,q=0; i<=450; i=i+65,q++)
	{	if(A[p][q]==0)
		{
		setfillstyle(SOLID_FILL,WHITE);
		}
		else if(B.A[p][q]==3)
		{
		setfillstyle(SOLID_FILL,RED);
		}
		else if(B.A[p][q]==4)
		{
		setfillstyle(SOLID_FILL,BLUE);
		}
			bar(i,j,i+55,j+55);
		  }
		settextstyle(3,HORIZ_DIR,3);
		setcolor(RED);
		outtextxy(590,1,"X");
}

void change(int x,int y)
{
	int p,q,j,i;
	for(j=30,p=0; j<=400; j=j+65,p++)
	for(i=100,q=0; i<=450; i=i+65,q++)
	if(x>=i && x<=i+55 && y>=j && y<=j+55)
	{
		if(B.A[p][q]==0)
		{
		setfillstyle(SOLID_FILL,RED);
		B.A[p][q]=1;
		bar(i,j,i+55,j+55);
		}
		else if(B.A[p][q]==1)
		{
		setfillstyle(SOLID_FILL,BLUE);
		B.A[p][q]=2;
		bar(i,j,i+55,j+55);
		}
		else if(B.A[p][q]==2)
		{
		setfillstyle(SOLID_FILL,WHITE);
		B.A[p][q]=0;
		bar(i,j,i+55,j+55);
		}
		else
		{
			setcolor(WHITE);
			settextstyle(3,HORIZ_DIR,4);
			outtextxy(getmaxx()-450,getmaxy()-50,"BLOCKED TILE");
			delay(500);
			setcolor(BLACK);
			outtextxy(getmaxx()-450,getmaxy()-50,"BLOCKED TILE");

		}
	}
	if(x>=590 && x<=620 && y>=1 && y<=20)
	exit(0);
}
void welcome()
{
	settextstyle(3,HORIZ_DIR,4);
	for(int i=1;i<=12;i++)
	{
		setbkcolor(i);
		outtextxy(getmaxx()/2-50,getmaxy()/2-50,"oh hi!");
		delay(500);
	}
}
void rules()
{
	setbkcolor(BLUE);
	settextstyle(1,HORIZ_DIR,5);
	outtextxy(165,1,"INSTRUCTIONS");
	settextstyle(3,HORIZ_DIR,3);
	outtextxy(100,100,"Three adjacent tiles of the same color");
	outtextxy(125,125,"in a row or column are not allowed.");
	outtextxy(70,170,"Rows and columns have an equal number of");
	outtextxy(250,195,"each color.");
	outtextxy(125,235,"No two rows and no two columns");
	outtextxy(230,255,"are the same.");
	outtextxy(150,335,"Click on a tile to turn it red");
	outtextxy(135,355,"Click twice to turn the tile blue.");
	setfillstyle(SOLID_FILL,BLUE);
	bar(400,420,250,460);
	setcolor(WHITE);
	settextstyle(3,HORIZ_DIR,5);
	outtextxy(270,415,"PLAY!");

}
void message()
{

	settextstyle(3,HORIZ_DIR,2);
	setcolor(WHITE);
	if(!B.check_row_cons(6))
		outtextxy(getmaxx()-600,getmaxy()-50,"3 tiles of same color aren't allowed next to each other");
	else if(!B.check_column_cons(6))
		outtextxy(getmaxx()-600,getmaxy()-50,"3 tiles of same color aren't allowed next to each other");
	else if(!B.equal_blocks_row(6))
		outtextxy(getmaxx()-600,getmaxy()-50,"Unequal number of tiles of each color");
	else if(!B.check_same_row(6))
		outtextxy(getmaxx()-600,getmaxy()-50,"No two rows are the same");
	else if(!B.check_same_col(6))
		outtextxy(getmaxx()-600,getmaxy()-50,"No two columns are the same");
	else
	{
		fstream f("comments.txt",ios::in|ios::binary);
		f.seekp((random(5))*20);
		char a[20];
		f.read((char*)&a,sizeof(a));
		settextstyle(3,HORIZ_DIR,4);
		outtextxy(getmaxx()-550,getmaxy()-50,a);
		delay(2000);
		f.close();
		exit(0);
	}
	delay(100);
}
void main()
{
	int gd=DETECT,gm;
	int x,y,cl;
	char ch;
	initgraph(&gd,&gm,"c:\\turboc3\\bgi");
	cleardevice();
	//welcome();
	cleardevice();
	setposi(0,0);
	callmouse();
	int c=1;
	do{
	rules();
	mouseposi(x,y,cl);
	if(cl==1)
	{
		if(x>=250 && x<=400 && y>=420 && y<=460)
		{ mousehide();      c--; }
	}
	}while(c);

	cleardevice();
	setbkcolor(BLACK);
	callmouse();
	setposi(0,0);
	rectangle(70,25,500,420);
	B.displayboard();
	do
	{
		callmouse();
		setcolor(BLACK);
		mouseposi(x,y,cl);
		gotoxy(2,3);
			printf("%d ",cl);
		if(cl==1)
		{
			mousehide();
			change(x,y);
			delay(250);
			setfillstyle(SOLID_FILL,BLACK);
			bar(getmaxx()-600,getmaxy()-50,getmaxx(),getmaxy());
		}
		settextstyle(3,HORIZ_DIR,4);

		if(B.board_fill(6))
		{
			setcolor(WHITE);
			message();
		}
	       //	mouseposi(x,y,cl);


	}while(cl!=2);
	getch();

	closegraph();
	getch();

}

