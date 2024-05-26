#include "Database.h"

// Constructor
Database::Database(const std::string& host, const std::string& user, const std::string& password, const std::string& dbname)
        : host(host), user(user), password(password), dbname(dbname), driver(nullptr), connection(nullptr) {}

// Destructor
Database::~Database() {
    disconnect();
}

// Connect to the database
void Database::connect() {
    driver = sql::mysql::get_mysql_driver_instance();
    connection = driver->connect(host, user, password);
    connection->setSchema(dbname);
}

// Disconnect from the database
void Database::disconnect() {
    if (connection) {
        delete connection;
        connection = nullptr;
    }
}

// Execute a query without expecting a result
void Database::executeQuery(const std::string& query) {
    sql::Statement* stmt = connection->createStatement();
    stmt->execute(query);
    delete stmt;
}

// Execute a query and return the result set
sql::ResultSet* Database::executeQueryWithResult(const std::string& query) {
    sql::Statement* stmt = connection->createStatement();
    sql::ResultSet* res = stmt->executeQuery(query);
    delete stmt;
    return res;
}
