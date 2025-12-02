#include "SQLiteDatabase.h"
#include "SQLiteLink.h"

SQLiteDatabase::SQLiteDatabase()
{
}

SQLiteDatabase::~SQLiteDatabase()
{
    Close();
}

bool SQLiteDatabase::Open(const std::u8string& databasePath)
{
    const char* path = reinterpret_cast<const char*>(databasePath.c_str());

    int rc = sqlite3_open(path, &m_database);
    return rc == SQLITE_OK;
}

void SQLiteDatabase::Close()
{
    if (nullptr != m_database)
    {
        sqlite3_close(m_database);
    }
}

DisposableLink SQLiteDatabase::GetDisposableLink()
{
    auto link = std::make_shared<SQLiteLink>(this);
    return std::static_pointer_cast<IDatabaseLink>(link);
}

sqlite3* SQLiteDatabase::GetDatabase()
{
    return m_database;
}
