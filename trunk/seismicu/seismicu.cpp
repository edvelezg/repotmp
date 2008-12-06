#include <QtGui>
#include "seismicu.h"

SeismicU::SeismicU(QWidget *parent)
: QDialog(parent)
{
    setupUi(this);

    QPushButton *convertButton =
        buttonBox->button(QDialogButtonBox::Ok);
    convertButton->setText(tr("&Run"));
    convertButton->setEnabled(true);
    outputTextEdit->append("Lol" );

    connect(convertButton, SIGNAL(clicked()),
        this, SLOT(runScript()));
    //  connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
    connect(&process, SIGNAL(readyReadStandardError()),
        this, SLOT(updateOutputTextEdit()));
    connect(&process, SIGNAL(finished(int, QProcess::ExitStatus)),
        this, SLOT(processFinished(int, QProcess::ExitStatus)));
    connect(&process, SIGNAL(error(QProcess::ProcessError)),
        this, SLOT(processError(QProcess::ProcessError)));
}


void SeismicU::runScript()
{
    outputTextEdit->clear();

    QFile file("script.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&file);
    out << "#!/bin/sh																						  " << endl;
    out << "# Sufdmod2 --- example script for sufdmod2                                                      " << endl;
    out << "# finite-difference modeling: part 1, the movie                                                 " << endl;
    out << "# Author: John Stockwell                                                                        " << endl;
    out << "                                                                                                " << endl;
    out << "WIDTH=450                                                                                       " << endl;
    out << "HEIGHT=450                                                                                      " << endl;
    out << "WIDTHOFF1=10                                                                                    " << endl;
    out << "WIDTHOFF2=500                                                                                   " << endl;
    out << "HEIGHTOFF1=50                                                                                   " << endl;
    out << "HEIGHTOFF2=530                                                                                  " << endl;
    out << "                                                                                                " << endl;
    out << "n1=100 d1=5 f1=0.0 label1=\"Depth (km)\"                                                        " << endl;
    out << "n2=100 d2=5 f2=0.0 label2=\"Distance (km)\"                                                     " << endl;
    out << "xs=250 zs=50 hsz=50 vsx=250 verbose=2                                                           " << endl;
    out << "vsfile=\"vseis.out\" ssfile=\"sseis.out\" hsfile=\"hseis.out\"                                  " << endl;
    out << "tmax=.4 mt=5 fpeak=35 fmax=40                                                                   " << endl;

    // Setting the arguments for sh.
    QStringList args;
    args << "script.txt";
    outputTextEdit->append(args.at(0));
    process.setWorkingDirectory("/Users/Naix/Tmp/repotmp/seismicu");
    outputTextEdit->append(process.workingDirectory());

    // Setting the Environment for Seismic Unix
    QStringList env = QProcess::systemEnvironment();
    process.setEnvironment(env);

    env << "CWPROOT=/opt/SU";
    env << "PATH=$PATH:/opt/SU/bin";

    process.start("sh", args);
}


void SeismicU::processFinished(int exitCode,
QProcess::ExitStatus exitStatus)
{
    if (exitStatus == QProcess::CrashExit) {
        outputTextEdit->append(tr("Conversion program crashed"));
    }
    else if (exitCode != 0) {
        outputTextEdit->append(QString("Conversion failed, code=%1").arg(exitCode));
    }
    else {
        outputTextEdit->append(tr("File %1 created").arg(targetFile));
    }
    buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
}


void SeismicU::processError(QProcess::ProcessError error)
{
    if (error == QProcess::FailedToStart) {
        outputTextEdit->append(tr("Conversion program not found"));
        buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
    }
}


void SeismicU::updateOutputTextEdit()
{
    QByteArray newData = process.readAllStandardError();
    QString text = outputTextEdit->toPlainText()
        + QString::fromLocal8Bit(newData);
    outputTextEdit->setPlainText(text);
}
