//#include "stdafx.h"
#include "qword.h"

QWord::QWord(QObject *parent)
{		
	m_word = new QAxObject(parent); 			
	m_documents = NULL;
	m_document = NULL;	
}

QWord::~QWord()
{
	close();
}

bool QWord::createNewWord()		//����һ���µ�word
{
    QString defaultFileName = QStringLiteral("����¼%1").arg(QDateTime::currentDateTime().toString("yyyyMMddhhmmss"));
    QFileDialog filedialong;
    m_saveName=filedialong.getSaveFileName(0,QStringLiteral("����¼"),defaultFileName,tr("*.doc"));
	QFile file(m_saveName);
	if(file.exists())
	{
        m_strError += QStringLiteral("Ŀ���ļ��Ѿ����ڣ�������������");
		return false;
	}
	if(!m_saveName.isEmpty())
	{		
		if(!m_word->setControl("Word.Application"))
		{
            m_strError += QStringLiteral("���󣺻�ȡword���ʧ�ܣ���ȷ���Ƿ�װ��word!");
			return false;
		}
		m_word->setProperty("Visible",false);
		m_word->setProperty("DisplayAlerts", false);//����ʾ�κξ�����Ϣ�����Ϊtrue��ô�ڹر��ǻ�������ơ��ļ����޸ģ��Ƿ񱣴桱����ʾ
		m_documents = m_word->querySubObject("Documents");
		m_documents->dynamicCall("Add (void)");
		m_document = m_word->querySubObject("ActiveDocument");//��ȡ��ǰ������ĵ� 	
		return true;
	}else
	{
        m_strError += QStringLiteral("�����ļ���Ϊ��");
		return false;
	}

    if(filedialong.exec() == QFileDialog::Rejected)
    {
       this->close();
       filedialong.close();
    }
}
bool QWord::createNewWord(const QString& filePath )
{	
	m_saveName = filePath;
	QFile file(m_saveName);
	if(file.exists())
	{
		m_strError += "����Ŀ���ļ��Ѵ���!";			
		return false;
	}
	if(!m_saveName.isEmpty())
	{		
		if(!m_word->setControl("Word.Application"))
		{
			m_strError += "���󣺻�ȡword���ʧ�ܣ���ȷ���Ƿ�װ��word!\n";
			return false;
		}
		m_word->setProperty("Visible",false);
		m_word->setProperty("DisplayAlerts", false);//����ʾ�κξ�����Ϣ�����Ϊtrue��ô�ڹر��ǻ�������ơ��ļ����޸ģ��Ƿ񱣴桱����ʾ
		m_documents = m_word->querySubObject("Documents");
		if(!m_documents)
		{
			m_strError += "��ȡ�ĵ�ʧ�ܣ�\n";
			return false;
		}
		m_documents->dynamicCall("Add (void)");
		m_document = m_word->querySubObject("ActiveDocument");//��ȡ��ǰ������ĵ� 	
		return true;
	}else
	{
		m_strError += "�����ļ���Ϊ��";		
		return false;
	}
}
void QWord::save()	
{
	if(m_document)
		m_document->dynamicCall("Save()");
	else
		return;
}
void QWord::close()				//�ر� �˳� ����ʱ��Ҳ���Զ�����һ��
{
	if(!m_saveName.isEmpty())		//�����Ϊ��  ��Ϊ�½�   
	{
		saveAs();
		m_saveName = "";
	}
	if(m_document)
		m_document->dynamicCall("Close (boolean)",false);
	if(m_word)	
		m_word->dynamicCall("Quit (void)");	
	if(m_documents)
		delete m_documents;	
	if(m_word)
		delete m_word;	
	m_document = NULL;
	m_documents = NULL;
	m_word = NULL;
}
void QWord::saveAs()				
{
	if(m_document)
		m_document->dynamicCall("SaveAs(const QString&)",QDir::toNativeSeparators(m_saveName));	
	else
		return;
}

void QWord::setPageOrientation(int flag)	//����ҳ��1 ������ 0����
{	
	QAxObject* selection = m_word->querySubObject("Selection");	
	QString page;
	switch (flag)
	{
	case 0:
		page = "wdOrientPortrait";
		break;
	case 1:
		page = "wdOrientLandscape";
		break;
	}
	selection->querySubObject("PageSetUp")->setProperty("Orientation",page);
}
void QWord::setWordPageView(int flag)		
{
	QAxObject* viewPage = m_word->querySubObject("ActiveWindow");
	QString view;
	switch (flag)
	{
	case 1:
		view = "wdNormalView";
		break;
	case 2:
		view = "wdOutlineView";
		break;
	case 3:
		view = "wdPrintView";
		break;
	case 4:
		view = "wdPrintPreview";
		break;
	case 5:
		view = "wdMasterView";
		break;
	case 6:
		view = "wdWebView";
		break;
	case 7:
		view = "wdReadingView";
		break;
	case 8:
		view = "wdConflictView";
		break;
	}	
	viewPage->querySubObject("View")->setProperty("Type",view);
}
void QWord::insertMoveDown()				//����س�
{
	QAxObject* selection  = m_word->querySubObject("Selection");	
	selection->dynamicCall("TypeParagraph(void)");	
}
void QWord::insertText(const QString& text)
{
	QAxObject* selection  = m_word->querySubObject("Selection");	
	selection->dynamicCall("TypeText(const QString&)",text);		
}

QString QWord::GetText()
{
	QAxObject* selection = m_word->querySubObject("Selection");	
	QString str = selection->dynamicCall("GetText(void)").toString();	
	return str;
}
void QWord::setParagraphAlignment(int flag)
{
	QAxObject* selection = m_word->querySubObject("Selection");	
	if(flag == 0)
	{
		selection->querySubObject("ParagraphFormat")->setProperty("Alignment","wdAlignParagraphCenter");
	}else if(flag == 1)
	{
		selection->querySubObject("ParagraphFormat")->setProperty("Alignment","wdAlignParagraphJustify");
	}else if(flag == 2)
	{
		selection->querySubObject("ParagraphFormat")->setProperty("Alignment","wdAlignParagraphRight");
	}
}
void QWord::setFontSize(int fontsize)		//���������С
{
	QAxObject* selection = m_word->querySubObject("Selection");	
	selection->querySubObject("Font")->setProperty("Size",fontsize);
}
void QWord::setFontBold(bool flag)
{
	QAxObject* selection = m_word->querySubObject("Selection");	
	selection->querySubObject("Font")->setProperty("Bold",flag);
}
void QWord::setFontName(QString& fontName)
{
	QAxObject* selection = m_word->querySubObject("Selection");	
	selection->querySubObject("Font")->setProperty("Name",fontName);
}
void QWord::setSelectionRange(int start,int end)
{
	QAxObject* selection = m_word->querySubObject("Selection");	
	selection->dynamicCall("SetRange(int, int)", start,end);	//��1���ַ���ʼ������9���ַ�������Χ
}
void QWord::getUsedRange(int *topLeftRow, int *topLeftColumn, int *bottomRightRow, int *bottomRightColumn)
{
	QAxObject* range = m_document->querySubObject("Range");
	*topLeftRow = range->property("Row").toInt();
	*topLeftColumn = range->property("Column").toInt();

	QAxObject *rows = range->querySubObject("Rows");
	*bottomRightRow = *topLeftRow + rows->property("Count").toInt() - 1;

	QAxObject *columns = range->querySubObject("Columns");
	*bottomRightColumn = *topLeftColumn + columns->property("Count").toInt() - 1;
}
void QWord::intsertTable(int row,int column)
{	

	QAxObject* tables = m_document->querySubObject("Tables");	
	QAxObject* selection = m_word->querySubObject("Selection");	
	QAxObject* range = selection->querySubObject("Range");
	QVariantList params;
	params.append(range->asVariant());		
	params.append(row);
	params.append(column);	
	tables->querySubObject("Add(QAxObject*, int, int, QVariant&, QVariant&)", params);
	QAxObject* table = selection->querySubObject("Tables(1)");
	table->setProperty("Style","������");

//    table->querySubObject("ParagraphFormat")->setProperty("Alignment","wdAlignParagraphCenter");
//   table->querySubObject("ParagraphFormat")->setProperty("HorizontalAlignment", "Parent"); //����루xlLeft����-4131  ���У�xlCenter����-4108  �Ҷ��루xlRight����-4152
//    table->setProperty("VerticalAlignment", -4108);  //�϶��루xlTop��-4160 ���У�xlCenter����-4108  ��

//    setParagraphAlignment(0);
}
void QWord::setColumnWidth(int column, int width)		//�����п�
{
	QAxObject* selection = m_word->querySubObject("Selection");	
	QAxObject* table = selection->querySubObject("Tables(1)");
	table->querySubObject("Columns(int)",column)->setProperty("Width",width);
}

void QWord::setRowWidth(int row, int width)		//�����п�
{
    QAxObject* selection = m_word->querySubObject("Selection");
    QAxObject* table = selection->querySubObject("Tables(1)");
    table->querySubObject("Rows(int)",row)->setProperty("Width",width);
}

void QWord::setCellString(int row, int column, const QString& text)
{
    //setParagraphAlignment(0);
	QAxObject* selection = m_word->querySubObject("Selection");	
	QAxObject* table = selection->querySubObject("Tables(1)");	
	table->querySubObject("Cell(int, int)",row,column)->querySubObject("Range")->dynamicCall("SetText(QString)", text);
}
void QWord::MergeCell(int row1, int column1, int row2,int column2)    //�ϲ�word��Ԫ��
{


//    AxObject *merge_range = work_sheet->querySubObject("Range(const QString&)", merge_cell);
//    merge_range->setProperty("HorizontalAlignment", -4108);
//    merge_range->setProperty("VerticalAlignment", -4108);
//    merge_range->setProperty("WrapText", true);
//    merge_range->setProperty("MergeCells", true);  //�ϲ���Ԫ��
    QAxObject* selection = m_word->querySubObject("Selection");
    QAxObject* table = selection->querySubObject("Tables(1)");

    QVariantList params;
    params.append(row1);
    params.append(row2);
    params.append(column1);
    params.append(column2);

    table->querySubObject("Rows(int)", row1)->setProperty("MergeRows", true);  //�ϲ���Ԫ��

}

void QWord::setCellFontBold(int row, int column, bool isBold)	//�������ݴ���  isBold�����Ƿ����
{
	QAxObject* selection = m_word->querySubObject("Selection");	
	QAxObject* table = selection->querySubObject("Tables(1)");
	table->querySubObject("Cell(int, int)",row,column)->querySubObject("Range")->dynamicCall("SetBold(int)", isBold);
}
void QWord::setCellFontSize(int row, int column, int size)		//�������ִ�С
{
	QAxObject* selection = m_word->querySubObject("Selection");	
	QAxObject* table = selection->querySubObject("Tables(1)");
	table->querySubObject("Cell(int, int)",row,column)->querySubObject("Range")->querySubObject("Font")->setProperty("Size", size);	
}
QVariant QWord::getCellValue(int row, int column)					//��ȡ��Ԫ������ �˴�����Excel��˵�к��д�1��ʼ����
{
	QAxObject* selection = m_word->querySubObject("Selection");	
	QAxObject* table = selection->querySubObject("Tables(1)");
	return table->querySubObject("Cell(int, int)",row,column)->querySubObject("Range")->property("Text");	
}
int QWord::getTableCount()
{
	QAxObject* tables = m_document->querySubObject("Tables");	
	int val = tables->property("Count").toInt();
	return val;
}
void QWord::moveForEnd()
{
	QAxObject* selection = m_word->querySubObject("Selection");	
	QVariantList params;
	params.append(6);		
	params.append(0);		
	selection->dynamicCall("EndOf(QVariant&, QVariant&)", params).toInt();
}
void QWord::insertCellPic(int row,int column,const QString& picPath)
{
	QAxObject* selection = m_word->querySubObject("Selection");	
	QAxObject* table = selection->querySubObject("Tables(1)");
	QAxObject* range = table->querySubObject("Cell(int, int)",row,column)->querySubObject("Range");
	range->querySubObject("InlineShapes")->dynamicCall("AddPicture(const QString&)",picPath);
}
void QWord::setTableAutoFitBehavior(int flag)
{
	QAxObject* selection = m_word->querySubObject("Selection");	
	QAxObject* table = selection->querySubObject("Tables(1)");
	if(0 <= flag & flag <= 2 )
		table->dynamicCall("AutoFitBehavior(WdAutoFitBehavior)", flag);
}
void QWord::deleteSelectColumn(int column)
{
	QAxObject* selection = m_word->querySubObject("Selection");	
	QAxObject* table = selection->querySubObject("Tables(1)");
	QAxObject* columns = table->querySubObject("Columns(int)",column);	
	columns->dynamicCall("Delete()");
}
void QWord::insertTitle(const QString& str1,const QString& str2,const QString& str3,const QString& str4)
{
	setPageOrientation(1);			//ҳ�����
    setWordPageView(7);				//ҳ����ͼ
	setFontSize(25);				//�����С	
	setParagraphAlignment(0);		//������������
	setFontBold(true);				//����Ӵ�
    insertText(QString("�ֻ���ȫ��ⱨ��"));//��������
    setFontBold(true);				//����ȡ���Ӵ�
	insertMoveDown();				//�س�����
	setParagraphAlignment(1);		//������������
	setFontSize(14);
	insertText(QString("Ѳ�쵥λ��%1").arg(str1));//��������	
	insertMoveDown();	
	insertText(QString("Ѳ��ƻ���%1").arg(str2));//��������	
	insertMoveDown();		
	insertText(QString("Ѳ��ʱ�䣺%1").arg(str3));//��������	
	insertMoveDown();	
	insertText(QString("Ѳ �� �ˣ�%1").arg(str4));//��������	
	insertMoveDown();	
	setFontSize(12);
	setParagraphAlignment(0);		//������������
	insertText(QString("Ѳ����ͳ�Ʊ�"));
	insertMoveDown();	
}
void QWord::setOptionCheckSpell(bool flags)
{
	QAxObject* opetions = m_word->querySubObject("Options");	
	if(!opetions)
		return;
	opetions->setProperty("CheckGrammarAsYouType",flags);
	opetions->setProperty("CheckGrammarWithSpelling",flags);
	opetions->setProperty("ContextualSpeller",flags);
	opetions->setProperty("CheckSpellingAsYouType",flags);
}


void QWord::showinfo()
{
    qDebug()<<"{rtgtyyhyjryjrtjhnrt";
}

void QWord::showSafewordinfo(QString unit,QString name, QString phone, QString detail)
{

    QWord word;
    QString msg;
    QStringList AllInfo;
    int percount;
    QStringList perInfoList;

    QTextCodec *codec = QTextCodec::codecForName("utf-8");
    QTextCodec::setCodecForLocale(codec);

    QString path = QDir::currentPath();//��ǰ·��
    qDebug() << path<<"frfggef";

    //word���ⲿ��

    word.createNewWord();
    word.setPageOrientation(0);			//ҳ�����
    word.setWordPageView(1);			//ҳ����ͼ

    word.setFontSize(20);				//�����С
    word.setParagraphAlignment(0);		//������������
    word.setFontBold(true);				//����Ӵ�
    word.insertText(QStringLiteral("�ֻ���ȫ��ⱨ��"));//��������


    //�������Ĳ���
    word.setFontBold(false);			//����bu��cu
    word.insertMoveDown();
    word.insertMoveDown();

    word.setFontBold(true);
    word.setParagraphAlignment(1);		//������������
    word.setFontSize(15);
    word.insertText(QStringLiteral("1.������˻�����Ϣ:"));//��������
    word.insertMoveDown();

    word.setFontSize(10);
    word.setFontBold(false);
    word.setParagraphAlignment(0);		//������������
    word.intsertTable(2,3);			//���м���table
    word.setColumnWidth(1,160);
    word.setColumnWidth(2,160);
    word.setColumnWidth(3,160);

    word.setCellString(1,1,QStringLiteral("��λ"));
    word.setCellString(1,2,QStringLiteral("����"));
    word.setCellString(1,3,QStringLiteral("�ֻ���"));

    //word.setCellString(2,1,QStringLiteral("�侯�ܶ�"));
    word.setCellString(2,1,unit);

    //word.setCellString(2,2,QStringLiteral("�"));
    word.setCellString(2,2,name);


    //word.setCellString(2,3,QStringLiteral("18234095185"));
    word.setCellString(2,3,phone);

    word.setTableAutoFitBehavior(2);
    word.moveForEnd();
    word.insertMoveDown();

    word.setParagraphAlignment(1);		//������������
    word.intsertTable(2,2);			//���м���table
    word.setColumnWidth(1,160);
    word.setColumnWidth(2,320);
    word.setCellString(1,1,QStringLiteral("��ע:"));
    word.setCellString(1,2,detail);
    word.setCellString(2,1,QStringLiteral("��ά��:"));
    //word.insertCellPic(2,2,QStringLiteral("123.jpg"));

    word.insertCellPic(2,2,"D:/temp/123.jpg");
    word.setTableAutoFitBehavior(2);
    word.moveForEnd();
    word.insertMoveDown();

    //��������
    word.setFontBold(true);
    word.setParagraphAlignment(1);		//������������
    word.setFontSize(15);
    word.insertText(QStringLiteral("2.��������"));//��������
    word.insertMoveDown();
    word.setFontBold(false);
    word.setParagraphAlignment(1);		//������������

    word.setFontSize(10);
    int num1 = AppList::AppNameList.count();
    int num2 = AppList::riskcount;
    int num3 = num1 - num2;
    QString str1 =  QStringLiteral("   ���ι����(%1)��Ӧ�ã���������Ӧ��(%2)��,��ȫӦ��(%3)����").arg(QString::number(num1).arg(QString::number(num2)).arg(QString::number(num3)));
    word.insertText(str1);//��������
    word.insertMoveDown();
    word.insertMoveDown();

    //�ֻ�������Ϣ
    word.setFontBold(true);
    word.setParagraphAlignment(1);		//������������
    word.setFontSize(15);
    word.insertText(QStringLiteral("3.�ֻ�������Ϣ��"));//��������
    word.insertMoveDown();

    word.setFontBold(false);
    word.setParagraphAlignment(0);		//����������zhong
    word.setFontSize(10);
    word.intsertTable(5,4);			//���м���table
    word.setColumnWidth(1,110);
    word.setColumnWidth(2,110);
    word.setColumnWidth(3,110);
    word.setColumnWidth(4,110);

    QString mobileiInfoilist = AppList::mobileinfo.split(MSG_DATA_ITEMS_SEPARATOR);

    word.setCellString(1,1,QStringLiteral("�ֻ��ͺţ�"));
    word.setCellString(1,2,mobileiInfoilist.at(0));
    word.setCellString(1,3,QStringLiteral("�����̣�"));
    word.setCellString(1,4,mobileiInfoilist.at(2));

    word.setCellString(2,1,QStringLiteral("����ϵͳ��"));
    word.setCellString(2,2,mobileiInfoilist.at(1));
    word.setCellString(2,4,mobileiInfoilist.at(3));
    word.setCellString(2,3,QStringLiteral("ϵͳ�汾��"));

    word.setCellString(3,1,QStringLiteral("SDK�汾��"));
    word.setCellString(3,2,mobileiInfoilist.at(4));
    word.setCellString(3,3,QStringLiteral("Ψһ�룺"));
    word.setCellString(3,4,mobileiInfoilist.at(2));

    word.setCellString(4,1,QStringLiteral("CPU�ͺţ�"));
    word.setCellString(4,2,mobileiInfoilist.at(5));
    word.setCellString(4,3,QStringLiteral("MAC��ַ��"));
    word.setCellString(4,4,mobileiInfoilist.at(6));

    word.setCellString(5,1,QStringLiteral("�Ƿ�Root��"));
    word.setCellString(5,2,mobileiInfoilist.at(8));
    word.setCellString(5,3,QStringLiteral("��Ӫ�̣�"));
    word.setCellString(5,4,mobileiInfoilist.at(7));

    word.setTableAutoFitBehavior(4);
    word.moveForEnd();
    word.insertMoveDown();

    //Σ��Ӧ����Ϣ
    word.setFontBold(true);
    word.setParagraphAlignment(1);		//������������
    word.setFontSize(15);
    word.insertText(QStringLiteral("4.Σ��Ӧ����Ϣ(�� %1 ��)").arg(AppList::riskcount));//��������
    word.insertMoveDown();

    for(int i = 1; i < AppList::AppPackageList.count()+1;i++)
    {
        word.setFontSize(12);
        word.insertText(QStringLiteral("4.%1  %2").arg(QString::number(i)).arg(AppList::AppNameList.at(i-1)));//��������
        word.insertMoveDown();
        word.insertMoveDown();
        word.setFontSize(10);
        word.insertText(QStringLiteral("1) ������Ϣ"));//��������
        word.insertMoveDown();
        //word.insertMoveDown();

        word.setFontBold(false);
        word.setParagraphAlignment(0);		//������������
        word.intsertTable(3,4);			//���м���table
        word.setColumnWidth(1,110);
        word.setColumnWidth(2,110);
        word.setColumnWidth(3,110);
        word.setColumnWidth(4,110);

        word.setCellString(1,1,QStringLiteral("Ӧ����:"));
        word.setCellString(1,2,AppList::AppNameList.at(i - 1));
        word.setCellString(1,3,QStringLiteral("������"));
        word.setCellString(1,4,AppList::AppPackageList.at(i - 1));
        word.setCellString(2,1,QStringLiteral("�汾�ţ�"));
        word.setCellString(2,2,mobileiInfoilist.at(4));
        word.setCellString(2,3,QStringLiteral("Ӧ����Դ��"));
        word.setCellString(2,2,QStringLiteral("�û���װ"));
        word.setCellString(3,1,QStringLiteral("������ʱ�䣺"));
        word.setCellString(3,3,QStringLiteral("��װʱ�䣺"));

        word.setTableAutoFitBehavior(4);
        word.moveForEnd();
        word.insertMoveDown();

        word.setParagraphAlignment(1);		//������������
        word.setFontBold(true);
        word.insertText(QStringLiteral("2) Σ������"));//��������
        word.insertMoveDown();
        word.setFontBold(false);

        msg =  AppList::ApkPermission[i-1];
        AllInfo = msg.split(MSG_CHECKOUT);
        qDebug()<<msg<<AllInfo.count()<<"uuuuu";
        QString permissonInfo = AllInfo.at(2);
        QString vires = AllInfo.at(1);

        perInfoList = permissonInfo.split(MSG_DATA_ITEMS_SEPARATOR);
        percount = perInfoList.count();
        for(int i = 0; i < percount - 1; i++)
        {
            word.insertText(perInfoList.at(i));//��������
            word.insertMoveDown();

        }
         word.insertMoveDown();
         word.setFontBold(true);
         word.insertText(QStringLiteral("3) ӵ��Ȩ��"));//��������
         word.insertMoveDown();

         word.setFontBold(false);
         word.setParagraphAlignment(1);		//������������
         word.intsertTable(percount,4);			//���м���table

         word.setColumnWidth(1,110);
         word.setColumnWidth(2,110);
         word.setColumnWidth(3,110);
         word.setColumnWidth(4,110);

       for(int i = 1; i < percount+1;i++)
       {

           word.setCellString(i,1,QString::number(i));
           QStringList detailinfo = cmdData::selectperdetail(perInfoList.at(i-1));
           qDebug()<<detailinfo.count()<<"jjjjj";
           word.setCellString(i,2,detailinfo.at(0));
           word.setCellString(i,3,perInfoList.at(i-1));
           word.setCellString(i,4,detailinfo.at(1));
           word.setTableAutoFitBehavior(4);
           word.moveForEnd();
           word.insertMoveDown();
       }

        word.setParagraphAlignment(1);
        word.setFontBold(true);
        word.insertText(QStringLiteral("4)Ӧ���漰������� "));//��������
        word.insertMoveDown();
        word.setFontBold(false);
        QStringList virus = vires.split(MSG_DATA_ITEMS_SEPARATOR);
        int vcount = virus.count();
        if(vcount == 1)
        {
            word.insertText(QStringLiteral("δ���ֲ���Σ��"));//��������
            word.insertMoveDown();

        }else
        {
            for(i = 1 ;i < vcount; i++)
            {
                word.insertText(virus.at(i));//��������
                word.insertMoveDown();

            }

        }

  }
  word.insertMoveDown();
  word.insertMoveDown();
  word.insertMoveDown();
  word.setParagraphAlignment(2);		//������������
  word.setFontSize(14);
  word.setFontBold(false);

  QString defaultFileName = QStringLiteral("���ʱ��: %1").arg(QDateTime::currentDateTime().toString("yyyy.MM.dd"));
  word.insertText(defaultFileName);
  word.insertMoveDown();
  word.insertText(QStringLiteral("����ˣ��侯�ܲ� ����Ա"));
  word.close();

}
