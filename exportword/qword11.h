/**************************************************************************/
/*		wzq����������2014.4.28											  */
/**************************************************************************/
#ifndef QWORD_H
#define QWORD_H

//#include "stdafx.h"

#include <QMainWindow>
#include <QString>
#include <QVariant>
#include <QAxObject>
#include <QAxWidget>
#include <QDateTime>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QTextCodec>
#include <QtCore>
#include <QDir>
#include <Common/applist.h>
#include <protocal.h>
#include <Database/cmddata.h>
#include <QStringList>
#include <QApplication>
#include <QtCore>
#include <QMessageBox>


class QWord : public QObject
{
	Q_OBJECT

public:
	QWord(QObject *parent = 0);
	~QWord();

public:
	QAxObject* getDocuments(){return m_documents;}
	QAxObject* getDocument(){return m_document;}
	QAxObject* getWordApp(){return m_word;}	
public:
	/**************************************************************************/
	/* �ļ�   ����                                                            */
	/**************************************************************************/
	void save();				//�����������	
	void close();				//�ر� �˳� ����ʱ��Ҳ���Զ�����һ��
	void saveAs();				//�½�excel���Ϊ
	bool createNewWord();		//����һ���µ�excel
	void openWord();			//��һ�����е�excel
	bool createNewWord(const QString& filePath );		//����һ���µ�excel

	void setTableAutoFitBehavior(int flag);				//����Զ������� 0�̶�  1�������ݵ���  2 ���ݴ��ڵ���
	void setPageOrientation(int flag);					//����ҳ��0Ϊ����wdOrientPortrait  1Ϊ����wdOrientLandscape 
	void setWordPageView(int flag);						//����ҳ����ͼ����web��ͼwdWebView 6����ҳ����ͼwdPrintView 3 �����Ķ���ͼwdReadingView 7
	void setFontSize(int fontsize);						//���������С
	void setFontName(QString& fontName);				//��������	���� �����塱
	void setFontBold(bool flag);						//����Ӵ�
	void setParagraphAlignment(int flag);				//����ѡ��λ�����־��� 0 ,���� 1,���� 2
	void setColumnWidth(int column, int width);			//�����п�
    void setRowWidth(int row, int width);		//�����п�
	void setCellString(int row, int column, const QString& text);	
	void setCellFontBold(int row, int column, bool isBold);			//�������ݴ���  isBold�����Ƿ����
	void setCellFontSize(int row, int column, int size);			//�������ִ�С
	void setOptionCheckSpell(bool flags);							//�������ĵ�ƴд���  true�������  false ȡ����� 

	QString GetText();												//��ȡ����
	void getUsedRange(int *topLeftRow, int *topLeftColumn, int *bottomRightRow, int *bottomRightColumn);
	void setSelectionRange(int start,int end);						//"SetRange(1, 9)"��1���ַ���ʼ������9���ַ�������Χ
	QVariant getCellValue(int row, int column);						//��ȡ��Ԫ������ 
	int getTableCount();											//��ȡword�б������	


	QString getStrErrorInfo(){return m_strError;}					//��ȡ�����г��ֵĴ�����Ϣ������QMessageBox::information��ӡ ��cpp����QMessageBox �����������߳��е���������  
	void deleteSelectColumn(int column);							//ɾ��ָ������
	void moveForEnd();												//�ƶ�ѡ�������ĵ�ĩβ
	void insertCellPic(int row,int column,const QString& picPath);	//��Ԫ�����ͼƬ
	void intsertTable(int row,int column);							//����һ�����м��б��
	void insertMoveDown();											//����س�
	void insertText(const QString& text);							//��������
	//����Ѳ�쵥λ  Ѳ��ƻ� Ѳ��ʱ�� Ѳ �� ��  ˳�򴫲�
    void insertTitle(const QString& str1,const QString& str2,const QString& str3,const QString& str4);

    void MergeCell(int row1, int column1, int row2,int column2);    //�ϲ�word��Ԫ��

    void showSafewordinfo(QString ,QString,QString,QString);

    void showinfo();

private:
	QAxObject* m_word;
	QAxObject* m_documents;	
	QAxObject* m_document;	
	QString  m_fileName;
	QString  m_saveName;
	QString  m_strError;

};

#endif // QWORD_H
