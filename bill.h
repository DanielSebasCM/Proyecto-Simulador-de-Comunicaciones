// =========================================================
// File: bill.h
// Author: Danel Sebastian Cajas Morales
// Date: 23/05/2022
// Description: Reperesenta las facturas generadas con las transacciones entre 
// clientes y operadores
// =========================================================

#ifndef BILL_H
#define BILL_H
#include <iostream>
class Bill {
private:
  double limitAmount, currentDebt, totalMoneySpent;

public:
  Bill();
  Bill(double);
  Bill(const Bill&);

  double getLimitAmount() const;
  double getCurrentDebt() const;
  double getTotalMoneySpent() const;

  void add(double);
  void pay(double);
  void changeTheLimit(double);
  bool check(double) const;
};

Bill::Bill() {
  limitAmount = 0;
  currentDebt = 0;
  totalMoneySpent = 0;
}

Bill::Bill(double limit) {
  if (limit <= 0 ) {
    limit = 0;
  }
  limitAmount = limit;
  currentDebt = 0;
  totalMoneySpent = 0;
}

Bill::Bill(const Bill &other) {
  limitAmount = other.limitAmount;
  currentDebt = other.currentDebt;
  totalMoneySpent = other.totalMoneySpent;
}

double Bill::getLimitAmount() const {
  return limitAmount;
}

double Bill::getCurrentDebt() const {
  return currentDebt;
}

double Bill::getTotalMoneySpent() const {
  return totalMoneySpent;
}

void Bill::add(double amount) {
  if (amount > 0) {
    currentDebt += amount;
  }  
}

void Bill::pay(double amount) {
  if (amount > 0) {
    if (amount > currentDebt) {
      //std::cout << "Pay Ammount " << amount << " higher than debt, paying " << currentDebt <<"\n";
      amount = currentDebt;
    }
    totalMoneySpent += amount;
    currentDebt -= amount;
  }
  /*
  else { 
    std::cout << "Pay Ammount " << amount << " lower than zero\n";
  }
  */
}

void Bill::changeTheLimit(double ammount) {
  if (!(ammount <= 0 || ammount <= currentDebt)) {
    limitAmount = ammount;
  }
}

bool Bill::check(double amount) const {
  /*
  if (!((currentDebt + amount) <= limitAmount)) {
    std::cout << " Check Ammount " << amount << " Current debt " << currentDebt 
              << " higher than limit " << limitAmount << "\n";
  }
  */
  return (currentDebt + amount) <= limitAmount;
}
#endif