#ifndef MESMAINWINDOW_H
#define MESMAINWINDOW_H

#include <QMainWindow>

namespace Ui {
    class MesMainWindow;
}

class MesMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MesMainWindow(QWidget *parent = 0);
    ~MesMainWindow();

protected:
    virtual void closeEvent(QCloseEvent *);
private slots:
    void on_exit_action_triggered();

private:
    Ui::MesMainWindow *ui;
};

#endif // MESMAINWINDOW_H
