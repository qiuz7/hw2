#include "coins.hpp"
#include<iostream>
using namespace std;
#include <iomanip>

Coins::Coins(int q, int d, int n, int p) {
    quarters=q;
    dimes=d;
    nickels=n;
    pennies=p;
}
void Coins::deposit_coins(Coins & coins){
    quarters+=coins.quarters;
    dimes+=coins.dimes;
    nickels+=coins.nickels;
    pennies+=coins.pennies;

    coins.quarters = 0;
    coins.dimes = 0;
    coins.nickels = 0;
    coins.pennies = 0;
}

bool Coins::has_exact_change_for_coins(const Coins& coins) const{
    return(quarters >= coins.quarters && dimes >= coins.dimes && 
            nickels >= coins.nickels && pennies >= coins.pennies);
}

Coins Coins::extract_exact_change(const Coins& coins){
    if (!has_exact_change_for_coins(coins)) {
        return Coins(0, 0, 0, 0); 
    }
    quarters -= coins.quarters;
    dimes -= coins.dimes;
    nickels -= coins.nickels;
    pennies -= coins.pennies;
    return coins;
}

int Coins::total_value_in_cents() const{
    return (quarters * CENTS_PER_QUARTER) + (dimes * CENTS_PER_DIME) + 
           (nickels * CENTS_PER_NICKEL) + pennies;
}

void Coins::print(std::ostream& out) const {
    out << quarters << " quarters, " << dimes << " dimes, " 
        << nickels << " nickels, " << pennies << " pennies";
}


std::ostream& operator<<(std::ostream& out, const Coins& coins) {
    coins.print(out);
    return out;
}

Coins coins_required_for_cents(int amount_in_cents) {
    int q = amount_in_cents / CENTS_PER_QUARTER;
    amount_in_cents %= CENTS_PER_QUARTER;
    
    int d = amount_in_cents / CENTS_PER_DIME;
    amount_in_cents %= CENTS_PER_DIME;
    
    int n = amount_in_cents / CENTS_PER_NICKEL;
    int p = amount_in_cents % CENTS_PER_NICKEL;
    
    return Coins(q, d, n, p);
}

void print_cents(int cents, std::ostream& out) {
    
    out << "$" << (cents / 100) << "." 
        << std::setfill('0') << std::setw(2) << (cents % 100);
}

Coins ask_for_coins(std::istream& in, std::ostream& out) {
    int q, d, n, p;
   
    out << "Quarters? "; in >> q;
    out << "Dimes? ";    in >> d;
    out << "Nickels? ";  in >> n;
    out << "Pennies? ";  in >> p;
    
   
    return Coins(q, d, n, p);
}

void coins_menu(std::istream& in, std::ostream& out) {
    Coins myCoins(0, 0, 0, 0);
    int choice;

    out << "Coins Menu" << endl;

    while (true) {
        out << "\n1. Deposit Change" << endl;
        out << "2. Extract Change" << endl;
        out << "3. Print Balance" << endl;
        out << "4. Exit" << endl;
        out << "\nUser Input: ";

        if (!(in >> choice)) {
            break;
        }

        if (choice == 1) {
            out << "\n";
            Coins deposit = ask_for_coins(in, out);
            myCoins.deposit_coins(deposit);
            out << "\nThank you!" << endl;
        }
        else if (choice == 2) {
            out << "\n";
            Coins needed = ask_for_coins(in, out);
            out << "\nThank you!" << endl;
            if (myCoins.has_exact_change_for_coins(needed)) {
                myCoins.extract_exact_change(needed);
            } else {
                out << "\nERROR: Insufficient Funds" << endl;
            }
        }
        else if (choice == 3) {
            out << "\n";
            print_cents(myCoins.total_value_in_cents(), out);
            out << "\n\nThank you!" << endl;
        }
        else if (choice == 4) {
            break;
        }
        else {
            out << "\nERROR: Invalid Command" << endl;
        }
    }
}