#include "func2.h"
#include "ui_func2.h"

func2::func2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::func2)
{
    ui->setupUi(this);
    setWindowTitle("func2");
    init();
}

func2::~func2()
{
    delete ui;
}

void func2::init()
{
    QStringList names;
    for (int i = 0; i < RexTypeCount; i++) {
        names << to_str(i);
    }
    ui->comboBox_type->addItems(names);

    connect(ui->checkBox_case_insensi, &QCheckBox::checkStateChanged, this, [this](Qt::CheckState state){
        if (state == Qt::CheckState::Checked) {
            regex.setPatternOptions(QRegularExpression::CaseInsensitiveOption);
        } else {
            regex.setPatternOptions(QRegularExpression::NoPatternOption);
        }
    });
}

void func2::on_curr_reg_returnPressed()
{
    // ui输入字面量即可,不需要考虑转义
    // ui输入   "^[+-]?[0-9]+(\.[0-9]*)?$"
    // 控制台打印"^[+-]?[0-9]+(\\.[0-9]*)?$"
    QRegularExpression re(ui->curr_reg->text().trimmed());
    if (!re.isValid()) {
        ui->output->setText("Invalid regex");
        return;
    }
    regex = re;
    on_btn_filter_released();
}

void func2::on_comboBox_type_currentIndexChanged(int type)
{
    QString filter;
    if (type == NoFilter) {
        filter = "";
    } else if (type == PureNum) {
        filter = "^[+-]?[0-9]+(\\.[0-9]*)?$";
    } else if (type == HascORf) {
        filter = "^[+-]?([0-9]+)(\\.[0-9]*)?\\s*[cf]$";
    } else if (type == IgnoreBeginxx) {
        /// (?!x), 不能包含x
        ///  .*? , 非贪婪匹配：尽量少地匹配任意字符。
        filter = "^(?!.*font-size).*?([0-9]+px)";
    } else if (type == MustContainxx) {
        /// (?=x), 必须包含x
        filter = "(?=.*border)";
    }
    regex.setPattern(filter);
    ui->curr_reg->setText(filter);
    on_btn_filter_released();
}

QString func2::to_str(int type)
{
    if (type == NoFilter) {
        return "NoFilter";
    } else if (type == PureNum) {
        return "PureNum";
    } else if (type == HascORf) {
        return "HascORf";
    } else if (type == IgnoreBeginxx) {
        return "IgnoreBeginxx";
    } else if (type == MustContainxx) {
        return "MustContainxx";
    }
    return "UnKnown";
}

void func2::on_btn_filter_released()
{
    qDebug() << "pattern" << regex.pattern();
    ui->out_capture->clear();

    QString text = ui->input->toPlainText();
    QStringList lines = text.split("\n");
    QStringList matched_lines;
    for (auto &line : lines) {
        QRegularExpressionMatch match = regex.match(line.trimmed());
        QStringList captured_lines;
        if (match.hasMatch()) {
            auto cnt = regex.captureCount();// 不含group 0
            // 如果没有捕获列表,match.captured(0)是空的
            // 所有这里只能 << line, 不能match.captured(0)
            matched_lines << line;
            for (int i = 0; i < cnt; ++i) {
                captured_lines << match.captured(i + 1);
            }
            ui->out_capture->append("[" + captured_lines.join("] [") +"]");
        }
    }
    if (!matched_lines.isEmpty()) {
        ui->output->setText(matched_lines.join("\n"));
    } else {
        ui->output->setText("false");
    }
}

