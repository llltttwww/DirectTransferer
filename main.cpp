#include "external_functions.h"
#include <QApplication>
#include "widget.h"
#include "tdialoglogin.h"
#include <Windows.h>


int main(int argc, char *argv[])
{
    QApplication a(argc,argv);
    TDialogLogin* login=new TDialogLogin;
    if(login->exec()==QDialog::Accepted)
    {

        Widget w;
        w.show();
        return a.exec();
    }
    delete login;
}


// #include "widget.h"
// #include "tdialoglogin.h"
// #include <QApplication>
// #include "mainwindow.h"

// int main(int argc, char *argv[])
// {
//     QApplication a(argc, argv);
//     TDialogLogin* dlgLogin=new TDialogLogin;
//     if(dlgLogin->exec()==QDialog::Accepted)
//         if(true)
//         {
//             MainWindow w;
//             w.show();
//             return a.exec();
//         }
//         else
//             return 0;

// }
