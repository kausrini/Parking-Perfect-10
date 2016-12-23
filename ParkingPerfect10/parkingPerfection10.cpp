#include<graphics.h>
#include<fstream.h>
#include<conio.h>
#include<alloc.h>
#include<dos.h>
#include<bios.h>
#include<process.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<iomanip.h>
void credits();

void	*p,*q,*r,*s,*t,*u,*v,*w;                               //THESE  WILL  BE  HOLDING  THE IMAGES  OF  THE TRUCK
int 	cx,cy,e;
struct 	detail
{

	int 	a,b,c,d;

}dr;

class mouse
{
		REGS regs;
		int no_buttons;
	public:
		mouse()
		{
			regs.x.ax=0;
			int86(0x33,&regs,&regs);
			if(regs.x.ax==0xfff)no_buttons=regs.x.bx;
		}
		void show_mouse()
		{
			regs.x.ax=0x01;
			int86(0x33,&regs,&regs);
		}
		void hide_mouse()
		{
			regs.x.ax=0x02;
			int86(0x33,&regs,&regs);
		}
		void get_status()
		{
			regs.x.ax=0x03;
			int86(0x33,&regs,&regs);
			while(e!=1)
			{
				regs.x.ax=0x03;
				int86(0x33,&regs,&regs);
				e=regs.x.bx;
				cx=regs.x.cx;
				cy=regs.x.dx;
			}
			e=0;

		}
};

void graphics()
{
	int	gdriver=DETECT,gmode=DETECT;
		initgraph(&gdriver,&gmode,"D:\\turboc2");
		cleardevice();
}

void instructions()
{
	void 	background();
		cleardevice();
	char 	na[395];
		ifstream f("D:\\park.txt",ios::in|ios::binary);
		f.read((char *)&na,sizeof(na));
		for(int i=0; i<395; i++)
		{
			cout<<na[i];
		}
		getch();
		cleardevice();
		background();


}

void loading()
{               cleardevice();

		setcolor(GREEN);
		settextstyle(10,0,9);
		outtextxy(20,100,"PARKING");
		putpixel(76,228,GREEN);
		putpixel(79,162,GREEN);
		putpixel(277,162,GREEN);
		putpixel(509,228,BLACK);
		putpixel(604,279,GREEN);
		putpixel(582,186,GREEN);
		putpixel(608,162,GREEN);
		putpixel(614,165,2);

		setcolor(RED);

		for(int k=279,flag=0,s,e;k>160;k-=3)
		{
			delay(650);
			flag=1;
			for(int i=0;i<640;++i)
			{
				if(getpixel(i+3,k)==GREEN)flag++;
				{
					if(flag%2!=0)s=i+2;
					 else if(flag!=0 && flag%2==0)
					      {
							e=i;
							line(s+3,k,e+3,k);
					       }
				 }
			 }
		}


}
class high
{
	public:
		int 	rank;
		char 	na[50];
		int 	score;
};



int search(high ob)
{
	high		t;
	ifstream 	f("D:\\turboc\\program\\highscores.doc",ios::binary);

			f.read((char *)&t,sizeof(t));
			while(!f.eof())
			{
				if(!strcmpi(t.na,ob.na))
				{
					f.close();
					return 1;
				}
				f.read((char *)&t,sizeof(t));
			}

			f.close();
			return 0;
}

void sort()
{
	high		ob[100];
	int		n=0;
	ifstream	f("D:\\turboc\\program\\highscores.doc",ios::binary);

			while(f.read((char *)&ob[n++],sizeof(high)));

			f.close();

			for(int i=1;i<n;++i)
			{
				high	temp=ob[i];
				for(int j=i-1;j>=0 && temp.rank<ob[j].rank;j--)
				{
					ob[j+1]=ob[j];
				}
				ob[j+1]=temp;
			}

	ofstream	g("D:\\turboc\\program\\highscores.doc",ios::binary);
			g.write((char *)&ob[0],(n-1)*sizeof(high));
}

int last_rank()
{
	ifstream	g("D:\\turboc\\program\\highscores.doc",ios::binary);
	high		ob;
	int		min;

			g.read((char *)&ob,sizeof(ob));

			min=ob.rank;

			while(!g.eof())
			{
				if(min<ob.rank) min=ob.rank;
				g.read((char *)&ob,sizeof(ob));
			}

			g.close();

			return min;
}


int rank_calc(const int score)
{
			      //	sort();   disp(); getch();

		fstream 	f("D:\\turboc\\program\\highscores.doc",ios::binary|ios::in|ios::out);
		high            t,ob,a[50];
		int		rank,record_no=0,flag=0,check=0;



				rank=last_rank();

				f.read((char *)&t,sizeof(t));

				while(!f.eof()&&!flag)
				{
					record_no++;

					if(score==t.score)
					{
						rank=t.rank;
						flag=1;
					}

					else if(score>t.score)
					{


						if(check == 0)
						{
							rank=t.rank;
							check = 1;
						}

						t.rank=t.rank+1;
						ob=t;
						f.seekp((record_no-1)*sizeof(t),ios::beg);
						f.write((char *)&ob,sizeof(ob));
					}

					f.read((char *)&t,sizeof(t));

				}

				f.close();
			return 	rank;

}
			/*
int rank_calc(const int score)
{
			      //	sort();   disp(); getch();

		fstream 	f("D:\\turboc\\program\\highscores.doc",ios::binary|ios::in|ios::out);
		high            t,ob,a[50];
		int		rank,record_no=0,flag=0,check=0,n=0,i=0;

				while(f.read((char *)&a[n++],sizeof(high)));


				rank=last_rank();

				f.read((char *)&t,sizeof(t));

				while(!f.eof()&&!flag)
				{
					if(score==t.score)
					{
						rank=t.rank;
						flag=1;
					}

					else if(score>t.score)
					{
						flag=1;
						rank=t.rank;

						for(;i<n;++i)
						{
							a[i].rank=a[i].rank+1;
						}

						f.write((char *)&a[0],(n-1)*sizeof(ob));

					}

					f.read((char *)&t,sizeof(t));
					i++;
				}

				f.close();
			return 	rank;

}                     */


void add(const int score)
{
		   //	cleardevice();
		     //	sort();
			settextstyle(4,0,0);
	fstream 	f;
			do
			{
				f.open("D:\\turboc\\program\\highscores.doc",ios::out|ios::in|ios::binary|ios::app|ios::nocreate);
				if(!f)
				{
						outtextxy(4,200,"Please copy the highscores file to the directory");
						outtextxy(105,250,"specified in the source code .");
						getch();
				}
				else
				{
					high		ob;
							cout<<"\nNAME  : ";
							gets(ob.na);
							strupr(ob.na);
							ob.score=score;
							ob.rank=rank_calc(score);

							if(search(ob))
							{
								do
								{
									cout<<"\nERROR! Name already exists";
									cout<<"\n\nNAME  : ";
									gets(ob.na);
									strupr(ob.na);

								}while(search(ob));
							}

							f.write((char *)&ob,sizeof(ob));

				}
			}while(!f);
			f.close();
}


void disp()
{
	cleardevice();
	ifstream	g("D:\\turboc\\program\\highscores.doc",ios::binary);
	high		ob;
			if(!g)
			{
				outtextxy(4,200,"Please copy the highscores file to the directory");
				outtextxy(105,250,"specified in the source code .");
				getch();
				cleardevice();
			}
			else
			{       cout<<"\n\t\t\t\tRANKING\n" ;
				g.read((char *)&ob,sizeof(ob));
				while(!g.eof())
				{
					cout<<"NAME  : "<<ob.na<<"\nSCORE : "<<ob.score<<"\nRANK  : "<<ob.rank<<"\n\n";
					g.read((char *)&ob,sizeof(ob));
				}
			}
			g.close();
			getch();
}

void modify(int score)
{
			cleardevice();
		high		t,ob;
		char            na[50];
		fstream 	f("D:\\turboc\\program\\highscores.doc",ios::in|ios::out|ios::binary);

				cout<<"\nENTER NAME : ";
				strupr(gets(na));
		int 		flag=1,record_no=0;

				f.read((char *)&t,sizeof(t));
				while(!f.eof()&&flag)
				{
					record_no++;
					if(!strcmpi(t.na,na))
					{
						flag=0;
						if(!(strcmpi(na,"KAUSHIK")==0||strcmpi(na,"KARTHIK")==0||strcmpi(na,"CHRIS")==0||strcmpi(na,"SHANKY")==0||strcmpi(na,"TP")==0))
						{
							if(score<=t.score)
							{
								 cout<<endl<<score<<"Not as good as your best score of "<<t.score<<" in your earlier attempt\n";
								 getch();
							}
							 else
							 {
								cout<<"\n\tExcellent,you have overhauled your best of "<<t.score<<" by parking "<<score;
								getch();
								t.score= score;
								t.rank = rank_calc(score);
								ob=t;
								f.seekp((record_no-1)*sizeof(t),ios::beg);
								f.write((char *)&ob,sizeof(ob));
							  }
						}
						else
						{
							cleardevice();
							settextstyle(4,0,0);
							outtextxy(15,210,"YOU CAN'T MODIFY THE CREATOR");outtextxy(117,260,"(DEVELOPER)");
							getch();
						}

					}
					f.read((char *)&t,sizeof(t));
				}
				f.close();
				sort();
				disp();
}



void highscores(int score)
{
	add(score);
	sort();
	disp();
}

void truck1()                            //normal
{
								  //MAIN  BODY
		setcolor(GREEN);
		setfillstyle(1,BROWN) ;
		rectangle(22,430,42,470);
		floodfill(35,450,GREEN);
		rectangle(25,425,39,430);
		setfillstyle(1,GREEN);
		floodfill(26,426,GREEN);

		setcolor(BLACK);                           //DESIGN
		for(int i=430;i<=475;i+=7)
		{
			line(22,i,42,i);
		}

		setcolor(WHITE);                           //EXHAUST
		for( i=37;i<=39;++i)
		{
			line(i,470,i,472);
		}

		setfillstyle(1,WHITE);                     //HEADLAMP
		sector(28,424,70,110,5,5);
		sector(36,424,70,110,5,5);

}

void truck2()                               //2nd quad diagonal     q
{
		truck1();
							  //MAIN  BODY
		setcolor(GREEN);
		setfillstyle(1,BROWN) ;

		int a[10] = {132,146,146,132,174,160,160,174,132,146};
		fillpoly(5,a);

		setcolor(BLACK);                           //DESIGN
		line(151,137,137,151);
		line(156,142,142,156);
		line(161,147,147,161);
		line(166,152,152,166);
		line(171,157,157,171);
		line(146,132,132,146);


		setcolor(WHITE);                           //EXHAUST
		int c[10] = {170,164,172,166,174,164,172,162,170,164};
		setfillstyle(1,WHITE);
		fillpoly(5,c);

		setfillstyle(1,WHITE);                     //HEADLAMP
		sector(133,139,110,150,5,6);
		sector(139,133,110,150,5,6);

		setcolor(BLACK);
		int b[10] = {134,144,144,134,140,130,130,140,134,144};
		setfillstyle(1,GREEN);
		fillpoly(5,b);

}

void truck3()                                    //left horizontal
{

							  //MAIN  BODY
		setcolor(GREEN);
		setfillstyle(1,BROWN) ;
		rectangle(234,260,274,240);
		floodfill(238,256,GREEN);
		rectangle(229,243,234,257);
		setfillstyle(1,GREEN);
		floodfill(230,247,GREEN);

		setcolor(BLACK);                           //DESIGN
		for(int i=241;i<=269;i+=7)
		{
			line(i,240,i,260);
		}
		line(234,243,234,257);

		setcolor(WHITE);                           //EXHAUST
		for( i=243;i<=245;++i)
		{
			line(274,i,276,i);
		}

		setfillstyle(1,WHITE);                     //HEADLAMP
		sector(230,246,160,200,5,5);
		sector(230,254,160,200,5,5);

}

void truck4()                //3rd quad diag
{

		truck1();
							  //MAIN  BODY
		setcolor(GREEN);
		setfillstyle(1,BROWN) ;

		int a[10] = {532,354,560,326,574,340,546,368,532,354};
		fillpoly(5,a);


		setcolor(BLACK);                           //DESIGN
		line(546,368,532,354);
		line(551,363,537,349);
		line(556,358,542,344);
		line(561,353,547,339);
		line(566,348,552,334);
		line(571,343,557,329);


		setcolor(WHITE);                           //EXHAUST
		int c[10] = {562,328,564,326,566,328,564,330,562,328};
		setfillstyle(1,WHITE);
		fillpoly(5,c);

		setfillstyle(1,WHITE);                     //HEADLAMP
		sector(533,361,210,250,5,6);
		sector(539,367,210,250,5,6);

		int b[10] = {534,356,544,366,540,370,530,360,534,356};//truck top
		setcolor(BLACK);
		setfillstyle(1,GREEN);
		fillpoly(5,b);

}

void truck5()                                    //downward movement
{
								  //MAIN  BODY
		setcolor(GREEN);
		setfillstyle(1,BROWN) ;
		rectangle(340,326,360,366);
		floodfill(350,350,GREEN);
		rectangle(342,371,358,366);
		setfillstyle(1,GREEN);
		floodfill(343,368,GREEN);

		setcolor(BLACK);                           //DESIGN
		for(int i=359;i>=331;i-=7)
		{
			line(340,i,360,i);
		}
		line(340,366,360,366);

		setcolor(WHITE);                           //EXHAUST
		for( i=345;i>=343;--i)
		{
			line(i,326,i,324);
		}

		setfillstyle(1,WHITE);                     //HEADLAMP
		sector(345,370,250,290,5,5);
		sector(356,370,250,290,5,5);

}

void truck6()                //4th quad diag
{

		truck1();
							  //MAIN  BODY
		setcolor(GREEN);
		setfillstyle(1,BROWN) ;

		int a[10] = {354,168,368,154,340,126,326,140,354,168};
		fillpoly(5,a);


		setcolor(BLACK);                           //DESIGN
		line(354,168,368,154);
		line(349,163,363,149);
		line(344,158,358,144);
		line(339,153,353,139);
		line(329,143,343,129);
		line(334,148,348,134);


		setcolor(WHITE);                           //EXHAUST
		int c[10] = {328,138,326,136,328,134,330,136,328,138};
		setfillstyle(1,WHITE);
		fillpoly(5,c);

		setfillstyle(1,WHITE);                     //HEADLAMP
		sector(361,167,295,330,6,6);
		sector(367,161,295,330,6,6);

		int b[10] = {356,166,360,170,370,160,366,156,356,166};//truck top
		setcolor(BLACK);
		setfillstyle(1,GREEN);
		fillpoly(5,b);

}

void truck7()                       //right horizontal
{

							  //MAIN  BODY
		setcolor(GREEN);
		setfillstyle(1,BROWN) ;
		rectangle(26,40,66,60);
		floodfill(46,50,GREEN);
		rectangle(66,42,71,58);
		setfillstyle(1,GREEN);
		floodfill(68,50,GREEN);

		setcolor(BLACK);                           //DESIGN
		for(int i=59;i>=31;i-=7)
		{
			line(i,60,i,40);

		}
		line(66,40,66,58);

		setcolor(WHITE);                           //EXHAUST
		for( i=54;i<=56;++i)
		{
			line(24,i,26,i);
		}

		setfillstyle(1,WHITE);                     //HEADLAMP
		sector(70,45,0,20,5,5);
		sector(70,55,0,20,5,5);
		sector(70,45,340,360,5,5);
		sector(70,55,340,360,5,5);

}


void truck8()                     //1st quad diag
{
		truck1();
							  //MAIN  BODY
		setcolor(GREEN);
		setfillstyle(1,BROWN) ;

		int a[10] = {540,174,568,146,554,132,526,160,540,174};
		fillpoly(5,a);


		setcolor(BLACK);                           //DESIGN
		line(554,132,568,146);
		line(549,137,563,151);
		line(544,142,558,156);
		line(539,147,553,161);
		line(534,152,548,166);
		line(529,157,543,171);


		setcolor(WHITE);                           //EXHAUST
		int c[10] = {534,172,536,170,538,172,536,174,534,172};
		setfillstyle(1,WHITE);
		fillpoly(5,c);

		setfillstyle(1,WHITE);                     //HEADLAMP
		sector(567,139,20,60,5,5);
		sector(561,133,20,60,5,5);

		int b[10] = {560,130,570,140,566,144,556,134,560,130};//truck top
		setcolor(BLACK);
		setfillstyle(1,GREEN);
		fillpoly(5,b);

}

void background()
{
		setcolor(WHITE);
		for(int i=0;i<4;++i)                       //BORDER
		{
			line(1+i,1,1+i,480);
			line(1,479-i,639,479-i);
			line(639-i,479,639-i,0);
			line(639,1+i,1,1+i);
		}

		setcolor(7);
		for(i=50;i<640;i+=40)                      //PARKING  SPACE
		{
			if(i<570)line(i,5,i,65);
			line(i,209,i,269);
			line(i,409,i,474);
		}

		setcolor(WHITE);
		for(i=531;i<534;++i)
		{
			line(i,5,i,65);
		}
		for(i=62;i<66;++i)
		{
			line(531,i,640,i);
		}

}

void store()
{
	int	size1=imagesize(20,418,44,474);     //up and down        //CALCULATING  MEMORY  SIZE  OF  TRUCK
	int 	size2=imagesize(222,238,278,262);   //left and right
	int 	size3=imagesize(530,178,591,122);
      //int 	size4=imagesize(522,578,578,522);   //3rd quad

		p=(char *)malloc(size1);			   //ALLOCATING SIZE  FOR  TRUCKS
		q=(char *)malloc(size3);
		r=(char *)malloc(size2);
		s=(char *)malloc(size3);
		t=(char *)malloc(size1);
		u=(char *)malloc(size3);
		v=(char *)malloc(size2);
		w=(char *)malloc(size3);

		setfillstyle(1,0);

		getimage(578,322,522,378,s);                 //3rd quad diag

		getimage(20,418,44,474,p);                  //STORING THE IMAGE p AND PATCHING

		getimage(122,178,178,122,q) ;                         //second quad diag

		getimage(222,238,278,262,r);                 //left oriented


		getimage(338,322,362,378,t);                        //down  oriented


		getimage(22,38,78,62,v);                            //right oriented



		getimage(378,178,322,122,u);                  //4th quad diag



		getimage(522,178,578,122,w);                  //1st quad diag

		cleardevice();
}


int  mouse1()
{
	int	x=1;
		do
		{
			char	opt;
			mouse 	m;

			m.show_mouse();
			m.get_status();
			m.hide_mouse();
			delay(200);

				if((cx>=216&&cx<=423) && (cy>=161&&cy<=199))     //New Game
				{
					cleardevice();
					background();
					return 1;
				}
				else if((cx>=216&&cx<=423) && (cy>=200&&cy<=239)) //HIGHSCORES
				{
					cleardevice();
					disp();
					return 0;
				}

				else if((cx>=216&&cx<=423) && (cy>=241&&cy<=279))//instructions
				{
					cleardevice();
					instructions();
					return 0;
				}


				 else if((cx>=216&&cx<=423) && (cy>=281&&cy<=319)) //exit
				 {
					setfillstyle(1,0) ;
					setcolor(0);
					bar3d(215,155,425,370,5,1);
					background();
					settextstyle(6,0,1);
					setcolor(15);
					bar3d(213,148,435,180,5,1);
					setcolor(14);
					outtextxy(218,150,"DO YOU WANT TO EXIT ???");
					setcolor(15);
					setfillstyle(1,14);
					bar3d(212,180,323,210,5,1);
					bar3d(325,180,435,210,5,1);
					settextstyle(4,0,1);
					setcolor(4);
					outtextxy(213,183,"    YES");
					outtextxy(326,183,"     NO");

					m.show_mouse();
					m.get_status();
					m.hide_mouse();

					if((cx>212 &&cx<323) && (cy>180 && cy<210)) opt = 'y';
					 else if((cx>325 && 435) && (cy>180 && cy<210)) opt = 'n';

					if(opt=='y')
					{
						x=0;
						closegraph();
						credits();
						exit(0);
					}

					else if (opt == 'n')
					{
						x=0;
						cleardevice();
						background();
						return 2;
					}

				 }
		}while(x==1);

}



int  menu1()
{
	int	x;

		cleardevice();

		do
		{
			setcolor(9);
			settextstyle(7,0,4);
			outtextxy(285,66,"MENU");
			setcolor(15);
			delay(250);
			for(int i=10,j=100,k=360,l=0,flag=1;flag==1;)
			{
				arc(324,100,10,i,5);

				line(320,100,320,j);

				arc(315,138,k,360,5);

				arc(320,150,0,l,10);

				delay(50);
				flag=0;

				if(i<=120)
				{
					i+=6;
					flag=1;
				}

				if(j<=137)
				{
					j+=2;
					flag=1;
				}

				if(k>=200)
				{
					k-=8;
					flag=1;
				}

				if(l<=170)
				{
					l+=10;
					flag=1;
				}
			}

			setfillstyle(1,9);
			bar3d(215,155,425,330,5,1);

			outtextxy(220,160,"New Game");
			outtextxy(220,200,"High scores");
			outtextxy(220,240,"Instructions");
			outtextxy(220,280,"Exit");

			x=mouse1();

		}while(x==2);

	       if(x==1) return 1;

	       return 0;
}


int  mouse2()
{
	int	x=1;
		do
		{
			char	opt;
			mouse 	m;
				m.show_mouse();
				m.get_status();
				m.hide_mouse();
				delay(200);

					if((cx>=216&&cx<=423) && (cy>=161&&cy<=199))     //continue
					{
						cleardevice();
						background();
						return 0;
					}

					else if((cx>=216&&cx<=423) && (cy>=201&&cy<=239))   //new game
					{
						cleardevice();
						background();
						return 1;
					}

					else if((cx>=216&&cx<=423) && (cy>=241&&cy<=279))   // high scores
					{
						cleardevice();
						disp();
						cleardevice();
						return 0;
					}

					else if((cx>=216&&cx<=423) && (cy>=281&&cy<=319))//instructions
					{
						setbkcolor(0);
						instructions();
						return 0;
					}

					else if((cx>=216&&cx<=423) && (cy>=321&&cy<=359)) //exit
					{
						setfillstyle(1,0) ;
						setcolor(0);
						bar3d(215,155,425,370,5,1);
						background();
						settextstyle(6,0,1);
						setcolor(15);
						bar3d(213,148,435,180,5,1);
						setcolor(14);
						outtextxy(218,150,"DO YOU WANT TO EXIT ???");
						setcolor(15);
						setfillstyle(1,14);
						bar3d(212,180,323,210,5,1);
						bar3d(325,180,435,210,5,1);
						settextstyle(4,0,1);
						setcolor(4);
						outtextxy(213,183,"    YES");
						outtextxy(326,183,"     NO");

						m.show_mouse();
						m.get_status();
						m.hide_mouse();

						if((cx>212 &&cx<323) && (cy>180 && cy<210)) opt = 'y';
						 else if((cx>325 && 435) && (cy>180 && cy<210)) opt = 'n';

						if(opt=='y')
						{
							x=0;
							closegraph();
							credits();
							exit(0);
						}
						else if (opt == 'n')
						{
							x=0;
							cleardevice();
							background();
							return 2;
						}
					}

		}while(x==1);
}


int  menu2()
{
	int	x=0;

		do
		{
			setcolor(9);
			settextstyle(7,0,4);
			outtextxy(285,66,"MENU");
			setcolor(15);
			delay(250);

			for(int i=10,j=100,k=360,l=0,flag=1;flag==1;)
			{
				arc(324,100,10,i,5);

				line(320,100,320,j);

				arc(315,138,k,360,5);

				arc(320,150,0,l,10);

				delay(50);
				flag=0;

				if(i<=120)
				{
					i+=6;
					flag=1;
				}

				if(j<=137)
				{
					j+=2;
					flag=1;
				}

				if(k>=200)
				{
					k-=8;
					flag=1;
				}

				if(l<=170)
				{
					l+=10;
					flag=1;
				}
			}

			setfillstyle(1,9);
			bar3d(215,155,425,370,5,1);

			outtextxy(220,160,"Continue");
			outtextxy(220,200,"New Game");
			outtextxy(220,240,"High scores");
			outtextxy(220,280,"Instructions");
			outtextxy(220,320,"Exit");

			x=mouse2();
		}while(x==2);

		if(x==1) return 0;

		return 1;


}

int highlight(int x1,int y1,int x2,int y2,int x,int y)         //x & y are top left co ordinates of truck
{

		setfillstyle(11,CYAN);
		bar(x1,y1,x2,y2);
	int 	l=52,b=20;
		if(x>=x1 && x+b <=x2 && y>=y1 && y+l <=y2)               //to check whether parked or not
		{
			if(bioskey(1)==0)
			{
				return 1;
			}


		}
			return 0;

}

void parking_gen(int &r,int &c)
{
	int		u;
	unsigned int	seed;
	time_t		t;

			randomize();
			seed=(unsigned)time(&t);
			srand(seed);
			r=1+random(3);
			if(r==1)u=12;
			else u=14 ;
			c=1+random(u);
}


int parking_shade(int x,int y)                          //x & y got to pass to highlight fn
{
	int	r,c,x1,x2,y1,y2;
		x1=51;
		parking_gen(r,c);
		if(r==1)
		{
			y1=5;
			y2=65;
		}
		else if(r==2)
		{
			y1=209;
			y2=269;
		}
		else if(r==3)
		{
			y1=409;
			y2=474;
		}

		x1 = x1 + c*40 - 40;
		x2 = x1 + 38;
		dr.a = x1;
		dr.b = y1;
		dr.c = x2;
		dr.d = y2;

		return	highlight(x1,y1,x2,y2,x,y);
}

void movement()
{
	int	newg=1,park=1,count=0;
	int	dir = 1; 				// If up dir = 1 , left --> 2 , right --> 4, down -->3
	void	*ptr = p;


		do
		{
				ptr=p;
				newg=menu1();
			int	key, x = 20, y = 418,flag=0,s1=2,s2=5,check=1,score=-1;
			float	s3=s1*5+s2;
				putimage(x,y,ptr,0);                          //PLACING THE TRUCK  IN  STARTING  POSITION
				for (int  i = 1;newg==1;i++)
				{
					if(park==1)
					{
					     ++score;
					     if(s2<7) s2+=3;
					      else
					      {
						s2=s2%7;
						s1+=1;
					      }

					     park =  parking_shade(x,y);
					     putimage(20,418,p,0);
					     x = 20;
					     y = 418;
					     ptr=p;
					}

					park = highlight(dr.a,dr.b,dr.c,dr.d,x,y);

					setfillstyle(1,0);
					settextstyle(0,0,4);
					if(int(s3*10)==int(s3)*10)
					{
						bar(534,5,635,61);
						char	s[3]={s1+48,s2+48,'\0'};
						setcolor(LIGHTBLUE+BLINK);
						outtextxy(548,19,s);
						if(s2==0&&s1==0)check=0;
						else if(s2==0)
						{
							s2=9;
							s1--;
						}
						else s2--;
					}
					s3=s3-0.1;

					if(bioskey(1)!= 0)                         //IF NO KEY IS PRESSED TRUCK WON'T MOVE
					{
						key = bioskey(0);
						switch(key)
						{
							case  18432 : switch(dir)                       //UP
								      {
									   case 1 :     y = y-7;
											putimage(x,y,ptr,0);

											setfillstyle(1,0);
											bar(x+2,y+57,x+22,y+63);
											break;

									   case 2 :   	ptr = p;            //in left, pressing up
											delay(250);
											y=y-20;
											x=x+10;
											setfillstyle(1,BLACK);
											bar(x-22,y+29,x,y-13);
											background();
											putimage(x-15,y-20,q,0);
											delay(250);
											x=x-17;
											y=y-33;
											dir = 1;

											putimage(x,y,ptr,0);
											setfillstyle(1,0);
											bar(x+10,y+20,x+61,y+75);
											break;

									   case 3 :	y=y-3;	       //reverse
											putimage(x,y,ptr,0);
											setfillstyle(1,0);
											//bar(x,y,x+24,y+2);

											break;

									   case 4 : 	ptr = p;
											delay(250);
											y=y-20;
											x=x+30;
											bar(x-50,y+42,x,y-10);
											background();
											putimage(x-20,y,w,0);
											delay(250);
											x=x+15;

											dir = 1;
											putimage(x,y,ptr,0);
											setfillstyle(1,0);
											bar(x,y+11,x-31,y+52);
											break;
								      }

								      if(y<=4)
								      {
										flag=1;
								      }

								      break;

							case  20480 : switch(dir)                           	//DOWN
								      {
									   case 1 :     y=y+3;
											if(y+58>475)
											{
												flag=1;
											}
											putimage(x,y,ptr,0);
											bar(x+6,y,x+18,y-2);
											break; 		//reverse

									   case 2 : 	ptr = t;
											delay(250);
											y=y+20;
											x=x-25;
											bar(x+19,y+45,x+80,y-20);
											background();
											putimage(x,y+5,s,0);
											delay(250);
											x=x+16;
											y=y-5;

											dir = 3;
											putimage(x,y,ptr,0);
											setfillstyle(1,0);
											bar(x+24,y+14,x+36,y+39);
											bar(x-10,y+38,x+3,y+61);
											break;

									   case 3 : 	y = y+7;
											putimage(x,y,ptr,0);
											setfillstyle(1,0);
											bar(x+2,y+2,x+22,y-5);
											break;

									   case 4 :     ptr = t;
											delay(250);
											y=y-20;
											x=x+25;
											bar(x+27,y-30,x+85,y);
											bar(x-35,y,x-20,y+40);
											background();
											putimage(x+10,y,u,0);
											delay(250);
											x=x+25;
											dir = 3;
											putimage(x,y,ptr,0);
											setfillstyle(1,0);
											bar(x-50,y+3,x,y+43);
											bar(x+24,y+51,x+35,y+24);
											break;

								      }

								      if(y+47>472)
								      {
										flag=1;
								      }

								      break;


							case  19200 : switch(dir)                      //LEFT
								      {
									   case 1 : 	ptr = r;
											delay(250);
											y=y+20;
											x=x-50;
											bar(x-50,y+42,x,y-10);
											background();
											putimage(x+20,y-20,q,0);
											delay(250);
											x=x+25;
											y-=20;

											if(x+54>634)
											{
												flag=1;
											}

											dir = 2;
											putimage(x,y,ptr,0);
											setfillstyle(1,0);
											bar(x+6,y+22,x+48,y+52);
											break;

									   case 2 : 	x = x-7;
											putimage(x,y,ptr,0);
											setfillstyle(1,0);
											bar(x+57,y+2,x+62,y+22);
											break;

									   case 3 : 	ptr = r;
											delay(250);
											y=y+20;
											x=x-50;
											bar(x+70,y+32,x,y-10);
											background();
											putimage(x+20,y-10,s,0);
											delay(250);
											bar(x+87,y+32,x+50,y-20);
											x=x+20;
											y+=5;

											dir = 2;
											putimage(x,y,ptr,0);
											setfillstyle(1,0);
											bar(x+6,y+24,x+29,y+36);
											bar(x+28,y-2,x+30,y);
											break;

									   case 4 :   	x=x-3;   //reverse
											putimage(x,y,ptr,0);
											break;
								      }

								      if(x<6)
								      {
										flag=1;
								      }

								      break;

							case  19712 : switch(dir)                          //RIGHT
								      {
									    case 1 :	ptr = v;
											delay(250);
											y=y+20;
											x=x;
											bar(x-50,y+42,x+80,y-16);
											background();
											putimage(x,y-25,w,0);

											delay(250);
											bar(x-50,y+42,x+80,y-16);
											x=x+25;
											y=y-30;

											dir = 4;

											if(y+22>474)
											{
												flag=1;
											}
											putimage(x,y,ptr,0);
											break;

									    case 2 :    x=x+3;        //reverse
											putimage(x,y,ptr,0);
											break;

									    case 3 : 	ptr = v;
											delay(250);
											y=y ;
											x=x;
											bar(x-50,y+42,x+30,y-8);
											background();
											putimage(x,y+35,u,0);
											delay(250);
											y=y+35;

											dir = 4;
											putimage(x,y,ptr,0);
											setfillstyle(1,0);
											bar(x+6,y+24,x+50,y+52);
											break;

									    case 4 : 	x = x+7;
											if(x+52>634)
											{
												flag=1;
											}
											putimage(x,y,ptr,0);
											setfillstyle(1,0);
											bar(x,y+2,x-5,y+22);
											break;
								      }

								      if(x+54>634)
								      {
										flag=1;
								      }

								      break;

							case  283   : newg=menu2();  				//ESCAPE
						}
						if(newg==1)
						{
							setcolor(15);
						//	putimage(x,y,ptr,0);
							setfillstyle(0,0);
						  //	bar(x-47,y-6,x+32,y+61);
							background();			//PATCHING THE REMAINING PART OF THE TRUCK
						}

					}
					if(newg==1)
					{
						setcolor(15);

						putimage(x,y,ptr,0);
						if(y>200)
						{

							if(ptr==p)                        //slow start
							{
								setfillstyle(1,0);
								bar(x+2,y+57,x+22,y+63);
								background();
							}
						}

						if(flag)
						{
							settextstyle(0,0,1);
							outtextxy(200,270,"YOU ARE FIRED!!! NO RANKING ");
							newg=0;
							delay(2000);
						}

						if(!check)
						{
							settextstyle(0,0,1);
							outtextxy(240,270,"TIME OUT!!!!")   ;
							delay(2000);

							cleardevice();
							char	ppt;
							cout<<"ARE U AN EXISTING PLAYER (Y/N): ";
							cin >> ppt;
							if(ppt=='N'||ppt=='n')
							{
								highscores(score);
								newg=0;
							}
							else
							{
								modify(score);
								newg=0;
							}
						}

						delay(100);
					}

				}
			}while(1);
									//FREEING  MEMORY SPACE
			delete ptr;
			delete p;
			delete q;
			delete r;
			delete s;
			delete t;
			delete u;
			delete v;
			delete w;

}

/*void search1()       //    THIS IS A FUNCTION WRITTEN BY THE PROGRAMMERS(THAT'S US) TO EDIT HIGHSCORES FILES.
{
	high		t,ob;
	int 		flag=0,record_no=0 ;
	fstream 	f("D:\\turboc\\program\\highscores.doc",ios::in|ios::out|ios::binary);

			f.read((char *)&t,sizeof(t));
			while(!f.eof()&&!flag)
			{
				record_no++;
				if(!strcmpi(t.na,"obama"))
				{
					strcpy(t.na,"OBAMA");
					ob=t;
					f.seekp((record_no-1)*sizeof(ob),ios::beg);
					f.write((char *)&ob,sizeof(ob));
					flag=1;
				}
				f.read((char *)&t,sizeof(t));
			}

			f.close();
}
*/

void line()
{
	for(int i=0; i<80; i++)
	{
		cout<<"";
	}
	cout<<endl;
}
void credits()
{
		clrscr();
		cout<<"\n\n"<<setw(20)<<" "<<"Thank you for playing,Hope you enjoyed\n\n";
		line();
		cout<<"\n\n"<<setw(33)<<" "<<" Credits \n\n\n";
		line();
		cout<<"\n\n This Project is done by : \n\n";
		cout<<setw(25)<<" " <<"Kaushik.S \t\t Karthik.K\n\n"
			<<setw(20)<<"  " <<"     Chris Richard \t\t Sashank Ramesh\n\n"
				<<setw(35)<<" "<<" Jayanthan.T.P";

		getch();
}

void main()
{
		graphics();
		truck2();
		truck3();
		truck1();
		truck4();
		truck5();
		truck6();
		truck7();
		truck8();
		store();
		loading();
		movement();

}


