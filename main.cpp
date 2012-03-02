#include <QtGui/QApplication>
#include <QTextCodec>
#include <QDate>
#include <QDebug>
#include <QFile>
#include <QDateTime>
#include <QTextStream>
#include <QSettings>
#include <QFile>
#include "def_config.h"
#include "mesmainwindow.h"

//注册Log消息
void customMessageHandler(QtMsgType type, const char *msg)
{
    QString txt;
    switch (type) {
    case QtDebugMsg:
        txt = QString("Debug: %1").arg(msg);
        break;
    case QtWarningMsg:
        txt = QString("Warning: %1").arg(msg);
    break;
    case QtCriticalMsg:
        txt = QString("Critical: %1").arg(msg);
    break;
    case QtFatalMsg:
        txt = QString("Fatal: %1").arg(msg);
        abort();
    }

    QFile outFile(QDate::currentDate().toString(DEF_DATEFORMET)+"-mes.log");
    outFile.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream ts(&outFile);
    ts << QDateTime::currentDateTime().toString(DEF_TIMEFORMET)<< "  "  << txt << endl;
}

//初始化环境
void InitEnv(void)
{

#ifndef QT_DEBUG //非调试才启用日志文件
    qInstallMsgHandler(customMessageHandler);
#endif
    qDebug() << QApplication::tr(" init env start ");
    //g_codec =
    QFile configFile(DEF_CONFIG_INI);
    QSettings settings(DEF_CONFIG_INI,QSettings::IniFormat);
    if(!configFile.exists()) {

        settings.setValue("main/g_codec",DEF_CODEC);
        settings.setValue("main/g_dateformat",DEF_DATEFORMET);
        settings.setValue("main/g_timeformat",DEF_TIMEFORMET);
        if(!settings.isWritable())qFatal("can not write ini file ") ;
        settings.sync();
    }
    g_codec = settings.value("main/g_codec").toString();
    g_dateformat = settings.value("main/g_codec").toString();
    g_timeformat = settings.value("main/g_timeformat").toString();
    QTextCodec* def_codec = QTextCodec::codecForName(g_codec.toAscii());
    QTextCodec::setCodecForCStrings(def_codec);
    QTextCodec::setCodecForLocale(def_codec);
    QTextCodec::setCodecForTr(def_codec);
}

//退出程序
void ExitProgram(void)
{
    qDebug() << QApplication::tr(" exit program  ");
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    InitEnv();

    MesMainWindow w;
    w.show();

    return a.exec();
}
