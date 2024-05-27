/**
 * @file main.cpp
 * @brief Main entry point for the Warehouse Simulator application.
 */

#include "gui/gui.h"
#include "Simulation/Simulation.h"
#include <iostream>
#include <QFile>
#include <QTextStream>

#include <QApplication>

/**
 * @brief Creates a configuration file for the simulation.
 *
 * This function prompts the user to configure the simulation settings
 * and writes them to a file named "settings.sim".
 */
void createConfigFile()
{
    QFile file("settings.sim");

    // Attempt to open the file for writing text.
    if(file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream out(&file);

        // Write the header to the config file.
        out << "Warehouse-simulator config file. Do not edit!\n";

        unsigned short option = 0;

        // Interactive menu to configure simulation settings.
        while(option != 9)
        {
            // Display options to the user.
            std::cout << "\n\n***************************" << std::endl
                      << "* 1. Add warehouse        *" << std::endl
                      << "* 2. Add product          *" << std::endl
                      << "* 3. Set number of cycles *" << std::endl
                      << "* 9. Run simulation       *" << std::endl
                      << "***************************" << std::endl;

            std::cout << "\n\nEnter option: "; std::cin >> option;

            // Handle user input based on selected option.
            switch(option)
            {
            case 1:
            {
                std::string location;
                double capacity;
                std::cout << "\n\nEnter warehouse location: "; std::cin >> location;
                std::cout << "Enter capacity of warehouse: "; std::cin >> capacity;

                // Write warehouse details to the config file.
                out << "Add warehouse;\n";
                out << QString::fromStdString(location) << "\n";
                out << capacity << "\n";
                break;
            }
            case 2:
            {
                std::string name;
                double price;
                int quantity;
                std::cout << "\n\nEnter product name: "; std::cin >> name;
                std::cout << "Enter product price: "; std::cin >> price;
                std::cout << "Enter quantity: "; std::cin >> quantity;

                // Write product details to the config file.
                out << "Add product;\n";
                out << QString::fromStdString(name) << "\n";
                out << price << "\n";
                out << quantity << "\n";
                break;
            }
            case 3:
            {
                int cycles;
                std::cout << "\n\nEnter number of cycles: "; std::cin >> cycles;

                // Write the number of cycles to the config file.
                out << "Set currentCycle;\n";
                out << cycles << "\n";
                break;
            }
            case 9:
            {
                // Exit the configuration menu.
                break;
            }
            default:
            {
                // Handle invalid input.
                std::cout << "\n\nWrong option. Please try again.";
            }
            }
        }

        // Close the file after writing.
        file.close();
    }
    else
    {
        // Error handling if the file cannot be opened.
        std::cerr << "Error: Can't open file to write.";
    }
}

/**
 * @brief Main function of the application.
 *
 * This function initializes the application, processes command-line arguments,
 * and starts the GUI or simulation based on the provided options.
 *
 * @param argc Number of command-line arguments.
 * @param argv Array of command-line arguments.
 * @return Exit code of the application.
 */
int main(int argc, char *argv[])
{
    bool _gui = true;
    bool _config = true;

    // Process command-line arguments.
    for(int arg = 1; arg < argc; ++arg)
    {
        if(strcmp(argv[arg], "--nogui") == 0)
        {
            _gui = false;
        }
        else if(strcmp(argv[arg], "--noconfig") == 0)
        {
            _config = false;
        }
    }

    QApplication a(argc, argv);
    GUI w;

    // Start the GUI if enabled.
    if(_gui)
    {
        w.show();
    }
    else
    {
        // Create a config file and run the simulation if enabled.
        if(_config)
        {
            createConfigFile();
        }

        Simulation simulation = Simulation();
        simulation.run();
        exit(0);
    }

    // Execute the application.
    return a.exec();
}
