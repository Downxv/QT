#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QMessageBox>
#include<QFile>
#include<QFileInfo>
#include<QDir>
#include<QFileDialog>
#include<QTextStream>
#include<QtDebug>
#include<QFontDialog>
#include<QFont>
#include<QColor>
#include<QColorDialog>
#include<QDateTime>
#include<QCloseEvent>
#include<QListWidgetItem>
#include<QListWidget>
#include<QStringList>
#include<QTimer>
#include<QSharedMemory>
#include<QBuffer>
#include<QDataStream>
#include<QColorDialog>
#include<QFontDialog>
#include<QProgressDialog>
#include<QInputDialog>


namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

protected:
    void closeEvent(QCloseEvent* event);
    void inc();

private slots:
    void on_comfirm_clicked();
    void calSlot();
    void openFileSlot();
    void newFileSlot();
    void saveFileSlot();
    void setFontSlot();
    void setColorSlot();
    void setDateTimeSlot();
    void on_openweb_clicked();
    void on_customdialog_clicked();
    void addSlot();
    void deleteSlot();
    void showDirSlot();

    void on_listWidget_itemClicked(QListWidgetItem *item);

    void on_newscreenshot_clicked();

    void on_savescreenshot_clicked();

    void on_pushButton_clicked();

    void on_checkBox_clicked(bool checked);

    void on_checkBox_2_clicked(bool checked);

    void on_checkBox_3_clicked(bool checked);

    void doColorSlot();

private:
    Ui::Widget *ui;
    QPixmap pixmap;
    QSharedMemory* memory;

signals:
    ageChanged(int val);
};

#endif // WIDGET_H
