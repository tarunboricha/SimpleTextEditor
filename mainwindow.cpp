#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    textEdit = new QTextEdit(this);
    setCentralWidget(textEdit);
    subScript = new QAction("Sub", this);
    subScript -> setIcon(QIcon::fromTheme(":Images/icons8-subscript-30.png"));
    subScript->setCheckable(true);
    subScript->setChecked(false);
    connect(subScript, SIGNAL(triggered()), this, SLOT(subscript_Checked()));

    superScript = new QAction("Super", this);
    superScript -> setIcon(QIcon::fromTheme(":Images/icons8-superscript-30.png"));
    superScript->setCheckable(true);
    superScript->setChecked(false);
    connect(superScript, SIGNAL(triggered()), this, SLOT(superscript_Checked()));

    ui -> toolBar -> addAction(subScript);
    ui -> toolBar -> addAction(superScript);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNew_triggered(){
    mFilename =  "";
    textEdit->setPlainText("");
}

void MainWindow::on_actionOpen_triggered() {
    QString file = QFileDialog::getOpenFileName(this, "open a file");
    if(!file.isEmpty()){
        QFile sFile(file);
        if(sFile.open(QFile::ReadOnly | QFile::Text)){
            mFilename = file;
            QTextStream in(&sFile);
            QString text = in.readAll();
            sFile.close();
            textEdit->setPlainText(text);
        }
    }
}

void MainWindow::on_actionSave_triggered()
{
    if(mFilename.isEmpty()){
        on_actionSave_As_triggered();
        return;
    }
    QFile sFile(mFilename);
    if(sFile.open(QFile::WriteOnly | QFile::Text)){
        QTextStream out(&sFile);
        out << textEdit->toPlainText();
        sFile.flush();
        sFile.close();
    }
}


void MainWindow::on_actionSave_As_triggered()
{
    QString file = QFileDialog::getSaveFileName(this, "Save File");
    if(!file.isEmpty()){
        mFilename = file;
        on_actionSave_triggered();
    }
}


void MainWindow::on_actionCut_triggered()
{
    textEdit->cut();
}


void MainWindow::on_actionCopy_triggered()
{
    textEdit->copy();
}


void MainWindow::on_actionPaste_triggered()
{
    textEdit->paste();
}

void MainWindow::on_actionBold_triggered()
{
    QFont font = textEdit->currentFont();
    font.bold() ? font.setBold(false) : font.setBold(true);
    textEdit->setCurrentFont(font);
}

void MainWindow::on_actionItalic_triggered()
{
    QFont font = textEdit->currentFont();
    font.italic() ? font.setItalic(false) : font.setItalic(true);
    textEdit->setCurrentFont(font);
}

void MainWindow::superscript_Checked()
{
    subScript -> setChecked(false);
    QTextCharFormat format;
    if(superScript -> isChecked())
        format.setVerticalAlignment(QTextCharFormat::AlignSuperScript);
    else
        format.setVerticalAlignment(QTextCharFormat::AlignNormal);

    textEdit -> mergeCurrentCharFormat(format);
}

void MainWindow::subscript_Checked()
{
    superScript -> setChecked(false);
    QTextCharFormat format;

    if(subScript -> isChecked())
        format.setVerticalAlignment(QTextCharFormat::AlignSubScript);
    else
        format.setVerticalAlignment(QTextCharFormat::AlignNormal);

    textEdit -> mergeCurrentCharFormat(format);
}
