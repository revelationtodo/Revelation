#include "DataPersistenceInterface.h"
#include "TaskSerializer/TaskSerializer.h"
#include "RoutineSerializer/RoutineSerializer.h"

DataPersistenceInterface::DataPersistenceInterface(IRevelationInterface* intf)
    : m_interface(intf)
{
}

DataPersistenceInterface::~DataPersistenceInterface()
{
    delete m_taskSerialzier;
    delete m_routineSerializer;
}

void DataPersistenceInterface::Initialize()
{
}

void DataPersistenceInterface::Uninitialize()
{
}

ITaskSerializer* DataPersistenceInterface::GetTaskSerializer()
{
    if (nullptr == m_taskSerialzier)
    {
        m_taskSerialzier = new TaskSerializer(m_interface);
    }
    return m_taskSerialzier;
}

IRoutineSerialzer* DataPersistenceInterface::GetRoutineSerializer()
{
    if (nullptr == m_routineSerializer)
    {
        m_routineSerializer = new RoutineSerializer(m_interface);
    }
    return m_routineSerializer;
}

bool DataPersistenceInterface::RegisterDatabase(DatabaseRole role, IDatabase* database)
{
    if (nullptr == database)
    {
        return false;
    }

    m_databases[role] = database;
    m_interface->Broadcast(BroadcastType::DatabaseCreated, database);
    return true;
}

IDatabase* DataPersistenceInterface::GetDatabase(DatabaseRole role)
{
    auto finder = m_databases.find(role);
    if (finder == m_databases.end())
    {
        return nullptr;
    }

    return finder->second;
}
