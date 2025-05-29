#include "func1.h"
#include <QApplication>
#include "func2.h"

#define test2

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
#ifdef test2
    /// func2, QRegularExpression
    func2 w;
    w.show();
#endif

#ifdef test1
    /// func1, QElapsedTimer.elapsed()
    MainWindow w;
    w.show();
#endif
    return a.exec();
}
