#ifndef CONNECTION_HPP
#define CONNECTION_HPP

#include "PreparedStatement.hpp"

namespace SQLite
{
    class Connection
    {
        public:
            Connection();
            Connection(Connection&& other);
            ~Connection();

            Connection& operator=(Connection&& other);

            void Close();

            PreparedStatement Prepare(const char* sql);

            bool IsOpen() const;

        private:
            Connection(const Connection&) = delete;
            Connection& operator=(const Connection&) = delete;

            sqlite3* _connection;
            PreparedStatement* _firstStatement;
    };
}

#endif
