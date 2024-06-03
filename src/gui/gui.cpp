#include "gui.h"
#include "./ui_gui.h"

GUI::GUI(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GUI)
{
    ui->setupUi(this);
}

GUI::~GUI()
{
    delete ui;
}

void GUI::render() 
{
    // Implementation of render method
}

void GUI::updateGUI(GUIEvent& event) 
{
    // Implementation of updateGUI method
}

void GUI::handleEvents(GUIEvent& event) 
{
    // Implementation of handleEvents method
}
void GUI::on_addbutton_clicked()
{
    QMessageBox::StandardButton reply = QMessageBox::question(this,"Warehouse","Czy chcesz wczytać dane z pliku?",QMessageBox::Yes | QMessageBox::No);
    if(reply== QMessageBox::No)
    {
        ui->stackedWidget->setCurrentIndex(1);
    }
}

void GUI::on_back_to_menu_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void GUI::on_back_to_menu_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void GUI::on_back_to_menu_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void GUI::on_settings_button_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void GUI::on_start_simulation_button_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}
