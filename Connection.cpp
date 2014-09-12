#include "Connection.hpp"
#include <new>
#include <utility>

namespace SQLite
{
    Connection::Connection()
        : _connection(nullptr)
        , _firstStatement(nullptr)
    {
    }

    Connection::Connection(Connection&& other)
        : _connection(other._connection)
        , _firstStatement(other._firstStatement)
    {
        other._connection = nullptr;
        other._firstStatement = nullptr;

        if (_firstStatement)
            _firstStatement->_previousPointer = &_firstStatement;
    }

    Connection::~Connection()
    {
        Close();
    }

    Connection& Connection::operator=(Connection&& other)
    {
        if (this != &other)
        {
            this->~Connection();
            new (this) Connection(std::move(other));
        }

        return *this;
    }

    void Connection::Close()
    {
        while (_firstStatement) _firstStatement->Finalize();

        sqlite3_close(_connection);
        _connection = nullptr;
    }

    PreparedStatement Connection::Prepare(const char* sql)
    {
        PreparedStatement result;

        if (_connection)
        {
            sqlite3_prepare(_connection, sql, -1, &result._statement, nullptr);

            if (_firstStatement)
            {
                result._nextStatement = _firstStatement;
                _firstStatement->_previousPointer = &result._nextStatement;
            }

            _firstStatement = &result;
        }

        return result;
    }

    bool Connection::IsOpen() const
    {
        return _connection;
    }
}
