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
#include<QElapsedTimer>
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
    void doASlot(int val);

    void on_checkBox_4_clicked(bool checked);

    void on_checkBox_5_clicked(bool checked);

    void on_radioButton_4_clicked(bool checked);

    void on_radioButton_5_clicked(bool checked);

    void on_radioButton_4_clicked();

    void on_radioButton_5_clicked();

    void on_timeEdit_userTimeChanged(const QTime &time);

    void on_dateEdit_userDateChanged(const QDate &date);

    void on_dateTimeEdit_dateChanged(const QDate &date);

    void on_dateTimeEdit_dateTimeChanged(const QDateTime &dateTime);

    void on_calendarWidget_selectionChanged();

    void do_timeout();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_10_clicked();

    void on_checkBox_6_stateChanged(int arg1);

    void on_checkBox_6_clicked(bool checked);

    void on_pushButton_11_clicked();

    void on_pushButton_12_clicked();

    void on_comboBox_currentTextChanged(const QString &arg1);

    void on_comboBox_2_currentIndexChanged(int index);

    void on_comboBox_2_currentIndexChanged(const QString &arg1);

    void on_pushButton_14_clicked();

    void on_pushButton_15_clicked();

    void on_pushButton_16_clicked();

    void on_pushButton_35_clicked();

    void on_pushButton_18_clicked();

    void on_pushButton_19_clicked();

    void on_pushButton_20_clicked();

    void on_pushButton_21_clicked();

    void on_pushButton_22_clicked();

    void on_pushButton_23_clicked();

    void on_pushButton_24_clicked();

    void on_pushButton_31_clicked();

    void on_pushButton_25_clicked();

    void on_pushButton_26_clicked();

    void on_pushButton_27_clicked();

private:
    Ui::Widget *ui;
    QPixmap pixmap;
    QSharedMemory* memory;
    QTimer* qtimer;
    QElapsedTimer* qcount;

signals:
    ageChanged(int val);

    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);

    // QWidget interface
protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);
};

#endif // WIDGET_H
