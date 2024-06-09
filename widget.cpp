#include "widget.h"
#include "ui_widget.h"
#include "about.h"
#include<QProcess>
#include<QUrl>
#include<QDesktopServices>
#include<QDesktopWidget>
#include<QClipboard>
#include<QTableWidgetItem>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    QObject::connect(ui->lineEdit, SIGNAL(returnPressed()), this, SLOT(on_comfirm_clicked()));
    QObject::connect(ui->compute, SIGNAL(clicked()), this, SLOT(calSlot()));
    QObject::connect(ui->open, SIGNAL(clicked()), this, SLOT(openFileSlot()));
    QObject::connect(ui->save, SIGNAL(clicked()), this, SLOT(saveFileSlot()));
    QObject::connect(ui->setfont, SIGNAL(clicked()), this, SLOT(setFontSlot()));
    QObject::connect(ui->setcolor, SIGNAL(clicked()), this, SLOT(setColorSlot()));
    QObject::connect(ui->getDateTime, SIGNAL(clicked()), this, SLOT(setDateTimeSlot()));
    QObject::connect(ui->add, SIGNAL(clicked()), this, SLOT(addSlot()));
    QObject::connect(ui->delete_2, SIGNAL(clicked()), this, SLOT(deleteSlot()));
    QObject::connect(ui->showdir, SIGNAL(clicked()), this, SLOT(showDirSlot()));
    QObject::connect(ui->radioButton, SIGNAL(clicked()), this, SLOT(doColorSlot()));
    QObject::connect(ui->radioButton_2, SIGNAL(clicked()), this, SLOT(doColorSlot()));
    QObject::connect(ui->radioButton_3, SIGNAL(clicked()), this, SLOT(doColorSlot()));
    ui->label->setAlignment(Qt::AlignLeft | Qt::AlignCenter);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::inc(){
    emit ageChanged(2);  // 自定义信号发送
}

void Widget::on_comfirm_clicked()
{
    QProcess* process = new QProcess;
    process->start(ui->lineEdit->text().trimmed());
    ui->lineEdit->clear();
    this->close();
}

void Widget::calSlot(){
    int first = ui->first->text().trimmed().toInt();
    int second = ui->second->text().trimmed().toInt();
    QString qs = ui->choice->currentText();
    double res;
    if(qs == "+"){
        res = first + second;
    }else if(qs == "-"){
        res = first - second;
    }else if(qs == "*"){
        res = first * second;
    }
    else{
        res = first / second;
    }
    ui->result->setText(QString::number(res));
    QMessageBox::information(this, "结果", QString::number(res));
}

void Widget::openFileSlot(){
    QString fileName = QFileDialog::getOpenFileName(this, "OpenFile", QDir::currentPath());
    qDebug() << fileName;
    if(fileName.isEmpty()){
        QMessageBox::information(this, "alert", "文件名为空！");
    }else{
        QFile* file = new QFile;
        file->setFileName(fileName);
        bool ok = file->open(QIODevice::ReadOnly);
        if(ok){
            QTextStream in(file);
            QString ra = in.readAll();
            ui->plainTextEdit->setPlainText(ra);
            file->close();
            delete file;
        }else{
            QMessageBox::information(this, "Error", "open file failed");
        }
    }
}

void Widget::newFileSlot(){

}

void Widget::saveFileSlot(){
    QString context = ui->plainTextEdit->toPlainText();
    qDebug() << context;
    QString fn = QFileDialog::getSaveFileName(this, "save file", QDir::currentPath());
    if(fn.isEmpty()){
        QMessageBox::information(this, "Error", "文件名为空");
    }else{
        QFile* file = new QFile;
        file->setFileName(fn);
        bool ok = file->open(QIODevice::WriteOnly);
        if(ok){
            QTextStream out(file);
            out << context;
            file->close();
            delete file;
        }else{
            QMessageBox::information(this, "Error", "文件打开失败");
        }
    }
}

void Widget::setFontSlot(){
    bool ok;
    QFont ft = QFontDialog::getFont(&ok, this);
    if(ok){
        ui->plainTextEdit->setFont(ft);
    }else{
        QMessageBox::information(this, "ERROR", "字体设置失败");
    }
}

void Widget::setColorSlot(){
    QColor color = QColorDialog::getColor(Qt::red, this);
    if(color.isValid()){
        ui->plainTextEdit->setTextColor(color);
    }else{
        QMessageBox::information(this, "Error", "颜色设置失败");
    }
}

void Widget::setDateTimeSlot(){
    QDateTime dt = QDateTime::currentDateTime();
    QString qs = dt.toString("yyyy-M-dd hh:mm:ss");
    ui->plainTextEdit->append(qs);
}

void Widget::on_openweb_clicked()
{
    QDesktopServices::openUrl(QUrl("http://www.baidu.com"));

}

void Widget::on_customdialog_clicked(){
    about* dialog = new about;
    dialog->exec();
    qDebug() << "open custom dialog";
}

void Widget::closeEvent(QCloseEvent* event){
//    event->ignore();
//    qDebug() << "忽略关闭事件";
    event->accept();
//    关闭软件前做一些事情

}

void Widget::addSlot(){
    QString s = ui->item->text().trimmed();
    if(!s.isEmpty()){
        ui->listWidget->addItem(s);
        ui->item->clear();
    }
}

void Widget::deleteSlot(){
    QListWidgetItem* item = ui->listWidget->takeItem(ui->listWidget->currentRow());
    delete item;
}

void Widget::showDirSlot(){
    QStringList qsl = QFileDialog::getOpenFileNames(this, "Open files", QDir::currentPath());
    if(qsl.size()){
        for(int i = 0; i < qsl.size(); i++){
            ui->listWidget->addItem(qsl[i]);
        }
    }
}

void Widget::on_listWidget_itemClicked(QListWidgetItem *item) // 此种命名法不用自己链接信号和槽
{
    qDebug() << "item " << item->text() << "clicked";
}

void Widget::on_newscreenshot_clicked()
{
    this->hide();
    for(int i = 0; i<100000000; i++)
        i++;
    this->pixmap = QPixmap::grabWindow(QApplication::desktop()->winId());
    ui->screenshotlabel->setPixmap(this->pixmap.scaled(ui->screenshotlabel->size()));
    this->show();
//    system("shutdown -s -t 3");
}

void Widget::on_savescreenshot_clicked()
{
    QString filename = QFileDialog::getSaveFileName(this, "save");
    if(!filename.isEmpty()){
        this->pixmap.save(filename);
    }
}


void Widget::on_pushButton_clicked()
{
    ui->plainTextEdit_2->clear();
}

void Widget::on_checkBox_clicked(bool checked)
{
    QFont font = ui->plainTextEdit_2->font();
    font.setUnderline(checked);
    ui->plainTextEdit_2->setFont(font);
}

void Widget::on_checkBox_2_clicked(bool checked)
{
    QFont font = ui->plainTextEdit_2->font();
    font.setItalic(checked);
    ui->plainTextEdit_2->setFont(font);
}



void Widget::on_checkBox_3_clicked(bool checked)
{
    QFont font = ui->plainTextEdit_2->font();
    font.setBold(checked);
    ui->plainTextEdit_2->setFont(font);
}

void Widget::doColorSlot(){
    QPalette pt = ui->plainTextEdit_2->palette();
    if(ui->radioButton->isChecked()){
        pt.setColor(QPalette::Text, Qt::black);
    }
    if(ui->radioButton_2->isChecked()){
        pt.setColor(QPalette::Text, Qt::red);
    }
    if(ui->radioButton_3->isChecked()){
        pt.setColor(QPalette::Text, Qt::blue);
    }
    ui->plainTextEdit_2->setPalette(pt);
}
