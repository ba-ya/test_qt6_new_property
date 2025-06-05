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
        PureNum,// 纯数字
        HascORf,// 含c/f温度单位
        IgnoreBeginxx,// 忽略以xx开始的
        MustContainxx,// 必须包含xx
        Beginxx,// 以xx开始的
        ExtractContent,

        RexTypeCount,  // 最后一个枚举值 + 1
    };

private slots:
    void on_comboBox_type_currentIndexChanged(int index);
    void on_btn_filter_released();
    void on_curr_reg_returnPressed();

private:
    void init();
    QString to_str(int type);

private:
    Ui::func2 *ui;
    QRegularExpression regex;
};

#endif // FUNC2_H
