#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//Cac bien toan cuc
int SoLanSDQTG50_50 = 0; //So lan su dung quyen tro giup 50:50
int SoLanSDQTGGDTCNT = 0;	//So lan su dung quyen tro giup Goi dien thoai cho nguoi than
int SoLanSDQTGXYKKGTTQ = 0;	//So lan su dung quyen tro giup Xin y kien khan gia tai truong quay
int SoLanSDQTGHTVTTQ= 0;	//So lan su dung quyen tro giup Hoi to tu van o truong quay
int soCauTraLoiDung = 0;	//So cau tra loi dung chung cuoc


typedef struct 
{
	char A[300];
	char B[300];
	char C[300];
	char D[300];
}CauTraLoi;

typedef struct{
	char DA_Dung[3];
  	char DA_Sai_1[3];
  	char DA_Sai_2[3];
}DapAnCauHoi;

typedef struct 
{
  char CauHoi[300];
  CauTraLoi  TraLoi;
  DapAnCauHoi DapAn; 
}DSCH;

typedef struct node{
    DSCH data;
    struct node *next;
}Node;

Node* createNode(DSCH cauhoi){
    Node *temp = (Node*)malloc(sizeof(Node));
    temp->next = NULL; 
    temp->data = cauhoi;  
    return temp;
}

Node* addEnd(Node* head, DSCH cauhoi){
	Node *p=head;
	
	if(head==NULL){
		return createNode(cauhoi);
	}
	while(p->next != NULL){
		p = p->next;
	}
		
	while(p->next != NULL)
		p = p->next;
	Node* q = createNode(cauhoi);
	p->next = q;
	
	return head;	
}

void docFileTxt(Node **head){
	printf("\nJUMP TO FUNTION \n");
	FILE *p;
	DSCH cauhoi[50];
	p = fopen("cauhoi.txt","r");

	if (p == NULL){
		printf("Cannot open %s.\n", "cauhoi.txt");
		//return;
    } 
    char pstr[300];
	int i = 0;

    while(fgets(pstr,300,p)!=NULL){
        char *str;

        //Doc cau hoi
        str = strtok(pstr, ";");
        strcpy(cauhoi[i].CauHoi,str);

        //Doc dap an A
        str = strtok(NULL, ";");
        strcpy(cauhoi[i].TraLoi.A,str);
        //Doc dap an B
        str = strtok(NULL, ";");
        strcpy(cauhoi[i].TraLoi.B,str);
        //Doc dap an C
        str = strtok(NULL, ";");
        strcpy(cauhoi[i].TraLoi.C,str);
        //Doc dap an D
        str = strtok(NULL, ";");
        strcpy(cauhoi[i].TraLoi.D,str);
        //Doc dap an dung
        str = strtok(NULL, ";");
        strcpy(cauhoi[i].DapAn.DA_Dung,str);
        //Doc dap an sai 1
        str = strtok(NULL, ";");
        strcpy(cauhoi[i].DapAn.DA_Sai_1,str);
        //Doc dap an sai 2
        str = strtok(NULL, ";");
        strcpy(cauhoi[i].DapAn.DA_Sai_2,str);
        *head = addEnd(*head,cauhoi[i]);
        i++;
    }

	fclose(p);
}

char* xuatMotCauHoi(Node *head){
    Node *p=head;
    //printf("%s\nA. %s\nB. %s\nC. %s\nD. %s\n",p->data.CauHoi,p->data.TraLoi.A,p->data.TraLoi.B,p->data.TraLoi.C,p->data.TraLoi.D);  
    char send_buff[500];
    strcpy(send_buff,p->data.CauHoi);
    strcpy(send_buff,"\n");
    strcpy(send_buff,p->data.TraLoi.A);
    strcpy(send_buff,"\n");
    strcpy(send_buff,p->data.TraLoi.B);
    strcpy(send_buff,"\n");
    strcpy(send_buff,p->data.TraLoi.C);
    strcpy(send_buff,"\n");
    strcpy(send_buff,p->data.TraLoi.D);
    strcpy(send_buff,"\n");
    return &send_buff;
}

void xuatMotDanhSachCauHoi(Node *head){
    Node *p=head;

    while(p!=NULL){
        //printf("%s\n%s\n%s\n%s\n%s\n",p->data.CauHoi,p->data.TraLoi.A,p->data.TraLoi.B,p->data.TraLoi.C,p->data.TraLoi.D);
        xuatMotCauHoi(p);
        p = p->next;
    }
}

int KiemTraPhuongAnDungSai(char PA_Dung[], char PA_TraLoi[])
{
	if(strcmp(PA_Dung,PA_TraLoi)==0)
	{
		return 1;
	}
	return 0;
}

void XuatKetQuaDungSai(int x)
{
	if(x == 1){
		//TextColor(30);
		printf("*Chuc mung ban da da tra loi dung*\n\n");
		//DapAnDung(); //sound
		//TextColor(14);
	}
	else{
		//TextColor(79);
		printf("Rat tiec ban da da tra loi sai, phan choi cua ban da ket thuc!\n\n");
		//DapAnSai();  //sound
		//TextColor(14);
	}
}

double TinhThangTienThuong(int SoCauTraLoiDung)
{
	double TienThuong = 200000;
	if(SoCauTraLoiDung == 1)
		TienThuong = 200000;
	if(SoCauTraLoiDung == 2)
		TienThuong = 400000;
	if(SoCauTraLoiDung == 3)
		TienThuong = 600000;
	if(SoCauTraLoiDung == 4)
		TienThuong = 1000000;
	if(SoCauTraLoiDung == 5)
		TienThuong = 2000000;
	if(SoCauTraLoiDung == 6)
		TienThuong = 3000000;
	if(SoCauTraLoiDung == 7)
		TienThuong = 6000000;
	if(SoCauTraLoiDung == 8)
		TienThuong = 10000000;
	if(SoCauTraLoiDung == 9)
		TienThuong = 14000000;
	if(SoCauTraLoiDung == 10)
		TienThuong = 22000000;
	if(SoCauTraLoiDung == 11)
		TienThuong = 30000000;
	if(SoCauTraLoiDung == 12)
		TienThuong = 40000000;
	if(SoCauTraLoiDung == 13)
		TienThuong = 60000000;
	if(SoCauTraLoiDung == 14)
		TienThuong = 85000000;
	if(SoCauTraLoiDung == 15)
		TienThuong = 150000000;
	return TienThuong;
}

char MenuChonQuyenTroGiup()
{
	//TextColor(11);
	//NhacTroGiup();
	printf("\n\t\t\tMENU TRO GIUP");
  	printf("\n\tBam phim (1) de chon quyen tro giup 50:50\n");
    printf("\n\tBam phim (2) de chon quyen tro giup Goi dien thoai cho nguoi than\n");
    printf("\n\tBam phim (3) de chon quyen tro giup Xin y kien khan gia truong quay\n");
    printf("\n\tBam phim (4) de chon quyen tro giup Hoi to tu van o truong quay\n");
    //TextColor(14);
    fflush(stdin);
    char chon;
    scanf("%c\n",&chon);
    if((chon != '1') && (chon != '2') && (chon != '3') && (chon != '4'))
	{
		do{
			//TextColor(241);
			printf("Du lieu nhap vao khong hop le. Vui long nhap lai theo dung ky tu (1) (2) (3) (4) ung voi quyen tro giup ban muon chon:\n");
			//TextColor(14);
			fflush(stdin);
            scanf("%c\n",&chon);
			//chon = getch();
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

int checkDapAnNhapVao(char *k){
    if((strcmp(k,"A")!=0) && (strcmp(k,"B")!=0) && (strcmp(k,"C")!=0) && (strcmp(k,"D")!=0) && (strcmp(k,"H")!=0) && (strcmp(k,"R")!=0))
		return 1;
    return 0;
}

int BatDauTraLoi(Node *head)
{
	char k[2], enter;
	int dem = 0;
	int dem_temp = 0;
	Node *p = head;
	int SoThuTuCau = 1;
	while((p != NULL) && (SoThuTuCau <= 15))
	{ 
		/*if ((SoThuTuCau >=1) && (SoThuTuCau <= 5))
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
		}*/
		
		//TextColor(10);
		printf("Cau hoi %d:\n",SoThuTuCau);
		//TextColor(11);
		xuatMotCauHoi(p);
		//TextColor(12);
		printf("Nhap cau tra loi: ");
		fflush(stdin);
		//gets(k);
        scanf("%s",k);
        scanf("%c",&enter);
        fflush(stdin);
		//TextColor(14);

        //Check du lieu nhap vao
		if(checkDapAnNhapVao(k)==1){
			do{
				//TextColor(241);
				printf("Du lieu nhap vao khong hop le. Vui long nhap lai dap an ban chon theo dung ky tu (A) (B) (C) (D) ung voi phuong an muon chon / (H) de chon quyen tro giup / (R) de dung cuoc choi va bao toan so tien thuong: ");
				//TextColor(12);
				fflush(stdin);
				//gets(k);
                scanf("%s",k);
                scanf("%c",&enter);
				//TextColor(14);
			}while(checkDapAnNhapVao(k)==1);
		}
		
		//Su dung quyen tro giup
		if(strcmp(k,"H")==0)
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
	  						//TextColor(244);
							printf("Quyen tro giup nay da duoc chon truoc do. Vui long chon quyen tro giup khac\n");
							//TextColor(14);	
							break;
						  }
					
				default: { 
							//TextColor(237);
							printf("Tinh nang ban chon chua duoc cap nhat hoac ban da het quyen tro giup\n");
							//TextColor(14);
							break;
					     }
		 	}
		 	//TextColor(12);
			printf("Nhap cau tra loi: ");
			fflush(stdin);
			//gets(k);
            scanf("%s",k);
            scanf("%c",&enter);
			//TextColor(14);
			if(checkDapAnNhapVao(k)==1)
			{
				do{
					//TextColor(241);
					printf("Du lieu nhap vao khong hop le. Vui long nhap lai dap an ban chon theo dung ky tu (A) (B) (C) (D) ung voi phuong an muon chon / (H) de chon quyen tro giup / (R) de dung cuoc choi va bao toan so tien thuong: ");
					//TextColor(12);
					fflush(stdin);
					//gets(k);
                    scanf("%s",k);
                    scanf("%c",&enter);
					//TextColor(14);
				}while(checkDapAnNhapVao(k)==1);
			}
			
			if(strcmp(k,"H")==0)
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
			  					//TextColor(244);
								printf("Quyen tro giup nay da duoc chon truoc do. Vui long chon quyen tro giup khac\n");
								//TextColor(14);	
								break;
						      }
							
					default: { 
								//TextColor(237);
								printf("Tinh nang ban chon chua duoc cap nhat hoac ban da het quyen tro giup\n");
								//TextColor(14);
								break;
						     }
			 		}
			 		//TextColor(12);
			 		printf("Nhap cau tra loi: ");
					fflush(stdin);
					//gets(k);
                    scanf("%s",k);
                    scanf("%c",&enter);
					//TextColor(14);
					if(checkDapAnNhapVao(k)==1)
					{
						do{
							//TextColor(241);
							printf("Du lieu nhap vao khong hop le. Vui long nhap lai dap an ban chon theo dung ky tu (A) (B) (C) (D) ung voi phuong an muon chon / (H) de chon quyen tro giup / (R) de dung cuoc choi va bao toan so tien thuong: ");
							//TextColor(12);
							fflush(stdin);
							//gets(k);
                            scanf("%s",k);
                            scanf("%c",&enter);
							//TextColor(14);
						}while(checkDapAnNhapVao(k)==1);
					}
				}while(strcmp(k,"H")==0);
			}
		}
		
		//Dung cuoc choi va bao toan so tien thuong
		if(strcmp(k,"R")==0)
		{
			//TextColor(176);
			printf("Ban da quyet dinh dung cuoc choi de bao toan so tien thuong\n");
			//TextColor(14);
			break;
		}

        printf("=> Ban da chon phuong an: %s\n", k);
        int m = KiemTraPhuongAnDungSai(p->data.DapAn.DA_Dung,k);
		if(m==0){ 	
			//TextColor(15);
			XuatKetQuaDungSai(m);
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
		else{ 
			//TextColor(15);
			//TextColor(14);
			XuatKetQuaDungSai(m);
			SoThuTuCau++;
			dem++;
			dem_temp++;
		}
		p = p->next;
	}
	soCauTraLoiDung = dem_temp;
	return dem;	  
}


void MenuNguoiChoi(Node *head)
{
    Node *p,*q,*moi;
    DSCH x;
    int choice, count =5;    
    do
    {
        printf("\n\n\t\t\t\t\t==== MENU NGUOI CHOI  ====");
        printf("\n\t\t\t\t\t=  1. BAT DAU TRO CHOI   =");
        printf("\n\t\t\t\t\t=     NHAP 0 DE THOAT    =\n");
        printf("\t\t\t\t\t========== END ===========\n");
        fflush(stdin);
        scanf("%d",&choice);
        switch(choice)
        {
            case 1: {
					 //	BatDau();
						printf("\n----BAT DAU TRO CHOI----\n");
                        printf("Ban chi duoc nhap 4 dap an theo quy dinh la: (A} (B) (C) (D) hoac nhap (H) de nhan quyen tro giup hoac nhap (R) de dung cuoc choi va bao luu so tien thuong\n\n");
			            count = BatDauTraLoi(head);
			            
			            printf("\n----KET QUA CHUNG CUOC----\n");
			            
			            printf("So cau tra loi dung cua ban la: %d/15 cau\n",soCauTraLoiDung);
			            printf("Moc tra loi dung cua ban la: %d/15 cau\n",count);
			            printf("So tien thuong cua ban la: %.0f VND\n",TinhThangTienThuong(count));
			            if(count==15)
			            {
			            	//TextColor(30);
            				printf("Xin chuc mung ban da vuot tat ca cac cau hoi cua chung toi va ban da tro thanh trieu phu cua chuong trinh\n");
            				//TextColor(14);
            			}
			            //TextColor(14);
						break;
					  }
                    
            case 0: {	
						exit(1);
            			break;
				    }
				      
            default:  { 
						printf("\nBan da chon tinh nang khong hop le. Moi ban vui long nhap lai\n");
						break;
         			  }
        }
    }while(choice!='0');
}








int main(){
    Node *head=NULL;
    printf("AI LA TRIEU PHU \n");

    docFileTxt(&head);
    printf("AI LA TRIEU PHU \n");
	printf("\n%s\n",xuatMotCauHoi(head));
    //xuatMotDanhSachCauHoi(head);
    printf("\n");
    MenuNguoiChoi(head);
    return 0;
}
