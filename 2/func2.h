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
        ThousandsSeparator, // 千位分隔符

        RexTypeCount,  // 最后一个枚举值 + 1
    };

private slots:
    void on_comboBox_type_currentIndexChanged(int index);
    void on_btn_filter_released();
    void on_btn_other_released();

private:
    void init();
    QString to_str(int type);

    void update_regex_option();
    bool set_reg_pattern(const QString &filter);
    void do_filter();

private:
    Ui::func2 *ui;
    QRegularExpression regex;
};

#endif // FUNC2_H
