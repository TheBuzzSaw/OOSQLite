#include "PreparedStatement.hpp"
#include <new>
#include <utility>

namespace SQLite
{
    PreparedStatement::PreparedStatement()
        : _statement(nullptr)
        , _previousPointer(nullptr)
        , _nextStatement(nullptr)
    {
    }

    PreparedStatement::PreparedStatement(PreparedStatement&& other)
        : _statement(other._statement)
        , _previousPointer(other._previousPointer)
        , _nextStatement(other._nextStatement)
    {
        other._statement = nullptr;
        other._previousPointer = nullptr;
        other._nextStatement = nullptr;

        if (_statement)
        {
            *_previousPointer = this;

            if (_nextStatement)
                _nextStatement->_previousPointer = &_nextStatement;
        }
    }

    PreparedStatement::~PreparedStatement()
    {
        Finalize();
    }

    PreparedStatement& PreparedStatement::operator=(PreparedStatement&& other)
    {
        if (this != &other)
        {
            this->~PreparedStatement();
            new (this) PreparedStatement(std::move(other));
        }

        return *this;
    }

    void PreparedStatement::Finalize()
    {
        if (_statement)
        {
            *_previousPointer = _nextStatement;

            if (_nextStatement)
                _nextStatement->_previousPointer = _previousPointer;

            sqlite3_finalize(_statement);
            _statement = nullptr;
        }
    }
}
