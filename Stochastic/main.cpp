#include <QApplication>
#include "mafenetre.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);


    MaFenetre *window = new MaFenetre();

    window->show();




    return app.exec();
}
