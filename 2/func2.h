#ifndef FUNC2_H
#define FUNC2_H

#include <QRegularExpression>
#include <QWidget>

namespace Ui {
class func2;
}

class func2 : public QWidget
{
    Q_OBJECT

public:
    explicit func2(QWidget *parent = nullptr);
    ~func2();

    enum RexType {
        NoFilter,
        PureNum,
    };

private slots:
    void on_comboBox_type_currentIndexChanged(int index);

    void on_btn_filter_released();

private:
    void init();
    QString to_str(int type);

private:
    Ui::func2 *ui;
    QString filter;
    QRegularExpression regex;
};

#endif // FUNC2_H
