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

    connect(ui->checkBox_case_insensi, &QCheckBox::checkStateChanged, this, [this](){
        update_regex_option();
    });
    connect(ui->checkBox_ignore_space, &QCheckBox::checkStateChanged, this, [this](){
        update_regex_option();
    });

    on_comboBox_type_currentIndexChanged(RexTypeCount - 1);
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
    ui->comboBox_type->blockSignals(true);
    ui->comboBox_type->setCurrentIndex(type);
    ui->comboBox_type->blockSignals(false);

    QString filter;
    if (type == NoFilter) {
        filter = "";
    } else if (type == PureNum) {
        filter = "^[+-]?[0-9]+(\\.[0-9]*)?$";
    } else if (type == HascORf) {
        filter = "^[+-]?([0-9]+)(\\.[0-9]*)?\\s*[cf]$";
    }else if (type == IgnoreBeginxx) {
        /// (?!x), 不能包含x
        ///  .*? , 非贪婪匹配：尽量少地匹配任意字符。
        filter = "^(?!.*font-size).*?([0-9]+px)";
    } else if (type == MustContainxx) {
        /// (?=x), 必须包含x
        filter = "(?=.*border)";
    } else if (type == Beginxx) {
        /// MustContainxx和Beginxx几乎一致,区别就在于有没有脱字符
        filter = "^border(.*)";
    } else if (type == ExtractContent) {
        filter = "^From:(\\S+) \\(([^()]*)\\)";
    } else if (type == ThousandsSeparator) {
        /// Qt不能逆序查找
        filter = "(\\d)(?=(\\d{3})+(?!\\d))";
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
    }else if (type == IgnoreBeginxx) {
        return "IgnoreBeginxx";
    } else if (type == MustContainxx) {
        return "MustContainxx";
    } else if (type == Beginxx) {
        return "Beginxx";
    } else if (type == ExtractContent) {
        return "ExtractContent";
    } else if (type == ThousandsSeparator) {
        return "ThousandsSeparator";
    }
    return "UnKnown";
}

void func2::update_regex_option()
{
    QRegularExpression::PatternOptions flag = QRegularExpression::NoPatternOption;
    if (ui->checkBox_case_insensi->isChecked()) {
        flag |= QRegularExpression::PatternOption::CaseInsensitiveOption;
    }
    if (ui->checkBox_ignore_space->isChecked()) {
        flag |= QRegularExpression::PatternOption::ExtendedPatternSyntaxOption;
    }
    regex.setPatternOptions(flag);
}

void func2::on_btn_filter_released()
{
    qDebug() << "pattern" << regex.pattern();
    ui->out_capture->clear();

    QString text = ui->input->toPlainText();
    QStringList lines = text.split("\n");
    QStringList matched_lines;
    for (auto &line : lines) {
        // match返回的是第一次匹配到结果
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


void func2::on_btn_other_released()
{
    {
        qDebug() << "-----------ThousandsSeparator";
        // 迭代+替换
        // 多次匹配+替换
        QString num = "12345678901";
        QString formatted = num.replace(regex, "\\1,");
        qDebug() <<"12345678901" << formatted;
    }

    {
        qDebug() << "-----------cpature by <name>";
        QRegularExpression re("^(?<date>\\d+)/(?<month>\\d+)/(?<year>\\d+)$");
        QRegularExpressionMatch match = re.match("08/12/1985");
        if (match.hasMatch()) {
            QString date = match.captured("date"); // date == "08"
            QString month = match.captured("month"); // month == "12"
            QString year = match.captured("year"); // year == 1985
            qDebug() << "date" << date
                     << "month" << month
                     << "year" << year;
        }
    }

    {
        qDebug() << "-----------global match";
        QRegularExpression re("\\w+");
        QRegularExpressionMatchIterator i = re.globalMatch("the quick fox");
        QStringList words;
        while (i.hasNext()) {
            auto match = i.next();
            QString word = match.captured(0);
            words << word;
        }
        qDebug() << words;

    }
}

