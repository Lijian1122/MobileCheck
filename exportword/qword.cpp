//#include "stdafx.h"
#include "qword.h"
#include <Common/applist.h>
#include <Protocal/protocal.h>
#include <QStringList>
#include <Database/cmddata.h>
#include <QMessageBox>
#include <QDir>
#include <LoginWidget/loginwidget.h>
#include <QDesktopServices>
#include <QCoreApplication>
#include <QProgressBar>

QString QWord::currentpath;
QString QWord::User;
QString QWord::UserPart;
QString QWord::CurrentExportDir;

QWord::QWord(QObject *parent)
{		
	m_word = new QAxObject(parent); 			
	m_documents = NULL;
	m_document = NULL;	

    creatExportForderPre();

    QString path = QDir::currentPath();//当前路径
    qDebug() << path<<"frfggef";

    currentpath = path.append("/QrcodeImage/qrcode.png");

    if(!LoginWidget::userlist.isEmpty())
    {
        User = LoginWidget::userlist.at(0);


        qDebug()<<LoginWidget::userlist.at(2)<<"userinfo";

        if(LoginWidget::userlist.at(2) == QStringLiteral("管理员"))
        {
            UserPart == LoginWidget::userlist.at(2);
        }else
        {
            //UserPart = "";
            UserPart == LoginWidget::userlist.at(2);
        }
    }

}
QWord::~QWord()
{
    close();
}
void QWord::creatExportForderPre()
{

    QString saveFileName= QDir::currentPath();

    QString currentpathPre = saveFileName.append("/").append("Export");

    QDir *temp = new QDir;
    bool exist = temp->exists(currentpathPre);
    if(exist)
    {
       //QMessageBox::warning(this,tr("创建文件夹"),tr("文件夹已经存在！"));
        return;
    }
    else
    {
        bool ok = temp->mkdir(currentpathPre);
        if( ok )
        {
           //QMessageBox::warning(this,tr("创建文件夹"),tr("文件夹创建成功！"));
            return;
        }

    }

}
void QWord::creatExportForder()
{
    QString saveFileName= QDir::currentPath();

    //QString currentpathpre = saveFileName.append("/%1").append("Export");

    QString str1 = saveFileName.append("/Export/");
    currentpath = str1.append(AppList::MobileImei);

    qDebug()<<currentpath<<"jujuujuu";

    QDir *temp = new QDir;
    bool exist = temp->exists(currentpath);
    if(exist)
    {
       //QMessageBox::warning(this,tr("创建文件夹"),tr("文件夹已经存在！"));
        return;
    }
    else
    {
        bool ok = temp->mkdir(currentpath);
        if( ok )
        {
           //QMessageBox::warning(this,tr("创建文件夹"),tr("文件夹创建成功！"));
            return;
        }

    }
}

bool QWord::createNewWord(QString str)		//创建一个新的word
{ 

    creatExportForder();
    QString defaultFileName = QStringLiteral("%1记录%2").arg(str).arg(QDateTime::currentDateTime().toString("yyyyMMddhhmmss"));

    AppList::currentExportDir = currentpath.append("/%1%2").arg(defaultFileName).arg(".doc");

    QFileDialog filedialong;

    //filedialong.setNameFilter(tr("*.doc *.docx"));
    m_saveName =  filedialong.getSaveFileName(0,QStringLiteral("另存为"),AppList::currentExportDir,tr("*.doc"));

        if(!m_saveName.isEmpty())
        {
            QFile file(m_saveName);

            if(file.exists())
            {
                m_strError += QStringLiteral("目标文件已经存在，请重新命名！");
                qDebug()<<m_strError<<"word";
                return false;
            }

            if(!m_word->setControl("Word.Application"))
            {
                m_strError += QStringLiteral("错误：获取word组件失败，请确定是否安装了word!");
                qDebug()<<m_strError<<"word";
                return false;
            }
            m_word->setProperty("Visible",false);
            m_word->setProperty("DisplayAlerts", false);//不显示任何警告信息。如果为true那么在关闭是会出现类似“文件已修改，是否保存”的提示
            m_documents = m_word->querySubObject("Documents");
            m_documents->dynamicCall("Add (void)");
            m_document = m_word->querySubObject("ActiveDocument");//获取当前激活的文档

            //filedialong.close();
            //->close();

            qDebug()<<"grwgfgfefqefqfqefqef";

            return true;
        }else
        {
            qDebug()<<"theethte";

            filedialong.close();
            //this->close();
            return false;
        }

}
//bool QWord::createNewWord(const QString& filePath )
//{
//	m_saveName = filePath;
//	QFile file(m_saveName);
//	if(file.exists())
//	{
//		m_strError += "错误：目标文件已存在!";
//		return false;
//	}
//	if(!m_saveName.isEmpty())
//	{
//		if(!m_word->setControl("Word.Application"))
//		{
//			m_strError += "错误：获取word组件失败，请确定是否安装了word!\n";
//			return false;
//		}
//		m_word->setProperty("Visible",false);
//		m_word->setProperty("DisplayAlerts", false);//不显示任何警告信息。如果为true那么在关闭是会出现类似“文件已修改，是否保存”的提示
//		m_documents = m_word->querySubObject("Documents");
//		if(!m_documents)
//		{
//			m_strError += "获取文档失败！\n";
//			return false;
//		}
//		m_documents->dynamicCall("Add (void)");
//		m_document = m_word->querySubObject("ActiveDocument");//获取当前激活的文档
//		return true;
//	}else
//	{
//		m_strError += "错误：文件名为空";
//		return false;
//	}
//}
void QWord::save(QString str)
{
	if(m_document)
		m_document->dynamicCall("Save()");
	else
		return;
}
void QWord::close()				//关闭 退出 析构时候也会自动调用一次
{
	if(!m_saveName.isEmpty())		//如果不为空  则为新建   
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

void QWord::setPageOrientation(int flag)	//设置页面1 横向还是 0竖向
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
void QWord::insertMoveDown()				//插入回车
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
void QWord::setFontSize(int fontsize)		//设置字体大小
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
	selection->dynamicCall("SetRange(int, int)", start,end);	//第1个字符后开始，到第9个字符结束范围
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
	table->setProperty("Style","网格型");

//    table->querySubObject("ParagraphFormat")->setProperty("Alignment","wdAlignParagraphCenter");
//   table->querySubObject("ParagraphFormat")->setProperty("HorizontalAlignment", "Parent"); //左对齐（xlLeft）：-4131  居中（xlCenter）：-4108  右对齐（xlRight）：-4152
//    table->setProperty("VerticalAlignment", -4108);  //上对齐（xlTop）-4160 居中（xlCenter）：-4108  下

//    setParagraphAlignment(0);
}
void QWord::setColumnWidth(int column, int width)		//设置列宽
{
	QAxObject* selection = m_word->querySubObject("Selection");	
	QAxObject* table = selection->querySubObject("Tables(1)");
	table->querySubObject("Columns(int)",column)->setProperty("Width",width);
}

void QWord::setRowWidth(int row, int width)		//设置行宽
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
void QWord::MergeCell(int row1, int column1, int row2,int column2)    //合并word单元格
{


//    AxObject *merge_range = work_sheet->querySubObject("Range(const QString&)", merge_cell);
//    merge_range->setProperty("HorizontalAlignment", -4108);
//    merge_range->setProperty("VerticalAlignment", -4108);
//    merge_range->setProperty("WrapText", true);
//    merge_range->setProperty("MergeCells", true);  //合并单元格
    QAxObject* selection = m_word->querySubObject("Selection");
    QAxObject* table = selection->querySubObject("Tables(1)");

    QVariantList params;
    params.append(row1);
    params.append(row2);
    params.append(column1);
    params.append(column2);

    table->querySubObject("Rows(int)", row1)->setProperty("MergeRows", true);  //合并单元格

}

void QWord::setCellFontBold(int row, int column, bool isBold)	//设置内容粗体  isBold控制是否粗体
{
	QAxObject* selection = m_word->querySubObject("Selection");	
	QAxObject* table = selection->querySubObject("Tables(1)");
	table->querySubObject("Cell(int, int)",row,column)->querySubObject("Range")->dynamicCall("SetBold(int)", isBold);
}
void QWord::setCellFontSize(int row, int column, int size)		//设置文字大小
{
	QAxObject* selection = m_word->querySubObject("Selection");	
	QAxObject* table = selection->querySubObject("Tables(1)");
	table->querySubObject("Cell(int, int)",row,column)->querySubObject("Range")->querySubObject("Font")->setProperty("Size", size);	
}
QVariant QWord::getCellValue(int row, int column)					//获取单元格内容 此处对于Excel来说列和行从1开始最少
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
	setPageOrientation(1);			//页面横向
    setWordPageView(7);				//页面视图
	setFontSize(25);				//字体大小	
	setParagraphAlignment(0);		//下面文字置中
	setFontBold(true);				//字体加粗
    insertText(QString("手机安全检测报告"));//插入文字
    setFontBold(true);				//字体取消加粗
	insertMoveDown();				//回车换行
	setParagraphAlignment(1);		//下面文字置左
	setFontSize(14);
	insertText(QString("巡检单位：%1").arg(str1));//插入文字	
	insertMoveDown();	
	insertText(QString("巡检计划：%1").arg(str2));//插入文字	
	insertMoveDown();		
	insertText(QString("巡检时间：%1").arg(str3));//插入文字	
	insertMoveDown();	
	insertText(QString("巡 检 人：%1").arg(str4));//插入文字	
	insertMoveDown();	
	setFontSize(12);
	setParagraphAlignment(0);		//下面文字置中
	insertText(QString("巡检结果统计表"));
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


//void QWord::showinfo()
//{
//    qDebug()<<"{rtgtyyhyjryjrtjhnrt";
//}
bool QWord::slotSafeProgresscancel()
{
     qDebug()<<"gggrwg";
     progressDlg->setValue(0);
     progressDlg->close();

     return false;
}

bool QWord::showSafewordinfo(QString unit,QString name, QString phone, QString detail,int row,int score)
{

    QWord word;
    QString msg;
    QStringList AllInfo;
    int percount;
    QStringList perInfoList;
    QTextCodec *codec = QTextCodec::codecForName("utf-8");
    QTextCodec::setCodecForLocale(codec);

    QString path = QDir::currentPath();//当前路径
    qDebug() << path<<"frfggefefqqeffff";

    QString currentpath = path.append("/QrcodeImage/qrcode.png");

    //word标题部分

    //word.createNewWord();
    bool OK =  word.createNewWord(QStringLiteral("安全检测"));
    if(OK == false)
    {
        //this->close();
        return false;
    }

    //QProgressDialog *progressDlg=new QProgressDialog();
    progressDlg=new QProgressDialog();
    //connect(progressDlg,SIGNAL(canceled()),this,SLOT(slotSafeProgresscancel()));

    progressDlg->setFixedSize(300,120);
    //progressDlg->set
    QFont font("ZYSong18030",11);
    progressDlg->setFont(font);
    progressDlg->setWindowModality(Qt::WindowModal);

    QProgressBar *progressbar = new QProgressBar();
    //progressbar->setRange(0,row+5);
    progressDlg->setRange(0,row+5);
    //progressDlg->setFormat("");
//    double dProgress = ( progressDlg->value() -  progressDlg->minimum()) * 100.0
//                    / ( progressDlg->maximum() - progressDlg->minimum());
//    QString str22 = QStringLiteral("当前已完成：");
//    progressbar->setFormat((str22.append("%1%")).arg(QString::number(progressDlg->value()/progressDlg->maximum())));
    progressbar->setAlignment(Qt::AlignRight | Qt::AlignVCenter);  // 对齐方式

    progressDlg->setBar(progressbar);
    QCoreApplication::processEvents();
    progressDlg->setWindowIcon(QIcon("screen/export.png"));
    progressDlg->setMinimumDuration(5);
    progressDlg->setWindowTitle(QStringLiteral("请稍等"));
    progressDlg->setLabelText(QStringLiteral("正在导出中......"));

    progressDlg->setRange(0,row+5);

//    progressDlg->sett

//    progressDlg->Alignment = Qt::AlignCenter;
//            // 设置进度

//            progress = QString("%1%").arg(nProgress);
    progressDlg->setCancelButton(false);
    //progressDlg->setCancelButtonText(QStringLiteral("取消"));
    //QPushButton *cancelbutton = progressDlg->
    progressDlg->setRange(0,row+5);
    progressDlg->show();

    if(progressDlg->wasCanceled())
    {
        progressDlg->close();
        delete &word;
        return false;
        //break;
    }

    word.setPageOrientation(0);			//页面横向
    word.setWordPageView(1);			//页面视图

    word.setFontSize(20);				//字体大小
    word.setParagraphAlignment(0);		//下面文字置中
    word.setFontBold(true);				//字体加粗
    word.insertText(QStringLiteral("手机安全检测报告"));//插入文字


    //下面正文部分
    word.setFontBold(false);			//字体bu加cu
    word.insertMoveDown();
    word.insertMoveDown();

    word.setFontBold(true);
    word.setParagraphAlignment(1);		//下面文字置左
    word.setFontSize(15);
    word.insertText(QStringLiteral("1.被检测人基本信息:"));//插入文字
    word.insertMoveDown();

    word.setFontSize(10);
    word.setFontBold(false);
    word.setParagraphAlignment(0);		//下面文字置左
    word.intsertTable(2,3);			//几行几列table
    word.setColumnWidth(1,160);
    word.setColumnWidth(2,160);
    word.setColumnWidth(3,160);

    word.setCellString(1,1,QStringLiteral("单位"));
    word.setCellString(1,2,QStringLiteral("姓名"));
    word.setCellString(1,3,QStringLiteral("手机号"));

    //word.setCellString(2,1,QStringLiteral("武警总队"));
    word.setCellString(2,1,unit);

    //word.setCellString(2,2,QStringLiteral("李剑"));
    word.setCellString(2,2,name);


    //word.setCellString(2,3,QStringLiteral("18234095185"));
    word.setCellString(2,3,phone);

    word.setTableAutoFitBehavior(2);
    word.moveForEnd();
    word.insertMoveDown();

    word.setParagraphAlignment(1);		//下面文字置左
    word.intsertTable(2,2);			//几行几列table
    word.setColumnWidth(1,160);
    word.setColumnWidth(2,320);
    word.setCellString(1,1,QStringLiteral("备注:"));
    word.setCellString(1,2,detail);
    word.setCellString(2,1,QStringLiteral("二维码:"));
    //word.insertCellPic(2,2,QStringLiteral("123.jpg"));

    //word.insertCellPic(2,2,"D:/temp/123.jpg");

    word.insertCellPic(2,2,currentpath);
    word.setTableAutoFitBehavior(2);
    word.moveForEnd();
    word.insertMoveDown();

    progressDlg->setValue(1);

    //报告结果：
    word.setFontBold(true);
    word.setParagraphAlignment(1);		//下面文字置左
    word.setFontSize(15);
    word.insertText(QStringLiteral("2.报告结果："));//插入文字
    word.insertMoveDown();
    word.setFontBold(false);
    word.setParagraphAlignment(1);		//下面文字置左

    word.setFontSize(10);
    int num1 = AppList::CheckAllApk;
    int num2 = AppList::riskcount;
    int num3 = AppList::Viruscount;
    int num4 = num1 - num2;
    QString str1;


    if(AppList::Viruscount != 0)
    {
        str1 = QStringLiteral("   本次共检查(%1)个应用，发现问题应用(%2)个，安全应用(%3)个，").arg(QString::number(num1)).
                arg(QString::number(num2)).arg(QString::number(num4));

    }else
    {
        str1 =  QStringLiteral("   本次共检查(%1)个应用，发现问题应用(%2)个,安全应用(%4)个，").arg(QString::number(num1)).arg(QString::number(num2)).
                arg(QString::number(num4));
    }

    QString str3 = QStringLiteral("检测得分：%1分。").arg(QString::number(score));

    str1 = str1.append(str3);

    word.insertText(str1);//插入文字
    word.insertMoveDown();
    word.insertMoveDown();

    progressDlg->setValue(2);

    //手机基本信息
    word.setFontBold(true);
    word.setParagraphAlignment(1);		//下面文字置左
    word.setFontSize(15);
    word.insertText(QStringLiteral("3.手机基本信息："));//插入文字
    word.insertMoveDown();

    word.setFontBold(false);
    word.setParagraphAlignment(0);		//下面文字置zhong
    word.setFontSize(10);
    word.intsertTable(5,4);			//几行几列table
    word.setColumnWidth(1,110);
    word.setColumnWidth(2,110);
    word.setColumnWidth(3,110);
    word.setColumnWidth(4,110);


    QStringList mobileiInfoilist = AppList::mobileinfo.split(MSG_DATA_ITEMS_SEPARATOR);

    word.setCellString(1,1,QStringLiteral("手机型号："));
    word.setCellString(1,2,mobileiInfoilist.at(0));
    word.setCellString(1,3,QStringLiteral("制造商："));
    word.setCellString(1,4,mobileiInfoilist.at(2));

    word.setCellString(2,1,QStringLiteral("操作系统："));
    word.setCellString(2,2,mobileiInfoilist.at(1));
    word.setCellString(2,4,mobileiInfoilist.at(3));
    word.setCellString(2,3,QStringLiteral("系统版本："));

    word.setCellString(3,1,QStringLiteral("SDK版本："));
    word.setCellString(3,2,mobileiInfoilist.at(4));
    word.setCellString(3,3,QStringLiteral("唯一码："));
    word.setCellString(3,4,mobileiInfoilist.at(2));

    word.setCellString(4,1,QStringLiteral("CPU型号："));
    word.setCellString(4,2,mobileiInfoilist.at(5));
    word.setCellString(4,3,QStringLiteral("MAC地址："));
    word.setCellString(4,4,mobileiInfoilist.at(6));

    word.setCellString(5,1,QStringLiteral("是否Root："));
    word.setCellString(5,2,mobileiInfoilist.at(8));
    word.setCellString(5,3,QStringLiteral("运营商："));
    word.setCellString(5,4,mobileiInfoilist.at(7));

    word.setTableAutoFitBehavior(4);
    word.moveForEnd();
    word.insertMoveDown();

        //危险应用信息
        word.setFontBold(true);
        word.setParagraphAlignment(1);		//下面文字置左
        word.setFontSize(15);

        progressDlg->setValue(4);
        word.insertText(QStringLiteral("4.风险应用信息(共 %1 个)").arg(QString::number(AppList::riskcount)));//插入文字
        word.insertMoveDown();

        qDebug()<<AppList::AppPackageDanger.count()<<"HTHETH";
        for(int i = 1; i < AppList::AppPackageDanger.count()+1;i++)
        {
            qDebug()<<AppList::AppPackageDanger.count()<<"6666";

            word.setFontSize(12);
            word.setFontBold(true);
            word.insertText(QStringLiteral("4.%1  %2").arg(QString::number(i)).arg(AppList::AppNameListDanger.at(i-1)));//插入文字
            word.insertMoveDown();
            word.insertMoveDown();
            word.setFontSize(10);
            word.insertText(QStringLiteral("1) 基本信息"));//插入文字
            word.insertMoveDown();
            word.insertMoveDown();

            word.setFontBold(false);
            word.setParagraphAlignment(0);		//下面文字置左
            word.intsertTable(2,4);			//几行几列table
            word.setColumnWidth(1,110);
            word.setColumnWidth(2,110);
            word.setColumnWidth(3,110);
            word.setColumnWidth(4,110);

            word.setCellString(1,1,QStringLiteral("应用名:"));
            word.setCellString(1,2,AppList::AppNameListDanger.at(i - 1));
            word.setCellString(1,3,QStringLiteral("包名："));
            word.setCellString(1,4,AppList::AppPackageDanger.at(i - 1));
            word.setCellString(2,1,QStringLiteral("版本号："));
            word.setCellString(2,2,mobileiInfoilist.at(4));
            word.setCellString(2,3,QStringLiteral("应用来源："));
            word.setCellString(2,4,QStringLiteral("用户安装"));
//            word.setCellString(3,1,QStringLiteral("最后更新时间："));
//            word.setCellString(3,3,QStringLiteral("安装时间："));

            word.setTableAutoFitBehavior(4);
            word.moveForEnd();
            word.insertMoveDown();

            word.setParagraphAlignment(1);		//下面文字置左
            word.setFontBold(true);
            word.insertText(QStringLiteral("2) 危险描述"));//插入文字
            word.insertMoveDown();
            word.setFontBold(false);

            qDebug()<<"hthhtheheth"<<"msg.....";

            msg =  AppList::ApkPermission[i-1];
            AllInfo = msg.split(MSG_CHECKOUT);

            qDebug()<<msg<<AllInfo.count()<<"uuuuu";

            QString permissonInfo = AllInfo.at(2);

            QString vires = AllInfo.at(1);

            perInfoList = permissonInfo.split(MSG_DATA_ITEMS_SEPARATOR);
            percount = perInfoList.count();

            qDebug()<<percount<<"iiiii";
            if(percount == 1)
            {

                word.insertText(QStringLiteral("一、应用拥有的敏感权限如下:"));//插入文字
                word.insertMoveDown();
                word.insertText(QStringLiteral("无权限。"));//插入文字
                word.insertMoveDown();
            }else
            {

                for(int i = 0; i < percount; i++)
                {
                     word.insertText(perInfoList.at(i));//插入文字
                     word.insertMoveDown();

                }
            }

             word.insertMoveDown();
             word.setFontBold(true);
             word.insertText(QStringLiteral("3) 拥有权限"));//插入文字
             word.insertMoveDown();

             word.setFontBold(false);
             word.setParagraphAlignment(1);		//下面文字置左


            //qDebug()<<percount<<"LLLLL";
            QString riskper = AppList::permisson[i-1];
            QStringList riskperList = riskper.split(MSG_DATA_ITEMS_SEPARATOR);
            int count1 = riskperList.count();
            qDebug()<<count1<<"hrehtht";

            if(count1 == 1)
            {

                word.insertText(QStringLiteral("无"));//插入文字
                word.insertMoveDown();
               //ord.insertMoveDown();
            }else
            {

               word.intsertTable(count1-1,4);			//几行几列table

               word.setColumnWidth(1,110);
               word.setColumnWidth(2,110);
               word.setColumnWidth(3,110);
               word.setColumnWidth(4,110);


               qDebug()<<"cout:"<<riskper<<count1;
               for(int i = 1; i < count1;i++)
               {

                 qDebug()<<riskperList.at(i)<<"kkkk";
                 QString str1 = riskperList.at(i-1);

                 QString str2;
                 QStringList list1;
                 if(!str1.isEmpty())
                 {
                   str2 = cmdData::selectperdetail(str1);
                 }
                 qDebug()<<str2<<str2.count()<<"jjjjj";

                 list1 =str2.split(MSG_DATA_ITEMS_SEPARATOR);
                 qDebug()<<list1.count()<<"fffff";
                 word.setCellString(i,1,QString::number(i));
                 word.setCellString(i,2,list1.at(0));
                 word.setCellString(i,3,list1.at(1));
                 word.setCellString(i,4,list1.at(2));

                 qDebug()<<"hetherherh"<<"gewgeg";
               }
            }
            word.setTableAutoFitBehavior(4);
            word.moveForEnd();
            word.insertMoveDown();
            word.setParagraphAlignment(1);
            word.setFontBold(true);
            word.insertMoveDown();
            word.insertText(QStringLiteral("4)应用涉及病毒情况 "));//插入文字
            word.insertMoveDown();
            word.setFontBold(false);
            QStringList virus = vires.split(MSG_DATA_ITEMS_SEPARATOR);
            int vcount = virus.count();
            if(vcount == 1)
            {
                word.insertText(QStringLiteral("未发现病毒危险"));//插入文字
                word.insertMoveDown();
                word.insertMoveDown();

            }else
            {
                for(i = 1 ;i < vcount; i++)
                {
                    word.insertText(virus.at(i));//插入文字
                    word.insertMoveDown();
                    word.insertMoveDown();

                }

            }
            progressDlg->setValue(4+i);

            if(progressDlg->wasCanceled())
            {
                progressDlg->close();
                delete &word;
                return false;
                //break;
            }

      }
  word.insertMoveDown();
  word.insertMoveDown();

  word.insertMoveDown();
  word.setParagraphAlignment(2);		//下面文字置右
  word.setFontSize(14);
  word.setFontBold(false);
  QString str11 = QStringLiteral("检测人：%1").arg(LoginWidget::Username);
  QString str2 = str11.append("  %1").arg(LoginWidget::Userpart);
  word.insertText(str2);
  word.insertMoveDown();

  QString defaultFileName = QStringLiteral("检测时间: %1").arg(QDateTime::currentDateTime().toString("yyyy.MM.dd"));
  word.insertText(defaultFileName);

  word.getDocument()->dynamicCall("SaveAs (const QString&)",QString(AppList::currentExportDir));

  word.close();

  progressDlg->setValue(5+row);

  return true;

//  QString defaultFileName = QStringLiteral("检测时间: %1").arg(QDateTime::currentDateTime().toString("yyyy.MM.dd"));
//  word.insertText(defaultFileName);
//  word.insertMoveDown();
//  word.insertText(QStringLiteral("检测人：%1 %2").arg(User).arg(QWord::UserPart));
//  word.insertText(QStringLiteral("检测人：武警总部 管理员"));

}

bool QWord::showContanctInfo(int Row,QString unit,QString name, QString phone, QString detail)
{
    QWord word;
    int contacount;
    QStringList contaInfoList;
    QString contanctInfo;

    QTextCodec *codec = QTextCodec::codecForName("utf-8");
    QTextCodec::setCodecForLocale(codec);

    //QString path = QDir::currentPath();//当前路径
    //qDebug() << path<<"frfggef";

    QString path = QDir::currentPath();//当前路径
    qDebug() << path<<"frfggefefqqeffff";

    QString currentpath = path.append("/QrcodeImage/qrcode.png");

    //word标题部分

   bool OK =  word.createNewWord(QStringLiteral("通讯录检测"));
   if(OK == false)
   {
       //this->close();
       return false;
   }

   QProgressDialog *progressDlg=new QProgressDialog();

   progressDlg->setFixedSize(300,120);
   QFont font("ZYSong18030",11);
   progressDlg->setFont(font);

   progressDlg->setWindowModality(Qt::WindowModal);

   QProgressBar *progressbar = new QProgressBar();

   progressDlg->setRange(0,Row+5);
   progressbar->setAlignment(Qt::AlignRight | Qt::AlignVCenter);  // 对齐方式

   progressDlg->setBar(progressbar);
   QCoreApplication::processEvents();
   progressDlg->setWindowIcon(QIcon("screen/export.png"));
   progressDlg->setMinimumDuration(5);
   progressDlg->setCancelButton(false);
   progressDlg->setWindowTitle(QStringLiteral("请稍等"));
   progressDlg->setLabelText(QStringLiteral("正在导出中......"));

   progressDlg->setRange(0,Row+5);

    word.setPageOrientation(0);			//页面横向
    word.setWordPageView(1);			//页面视图

    word.setFontSize(20);				//字体大小
    word.setParagraphAlignment(0);		//下面文字置中
    word.setFontBold(true);				//字体加粗
    word.insertText(QStringLiteral("手机通讯录检测报告"));//插入文字


    //下面正文部分
    word.setFontBold(false);			//字体bu加cu
    word.insertMoveDown();
    word.insertMoveDown();

    word.setFontBold(true);
    word.setParagraphAlignment(1);		//下面文字置左
    word.setFontSize(15);
    word.insertText(QStringLiteral("1.被检测人基本信息:"));//插入文字
    word.insertMoveDown();

    word.setFontSize(10);
    word.setFontBold(false);
    word.setParagraphAlignment(0);		//下面文字置左
    word.intsertTable(2,3);			//几行几列table
    word.setColumnWidth(1,160);
    word.setColumnWidth(2,160);
    word.setColumnWidth(3,160);

    word.setCellString(1,1,QStringLiteral("单位"));
    word.setCellString(1,2,QStringLiteral("姓名"));
    word.setCellString(1,3,QStringLiteral("手机号"));

    //word.setCellString(2,1,QStringLiteral("武警总队"));
    word.setCellString(2,1,unit);

    //word.setCellString(2,2,QStringLiteral("李剑"));
    word.setCellString(2,2,name);


    //word.setCellString(2,3,QStringLiteral("18234095185"));
    word.setCellString(2,3,phone);

    word.setTableAutoFitBehavior(2);
    word.moveForEnd();
    word.insertMoveDown();
    progressDlg->setValue(1);

    word.setParagraphAlignment(1);		//下面文字置左
    word.intsertTable(2,2);			//几行几列table
    word.setColumnWidth(1,160);
    word.setColumnWidth(2,320);
    word.setCellString(1,1,QStringLiteral("备注:"));
    word.setCellString(1,2,detail);
    word.setCellString(2,1,QStringLiteral("二维码:"));
    //word.insertCellPic(2,2,QStringLiteral("123.jpg"));

    word.insertCellPic(2,2,currentpath);
    word.setTableAutoFitBehavior(2);
    word.moveForEnd();
    word.insertMoveDown();
    progressDlg->setValue(2);

    //报告结果：
    word.setFontBold(true);
    word.setParagraphAlignment(1);		//下面文字置左
    word.setFontSize(15);
    word.insertText(QStringLiteral("2.报告结果："));//插入文字
    word.insertMoveDown();
    word.setFontBold(false);
    word.setParagraphAlignment(1);		//下面文字置左

    word.setFontSize(10);

    QString str1 =  QStringLiteral("   本次共检查(%1)条通讯录。").arg(QString::number(Row));
    word.insertText(str1);//插入文字
    word.insertMoveDown();
    word.insertMoveDown();
    progressDlg->setValue(3);

    //手机基本信息
    word.setFontBold(true);
    word.setParagraphAlignment(1);		//下面文字置左
    word.setFontSize(15);
    word.insertText(QStringLiteral("3.通讯录详细信息："));//插入文字
    word.insertMoveDown();

    word.setFontBold(false);
    word.setParagraphAlignment(0);		//下面文字置zhong
    word.setFontSize(10);
    word.intsertTable(Row+1,3);			//几行几列table
    word.setColumnWidth(1,110);
    word.setColumnWidth(2,150);
    word.setColumnWidth(3,180);
    //word.setColumnWidth(4,110);
    
    word.setCellString(1,1,QStringLiteral("编号"));
    word.setCellString(1,2,QStringLiteral("姓名"));
    word.setCellString(1,3,QStringLiteral("联系方式"));
    //word.setCellString(1,4,QStringLiteral("唯一编码"));

    for(int i = 2; i < Row+2;i++)
    {

         contanctInfo = AppList::ContactsInfo[i-2] ;
         contaInfoList = contanctInfo.split(MSG_DATA_ITEMS_SEPARATOR);

         contacount = contaInfoList.count();
         qDebug()<<contanctInfo <<contacount<<"sssss";


         word.setCellString(i,1,QString::number(i-1));
         word.setCellString(i,2,contaInfoList.at(1));
         word.setCellString(i,3,contaInfoList.at(0));
         //word.setCellString(i,4,contaInfoList.at(2));

         progressDlg->setValue(i+3);

         qDebug()<<"hetherherh"<<"gewgeg";

   }

  word.setTableAutoFitBehavior(3);
  word.moveForEnd();
  word.insertMoveDown();

    
  //word.insertMoveDown();
  word.insertMoveDown();
  word.insertMoveDown();
  word.setParagraphAlignment(2);		//下面文字置右
  word.setFontSize(14);
  word.setFontBold(false);

  //QString str11 = QStringLiteral("检测人：%1").arg(User);
  //QString str2 = str11.append("  %1").arg(UserPart);
  QString str11 = QStringLiteral("检测人：%1").arg(LoginWidget::Username);
  QString str2 = str11.append("  %1").arg(LoginWidget::Userpart);
  word.insertText(str2);
  word.insertMoveDown();

  QString defaultFileName = QStringLiteral("检测时间: %1").arg(QDateTime::currentDateTime().toString("yyyy.MM.dd"));
  word.insertText(defaultFileName);

  progressDlg->setValue(Row+5);

//  QString defaultFileName = QStringLiteral("检测时间: %1").arg(QDateTime::currentDateTime().toString("yyyy.MM.dd"));
//  word.insertText(defaultFileName);
//  word.insertMoveDown();
//  word.insertText(QStringLiteral("检测人：武警总部 管理员"));

  //word.save();
  word.close();

//  QString safeResultInfo = QStringLiteral("检测结果已经导出，请查阅！！！");
//  QMessageBox::information(NULL, QStringLiteral("导出提示"),
//                               safeResultInfo, QStringLiteral("确定"));

  return true;
    
}

bool QWord::showCallhistoryInfo(int row,QString unit,QString name,QString phone,QString detail)
{


    qDebug()<< QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");

    QWord word;
    int contacount;
    QStringList callhisInfoList;
    QString callhistoryInfo ;

    QTextCodec *codec = QTextCodec::codecForName("utf-8");
    QTextCodec::setCodecForLocale(codec);

    QString path = QDir::currentPath();//当前路径
    qDebug() << path<<"556688";
    QString currentpath = path.append("/QrcodeImage/qrcode.png");


    //word标题部分

    //word.createNewWord();
    bool OK =  word.createNewWord(QStringLiteral("通话记录检测"));
    if(OK == false)
    {
        //this->close();
        return false;
    }

    QProgressDialog *progressDlg=new QProgressDialog();

    progressDlg->setFixedSize(300,120);
    QFont font("ZYSong18030",11);
    progressDlg->setFont(font);

    progressDlg->setWindowModality(Qt::WindowModal);

    QProgressBar *progressbar = new QProgressBar();

    progressDlg->setRange(0,row+5);

    progressbar->setAlignment(Qt::AlignRight | Qt::AlignVCenter);  // 对齐方式

    progressDlg->setBar(progressbar);
    QCoreApplication::processEvents();
    progressDlg->setWindowIcon(QIcon("screen/export.png"));
    progressDlg->setMinimumDuration(5);
    progressDlg->setCancelButton(false);
    progressDlg->setWindowTitle(QStringLiteral("请稍等"));
    progressDlg->setLabelText(QStringLiteral("正在导出中......"));

    progressDlg->setRange(0,row+5);


    word.setPageOrientation(0);			//页面横向
    word.setWordPageView(1);			//页面视图

    word.setFontSize(20);				//字体大小
    word.setParagraphAlignment(0);		//下面文字置中
    word.setFontBold(true);				//字体加粗
    word.insertText(QStringLiteral("通话记录检测报告"));//插入文字


    //下面正文部分
    word.setFontBold(false);			//字体bu加cu
    word.insertMoveDown();
    word.insertMoveDown();

    word.setFontBold(true);
    word.setParagraphAlignment(1);		//下面文字置左
    word.setFontSize(15);
    word.insertText(QStringLiteral("1.被检测人基本信息:"));//插入文字
    word.insertMoveDown();

    word.setFontSize(10);
    word.setFontBold(false);
    word.setParagraphAlignment(0);		//下面文字置左
    word.intsertTable(2,3);			//几行几列table
    word.setColumnWidth(1,160);
    word.setColumnWidth(2,160);
    word.setColumnWidth(3,160);

    word.setCellString(1,1,QStringLiteral("单位"));
    word.setCellString(1,2,QStringLiteral("姓名"));
    word.setCellString(1,3,QStringLiteral("手机号"));

    //word.setCellString(2,1,QStringLiteral("武警总队"));
    word.setCellString(2,1,unit);

    //word.setCellString(2,2,QStringLiteral("李剑"));
    word.setCellString(2,2,name);


    //word.setCellString(2,3,QStringLiteral("18234095185"));
    word.setCellString(2,3,phone);

    word.setTableAutoFitBehavior(2);
    word.moveForEnd();
    word.insertMoveDown();
    progressDlg->setValue(1);

    word.setParagraphAlignment(1);		//下面文字置左
    word.intsertTable(2,2);			//几行几列table
    word.setColumnWidth(1,160);
    word.setColumnWidth(2,320);
    word.setCellString(1,1,QStringLiteral("备注:"));
    word.setCellString(1,2,detail);
    word.setCellString(2,1,QStringLiteral("二维码:"));
    //word.insertCellPic(2,2,QStringLiteral("123.jpg"));

    word.insertCellPic(2,2,currentpath);
    word.setTableAutoFitBehavior(2);
    word.moveForEnd();
    word.insertMoveDown();
    progressDlg->setValue(2);

    //报告结果：
    word.setFontBold(true);
    word.setParagraphAlignment(1);		//下面文字置左
    word.setFontSize(15);
    word.insertText(QStringLiteral("2.报告结果："));//插入文字
    word.insertMoveDown();
    word.setFontBold(false);
    word.setParagraphAlignment(1);		//下面文字置左

    word.setFontSize(10);

    QString str1 =  QStringLiteral("   本次共检查(%1)条通话记录。").arg(QString::number(row));
    word.insertText(str1);//插入文字
    word.insertMoveDown();
    word.insertMoveDown();

    progressDlg->setValue(3);

    //手机基本信息
    word.setFontBold(true);
    word.setParagraphAlignment(1);		//下面文字置左
    word.setFontSize(15);
    word.insertText(QStringLiteral("3.有关通话记录详细信息："));//插入文字
    word.insertMoveDown();

    word.setFontBold(false);
    word.setParagraphAlignment(0);		//下面文字置zhong
    word.setFontSize(10);
    word.intsertTable(row+1,5);			//几行几列table
    word.setColumnWidth(1,80);
    word.setColumnWidth(2,100);
    word.setColumnWidth(3,100);
    word.setColumnWidth(4,100);
    word.setColumnWidth(5,100);

    word.setCellString(1,1,QStringLiteral("编号"));
    word.setCellString(1,2,QStringLiteral("通话号码"));
    word.setCellString(1,3,QStringLiteral("通话时长"));
    word.setCellString(1,4,QStringLiteral("通话状态"));
    word.setCellString(1,5,QStringLiteral("时间"));

    for(int i = 2; i < row+2;i++)
    {

         callhistoryInfo = AppList::CallhistoryInfo[i-2] ;
         callhisInfoList = callhistoryInfo.split(MSG_DATA_ITEMS_SEPARATOR);

         contacount = callhisInfoList.count();
         qDebug()<<callhistoryInfo <<contacount<<"sssss";

         word.setCellString(i,1,QString::number(i-1));
         word.setCellString(i,2,callhisInfoList.at(0));
         word.setCellString(i,3,callhisInfoList.at(1));
         word.setCellString(i,4,callhisInfoList.at(2));
         word.setCellString(i,5,callhisInfoList.at(3));

         progressDlg->setValue(3+i);
         qDebug()<<"hetherherh"<<"gewgeg";
   }

  word.setTableAutoFitBehavior(4);
  word.moveForEnd();
  word.insertMoveDown();


  //word.insertMoveDown();
  word.insertMoveDown();
  word.insertMoveDown();
  word.setParagraphAlignment(2);		//下面文字置右
  word.setFontSize(14);
  word.setFontBold(false);

  //QString str11 = QStringLiteral("检测人：%1").arg(User);
  //QString str2 = str11.append("  %1").arg(UserPart);
  QString str11 = QStringLiteral("检测人：%1").arg(LoginWidget::Username);
  QString str2 = str11.append("  %1").arg(LoginWidget::Userpart);
  word.insertText(str2);
  word.insertMoveDown();

  QString defaultFileName = QStringLiteral("检测时间: %1").arg(QDateTime::currentDateTime().toString("yyyy.MM.dd"));
  word.insertText(defaultFileName);

  progressDlg->setValue(row+5);

  word.close();

  return true;

}
bool QWord::showMessageInfo(int row,QString unit,QString name,QString phone,QString detail)
{


    QWord word;
    int contacount;
    QStringList callhisInfoList;
    QString callhistoryInfo ;

    QTextCodec *codec = QTextCodec::codecForName("utf-8");
    QTextCodec::setCodecForLocale(codec);

    QString path = QDir::currentPath();//当前路径
    qDebug() << path<<"556688"<<row<<"ooooo";
    QString currentpath = path.append("/QrcodeImage/qrcode.png");

    //word标题部分

    //word.createNewWord();
    bool OK =  word.createNewWord(QStringLiteral("短信检测"));
    if(OK == false)
    {
        //this->close();
        return false;
    }
    QProgressDialog *progressDlg=new QProgressDialog();

    progressDlg->setFixedSize(300,120);
    QFont font("ZYSong18030",11);
    progressDlg->setFont(font);

    progressDlg->setWindowModality(Qt::WindowModal);

    QProgressBar *progressbar = new QProgressBar();
    //progressbar->setRange(0,row+5);
    progressDlg->setRange(0,row+5);
    //progressDlg->setFormat("");
//    double dProgress = ( progressDlg->value() -  progressDlg->minimum()) * 100.0
//                    / ( progressDlg->maximum() - progressDlg->minimum());
//    QString str22 = QStringLiteral("当前已完成：");
//    progressbar->setFormat((str22.append("%1%")).arg(QString::number(progressDlg->value()/progressDlg->maximum())));
    progressbar->setAlignment(Qt::AlignRight | Qt::AlignVCenter);  // 对齐方式

    progressDlg->setBar(progressbar);
    QCoreApplication::processEvents();
    progressDlg->setWindowIcon(QIcon("screen/export.png"));
    progressDlg->setMinimumDuration(5);
    progressDlg->setCancelButton(false);
    progressDlg->setWindowTitle(QStringLiteral("请稍等"));
    progressDlg->setLabelText(QStringLiteral("正在导出中......"));

    progressDlg->setRange(0,row+5);


    word.setPageOrientation(0);			//页面横向
    word.setWordPageView(1);			//页面视图

    word.setFontSize(20);				//字体大小
    word.setParagraphAlignment(0);		//下面文字置中
    word.setFontBold(true);				//字体加粗
    word.insertText(QStringLiteral("短信记录检测报告"));//插入文字


    //下面正文部分
    word.setFontBold(false);			//字体bu加cu
    word.insertMoveDown();
    word.insertMoveDown();

    word.setFontBold(true);
    word.setParagraphAlignment(1);		//下面文字置左
    word.setFontSize(15);
    word.insertText(QStringLiteral("1.被检测人基本信息:"));//插入文字
    word.insertMoveDown();

    word.setFontSize(10);
    word.setFontBold(false);
    word.setParagraphAlignment(0);		//下面文字置左
    word.intsertTable(2,3);			//几行几列table
    word.setColumnWidth(1,160);
    word.setColumnWidth(2,160);
    word.setColumnWidth(3,160);

    word.setCellString(1,1,QStringLiteral("单位"));
    word.setCellString(1,2,QStringLiteral("姓名"));
    word.setCellString(1,3,QStringLiteral("手机号"));

    //word.setCellString(2,1,QStringLiteral("武警总队"));
    word.setCellString(2,1,unit);

    //word.setCellString(2,2,QStringLiteral("李剑"));
    word.setCellString(2,2,name);


    //word.setCellString(2,3,QStringLiteral("18234095185"));
    word.setCellString(2,3,phone);

    word.setTableAutoFitBehavior(2);
    word.moveForEnd();
    word.insertMoveDown();
    progressDlg->setValue(1);

    word.setParagraphAlignment(1);		//下面文字置左
    word.intsertTable(2,2);			//几行几列table
    word.setColumnWidth(1,160);
    word.setColumnWidth(2,320);
    word.setCellString(1,1,QStringLiteral("备注:"));
    word.setCellString(1,2,detail);
    word.setCellString(2,1,QStringLiteral("二维码:"));
    //word.insertCellPic(2,2,QStringLiteral("123.jpg"));

    word.insertCellPic(2,2,currentpath);
    word.setTableAutoFitBehavior(2);
    word.moveForEnd();
    word.insertMoveDown();

    progressDlg->setValue(2);

    //报告结果：
    word.setFontBold(true);
    word.setParagraphAlignment(1);		//下面文字置左
    word.setFontSize(15);
    word.insertText(QStringLiteral("2.报告结果："));//插入文字
    word.insertMoveDown();
    word.setFontBold(false);
    word.setParagraphAlignment(1);		//下面文字置左

    word.setFontSize(10);

    QString str1 =  QStringLiteral("   本次共检测(%1)条短信记录。").arg(QString::number(row));
    word.insertText(str1);//插入文字
    word.insertMoveDown();
    word.insertMoveDown();

    //手机基本信息
    word.setFontBold(true);
    word.setParagraphAlignment(1);		//下面文字置左
    word.setFontSize(15);
    progressbar->setValue(2);
    word.insertText(QStringLiteral("3.有关短信记录详细信息："));//插入文字
    word.insertMoveDown();
    progressDlg->setValue(3);

    word.setFontBold(false);
    word.setParagraphAlignment(0);		//下面文字置zhong
    word.setFontSize(10);
    word.intsertTable(row+1,5);			//几行几列table
    word.setColumnWidth(1,80);
    word.setColumnWidth(2,100);
    word.setColumnWidth(3,100);
    word.setColumnWidth(4,100);
    word.setColumnWidth(5,100);

    word.setCellString(1,1,QStringLiteral("编号"));
    word.setCellString(1,2,QStringLiteral("接收号码"));
    word.setCellString(1,3,QStringLiteral("短信详细"));
    word.setCellString(1,4,QStringLiteral("发送状态"));
    word.setCellString(1,5,QStringLiteral("时间"));

    for(int i = 2; i < row+2;i++)
    {

         callhistoryInfo = AppList::MessageExportInfo[i-2] ;
         callhisInfoList = callhistoryInfo.split(MSG_DATA_ITEMS_SEPARATOR);

         contacount = callhisInfoList.count();
         qDebug()<<callhistoryInfo <<contacount<<"sssss";

         word.setCellString(i,1,QString::number(i-1));
         word.setCellString(i,2,callhisInfoList.at(0));
         word.setCellString(i,3,callhisInfoList.at(1));
         word.setCellString(i,4,callhisInfoList.at(2));
         word.setCellString(i,5,callhisInfoList.at(3));

         qDebug()<<"hetherherh"<<"gewgeg";

         progressDlg->setValue(3+i);
   }

  word.setTableAutoFitBehavior(4);
  word.moveForEnd();
  word.insertMoveDown();


  //word.insertMoveDown();
  word.insertMoveDown();
  word.insertMoveDown();
  word.setParagraphAlignment(2);		//下面文字置右
  word.setFontSize(14);
  word.setFontBold(false);

  //QString str11 = QStringLiteral("检测人：%1").arg(User);
  //QString str2 = str11.append("  %1").arg(UserPart);
  QString str11 = QStringLiteral("检测人：%1").arg(LoginWidget::Username);
  QString str2 = str11.append("  %1").arg(LoginWidget::Userpart);
  word.insertText(str2);
  word.insertMoveDown();

  QString defaultFileName = QStringLiteral("检测时间: %1").arg(QDateTime::currentDateTime().toString("yyyy.MM.dd"));
  word.insertText(defaultFileName);

  progressDlg->setValue(row+5);

//  QString defaultFileName = QStringLiteral("检测时间: %1").arg(QDateTime::currentDateTime().toString("yyyy.MM.dd"));
//  word.insertText(defaultFileName);
//  word.insertMoveDown();
//  word.insertText(QStringLiteral("检测人：武警总部 管理员"));
  word.close();

//  QString safeResultInfo = QStringLiteral("检测结果已经导出，请查阅！！！");
//  QMessageBox::information(NULL, QStringLiteral("导出提示"),
//                               safeResultInfo, QStringLiteral("确定"));

  return true;

}

bool QWord::showFileInfo(int row,QString unit,QString name,QString phone,QString detail)
{

    QWord word;
    int contacount;
    QStringList callhisInfoList;
    QString callhistoryInfo ;

    QTextCodec *codec = QTextCodec::codecForName("utf-8");
    QTextCodec::setCodecForLocale(codec);

    QString path = QDir::currentPath();//当前路径
    qDebug() << path<<"556688"<<row<<"uuuuu";
    QString currentpath = path.append("/QrcodeImage/qrcode.png");

    //word标题部分

    //word.createNewWord();
    bool OK =  word.createNewWord(QStringLiteral("文件检测"));
    if(OK == false)
    {
        //this->close();
        return false;
    }

    QProgressDialog *progressDlg=new QProgressDialog();

    progressDlg->setFixedSize(300,120);
    QFont font("ZYSong18030",11);
    progressDlg->setFont(font);

    progressDlg->setWindowModality(Qt::WindowModal);

    QProgressBar *progressbar = new QProgressBar();

    progressDlg->setRange(0,row+5);
    //progressDlg->setFormat("");
//    double dProgress = ( progressDlg->value() -  progressDlg->minimum()) * 100.0
//                    / ( progressDlg->maximum() - progressDlg->minimum());
//    QString str22 = QStringLiteral("当前已完成：");
//    progressbar->setFormat((str22.append("%1%")).arg(QString::number(progressDlg->value()/progressDlg->maximum())));
    progressbar->setAlignment(Qt::AlignRight | Qt::AlignVCenter);  // 对齐方式

    progressDlg->setBar(progressbar);
    QCoreApplication::processEvents();
    progressDlg->setWindowIcon(QIcon("screen/export.png"));
    progressDlg->setMinimumDuration(5);
    progressDlg->setCancelButton(false);
    progressDlg->setWindowTitle(QStringLiteral("请稍等"));
    progressDlg->setLabelText(QStringLiteral("正在导出中......"));

    progressDlg->setRange(0,row+5);

    word.setPageOrientation(0);			//页面横向
    word.setWordPageView(1);			//页面视图

    word.setFontSize(20);				//字体大小
    word.setParagraphAlignment(0);		//下面文字置中
    word.setFontBold(true);				//字体加粗
    word.insertText(QStringLiteral("手机文件检测报告"));//插入文字


    //下面正文部分
    word.setFontBold(false);			//字体bu加cu
    word.insertMoveDown();
    word.insertMoveDown();

    word.setFontBold(true);
    word.setParagraphAlignment(1);		//下面文字置左
    word.setFontSize(15);
    word.insertText(QStringLiteral("1.被检测人基本信息:"));//插入文字
    word.insertMoveDown();

    word.setFontSize(10);
    word.setFontBold(false);
    word.setParagraphAlignment(0);		//下面文字置左
    word.intsertTable(2,3);			//几行几列table
    word.setColumnWidth(1,160);
    word.setColumnWidth(2,160);
    word.setColumnWidth(3,160);

    word.setCellString(1,1,QStringLiteral("单位"));
    word.setCellString(1,2,QStringLiteral("姓名"));
    word.setCellString(1,3,QStringLiteral("手机号"));

    //word.setCellString(2,1,QStringLiteral("武警总队"));
    word.setCellString(2,1,unit);

    //word.setCellString(2,2,QStringLiteral("李剑"));
    word.setCellString(2,2,name);


    //word.setCellString(2,3,QStringLiteral("18234095185"));
    word.setCellString(2,3,phone);

    word.setTableAutoFitBehavior(2);
    word.moveForEnd();
    word.insertMoveDown();
    progressDlg->setValue(1);

    word.setParagraphAlignment(1);		//下面文字置左
    word.intsertTable(2,2);			//几行几列table
    word.setColumnWidth(1,160);
    word.setColumnWidth(2,320);
    word.setCellString(1,1,QStringLiteral("备注:"));
    word.setCellString(1,2,detail);
    word.setCellString(2,1,QStringLiteral("二维码:"));
    //word.insertCellPic(2,2,QStringLiteral("123.jpg"));

    word.insertCellPic(2,2,currentpath);
    word.setTableAutoFitBehavior(2);
    word.moveForEnd();
    word.insertMoveDown();
    progressDlg->setValue(2);

    //报告结果：
    word.setFontBold(true);
    word.setParagraphAlignment(1);		//下面文字置左
    word.setFontSize(15);
    word.insertText(QStringLiteral("2.报告结果："));//插入文字
    word.insertMoveDown();
    word.setFontBold(false);
    word.setParagraphAlignment(1);		//下面文字置左

    word.setFontSize(10);

    QString str1 =  QStringLiteral("   本次共扫描(%1)个文件。").arg(QString::number(row));
    word.insertText(str1);//插入文字
    word.insertMoveDown();
    word.insertMoveDown();
    //progressDlg->setValue(3);

    //手机基本信息
    word.setFontBold(true);
    word.setParagraphAlignment(1);		//下面文字置左
    word.setFontSize(15);
    word.insertText(QStringLiteral("3.有关手机文件详细信息："));//插入文字
    word.insertMoveDown();

    word.setFontBold(false);
    word.setParagraphAlignment(0);		//下面文字置zhong
    word.setFontSize(10);
    word.intsertTable(row+1,3);			//几行几列table
    word.setColumnWidth(1,80);
    word.setColumnWidth(2,150);
    word.setColumnWidth(3,250);

    word.setCellString(1,1,QStringLiteral("编号"));
    word.setCellString(1,2,QStringLiteral("文件名"));
    word.setCellString(1,3,QStringLiteral("文件所在路径"));

    for(int i = 2; i < row+2;i++)
    {

         callhistoryInfo = AppList::FileInfo[i-2] ;
         callhisInfoList = callhistoryInfo.split(MSG_DATA_ITEMS_SEPARATOR);

         contacount = callhisInfoList.count();
         qDebug()<<callhistoryInfo <<contacount<<"sssss";

         word.setCellString(i,1,QString::number(i-1));
         word.setCellString(i,2,callhisInfoList.at(0));
         word.setCellString(i,3,callhisInfoList.at(1));
//         word.setCellString(i,4,callhisInfoList.at(2));
//         word.setCellString(i,5,callhisInfoList.at(3));

         progressDlg->setValue(3+i);

         qDebug()<<"hetherherh"<<"gewgeg";

   }

  word.setTableAutoFitBehavior(4);
  word.moveForEnd();
  word.insertMoveDown();


  //word.insertMoveDown();
  word.insertMoveDown();
  word.insertMoveDown();
  word.setParagraphAlignment(2);		//下面文字置右
  word.setFontSize(14);
  word.setFontBold(false);

  //QString str11 = QStringLiteral("检测人：%1").arg(User);
  //QString str2 = str11.append("  %1").arg(UserPart);
  QString str11 = QStringLiteral("检测人：%1").arg(LoginWidget::Username);
  QString str2 = str11.append("  %1").arg(LoginWidget::Userpart);
  word.insertText(str2);
  word.insertMoveDown();

  QString defaultFileName = QStringLiteral("检测时间: %1").arg(QDateTime::currentDateTime().toString("yyyy.MM.dd"));
  word.insertText(defaultFileName);
  //word.insertText(QStringLiteral("检测人：%1 %2").arg(User).arg(UserPart));

  progressDlg->setValue(row+5);

  word.close();

//  QString safeResultInfo = QStringLiteral("检测结果已经导出，请查阅！！！");
//  QMessageBox::information(NULL, QStringLiteral("导出提示"),
//                               safeResultInfo, QStringLiteral("确定"));

  return true;

}
