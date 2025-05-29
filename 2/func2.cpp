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
        filter = "^[+-]?[0-9]+(\\.[0-9]*)?\\s*[cf]$";
    }
    regex.setPattern(filter);
    ui->curr_reg->setText(filter);
}

QString func2::to_str(int type)
{
    if (type == NoFilter) {
        return "NoFilter";
    } else if (type == PureNum) {
        return "PureNum";
    } else if (type == HascORf) {
        return "HascORf";
    }
    return "UnKnown";
}

void func2::on_btn_filter_released()
{
    qDebug() << "pattern" << regex.pattern();
    QString text = ui->input->toPlainText();
    QStringList lines = text.split("\n");
    QStringList matched_lines;
    for (auto &line : lines) {
        QRegularExpressionMatch match = regex.match(line.trimmed());
        if (match.hasMatch()) {
            matched_lines << line;
        }
    }
    if (!matched_lines.isEmpty()) {
        ui->output->setText(matched_lines.join("\n"));
    } else {
        ui->output->setText("false");
    }
}

