#ifndef DATABASE_H
#define DATABASE_H

#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <string>

class Database {
public:
    // Constructor
    Database(const std::string& host, const std::string& user, const std::string& password, const std::string& dbname);

    // Destructor
    ~Database();

    // Database operations
    void connect();
    void disconnect();
    void executeQuery(const std::string& query);
    sql::ResultSet* executeQueryWithResult(const std::string& query);

private:
    std::string host;
    std::string user;
    std::string password;
    std::string dbname;
    sql::mysql::MySQL_Driver* driver;
    sql::Connection* connection;
};

#endif // DATABASE_H
