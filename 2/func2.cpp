#include "func2.h"
#include "ui_func2.h"

func2::func2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::func2)
{
    ui->setupUi(this);
    init();
}

func2::~func2()
{
    delete ui;
}

void func2::init()
{
    auto min = NoFilter;
    auto max = PureNum;
    QStringList names;
    for (int i = min; i <= max; i++) {
        names << to_str(i);
    }
    ui->comboBox_type->addItems(names);
}

QString func2::to_str(int type)
{
    if (type == NoFilter) {
        return "NoFilter";
    } else if (type == PureNum) {
        return "PureNum";
    }
    return "UnKnown";
}
void func2::on_comboBox_type_currentIndexChanged(int type)
{
    if (type == NoFilter) {
        filter = R"()";
    } else if (type == PureNum) {
        filter = R"(^[+-]?[0-9]*(\.[0-9]*)?$)";
    }
    regex.setPattern(filter);
    ui->curr_reg->setText(filter);
}

void func2::on_btn_filter_released()
{
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

