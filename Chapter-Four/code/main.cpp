// #define STB_IMAGE_IMPLEMENTATION
// #include "stb_image.h"

#include "widget.h"
#include <QApplication>
#include <QCoreApplication>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
    return a.exec();
}
