#include "widget.h"
#include <QApplication>
#include<QtDebug>
#include<QPixmap>
#include<QSplashScreen>
#include<QtSql>
#include<QVariant>
#include<QTime>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QPixmap pixmap(":/rs/a.gif");
    QSplashScreen splash(pixmap);
    splash.show();
    a.processEvents();
    Widget w;
    w.show();
    qDebug() << "ok";
    splash.finish(&w);
    qDebug() << "home path is " << QDir::homePath();
    qDebug() << "root path is " << QDir::rootPath();
    qDebug() << "temp path is " << QDir::tempPath();
    QFileInfo info(":/rs/a.gif");
    qDebug() << "size " << info.size();
    qDebug() << "isDir " << info.isDir();
    QDateTime created = info.birthTime();
    qDebug() << "created " << created.toString("yyyy-MM-dd hh:mm:ss");
    qDebug() << "lastRead " << info.lastRead().toString("yyyy-MM-dd hh:mm:ss");
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("sqlite.db");
    if(!db.open()){
        qDebug() << "open database failed " << db.lastError().text();
    }else{
        QSqlQuery query;
        bool ret = query.exec("create table if not exists member(id integer primary key autoincrement,"
                              "name varchar(10))");
        if(!ret){
            qDebug() << "failed to create table " << db.lastError().text();
        }else{
            qDebug() << "table created";
        }
    }
    // 容器类[线程安全] 建议使用STL[非线程安全]
    // QList<QString>
    // QStack
    // QQueue
    // QMap
    // QMultiMap
    // QHash
    // QMultiHash
    // QSet
    // 字符串 QString
    QString qst;
    qst[0] = QChar('2');
    qDebug() << qst.contains("1");
    float ff = qst.toFloat();
    qDebug() << QString::number(ff, 'f', 3);

    return a.exec();
}

// setProperty()
// property()
