#include"Book.h"
#include<string.h>
#include<fstream>
#include<iostream>
#include<iomanip>
using namespace std;
CBook::CBook(char *cName,char*clsbn,char*cPrice,char*cAuthor){
    strncpy(m_cName,cName,NUM1);
    strncpy(m_clsbn,clsbn,NUM1);
    strncpy(m_cPrice,cPrice,NUM2);
    strncpy(m_cAuthor,cAuthor,NUM2);
}

char * CBook ::GetName() {
    return m_cName;
}
void CBook::SetName(char* cName) {
    strncpy(m_cName,cName,NUM1);
} 
char * CBook::Getlsbn () {
    return m_clsbn;
}
void CBook::Setlsbn(char*clsbn){
    strncpy(m_clsbn,clsbn,NUM1);
}
char * CBook ::GetPrice() {
    return m_cPrice;
}
void CBook::SetPrice(char* cPrice ) {
    strncpy(m_cPrice,cPrice,NUM2);
} 
char * CBook ::GetAuthor() {
    return m_cAuthor;
}
void CBook::SetAuthor(char* cAuthor) {
    strncpy(m_cAuthor,cAuthor,NUM2);
} 

void CBook::WriteData() {
    ofstream ofile;            //从内存到硬盘
    ofile.open("book.dat",ios::binary|ios::app); 
    try {
        ofile.write(m_cName,NUM1);
        ofile.write(m_clsbn,NUM1);
        ofile.write(m_cPrice,NUM2);
        ofile.write(m_cAuthor,NUM2);
    }
    catch(...) {
        throw "file error occurred" ;
        ofile.close;
    }
    ofile.close;
}

void CBook::GetBookFromFIle(int iCount){
    char cName[NUM1];
    char clsbn[NUM1];
    char cPrice[NUM2];
    char cAuthor[NUM2];
    ifstream ifile;        //从硬盘到内存
    ifile.open("book.dat",ios::binary);
    try {
        ifile.seekg(iCount* (NUM1 + NUM1+NUM2 +NUM2),ios::beg);
            /*
            * seekg 对输入文件定位，有两个参数：
            * 第一个：表示偏移量，可正可负，正表示向后，负表示向前
            * 第二个：偏移的基地址，可以是：
            * ios::beg 输入流的开始
            * ios::cur 输入流的当前位置
            * ios::end 输入流的结束
            * tellg（）函数不需要带参数，它返回当前定位指针的位置，也代表着输入流的大小。
            */
        ifile.read(cName,NUM1);
        if(ifile.tellg()>0 ) {
            strncpy(m_cName,cName,NUM1);
        }
        ifile.read(clsbn,NUM1);
        if(ifile.tellg()>0) 
            strncpy(m_clsbn,clsbn,NUM1);
        ifile.read(cPrice,NUM2) ;
        if(ifile.tellg() > 0) 
            strncpy(m_cPrice,cPrice,NUM2);
        ifile.read(cAuthor,NUM2);
        if(ifile.tellg>0)
            strncpy(m_cAuthor,cAuthor,NUM2);
    }
    catch(...) {
        throw"file error occurred";
        ifile.close();
    }
    ifile.close();
}

void CBook::DeleteData() {
    xxxxxxxx
}
