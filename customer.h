// =========================================================
// File: customer.h
// Author:
// Date:
// Description:
// =========================================================
#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
#include <sstream>
#include <iomanip>
#include "bill.h"
#include "operator.h"

class Customer {
private:
  int id, age, totalSpentTalkingTime, totalMessageSent, totalInternetUsage;
  std::string name;
  Operator* op;
  Bill *bill;

public:
  Customer(){}
  Customer(int, std::string, int, Operator*, double);
  Customer(const Customer&);
//  ~Customer();

  int getId() const;
  int getAge() const;
  int getTotalSpentTalkingTime() const;
  int getTotalMessageSent() const;
  double getTotalInternetUsage() const;
  std::string getName() const;
  Operator* getOperator() const;
  Bill* getBill() const;

  void addTalkingTime(int);
  void addTotalMessageSent(int);
  void addTotalInternetUsage(double);
  void setOperator(Operator*);

  std::string toString() const;

  void talk (int, Customer&);
  void message(int, const Customer&);
  void connection(double);
//  void pay(double);
};

Customer::Customer(int id_, std::string name_, int age_, Operator* op_, double limit) {
  id = id_;
  name = name_;
  age = age_;
  op = op_;
  *bill = Bill(limit);
  totalInternetUsage = 0;
  totalMessageSent = 0;
  totalSpentTalkingTime = 0;
}

Customer::Customer(const Customer &other) {
  id = other.id;
  name = other.name;
  age = other.age;
  totalSpentTalkingTime = other.totalSpentTalkingTime;
  totalMessageSent = other.totalMessageSent;
  totalInternetUsage = other.totalInternetUsage;
  bill = other.bill;
  op = other.op;
}

std::string Customer::toString() const {
    std::ostringstream stream;

  stream << std::setprecision(2) << "Customer #" << id << " : " 
        << bill->getTotalMoneySpent() << " " << bill->getCurrentDebt() << "\n";
  std::string str = stream.str();

  return str;
}

void Customer::talk (int minutes, Customer &other) {
  double cost;
  if (minutes > 0 && other.getId() != id) {
    cost = op->calculateTalkingCost(minutes, age);
    if (bill->check(cost)) {
      bill->add(cost);
      addTalkingTime(minutes);
      other.addTalkingTime(minutes);
      op->addTalkingTime(minutes);
      other.op->addTalkingTime(minutes);
    }
  }
}
void Customer::message(int quantity, const Customer &other) {
  double cost = 0;
  if (quantity > 0 && other.getId() != id) {
    cost = op->calculateMessageCost(quantity, op->getId(), other.op->getId());
    if (bill->check(cost)) {
      bill->add(cost);
      addTotalMessageSent(quantity);
      op->addTotalMessageSent(quantity);
    }
  }
}

void Customer::connection(double ammount) {
  double cost = 0;
  if (ammount > 0) {
    cost = op->calculateNetworkCost(ammount);
    if (bill->check(cost)) {
      bill->add(cost);
      addTotalInternetUsage(ammount);
      op->addTotalInternetUsage(ammount);
    }
  }
}

int Customer::getId() const {
  return id;
}

int Customer::getAge() const {
  return age;
}

int Customer::getTotalSpentTalkingTime() const {
  return totalSpentTalkingTime;
}

int Customer::getTotalMessageSent() const {
  return totalMessageSent;
}

double Customer::getTotalInternetUsage() const {
  return totalInternetUsage;
}

std::string Customer::getName() const {
  return name;
}

Operator* Customer::getOperator() const {
  return op;
}
Bill* Customer::getBill() const {
  return bill;
}

void Customer::addTalkingTime(int minute) {
  if (minute > 0) {
    totalSpentTalkingTime += minute;
  }
}

void Customer::addTotalMessageSent(int message) {
  if (message > 0) {
    totalMessageSent += message;
  }
}

void Customer::addTotalInternetUsage(double ammount) {
  if (ammount > 0) {
    totalInternetUsage += ammount;
  }
}

void Customer::setOperator(Operator *op_) {
  op = op_;
}
#endif
