#ifndef PREPAREDSTATEMENT_HPP
#define PREPAREDSTATEMENT_HPP

#include "sqlite3.h"

namespace SQLite
{
    class PreparedStatement
    {
        public:
            PreparedStatement();
            PreparedStatement(PreparedStatement&& other);
            ~PreparedStatement();

            PreparedStatement& operator=(PreparedStatement&& other);

            void Finalize();

        private:
            PreparedStatement(const PreparedStatement&) = delete;
            PreparedStatement& operator=(const PreparedStatement&) = delete;

            sqlite3_stmt* _statement;
            PreparedStatement** _previousPointer;
            PreparedStatement* _nextStatement;

            friend class Connection;
    };
}

#endif
