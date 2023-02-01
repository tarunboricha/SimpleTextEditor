#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QtCore>
#include <QColorDialog>
#include <QTextCursor>
#include <QTextCharFormat>
#include <QtWidgets>
#include <QtCore>
#include <QtGui>

QT_BEGIN_NAMESPACE
class QTextEdit;
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_actionBold_triggered();

    void on_actionNew_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionSave_As_triggered();

    void on_actionCut_triggered();

    void on_actionCopy_triggered();

    void on_actionPaste_triggered();

    void on_actionItalic_triggered();

    void subscript_Checked();

    void superscript_Checked();

private:
    Ui::MainWindow *ui;
    QString mFilename;
    QTextEdit *textEdit;
    QPointer<QAction> subScript = nullptr;
    QPointer<QAction> superScript = nullptr;
};
#endif // MAINWINDOW_H
