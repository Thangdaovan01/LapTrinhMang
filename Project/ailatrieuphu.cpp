#include <windows.h>
#include <mmsystem.h>
#include <iostream>
#include<stdio.h>
#include<conio.h>
#include<windows.h>
#include <string.h>
#include<iomanip>
#include <stdlib.h>
#include <conio.h>
#define MK "123456"
#include <fstream>
#pragma GCC diagnostic ignored "-Wwrite-strings"

using namespace std;

int Theme1() //Nhac nen 1
{
	PlaySound(TEXT("Main Theme1.wav"), NULL, SND_SYNC | SND_ASYNC | SND_LOOP);
	return 0;
}

int BatDau() //Nhac Bat Dau
{
	PlaySound(TEXT("lets play.wav"), NULL, SND_ASYNC);
	return 0;
}

int DapAn() //Nhac Dap An Cuoi Cung
{
	PlaySound(TEXT("final answer.wav"), NULL, SND_SYNC);
	return 0;
}

int DapAnDung() //Nhac Dap An Dung
{
	PlaySound(TEXT("correct answer.wav"), NULL, SND_SYNC);
	return 0;
}

int DapAnSai() //Nhac Dap An Sai
{
	PlaySound(TEXT("wrong answer.wav"), NULL, SND_ASYNC);
	return 0;
}

int CauHoi1Den5() //Nhac câu hoi 1-5
{
	PlaySound(TEXT("64000 music.wav"), NULL, SND_ASYNC | SND_LOOP);
	return 0;
}

int CauHoi6Den10() //Nhac câu hoi 6-10
{
	PlaySound(TEXT("1001000 music.wav"), NULL, SND_ASYNC);
	return 0;
}

int CauHoi11Den15() //Nhac câu hoi 1-15
{
	PlaySound(TEXT("125000250000 music.wav"), NULL, SND_ASYNC);
	return 0;
}


int NhacTroGiup() //Nhac câu hoi 1-15
{
	PlaySound(TEXT("fastest finger.wav"), NULL, SND_ASYNC | SND_LOOP);
	return 0;
}

//Cac bien toan cuc
int SoLanSDQTG50_50 = 0; //So lan su dung quyen tro giup 50:50
int SoLanSDQTGGDTCNT = 0;	//So lan su dung quyen tro giup Goi dien thoai cho nguoi than
int SoLanSDQTGXYKKGTTQ = 0;	//So lan su dung quyen tro giup Xin y kien khan gia tai truong quay
int SoLanSDQTGHTVTTQ= 0;	//So lan su dung quyen tro giup Hoi to tu van o truong quay
int soCauTraLoiDung = 0;	//So cau tra loi dung chung cuoc

//Cac ham giao dien
//Ham to mau
void TextColor(int x)
{
	HANDLE mau;
	mau=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(mau,x);
}

//Ham GoToXY
void gotoxy(short x, short y)
{
 	HANDLE hConsoleOutput;
 	COORD Cursor_an_Pos = { x, y };
 	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
 	SetConsoleCursorPosition(hConsoleOutput, Cursor_an_Pos);
}

struct CauTraLoi
{
	char A[300];
	char B[300];
	char C[300];
	char D[300];
};

struct DapAnCauHoi
{
	char DA_Dung[3];
  	char DA_Sai_1[3];
  	char DA_Sai_2[3];
};

struct DSCH
{
  char	CauHoi[300];
  CauTraLoi  TraLoi;
  DapAnCauHoi DapAn; 
};

typedef struct Node 
{
	DSCH data;
	Node *link;
}Node1;

typedef struct List
{
	Node *first;
 	Node *last;
}Node2;

void init(List &l)
{
	l.first=l.last=NULL;
}

Node *GetNode(DSCH x)
{
	Node *p;
 	p = new Node;
  	if(p==NULL)
	{
	  printf("Khong du bo nho\n");  
	  return NULL;
	}
  	p->data = x;
  	p->link = NULL;
  	return p;
}

void AddFirst(List &l, Node *new_ele)
{
	if(l.first==NULL)
	{
		l.first = new_ele;
		l.last = l.first;
	}
	else
	{
		new_ele->link = l.first;
		l.first = new_ele;
	}
}

void InsertFirst(List &l, DSCH x)
{
	Node *new_ele = GetNode(x);
	if(new_ele==NULL)
	{
		return;
	}
	AddFirst(l,new_ele);
}

void AddLast(List &l, Node *new_ele)
{
	if(l.first==NULL)
	{
		l.first = l.last = new_ele;
	}
	else
	{
		l.last->link = new_ele;
		l.last = new_ele;
	}
}

void InsertLast(List &l, DSCH x)
{
	Node *new_ele = GetNode(x);
	if(new_ele == NULL)
	{
		return;
	}
	AddLast(l,new_ele);
}

int NhapMotCauHoi(DSCH &x) //admin
{
	TextColor(11);
	printf("Nhap cau hoi: ");
	fflush(stdin);
	gets(x.CauHoi);
	if(stricmp(x.CauHoi,"0")==0)
	{
		return 0;
	}
	
	TextColor(14);
	printf("Nhap cau tra loi A: ");
	fflush(stdin);
	gets(x.TraLoi.A);
	
	printf("Nhap cau tra loi B: ");
	fflush(stdin);
	gets(x.TraLoi.B);
	if(stricmp(x.TraLoi.A,x.TraLoi.B)==0)
	{
		do{
			printf("Dap an khong duoc trung nhau. Vui long nhap lai cau tra loi B: ");
			fflush(stdin);
			gets(x.TraLoi.B);
		}while(stricmp(x.TraLoi.A,x.TraLoi.B)==0);
	}
	
	printf("Nhap cau tra loi C: ");
	fflush(stdin);
	gets(x.TraLoi.C);
	if((stricmp(x.TraLoi.A,x.TraLoi.C)==0) || (stricmp(x.TraLoi.B,x.TraLoi.C)==0))
	{
		do{
			printf("Dap an khong duoc trung nhau. Vui long nhap lai cau tra loi C: ");
			fflush(stdin);
			gets(x.TraLoi.C);
		}while((stricmp(x.TraLoi.A,x.TraLoi.C)==0) || (stricmp(x.TraLoi.B,x.TraLoi.C)==0));
	}
	
	printf("Nhap cau tra loi D: ");
	fflush(stdin);
	gets(x.TraLoi.D);
	if((stricmp(x.TraLoi.A,x.TraLoi.D)==0) || (stricmp(x.TraLoi.B,x.TraLoi.D)==0) || (stricmp(x.TraLoi.C,x.TraLoi.D)==0))
	{
		do{
			printf("Dap an khong duoc trung nhau. Vui long nhap lai cau tra loi D: ");
			fflush(stdin);
			gets(x.TraLoi.D);
		}while((stricmp(x.TraLoi.A,x.TraLoi.D)==0) || (stricmp(x.TraLoi.B,x.TraLoi.D)==0) || (stricmp(x.TraLoi.C,x.TraLoi.D)==0));
	}
	
	TextColor(12);
	printf("Nhap dap an dung: ");
	fflush(stdin);
	gets(x.DapAn.DA_Dung);
	
	printf("Nhap dap an sai thu nhat: ");
	fflush(stdin);
	gets(x.DapAn.DA_Sai_1);
	
	printf("Nhap dap an sai thu hai: ");
	fflush(stdin);
	gets(x.DapAn.DA_Sai_2);
	TextColor(14);
	return 1;
}

void NhapDSCauHoi(List &l) //admin
{
  	DSCH x;
  	TextColor(10);
  	printf("Nhap danh sach cau hoi\n");
  	TextColor(14);
  	int flag = NhapMotCauHoi(x);
  	while(flag)
  	{
  		InsertLast(l,x);
  		flag = NhapMotCauHoi(x);
	}
	TextColor(15);
  	printf("\nKet thuc nhap danh sach cau hoi\n");
  	TextColor(14);
}

void XuatMotCH(DSCH x)
{
	TextColor(11);
 	printf("%s\n ",x.CauHoi);
 	TextColor(14);
 	printf("A.%s\n ",x.TraLoi.A);
 	TextColor(14);
	printf("B.%s\n ",x.TraLoi.B);
	TextColor(14);
 	printf("C.%s\n ",x.TraLoi.C);
 	TextColor(14);
 	printf("D.%s\n ",x.TraLoi.D);
 	TextColor(14);
}

void XuatDSCauHoi(List l)
{
 	Node *p;
 	p=l.first;
 	while(p!=NULL)
 	{
    	XuatMotCH(p->data);
 		p=p->link;
 	}
}

void DocFileTextVaoMang(char s[], int speed) //in ra man hinh
{
	FILE *fp = fopen(s,"r");
	while(!feof(fp))
	{
		Sleep(speed);
		char ch = getc(fp);
		printf("%c",ch);
		if(GetAsyncKeyState(VK_RIGHT))
		{
			fclose(fp);
			return;
		}
	}
	fclose(fp);
}

void GhiFile(List &l) //admin - ghi vao cuoi file
{
    FILE *fp;
    fp = fopen("CauHoi.txt","a+");	//Mo file "CauHoi.txt" va ghi noi dung moi vao phia sau noi dung da co
    for(Node *p = l.first ; p != NULL; p = p->link)
	{
		//Noi dau ";" vao sau cau hoi de phan cach voi cac phan tu khac
		strcat(p->data.CauHoi,";");	
		fputs(p->data.CauHoi,fp);	//Tien hanh ghi du lieu vao file
		
		//Noi dau ";" vao sau cau tra loi A de phan cach voi cac phan tu khac
		strcat(p->data.TraLoi.A,";");	
		fputs(p->data.TraLoi.A,fp);	//Tien hanh ghi du lieu vao file
		
		//Noi dau ";" vao sau cau tra loi B de phan cach voi cac phan tu khac
		strcat(p->data.TraLoi.B,";");
		fputs(p->data.TraLoi.B,fp);	//Tien hanh ghi du lieu vao file
		
		//Noi dau ";" vao sau cau tra loi C de phan cach voi cac phan tu khac
		strcat(p->data.TraLoi.C,";");	
		fputs(p->data.TraLoi.C,fp);	//Tien hanh ghi du lieu vao file
		
		//Noi dau ";" vao sau cau tra loi D de phan cach voi cac phan tu khac
		strcat(p->data.TraLoi.D,";");
		fputs(p->data.TraLoi.D,fp);	//Tien hanh ghi du lieu vao file
		
		//Noi dau ";" vao sau dap an dung de phan cach voi cac phan tu khac
		strcat(p->data.DapAn.DA_Dung,";");
		fputs(p->data.DapAn.DA_Dung,fp);	//Tien hanh ghi du lieu vao file
		
		//Noi dau ";" vao sau dap an sai 1 de phan cach voi cac phan tu khac
		strcat(p->data.DapAn.DA_Sai_1,";");
		fputs(p->data.DapAn.DA_Sai_1,fp);	//Tien hanh ghi du lieu vao file
		
		//Noi dau ";" vao sau dap an sai 2 de phan cach voi cac phan tu khac
		strcat(p->data.DapAn.DA_Sai_2,";");
		strcat(p->data.DapAn.DA_Sai_2,"\n");	//Them ky tu xuong dong de phan cach giua cac cau hoi
		fputs(p->data.DapAn.DA_Sai_2,fp);	//Tien hanh ghi du lieu vao file
    }
    TextColor(30);
    printf("Ghi file thanh cong\n");
    TextColor(14);
    fclose(fp);
}

void CapNhatFile(List &l) //admin
{
    FILE *fp;
    fp = fopen("CauHoi.txt","w");	//Mo file "CauHoi.txt" va tien hanh ghi de tat ca
    for(Node *p = l.first ; p != NULL; p = p->link)
	{
		//Noi dau ";" vao sau cau hoi de phan cach voi cac phan tu khac
		strcat(p->data.CauHoi,";");	
		fputs(p->data.CauHoi,fp);	//Tien hanh ghi du lieu vao file
		
		//Noi dau ";" vao sau cau tra loi A de phan cach voi cac phan tu khac
		strcat(p->data.TraLoi.A,";");	
		fputs(p->data.TraLoi.A,fp);	//Tien hanh ghi du lieu vao file
		
		//Noi dau ";" vao sau cau tra loi B de phan cach voi cac phan tu khac
		strcat(p->data.TraLoi.B,";");
		fputs(p->data.TraLoi.B,fp);	//Tien hanh ghi du lieu vao file
		
		//Noi dau ";" vao sau cau tra loi C de phan cach voi cac phan tu khac
		strcat(p->data.TraLoi.C,";");	
		fputs(p->data.TraLoi.C,fp);		//Tien hanh ghi du lieu vao file
		
		//Noi dau ";" vao sau cau tra loi D de phan cach voi cac phan tu khac
		strcat(p->data.TraLoi.D,";");
		fputs(p->data.TraLoi.D,fp);	//Tien hanh ghi du lieu vao file
		
		//Noi dau ";" vao sau dap an dung de phan cach voi cac phan tu khac
		strcat(p->data.DapAn.DA_Dung,";");
		fputs(p->data.DapAn.DA_Dung,fp);	//Tien hanh ghi du lieu vao file
		
		//Noi dau ";" vao sau dap an sai 1 de phan cach voi cac phan tu khac
		strcat(p->data.DapAn.DA_Sai_1,";");
		fputs(p->data.DapAn.DA_Sai_1,fp);	//Tien hanh ghi du lieu vao file
		
		//Noi dau ";" vao sau dap an sai 2 de phan cach voi cac phan tu khac
		strcat(p->data.DapAn.DA_Sai_2,";");
		strcat(p->data.DapAn.DA_Sai_2,"\n");	//Them ky tu xuong dong de phan cach giua cac cau hoi
		fputs(p->data.DapAn.DA_Sai_2,fp);	//Tien hanh ghi du lieu vao file
    }
    TextColor(30);
    printf("Cap nhat thanh cong\n");
    TextColor(14);
    fclose(fp);
}

bool KiemTraPhuongAnDungSai(char PA_Dung[], char PA_TraLoi[])
{
	if(stricmp(PA_Dung,PA_TraLoi)==0)
	{
		return true;
	}
	return false;
}

void XuatKetQuaDungSai(bool x)
{
	if(x == true)
	{
		TextColor(30);
		printf("*Chuc mung ban da da tra loi dung*\n\n");
		DapAnDung();
		TextColor(14);
	}
	else
	{
		TextColor(79);
		printf("Rat tiec ban da da tra loi sai, phan choi cua ban da ket thuc!\n\n");
		DapAnSai();
		TextColor(14);
	}
}

double TinhThangTienThuong(int SoCauTraLoiDung)
{
	double TienThuong = 200000;
	if(SoCauTraLoiDung == 1)
	{
		TienThuong = 200000;
	}
	if(SoCauTraLoiDung == 2)
	{
		TienThuong = 400000;
	}
	if(SoCauTraLoiDung == 3)
	{
		TienThuong = 600000;
	}
	if(SoCauTraLoiDung == 4)
	{
		TienThuong = 1000000;
	}
	if(SoCauTraLoiDung == 5)
	{
		TienThuong = 2000000;
	}
	if(SoCauTraLoiDung == 6)
	{
		TienThuong = 3000000;
	}
	if(SoCauTraLoiDung == 7)
	{
		TienThuong = 6000000;
	}
	if(SoCauTraLoiDung == 8)
	{
		TienThuong = 10000000;
	}
	if(SoCauTraLoiDung == 9)
	{
		TienThuong = 14000000;
	}
	if(SoCauTraLoiDung == 10)
	{
		TienThuong = 22000000;
	}
	if(SoCauTraLoiDung == 11)
	{
		TienThuong = 30000000;
	}
	if(SoCauTraLoiDung == 12)
	{
		TienThuong = 40000000;
	}
	if(SoCauTraLoiDung == 13)
	{
		TienThuong = 60000000;
	}
	if(SoCauTraLoiDung == 14)
	{
		TienThuong = 85000000;
	}
	if(SoCauTraLoiDung == 15)
	{
		TienThuong = 150000000;
	}
	return TienThuong;
}

char MenuChonQuyenTroGiup()
{
	TextColor(11);
	NhacTroGiup();
	printf("\n\t\t\tMENU TRO GIUP");
  	printf("\n\tBam phim (1) de chon quyen tro giup 50:50\n");
    printf("\n\tBam phim (2) de chon quyen tro giup Goi dien thoai cho nguoi than\n");
    printf("\n\tBam phim (3) de chon quyen tro giup Xin y kien khan gia truong quay\n");
    printf("\n\tBam phim (4) de chon quyen tro giup Hoi to tu van o truong quay\n");
    TextColor(14);
    fflush(stdin);
    char chon = getch();
    if((chon != '1') && (chon != '2') && (chon != '3') && (chon != '4'))
	{
		do{
			TextColor(241);
			printf("Du lieu nhap vao khong hop le. Vui long nhap lai theo dung ky tu (1) (2) (3) (4) ung voi quyen tro giup ban muon chon:\n");
			TextColor(14);
			fflush(stdin);
			chon = getch();
		}while((chon != '1') && (chon != '2') && (chon != '3') && (chon != '4'));
	}
    
    if((SoLanSDQTG50_50>=1) && (SoLanSDQTGGDTCNT>=1) && (SoLanSDQTGXYKKGTTQ>=1) && (SoLanSDQTGHTVTTQ>=1))
    {
    	chon = '0';
    	return chon;
    }
    
    if(chon == '1')
    {
    	SoLanSDQTG50_50++;
    	if(SoLanSDQTG50_50==1)
    	{
    		return chon;
    	}
    	chon = '5';
    }
    
    if(chon == '2')
    {
    	SoLanSDQTGGDTCNT++;
    	if(SoLanSDQTGGDTCNT==1)
    	{
    		return chon;
    	}
    	chon = '5';
    }
    
    if(chon == '3')
    {
    	SoLanSDQTGXYKKGTTQ++;
    	if(SoLanSDQTGXYKKGTTQ==1)
    	{
    		return chon;
    	}
    	chon = '5';
    }
    
    if(chon == '4')
    {
    	SoLanSDQTGHTVTTQ++;
    	if(SoLanSDQTGHTVTTQ==1)
    	{
    		return chon;
    	}
    	chon = '5';
    }
    return chon;
}

int BatDauTraLoi(List l)
{
	char k[2];
	int dem = 0;
	int dem_temp = 0;
	Node *p = l.first;
	int SoThuTuCau = 1;
	while((p != NULL) && (SoThuTuCau <= 15))
	{ 
		if ((SoThuTuCau >=1) && (SoThuTuCau <= 5))
		{
			CauHoi1Den5();
		}
		
		if ((SoThuTuCau >=6) && (SoThuTuCau <= 10))
		{
			CauHoi6Den10();
		}
		
		if ((SoThuTuCau >=11) && (SoThuTuCau <= 15))
		{
			CauHoi11Den15();
		}
		
		TextColor(10);
		printf("Cau hoi %d:\n",SoThuTuCau);
		TextColor(11);
		XuatMotCH(p->data);
		TextColor(12);
		printf("Nhap cau tra loi: ");
		fflush(stdin);
		gets(k);
		TextColor(14);
		if((stricmp(k,"A")!=0) && (stricmp(k,"B")!=0) && (stricmp(k,"C")!=0) && (stricmp(k,"D")!=0) && (stricmp(k,"H")!=0) && (stricmp(k,"R")!=0))
		{
			do{
				TextColor(241);
				printf("Du lieu nhap vao khong hop le. Vui long nhap lai dap an ban chon theo dung ky tu (A) (B) (C) (D) ung voi phuong an muon chon / (H) de chon quyen tro giup / (R) de dung cuoc choi va bao toan so tien thuong: ");
				TextColor(12);
				fflush(stdin);
				gets(k);
				TextColor(14);
			}while((stricmp(k,"A")!=0) && (stricmp(k,"B")!=0) && (stricmp(k,"C")!=0) && (stricmp(k,"D")!=0) && (stricmp(k,"H")!=0) && (stricmp(k,"R")!=0));
		}
		
		//Su dung quyen tro giup
		if(stricmp(k,"H")==0)
		{
			char choice = MenuChonQuyenTroGiup();
			switch(choice)
			{
				case '1': {
							printf("Dap an %s va dap an %s la hai dap an sai\n",p->data.DapAn.DA_Sai_1,p->data.DapAn.DA_Sai_2);
							break;
			              }
						
				case '2': {
							printf("Dap an %s la dap an dung\n",p->data.DapAn.DA_Dung);
							break;
   	                      }	
	                    
				case '3': {
							printf("Phuong an duoc nhieu khan gia trong truong quay chon nhat la: %s\n",p->data.DapAn.DA_Dung);
							break;
						  }
					
				case '4': {
							printf("Phuong an duoc nhieu khan gia trong to tu van chon nhat la: %s\n",p->data.DapAn.DA_Dung);	
							break;
						  }
						  
	  			case '5': { 
	  						TextColor(244);
							printf("Quyen tro giup nay da duoc chon truoc do. Vui long chon quyen tro giup khac\n");
							TextColor(14);	
							break;
						  }
					
				default: { 
							TextColor(237);
							printf("Tinh nang ban chon chua duoc cap nhat hoac ban da het quyen tro giup\n");
							TextColor(14);
							break;
					     }
		 	}
		 	TextColor(12);
			printf("Nhap cau tra loi: ");
			fflush(stdin);
			gets(k);
			TextColor(14);
			if((stricmp(k,"A")!=0) && (stricmp(k,"B")!=0) && (stricmp(k,"C")!=0) && (stricmp(k,"D")!=0) && (stricmp(k,"H")!=0) && (stricmp(k,"R")!=0))
			{
				do{
					TextColor(241);
					printf("Du lieu nhap vao khong hop le. Vui long nhap lai dap an ban chon theo dung ky tu (A) (B) (C) (D) ung voi phuong an muon chon / (H) de chon quyen tro giup / (R) de dung cuoc choi va bao toan so tien thuong: ");
					TextColor(12);
					fflush(stdin);
					gets(k);
					TextColor(14);
				}while((stricmp(k,"A")!=0) && (stricmp(k,"B")!=0) && (stricmp(k,"C")!=0) && (stricmp(k,"D")!=0) && (stricmp(k,"H")!=0) && (stricmp(k,"R")!=0));
			}
			
			if(stricmp(k,"H")==0)
			{
				do{
					char choice = MenuChonQuyenTroGiup();
					switch(choice)
					{
					case '1': {
								printf("Dap an %s va dap an %s la hai dap an sai\n",p->data.DapAn.DA_Sai_1,p->data.DapAn.DA_Sai_2);
								break;
				              }
							
					case '2': {
								printf("Dap an %s la dap an dung\n",p->data.DapAn.DA_Dung);
								break;
	   	                      }	
		                    
					case '3': {
								printf("Phuong an duoc nhieu khan gia trong truong quay chon nhat la: %s\n",p->data.DapAn.DA_Dung);
								break;
							  }
							  
			  		case '4': {
								printf("Phuong an duoc nhieu khan gia trong to tu van chon nhat la: %s\n",p->data.DapAn.DA_Dung);	
								break;
							  }
							  
			  		case '5': { 
			  					TextColor(244);
								printf("Quyen tro giup nay da duoc chon truoc do. Vui long chon quyen tro giup khac\n");
								TextColor(14);	
								break;
						      }
							
					default: { 
								TextColor(237);
								printf("Tinh nang ban chon chua duoc cap nhat hoac ban da het quyen tro giup\n");
								TextColor(14);
								break;
						     }
			 		}
			 		TextColor(12);
			 		printf("Nhap cau tra loi: ");
					fflush(stdin);
					gets(k);
					TextColor(14);
					if((stricmp(k,"A")!=0) && (stricmp(k,"B")!=0) && (stricmp(k,"C")!=0) && (stricmp(k,"D")!=0) && (stricmp(k,"H")!=0) && (stricmp(k,"R")!=0))
					{
						do{
							TextColor(241);
							printf("Du lieu nhap vao khong hop le. Vui long nhap lai dap an ban chon theo dung ky tu (A) (B) (C) (D) ung voi phuong an muon chon / (H) de chon quyen tro giup / (R) de dung cuoc choi va bao toan so tien thuong: ");
							TextColor(12);
							fflush(stdin);
							gets(k);
							TextColor(14);
						}while((stricmp(k,"A")!=0) && (stricmp(k,"B")!=0) && (stricmp(k,"C")!=0) && (stricmp(k,"D")!=0) && (stricmp(k,"H")!=0) && (stricmp(k,"R")!=0));
					}
				}while(stricmp(k,"H")==0);
			}
		}
		
		//Dung cuoc choi va bao toan so tien thuong
		if(stricmp(k,"R")==0)
		{
			TextColor(176);
			printf("Ban da quyet dinh dung cuoc choi de bao toan so tien thuong\n");
			TextColor(14);
			break;
		}
		
		if(KiemTraPhuongAnDungSai(k,p->data.DapAn.DA_Dung)==false)
		{ 	
			TextColor(15);
			if(stricmp(k,"A")==0)
			{
					printf("=> Ban da chon phuong an: A\n");
			}
			if(stricmp(k,"B")==0)
			{
					printf("=> Ban da chon phuong an: B\n");
			}
			if(stricmp(k,"C")==0)
			{
					printf("=> Ban da chon phuong an: C\n");
			}
			if(stricmp(k,"D")==0)
			{
					printf("=> Ban da chon phuong an: D\n");
			} 
			TextColor(15);
			XuatKetQuaDungSai(KiemTraPhuongAnDungSai(k,p->data.DapAn.DA_Dung));
			if((dem>=1) && (dem<5))
			{
				dem = 1;
			}
			if((dem>=5) && (dem<10))
			{
				dem = 5;
			}
			if((dem>=10) && (dem<15))
			{
				dem = 10;
			}
			break;
		}
		else
		{ 
			TextColor(15);
			if(stricmp(k,"A")==0)
			{
					printf("=> Ban da chon phuong an: A\n");
			}
			if(stricmp(k,"B")==0)
			{
					printf("=> Ban da chon phuong an: B\n");
			}
			if(stricmp(k,"C")==0)
			{
					printf("=> Ban da chon phuong an: C\n");
			}
			if(stricmp(k,"D")==0)
			{
					printf("=> Ban da chon phuong an: D\n");
			}
			TextColor(14);
			XuatKetQuaDungSai(KiemTraPhuongAnDungSai(k,p->data.DapAn.DA_Dung));
			SoThuTuCau++;
			dem++;
			dem_temp++;
		}
		p = p->link;
	}
	soCauTraLoiDung = dem_temp;
	return dem;	  
}

void ThemCauHoi(List &l) //admin
{
	DSCH x;
	printf("Nhap Cau hoi va Dap an can them: \n");
	NhapMotCauHoi(x);
	Node *p = GetNode(x);
	InsertLast(l,x);
}

void TimKiemCauHoiTheoTen(List l) //admin
{
	char k[300];
	TextColor(11);
	printf("Nhap cau hoi can tim: ");
	fflush(stdin);
	gets(k);
	TextColor(14);
	Node *p = l.first;
	int dem=0;
	while(p!=NULL)
	{
		if(stricmp(k,p->data.CauHoi)==0)
		{  
			TextColor(30);
		    printf("Tim Thay.\n"); 
		    TextColor(14);
		    dem++;
			XuatMotCH(p->data);
		}
		p=p->link;
	}
	if(dem==0)
	{
		TextColor(79);
		printf("Khong Tim Thay.\n");
		TextColor(14);
	}
}

int DocFile(List &l)
{
	FILE *fp = fopen("CauHoi.txt", "r");
	char *pstr = new char[300];
	int number = 0;
	if (fp == NULL)
 	{
		printf("Khong co file");
		return 0;
	}
	while(fgets(pstr,500,fp)!=NULL)
	{
		char *str;
		Node *p = new Node;
		//Doc cau hoi
		str = strtok(pstr, ";");
		strcpy(p->data.CauHoi, str);
		//Doc cau tra loi A
		str = strtok(NULL, ";");
		strcpy(p->data.TraLoi.A, str);
		//Doc cau tra loi B
		str = strtok(NULL, ";");
		strcpy(p->data.TraLoi.B, str);
		//Doc cau tra loi C
		str = strtok(NULL, ";");
		strcpy(p->data.TraLoi.C, str); 
		//Doc cau tra loi D
		str = strtok(NULL, ";");
		strcpy(p->data.TraLoi.D, str);
		//Doc dap an
		str = strtok(NULL, ";");
		strcpy(p->data.DapAn.DA_Dung, str);
		//Doc dap sai 1
		str = strtok(NULL, ";");
		strcpy(p->data.DapAn.DA_Sai_1, str);
		//Doc dap sai 2
		str = strtok(NULL, ";");
		strcpy(p->data.DapAn.DA_Sai_2, str);
		Node *q = GetNode(p->data);
		AddLast(l, q);
		number++;
	}
	if (fp == NULL)
 	{
		printf("Khong co file");
		return 0;
	}
	fclose(fp);
	return number;
}

void Swap(DSCH &x, DSCH &y)
{
	DSCH tam = x;
	x = y;
	y = tam;
}

//Quick Sort
void SListAppend(List &l, List &l2) //Noi 2 danh sach
{
	if(l2.first==NULL)
	{
		return;
	}
	if(l.first==NULL)
	{
		l = l2;
	}
	else
	{
		l.last->link = l2.first;
		l.last = l2.last;
	}
	init(l2);
}

void SListQuickSort(List &l)
{
	Node *X, *p;
	List l1, l2;
	if(l.first == l.last)
	{
		return;
	}
	init(l1);
	init(l2);
	X = l.first;
	l.first = X->link;
	X->link = NULL;
	while(l.first != NULL)
	{
		p = l.first;
		l.first = l.first->link;
		p->link = NULL;
		if(stricmp(p->data.CauHoi,X->data.CauHoi)<0)
		{
			AddFirst(l1,p);
		}
		else
		{
			AddFirst(l2,p);
		}
	}
	//Sap xep lai
	SListQuickSort(l1);
	SListQuickSort(l2);
	SListAppend(l,l1);
	AddLast(l,X);
	SListAppend(l,l2);
}

void RemoveFirst(List &l)
{
	if(l.first != NULL)
	{
		Node *p = l.first;
		l.first = p->link;
		p->link = NULL;
		delete(p);
		if(l.first == NULL) 
		{
			l.last=NULL;
		}
	}
}

void RemoveAfter(List &l, Node *q)
{
	if(q->link != NULL)
	{
		Node *p = q->link;
		if(p==l.last)	 
		{
			l.last=q;
		}
		q->link = p->link;
		p->link = NULL;
		delete(p);
	}
}

Node *TimXoa(List l, char x[])
{
	Node* p=l.first;
	while( p!=l.last && stricmp(p->link->data.CauHoi,x)!=0)
	{
		p=p->link;
	}
	return p;
}

void RemoveX(List &l, char x[])
{
	if(stricmp(l.first->data.CauHoi,x)==0)
	{
		RemoveFirst(l);
	}
	else
	{
		RemoveAfter(l,TimXoa(l,x));
	}
}

void XoaCauHoi(List &l)
{
	char a[300];
	TextColor(11);
	printf("\nNhap cau hoi can xoa : ");
    fflush(stdin);
    gets(a);
    TextColor(14);
    RemoveX(l,a);
}

char MenuChonAdmin()
{
	printf("\n\n\t\t\t\t\t======= MENU ADMIN  =======");
    printf("\n\t\t\t\t\t=  1. NHAP DANH SACH      =");
    printf("\n\t\t\t\t\t=  2. IN DANH SACH        =");
    printf("\n\t\t\t\t\t=  3. TIM CAU HOI         =");
    printf("\n\t\t\t\t\t=  4. XOA CAU HOI         =");
    printf("\n\t\t\t\t\t=  5. SAP XEP DANH SACH   =");
    printf("\n\t\t\t\t\t=  6. CHEN CAU HOI        =");
    printf("\n\t\t\t\t\t=  NHAP 0 DE THOAT        =\n");
    printf("\t\t\t\t\t=========== END ===========\n");
    fflush(stdin);
    char chon = getch();
    system("cls");
    return chon;
}

void MenuAdmin()
{
    List l;
    Node *p,*q,*moi;
    DSCH x;
    char choice;
    init(l);
    DocFile(l);
    do
    {
       	choice = MenuChonAdmin();
        switch(choice)
        {
            case '1': { 
						NhapDSCauHoi(l);
	   				   	CapNhatFile(l);
	   				   	TextColor(96);
					   	printf("Ban can thoat cua so Console de cau hoi duoc cap nhat\n");
					   	TextColor(14);
	   				   	break;
                      }
                      
            case '2': {	
            			TextColor(10);
						printf("Danh sach cac cau hoi hien co la:\n");
						TextColor(14);
						XuatDSCauHoi(l);
					 	break;
				      }
					  		  
            case '3': {
						TimKiemCauHoiTheoTen(l); 
						break;
				      }
				      
            case '4': { 
						XoaCauHoi(l); 
            			CapNhatFile(l);
            			TextColor(96);
						printf("Ban can thoat cua so Console de cau hoi duoc cap nhat\n");
						TextColor(14);
						break;
			 		  }
			 		  
            case '5': { 
						SListQuickSort(l);
            			TextColor(10);
						printf("\nDanh sach cau hoi sau khi sap xep theo ten cau hoi:\n"); 
						TextColor(14);
						XuatDSCauHoi(l); 
						break;
				      }
				      
            case '6':{	
						NhapDSCauHoi(l);
	   				   	CapNhatFile(l); 
	   				   	TextColor(96);
	   				   	printf("Ban can thoat cua so Console de cau hoi duoc cap nhat\n");
	   				   	TextColor(14);
                        break;
                     }
                    
            case '0': {	
						exit(1);
            			break;
				      }
				      
            default:  { 
						TextColor(241);
						printf("\nBan da chon tinh nang khong hop le. Moi ban vui long nhap lai\n");
						TextColor(14);
      				 	break;
         			  }
        }
    }while(choice!='0');
}

char MenuChonNguoiChoi()
{
	printf("\n\n\t\t\t\t\t==== MENU NGUOI CHOI  ====");
    printf("\n\t\t\t\t\t=  1. BAT DAU TRO CHOI   =");
    printf("\n\t\t\t\t\t=     NHAP 0 DE THOAT    =\n");
    printf("\t\t\t\t\t========== END ===========\n");
    fflush(stdin);
    char chon = getch();
    system("cls");
    return chon;
}

void MenuNguoiChoi()
{
    List l;
    Node *p,*q,*moi;
    DSCH x;
    char choice;
    init(l);
    DocFile(l);
    do
    {
       	choice = MenuChonNguoiChoi();
        switch(choice)
        {
            case '1': {
					 //	BatDau();
						printf("\n----BAT DAU TRO CHOI----\n");
                        printf("Ban chi duoc nhap 4 dap an theo quy dinh la: (A} (B) (C) (D) hoac nhap (H) de nhan quyen tro giup hoac nhap (R) de dung cuoc choi va bao luu so tien thuong\n\n");
			            int count = BatDauTraLoi(l);
			            TextColor(11);
			            printf("\n----KET QUA CHUNG CUOC----\n");
			            TextColor(15);
			            printf("So cau tra loi dung cua ban la: %d/15 cau\n",soCauTraLoiDung);
			            printf("Moc tra loi dung cua ban la: %d/15 cau\n",count);
			            printf("So tien thuong cua ban la: %.0f VND\n",TinhThangTienThuong(count));
			            if(count==15)
			            {
			            	TextColor(30);
            				printf("Xin chuc mung ban da vuot tat ca cac cau hoi cua chung toi va ban da tro thanh trieu phu cua chuong trinh\n");
            				TextColor(14);
            			}
			            TextColor(14);
						break;
					  }
                    
            case '0': {	
						
						exit(1);
            			break;
				      }
				      
            default:  { 
						TextColor(241);
						printf("\nBan da chon tinh nang khong hop le. Moi ban vui long nhap lai\n");
						TextColor(14);
      				 	break;
         			  }
        }
    }while(choice!='0');
}

void MenuCase()
{
	char a[50];
	char chon;
    do
    {
        printf("\n\n\t\t\t\t\t========= MENU ==========");
        printf("\n\t\t\t\t\t=  1. ADMIN             =");
        printf("\n\t\t\t\t\t=  2. NGUOI CHOI        =");
        printf("\n\t\t\t\t\t=  NHAP 0 DE THOAT      =\n");
        printf("\t\t\t\t\t========== END ==========\n");
        chon = getch();
        switch(chon)
        {
            case '1': {
       					   TextColor(11);
	            	       printf("Nhap mat khau admin: ");
	            	       scanf("%s",&a);
	            	       TextColor(14);
	            	       if(stricmp(a,MK)==0)
	            	       {
	            	       		system("cls");
	       	                	MenuAdmin();	
	       	               } 
	       	               else 
	       	               {
	       	               		TextColor(79);
	       	               		printf("Mat khau sai, khong the dang nhap MENU ADMIN. Vui long nhap lai mat khau\n");
	       	               		TextColor(14);
	       	               		system("cls");
	               	       }
	               	       break;
                      }
            	       
	        case '2':{
      			        system("cls");
      			        BatDau();
        		      	MenuNguoiChoi();
					  	break;  
        	         }
                    
            case '0': {	
						exit(1);
            			break;
				      }
				      
            default:  { 
            			TextColor(241);
						printf("\nBan da chon tinh nang khong hop le. Moi ban vui long nhap lai.");
						TextColor(14);
						Sleep(40);
						system("cls");
						
      				 	break;
         			  }
        }
    }while(chon!='0');
}


int main() {
	Theme1();
	//Trang gioi thieu ve "Bai tap lon"
	TextColor(11);
	DocFileTextVaoMang("TieuDeLonTrangBia.txt",0);
	TextColor(15);
	DocFileTextVaoMang("DuongVienTieuDeLonTrangBia.txt",0);
	printf("\n\n");
	TextColor(10);
	DocFileTextVaoMang("TieuDeNhoTrangBia.txt",0);
	TextColor(15);
	DocFileTextVaoMang("DuongVienTieuDeNhoTrangBia.txt",0);
	printf("\n\n");
	TextColor(12);
	DocFileTextVaoMang("TenDeTai.txt",0);
	TextColor(14);
	printf("\n\n");
	DocFileTextVaoMang("NoiDungTrangBia.txt",0);
	printf("\n\n");
	TextColor(11);
	DocFileTextVaoMang("KhungVienLogo1.txt",50);
	Sleep(2000);
	system("cls");
	
	//Trang gioi thieu ve tro choi "Ai la trieu phu"
	TextColor(11);
	DocFileTextVaoMang("KhungVienLogo1.txt",0);
	TextColor(14);
	DocFileTextVaoMang("KhungVienLogo2.txt",0);
	TextColor(10);
	DocFileTextVaoMang("LogoGame.txt",0);
	printf("\n");
	gotoxy(51,19);
	TextColor(206);
	printf("Version Console");
	printf("\n");
	TextColor(11);
	DocFileTextVaoMang("KhungVienLogo1.txt",50);
	Sleep(2000);
	system("cls");
	
	//Trang gioi thieu ve game show "Ai la trieu phu"
	TextColor(15);
	DocFileTextVaoMang("KhungVienLogo1.txt",0);
	TextColor(14);
	DocFileTextVaoMang("KhungVienLogo2.txt",0);
	TextColor(12);
	DocFileTextVaoMang("KhungGachDuoi.txt",0);
	TextColor(11);
	DocFileTextVaoMang("LogoGioiThieu.txt",0);
	printf("\n\n");
	TextColor(12);
	DocFileTextVaoMang("KhungGachDuoi.txt",0);
	gotoxy(52,19);
	TextColor(237);
	printf("Ai la trieu phu");
	printf("\n");
	TextColor(10);
	DocFileTextVaoMang("KhungVienLogo1.txt",40);
	Sleep(1500);
	system("cls");
	
	//Noi dung gioi thieu ve game show "Ai la trieu phu"
	TextColor(11);
	DocFileTextVaoMang("TieuDeGioiThieu.txt",70);
	TextColor(14);
	printf("\n");
	DocFileTextVaoMang("GioiThieu.txt",40);
	Sleep(1000);
	system("cls");
	
	//Trang huong dan ve luat choi cua tro choi "Ai la trieu phu"
	TextColor(9);
	DocFileTextVaoMang("KhungVienLogo1.txt",0);
	TextColor(10);
	DocFileTextVaoMang("KhungVienLogo2.txt",0);
	TextColor(11);
	DocFileTextVaoMang("LogoHuongDanLuatChoi.txt",0);
	gotoxy(53,22);
	TextColor(241);
	printf("Ai la trieu phu");
	printf("\n");
	TextColor(10);
	DocFileTextVaoMang("KhungVienLogo2.txt",0);
	printf("\n");
	TextColor(12);
	DocFileTextVaoMang("KhungVienLogo1.txt",50);
	system("cls");
	
	//Trang huong dan ve luat choi cua tro choi "Ai la trieu phu"
	TextColor(14);
	DocFileTextVaoMang("HuongDanLuatChoi.txt",50);
	Sleep(3000);
	system("cls");
	
	//Bat dau tai vao game
	TextColor(7);
	DocFileTextVaoMang("Loading.txt",0);
	Sleep(2000);
	TextColor(7);
	DocFileTextVaoMang("Start.txt",0);
	Sleep(2000);
	system("cls");
	
	//Chuong trinh chinh
	TextColor(14);
	MenuCase();
	
   	return 0;	//Ket thuc chuong trinh
}