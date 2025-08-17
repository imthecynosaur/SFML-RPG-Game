# C++/SFML RPG Game

This is a 2D RPG-style adventure game developed from scratch using C++ and the **SFML**. The project serves as a practical exploration of game development principles, including game loops, state management, entity systems, and tile-based maps.



## Features

The game currently includes the following features:

* **Player Character:** Control a character with basic animations for movement.
* **Tile-Based Map System:** The world is built on a grid-based tile map, allowing for simple and efficient level design.
* **Game State Management:** A simple state machine handles switching between different parts of the application, such as the main menu, the game itself, and the map editor.
* **Built-in Map Editor:** The project includes a map editor mode, allowing you to create and modify game levels directly within the application.

## Built With

* **C++:** The core language used for all game logic.
* **SFML 2.5.1:** A cross-platform, object-oriented multimedia C++ API used for handling graphics, windowing, and input.

## Getting Started

To compile and run this project on your local machine, you'll need to set up the development environment correctly.

### Prerequisites

* **Visual Studio:** The project is configured to be built with Visual Studio (2019 or later recommended). Make sure you have the **"Desktop development with C++"** workload installed.
* **Git:** For cloning the repository.
* **SFML:** You must download the SFML library separately. You can get it from the [official SFML website](https://www.sfml-dev.org/download.php).
    * Make sure to download the version that matches your Visual Studio compiler version (e.g., "Visual C++ 15 (2017)") and architecture (e.g., "64-bit").

### Build Instructions

1.  **Clone the repository:**
    ```bash
    git clone [https://github.com/imthecynosaur/SFML-RPG-Game.git](https://github.com/imthecynosaur/SFML-RPG-Game.git)
    ```

2.  **Set up SFML:**
    * Unzip the downloaded SFML library to a known location on your computer (e.g., `C:\libs\SFML-2.5.1`).

3.  **Configure the Visual Studio Project:**
    * Open the `SFML-RPG-Game.sln` file in Visual Studio.
    * Right-click on the `SFML-RPG-Game` project in the Solution Explorer and go to **Properties**.
    * At the top of the properties window, set **Configuration** to **`All Configurations`** and **Platform** to **`All Platforms`**.

    * **Configure Include Directories:**
        * Navigate to `Configuration Properties > C/C++ > General`.
        * In the **"Additional Include Directories"** field, add the path to SFML's `include` folder. (e.g., `C:\libs\SFML-2.5.1\include`).

    * **Configure Library Directories:**
        * Navigate to `Configuration Properties > Linker > General`.
        * In the **"Additional Library Directories"** field, add the path to SFML's `lib` folder. (e.g., `C:\libs\SFML-2.5.1\lib`).

    * **Configure Linker Dependencies:**
        * Navigate to `Configuration Properties > Linker > Input`.
        * In the **"Additional Dependencies"** field, you need to add the SFML library files.
            * For **Debug** configuration, you typically need: `sfml-graphics-d.lib;sfml-window-d.lib;sfml-system-d.lib;sfml-audio-d.lib;`
            * For **Release** configuration, you typically need: `sfml-graphics.lib;sfml-window.lib;sfml-system.lib;sfml-audio.lib;`
            * *(You can switch the "Configuration" at the top to `Debug` and `Release` to set these separately).*

4.  **Copy SFML DLLs:**
    * Go to the SFML `bin` folder (e.g., `C:\libs\SFML-2.5.1\bin`).
    * Copy all the `.dll` files from this folder.
    * Paste them into your project's build output directory (e.g., `SFML-RPG-Game/x64/Debug/`) where your final `.exe` file will be created. **The application will not run without these DLLs.**

5.  **Build the Solution:**
    * From the main menu, go to **Build > Build Solution** (or press `F7`). The project should now compile successfully.

## How to Play

After building the project, run the generated `.exe` file from the output directory.
* **Movement:** Use the **WASD** keys to move the player character.
* **Menu/Editor:** Follow the on-screen options to navigate the main menu or use the map editor.

## License

This project is licensed under the MIT License. See the `LICENSE` file for details.
