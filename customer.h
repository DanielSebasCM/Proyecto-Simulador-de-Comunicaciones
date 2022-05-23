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
  Customer(int, std::string, int, Operator*, double);
  Customer(const Customer&);
  ~Customer();

  int getId() const;
  int getAge() const;
  int getTotalSpentTalkingTime() const;
  int getTotalMessageSent() const;
  double getTotalInternetUsage() const;
  std::string getName() const;
  Operator* getOperator() const;
  Bill* getBill() const;

  void setOperator(Operator*);

  std::string toString() const;

  void talk (int, Customer&);
  void message(int, const Customer&);
  void connection(double);
  void pay(double);
};



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
#endif
