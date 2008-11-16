#ifndef SEISUNIX_H
#define SEISUNIX_H

#include <QDialog>
#include <QProcess>

#include "ui_seisunix.h"

class SeisUnix : public QDialog, private Ui::SeisUnix
{
    Q_OBJECT

public:
    SeisUnix(QWidget *parent = 0);

private slots:
    void processFinished(int exitCode, QProcess::ExitStatus exitStatus);
    void convertImage();
    void processError(QProcess::ProcessError error);


private:
    QProcess process;
    QString targetFile;
};

#endif
