#ifndef FUNC1_H
#define FUNC1_H

#include <QElapsedTimer>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_spinBox_test1_editingFinished();

private:
    Ui::MainWindow *ui;
    QElapsedTimer timer;
    int cnt = 0;
};
#endif // FUNC1_H
