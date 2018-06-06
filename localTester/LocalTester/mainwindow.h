#pragma once

#include <QMainWindow>
#include <QSettings>
#include <QString>
#include <QTimer>

#include <atomic>
#include <thread>

#include "serialportio.h"
#include "serialoverwifi.h"
#include "userio.h"
#include "jssystem.h"
#include "testexecutionenviroment.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
   Q_OBJECT

public:
   explicit MainWindow(QWidget* parent = 0);
   ~MainWindow();

private slots:
   void updateWindow();
   void launchJs(bool serialOverWifi);
   bool wifiValidate();

   void on_pickTestProgram_clicked();
   void on_startLocalTesting_clicked();
   void on_startRemoteTesting_clicked();
   void on_startTestProxy_clicked();
   void on_pickDependencyBlob_clicked();
   void on_pickSslCertificate_clicked();
   void on_refreshSerialPorts_clicked();

   void on_sendText_returnPressed();

   void on_clearTerminal_clicked();

private:
   SerialPortIO*           serialOut;
   SerialOverWifi*         wifiSerialOut;
   UserIO*                 userTerminal;
   JSSystem*               systemInterface;
   TestExecutionEnviroment testEnv;
   QSettings               appSettings;
   QString                 testProgram;
   QString                 dependencyBlob;
   QString                 sslCertPath;
   QTimer*                 refreshWindow;
   Ui::MainWindow*         ui;
};