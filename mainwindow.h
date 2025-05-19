#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QMessageBox>
#include "shell.h"
#include "history.h"
#include "shell_repository.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButtonAdd_clicked();

    void on_pushButtonRemove_clicked();

    void on_pushButtonFilter_clicked();

private:
    Ui::MainWindow *ui;
    shell_repository shell_repo;
    history m_history;

    void update_table();
    void show_history();
    int get_type_shell(int index);
};
#endif // MAINWINDOW_H
