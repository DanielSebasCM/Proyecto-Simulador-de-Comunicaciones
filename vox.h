// =========================================================
// File: vox.h
// Author:
// Date:
// Description:
// =========================================================

#ifndef VOXOPERATOR_H
#define VOXOPERATOR_H

#include "operator.h"

class VoxOperator : public Operator {
public:
  VoxOperator(int, double, double, double, int, OperatorType);
  VoxOperator(const VoxOperator&);

  double calculateTalkingCost(int, int);
  double calculateMessageCost(int, int, int);
  double calculateNetworkCost(double);
};

VoxOperator::VoxOperator(int i, double talking, double message, double network, int discount, OperatorType typ)
            :Operator(i, talking, message, network, discount, typ){}

VoxOperator::VoxOperator(const VoxOperator &other)
            :Operator(other){}

double VoxOperator::calculateTalkingCost(int minute, int age) {
  double cost = 0;
  if (minute > 0) {
    cost = minute * talkingCharge;
    if (age < 18 || age > 65) {
      cost *= discountRate;
    }
  }

  return cost;
}

double VoxOperator::calculateMessageCost(int quantity, int thisOpId, int otherOpId) {
  double cost = 0;
  if (quantity > 0) {
    cost = quantity * messageCost;
    if (thisOpId == otherOpId) {
      cost *= discountRate;
    }
  }

  return cost;
}

double VoxOperator::calculateNetworkCost(double ammount) {      
  double cost = 0;
  if (ammount > 0) {
    cost = ammount * networkCharge;
  }

  return cost;
}    
#endif
