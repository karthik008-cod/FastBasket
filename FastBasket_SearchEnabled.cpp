#include<iostream>
#include<string>
#include<vector>
#include<stack>
#include<iomanip>
#include<algorithm>
#include<windows.h>
using namespace std;

#define MAX 30
#define PIN 12061010
int i=0;

void Dashboard();
void AddIteamsToCart();
void YourOrders();
void ViewCart();
void TrackYourOrders();
void Display(int);
void DisplayCart();
void DeleteItems();
void Delete(stack<string>*, int);
void edit(stack<int>, int, int);
void login();
void UI();
void placeOrder(int);
void payment(int, string);
void crew();
void AddIteamsCrew();
void DeleteIteamsCrew();
void EditPricesCrew();
stack<int> TotalFareForHistory;
void SearchDashboard();
string normalize(const string& str);
void searchItems(stack<string> originalStack, const string& keyword);

stack<string> Cart;
stack<int> Price, Quantity;
stack<string> Category, Fruits, Vegetables, Snacks, Drinks;
stack<int> FruitsP, VegetablesP, DrinksP;
stack<string> Lays, Kurkure, Bingo, Biscuits;
stack<int> LaysP, KurkureP, BingoP, BiscuitsP;
stack<string> DeliveryAddress, PaymentType;

int main(){
    Category.push("Drinks");
    Category.push("Snacks");
    Category.push("Vegetables");
    Category.push("Fruits");

    Fruits.push("Orange");
    Fruits.push("Kiwi");
    Fruits.push("Dragon Fruit");
    Fruits.push("Apple");
    Fruits.push("Guava");
    Fruits.push("Papaya");
    Fruits.push("Coconut");
    Fruits.push("Grapes");
    Fruits.push("Pineapple");
    Fruits.push("Banana");
    Fruits.push("Watermelon");
    Fruits.push("Mango");

    FruitsP.push(20);
    FruitsP.push(20);
    FruitsP.push(90);
    FruitsP.push(30);
    FruitsP.push(25);
    FruitsP.push(45);
    FruitsP.push(30);
    FruitsP.push(40);
    FruitsP.push(60);
    FruitsP.push(5);
    FruitsP.push(50);
    FruitsP.push(125);

    Vegetables.push("Ridge Gourd");
    Vegetables.push("Ladies Finger");
    Vegetables.push("Raw Banana");
    Vegetables.push("Ash Gourd");
    Vegetables.push("Bottle Gourd");
    Vegetables.push("Bitter Gourd");
    Vegetables.push("Snake Gourd");
    Vegetables.push("Drumstick");
    Vegetables.push("Brinjal");
    Vegetables.push("Tomato");

    VegetablesP.push(18);
    VegetablesP.push(12);
    VegetablesP.push(10);
    VegetablesP.push(28);
    VegetablesP.push(25);
    VegetablesP.push(18);
    VegetablesP.push(20);
    VegetablesP.push(12);
    VegetablesP.push(8);
    VegetablesP.push(4);

    Snacks.push("Biscuits");
    Snacks.push("Bingo");
    Snacks.push("Kurkure");
    Snacks.push("Lay's");

    Lays.push("Chile Limon Flavour Potato Chips");
    Lays.push("Classic Salted Flavor Potato Chips");
    Lays.push("Spanish Tomato Tango Potato Chips");
    Lays.push("American Style Cream & Onion Potato Chips");
    Lays.push("India's Magic Masala Potato Chips");

    Kurkure.push("Puffcorn Yummy Cheese Puffs");
    Kurkure.push("Chilli Chatka Crisps");
    Kurkure.push("Masala Munch Crisps");
    
    Bingo.push("Original Style Chilli Sprinkled Potato Chips");
    Bingo.push("Mad Angles Cheese Nachos");
    Bingo.push("Mad Angles Achaari Masti Crisps");
    Bingo.push("Mad Angles Tomato Madness Crisps");    
    
    Biscuits.push("Mom's Magic(Cashew & Almond)");
    Biscuits.push("Parle Hide & Seek");
    Biscuits.push("Monaco");
    Biscuits.push("Parle-G");
    Biscuits.push("Britannia Marie Gold");
    Biscuits.push("Britannia Nice Time");
    Biscuits.push("Sunfeast Dark Fantacy");
    Biscuits.push("Sunfeast Bourbon");
    Biscuits.push("Cadbury Oreo");

    BiscuitsP.push(40);
    BiscuitsP.push(60);
    BiscuitsP.push(30);
    BiscuitsP.push(100);
    BiscuitsP.push(45);
    BiscuitsP.push(30);
    BiscuitsP.push(80);
    BiscuitsP.push(80);
    BiscuitsP.push(125);

    Drinks.push("Appy Fizz");
    Drinks.push("Pulpy Orange");
    Drinks.push("Maaza");
    Drinks.push("Coca-Cola");
    Drinks.push("Thumbs up");
    Drinks.push("Sprite");

    DrinksP.push(40);
    DrinksP.push(90);
    DrinksP.push(99);
    DrinksP.push(99);
    DrinksP.push(99);
    DrinksP.push(96);

    cout<<endl<<endl<<"\033[1mWelcome to FastBasket!\nBlink. Delivered.\033[0m"<<endl<<endl;
    UI();
    return 0;
}

template <typename T>
void displayStack(stack<T> s) {
    int i=1;
    while (!s.empty()) {
        cout<<i<<". "<<s.top()<<endl;
        s.pop();
        i++;
    }
}

void YourOrders() {
    if (TotalFareForHistory.empty()) {
        cout << "\n\033[1mYou haven't placed any orders yet.\033[0m\n";
        Dashboard();
        return;
    }

    stack<string> tempAddress = DeliveryAddress;
    stack<string> tempPayment = PaymentType;
    stack<int> tempFare = TotalFareForHistory;

    int orderNo = 1;
    cout << "\n\033[1mYour Order History:\033[0m\n";
    cout << left << setw(10) << "Order" << setw(20) << "Payment Method" << setw(30) << "Delivery Address" << "Total (Rs.)\n";
    cout << "----------------------------------------------------------------------------\n";

    vector<tuple<int, string, string>> orderData;

    while (!tempFare.empty()) {
        orderData.push_back({tempFare.top(), tempPayment.top(), tempAddress.top()});
        tempFare.pop();
        tempPayment.pop();
        tempAddress.pop();
    }

    reverse(orderData.begin(), orderData.end());

    for (int i = 0; i < orderData.size(); ++i) {
        float fare = get<0>(orderData[i]);
        string payment = get<1>(orderData[i]);
        string address = get<2>(orderData[i]);
        cout << left << setw(10) << orderNo++<< setw(20) << payment<< setw(30) << address<< fare << endl;
    }
    
    cout << "\n";
    Dashboard(); 
}

void TrackYourOrders() {
    if (DeliveryAddress.empty()) {
        cout << "\n\033[1mYou have no orders to track.\033[0m\n";
        Dashboard();
        return;
    }

    stack<string> tempAddress = DeliveryAddress;
    stack<string> tempPayment = PaymentType;
    stack<int> tempFare = TotalFareForHistory;
    vector<tuple<string, int, string>> orders;
    
    while (!tempAddress.empty()) {
        orders.push_back({tempAddress.top(), tempFare.top(), tempPayment.top()});
        tempAddress.pop();
        tempFare.pop();
        tempPayment.pop();
    }
    reverse(orders.begin(), orders.end());
    cout << "\n\033[1mOrder Tracking:\033[0m\n";
    int orderId = 1;
    for (int i = 0; i < orders.size(); ++i) {
        string address = get<0>(orders[i]);
        float fare = get<1>(orders[i]);
        string payment = get<2>(orders[i]);
        cout << "\nOrder #" << orderId++;
        cout << "\nDelivery Address  : " << address;
        cout << "\nTotal Fare        : Rs. " << fare;
        cout << "\nPayment Method    : " << payment;
        cout << "\nStatus            : ";
        switch (rand() % 4) {
            case 0: cout << "Order Recieved"; break;
            case 1: cout << "Packed and ready to go!"; break;
            case 2: cout << "Delivery patner is on the way..."; break;
            case 3: cout << "Delivered successfully. Enjoy your Order!"; break;
        }
        int eta = (rand() % 26) + 5;
        cout << "\nEstimated Delivery: " << eta << " minutes\n";
    }

    cout << "\n";
    Dashboard();
}

void crew(){
    cout<<endl<<"\033[1;33mInventory Control Center (Crew Access)\033[0m"<<endl
    <<"1. Add Iteams"<<endl
    <<"2. Delete Iteams"<<endl
    <<"3. Edit Prices"<<endl
    <<endl<<"Select the action you want to perform:";
    int action;
    cin>>action;
    switch(action){
    case 1:
        AddIteamsCrew();
        break;
    case 2:
        DeleteIteamsCrew();
        break;
    case 3:
        EditPricesCrew();
        break;
    default:
        cout << "\033[1;31mInvalid Option!\033[0m" << endl;
        break;
    }
}

void AddIteamsCrew(){
    cout<<endl;
    displayStack(Category);
    cout<<endl<<"Select your category to add iteam(s): ";
    int category;
    cin>>category;
    cout<<endl<<endl;
    string fruit, vegetable, s, drink;
    int price, p, snacks;
    switch(category){
    case 1:
        cout<<"Enter the name of the fruit you wanted to add: ";
        cin>>fruit;
        Fruits.push(fruit);
        cout<<"Enter the price of "<<fruit<<" :";
        cin>>price;
        Price.push(price);
        cout<<fruit<<" added successfully!"<<endl;
        crew();
        break;
    case 2:
        cout<<"Enter the name of the vegetable you wanted to add: ";
        cin>>vegetable;
        Vegetables.push(vegetable);
        cout<<"Enter the price of "<<vegetable<<" :";
        cin>>price;
        Price.push(price);
        cout<<vegetable<<" added successfully!"<<endl;
        crew();
        break;
    case 3:
        displayStack(Snacks);
        cout<<"Enter the type of snack you wanted to add: ";
        cin>>snacks;
        switch(snacks){
        case 1:
            cout<<"Enter the name of Lays: ";
            cin>>s;
            Lays.push(s);
            cout<<"Enter the price of "<<s<<" :";
            cin>>price;
            LaysP.push(price);
            cout<<s<<" added successfully!"<<endl;
            crew();
            break;
        case 2:
            cout<<"Enter the name of Kurkure: ";
            cin>>s;
            Kurkure.push(s);
            cout<<"Enter the price of "<<s<<" :";
            cin>>price;
            KurkureP.push(price);
            cout<<s<<" added successfully!"<<endl;
            crew();
            break;
        case 3:
            cout<<"Enter the name of Bingo: ";
            cin>>s;
            Bingo.push(s);
            cout<<"Enter the price of "<<s<<" :";
            cin>>price;
            BingoP.push(price);
            cout<<s<<" added successfully!"<<endl;
            crew();
            break;
        case 4:
            cout<<"Enter the name of Biscuit: ";
            cin>>s;
            Biscuits.push(s);
            cout<<"Enter the price of "<<s<<" :";
            cin>>price;
            BiscuitsP.push(price);
            cout<<s<<" added successfully!"<<endl;
            crew();
            break;
        default: 
            cout << "\033[1;31mInvalid Option!\033[0m" << endl;
            AddIteamsCrew();
        }
    case 4:
        cout<<"Enter the name of Drink you wanted to add: ";
        cin>>drink;
        Drinks.push(drink);
        cout<<"Enter the price of "<<drink<<" :";
        cin>>price;
        DrinksP.push(price);
        cout<<drink<<" added successfully!"<<endl;
        crew();
        break;
    default:
        cout << "\033[1;31mInvalid Option!\033[0m" << endl;
        crew();
    }
}

void Delete(stack<string>& Stack, int n){
    stack<string> dup;
    for(int i=1;i<n;i++){
        dup.push(Stack.top());
        Stack.pop();
    }
    Stack.pop();
    while(!dup.empty()){
        Stack.push(dup.top());
        dup.pop();
    }
}

void DeleteIteamsCrew(){
    cout<<endl;
    int category, fruit, vegetable, snacks, s, drink;
    displayStack(Category);
    cout<<"Enter the category: ";
    cin>>category;
    cout<<endl;
    switch(category){
    case 1:
        displayStack(Fruits);
        cout<<"Enter the serial number of the Fruit you wanted to delete: ";
        cin>>fruit;
        Delete(Fruits, fruit);
        cout<<fruit<<" deleted successfully!"<<endl;
        crew();
        break;
    case 2:
        displayStack(Vegetables);
        cout<<"Enter the serial number of the Vegetable you wanted to delete: ";
        cin>>vegetable;
        Delete(Vegetables, vegetable);
        cout<<vegetable<<" deleted successfully!"<<endl;
        crew();
        break;
    case 3:
        displayStack(Snacks);
        cout<<"Enter the type of Snack you wanted to delete: ";
        cin>>snacks;
        switch(snacks){
        case 1:
            displayStack(Lays);
            cout<<"Enter the serial number of the Lays you wanted to delete: ";
            cin>>s;
            Delete(Lays, s);
            cout<<s<<" deleted successfully!"<<endl;
            crew();
            break;
        case 2:
            displayStack(Kurkure);
            cout<<"Enter the serial number of the Kurkure you wanted to delete: ";
            cin>>s;
            Delete(Kurkure, s);
            cout<<s<<" deleted successfully!"<<endl;
            crew();
            break;
        case 3:
            displayStack(Bingo);
            cout<<"Enter the serial number of the Bingo you wanted to delete: ";
            cin>>s;
            Delete(Bingo, s);
            cout<<s<<" deleted successfully!"<<endl;
            crew();
            break;
        case 4:
            displayStack(Biscuits);
            cout<<"Enter the serial number of the Biscuit you wanted to delete: ";
            cin>>s;
            Delete(Biscuits, s);
            cout<<s<<" deleted successfully!"<<endl;
            crew();
            break;
        default: 
            cout << "\033[1;31mInvalid Option!\033[0m" << endl;
            AddIteamsCrew();
        }
    case 4:
        displayStack(Drinks);
        cout<<"Enter the serial number of the Drink you wanted to delete: ";
        cin>>drink;
        Delete(Drinks, drink);
        cout<<drink<<" deleted successfully!"<<endl;
        crew();
        break;
    default:
        cout << "\033[1;31mInvalid Option!\033[0m" << endl;
        crew();
    }
}

void edit(stack<int> Stack, int price, int n){
    stack<int> dup;
    for(int i=1;i<n;i++){
        dup.push(Stack.top());
        Stack.pop();
    }
    Stack.pop();
    Stack.push(price);
    for(int i=1;i<n;i++){
        Stack.push(dup.top());
        dup.pop();
    }
    return;
}

void EditPricesCrew(){
    cout<<endl;
    displayStack(Category);
    cout<<endl<<"Select your category to Edit their prices: ";
    int category;
    cin>>category;
    int fruit, vegetable, s, drink, price, p, snacks;
    cout<<endl;
    switch(category){
    case 1:
        displayStack(Fruits);
        cout<<"Enter the serial number of the fruit you wanted to edit: ";
        cin>>fruit;
        cout<<"Enter the new price of "<<fruit<<" :";
        cin>>price;
        edit(FruitsP, fruit, price);
        cout<<fruit<<" edited successfully!"<<endl;
        crew();
        break;
    case 2:
        displayStack(Vegetables);
        cout<<"Enter the serial number of the vegetable you wanted to edit: ";
        cin>>vegetable;
        cout<<"Enter the new price of "<<vegetable<<" :";
        cin>>price;
        edit(VegetablesP, vegetable, price);
        cout<<vegetable<<" edited successfully!"<<endl;
        crew();
        break;
    case 3:
        displayStack(Snacks);
        cout<<"Enter the type of snack you wanted to edit: ";
        cin>>snacks;
        switch(snacks){
        case 1:
            displayStack(Lays);
            cout<<"Enter the serial number of the Lays you wanted to edit: ";
            cin>>s;
            cout<<"Enter the new price of "<<s<<" :";
            cin>>price;
            edit(LaysP, s, price);
            cout<<s<<" edited successfully!"<<endl;
            crew();
            break;
        case 2:
            displayStack(Kurkure);
            cout<<"Enter the serial number of the Kurkure you wanted to edit: ";
            cin>>s;
            cout<<"Enter the new price of "<<s<<" :";
            cin>>price;
            edit(KurkureP, s, price);
            cout<<s<<" edited successfully!"<<endl;
            crew();
            break;
        case 3:
            displayStack(Bingo);
            cout<<"Enter the serial number of the Bingos you wanted to edit: ";
            cin>>s;
            cout<<"Enter the new price of "<<s<<" :";
            cin>>price;
            edit(BingoP,s, price);
            cout<<s<<" edited successfully!"<<endl;
            crew();
            break;
        case 4:
            displayStack(Biscuits);
            cout<<"Enter the serial number of the biscuit you wanted to edit: ";
            cin>>s;
            cout<<"Enter the new price of "<<s<<" :";
            cin>>price;
            edit(BiscuitsP, s, price);
            cout<<s<<" edited successfully!"<<endl;
            crew();
            break;
        default: 
            cout << "\033[1;31mInvalid Option!\033[0m" << endl;
            AddIteamsCrew();
        }
    case 4:
        displayStack(Drinks);
        cout<<"Enter the serial number of the drink you wanted to edit: ";
        cin>>drink;
        cout<<"Enter the new price of "<<drink<<" :";
        cin>>price;
        edit(DrinksP, drink, price);
        cout<<drink<<" edited successfully!"<<endl;
        crew();
        break;
    default:
        cout << "\033[1;31mInvalid Option!\033[0m" << endl;
        crew();
    }
}

void UI(){
    cout<<"1. Customer"<<endl
    <<"2. Crew"<<endl<<endl
    <<"Who are you (Select 1 or 2): ";
    int user;
    cin>>user;
    switch(user){
    case 1:
        Dashboard();
        break;
    case 2:
        login();
        break;
    default:
        cout << "\033[1;31mInvalid Option!\033[0m" << endl;
        UI();
    }
}

void login(){
    cout<<"\nEnter Pin: ";
    int pin;
    cin>>pin;
    if (pin == 12061010){
        crew();
    }else{
        cout<<"\033[1;31mIncorrect Pin entered!\nTry again:\033[0m";
        cin>>pin;
        if (pin == 12061010){
            crew();
        }else{
            UI();            
        }
    }
}

void Dashboard(){
    cout<<endl<<"1. Place an order\n2. Your orders\n3. View Cart\n4. Track your Order\n5. Search Items\n\nSelect your choice: ";
    int choice;
    cin>>choice;
    switch(choice){
    case 5:
        SearchDashboard();
        break;
    case 1:
        AddIteamsToCart();
        break;
    case 2:
        YourOrders();
        break;
    case 3:
        ViewCart();
        break;
    case 4:
        TrackYourOrders();
        break;
    default:
        cout << "\033[1;31mInvalid Option!\033[0m" << endl;
        Dashboard();
    }
}

void AddIteamsToCart(){
    cout<<endl<<endl<<"\033[1mCategories:\033[0m"<<endl<<endl;
    displayStack(Category);
    cout<<"5. View Dashboard\n\n";

    cout<<"Select your Category: ";
    int category;
    cin>>category;
    if (category == 1){
        displayStack(Fruits);
        cout<<"\n\nSelect Your Fruit:";
        int fruit;
        cin>>fruit;
        switch(fruit){
        case 1:
            if (Cart.size() <= 30){
                int Mango = 125, MangoC = 0;
                cout<<"\nCost of 2 Mangoes(Weighs around 500g each): "<<Mango<< " INR" <<endl;
                cout<<"How many PAIRS of Mangoes do you wanna add to your cart: ";
                cin>>MangoC;
                Cart.push("Mango");
                Price.push(MangoC*Mango);
                Quantity.push(MangoC);
                cout<<endl<<MangoC*2<<" Mangoes added successfully to your cart!";
                Sleep(1000);
                AddIteamsToCart();
            }else {
                cout<<"Cart has reached its Max limit! (Limit: 30)";
                Dashboard();
            }
            break;
        case 2:
            if (Cart.size() <= 30){
                int Watermelon = 50, WatermelonC = 0;
                cout<<"\nCost of 1 Watermelons(Weighs around 2.5Kg each): "<<Watermelon<<" INR"<<endl;
                cout<<"How many PAIRS of Watermelons do you wanna add to your cart: ";
                cin>>WatermelonC;
                Cart.push("Watermelon");
                Price.push(WatermelonC*Watermelon);
                Quantity.push(WatermelonC);
                cout<<endl<<WatermelonC<<" Watermelons added successfully to your cart!";
                Sleep(1000);
                AddIteamsToCart();
            }else {
                cout<<"Cart has reached its Max limit! (Limit: 30)";
                Dashboard();
            }
            break;
        case 3:
            if (Cart.size() <= 30){
                int Banana = 5, BananaC = 0;
                cout << "\nCost of 1 Banana (Weighs around 120g each): " << Banana << " INR" << endl;
                cout << "How many PAIRS of Bananas do you wanna add to your cart: ";
                cin >> BananaC;
                Cart.push("Banana");
                Price.push(BananaC*Banana);
                Quantity.push(BananaC);
                cout << endl << BananaC * 2 << " Bananas added successfully to your cart!";
                Sleep(1000);
                AddIteamsToCart();
            }else {
                cout<<"Cart has reached its Max limit! (Limit: 30)";
                Dashboard();
            }
            break;
        case 4:
            if (Cart.size() <= 30){
                int Pineapple = 60, PineappleC = 0;
                cout << "\nCost of 1 Pineapple (Weighs around 1.5Kg each): " << Pineapple << " INR" << endl;
                cout << "How many Pineapples do you wanna add to your cart: ";
                cin >> PineappleC;
                Cart.push("Pineapple");
                Price.push(Pineapple*PineappleC);
                Quantity.push(PineappleC);
                cout << endl << PineappleC << " Pineapple(s) added successfully to your cart!";
                Sleep(1000);
                AddIteamsToCart();
            }else {
                cout<<"Cart has reached its Max limit! (Limit: 30)";
                Dashboard();
            }
            break;
        case 5:
            if (Cart.size() <= 30){
                cout<<"1. Green Grapes\n2. Black Grapes\nChoose the kind of Grapes: ";
                int typeOfGrapes;
                cin>> typeOfGrapes;
                switch(typeOfGrapes){
                    case 1:
                        if (Cart.size() <= 30){
                            int GreenGrapes = 40, GreenGrapesC = 0;
                            cout << "\nCost of 1 bunch of Green Grapes (Weighs around 500g): " << GreenGrapes << " INR" << endl;
                            cout << "How many bunches of Green Grapes do you wanna add to your cart: ";
                            cin >> GreenGrapesC;
                            Cart.push("Green Grapes");
                            Quantity.push(GreenGrapesC);
                            cout << endl << GreenGrapesC << " bunch(es) of Green Grapes added successfully to your cart!" << endl;
                            Sleep(1000);
                            AddIteamsToCart();
                        }else {
                            cout<<"Cart has reached its Max limit! (Limit: 30)";
                            Dashboard();
                        }
                        break;
                    case 2:
                        if (Cart.size() <= 30){
                            int BlackGrapes = 40, BlackGrapesC = 0;
                            cout << "\nCost of 1 bunch of Black Grapes (Weighs around 500g): " << BlackGrapes << " INR" << endl;
                            cout << "How many bunches of Black Grapes do you wanna add to your cart: ";
                            cin >> BlackGrapesC;
                            Cart.push("Black Grapes");
                            Price.push(BlackGrapes*BlackGrapesC);
                            Quantity.push(BlackGrapesC);
                            cout << endl << BlackGrapesC << " bunch(es) of Black Grapes added successfully to your cart!" << endl;
                            Sleep(1000);
                            AddIteamsToCart();
                        }else {
                            cout<<"Cart has reached its Max limit! (Limit: 30)";
                            Dashboard();
                        }
                    default:
                        cout << "\033[1;31mInvalid Option!\033[0m" << endl;
                        Dashboard();
                        break;
                }
            }else {
                cout<<"Cart has reached its Max limit! (Limit: 30)";
                Dashboard();
            }
        case 6:
            if (Cart.size() <= 30){
                int Coconut = 30, CoconutC = 0;
                cout << "\nCost of 1 Coconut (Weighs around 1.2Kg): " << Coconut << " INR" << endl;
                cout << "How many Coconuts do you wanna add to your cart: ";
                cin >> CoconutC;
                Cart.push("Coconut");
                Price.push(Coconut*Coconut);
                Quantity.push(CoconutC);
                cout << endl << CoconutC << " Coconut(s) added successfully to your cart!" << endl;
                Sleep(1000);
                AddIteamsToCart();
            }else {
                cout<<"Cart has reached its Max limit! (Limit: 30)";
                Dashboard();
            }
            break;
        case 7:
            if (Cart.size() <= 30){
                int Papaya = 45, PapayaC = 0;
                cout << "\nCost of 1 Papaya (Weighs around 1.8Kg): " << Papaya << " INR" << endl;
                cout << "How many Papayas do you wanna add to your cart: ";
                cin >> PapayaC;
                Cart.push("Papaya");
                Price.push(Papaya*PapayaC);
                Quantity.push(PapayaC);
                cout << endl << PapayaC << " Papaya(s) added successfully to your cart!" << endl;
                Sleep(1000);
                AddIteamsToCart();

            }else {
                cout<<"Cart has reached its Max limit! (Limit: 30)";
                Dashboard();
            }
            break;
        case 8:
            if (Cart.size() <= 30){
                int Guava = 25, GuavaC = 0;
                cout << "\nCost of 2 Guavas (Weighs around 400g): " << Guava * 2 << " INR" << endl;
                cout << "How many Pairs of Guavas do you wanna add to your cart: ";
                cin >> GuavaC;
                Cart.push("Guava");
                Price.push(Guava*GuavaC);
                Quantity.push(GuavaC);
                cout << endl << GuavaC * 2 << " Guava(s) added successfully to your cart!" << endl;
                Sleep(1000);
                AddIteamsToCart();

            }else {
                cout<<"Cart has reached its Max limit! (Limit: 30)";
                Dashboard();
            }
            break;
        case 9:
            if (Cart.size() <= 30){
                int Apple = 30, AppleC = 0;
                cout << "\nCost of 2 Apples (Weighs around 360g): " << Apple * 2 << " INR" << endl;
                cout << "How many Pairs of Apples do you wanna add to your cart: ";
                cin >> AppleC;
                Cart.push("Apple");
                Price.push(Apple*AppleC);
                Quantity.push(AppleC);
                cout << endl << AppleC * 2 << " Apple(s) added successfully to your cart!" << endl;
                Sleep(1000);
                AddIteamsToCart();
            }else {
                cout<<"Cart has reached its Max limit! (Limit: 30)";
                Dashboard();
            }
            break;
        case 10:
            if (Cart.size() <= 30){
                int DragonFruit = 90, DragonFruitC = 0;
                cout << "\nCost of 2 Dragon Fruits (Weighs around 900g): " << DragonFruit * 2 << " INR" << endl;
                cout << "How many Pairs of Dragon Fruits do you wanna add to your cart: ";
                cin >> DragonFruitC;
                Cart.push("Dragon Fruit");
                Price.push(DragonFruit*DragonFruitC);
                Quantity.push(DragonFruitC);
                cout << endl << DragonFruitC * 2 << " Dragon Fruit(s) added successfully to your cart!" << endl;
                Sleep(1000);
                AddIteamsToCart();
            }else {
                cout<<"Cart has reached its Max limit! (Limit: 30)";
                Dashboard();
            }
            break;
        case 11:
            if (Cart.size() <= 30){
                int Kiwi = 20, KiwiC = 0;
                cout << "\nCost of 2 Kiwis (Weighs around 200g): " << Kiwi * 2 << " INR" << endl;
                cout << "How many Pairs of Kiwis do you wanna add to your cart: ";
                cin >> KiwiC;
                Cart.push("Kiwi");
                Price.push(Kiwi*KiwiC);
                Quantity.push(KiwiC);
                cout << endl << KiwiC * 2 << " Kiwi(s) added successfully to your cart!" << endl;
                Sleep(1000);
                AddIteamsToCart();
            }else {
                cout<<"Cart has reached its Max limit! (Limit: 30)";
                Dashboard();
            }
            break;
        case 12:
            if (Cart.size() <= 30){
                int Orange = 20, OrangeC = 0;
                cout << "\nCost of 2 Oranges (Weighs around 400g): " << Orange * 2 << " INR" << endl;
                cout << "How many Pairs of Oranges do you wanna add to your cart: ";
                cin >> OrangeC;
                Cart.push("Orange");
                Price.push(Orange*OrangeC);
                Quantity.push(OrangeC);
                cout << endl << OrangeC * 2 << " Orange(s) added successfully to your cart!" << endl;
                Sleep(1000);
                AddIteamsToCart();
            }else {
                cout<<"Cart has reached its Max limit! (Limit: 30)";
                Dashboard();
            }
            break;
        default:
            cout << "\033[1;31mInvalid Option!\033[0m" << endl;
            AddIteamsToCart();
        }
    }else if(category == 2){        
        displayStack(Vegetables);
        cout<<"\n\nSelect Your Vegetable:";
        int vegetable;
        cin>>vegetable;
        switch(vegetable){
        case 1:
            if (Cart.size() <= 30){
                int TomatoPer50g = 4, TomatoG = 0;
                cout << "\nCost of 100g Tomatoes: " << TomatoPer50g << " INR" << endl;
                cout << "Enter weight of Tomatoes in grams(above 200g): ";
                cin >> TomatoG;
                if (TomatoG >= 200){
                    Cart.push("Tomato");
                    Price.push(TomatoPer50g*TomatoG);
                    Quantity.push(TomatoG);
                    cout << endl << TomatoG << "g of Tomato(s) added successfully to your cart!" << endl;
                    Sleep(1000);
                    AddIteamsToCart();
                }else {
                    cout<<"\033[1;31mQuantity is less than the minimum allowed quantity!\033[0m";
                    AddIteamsToCart();
                }
            }else {
                cout<<"Cart has reached its Max limit! (Limit: 30)";
                Dashboard();
            }
            break;
        case 2:
            if (Cart.size() <= 30){
                int BrinjalPer100g = 8, BrinjalG = 0;
                cout << "\nCost of 100g Brinjal: " << BrinjalPer100g << " INR" << endl;
                cout << "Enter weight of Brinjal in grams: ";
                cin >> BrinjalG;
                Cart.push("Brinjal");
                Price.push(BrinjalPer100g*BrinjalG);
                Quantity.push(BrinjalG);
                cout << endl << BrinjalG << "g of Brinjal added successfully to your cart!" << endl;
                Sleep(1000);
                AddIteamsToCart();
            }else {
                cout<<"Cart has reached its Max limit! (Limit: 30)";
                Dashboard();
            }
            break;
        case 3:
            if (Cart.size() <= 30){
                int Drumstick = 12, DrumstickC = 0;
                cout << "\nCost of 2 Drumsticks (approx 250g): " << Drumstick * 2 << " INR" << endl;
                cout << "How many Pairs of Drumsticks do you wanna add to your cart: ";
                cin >> DrumstickC;
                Cart.push("Drumstick");
                Price.push(Drumstick*DrumstickC);
                Quantity.push(DrumstickC);
                cout << endl << DrumstickC * 2 << " Drumstick(s) added successfully to your cart!" << endl;
                Sleep(1000);
                AddIteamsToCart();
            }else {
                cout<<"Cart has reached its Max limit! (Limit: 30)";
                Dashboard();
            }
            break;
        case 4:
            if (Cart.size() <= 30){
                int SnakeGourd = 20, SnakeGourdC = 0;
                cout << "\nCost of 2 Snake Gourds (approx 700g): " << SnakeGourd * 2 << " INR" << endl;
                cout << "How many Pairs of Snake Gourds do you wanna add to your cart: ";
                cin >> SnakeGourdC;
                Cart.push("Snake Gourd");
                Price.push(SnakeGourd*SnakeGourdC);
                Quantity.push(SnakeGourdC);
                cout << endl << SnakeGourdC * 2 << " Snake Gourd(s) added successfully to your cart!" << endl;
                Sleep(1000);
                AddIteamsToCart();
            }else {
                cout<<"Cart has reached its Max limit! (Limit: 30)";
                Dashboard();
            }
            break;
        case 5:
            if (Cart.size() <= 30){
                int BitterGourd = 18, BitterGourdC = 0;
                cout << "\nCost of 2 Bitter Gourds (approx 350g): " << BitterGourd * 2 << " INR" << endl;
                cout << "How many Pairs of Bitter Gourds do you wanna add to your cart: ";
                cin >> BitterGourdC;
                Cart.push("Bitter Gourd");
                Price.push(BitterGourd*BitterGourdC);
                Quantity.push(BitterGourdC);
                cout << endl << BitterGourdC * 2 << " Bitter Gourd(s) added successfully to your cart!" << endl;
                Sleep(1000);
                AddIteamsToCart();
            }else {
                cout<<"Cart has reached its Max limit! (Limit: 30)";
                Dashboard();
            }
            break;
        case 7:
            if (Cart.size() <= 30){
                int AshGourd = 28, AshGourdC = 0;
                cout << "\nCost of 2 Ash Gourds (approx 1.5kg): " << AshGourd * 2 << " INR" << endl;
                cout << "How many Pairs of Ash Gourds do you wanna add to your cart: ";
                cin >> AshGourdC;
                Cart.push("Ash Gourd");
                Price.push(AshGourd*AshGourdC);
                Quantity.push(AshGourdC);
                cout << endl << AshGourdC * 2 << " Ash Gourd(s) added successfully to your cart!" << endl;
                Sleep(1000);
                AddIteamsToCart();
            }else {
                cout<<"Cart has reached its Max limit! (Limit: 30)";
                Dashboard();
            }
            break;
        case 8:
            if (Cart.size() <= 30){
                int RawBanana = 10, RawBananaC = 0;
                cout << "\nCost of 2 Raw Bananas (approx 350g): " << RawBanana * 2 << " INR" << endl;
                cout << "How many Pairs of Raw Bananas do you wanna add to your cart: ";
                cin >> RawBananaC;
                Cart.push("Raw Banana");
                Price.push(RawBanana*RawBananaC);
                Quantity.push(RawBananaC);
                cout << endl << RawBananaC * 2 << " Raw Banana(s) added successfully to your cart!" << endl;
                Sleep(1000);
                AddIteamsToCart();
            }else {
                cout<<"Cart has reached its Max limit! (Limit: 30)";
                Dashboard();
            }
            break;
        case 9:
            if (Cart.size() <= 30){
                int LadiesFingerPer100g = 12, LadiesFingerG = 0;
                cout << "\nCost of 100g Ladies Finger: " << LadiesFingerPer100g << " INR" << endl;
                cout << "Enter weight of Ladies Finger in grams: ";
                cin >> LadiesFingerG;
                Cart.push("Ladies Finger");
                Price.push(LadiesFingerPer100g*LadiesFingerG);
                Quantity.push(LadiesFingerG);
                cout << endl << LadiesFingerG << "g of Ladies Finger added successfully to your cart!" << endl;
                Sleep(1000);
                AddIteamsToCart();
            }else {
                cout<<"Cart has reached its Max limit! (Limit: 30)";
                Dashboard();
            }
            break;
        case 10:
            if (Cart.size() <= 30){
                int RidgeGourdPer100g = 10, RidgeGourdG = 0;
                cout << "\nCost of 100g Ridge Gourd: " << RidgeGourdPer100g << " INR" << endl;
                cout << "Enter weight of Ridge Gourd in grams: ";
                cin >> RidgeGourdG;
                Cart.push("Ridge Gourd");
                Price.push(RidgeGourdPer100g*RidgeGourdG);
                Quantity.push(RidgeGourdG);
                cout << endl << RidgeGourdG << "g of Ridge Gourd added successfully to your cart!" << endl;
                Sleep(1000);
                AddIteamsToCart();
            }else {
                cout<<"Cart has reached its Max limit! (Limit: 30)";
                Dashboard();
            }
            break;
        case 6:
            if (Cart.size() <= 30){
                int BottleGourd = 25, BottleGourdC = 0;
                cout << "\nCost of 2 Bottle Gourds (approx 1kg): " << BottleGourd * 2 << " INR" << endl;
                cout << "How many Pairs of Bottle Gourds do you wanna add to your cart: ";
                cin >> BottleGourdC;
                Cart.push("Bottle Gourd");
                Price.push(BottleGourd*BottleGourdC);
                Quantity.push(BottleGourdC);
                cout << endl << BottleGourdC * 2 << " Bottle Gourd(s) added successfully to your cart!" << endl;
                Sleep(1000);
                AddIteamsToCart();
            }else {
                cout<<"Cart has reached its Max limit! (Limit: 30)";
                Dashboard();
            }
            break;
        }
    }else if(category == 3){
        displayStack(Snacks);
        cout<<"\n\nSelect your type of Snack:";
        int SnackType;
        cin>>SnackType;
        cout<<endl;
        if (SnackType == 1){
            displayStack(Lays);
            cout<<"\nSelect Flavour: ";
            int flavour;
            cin>>flavour;
            cout<<"Enter the quantity (Every flavour is sold as a pac of '2', Costs 60 INR): ";
            int quantity;
            cin>>quantity;
            cout<<endl<<quantity<<" pairs added successfully to your cart!";
            switch(flavour){
                case 1:
                    Cart.push("India's Magic Masala Potato Chips");
                    Price.push(quantity*60);
                    Quantity.push(quantity);
                    Sleep(1000);
                    AddIteamsToCart();
                    break;
                case 2:
                    Cart.push("American Style Cream & Onion Potato Chips");
                    Price.push(quantity*60);
                    Quantity.push(quantity);
                    Sleep(1000);
                    AddIteamsToCart();
                    break;
                case 3:
                    Cart.push("Spanish Tomato Tango Potato Chips");
                    Price.push(quantity*60);
                    Quantity.push(quantity);
                    Sleep(1000);
                    AddIteamsToCart();
                    break;
                case 4:
                    Cart.push("Classic Salted Flavor Potato Chips");
                    Price.push(quantity*60);
                    Quantity.push(quantity);
                    Sleep(1000);
                    AddIteamsToCart();
                    break;
                case 5:
                    Cart.push("Chile Limon Flavour Potato Chips");
                    Price.push(quantity*60);
                    Quantity.push(quantity);
                    Sleep(1000);
                    AddIteamsToCart();
                    break;
                default: 
                    cout << "\033[1;31mInvalid Option!\033[0m" << endl;
                    Dashboard();
            }
        }else if (SnackType == 2){
            displayStack(Kurkure);
            cout<<"\nSelect Flavour: ";
            int flavour;
            cin>>flavour;
            cout<<"Enter the quantity (Every flavour is sold as a pac of '2', Costs 90 INR): ";
            int quantity;
            cin>>quantity;
            switch(flavour){
                case 1:
                    Cart.push("Masala Munch Crisps");
                    Price.push(quantity*90);
                    Quantity.push(quantity);
                    Sleep(1000);
                    AddIteamsToCart();
                    break;
                case 2:
                    Cart.push("Chilli Chatka Crisps");
                    Price.push(quantity*90);
                    Quantity.push(quantity);
                    Sleep(1000);
                    AddIteamsToCart();
                    break;
                case 3:
                    Cart.push("Puffcorn Yummy Cheese Puffs");
                    Price.push(quantity*90);
                    Quantity.push(quantity);
                    Sleep(1000);
                    AddIteamsToCart();
                    break;
                default: 
                    cout << "\033[1;31mInvalid Option!\033[0m" << endl;
                    Dashboard();
            }
        }else if (SnackType == 3){
            displayStack(Bingo);
            cout<<"\nSelect Flavour: ";
            int flavour;
            cin>>flavour;
            cout<<"Enter the quantity (Every flavour is sold as a pac of '2', Costs 100 INR): ";
            int quantity;
            cin>>quantity;
            switch(flavour){
                case 1:
                    Cart.push("Mad Angles Tomato Madness Crisps");
                    Price.push(quantity*100);
                    Quantity.push(quantity);
                    Sleep(1000);
                    AddIteamsToCart();
                    break;
                case 2:
                    Cart.push("Mad Angles Achaari Masti Crisps");
                    Price.push(quantity*100);
                    Quantity.push(quantity);
                    Sleep(1000);
                    AddIteamsToCart();
                    break;
                case 3:
                    Cart.push("Mad Angles Cheese Nachos");
                    Price.push(quantity*100);
                    Quantity.push(quantity);
                    Sleep(1000);
                    AddIteamsToCart();
                    break;
                case 4:
                    Cart.push("Original Style Chilli Sprinkled Potato Chips");
                    Price.push(quantity*100);
                    Quantity.push(quantity);
                    Sleep(1000);
                    AddIteamsToCart();
                    break;
                default: 
                    cout << "\033[1;31mInvalid Option!\033[0m" << endl;
                    Dashboard();
            }
        }else if (SnackType == 4){
            displayStack(Biscuits);
            cout<<"\nEnter the number corresponding to your choice: ";
            int Choice;
            cin>>Choice;
            switch(Choice){
                case 1:
                    cout<<"Pack of 2, costs 125 INR"<<endl;
                    cout<<"Enter the quantity : ";
                    int quantity;
                    cin>>quantity;
                    Cart.push("Oreo");
                    Price.push(quantity*125);
                    Quantity.push(quantity);
                    cout << endl << quantity << "pack(s)are added successfully to your cart!" << endl;
                    Sleep(1000);
                    AddIteamsToCart();
                    break;
                case 2:
                    cout<<"Pack of 2, costs 80 INR"<<endl;
                    cout<<"Enter the quantity : ";
                    cin>>quantity;
                    Cart.push("Sunfeast Bourbon");
                    Price.push(quantity*80);
                    Quantity.push(quantity);
                    cout << endl << quantity << "pack(s)are added successfully to your cart!" << endl;
                    Sleep(1000);
                    AddIteamsToCart();
                    break;
                case 3:
                    cout<<"Pack of 250 gm, costs 110 INR"<<endl;
                    cout<<"Enter the quantity : ";
                    cin>>quantity;
                    Cart.push("Dark Fantacy");
                    Price.push(quantity*80);
                    Quantity.push(quantity);
                    cout << endl << quantity << "pack(s)are added successfully to your cart!" << endl;
                    Sleep(1000);
                    AddIteamsToCart();
                    break;
                case 4:
                    cout<<"Pack of 125 gm, costs 30 INR"<<endl;
                    cout<<"Enter the quantity : ";
                    cin>>quantity;
                    Cart.push("Sunfeast Nice");
                    Price.push(quantity*30);
                    Quantity.push(quantity);
                    cout << endl << quantity << "pack(s)are added successfully to your cart!" << endl;
                    Sleep(1000);
                    AddIteamsToCart();
                    break;
                case 5:
                    cout<<"Pack of 208 gm, costs 45 INR"<<endl;
                    cout<<"Enter the quantity : ";
                    cin>>quantity;
                    Cart.push("Marie Gold");
                    Price.push(quantity*45);
                    Quantity.push(quantity);
                    cout << endl << quantity << "pack(s)are added successfully to your cart!" << endl;
                    Sleep(1000);
                    AddIteamsToCart();
                    break;
                case 6:
                    cout<<"Pack of 800 gm, costs 100 INR"<<endl;
                    cout<<"Enter the quantity : ";
                    cin>>quantity;
                    Cart.push("Parle-G");
                    Price.push(quantity*100);
                    Quantity.push(quantity);
                    cout << endl << quantity << "pack(s)are added successfully to your cart!" << endl;
                    Sleep(1000);
                    AddIteamsToCart();
                    break;
                case 7:
                    cout<<"Pack of 700 gm, costs 130 INR"<<endl;
                    cout<<"Enter the quantity : ";
                    cin>>quantity;
                    Cart.push("Monaco");
                    Price.push(quantity*30);
                    Quantity.push(quantity);
                    cout << endl << quantity << "pack(s)are added successfully to your cart!" << endl;
                    Sleep(1000);
                    AddIteamsToCart();
                    break;
                case 8:
                    cout<<"Pack of 200 gm, costs 60 INR"<<endl;
                    cout<<"Enter the quantity : ";
                    cin>>quantity;
                    Cart.push("Hide & Seek");
                    Price.push(quantity*60);
                    Quantity.push(quantity);
                    cout << endl << quantity << "pack(s)are added successfully to your cart!" << endl;
                    Sleep(1000);
                    AddIteamsToCart();
                    break;
                case 9:
                    cout<<"Pack of 200 gm, costs 40 INR"<<endl;
                    cout<<"Enter the quantity : ";
                    cin>>quantity;
                    Cart.push("Mom's Magic");
                    Price.push(quantity*40);
                    Quantity.push(quantity);
                    cout << endl << quantity << "pack(s)are added successfully to your cart!" << endl;
                    Sleep(1000);
                    AddIteamsToCart();
                    break;
                default: 
                    cout << "\033[1;31mInvalid Option!\033[0m" << endl;
                    Dashboard();
            }
        }else{
            cout << "\033[1;31mInvalid Option!\033[0m" << endl;
            Dashboard();
        }
    }else if(category == 4){
        displayStack(Drinks);
        int choice;
        cout<<endl<<"Enter your choice of Drink: ";
        cin>>choice;
        if (choice == 1){
            int Sprite = 96, SpriteC = 0;
            cout << "\nCost of 2 ltr Sprite: " << Sprite << " INR" << endl;
            cout << "Enter the no.of Bottles: ";
            cin >> SpriteC;
            Cart.push("Sprite");
            Price.push(Sprite*SpriteC);
            Quantity.push(SpriteC);
            cout << endl << SpriteC << " bottle(s) added successfully to your cart!" << endl;
            Sleep(1000);
            AddIteamsToCart();
        }else if(choice == 2){
            int Thumbsup = 99, ThumbsupC = 0;
            cout << "\nCost of 2 ltr Thumbsup: " << Thumbsup << " INR" << endl;
            cout << "Enter the no.of Bottles: ";
            cin >> ThumbsupC;
            Cart.push("Thumbsup");
            Price.push(Thumbsup*ThumbsupC);
            Quantity.push(ThumbsupC);
            cout << endl << ThumbsupC << " bottle(s) added successfully to your cart!" << endl;
            Sleep(1000);
            AddIteamsToCart();
        }else if(choice == 3){
            int CocaCola = 99, CocaColaC = 0;
            cout << "\nCost of 750 ml Coca-Cola: " << CocaCola << " INR" << endl;
            cout << "Enter the no.of Bottles: ";
            cin >> CocaColaC;
            Cart.push("CocaCola");
            Price.push(CocaCola*CocaColaC);
            Quantity.push(CocaColaC);
            cout << endl << CocaColaC << " bottle(s) added successfully to your cart!" << endl;
            Sleep(1000);
            AddIteamsToCart();
        }else if(choice == 4){
            int Maaza = 99, MaazaC = 0;
            cout << "\nCost of 2 ltr Maaza: " << Maaza << " INR" << endl;
            cout << "Enter the no.of Bottles: ";
            cin >> MaazaC;
            Cart.push("Maaza");
            Price.push(Maaza*MaazaC);
            Quantity.push(MaazaC);
            cout << endl << MaazaC << " bottle(s) added successfully to your cart!" << endl;
            Sleep(1000);
            AddIteamsToCart();
        }else if(choice == 5){
            int PulpyO = 90, PulpyOC = 0;
            cout << "\nCost of 1 ltr Pulpy Orange: " << PulpyO << " INR" << endl;
            cout << "Enter the no.of Bottles: ";
            cin >> PulpyOC;
            Cart.push("PulpyO");
            Price.push(PulpyO*PulpyOC);
            Quantity.push(PulpyOC);
            cout << endl << PulpyOC << " bottle(s) added successfully to your cart!" << endl;
            Sleep(1000);
            AddIteamsToCart();
        }else if(choice == 6){
            int Fizz = 40, FizzC = 0;
            cout << "\nCost of 600 ml Appy Fizz: " << Fizz << " INR" << endl;
            cout << "Enter the no.of Bottles: ";
            cin >> FizzC;
            Cart.push("Fizz");
            Price.push(Fizz*FizzC);
            Quantity.push(FizzC);
            cout << endl << FizzC << " bottle(s) added successfully to your cart!" << endl;
            Sleep(1000);
            AddIteamsToCart();
        }else{
            cout << "\033[1;31mInvalid Option!\033[0m" << endl;
            AddIteamsToCart();
        }
    }else if(category == 5){
        Dashboard();
    }else{
        cout << "\033[1;31mInvalid Option!\033[0m" << endl;
        AddIteamsToCart();
    }
}

void ViewCart(){
    cout<<"\n\033[1mYour Cart:\033[0m"<<endl;
    DisplayCart();
}

void DisplayCart(){
    int grandTotal = 0, discount = 0, total = 0;
    stack<string> tempCart(Cart);
    stack<int> tempQ(Quantity);
    stack<int> tempP(Price);
    cout<<left<<setw(45)<<"Item"<<setw(10)<<"Qty"<<setw(10)<<"Price"<<endl;
    cout << "----------------------------------------------------------------"<<endl;
    while(!tempCart.empty()){
        cout<<left<<setw(45)<<tempCart.top()<<setw(10)<<tempQ.top()<<setw(10)<<tempP.top()<<endl;
        total += tempP.top();
        tempCart.pop();
        tempQ.pop();
        tempP.pop();
    }
    discount = total / 10;
    grandTotal = total - discount;
    cout << "----------------------------------------------------------------"<<endl;
    cout<<right<<setw(55)<< "Total: Rs. "<<total<<endl;
    cout<<right<<setw(62)<< "\033[1;32mDISCOUNT:\033[0m"<<"Rs.  "<< total / 10 <<endl;
    cout<<right<<setw(56)<< "Grand Total: Rs.  "<<total - discount<<endl;
    Display(grandTotal);
}

void Display(int grandTotal){
    cout<<"\n1. Place Order"<<endl
    <<"2. Delete Items from cart"<<endl
    <<"3. View dashboard"<<endl;
    cout<<"Select the operation you wanted to do: ";
    int choice;
    cin>>choice;
    switch(choice){
    case 5:
        SearchDashboard();
        break;
        case 1:
            placeOrder(grandTotal);
            break;
        case 2:
	        DeleteItems();            
            break;
        case 3:
            Dashboard();
            break;
        default:
            cout << "\033[1;31mInvalid Option!\033[0m" << endl;
            Dashboard();
    }
}

void placeOrder(int grandTotal){
    if (!Cart.empty()){
        string DeliveryAdd;
        cout<<endl<<"Enter the pin code of the Delivery Address: ";
        int pinCode;
        cin>>pinCode;
        cout<<endl<<"Verifying whether we can Deliver to your Address";
        for(int j=0;j<5;j++){
            cout<<".";
            Sleep(1000);
        }
        Sleep(1000);
        if (pinCode>=500001 && pinCode<=502032){
            cout<<"\033[1;32m\n\nYay! Delivery is available at your place!\n\033[0m";
            cout<<"Enter Delivery Address: ";
            cin>>DeliveryAdd;
            payment(grandTotal, DeliveryAdd);
        }else{
            cout<<"\033[1;31m\nSorry, delivery is not available at your location.\033[0m";
            placeOrder(grandTotal);
        }
    }else{
        cout<<"\n\033[1;31mPlease add iteams to cart to Proceed!\033[0m";
        Dashboard();
    }
}

void payment(int grandTotal, string DeliveryAdd){
    cout << "\n1. Credit/Debit Card\n"
    << "2. UPI\n"
    << "3. Cash on Delivery\n"
    <<"Choose a payment method:\n";
    int paymentType;
    string upiID;
    cin>>paymentType;
    switch(paymentType){
    case 1:
        long long cardNumber;
        int cvv, cardPin;
        cout<<"\nEnter your Crad number: ";
        cin>>cardNumber;
        cout<<"Enter CVV: ";
        cin>>cvv;
        cout<<"Enter PIN: ";
        cin>>cardPin;
        if((cvv < 100 || cvv > 999) || (cardPin < 1000 || cardPin > 9999) || (cardNumber <= 100000000000 || cardNumber >= 999999999999)){
            cout<< "\033[1;31mIncorrect card details entered!\033[0m"<<endl;
            placeOrder(grandTotal);
            break;
        }
        cout<<"Processing payment";
        for(int j=0;j<5;j++){
            cout<<".";
            Sleep(1000);
        }
        cout<<"\nPayment Successful. Order Confirmed!\n";
        PaymentType.push("Credit Card / Debit Card");
        DeliveryAddress.push(DeliveryAdd);
        TotalFareForHistory.push(grandTotal);
        while(!Cart.empty()){
            Cart.pop();
            Quantity.pop();
            Price.pop();
        }
        Sleep(1000);
        Dashboard();
        break;
    case 2:
        cout << "Enter your UPI ID: ";
        cin >> upiID;
        cout << "Processing payment through "<<upiID;
        for(int j=0;j<5;j++){
            cout<<".";
            Sleep(1000);
        }
        cout << "Payment Successful via UPI!\n";
        PaymentType.push("UPI");
        DeliveryAddress.push(DeliveryAdd);
        TotalFareForHistory.push(grandTotal);
        while(!Cart.empty()){
            Cart.pop();
            Quantity.pop();
            Price.pop();
        }
        Sleep(1000);
        Dashboard();
        break;
    case 3:
        cout<<"Order Confirmed!\n";
        PaymentType.push("Cash on Delivery");
        DeliveryAddress.push(DeliveryAdd);
        TotalFareForHistory.push(grandTotal);
        while(!Cart.empty()){
            Cart.pop();
            Quantity.pop();
            Price.pop();
        }
        Sleep(1000);
        Dashboard();
        break;
    default:
        cout<<"\033[1;31mInvalid Payment Type!\033[0m";
        payment(grandTotal, DeliveryAdd);
    }
}

void DeleteItems() {
    vector<string> tempCart;
    vector<int> tempQty;
    vector<int> tempPrice;

    while (!Cart.empty()) {
        tempCart.push_back(Cart.top());
        tempQty.push_back(Quantity.top());
        tempPrice.push_back(Price.top());
        Cart.pop();
        Quantity.pop();
        Price.pop();
    }

    cout << "\nYour Cart:\n";
    cout << left << setw(45) << "Item" << setw(10) << "Qty" << "Price\n";
    cout << "----------------------------------------------------------------\n";
    for (int i = 0; i < tempCart.size(); ++i) {
        cout << setw(2) << (i + 1) << ". " << setw(42) << tempCart[i] << setw(10) << tempQty[i] << tempPrice[i] << "\n";
    }
    cout << "----------------------------------------------------------------\n";

    vector<int> deletingItemsList;
    int serial;
    cout << "Enter the serial numbers of the items you want to delete (Enter 0 when done): ";
    while (true) {
        cin >> serial;
        if (serial == 0) break;
        if (serial > 0 && serial <= tempCart.size()) {
            deletingItemsList.push_back(serial - 1);
        } else {
            cout << "Invalid serial number: " << serial << endl;
        }
    }

    sort(deletingItemsList.begin(), deletingItemsList.end());

    for (int i = 0; i < deletingItemsList.size(); ++i) {
        int idx = deletingItemsList[i];
        cout << "Deleting item " << (idx + 1) << ": " << tempCart[idx] << endl;
        tempCart.erase(tempCart.begin() + idx);
        tempQty.erase(tempQty.begin() + idx);
        tempPrice.erase(tempPrice.begin() + idx);
        for(int j=i;j<deletingItemsList.size();j++){
            deletingItemsList[j]--;
        }
    }

    for (int i = tempCart.size() - 1; i >= 0; --i) {
        Cart.push(tempCart[i]);
        Quantity.push(tempQty[i]);
        Price.push(tempPrice[i]);
    }

    cout << "\n  Selected items have been deleted from your cart.\n";
    Dashboard();

}

string normalize(const string& str) {
    string result;
    for (char ch : str) {
        if (!isspace(ch))
            result += tolower(ch);
    }
    return result;
}

void searchItems(stack<string> originalStack, const string& keyword) {
    vector<string> items;
    string target = normalize(keyword);

    while (!originalStack.empty()) {
        items.push_back(originalStack.top());
        originalStack.pop();
    }

    bool found = false;
    cout << "\n\033[1mSearch Results for '" << keyword << "':\033[0m\n";
    for (int i = items.size() - 1; i >= 0; --i) {
        string normItem = normalize(items[i]);
        if (normItem.find(target) != string::npos) {
            cout << "- " << items[i] << "\n";
            found = true;
        }
    }

    if (!found) {
        cout << "\033[1;31mNo match found.\033[0m\n";
    }
}

void SearchDashboard() {
    cout << "\n\033[1mSearch Panel:\033[0m\n";
    cout << "1. Fruits\n2. Vegetables\n3. Snacks - Lays\n4. Snacks - Kurkure\n5. Drinks\n6. Back to Dashboard\n";
    cout << "What do you want to search in: ";
    int choice;
    cin >> choice;
    string keyword;

    switch(choice) {
        case 1: 
            cout << "Enter item name to search: ";
            cin.ignore();
            getline(cin, keyword);
            searchItems(Fruits, keyword); 
            break;
        case 2: 
            cout << "Enter item name to search: ";
            cin.ignore();
            getline(cin, keyword);
            searchItems(Vegetables, keyword); 
            break;
        case 3: 
            cout << "Enter item name to search: ";
            cin.ignore();
            getline(cin, keyword);
            searchItems(Lays, keyword); 
            break;
        case 4: 
            cout << "Enter item name to search: ";
            cin.ignore();
            getline(cin, keyword);
            searchItems(Kurkure, keyword); 
            break;
        case 5: 
            cout << "Enter item name to search: ";
            cin.ignore();
            getline(cin, keyword);
            searchItems(Drinks, keyword); 
            break;
        case 6:
            Dashboard(); 
            return;
        default: cout << "Invalid choice!\n"; break;
    }

    SearchDashboard();
}