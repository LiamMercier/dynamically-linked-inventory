#pragma once
#include <string>
#include <array>
#include <iostream>
#include <fstream>
#include <dlfcn.h>

std::string inv_first =
"#include <array>\n#include <string>\nextern \"C\" {\nint num_items = ";

std::string inv_second = ";\nstd::array<std::string, 40> items {\n";

std::string inv_third = "};\n}\n";

class Inventory
{
public:
    // To open the inventory, we find the inventory dll and open it!
    void open()
    {
        handle = dlopen("./inventory.so", RTLD_LAZY);

        if (!handle)
        {
            std::cerr << "Error: ./inventory.so does not exist, creating default!\n";

            // create empty .dll
            std::string program = inv_first
                                  + "0"
                                  + inv_second
                                  + inv_third;
            compile_dll(program);

            handle = dlopen("./inventory.so", RTLD_LAZY);

            if (!handle)
            {
                std::cerr << "Failed to make default, exiting!\n";
                std::exit(EXIT_FAILURE);
            }
        }

        items_ptr = static_cast<std::array<std::string, 40>*>(dlsym(handle, "items"));
        num_items_ptr = static_cast<int*>(dlsym(handle, "num_items"));

        if (!items_ptr || !num_items_ptr)
        {
            std::cerr << "Failed to get required symbols for inventory!\n";
            dlclose(handle);
            handle = nullptr;
            std::exit(EXIT_FAILURE);
        }

        std::cout << "Inventory opened!\n";
    }

    // When we close the inventory, we make sure to compile a new dll for the next
    // time we open it to save our items.
    void close()
    {
        std::string all_items;

        for(int i = 0; i < *num_items_ptr; i++)
        {
            all_items += "\""
                         + (*items_ptr)[i]
                         + "\", ";
        }

        std::cout << "Saving items: " << all_items << "\n";

        std::string program = inv_first
                              + std::to_string(*num_items_ptr)
                              + inv_second
                              + all_items
                              + inv_third;

        compile_dll(program);

        dlclose(handle);
        handle = nullptr;
    }

    // compile a dll for saving our inventory
    void compile_dll(std::string program_str)
    {
        std::ofstream out("inv_dll.cpp");
        out << program_str;
        out.close();

        int res = system("g++ -shared -fPIC inv_dll.cpp -o inventory.so");

        if (res != 0)
        {
            std::cerr << "Failed to compile new inventory DLL!\n";
        }
    }

    void store(std::string item)
    {
        if (*num_items_ptr == 40)
        {
            std::cout << "Too many items stored already!\n";
            return;
        }

        (*items_ptr)[*num_items_ptr] = item;
        *num_items_ptr = *num_items_ptr + 1;
    }

    bool remove(std::string item)
    {
        bool found = false;

        if (*num_items_ptr == 0)
        {
            return found;
        }

        // remove the item from the array
        for (int i = 0; i < *num_items_ptr; i++)
        {
            if ((*items_ptr)[i] == item)
            {
                found = true;

                for (int j = i; j < (*num_items_ptr - 1); j++)
                {
                    (*items_ptr)[j] = (*items_ptr)[j + 1];
                }

                // remove the end item since we shifted down.
                (*items_ptr)[*num_items_ptr - 1] = "";
                *num_items_ptr = *num_items_ptr - 1;

                break;
            }
        }

        return found;
    }

    void show()
    {
        for (int i = 0; i < *num_items_ptr; i++)
        {
            std::cout << (*items_ptr)[i] << " ";
        }

        std::cout << "\n";
    }

private:
    void* handle = nullptr;
    std::array<std::string, 40>* items_ptr;
    int* num_items_ptr = nullptr;
};
