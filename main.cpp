#include<iostream>
#include<iomanip>
#include<stdlib.h>
#include<conio.h>       //
#include<string.h>
#include<fstream>
#include"Book.h"
//#include"Book.cpp"
#define CMD_COLS 80      //
#define CMD_LINES 25
using namespace std;

void SetScreenGrid() {
    char sysSetBuf[80];
    sprintf(sysSetBuf,"mode con cols =%d  lines =%d",CMD_COLS,CMD_LINES);
    system(sysSetBuf);
}

void ClearScreen() {
    system("cls");
}

void SetSysCaption(const char *pText) {
    char sysSetBuf[80];
    sprintf(sysSetBuf,"title =%s",pText);
    system(sysSetBuf);
}

void ShowWelcom() {
    for(int i =0;i<7;i++) {
        cout<<endl;
    }
    cout<<setw(40);          //����40���ո�
    cout<<"***********"<<endl;
    cout<<setw(40); 
    cout<<"*ͼ�����ϵͳ*"<<endl;
    cout<<setw(40);
    cout<<"***********"<<endl;
}

void ShowRootMenu() {
    cout<<setw(40);
    cout<<"��ѡ����"<<endl;
    cout<<setw(38);
    cout<<"1 �������"<<endl;
    cout<<setw(38);
    cout<<"2 ���ȫ��"<<endl;
    cout<<setw(38);
    cout<<"3 ɾ��ͼ��"<<endl;
}

void WaitUser() {
    int iInputPage =0;
    cout<<"enter �������˵�    q �˳�"<<endl;
    char buf[256];
    gets(buf);
    if(buf[0]=='q')
        system("exit");
}

int GetSelect() {
    char buf[256];
    gets(buf);
    return atoi(buf);   //
}
long GetFileLength(ifstream & ifs) {
    long tmppos;
    long respos;
    tmppos=ifs.tellg();
    ifs.seekg(0,ios::end);
    respos=ifs.tellg();
    ifs.seekg(tmppos,ios::beg);  //�ļ�ָ���ƻ�ԭʼλ��
    return respos;
}

void GuideInput() { //�������ģ��
    char inName[NUM1];
    char inlsbn[NUM1];
    char inPrice[NUM2];
    char inAuthor[NUM2];
    cout<<"����������"<<endl;
        cin>>inName;
    cout<<"������ISBN"<<endl;
        cin>>inlsbn;
    cout<<"������۸�"<<endl;
        cin>>inPrice;
    cout<<"����������"<<endl;
        cin>>inAuthor;
    CBook book(inName,inlsbn,inPrice,inAuthor) ;
    book.WriteData();
    cout<<"Write Finish"<<endl;
    WaitUser();
}


void DeleteBookFromeFile() {
    int iDelCount;
    cout<<"Input delete index"<<endl;
    cin>>iDelCount;
    CBook tmpbook;
    tmpbook.DeleteData(iDelCount);
    cout<<"Delete Finish"<<endl;
    WaitUser();
}

void WaitView(int);

void ViewData(int iSelPage =1) {
    int iPage =0;
    int iCurPage=0;
    int iDataCount=0;
    char inName[NUM1];
    char inlsbn[NUM1];
    char inPrice[NUM2];
    char inAuthor[NUM2];
    bool blndex=false;
    int iFileLength;
    iCurPage=iSelPage;
    ifstream ifile;
    ifile.open("book.dat",ios::binary) ;
    iFileLength=GetFileLength(ifile);
    iDataCount=iFileLength/(NUM1+NUM1+NUM2+NUM2);
    if(iDataCount>=1) {
        blndex=true;
    }
    iPage=iDataCount/20+1;
    ClearScreen();
    cout<<"���м�¼"<<iDataCount<<" ";
    cout<<"����ҳ��"<<iPage<<" ";
    cout<<"��ǰҳ��"<<iCurPage<<" ";
    cout<<"n��ʾ��һҳ  m����"<<endl;
    cout<<setw(5)<<"Index";
    cout<<setw(22)<<"Name"<<setw(22)<<"lsbn";
    cout<<setw(15)<<"Price"<<setw(15)<<"Author";
    cout<<endl;
    try{
        ifile.seekg((iCurPage-1)*20*(NUM1+NUM1+NUM2+NUM2),ios::beg);
        if(!ifile.fail() ){//
            for(int i=1;i<21;i++) {
                memset(inName,0,128);
                memset(inlsbn,0,128);
                memset(inPrice,0,50);
                memset(inAuthor,0,50);
                if(blndex) {
                    cout<<setw(3)<<((iCurPage-1)*20+i);
                }
                ifile.read(inName,NUM1);
                cout<<setw(24)<<inName;
                ifile.read(inlsbn,NUM1);
                cout<<setw(24)<<inlsbn;
                ifile.read(inPrice,NUM2);
                cout<<setw(24)<<inPrice;
                ifile.read(inAuthor,NUM2);
                cout<<setw(24)<<inAuthor;
                cout<<endl;
                if(ifile.tellg()<0){
                    blndex = false;
                }
                else 
                    blndex=true;
            }
        }
    }
    catch(...) {
        cout<<"throw file expection"<<endl;
        throw "file error occurred";
        ifile.close();
    }
    if(iCurPage<iPage){
        iCurPage=iCurPage+1;
        WaitView(iCurPage);
    }
    else{
        WaitView(iCurPage);
    }
    ifile.close();
}

void mainloop(){
    ShowWelcom();
    while(1) {
        ClearScreen();
        ShowWelcom();
        ShowRootMenu();
        switch(GetSelect()) {
            case 1:
                ClearScreen();
                GuideInput();
                break;
            case 2:
                ClearScreen();
                ViewData();      //
                break;
            case 3:
                ClearScreen();
                DeleteBookFromeFile();
                break;
        }
    }
}

void WaitView(int iCurPage) {
    char buf[256];
    gets(buf);
    if(buf[0]=='q') {
        system("exit");
    }
    if(buf[0]=='m')
        mainloop();
    if(buf[0]=='n')
        ViewData(iCurPage);
}

int main(){
    SetScreenGrid();
    SetSysCaption("ͼ�����ϵͳ");
    mainloop();
    return 0;
}
