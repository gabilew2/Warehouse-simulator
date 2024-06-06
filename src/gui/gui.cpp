#include "gui.h"
#include "./ui_gui.h"

GUI::GUI(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GUI)
{
    ui->setupUi(this);
    render();
}

GUI::~GUI()
{
    delete ui;
}

void GUI::render() 
{
    interfaceState = DISABLED;

    ui -> stackedWidget -> setCurrentIndex(0);

    //Warehouse page
    Warehouse warehouse;
    warehouse.id = 1;
    warehouses.append(warehouse);
    loadCurrentWarehouseData();

    ui->productTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->productTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->productTable->setStyleSheet("QHeaderView::section { font-size: 15pt; }");

    //Settings page
    ui -> configFileEdit -> setDisabled(true);
    ui -> seedEdit -> setText(QString::number(seed));
    ui -> cyclesEdit -> setText(QString::number(cycles));
    ui -> configFileEdit -> setText(filename);

    //Simulation page
    ui->statisticList->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->statisticList->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->statisticList->setStyleSheet("QHeaderView::section { font-size: 15pt; }");

    ui->raportList->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->raportList->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->raportList->setStyleSheet("QHeaderView::section { font-size: 15pt; }");

    interfaceState = IDLE;
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
    if(warehouses[0].name == "")
    {
        warehouses[0].name = QInputDialog::getText(this, "Add warehouse", "Please enter warehouse location below: ");
        warehouses[0].capacity = QInputDialog::getInt(this, "Add warehouse", "Please enter warehouse capacity below: ");
    }
    ui->stackedWidget->setCurrentIndex(1);
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
    if(interfaceState != ACTIVE)
    {
        ui->back_to_menu_3->setDisabled(false);
        ui->stackedWidget->setCurrentIndex(0);
    }
    else
    {
        ui->back_to_menu_3->setDisabled(true);
    }
}

void GUI::on_settings_button_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void GUI::on_start_simulation_button_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void GUI::on_aboutButton_clicked()
{
    QApplication::aboutQt();
}


void GUI::on_configFileButton_clicked()
{
    filename = QFileDialog::getOpenFileName(this, "Choose setting file", "settings.csv", "*.csv");
    if(filename == "")
    {
        QMessageBox::information(this, "Settings ", "No file selected.");
        ui -> configFileEdit -> setText(filename);
    }
    else
    {
        ui -> configFileEdit -> setText(filename);

        QFile file(filename);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QMessageBox::warning(this, "Load Data", "Cannot open file.");
            return;
        }

        QTextStream in(&file);

        warehouses.clear();

        Warehouse *currentWarehouse = nullptr;

        while (!in.atEnd())
        {
            QString line = in.readLine();
            QStringList fields = line.split(",");
            if (fields[0] == "Warehouse")
            {
                Warehouse warehouse;
                warehouse.id = warehouses.size() + 1;
                warehouse.name = fields[1];
                warehouse.capacity = fields[2].toInt();
                warehouses.append(warehouse);
                currentWarehouse = &warehouses.last();
            }
            else if (fields[0] == "Product" && currentWarehouse)
            {
                if (fields.size() < 4)
                {
                    QMessageBox::warning(this, "Load Data", "Incorrect product line format.");
                    continue;
                }
                Product product;
                product.name = fields[1];
                product.price = fields[2].toDouble();
                product.quantity = fields[3].toInt();
                currentWarehouse->products.append(product);
            }
            else if (fields[0] == "Seed")
            {
                seed = fields[5].toInt();
                ui -> seedEdit -> setText(QString::number(seed));
            }
            else if (fields[0] == "Cycles")
            {
                cycles = fields[4].toInt();
                ui -> cyclesEdit -> setText(QString::number(cycles));
            }
        }
        file.close();
        loadCurrentWarehouseData();
    }
}


void GUI::on_back_to_menu_7_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void GUI::on_start_button_clicked()
{
    if(warehouses.isEmpty() || seed == 0 || cycles == 0 || warehouses[0].products.isEmpty())
    {
        QMessageBox::warning(this, "Start Simulation", "Cannot start simulation without initial conditions.");
        return;
    }

    interfaceState = ACTIVE;

    QFile file("settings.csv");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Save Data", "Cannot open file.");
        return;
    }

    QTextStream out(&file);
    out << "Type,Location/Capacity/Name/Price/Quantity/Cycles,Seed\n";

    for (const Warehouse &warehouse : warehouses)
    {
        out << "Warehouse," << warehouse.name << "," << warehouse.capacity << "\n";

        for (const Product &product : warehouse.products)
        {
            int row = ui -> statisticList -> rowCount();
            ui -> statisticList -> insertRow(row);
            ui -> statisticList -> setItem(row, 0, new QTableWidgetItem(QString::number(warehouse.id-1)));
            ui -> statisticList -> setItem(row, 1, new QTableWidgetItem(QString::number(row+1)));
            ui -> statisticList -> setItem(row, 2, new QTableWidgetItem(product.name));
            ui -> statisticList -> setItem(row, 3, new QTableWidgetItem(QString::number(product.price)));
            ui -> statisticList -> setItem(row, 4, new QTableWidgetItem(QString::number(product.quantity)));
            out << "Product," << product.name << "," << product.price << "," << product.quantity << "\n";
        }
        out << "Cycles,,,," << cycles << "\n";
        out << "Seed,,,,," << seed << "\n";
    }
    file.close();

    SimulationThread *simulationThread = new SimulationThread();
    connect(simulationThread, &SimulationThread::finished, simulationThread, &QObject::deleteLater);
    simulationThread->start();

    setupUpdateTimer();
    updateTablesFromCSV();
}



void GUI::on_addProductButton_clicked()
{
    QString name = ui->productNameEntry->text();
    QString price = ui->productPriceEntry->text();
    QString quantity = ui->productQuantityEntry->text();

    bool priceValidation, quantityValidation;
    double priceValue = price.toDouble(&priceValidation);
    int quantityValue = quantity.toInt(&quantityValidation);

    Warehouse &currentWarehouse = warehouses[currentWarehouseIndex];
    int currentCapacity = 0;
    for (const Product &product : currentWarehouse.products)
    {
        currentCapacity += product.quantity;
    }

    if(!priceValidation || !quantityValidation || priceValue < 0 || quantityValue < 0 || currentCapacity + quantityValue > currentWarehouse.capacity)
    {
        QMessageBox::warning(this, "Add Product", "Wrong product parameters or exceeding warehouse capacity.");
        return;
    }

    Product newProduct{name, priceValue, quantityValue};
    currentWarehouse.products.append(newProduct);
    loadCurrentWarehouseData();
}

void GUI::on_removeButton_clicked()
{
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    if(button)
    {
        int row = button->property("row").toInt();
        ui->productTable->removeRow(row);

        Warehouse &currentWarehouse = warehouses[currentWarehouseIndex];
        if(row < currentWarehouse.products.size())
        {
            currentWarehouse.products.removeAt(row);
        }

        for(int currentRow = row; currentRow < ui->productTable->rowCount(); ++currentRow)
        {
            QPushButton *btnRemove = qobject_cast<QPushButton *>(ui->productTable->cellWidget(currentRow, 3));
            btnRemove->setProperty("row", currentRow);
        }

        ui->productTable->update();
    }
}

void GUI::loadCurrentWarehouseData()
{
    ui->productTable->setRowCount(0);
    Warehouse &currentWarehouse = warehouses[currentWarehouseIndex];

    ui->warehouseLabel->setText("Warehouse " + QString::number(currentWarehouse.id));

    for(const Product &product : currentWarehouse.products)
    {
        int currentRow = ui->productTable->rowCount();
        ui->productTable->insertRow(currentRow);

        ui->productTable->setItem(currentRow, 0, new QTableWidgetItem(product.name));
        ui->productTable->setItem(currentRow, 1, new QTableWidgetItem(QString::number(product.price)));
        ui->productTable->setItem(currentRow, 2, new QTableWidgetItem(QString::number(product.quantity)));

        QPushButton *btnRemove = new QPushButton("Remove");
        btnRemove->setProperty("row", currentRow);
        connect(btnRemove, &QPushButton::clicked, this, &GUI::on_removeButton_clicked);
        ui->productTable->setCellWidget(currentRow, 3, btnRemove);
    }
}

void GUI::on_previousWarehouse_clicked()
{
    if (currentWarehouseIndex > 0)
    {
        currentWarehouseIndex--;
    }
    else
    {
        currentWarehouseIndex = warehouses.size() - 1;
    }
    loadCurrentWarehouseData();
}


void GUI::on_nextWarehouse_clicked()
{
    if (currentWarehouseIndex == warehouses.size() - 1)
    {
        Warehouse newWarehouse;
        newWarehouse.id = warehouses.size() + 1;
        newWarehouse.name = QInputDialog::getText(this, "Add warehouse", "Please enter warehouse location below: ");
        newWarehouse.capacity = QInputDialog::getInt(this, "Add warehouse", "Please enter warehouse capacity below: ");
        warehouses.append(newWarehouse);
        currentWarehouseIndex = warehouses.size() - 1;
    }
    else
    {
        currentWarehouseIndex = (currentWarehouseIndex + 1) % warehouses.size();
    }
    loadCurrentWarehouseData();
}


void GUI::on_removeWarehouseButton_clicked()
{
    if (warehouses.size() > 1 && currentWarehouseIndex < warehouses.size())
    {
        warehouses.removeAt(currentWarehouseIndex);
        if (currentWarehouseIndex == warehouses.size())
        {
            currentWarehouseIndex--;
        }
        loadCurrentWarehouseData();
    }
    else
    {
        QMessageBox::warning(this, "Remove Warehouse", "Cannot remove the only warehouse.");
    }
}

void GUI::setupUpdateTimer()
{
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &GUI::updateTablesFromCSV);
    timer->start(1000);
}

void GUI::updateTablesFromCSV()
{
    static int cycleCount = 0;
    ui->raportList->setRowCount(0);

    QFile fileSimulation("SimulationReport.csv");
    if (fileSimulation.open(QIODevice::ReadOnly))
    {
        QTextStream in(&fileSimulation);
        int currentWarehouseID;
        QString line = in.readLine();

        while (!in.atEnd())
        {
            line = in.readLine();
            if (line.isEmpty())
            {
                cycleCount++;
                continue;
            }
            QStringList fields = line.split(',');

            if (fields[0].contains("Warehouse ID"))
            {
                currentWarehouseID = fields[1].toInt();
            }
            else if (fields[0].contains("Product Name"))
            {
                for (int product = 0; product < ui -> statisticList -> rowCount(); ++product)
                {
                    in.readLine();
                    QTableWidgetItem* item = ui -> statisticList -> item(product, 2);
                    if (item && item->text() == fields[0])
                    {
                        ui -> statisticList -> item(product, 3)->setText(fields[1]);
                        int newQuantity = ui -> statisticList -> item(product, 4)->text().toInt() + fields[2].toInt();
                        ui -> statisticList -> item(product, 4)->setText(QString::number(newQuantity));
                        continue;
                    }
                }
            }
            else if (fields[0].contains("Operational Costs"))
            {
                in.readLine();
                int row = ui -> raportList -> rowCount();
                ui -> raportList -> insertRow(row);
                ui -> raportList -> setItem(row, 0, new QTableWidgetItem(QString::number(cycleCount)));
                ui -> raportList -> setItem(row, 1, new QTableWidgetItem(QString::number(currentWarehouseID+1)));

                Warehouse warehouse = warehouses[currentWarehouseID];
                ui -> raportList -> setItem(row, 2, new QTableWidgetItem(warehouse.name));

                int currentCapacity = 0;
                for (const Product& product : warehouse.products)
                {
                    currentCapacity += product.quantity;
                }
                ui -> raportList -> setItem(row, 3, new QTableWidgetItem(QString::number(currentCapacity)));
                ui -> raportList -> setItem(row, 4, new QTableWidgetItem(QString::number(warehouse.capacity)));
                ui -> raportList -> setItem(row, 5, new QTableWidgetItem(fields[1]));
                ui -> raportList -> setItem(row, 6, new QTableWidgetItem(fields[2]));
            }
        }
        fileSimulation.close();
    }
}

