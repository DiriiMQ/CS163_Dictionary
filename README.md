# CS163 Project: Dictionary

Author: 

- 22125083 - Phan Minh Quang
- 22125081 - Dương Minh Quang
- ? - Nguyễn Quốc Nghĩa
- ? - Ngô Trí Sĩ

Our project provide a customize dictionary using some algorithms and data structures to improve the user experience.

## How to run

### Requirements

(this application works only on Windows because of using `wchar_t` which has different size on different platforms)

- C++ 17 – GNU GCC 7.3.0+
    - Please follow [this instruction](https://www.msys2.org/#installation) to install.
    - **Note**: Please install the `MinGW 64-bit` version. At step 6, please run the following command instead:
      - `pacman -S mingw-w64-x86_64-gcc`
- [CMake 3.26+](https://cmake.org/download/)
- Makefile
  - Please open the `MSYS2 MinGW 64-bit` terminal and run the following command:
    - `pacman -S make`

### Build

- Clone this repository
- Run the following commands:
  - `cd Visualgo_CS162`
  - Build the project:
    - for Windows users:
      - `cmake -G"MSYS Makefiles" -S . -B build`
  - `make -C build`
- The executable file will be in the `build` folder

### Run

- Click on the executable file in the folder `build` to run the program.
- If you want to run the program in the terminal, run the following command:
  - `cd build && ./Visualgo_CS162`

## Project structure

- `assets` – contains the assets used in the program
- `build` – contains the executable file
- `include` – contains the header and source files of the program
  - `core` – contains the core classes of the program
  - `draw` - contains the classes that draw objects structures
  - `stuff` - contains other classes that are used in the program

## Features
- The program will show the main screen when it starts.
![Main screen](./assets/preview/main_screen.png)
1.	Users can switch between data sets

There is a button: 

- ![EN-VI](./assets/preview/SwitchButton1.png)

- ![VI-EN](./assets/preview/SwitchButton2.png)

- ![EN-EN](./assets/preview/SwitchButton3.png) 

- ![EN-EMOJI](./assets/preview/SwitchButton4.png)

It switches between these button when clicked.

2.	Users can search with a keyword.
 ![Search Word](./assets/preview/SearchWord.png)

- Choose Word mode, enter a word that you want to find in the search bar

3. Users can search with a definition

![Search Definition](./assets/preview/SearchDef.png)

- Choose Definition mode, enter definition that you want to find the corresponding word in the search bar

4. Users can view the history of search words again.
 
 ![History](./assets/preview/History.png)

- Click the search bar, when you haven’t entered the search bar, you can view the history.

5.	Users can add a new word and its definition
 
  ![Add](./assets/preview/AddWord.png)

- Choose mode Word 
- Choose Add mode
-	Enter the format in order to create new word

6.	Users can edit the definition of an existing word
 
 ![Edit](./assets/preview/Edit.png)
 - Search word that you want to edit, choose Edit button. Click any line you want to edit
 7.	Users can remove a word from the dictionary
 
 ![Remove](./assets/preview/Remove.png)
- Search word that you want to remove, choose Remove button. The word will be removed
8.	Users can reset the dictionary to its original state
 
 ![Reset](./assets/preview/Reset.png)
- There is a Reset button in the down-right corner of the frame. The dictionary will be reset after this button is clicked
9.	Users can view a random word and its definition

![Random word](./assets/preview/Random.png)

- Choose mode Word. Choose the random button (is on the right side of the search bar) 

10.	Users can view their favorite list

![Favourite List](./assets/preview/Favourite.png)
 

- Click Favourite button to see the favorite list

11. Users can remove/add a word from their favorite list

  - When searching for any word, there is a Star. 

    - When it is non favourite word
         ![Star UnFavourite](./assets/preview/Star.png)

    - When it is favourite word
         ![Star Favourite](./assets/preview/StarFavourite.png)

- You can add/remove to favourite list when click that Star

11.	The app can make random a word with four definitions, and users guess its meaning
 
 ![Quiz mode](./assets/preview/QuizMode.png)

- When entering the SearchMode button, it will change to the Quiz mode.
- Choose mode Word, then The app can make random a word with four definitions, and users guess its meaning

![Quiz word](./assets/preview/QuizWord.png)

12.	The app can provide a random definition with four keywords, and users choose the correct word

![Quiz definition](./assets/preview/QuizDef.png)
- Choose Definition in the Quiz mode, the app can provide a random definition with four keywords, and users choose the correct word

13.	Show suggestions bar when searching
 
![Suggestions bar](./assets/preview/SuggestionBar.png)

- Entering the search bar, the suggestions bar will show for you

14.	The app has emoji data set

![Emoji](./assets/preview/Emoji.png)









## Data structures and algorithms
<!-- Write the DSAs and Algorithms IN DETAILS and calculate the time and space complexity with the real time measurement -->

## License

This project is licensed under the `GPL-3.0 License` - see the [LICENSE](./LICENSE) file for details.