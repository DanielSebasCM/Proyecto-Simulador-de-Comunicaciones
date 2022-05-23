// =========================================================
// File: vox.h
// Author:
// Date:
// Description:
// =========================================================

#ifndef InternetOperator_H
#define InternetOperator_H

#include "operator.h"

class InternetOperator : public Operator {
private:
  const double LIMITGB = 10.0;

public:
  InternetOperator(int, double, double, double, int, OperatorType);
  InternetOperator(const InternetOperator&);

  double calculateTalkingCost(int, int);
  double calculateMessageCost(int, int, int);
  double calculateNetworkCost(double);
};

InternetOperator::InternetOperator(int i, double talking, double message, double network, int discount, OperatorType typ)
            :Operator(i, talking, message, network, discount, typ){}

InternetOperator::InternetOperator(const InternetOperator &other)
            :Operator(other){}

double InternetOperator::calculateTalkingCost(int minute, int age) {
  double cost = 0;
  if (minute > 0 && age > 0) {
    cost = minute * talkingCharge;
    if (minute < 2) {
      cost -= cost  *  discountRate/100;
    }
  }

  return cost;
}

double InternetOperator::calculateMessageCost(int quantity, int thisOpId, int otherOpId) {
  double cost = 0;
  if (quantity > 0) {
    cost = quantity * messageCost;
    if (quantity < 3) {
      cost -= cost  *  discountRate/100;
    }
  }

  return cost;
}

double InternetOperator::calculateNetworkCost(double ammount) {      
  double cost = 0;
  if (ammount + totalInternetUsage > LIMITGB) {
    cost = ammount * networkCharge;
  }

  return cost;
}    

#endif
