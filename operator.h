// =========================================================
// File: operator.h
// Author: Daniel Sebastian Cajas Morales
// Date: 23/05/2022
// Description: Implementation of operator detailed in README
// =========================================================

#ifndef OPERATOR_H
#define OPERATOR_H

#include <string>
#include <sstream>
#include <iomanip>

typedef enum{VOX, INTERNET} OperatorType;

class Operator {
protected:
  int id, discountRate;
  double talkingCharge, messageCost, networkCharge, totalInternetUsage;
  int totalSpentTalkingTime, totalMessageSent;
  OperatorType type;

public:
  Operator();
  Operator(int, double, double, double, int, OperatorType);
  Operator(const Operator&);

  int getId() const;
  int getDiscountRate() const;
  double getTalkingChage() const;
  double getMessageCost() const;
  double getNetworkCharge() const;
  int getTotalSpentTalkingTime() const;
  int getTotalMessageSent() const;
  double getTotalInternetUsage() const;
  OperatorType getType() const;

  void addTalkingTime(int);
  void addTotalMessageSent(int);
  void addTotalInternetUsage(double);

  std::string toString() const;

  virtual double calculateTalkingCost(int, int){return 0;}
  virtual double calculateMessageCost(int, int, int){return 0;}
  virtual double calculateNetworkCost(double){return 0;}
};

Operator::Operator(){
  id = -1;
}

Operator::Operator(int i, double talking, double message, double network, int discount, OperatorType typ) {
  id = i;
  talkingCharge = talking;
  messageCost = message;
  networkCharge = network;
  discountRate = discount;
  type = typ;
  totalSpentTalkingTime = 0;
  totalMessageSent = 0;
  totalInternetUsage = 0;
}

Operator::Operator(const Operator &other) {
  id = other.id;
  talkingCharge = other.talkingCharge;
  messageCost = other.messageCost;
  networkCharge = other.networkCharge;
  discountRate = other.discountRate;
  type = other.type;
  totalSpentTalkingTime = other.totalSpentTalkingTime;
  totalMessageSent = other.totalMessageSent;
  totalInternetUsage = other.totalInternetUsage;
}

void Operator::addTalkingTime(int minute) {
  if (minute > 0) {
    totalSpentTalkingTime += minute;
  }
}

void Operator::addTotalMessageSent(int message) {
  if (message > 0) {
    totalMessageSent += message;
  }
}

void Operator::addTotalInternetUsage(double ammount) {
  if (ammount > 0) {
    totalInternetUsage += ammount;
  }
}

std::string Operator::toString() const {
  std::ostringstream stream;

  stream << std::fixed << std::setprecision(2) << "Operator #" << id << " : " << totalSpentTalkingTime << " " 
      << totalMessageSent << " " << totalInternetUsage << "\n";
  std::string str = stream.str();

  return str;
}

  int Operator::getId() const {
    return id;
  }

  int Operator::getDiscountRate() const {
    return discountRate;
  }

  double Operator::getTalkingChage() const {
    return talkingCharge;
  }

  double Operator::getMessageCost() const {
    return messageCost;
  }

  double Operator::getNetworkCharge() const {
    return networkCharge;
  }

  int Operator::getTotalSpentTalkingTime() const {
    return totalSpentTalkingTime;
  }

  int Operator::getTotalMessageSent() const {
    return totalMessageSent;
  }

  double Operator::getTotalInternetUsage() const {
    return totalInternetUsage;
  }

  OperatorType Operator::getType() const {
    return type;
  }
#endif