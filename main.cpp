#include <iostream>
#include <array>
#include "inventory.h"

int main()
{
    Inventory inv;
    inv.open();

    std::cout << "\nOptions:\n"
              << "store ItemName\n"
              << "remove ItemName\n"
              << "exit\n\n";

    while (true)
    {
        std::string item_str;
        std::getline(std::cin, item_str);

        if (item_str == "exit")
        {
            break;
        }
        else if (item_str.substr(0, 5) == "store")
        {
            if (item_str.size() > 6)
            {
                inv.store(item_str.substr(6));
            }
        }
        else if (item_str.substr(0, 6) == "remove")
        {
            if (item_str.size() > 7)
            {
                bool res = inv.remove(item_str.substr(7));
                if (!res)
                {
                    std::cout << "Item not found!\n";
                }
            }
        }
        else if (item_str.substr(0, 5) == "show")
        {
            inv.show();
        }
    }

    inv.close();
    return 0;
}
