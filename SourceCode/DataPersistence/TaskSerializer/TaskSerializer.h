#pragma once
#include "DataPersistence/ITaskSerialzer.h"
#include <unordered_set>
#include <mutex>

class IRevelationInterface;
class IDataPersistenceInterface;
class IUtilityInterface;
class SQLiteDatabase;

class TaskSerializer : public ITaskSerializer
{
  public:
    TaskSerializer(IRevelationInterface* intf);
    ~TaskSerializer();

    virtual void RecordTask(TaskPrototype task) override;
    virtual void RemoveTask(TaskPrototype task) override;

    virtual void RetrieveTasks(std::vector<TaskPrototype>& tasks) override;
    virtual void RetrieveTasks(std::vector<TaskPrototype>& tasks, const std::string& date) override;
    virtual void RetrieveTasks(std::vector<TaskPrototype>& tasks, const std::string& from, const std::string& to) override;

    void PrepareDatabaseForToday();

  private:
    void Initialize();
    void Uninitialize();

    void CollectTasks();
    void CollectRoutineTasks(std::unordered_set<TaskRoutine>& routines);
    void CollectMostRecentTasks(std::vector<TaskPrototype>& tasks);

  private:
    IRevelationInterface*      m_interface           = nullptr;
    IDataPersistenceInterface* m_dataPersistenceIntf = nullptr;
    IUtilityInterface*         m_utilityIntf         = nullptr;

    SQLiteDatabase* m_database = nullptr;
    std::mutex      m_insertMutex;
};
