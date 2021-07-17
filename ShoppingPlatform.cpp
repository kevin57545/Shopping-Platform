#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <fstream>

using namespace std;

class Commodity;
class Store;
class InputHandler;


class InputHandler {
public:
    /*
     * The function is used to read a full line into a string variable.
     * It read the redundant '\n' character to prevent the problem of getline function.
     * There is an overload version which can read from the specified data stream.
     * INPUT: None, or fstream
     * RETURN: Full line input by user
     * */
    static string readWholeLine() {
        string input;
        cin.get();
        getline(cin, input);
        return input;
    }

    static string readWholeLine(fstream& file) {
        string input;
        file.get();
        getline(file, input);
        return input;
    }

    /*
     * This function is used to configure whether the input string is a number
     * INPUT: A string
     * RETURN: Bool. True if input string is a number, otherwise false.
     */
    static bool isNum(string& str) {
        for (int i = 0; i < str.size(); i++) {
            if (!isdigit(str[i])) {
                return false;
            }
        }
        return true;
    }

    /*
     * Check the input string is a valid number.
     * First check the input is a number or not, then identify whether it is bigger than 0
     * INPUT: string
     * RETURN: bool
     */
    static bool isValidNum(string& str) {
        if (!isNum(str) || (isNum(str) && stoi(str) <= 0))
            return false;
        return true;
    }

    /*
     * Get a number from the user. This function will check the input validation.
     * INPUT: none
     * OUTPUT: integer, the input number
     */
    static int numberInput() {
        string input;
        cin >> input;
        while (!isValidNum(input)) {
            cout << "Please input again your input is NOT an integer or is lower than or equal to 0:" << endl;
            cin >> input;
        }
        return stoi(input);
    }

    /*
     * This function is used in function getInput. Check the input range is inside the specified range
     */
    static int inputCheck(string input, int maxChoiceLen, bool noZero) {
        // Change input to the general integer
        int choice = 0;
        for (int i = 0; i < input.size(); i++) {
            if (isdigit(input[i])) {
                choice = choice * 10 + (input[i] - '0');
            }
            else {
                return -1;
            }
        }

        if (noZero) {
            return (choice <= maxChoiceLen && choice > 0) ? choice : -1;
        }
        else {
            return (choice <= maxChoiceLen && choice >= 0) ? choice : -1;
        }
    }

    /*
     * Get the input from the user, and limit the input between the range [0, maxChoiceLen].
     * If noZero is signaled. Then the range will be [1, maxChoiceLen]
     * INPUT: integer, bool(option)
     * OUTPUT: integer, the choice number
     */
    static int getInput(int maxChoiceLen, bool noZero = false) {
        string input;

        cin >> input;
        int choice = inputCheck(input, maxChoiceLen, noZero);
        while (choice == -1) {
            cout << "your input is wrong, please input again:" << endl;
            cin >> input;
            choice = inputCheck(input, maxChoiceLen, noZero);
        }

        return choice;
    }
};

/*
 * Commodity is about an item which the user can buy and the manager can add or delete.
 * ATTRIBUTE:
 *  price: The price of the commodity, an integer.
 *  description: The text which describe the commodity detail, a string.
 *  commodityName: The name of the commodity, a string.
 */
class Commodity {
protected:
    int price;
    string description;
    string commodityName;
    int number = 0;
    int classifi;
    Commodity* ptr;
public:
    ~Commodity() = default;
    Commodity() {
        price = 0;
        description = "";
        commodityName = "";
    }

    Commodity(int price, string commodityName, string description) {
        this->price = price;
        this->commodityName = commodityName;
        this->description = description;
    }

    /*
     * This method will show the full information of the commodity to user interface.
     * There is a overloading version, with an argument amount which will output the information with the amount
     * INPUT: None, or an integer specify the amount of this commodity
     * RETURN: None
     */
    virtual void detail() {
        cout << commodityName << endl;
        cout << "price: " << price << endl;
        cout << "description: " << description << endl;
        cout << "----------------------------" << endl;
    }

    virtual void detail(int amount) {
        cout << commodityName << endl;
        cout << "price: " << price << endl;
        cout << "description: " << description << endl;
        cout << "x " << amount << endl;
        cout << "----------------------------" << endl;
    }

    /*
     * Use this function to get the information data from the user, this will init the object.
     * INPUT: none
     * OUTPUT: none
     */
    virtual void userSpecifiedCommodity() {
        cout << "Please input the commodity name:" << endl;
        commodityName = InputHandler::readWholeLine();
        cout << "Please input the commodity price:" << endl;
        price = InputHandler::numberInput();
        cout << "Please input the detail of the commodity:" << endl;
        description = InputHandler::readWholeLine();
    }

    /*
     * Save and load function is used to write the data to the file or read the data from the file.
     * According to the input parameter fstream, they complete the I/O on the specified file.
     * There have no definition of those method, because it is used to be override in the derived class.
     * INPUT: fstream
     * OUTPUT: none
     */
    virtual void save(fstream& file) {}

    virtual void load(fstream& file) {}

    /*
     * The getter function of commodityName
     */
    string getName() {
        return commodityName;
    }

    /*
     * The getter function of price
     */
    int getPrice() {
        return price;
    }
    void addNum() {
        number++;
    }
    void resetNum() {
        number = 0;
    }
    void writeptr(Commodity* a)
    {
        ptr = a;
    }
    int getNum() {
        return number;
    }
    Commodity* readptr()
    {
        return ptr;
    }
    int classification() {
        return classifi;
    }
};



class ComputerMonitor : public Commodity {
protected:
    string ratio;
    int size;
    string res;
    int rate;
    ComputerMonitor* ptr;
public:
    ~ComputerMonitor() = default;
    ComputerMonitor() {
        price = 0;
        description = "";
        commodityName = "";
        ratio = "";
        size = 0;
        res = "";
        rate = 0;
    }

    virtual void detail() {
        cout << commodityName << endl;
        cout << "price: " << price << endl;
        cout << "aspect ratio: " << ratio << endl;
        cout << "panel size: " << size << " inch" << endl;
        cout << "panel resolution: " << res << endl;
        cout << "refresh rate: " << rate << "Hz" << endl;
        cout << "description: " << description << endl;
        cout << "----------------------------" << endl;
    }

    virtual void detail(int amount) {
        cout << commodityName << endl;
        cout << "price: " << price << endl;
        cout << "aspect ratio: " << ratio << endl;
        cout << "panel size: " << size << " inch" << endl;
        cout << "panel resolution: " << res << endl;
        cout << "refresh rate: " << rate << "Hz" << endl;
        cout << "description: " << description << endl;
        cout << "x " << amount << endl;
        cout << "----------------------------" << endl;
    }

    virtual void userSpecifiedCommodity() {
        cout << "Please input the commodity name:" << endl;
        commodityName = InputHandler::readWholeLine();
        cout << "Please input the commodity price:" << endl;
        price = InputHandler::numberInput();
        cout << "What is the aspect ratio of this monitor?(e.g. 16:9,21:9...)" << endl;
        ratio = InputHandler::readWholeLine();
        cout << "What is the panel size of this monitor?(inch)" << endl;
        size = InputHandler::numberInput();
        cout << "What is the panel resolution of this monitor?(e.g. 1920*1080,4k...)" << endl;
        res = InputHandler::readWholeLine();
        cout << "What is the refresh rate of this monitor?(Hz)" << endl;
        rate = InputHandler::numberInput();
        cout << "Please input the detail of the commodity:" << endl;
        description = InputHandler::readWholeLine();
    }
    void save(fstream& file) {
        file << commodityName << endl << price << endl << ratio << endl << size
            << endl << res << endl << rate << endl << description << endl;
    }
    void load(fstream& file) {
        getline(file, commodityName);
        file >> price;
        ratio = InputHandler::readWholeLine(file);
        file >> size;
        res = InputHandler::readWholeLine(file);
        file >> rate;
        description = InputHandler::readWholeLine(file);
    }
    int classification() {
        classifi = 0;
        return classifi;
    }
};

class Mouse : public Commodity {
protected:
    int DPI;
    int button;
    string LED;
    int weight;
    int classifi = 1;
    Mouse* ptr;
public:
    ~Mouse() = default;
    Mouse() {
        price = 0;
        description = "";
        commodityName = "";
        DPI = 0;
        button = 0;
        LED = "";
        weight = 0;
    }

    virtual void detail() {
        cout << commodityName << endl;
        cout << "price: " << price << endl;
        cout << "Max DPI: " << DPI << endl;
        cout << "The number of buttons: " << button << endl;
        cout << "LED Light: " << LED << endl;
        cout << "weight: " << weight << "g" << endl;
        cout << "description: " << description << endl;
        cout << "----------------------------" << endl;
    }

    virtual void detail(int amount) {
        cout << commodityName << endl;
        cout << "price: " << price << endl;
        cout << "Max DPI: " << DPI << endl;
        cout << "The number of buttons: " << button << endl;
        cout << "LED Light: " << LED << endl;
        cout << "weight: " << weight << "g" << endl;
        cout << "description: " << description << endl;
        cout << "x " << amount << endl;
        cout << "----------------------------" << endl;
    }

    virtual void userSpecifiedCommodity() {
        cout << "Please input the commodity name:" << endl;
        commodityName = InputHandler::readWholeLine();
        cout << "Please input the commodity price:" << endl;
        price = InputHandler::numberInput();
        cout << "What is the Max DPI of this mouse?" << endl;
        DPI = InputHandler::numberInput();
        cout << "How many buttons are there on this mouse?" << endl;
        button = InputHandler::numberInput();
        cout << "What is the LED Light of this monitor?(e.g. RGB,none...)" << endl;
        LED = InputHandler::readWholeLine();
        cout << "How much does this mouse weigh?(g)" << endl;
        weight = InputHandler::numberInput();
        cout << "Please input the detail of the commodity:" << endl;
        description = InputHandler::readWholeLine();
    }
    void save(fstream& file) {
        file << commodityName << endl << price << endl << DPI << endl << button << endl
            << LED << endl << weight << endl << description << endl;
    }
    void load(fstream& file) {
        getline(file, commodityName);
        file >> price >> DPI >> button;
        LED = InputHandler::readWholeLine(file);
        file >> weight;
        description = InputHandler::readWholeLine(file);
    }
    int classification() {
        classifi = 1;
        return classifi;
    }
};

class USB : public Commodity {
protected:
    string type;
    int capacity;
    int read;
    int write;
    int classifi = 2;
    USB* ptr;
public:
    ~USB() = default;
    USB() {
        price = 0;
        description = "";
        commodityName = "";
        type = "";
        capacity = 0;
        read = 0;
        write = 0;
    }

    virtual void detail() {
        cout << commodityName << endl;
        cout << "price: " << price << endl;
        cout << "USB type: " << type << endl;
        cout << "capacity: " << capacity << " GB" << endl;
        cout << "Max Read Speed: " << read << " MB/s" << endl;
        cout << "Max Write Speed: " << read << " MB/s" << endl;
        cout << "description: " << description << endl;
        cout << "----------------------------" << endl;
    }

    virtual void detail(int amount) {
        cout << commodityName << endl;
        cout << "price: " << price << endl;
        cout << "USB type: " << type << endl;
        cout << "capacity: " << capacity << " GB" << endl;
        cout << "Max Read Speed: " << read << " MB/s" << endl;
        cout << "Max Write Speed: " << read << " MB/s" << endl;
        cout << "description: " << description << endl;
        cout << "x " << amount << endl;
        cout << "----------------------------" << endl;
    }

    virtual void userSpecifiedCommodity() {
        cout << "Please input the commodity name:" << endl;
        commodityName = InputHandler::readWholeLine();
        cout << "Please input the commodity price:" << endl;
        price = InputHandler::numberInput();
        cout << "What is the USB Type of this USB?" << endl;
        type = InputHandler::readWholeLine();
        cout << "What is the storage capacity of this USB?(GB)" << endl;
        capacity = InputHandler::numberInput();
        cout << "What is the Max Read Speed of this USB?(MB/s)" << endl;
        read = InputHandler::numberInput();
        cout << "What is the Max Write Speed of this USB?(MB/s)" << endl;
        write = InputHandler::numberInput();
        cout << "Please input the detail of the commodity:" << endl;
        description = InputHandler::readWholeLine();
    }
    void save(fstream& file) {
        file << commodityName << endl << price << endl << type << endl << capacity << endl
            << read << endl << write << endl << description << endl;
    }
    void load(fstream& file) {
        getline(file, commodityName);
        file >> price;
        type = InputHandler::readWholeLine(file);
        file >> capacity >> read >> write;
        description = InputHandler::readWholeLine(file);
    }
    int classification() {
        classifi = 2;
        return classifi;
    }
};
/*
 * This is a list storing the existing commodity in the store.
 */
class CommodityList {
private:
    vector<Commodity*> commoditylist[3];
    vector<Commodity*>::iterator it;
    Commodity* temp;
public:

    CommodityList() {


    }

    /*
     * Print the full information of the commodities inside the list
     * INPUT: None
     * RETURN: None
     */
    void showCommoditiesDetail() {
        int Num = 0;
        cout << "Computer Monitor type:" << endl;
        for (int i = 0; i < commoditylist[0].size(); i++) {
            cout << ++Num << ". ";
            commoditylist[0].at(i)->detail();
        }
        cout << "Mouse type:" << endl;
        for (int i = 0; i < commoditylist[1].size(); i++) {
            cout << ++Num << ". ";
            commoditylist[1].at(i)->detail();
        }
        cout << "USB type:" << endl;
        for (int i = 0; i < commoditylist[2].size(); i++) {
            cout << ++Num << ". ";
            commoditylist[2].at(i)->detail();
        }
    }

    /*
     * Print only the commodity name of the commodities inside the list
     * INPUT: None
     * RETURN: None
     */
    void showCommoditiesName() {
        int Num = 0;
        cout << "Computer Monitor type:" << endl;
        for (int i = 0; i < commoditylist[0].size(); i++) {
            cout << ++Num << ". " << commoditylist[0].at(i)->getName() << endl;
        }
        cout << "Mouse type:" << endl;
        for (int i = 0; i < commoditylist[1].size(); i++) {
            cout << ++Num << ". " << commoditylist[1].at(i)->getName() << endl;
        }
        cout << "USB type:" << endl;
        for (int i = 0; i < commoditylist[2].size(); i++) {
            cout << ++Num << ". " << commoditylist[2].at(i)->getName() << endl;
        }
    }

    /*
     * Check whether the list is empty or not
     * INPUT: None
     * RETURN: Bool. True if the list is empty, otherwise false
     */
    bool empty() {
        if (commoditylist[0].empty() == true && commoditylist[1].empty() == true && commoditylist[2].empty() == true)
            return true;
        else return false;

    }

    /*
     * Return the size(or length) of the list
     * INPUT: None
     * RETURN: Integer. List size
     */
    int size() {
        int size = 0;
        for (int i = 0; i < 3; i++)
        {
            size = size + commoditylist[i].size();
        }
        return size;
    }

    /*
     * Return a commodity object at specified position
     * INPUT: Integer. The index of that commodity
     * RETURN: Commodity. The wanted commodity object
     */
    Commodity* get(int index) {
        int find = 0;
        Commodity* ptr;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < commoditylist[i].size(); j++)
            {
                if (find == index) {
                    ptr = commoditylist[i][j];
                    return ptr;
                }
                else find++;
            }
        }
    }

    /*
     * Push a new commodity object into the list
     * INPUT: Commodity. The object need to be pushed
     * RETURN: None
     */
    void add(Commodity* newCommodity, string& cat) {
        if (cat == "ComputerMonitor")
            commoditylist[0].push_back(newCommodity);
        else if (cat == "Mouse")
            commoditylist[1].push_back(newCommodity);
        else
            commoditylist[2].push_back(newCommodity);

    }



    /*
     * Check the input commodity object is existing inside the list
     * INPUT: Commodity. The object need to be checked
     * OUTPUT: Bool. True if the object existing, otherwise false
     */
    bool isExist(Commodity* commodity) {
        int i;
        for (int i = 0; i < 3; i++) {
            it = commoditylist[i].begin();
            for (int j = 0; j < commoditylist[i].size(); j++)
            {
                if (commodity->getName() == (*(it + j))->getName())
                    return true;
            }
        }
        return false;
    }

    /*
     * Remove an object specified by the position
     * INPUT: Integer. The position of the object which need to be removed
     * OUTPUT: None
     */
    void remove(int index) {
        int find = 0;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < commoditylist[i].size(); j++)
            {
                if (find == index) {
                    it = commoditylist[i].begin();
                    commoditylist[i].erase(it + j);
                    return;
                }
                else find++;
            }
        }
    }

    void save() {
        fstream savefile;
        for (int i = 0; i < 3; i++) {
            if (i == 0) {
                savefile.open("ComputerMonitor.txt", ios_base::out);
            }
            else if (i == 1) {
                savefile.open("Mouse.txt", ios_base::out);
            }
            else if (i == 2) {
                savefile.open("USB.txt", ios_base::out);
            }
            for (int j = 0; j < commoditylist[i].size(); j++) {
                commoditylist[i][j]->save(savefile);
            }
            savefile.close();
        }
    }

    void load() {
        fstream loadfile;
        int i;
        string a;
        for (i = 0; i < 3; i++) {
            if (i == 0) {
                a = "ComputerMonitor";
                loadfile.open("ComputerMonitor.txt", ios_base::in);
                if(!loadfile) continue;
            }
            else if (i == 1) {
                a = "Mouse";
                loadfile.open("Mouse.txt", ios_base::in);
                if(!loadfile) continue;
            }
            else if (i == 2) {
                a = "USB";
                loadfile.open("USB.txt", ios_base::in);
                if(!loadfile) continue;
            }
            while (loadfile.eof() != true) {
                if (i == 0) {
                    temp = new ComputerMonitor;
                }
                else if (i == 1) {
                    temp = new Mouse;
                }
                else if (i == 2) {
                    temp = new USB;
                }
                temp->load(loadfile);
                if (!loadfile.fail()) {
                    add(temp, a);
                }

            }
            loadfile.close();
        }
    }
};

/*
 * The shopping cart is used to store the commodities user wanted.
 */
class ShoppingCart {
private:
    vector<Commodity*> shoppingcart;
    vector<Commodity*>::iterator it;
public:

    /*
     * Push an commodity object into the cart.
     * INPUT: Commodity. The object need to be pushed.
     * OUTPUT: None.
     */
    void push(Commodity* entry) {
        int i;
        for (i = 0; i < shoppingcart.size(); i++)
        {
            if (shoppingcart[i]->getName() == entry->getName()) {
                shoppingcart[i]->addNum();
                return;
            }
        }
        shoppingcart.push_back(entry);
        entry->resetNum();
        shoppingcart[i]->addNum();
    }

    /*
     * Show the content of the cart to user interface.
     * INPUT: None.
     * OUTPUT: None.
     */
    void showCart() {
        int Num = 0;
        for (int i = 0; i < shoppingcart.size(); i++) {
            Num++;
            cout << Num << "." << endl;
            shoppingcart[i]->detail(shoppingcart[i]->getNum());
        }
    }

    /*
     * Return the cart size. (The same object must be seen as one entry)
     * INPUT: None.
     * OUTPUT: Integer. The cart size.
     */
    int size() {
        int size = 0;
        for (int i = 0; i < shoppingcart.size(); i++)
        {
            size++;
        }
        return size;
    }

    /*
     * Remove an entry from the cart including the amount of the commodity.
     * INPUT: The order of the entry.
     * OUTPUT: None.
     */
    void remove(int index) {
        it = shoppingcart.begin();
        shoppingcart.erase(it + index);
        return;
    }

    /*
     * Check the total amount of price for the user and clear the list after checkout.
     * INPUT: None.
     * OUTPUT: Integer. The total price.
     */
    int checkOut() {
        int total = 0;

        for (int i = 0; i < shoppingcart.size(); i++) {
            total = total + (shoppingcart[i]->getPrice() * shoppingcart[i]->getNum());
        }
        shoppingcart.clear();
        return total;
    }

    /*
     * Check if the cart have nothing inside.
     * INPUT: None.
     * OUTPUT: Bool. True if the cart is empty, otherwise false.
     */
    bool empty() {
        if (shoppingcart.empty() == true)
            return true;
        else return false;
    }
};

/*
 * The Store class manage the flow of control, and the interface showing to the user.
 * Store use status to choose the interface to show.
 */
class Store {
private:
    enum UMode { USER, MANAGER } userStatus;
    enum SMode { OPENING, DECIDING, SHOPPING, CART_CHECKING, CHECK_OUT, MANAGING, CLOSE } storeStatus;
    CommodityList commodityList;
    ShoppingCart cart;

    void commodityInput() {
        Commodity* ptr;
        cout << "Which type of commodity you want to add?" << endl;
        cout << "1. Computer Monitor, 2. Mouse, 3. USB" << endl;
        int choice = InputHandler::getInput(3);
        string a;
        if (choice == 1) {
            ptr = new ComputerMonitor();
            a = "ComputerMonitor";
            ptr->userSpecifiedCommodity();
            if (commodityList.isExist(ptr)) {
                cout << "[WARNING] " << ptr->getName() << " is exist in the store. If you want to edit it, please delete it first" << endl;
            }
            else {
                commodityList.add(ptr, a);
            }
        }

        else if (choice == 2) {
            Mouse* ptr = new Mouse;
            ptr->userSpecifiedCommodity();
            a = "Mouse";
            if (commodityList.isExist(ptr)) {
                cout << "[WARNING] " << ptr->getName() << " is exist in the store. If you want to edit it, please delete it first" << endl;
            }
            else {
                commodityList.add(ptr, a);
            }
        }
        else {
            USB* ptr = new USB;
            ptr->userSpecifiedCommodity();
            a = "USB";
            if (commodityList.isExist(ptr)) {
                cout << "[WARNING] " << ptr->getName() << " is exist in the store. If you want to edit it, please delete it first" << endl;
            }
            else {
                commodityList.add(ptr, a);
            }
        }
    }

    void deleteCommodity() {
        if (commodityList.empty()) {
            cout << "No commodity inside the store" << endl;
            return;
        }

        int choice;
        cout << "There are existing commodity in our store:" << endl;
        commodityList.showCommoditiesName();
        cout << "Or type 0 to regret" << endl
            << "Which one do you want to delete?" << endl;

        choice = InputHandler::getInput(commodityList.size());

        if (choice != 0) {
            commodityList.remove(choice - 1);
        }
    }

    void showCommodity() {
        if (commodityList.empty()) {
            cout << "No commodity inside the store" << endl;
            return;
        }

        cout << "Here are all commodity in our store:" << endl;
        commodityList.showCommoditiesDetail();
        cout << endl;
    }

    void askMode() {
        string input;

        cout << "Are you a general user or a manager?" << endl
            << "1. general user, 2. manager" << endl
            << "Or type 0 to close the store" << endl;

        int choice = InputHandler::getInput(2);

        userStatus = (choice == 2) ? UMode::MANAGER : UMode::USER;

        if (choice == 0) {
            storeStatus = SMode::CLOSE;
        }
        else if (userStatus == UMode::USER) {
            storeStatus = SMode::DECIDING;
        }
        else if (userStatus == UMode::MANAGER) {
            storeStatus = SMode::MANAGING;
        }
    }

    void decideService() {
        string input;

        cout << "Below are our service:" << endl
            << "1. Buy the commodity you want" << endl
            << "2. Check your shopping cart" << endl
            << "3. Check out" << endl
            << "Or type 0 to exit user mode" << endl
            << "You may choose what you need:" << endl;

        int choice = InputHandler::getInput(3);

        if (choice == 1) {
            storeStatus = SMode::SHOPPING;
        }
        else if (choice == 2) {
            storeStatus = SMode::CART_CHECKING;
        }
        else if (choice == 3) {
            storeStatus = SMode::CHECK_OUT;
        }
        else if (choice == 0) {
            storeStatus = SMode::OPENING;
        }
    }

    void chooseCommodity() {
        string input;
        showCommodity();
        cout << "Or input 0 to exit shopping" << endl;

        int choice = InputHandler::getInput(commodityList.size());

        // Push the commodity into shopping cart here
        if (choice == 0) {
            storeStatus = SMode::DECIDING;
        }
        else {
            cart.push(commodityList.get(choice - 1));
        }
    }

    void showCart() {
        if (cart.empty()) {
            cout << "Your shopping cart is empty" << endl;
            storeStatus = SMode::DECIDING;
            return;
        }

        int choice;
        do {
            cout << "Here is the current cart content:" << endl;
            cart.showCart();

            cout << "Do you want to delete the entry from the cart?" << endl
                << "1. yes, 2. no" << endl;

            choice = InputHandler::getInput(2, true);

            if (choice == 1) {
                cout << "Which one do you want to delete(type the commodity index)?" << endl
                    << "Or type 0 to regret" << endl;
                int index = InputHandler::getInput(cart.size());
                if (index == 0) {
                    break;
                }
                cart.remove(index - 1);
            }
        } while (choice == 1);

        cout << "Do you want to checkout?" << endl
            << "1. yes, 2. No, I want to buy more" << endl;
        choice = InputHandler::getInput(2, true);
        if (choice == 1) {
            storeStatus = SMode::CHECK_OUT;
        }
        else {
            storeStatus = SMode::DECIDING;
        }
    }

    void checkOut() {
        if (cart.empty()) {
            cout << "Your shopping cart is empty, nothing can checkout" << endl;
        }
        else {
            cout << "Here is the current cart content:" << endl;
            cart.showCart();
            cout << "Are you sure you want to buy all of them?" << endl
                << "1. Yes, sure, 2. No, I want to buy more" << endl;

            int choice = InputHandler::getInput(2, true);

            if (choice == 1) {
                int amount = cart.checkOut();
                cout << "Total Amount: " << amount << endl;
                cout << "Thank you for your coming!" << endl;
                cout << "------------------------------" << endl << endl;
            }
        }

        storeStatus = SMode::DECIDING;
    }

    void managerInterface() {
        cout << "Here are some manager services you can use:" << endl
            << "1. Add new commodity" << endl
            << "2. Delete commodity from the commodity list" << endl
            << "3. Show all existing commodity" << endl
            << "Or type 0 to exit manager mode" << endl
            << "Which action do you need?" << endl;

        int choice = InputHandler::getInput(3);

        if (choice == 1) {
            commodityInput();
        }
        else if (choice == 2) {
            deleteCommodity();
        }
        else if (choice == 3) {
            showCommodity();
        }
        else if (choice == 0) {
            storeStatus = SMode::OPENING;
        }
    }

    void userInterface() {
        if (storeStatus == SMode::OPENING) {
            askMode();
        }
        else if (storeStatus == SMode::DECIDING) {
            decideService();
        }
        else if (storeStatus == SMode::SHOPPING) {
            chooseCommodity();
        }
        else if (storeStatus == SMode::CART_CHECKING) {
            showCart();
        }
        else if (storeStatus == SMode::CHECK_OUT) {
            checkOut();
        }
        else if (storeStatus == SMode::MANAGING) {
            managerInterface();
        }
        else if (storeStatus == SMode::CLOSE) {
            return;
        }
    }

public:
    Store() {
        userStatus = UMode::USER;
        storeStatus = SMode::CLOSE;
    }

    void open() {
        commodityList.load();
        storeStatus = SMode::OPENING;
        while (storeStatus != SMode::CLOSE) {
            userInterface();
        }
        commodityList.save();
    }
};


int main() {
    Store csStore;
    csStore.open();
    return 0;
}
