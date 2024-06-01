#ifndef GUI_H
#define GUI_H

#include <QMainWindow>

/**
 * @typedef GUIEvent
 * @brief Alias for QEvent representing GUI events.
 *
 * GUIEvent is an alias for QEvent and is used to handle all user interactions
 * with the graphical user interface, such as mouse clicks, key presses, and more.
 */
using GUIEvent = QEvent;

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
 * @enum GUIState
 * @brief Enumeration representing the possible states of the GUI.
 *
 * GUIState defines the various states that the GUI can be in, which can affect
 * how user interactions are handled and how GUI elements are displayed.
 */
enum GUIState {
    IDLE,    ///< The GUI is in an idle state, waiting for user interaction.
    ACTIVE,  ///< The GUI is actively engaged in processing an event.
    DISABLED ///< The GUI is disabled and not responding to user interactions.
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

    /**
     * @brief Updates the GUI based on the given event.
     *
     * This function handles GUI updates triggered by specific events. It takes a
     * GUIEvent as a parameter and modifies the GUI state or individual elements
     * accordingly. For example, it may update the text of a label or enable/disable
     * a button based on the event.
     *
     * @param event The GUI event that triggers the update.
     */
    void updateGUI(GUIEvent& event);

    /**
     * @brief Handles user-generated events.
     *
     * This function processes user interactions (e.g., mouse clicks, keyboard input)
     * and responds appropriately. It takes a GUIEvent as a parameter and performs
     * actions based on the event type. For instance, it may execute a specific action
     * when a button is clicked or update the GUI state when a key is pressed.
     *
     * @param event The GUI event to handle.
     */
    void handleEvents(GUIEvent& event);

private slots:
    void on_addbutton_clicked();
    void on_back_to_menu_clicked();
    void on_back_to_menu_2_clicked();
    void on_back_to_menu_3_clicked();
    void on_settings_button_clicked();
    void on_start_simulation_button_clicked();

private:
    Ui::GUI *ui; ///<   Pointer to the user interface setup.

    /**
     * @brief List of GUI elements currently managed by the GUI.
     *
     * This list contains all the GUI elements that are part of the user interface,
     * such as buttons, labels, sliders, etc. It is used to manage and render the
     * elements on the screen.
     */
    QList<GUIElement> interfaceElements;

    /**
     * @brief Current state of the GUI.
     *
     * This state represents the current condition of the GUI, which can be IDLE,
     * ACTIVE, or DISABLED. The GUI's behavior and response to user events may vary
     * depending on its state.
     */
    GUIState interfaceState;
};

#endif // GUI_H
