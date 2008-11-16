#include <QApplication>
#include "seisunix.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    SeisUnix dialog;
    dialog.show();
    return app.exec();
}
