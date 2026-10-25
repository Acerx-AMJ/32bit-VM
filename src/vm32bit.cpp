#include "executor.hpp"
#include "parser.hpp"
#include "translator.hpp"

int main()
{
   while (true)
   {
      // Get file from the user
      std::cout << "> ";
      std::string full, command, input, output;
      std::getline(std::cin, full);

      std::istringstream iss(full);
      iss >> command >> input >> output;

      if (command == "help"s || command == "info"s)
      {
         std::cout << "Run a file: 'run file.asx'\n";
         std::cout << "Quit the program: 'quit' or 'exit'\n";
         continue;
      }

      if (command == "quit"s || command == "exit"s)
      {
         std::cout << "Quitting...\n"s;
         break;
      }

      Catcher catcher;

      // Interpretation
      if (command == "run"s && output.empty())
      {
         if (!fs::is_regular_file(input))
         {
            catcher.insert("File '"s + input + "' could not be opened or found."s);
            catcher.display();
            continue;
         }

         catcher.specify(input);
         translated_files.clear();

         // Tokenize the file contents
         Lexer lexer (catcher, input);
         auto& tokens = lexer.tokenize();

         if (catcher.display()) continue;

         // Replace labels with memory addresses and handle includes
         Translator translator (catcher, tokens);
         translator.translate();

         if (catcher.display()) continue;
         catcher.specify(""s);

         // Parse tokens into instructions and place them in memory
         Parser parser (catcher, tokens);
         parser.parse();

         if (catcher.display()) continue;

         // Execute instructions one by one
         Executor executor;
         executor.execute();

         // Temporarily print out 5 registers before traps are added
         std::cout << reg.at(R_R0) << std::endl;
         std::cout << reg.at(R_R1) << std::endl;
         std::cout << reg.at(R_R2) << std::endl;
         std::cout << reg.at(R_R3) << std::endl;
         std::cout << reg.at(R_R4) << std::endl;
      }
      // Invalid statement
      else
      {
         catcher.insert("Unknown command: '"s + full + "'. Type 'help' for help."s);
         catcher.display();
         continue;
      }
   }
   return 0;
}