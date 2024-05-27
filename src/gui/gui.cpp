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
    ui->stackedWidget->setCurrentIndex(1);
}
