#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    ui->tableWidgetHistory->setColumnCount(4);
    ui->tableWidgetHistory->setAlternatingRowColors(true);
    ui->tableWidgetHistory->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidgetHistory->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidgetHistory->horizontalHeader()->setStretchLastSection(false);
    ui->tableWidgetHistory->verticalHeader()->setVisible(false);


    ui->tableWidgetHistory->setColumnWidth(0, 80);
    ui->tableWidgetHistory->setColumnWidth(1, 120);
    ui->tableWidgetHistory->setColumnWidth(2, 60);
    ui->tableWidgetHistory->setColumnWidth(3, 200);



     QVector<shell*> m_shells = shell_repo.getAll();
     for(shell* sh : m_shells) {
        sh->subscribe(&m_history);
     }

    update_table();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButtonAdd_clicked()
{
    int count = ui->lineEditAddCount->text().toInt();
    int index = ui->comboBoxType->currentIndex();
    int type = get_type_shell(index);

    shell* sh = shell_repo.find(type);
    if (sh == nullptr) {
        sh = new shell(type, 0);
        sh->subscribe(&m_history);
        sh->add_instock(count);

        shell_repo.add_shell(sh);
    }
    else {
         sh->add_instock(count);
         shell_repo.update(sh);
    }

    update_table();
}

void MainWindow::update_table()
{
    shell_repo.sort_by_instock();

    QVector<shell*> m_shells = shell_repo.getAll();

    ui->tableWidget->setRowCount(m_shells.size());

    for(int i = 0; i < m_shells.size(); i++) {
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(QString::number(m_shells[i]->get_type())));
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(QString::number(m_shells[i]->get_instock())));
        ui->tableWidget->setItem(i, 2, new QTableWidgetItem(QString::number(m_shells[i]->get_used())));
        ui->tableWidget->setItem(i, 3, new QTableWidgetItem(QString::number(m_shells[i]->get_total())));
    }

    show_history();
}

void MainWindow::show_history()
{
    QVector<historyItem> filtered_items;
    int index = ui->comboBoxFilterType->currentIndex();

    if (index == 0) {
        filtered_items = m_history.get_items();
    } else {
        int type = get_type_shell(index-1);

         QVector<historyItem> items = m_history.get_items();
         for(int i = 0; i < items.size(); i++) {
             if (items[i].get_type_shell() == type) {
                 filtered_items.push_back(items[i]);
             }
         }
    }

    ui->tableWidgetHistory->setRowCount(filtered_items.size());
    for(int i = 0; i < filtered_items.size(); i++) {
        ui->tableWidgetHistory->setItem(i, 0, new QTableWidgetItem(QString::number(filtered_items[i].get_type_shell())));
        ui->tableWidgetHistory->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(filtered_items[i].get_type_operation())));
        ui->tableWidgetHistory->setItem(i, 2, new QTableWidgetItem(QString::number(filtered_items[i].get_count())));
        ui->tableWidgetHistory->setItem(i, 3, new QTableWidgetItem(filtered_items[i].get_date().toString()));
    }
}

int MainWindow::get_type_shell(int index)
{
    int type;
    if (index == 0) {
        type = 60;
    }
    else if (index == 1) {
        type = 82;
    }
    else if (index == 2) {
        type = 100;
    }
    else if (index == 3) {
        type = 122;
    }
    else {
        type = 152;
    }
    return type;
}


void MainWindow::on_pushButtonRemove_clicked()
{
    int count = ui->lineEditAddCount->text().toInt();
    int index = ui->comboBoxType->currentIndex();
    int type = get_type_shell(index);

    shell* sh = shell_repo.find(type);
    if (sh == nullptr) {
        QMessageBox::warning(this, "Warning","Invalid shell type.");
    }
    else {
        if (sh->get_instock() >= count) {
            sh->add_used(count);
            shell_repo.update(sh);
            update_table();
        }
        else {
            QMessageBox::warning(this, "Warning","Insufficient quantity in stock.");
        }
    }
}


void MainWindow::on_pushButtonFilter_clicked()
{
    show_history();
}

