/**
 * @file gui.h
 * @brief Header file for the GUI class.
 *
 * Declares the GUI class and its members, which manage the user interface for the application.
 */

#ifndef GUI_H
#define GUI_H

#include <QMainWindow>
#include "Simulation/Simulation.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QInputDialog>
#include <QTimer>
#include <QThread>

/**
 * @typedef GUIElement
 * @brief Alias for QWidget representing GUI elements.
 *
 * GUIElement is an alias for QWidget and represents the basic unit of user interface
 * elements in Qt. It can be used to refer to any widget that is part of the GUI, such
 * as buttons, labels, text fields, etc.
 */
using GUIElement = QWidget;

/**
 * @class SimulationThread
 * @brief The SimulationThread class is responsible for running the simulation in a separate thread.
 *
 * This class inherits from QThread and overrides the run method to execute the simulation.
 * It emits a signal upon completion of the simulation to notify other components of its completion.
 */
class SimulationThread : public QThread
{
    Q_OBJECT
public:
    /**
     * @brief Executes the simulation in a separate thread.
     *
     * This function overrides the run method from QThread and is called when the thread starts.
     * It initializes a Simulation object and runs the simulation. Upon completion,
     * it emits the simulationFinished signal.
     */
    void run() override
    {
        Simulation simulation;
        simulation.run();
        emit simulationFinished();
    }
signals:
    /**
     * @brief Signal emitted when the simulation has finished running.
     */
    void simulationFinished();
};

namespace Ui {
class GUI;
}

/**
 * @class GUI
 * @brief The GUI class inherits from QMainWindow and represents the main window of the application.
 *
 * This class manages the user interface for the application. It sets up the main window
 * and its associated widgets, and handles user interactions.
 */
class GUI : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Constructor for the GUI class.
     *
     * @param parent Pointer to the parent widget, if any.
     */
    explicit GUI(GUIElement *parent = nullptr);

    /**
     * @brief Destructor for the GUI class.
     */
    ~GUI();

    /**
     * @brief Renders the graphical user interface elements.
     *
     * This function is responsible for rendering the GUI elements on the screen.
     * It ensures that all widgets (buttons, labels, etc.) are displayed correctly
     * based on their current state and properties.
     */
    void render();

private slots:
    /**
     * @brief Slot called when the 'Add' button is clicked.
     *
     * This slot is responsible for initiating the process of adding a new warehouse.
     * It prompts the user for warehouse details and updates the internal list of warehouses.
     */
    void on_addbutton_clicked();

    /**
     * @brief Slot called when the 'Back to Menu' button is clicked.
     *
     * This slot returns the user to the main menu of the application by changing the current view.
     */
    void on_back_to_menu_clicked();

    /**
     * @brief Slot called when the 'Back to Menu' button is clicked on the second page.
     *
     * This slot performs the same action as on_back_to_menu_clicked, but it is connected to the button
     * on the second page of the stacked widget.
     */
    void on_back_to_menu_2_clicked();

    /**
     * @brief Slot called when the 'Back to Menu' button is clicked on the third page.
     *
     * This slot performs the same action as on_back_to_menu_clicked, but it is connected to the button
     * on the third page of the stacked widget.
     */
    void on_back_to_menu_3_clicked();

    /**
     * @brief Slot called when the 'Settings' button is clicked.
     *
     * This slot navigates the user to the settings page of the application.
     */
    void on_settings_button_clicked();

    /**
     * @brief Slot called when the 'Start Simulation' button is clicked.
     *
     * This slot initiates the simulation process by switching to the simulation view
     * and starting the simulation thread.
     */
    void on_start_simulation_button_clicked();

    /**
     * @brief Slot called when the 'About' button is clicked.
     *
     * This slot displays information about the Qt framework used in the application.
     */
    void on_aboutButton_clicked();

    /**
     * @brief Slot called when the 'Choose Config File' button is clicked.
     *
     * This slot allows the user to select a configuration file for the simulation settings.
     * It updates the file path in the GUI and loads the selected configuration.
     */
    void on_configFileButton_clicked();

    /**
     * @brief Slot called when the 'Back to Menu' button is clicked on the settings page.
     *
     * This slot saves the current settings entered by the user and returns to the main menu.
     */
    void on_back_to_menu_7_clicked();

    /**
     * @brief Slot called when the 'Start' button is clicked on the simulation page.
     *
     * This slot begins the simulation with the current settings and warehouse data.
     * It also sets up the update timer and prepares the GUI for simulation output.
     */
    void on_start_button_clicked();

    /**
     * @brief Slot called when the 'Add Product' button is clicked.
     *
     * This slot is responsible for adding a new product to the current warehouse.
     * It prompts the user for product details and updates the warehouse data accordingly.
     */
    void on_addProductButton_clicked();

    /**
     * @brief Slot called when the 'Remove' button is clicked for a product.
     *
     * This slot removes the selected product from the current warehouse and updates the GUI.
     */
    void on_removeButton_clicked();

    /**
     * @brief Slot called when the 'Previous Warehouse' button is clicked.
     *
     * This slot switches the view to the previous warehouse in the list and updates the GUI.
     */
    void on_previousWarehouse_clicked();

    /**
     * @brief Slot called when the 'Next Warehouse' button is clicked.
     *
     * This slot switches the view to the next warehouse in the list, adding a new warehouse if necessary,
     * and updates the GUI.
     */
    void on_nextWarehouse_clicked();

    /**
     * @brief Slot called when the 'Remove Warehouse' button is clicked.
     *
     * This slot removes the current warehouse from the list and updates the GUI.
     */
    void on_removeWarehouseButton_clicked();

private:
    Ui::GUI *ui; ///<   Pointer to the user interface setup.

    /**
     * @struct Product
     * @brief Represents a product with a name, price, and quantity.
     *
     * This structure is used to store information about a product, including its name,
     * price per unit, and the quantity available in the warehouse.
     */
    struct Product
    {
        QString name;     ///< Name of the product.
        double price;     ///< Price per unit of the product.
        int quantity;     ///< Quantity of the product available.
    };

    /**
     * @struct Warehouse
     * @brief Represents a warehouse with an ID, capacity, name, and a list of products.
     *
     * This structure is used to store information about a warehouse, including its unique ID,
     * total capacity, name, and a list of products that are stored in the warehouse.
     */
    struct Warehouse
    {
        int id;                   ///< Unique identifier for the warehouse.
        int capacity;             ///< Total capacity of the warehouse.
        QString name;             ///< Name or location of the warehouse.
        QList<Product> products;  ///< List of products stored in the warehouse.
    };

    QList<Warehouse> warehouses; ///< List of all warehouses in the system.
    int currentWarehouseIndex = 0; ///< Index of the currently selected warehouse.

    QString filename; ///< Path to the configuration file.
    int seed = 100;    ///< Seed value used for simulation randomness. Defoult: 100
    int cycles = 10; ///< Number of cycles the simulation will run. Default: 10

    QTimer *timer; ///< Timer used for periodic updates during the simulation.

    /**
     * @brief Loads data for the current warehouse into the GUI.
     *
     * This function updates the product table with the information from the current warehouse.
     * It is called whenever the warehouse data needs to be displayed or refreshed.
     */
    void loadCurrentWarehouseData();

    /**
     * @brief Sets up a timer for periodic GUI updates.
     *
     * This function initializes a QTimer object to trigger periodic updates of the GUI.
     * It is used to refresh the GUI at regular intervals, such as during a simulation.
     */
    void setupUpdateTimer();

    /**
     * @brief Updates the tables in the GUI with data from a CSV file.
     *
     * This function reads data from a CSV file and updates the statistics and report tables in the GUI.
     * It is typically called by the update timer to refresh the data displayed to the user.
     */
    void updateTablesFromCSV();

    /**
     * @brief Slot called when the simulation has finished.
     *
     * This slot is connected to the simulationFinished signal of the SimulationThread.
     * It stops the update timer and prompts the user to save the simulation report and settings.
     */
    void onSimulationFinished();
};

#endif // GUI_H
