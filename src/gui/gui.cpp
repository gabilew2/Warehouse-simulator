#include "gui.h"
#include "./ui_gui.h"

/**
 * @brief Constructor for the GUI class.
 *
 * @param parent Pointer to the parent widget, if any.
 */
GUI::GUI(GUIElement *parent)
    : QMainWindow(parent)
    , ui(new Ui::GUI)
{
    ui->setupUi(this);
    render();
}

/**
 * @brief Destructor for the GUI class.
 */
GUI::~GUI()
{
    delete ui;
}

/**
 * @brief Renders the graphical user interface elements.
 */
void GUI::render() 
{
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
}

/**
 * @brief Slot called when the 'Add' button is clicked.
 *
 * This slot is responsible for initiating the process of adding a new warehouse.
 * It prompts the user for warehouse details and updates the internal list of warehouses.
 */
void GUI::on_addbutton_clicked()
{
    if(warehouses[0].name == "")
    {
        warehouses[0].name = QInputDialog::getText(this, "Add warehouse", "Please enter warehouse location below: ");
        warehouses[0].capacity = QInputDialog::getInt(this, "Add warehouse", "Please enter warehouse capacity below: ");
    }
    ui->stackedWidget->setCurrentIndex(1);
}

/**
 * @brief Slot called when the 'Back to Menu' button is clicked.
 */
void GUI::on_back_to_menu_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

/**
 * @brief Slot called when the 'Back to Menu' button is clicked.
 */
void GUI::on_back_to_menu_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

/**
 * @brief Slot called when the 'Back to Menu' button is clicked.
 */
void GUI::on_back_to_menu_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

/**
 * @brief Slot called when the 'Settings' button is clicked.
 */
void GUI::on_settings_button_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

/**
 * @brief Slot called when the 'Start Simulation' button is clicked.
 */
void GUI::on_start_simulation_button_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

/**
 * @brief Slot called when the 'About' button is clicked.
 */
void GUI::on_aboutButton_clicked()
{
    QApplication::aboutQt();
}

/**
 * @brief Slot called when the 'Choose Config File' button is clicked.
 */
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
            QMessageBox::critical(this, "Load Data", "Cannot open file.");
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
                    QMessageBox::critical(this, "Load Data", "Incorrect product line format.");
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

/**
 * @brief Slot called when the 'Back to Menu' button is clicked.
 */
void GUI::on_back_to_menu_7_clicked()
{
    seed = ui -> seedEdit -> text().toInt();
    cycles = ui -> cyclesEdit -> text().toInt();
    ui->stackedWidget->setCurrentIndex(0);
}

/**
 * @brief Slot called when the 'Start' button is clicked on the simulation page.
 */
void GUI::on_start_button_clicked()
{
    ui -> statisticList -> setRowCount(0);

    if(warehouses.isEmpty() || seed == 0 || cycles == 0 || warehouses[0].products.isEmpty())
    {
        QMessageBox::warning(this, "Start Simulation", "Cannot start simulation without initial conditions.");
        return;
    }

    QFile file("settings.csv");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Save Data", "Cannot open file.");
        return;
    }

    QTextStream out(&file);
    out << "Type,Location,Capacity,Name,Price,Quantity,Cycles,Seed\n";

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
    connect(simulationThread, &SimulationThread::simulationFinished, this, &GUI::onSimulationFinished);
    simulationThread->start();

    setupUpdateTimer();
    updateTablesFromCSV();
}

/**
 * @brief Slot called when the 'Add Product' button is clicked.
 */
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

/**
 * @brief Loads data for the current warehouse into the GUI.
 */
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

/**
 * @brief Slot called when the 'Previous Warehouse' button is clicked.
 */
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

/**
 * @brief Slot called when the 'Next Warehouse' button is clicked.
 */
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

/**
 * @brief Slot called when the 'Remove Warehouse' button is clicked.
 */
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

/**
 * @brief Sets up a timer for periodic GUI updates.
 */
void GUI::setupUpdateTimer()
{
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &GUI::updateTablesFromCSV);
    timer->start(1000);
}

/**
 * @brief Updates the tables in the GUI with data from a CSV file.
 */
void GUI::updateTablesFromCSV()
{
    ui -> raportList -> setRowCount(0);
    int cycles = -1;
    QFile report("SimulationReport.csv");

    if(!report.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::critical(this, "Read Report", "Cannot open report file to read.");
        return;
    }

    int currentWarehouse;
    int statisticRow = 0;

    QTextStream in(&report);

    while(!in.atEnd())
    {
        QString line = in.readLine();
        if(line.isEmpty())
        {
            statisticRow = 0;
            cycles++;
        }
        else if(line.contains("Warehouse ID,Capacity"))
        {
            line = in.readLine();

            QStringList fields = line.split(',');
            currentWarehouse = fields[0].toInt();
            int capacity = fields[1].toInt();
            QString location = warehouses[currentWarehouse].name;
            int sold = 0;

            line = in.readLine();
            if(!line.contains("Product Name,Price,Quantity"))
            {
                break;
            }
            line = in.readLine();
            while(!line.contains("Sales ID,Time"))
            {
                QString productName;
                double price;
                int quantity;

                fields = line.split(",");

                productName = fields[0];
                price = fields[1].toDouble();
                quantity = fields[2].toInt();

                ui -> statisticList -> item(statisticRow, 2) -> setText(productName);
                ui -> statisticList -> item(statisticRow, 3) -> setText(QString::number(price));
                ui -> statisticList -> item(statisticRow, 4) -> setText(QString::number(quantity));
                ui -> statisticList -> update();
                statisticRow++;
                line = in.readLine();
            }
            line = in.readLine();
            line = in.readLine();
            if(!line.contains("Product Name,Price,Quantity"))
            {
                break;
            }
            line = in.readLine();
            while(!line.contains("Operational Costs,Net Profit"))
            {
                fields = line.split(",");
                sold += fields[2].toInt();
                line = in.readLine();
            }

            line = in.readLine();
            fields = line.split(",");

            double costs = fields[0].toDouble();
            double netProfit = fields[1].toDouble();

            int row = ui -> raportList -> rowCount();
            ui -> raportList -> insertRow(row);
            ui -> raportList -> setItem(row, 0, new QTableWidgetItem(QString::number(cycles)));
            ui -> raportList -> setItem(row, 1, new QTableWidgetItem(QString::number(currentWarehouse)));
            ui -> raportList -> setItem(row, 2, new QTableWidgetItem(location));
            ui -> raportList -> setItem(row, 3, new QTableWidgetItem(QString::number(sold)));
            ui -> raportList -> setItem(row, 4, new QTableWidgetItem(QString::number(capacity)));
            ui -> raportList -> setItem(row, 5, new QTableWidgetItem(QString::number(costs)));
            ui -> raportList -> setItem(row, 6, new QTableWidgetItem(QString::number(netProfit)));
            ui -> raportList -> update();
        }
    }
    report.close();
}

/**
 * @brief Slot called when the simulation has finished.
 */
void GUI::onSimulationFinished()
{
    timer -> stop();

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Save Report", "Do you want to save the report in a location other than the default one?", QMessageBox::Yes|QMessageBox::No);

    QString filePath;
    if (reply == QMessageBox::Yes)
    {
        filePath = QFileDialog::getSaveFileName(this, "Save Report", "SimulationReport.csv", "*.csv");
        if (!filePath.isEmpty())
        {
            QFile::copy("SimulationReport.csv", filePath);
        }
    }

    reply = QMessageBox::question(this, "Save data", "Do you want to save data from the table 'Raport'?", QMessageBox::Yes|QMessageBox::No);

    if (reply == QMessageBox::Yes)
    {
        filePath = QFileDialog::getSaveFileName(this, "Save Report", "GUIReport.csv", "*.csv");

        QFile file(filePath);
        if(file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QTextStream stream(&file);
            stream << "Cycle,Warehouse ID,Location,Sold Products,Capacity,Operational Costs,Net Profit\n";
            for(int row = 0; row < ui->raportList->rowCount(); ++row)
            {
                QStringList rowData;
                for(int column = 0; column < ui->raportList->columnCount(); ++column)
                {
                    QTableWidgetItem *item = ui->raportList->item(row, column);
                    if(item)
                    {
                        rowData << item -> text();
                    }
                    else
                    {
                        rowData << "";
                    }
                }
                stream << rowData.join(",") << "\n";
            }
            file.close();
        }
        else
        {
            QMessageBox::critical(this, "Export to CSV", "Cannot open file for writing.");
        }
    }

    reply = QMessageBox::question(this, "Save Settings", "Do you want to save yours settings in a location other than the default one?", QMessageBox::Yes|QMessageBox::No);

    if (reply == QMessageBox::Yes)
    {
        filePath = QFileDialog::getSaveFileName(this, "Save Settings", "settings.csv", "*.csv");
        if (!filePath.isEmpty())
        {
            QFile::copy("settings.csv", filePath);
        }
    }
}
