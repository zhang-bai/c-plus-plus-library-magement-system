#include"Book.h"
#include<cstring>
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
        ofile.close();
    }
    ofile.close();
}

void CBook::GetBookFromFile(int iCount){
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
            * 
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
        if(ifile.tellg()>0)
            strncpy(m_cAuthor,cAuthor,NUM2);
    }
    catch(...) {
        throw"file error occurred";
        ifile.close();
    }
    ifile.close();
}

void CBook::DeleteData(int iCount) {
    long respos;
    int iDataCount=0;
    fstream file;
    fstream tmpfile;
    ofstream ofile;
    char cTempBuf[NUM1+NUM1+NUM2+NUM2];
    file.open("book.dat",ios::binary|ios::in|ios::out);
    tmpfile.open("temp.dat",ios::binary|ios::in|ios::out|ios::trunc);
    /*
    fstream对象可以同时具有ifstream和ofstream的功能
    常见的打开模式:
    ios::in–打开一个可读取文件
    ios::out–打开一个可写入文件
    ios:binary –以二进制的形式打开一个文件。
    ios::app –写入的所有数据将被追加到文件的末尾
    ios::trunk –删除文件原来已存在的内容
    ios::nocreate –如果要打开的文件并不存在，那么以此叁数调用open函数将无法进行。
    ios:noreplece –如果要打开的文件已存在，试图用open函数打开时将返回一个错误。
    */
    file.seekg(0,ios::end);
    respos=file.tellg();
    iDataCount=respos/(NUM1+NUM1+NUM2+NUM2);  //  图书记录数量
    if (iCount<0 && iCount > iDataCount) {
        throw "Input number error";
    }
    else {
        file.seekg((iCount)*(NUM1+NUM1+NUM2+NUM2),ios::beg);
        for(int j=0;j<(iDataCount - iCount);j++){
            memset(cTempBuf,0,NUM1+NUM1+NUM2+NUM2);
            file.read(cTempBuf,NUM1+NUM1+NUM2+NUM2);
            tmpfile.write(cTempBuf,NUM1+NUM1+NUM2+NUM2);
        }
        file.close();
        tmpfile.seekg(0,ios::beg);
        ofile.open("book.dat");
        ofile.seekp((iCount-1)*(NUM1+NUM1+NUM2+NUM2),ios::beg);
        /*
        seekp：设置输出文件流的文件流指针位置
        seekg：设置输入文件流的文件流指针位置
        */
        for(int i=0;i<(iDataCount - iCount);i++) {
            memset(cTempBuf,0,NUM1+NUM1+NUM2+NUM2);
            tmpfile.read(cTempBuf,NUM1+NUM1+NUM2+NUM2);
            ofile.write(cTempBuf,NUM1+NUM1+NUM2+NUM2);
        }
    }
    tmpfile.close();
    ofile.close();
    remove("temp.dat");
}



