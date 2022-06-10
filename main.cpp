// =========================================================
// File: main.cpp
// Author: Daniel Sebastian Cajas Morales
// Date: 23/05/2022
// Description: Implementation of main detailed in README
// =========================================================
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <vector>
#include "bill.h"
#include "operator.h"
#include "vox.h"
#include "internet.h"
#include "customer.h"

using namespace std;

int main(int argc, char* argv []) {

    ifstream inputFile;
    ofstream outputFile;

    if (argc != 3)
    {
        cout << "Uso: " << argv[0] << " Input.txt Output.txt";
        return -1;
    }

    inputFile.open(argv[1]);
    if (inputFile.fail())
    {
        cout << "No se pudo abrir el archivo de entrada.";
        return -1;
    }

    outputFile.open(argv[2]);
    if (outputFile.fail())
    {
        cout << "No se pudo abrir el archivo de salida.";
        return -1;
    }


    int C, O, N, inst, age, id_op, discount_rate, id_c1, id_c2, minutes, quantity;
    double limit, talking_charge, message_cost, network_charge, amount;
    string name;
    int type;

    inputFile >> C >> O >> N;

    vector<Customer *> customers;
    vector<Operator *> operators;

    customers.resize(C);
    operators.resize(O);

    int op_count = 0;
    int customer_count = 0;

    for (int i = 0; i < N; i++) {
        inputFile >> inst;

        switch (inst) {
            case 1: 
                inputFile >> name >> age >> id_op >> limit;
                customers.at(customer_count) =  new Customer(customer_count, name, age, operators.at(id_op), limit);
                customer_count ++;
                break;
            case 2: 
                inputFile >> type >> talking_charge >> message_cost >> network_charge >> discount_rate;
                if (type == 1) {
                  operators.at(op_count) = (new VoxOperator(op_count, talking_charge, message_cost, network_charge, discount_rate, VOX));
                  op_count ++;
                }
                else if (type == 2) {
                  operators.at(op_count) = (new InternetOperator(op_count, talking_charge, message_cost, network_charge, discount_rate, VOX));
                  op_count ++;
                }
                break;
            case 3: 
                inputFile >> id_c1 >> id_c2 >> minutes;
                (*customers.at(id_c1)).talk(minutes, *customers.at(id_c2));
                break;
            case 4: 
                inputFile >> id_c1 >> id_c2 >> quantity;
                customers.at(id_c1)->message(quantity, *customers.at(id_c2));
                break;
            case 5: 
                inputFile >> id_c1 >> amount;
                customers.at(id_c1)->connection(amount);
                break;
            case 6: 
                inputFile >> id_c1 >> amount;
                customers.at(id_c1)->pay(amount);
                break;
            case 7:
                inputFile >> id_c1 >> id_op;
                customers.at(id_c1)->setOperator(operators.at(id_op));
                break;
            case 8:
                inputFile >> id_c1 >> limit;
                customers.at(id_c1)->getBill()->changeTheLimit(limit);
            default:
                break;
        }
    }
    
    vector<Operator *>::iterator itr_op;
    for (itr_op = operators.begin(); itr_op != operators.end(); itr_op++) {

      outputFile << std::fixed << std::setprecision(2) << "Operator " << (*itr_op)->getId() << ": " << (*itr_op)->getTotalSpentTalkingTime() << " " 
                 << (*itr_op)->getTotalMessageSent() << " " << (*itr_op)->getTotalInternetUsage() << "\n";
    }

    int max_time = 0;
    int max_messages = 0;
    double max_connection = 0;
    
    int id_max_time = 0;
    int id_max_messages = 0;
    int id_max_connection = 0;
    
    vector<Customer *>::iterator itr_c;
    for (itr_c = customers.begin(); itr_c != customers.end(); itr_c++) {

      // Writes the Customers and theit total money spent, current debt 
      outputFile << std::fixed << std::setprecision(2) << "Customer " << (*itr_c)->getId() << ": " 
                 << (*itr_c)->getBill()->getTotalMoneySpent() << " " 
                 << (*itr_c)->getBill()->getCurrentDebt() << "\n";

      // Finds de customers with the most time, messages and networking used
      if ((*itr_c)->getTotalSpentTalkingTime() > max_time) {
        max_time = (*itr_c)->getTotalSpentTalkingTime();
        id_max_time = (*itr_c)->getId();
      }
      if ((*itr_c)->getTotalMessageSent() > max_messages) {
        max_messages = (*itr_c)->getTotalMessageSent();
        id_max_messages = (*itr_c)->getId();
      }
      if ((*itr_c)->getTotalInternetUsage() > max_connection) {
        max_connection = (*itr_c)->getTotalInternetUsage();
        id_max_connection = (*itr_c)->getId();
      }
    }

    // Writes the customers with most time, messages and networking used
    outputFile << std::fixed << std::setprecision(2) << customers[id_max_time]->getName() << ": " 
               << customers[id_max_time]->getTotalSpentTalkingTime() << "\n";

    outputFile << std::fixed << std::setprecision(2) << customers[id_max_messages]->getName() << ": " 
               << customers[id_max_messages]->getTotalMessageSent() << "\n";

    outputFile << std::fixed << std::setprecision(2) << customers[id_max_connection]->getName() << ": " 
               << customers[id_max_connection]->getTotalInternetUsage() << "\n";
/*  DEBUGING
    for (itr_c = customers.begin(); itr_c != customers.end(); itr_c++) {
    outputFile << std::fixed << std::setprecision(2) << (*itr_c)->getName() << ": " 
               << (*itr_c)->getTotalSpentTalkingTime() << " " 
               << (*itr_c)->getTotalMessageSent() << " " 
               << (*itr_c)->getTotalInternetUsage() << "\n";
    }
*/
    // Close files
    inputFile.close();
    outputFile.close();


    // Deconstruct customers

    for (int i = 0; i < customers.size(); ++i) {
        delete customers[i];
    }

    // Deconstruct operators
    for (int i = 0; i < operators.size(); ++i) {
        delete operators[i];
    }

    // Free memory alocated in vectors
    customers.clear();
    operators.clear();

    return 0;
}
