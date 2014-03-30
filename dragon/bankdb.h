#ifndef BANKDB_H
#define BANKDB_H
#include<QString>
#include "database.h"


struct Location {
    int ID;
    QString zipCode;
    QString city;
    QString strit;
};

struct Shop {
    QString name;
    Location location;
    QString NIP;
    QString branch;
};

struct Subject {
    int ID;
    QString name;
    uint number;
    float price;
    float unitPrice;
};

struct Account {
    int ID;
    QString name;
    QString number;
    float value;
};

struct Transaction {
    Shop shop;
    Location location;
    Account account;
    Subject * subiect;
};

class BankDB : public Database
{
public:
    BankDB();
    ~BankDB();
    bool createTable();
    bool addSubject(Subject subiect);
    bool addAccount(Account account);
    bool addLocation(Location location);
    bool addTransaction(Transaction transaction);

    bool selectAccount();
};

#endif // BANKDB_H
