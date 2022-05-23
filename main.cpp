// =========================================================
// File: main.cpp
// Author:
// Date:
// Description:
// To compile: g++ -std=c++11 main.cpp -o app
// To execute: ./app input_file output_file
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

    Customer customers[C];
    Operator operators[O];

    int op_count = 0;
    int customer_count = 0;

    for (int i = 0; i < N; i++) {
        inputFile >> inst;

        switch (inst) {
            case 1: 
                inputFile >> name >> age >> id_op >> limit;
                customers[customer_count] = Customer(customer_count, name, age, &operators[id_op], limit);
                customer_count ++;
                break;
            case 2: 
                inputFile >> type >> talking_charge >> message_cost >> network_charge >> discount_rate;
                if (type == 1) {
                  operators[op_count] = VoxOperator(op_count, talking_charge, message_cost, network_charge, discount_rate, VOX);
                  op_count ++;
                }
                else if (type == 2) {
                  operators[op_count] = InternetOperator(op_count, talking_charge, message_cost, network_charge, discount_rate, INTERNET);
                  op_count ++;
                }
                break;
            case 3: 
                inputFile >> id_c1 >> id_c2 >> minutes;
                customers[id_c1].talk(minutes, customers[id_c2]);
                break;
            case 4: 
                inputFile >> id_c1 >> id_c2 >> quantity;
                customers[id_c1].message(quantity, customers[id_c2]);
                break;
            case 5: 
                inputFile >> id_c1 >> amount;
                customers[id_c1].connection(amount);
                break;
            case 6: 
                inputFile >> id_c1 >> amount;
                customers[id_c1].getBill()->pay(amount);
                break;
            case 7:
                inputFile >> id_c1 >> id_op;
                customers[id_c1].setOperator(&operators[id_op]);
                break;
            case 8:
                inputFile >> id_c1 >> limit;
                customers[id_c1].getBill()->changeTheLimit(limit);
            default:
                break;
        }
    }

    for (int i = 0; i < op_count; i++) {

      outputFile << std::fixed << std::setprecision(2) << "Operator " << i << ": " << operators[i].getTotalSpentTalkingTime() << " " 
                 << operators[i].getTotalMessageSent() << " " << operators[i].getTotalInternetUsage() << "\n";
    }

    int max_time = 0;
    int max_messages = 0;
    double max_connection = 0;
    int id_max_time = 0;
    int id_max_messages = 0;
    int id_max_connection = 0;
    
    
    for (int i = 0; i < customer_count; i++) {

      outputFile << std::fixed << std::setprecision(2) << "Customer " << i << ": " 
                 << customers[i].getBill()->getTotalMoneySpent() << " " 
                 << customers[i].getBill()->getCurrentDebt() << "\n";

      if (customers[i].getTotalSpentTalkingTime() > max_time) {
        max_time = customers[i].getTotalSpentTalkingTime();
        id_max_time = i;
      }
      if (customers[i].getTotalMessageSent() > max_messages) {
        max_messages = customers[i].getTotalMessageSent();
        id_max_messages = i;
      }
      if (customers[i].getTotalInternetUsage() > max_connection) {
        max_connection = customers[i].getTotalInternetUsage();
        id_max_connection = i;
      }
    }

    outputFile << std::fixed << std::setprecision(2) << customers[id_max_time].getName() << ": " 
               << customers[id_max_time].getTotalSpentTalkingTime() << "\n";

    outputFile << std::fixed << std::setprecision(2) << customers[id_max_messages].getName() << ": " 
               << customers[id_max_messages].getTotalMessageSent() << "\n";

    outputFile << std::fixed << std::setprecision(2) << customers[id_max_connection].getName() << ": " 
               << customers[id_max_connection].getTotalInternetUsage() << "\n";


    inputFile.close();
    outputFile.close();


    return 0;
}
