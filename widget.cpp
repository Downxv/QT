#include "widget.h"
#include "ui_widget.h"
#include "about.h"
#include<QProcess>
#include<QUrl>
#include<QDesktopServices>
#include<QDesktopWidget>
#include<QClipboard>
#include<QTableWidgetItem>
#include<QSplitter>
#include<QTime>
#include<QMouseEvent>
#include<QMimeData>
#include<QFileInfo>
#include<QDragEnterEvent>
#include<QDropEvent>
#include<QFileDialog>
#include<QColorDialog>
#include<QFontDialog>
#include<QProgressDialog>
#include<QElapsedTimer>
#include<QInputDialog>

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
    QSplitter* splitter = new QSplitter(ui->tab_2);
    splitter->addWidget(ui->listWidget_2);
    splitter->addWidget(ui->tableWidget);
    splitter->addWidget(ui->treeWidget);
    ui->doubleSpinBox->setDecimals(3);
    // ui->plainTextEdit_2->setReadOnly(true);
    // ui->plainTextEdit_2->setEnabled(true);
    ui->lineEdit->setClearButtonEnabled(true);
    QObject::connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), this, SLOT(doASlot(int)));
    QObject::connect(ui->horizontalScrollBar, SIGNAL(valueChanged(int)), this, SLOT(doASlot(int)));
    QObject::connect(ui->dial, SIGNAL(valueChanged(int)), this, SLOT(doASlot(int)));
    qtimer = new QTimer(this);
    qtimer->stop();
    QObject::connect(qtimer, SIGNAL(timeout()), this, SLOT(do_timeout()));
    setAcceptDrops(true);
}

void Widget::do_timeout(){
    QTime tt = QTime::currentTime();
    ui->lcdNumber->display(tt.hour());
    ui->lcdNumber_2->display(tt.minute());
    ui->lcdNumber_3->display(tt.second());

    if(qtimer->isSingleShot()){
        ui->pushButton_7->setEnabled(true);
        ui->pushButton_8->setEnabled(false);
        ui->pushButton_9->setEnabled(true);
    }
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
            ui->plainTextEdit->append("ok");
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

void Widget::doASlot(int val){
    ui->progressBar->setValue(val);
}

void Widget::on_checkBox_4_clicked(bool checked)
{
    ui->progressBar->setTextVisible(checked);
}
void Widget::on_checkBox_5_clicked(bool checked)
{
    ui->progressBar->setInvertedAppearance(checked);
}


void Widget::on_radioButton_4_clicked()
{
    ui->progressBar->setFormat("%p%");
}

void Widget::on_radioButton_5_clicked()
{
    ui->progressBar->setFormat("%v");
}

void Widget::on_radioButton_4_clicked(bool checked)
{

}

void Widget::on_radioButton_5_clicked(bool checked)
{

}

void Widget::on_timeEdit_userTimeChanged(const QTime &time)
{
   QDate qd = ui->dateEdit->date();
   ui->dateTimeEdit->setDate(qd);
   ui->dateTimeEdit->setTime(time);
   qDebug() << time.toString("HH:mm:ss");
}

void Widget::on_dateEdit_userDateChanged(const QDate &date)
{
    QTime time = ui->timeEdit->time();
    ui->dateTimeEdit->setTime(time);
    ui->dateTimeEdit->setDate(date);
    qDebug() << date.toString("yyyy-MM-dd");
}

void Widget::on_dateTimeEdit_dateChanged(const QDate &date)
{
}

void Widget::on_dateTimeEdit_dateTimeChanged(const QDateTime &dateTime)
{
    qDebug() << dateTime.toSecsSinceEpoch();
}

void Widget::on_calendarWidget_selectionChanged()
{
    qDebug() << ui->calendarWidget->selectedDate().toString("yyyy年MM月dd日");
}

void Widget::on_pushButton_7_clicked()
{
    qtimer->setInterval(ui->spinBox_2->value());
    if(ui->radioButton_6->isChecked()){
        qtimer->setSingleShot(false);
    }else{
        qtimer->setSingleShot(true);
    }
    qtimer->start();
    ui->pushButton_7->setEnabled(false);
    ui->pushButton_8->setEnabled(true);
    ui->pushButton_9->setEnabled(false);
}

void Widget::on_pushButton_8_clicked()
{
    qtimer->stop();
    ui->pushButton_7->setEnabled(true);
    ui->pushButton_8->setEnabled(false);
    ui->pushButton_9->setEnabled(true);
}

void Widget::on_pushButton_13_clicked()
{
    ui->plainTextEdit_3->clear();
}

void Widget::on_pushButton_10_clicked()
{
    ui->comboBox->clear();
    for(int i = 0; i < 20; i++){
        ui->comboBox->addItem(QString("Item%1").arg(i));
    }
}

void Widget::on_checkBox_6_stateChanged(int arg1)
{

}

void Widget::on_checkBox_6_clicked(bool checked)
{
    ui->comboBox->setEditable(checked);
}

void Widget::on_pushButton_11_clicked()
{
    ui->comboBox->clear();
}

void Widget::on_pushButton_12_clicked()
{
    ui->comboBox_2->clear();
    QMap<QString, int> map;
    map.insert("北京", 10);
    map.insert("上海", 20);
    foreach(const QString& str, map.keys()){
        ui->comboBox_2->addItem(str, QString::number(map.value(str))); // 存入值
    }
}

void Widget::on_comboBox_currentTextChanged(const QString &arg1)
{
    ui->plainTextEdit_3->appendPlainText(arg1);
}

void Widget::on_comboBox_2_currentIndexChanged(int index)
{
    QString str = ui->comboBox_2->currentText()+ui->comboBox_2->currentData().toString();
    ui->plainTextEdit_3->appendPlainText(str);
}

void Widget::on_comboBox_2_currentIndexChanged(const QString &arg1)
{

}

void Widget::on_pushButton_14_clicked()
{
    ui->listWidget_3->clear();
}

void Widget::on_pushButton_15_clicked()
{
    ui->listWidget_3->clear();
    QVector<QString> qv;
    qv.append("list1");
    qv.append("list2");
    QListWidgetItem* aitem;
    foreach(const QString &qs, qv){
        aitem = new QListWidgetItem();
        aitem->setText(qs);
        aitem->setFlags(Qt::ItemIsEditable|Qt::ItemIsSelectable|Qt::ItemIsUserCheckable);
        ui->listWidget_3->addItem(aitem);
    }
}

void Widget::on_pushButton_16_clicked()
{
    ui->treeWidget_2->clear();
    QTreeWidgetItem* header = new QTreeWidgetItem();
    header->setText(0, "文件和目录");
    header->setText(1, "节点类型");
    header->setTextAlignment(0, Qt::AlignCenter);
    header->setTextAlignment(1, Qt::AlignCenter);
    ui->treeWidget_2->setHeaderItem(header);
    QTreeWidgetItem* item = new QTreeWidgetItem();
    item->setText(0, "图片");
    item->setText(1, "目录");
    item->setTextAlignment(0, Qt::AlignCenter);
    item->setTextAlignment(1, Qt::AlignCenter);
    item->setCheckState(0, Qt::Checked);
    ui->treeWidget_2->addTopLevelItem(item);

}

void Widget::mousePressEvent(QMouseEvent *event){
    if(event->button() == Qt::LeftButton){
        ui->label_5->move(event->pos());
        QPoint pt = event->pos();
        QPoint globpt = event->globalPos();
        qDebug() << "pos.x " << pt.x() << "pos.y " << pt.y();
        qDebug() << "globalPos.x " << globpt.x() << "gpobalPos.y " << globpt.y();
    }
}

void Widget::keyPressEvent(QKeyEvent *event){
    QPoint pt = ui->pushButton_17->pos();
    if(event->key() == Qt::Key_A){
        ui->pushButton_17->move(pt.x()-10, pt.y());
    }
    if(event->key() == Qt::Key_D){
        ui->pushButton_17->move(pt.x()+10, pt.y());
    }
    if(event->key() == Qt::Key_W){
        ui->pushButton_17->move(pt.x(), pt.y()-10);
    }
    if(event->key() == Qt::Key_S){
        ui->pushButton_17->move(pt.x(), pt.y()+10);
    }
}

void Widget::dragEnterEvent(QDragEnterEvent *event){
    if(event->mimeData()->hasUrls()){
        QString s = event->mimeData()->urls().at(0).fileName();
        qDebug() << s;
        QFileInfo filein(s);
        QString ex = filein.suffix().toUpper();
        if(ex == "PNG"){
            event->acceptProposedAction();
        }
        else{
            event->ignore();
        }
    }
    else{
        event->ignore();
    }
}

void Widget::dropEvent(QDropEvent *event){
    QString s = event->mimeData()->urls().at(0).path();
    s = s.right(s.length()-1);
    QPixmap px(s);
    ui->label_6->setPixmap(px);
    event->accept();
}

void Widget::on_pushButton_35_clicked()
{
    ui->plainTextEdit_4->clear();
}

void Widget::on_pushButton_18_clicked()
{
    QString curPath = QCoreApplication::applicationDirPath();
    QString fn = QFileDialog::getOpenFileName(this, "选择一个文件", curPath, "图片(*.jpg);;所有文件(*.*)");
    ui->plainTextEdit_4->appendPlainText(fn+"\n");
}

void Widget::on_pushButton_19_clicked()
{
    QString curPath = QCoreApplication::applicationDirPath();
    QStringList fns = QFileDialog::getOpenFileNames(this, "选择多个文件", curPath, "图片(*.jpg);;所有文件(*.*)");
    for(auto fn : fns){
        ui->plainTextEdit_4->appendPlainText(fn+"\n");
    }
}

void Widget::on_pushButton_20_clicked()
{
    QString curPath = QCoreApplication::applicationDirPath();
    QString ed = QFileDialog::getExistingDirectory(this, "选择一个目录", curPath);
    ui->plainTextEdit_4->appendPlainText(ed+"\n");
}

void Widget::on_pushButton_21_clicked()
{
    QString curPath = QCoreApplication::applicationDirPath();
    QString sf = QFileDialog::getSaveFileName(this, "保存文件", curPath, "图片(*.jpg);;所有文件(*.*)");
    ui->plainTextEdit_4->appendPlainText(sf+"\n");
}

void Widget::on_pushButton_22_clicked()
{
    QPalette p = ui->plainTextEdit_4->palette();
    QColor c = p.color(QPalette::Text);
    QColor qc = QColorDialog::getColor(c, this, "选择颜色");
    if(qc.isValid()){
        p.setColor(QPalette::Text, qc);
        ui->plainTextEdit_4->setPalette(p);
    }
}

void Widget::on_pushButton_23_clicked()
{
    QFont f = ui->plainTextEdit_4->font();
    bool ok = false;
    QFont qf = QFontDialog::getFont(&ok, f);
    if(ok){
        ui->plainTextEdit_4->setFont(qf);
    }
}

void Widget::on_pushButton_24_clicked()
{
    QProgressDialog dp("正在复制文件..", "取消", 0, 200, this);
    dp.setWindowTitle("复制文件");
    dp.setWindowModality(Qt::WindowModal);
    QElapsedTimer qe;
    for(int i = 0; i <= 200; i++){
        dp.setValue(i);
        dp.setLabelText(QString::asprintf("正在复制文件 第%d个", i));
        qe.start();
        while(true){
            if(qe.elapsed() > 30){
                break;
            }
        }
        if(dp.wasCanceled()){
            break;
        }
    }
}



void Widget::on_pushButton_31_clicked()
{
    QString dt = "输入文字对话框";
    QString tl = "请输入文件名";
    QString ii = "新建文件.txt";
    QLineEdit::EchoMode em = QLineEdit::Password;
    bool ok = false;
    QString t = QInputDialog::getText(this, dt, tl, em, ii, &ok);
    if(ok && !t.isEmpty()){
        ui->plainTextEdit_4->appendPlainText(t);
    }
}

void Widget::on_pushButton_25_clicked()
{
    QString t = "question消息框";
    QString s = "文件已修改，是否保存?";
    int res = QMessageBox::question(this, t, s, QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel);
    if(res == QMessageBox::Yes){
        ui->plainTextEdit_4->appendPlainText("QMessageBox消息框，Yes被选中");
    }
}

void Widget::on_pushButton_26_clicked()
{
    QString t = "infomation消息框";
    QString s = "文件已保存";
    QMessageBox::information(this, t, s);
}

void Widget::on_pushButton_27_clicked()
{

}
