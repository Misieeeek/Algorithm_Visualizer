#include "main_menu.h"
#include "main_window.h"
#include "options.h"

enum AppState { MAIN_MENU = -1, VISUALIZE, OPTIONS, EXIT };

int main() {
  MainWindow mainWindow;
  /* sf::RenderWindow window(sf::VideoMode(1280, 720), "Algorithm Visualizer",
   sf::Style::Close | sf::Style::Resize); MainMenu mainMenu; Options option;
   AppState appState = MAIN_MENU;

   while (window.isOpen())
   {
       sf::Event evnt;
       while (window.pollEvent(evnt))
       {
           switch (evnt.type)
           {
           case sf::Event::Closed:
               window.close();
               break;
           case sf::Event::KeyPressed:
               switch (evnt.key.code)
               {
               case sf::Keyboard::Up:
                   mainMenu.MoveUp();
                   break;
               case sf::Keyboard::Down:
                   mainMenu.MoveDown();
                   break;
               case sf::Keyboard::Enter:
                   int selected = mainMenu.pressed();
                  switch (selected)
                   {
                   case 0:
                       std::cout << "Visualize" << std::endl;
                       break;
                   case 1:
                       std::cout << "Options" << std::endl;
                       appState = OPTIONS;
                       break;
                   case 2:
                       std::cout << "About" << std::endl;
                       break;
                   case 3:
                       std::cout << "EXIT" << std::endl;
                       break;
                   }
                  break;
               }
               break;
           }
       }

       window.clear();
       switch (appState)
       {
       case MAIN_MENU:
           mainMenu.draw(window);
           break;
       case OPTIONS:
           option.draw(window);  // Rysowanie ekranu opcji
           break;
       }
       window.display();
   }*/
}
