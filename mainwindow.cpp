#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDir>
#include <QSettings>
#include <QSqlError>
#include <QActionGroup>
#include <QContextMenuEvent>
#include <QInputDialog>
#include "dialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , db(new database)
    , MyProxyModel(new proxyModel(this))
{
    ui->setupUi(this);

    readSettings();
    new_menu=ui->menuMenu;
    if (!db->connect(this)) {
        QMessageBox::warning(this,
                             tr("Application"),
                             db->getDatabase().lastError().text());
    }
    ui->tableView->setModel(MyProxyModel);
    ui->tableView->setSortingEnabled(true);

    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);

    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);

    auto model = db->getModel();
    model->select();
    model->setHeaderData(0, Qt::Horizontal, tr("Id"));
    model->setHeaderData(1, Qt::Horizontal, tr("Bolezn"));
    model->setHeaderData(2, Qt::Horizontal, tr("Temp"));
    model->setHeaderData(3, Qt::Horizontal, tr("Nausea"));
    model->setHeaderData(4, Qt::Horizontal, tr("Stomach hurts"));
    model->setHeaderData(5, Qt::Horizontal, tr("Procedure"));
    model->setHeaderData(6, Qt::Horizontal, tr("Id_med"));
    MyProxyModel->setSourceModel(model);
    ui->tableView->sortByColumn(0, Qt::AscendingOrder);
    ui->tableView->hideColumn(0);
    ui->tableView->hideColumn(6);
    ui->tableView->resizeColumnsToContents();
    connect(ui->groupBox_2, &QGroupBox::clicked, this, &MainWindow::filter);
    connect(ui->checkBox_2, &QCheckBox::stateChanged, this, &MainWindow::filter);
    connect(ui->checkBox_3, &QCheckBox::stateChanged, this, &MainWindow::filter);
    connect(ui->checkBox_4, &QCheckBox::stateChanged, this, &MainWindow::filter);
    connect(ui->bol,&QLineEdit::textChanged, this,&MainWindow::filter);
    connect(ui->proc,&QLineEdit::textChanged, this,&MainWindow::filter);
}


MainWindow::~MainWindow()
{
    writeSettings();
    delete db;
    delete MyProxyModel;
    delete ui;
}

void MainWindow::contextMenuEvent( QContextMenuEvent* event )
{
    if(new_menu)
    {
        new_menu->exec(event->globalPos());
    }
}


void MainWindow::on_actionAdd_triggered()
{
    auto dialog = new Dialog(this);
    dialog->setAttribute(Qt::WA_DeleteOnClose);
    dialog->setWindowTitle(tr("Add bolezn"));
    connect(dialog, &Dialog::sendBolezn, this, &MainWindow::AddBolezn);
    dialog->show();
}

void MainWindow::AddBolezn(class Bolezn bolezn)
{
    if (!db->addBolezn(bolezn)) {
        QMessageBox::warning(this,
                             tr("ERROR"),
                             tr("Error adding a bolezn!"));
        return;
    }
    db->getModel()->select();
    ui->tableView->resizeColumnsToContents();
}


void MainWindow::on_actionEdit_triggered()
{
    QModelIndex index = ui->tableView->currentIndex();
    Bolezn bolezn(index.siblingAtColumn(1).data().toString(),
                  index.siblingAtColumn(2).data().toBool(),
                  index.siblingAtColumn(3).data().toBool(),
                  index.siblingAtColumn(4).data().toBool(),
                  index.siblingAtColumn(5).data().toString(),
                  index.siblingAtColumn(6).data().toInt());


    auto dialog = new Dialog(bolezn, this);
    dialog->setAttribute(Qt::WA_DeleteOnClose);
    dialog->setWindowTitle(tr("Bolezn editing"));
    connect(dialog, &Dialog::sendBolezn, this, &MainWindow::EditBolezn);
    dialog->show();
}


void MainWindow::on_actionDelete_triggered()
{
    int id = ui->tableView->currentIndex().siblingAtColumn(0).data().toInt();
    if (!db->deleteBolezn(id))
    {
        QMessageBox::warning(this,
                             tr("ERROR"),
                             tr("Error deleting a bolezn!"));

        return;
    }
    db->getModel()->select();
    ui->tableView->resizeColumnsToContents();
}

void MainWindow::EditBolezn(Bolezn bolezn)
{
    int id = ui->tableView->currentIndex().siblingAtColumn(0).data().toInt();
    if (!db->editBolezn(id, bolezn)) {
        QMessageBox::warning(this,
                             tr("ERROR"),
                             tr("Error editing a bolezn!"));

        return;
    }

    db->getModel()->select();
    ui->tableView->resizeColumnsToContents();
}

void MainWindow::writeSettings()
{
    QSettings settings("Settings", "setting");
    settings.beginGroup("MainWindowGeometry");
    settings.setValue("size", size());
    settings.setValue("position", pos());
    settings.endGroup();
    settings.beginGroup("MainWindowLanguage");
    settings.setValue("language",language);
    settings.endGroup();
}

void MainWindow::readSettings()
{
    QSettings settings("Settings", "setting");
    settings.beginGroup("MainWindowGeometry");
    resize(settings.value("size", QSize(400, 400)).toSize());
    move(settings.value("position", QPoint(200, 200)).toPoint());
    settings.endGroup();
    settings.beginGroup("MainWindowLanguage");
    language=settings.value("language").toString();
    qtLanguageTranslator.load("QtLanguage_" + language, ".");
    qApp->installTranslator(&qtLanguageTranslator);
    settings.endGroup();
}

void MainWindow::on_actionExit_triggered()
{
    this->close();
}


void MainWindow::on_actionAbout_author_triggered()
{
    QMessageBox::about(this,tr("About author"), tr("Zobova Nataliia Yuryevna ICTMS 3-6"));
}

void MainWindow::on_actionChange_language_triggered()
{
    bool ok;
    QStringList list;
    list<<"Russian"<<"English";
    language=QInputDialog::getItem(this, tr("Language"),tr("Set Language"), list,1,false,&ok);
    if(language=="Russian")
        language="ru";
    if(language=="English")
        language="en";
    if(!ok||language.isEmpty())
        QMessageBox::warning(this,tr("Warning"), tr("Language is not set"));
    else
    {QMessageBox::about(this,tr("Language"),tr("Set ")+language+tr(" language"));
        if(language=="ru")
        {
            qtLanguageTranslator.load("QtLanguage_" + language, ".");
            qApp->installTranslator(&qtLanguageTranslator);
        }
        else
        {
            qtLanguageTranslator.load("QtLanguage_en.");
            qApp->installTranslator(&qtLanguageTranslator);
        }
    }
    auto model = db->getModel();
    model->select();
    model->setHeaderData(1, Qt::Horizontal, tr("Bolezn"));
    model->setHeaderData(2, Qt::Horizontal, tr("Temp"));
    model->setHeaderData(3, Qt::Horizontal, tr("Nausea"));
    model->setHeaderData(4, Qt::Horizontal, tr("Stomach hurts"));
    model->setHeaderData(5, Qt::Horizontal, tr("Procedure"));
    model->setHeaderData(6, Qt::Horizontal, tr("Id_med"));
    MyProxyModel->setSourceModel(model);
    ui->tableView->sortByColumn(0, Qt::AscendingOrder);
    ui->tableView->hideColumn(0);
    ui->tableView->hideColumn(6);
    ui->tableView->resizeColumnsToContents();
}

void MainWindow::changeEvent(QEvent *e)
{
    if(e->type()==QEvent::LanguageChange)
        ui->retranslateUi(this);
}

void MainWindow::on_tableView_doubleClicked(const QModelIndex &index)
{
    on_actionEdit_triggered();

}

void MainWindow::filter()
{
    int count=ui->tableView->model()->rowCount();
    qDebug()<<count;
    if(ui->groupBox_2->isChecked()) {
        QString filterBolezn = ui->bol->text();
        QString filterProcedure = ui->proc->text();
        int filterHighTemp = ui->checkBox_2->checkState();
        qDebug()<<filterHighTemp;
        int filterNausea = ui->checkBox_3->checkState();
        int filterStomachHurts = ui->checkBox_4->checkState();
        for(int i=0; i<count;i++)
        {
            QAbstractItemModel *M = ui->tableView->model();
            QString Bolezn = M->data(M->index(i,1,QModelIndex())).toString();
            QString Procedure = M->data(M->index(i,5,QModelIndex())).toString();
            bool HighTemp = M->data(M->index(i,2,QModelIndex())).toBool();
            bool Nausea = M->data(M->index(i,3,QModelIndex())).toBool();
            bool StomachHurts = M->data(M->index(i,4,QModelIndex())).toBool();
            bool flag = true;

            if(filterBolezn==""	|| Bolezn.contains(filterBolezn)) flag&=true; else flag&=false;
            if(filterProcedure==""	|| Procedure.contains(filterProcedure)) flag&=true; else flag&=false;
            if(filterHighTemp==2 && HighTemp==true)
                flag&=true;
            else if(filterHighTemp==1 && HighTemp==false)
                flag&=true;
            else if(filterHighTemp==0)
                flag&=true;
            else
                flag&=false;

            if(filterNausea==2 && Nausea==true)
                flag&=true;
            else if(filterNausea==1 && Nausea==false)
                flag&=true;
            else if(filterNausea==0)
                flag&=true;
            else
                flag&=false;

            if(filterStomachHurts==2 && StomachHurts==true)
                flag&=true;
            else if(filterStomachHurts==1 && StomachHurts==false)
                flag&=true;
            else if(filterStomachHurts==0)
                flag&=true;
            else
                flag&=false;
           /* if(filterNausea==true) flag&=true; else flag&=false;
            if(filterStomachHurts==true) flag&=true; else flag&=false;*/


            if(flag)
                ui->tableView->showRow(i);
            else
                ui->tableView->hideRow(i);
        }
    }
    else{
        for(int i=0;i<count;i++)
        {
            ui->tableView->showRow(i);
        }
    }
}

void MainWindow::getMedicaments()
{
    int id = ui->tableView->currentIndex().siblingAtColumn(0).data().toInt();
    QString res;
    res = db->getMedicaments(id);
    ui->Medi->setText(res);
}

void MainWindow::getKolvo()
{
    int id = ui->tableView->currentIndex().siblingAtColumn(0).data().toInt();
    QString res;
    res = db->getKolvo(id);
    ui->kolvo->setText(res);
}

void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    getMedicaments();
    getKolvo();
}
