// defines data prototypes
#pragma once
#include <string>
#include <vector>
#include <ctime>

using Int64  = int64_t;
using Uint64 = uint64_t;

enum class TaskStatus
{
    None = 0,
    Todo,
    Doing,
    Testing,
    Done
};

enum class TaskType
{
    None = 0,
    Bug,
    Feature,
    Test,
    UI
};

enum class TaskTag
{
    None = 0,
    Routine,
    Inherited
};

struct TaskPrototype
{
    Uint64      m_id;
    std::string m_title;
    std::string m_desc;
    std::string m_createTime;
    std::string m_startTime;
    std::string m_finishTime;
    std::string m_deadline;
    TaskStatus  m_taskStatus;
    TaskType    m_taskType;
    TaskTag     m_taskTag;

    bool operator==(const TaskPrototype& other) const
    {
        return this->m_id == other.m_id;
    }

    bool operator!=(const TaskPrototype& other) const
    {
        return this->m_id != other.m_id;
    }
};

using DateToTasks = std::pair<std::string, std::vector<TaskPrototype>>;

enum class TaskRepeatType
{
    None = 0,
    Daily,
    Weekly,
    Monthly,
    Yearly,
    WeekDay,
    Weekend,
};

struct TaskRoutine
{
    Uint64         m_id;
    std::string    m_createTime;
    TaskRepeatType m_repeatType;

    std::string m_taskTitle;
    std::string m_taskDesc;

    bool operator==(const TaskRoutine& other) const
    {
        return this->m_id == other.m_id;
    }

    bool operator!=(const TaskRoutine& other) const
    {
        return this->m_id != other.m_id;
    }

    bool IsRoutineDay(time_t today, time_t fromDay)
    {
        tm tToday, tFrom{};
        localtime_s(&tToday, &today);
        localtime_s(&tFrom, &fromDay);

        int daysDiff = int(std::difftime(today, fromDay) / 86400);

        switch (m_repeatType)
        {
            case TaskRepeatType::None:
                return false;

            case TaskRepeatType::Daily:
                return daysDiff >= 0;

            case TaskRepeatType::Weekly:
                return daysDiff >= 0 && (daysDiff % 7 == 0);

            case TaskRepeatType::Monthly:
                return tToday.tm_mday == tFrom.tm_mday &&
                       (tToday.tm_year > tFrom.tm_year ||
                        (tToday.tm_year == tFrom.tm_year && tToday.tm_mon >= tFrom.tm_mon));

            case TaskRepeatType::Yearly:
                return tToday.tm_mon == tFrom.tm_mon &&
                       tToday.tm_mday == tFrom.tm_mday &&
                       tToday.tm_year >= tFrom.tm_year;

            case TaskRepeatType::WeekDay:
                return tToday.tm_wday >= 1 && tToday.tm_wday <= 5;

            case TaskRepeatType::Weekend:
                return tToday.tm_wday == 0 || tToday.tm_wday == 6;

            default:
                return false;
        }
    }

    TaskPrototype ConvertToTask()
    {
        TaskPrototype task;
        task.m_id         = m_id;
        task.m_createTime = m_createTime;
        task.m_title      = m_taskTitle;
        task.m_desc       = m_taskDesc;
        task.m_taskTag    = TaskTag::Routine;
        // TODO:
        // task.m_deadline
        return task;
    }
};

template <>
struct std::hash<TaskRoutine>
{
    std::size_t operator()(const TaskRoutine& r) const noexcept
    {
        return std::hash<uint64_t>()(r.m_id);
    }
};