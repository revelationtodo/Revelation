#pragma once
#include "RevelationSidebar.h"
#include "ui_RevelationRightSidebar.h"
#include "IRevelationDataDefine.h"

class IDateTimeFormatter;
class RevelationRightSidebar : public RevelationSidebar
{
    Q_OBJECT

  public:
    RevelationRightSidebar(IRevelationInterface* intf, QWidget* parent = nullptr);
    ~RevelationRightSidebar();

  private:
    void Initialize();
    void InitWidget();
    void InitSignalSlots();

    virtual void showEvent(QShowEvent* event) override;
    virtual void hideEvent(QHideEvent* event) override;
    virtual void closeEvent(QCloseEvent* event) override;

    void SetBtnAddToRoutineState(bool isRoutine);

    void UpdateUI(const TaskPrototype& task);
    void UpdateUI(const TaskRoutine& routine);

  signals:
    void TaskItemEdited(const TaskPrototype& task);
    void TaskItemDeleted(const TaskPrototype& task);

    void RoutineAdded(const TaskRoutine& routine);
    void RoutineEdited(const TaskRoutine& routine);
    void RoutineDeleted(const TaskRoutine& routine);

  public slots:
    void OnThemeChanged();

    void OnTaskReparenting(const TaskPrototype& task);
    void OnTaskItemSelected(const TaskPrototype& task);
    void OnTaskItemEdited();

    void OnTaskRoutineAttached(const TaskRoutine& routine);

    void OnBtnAddToRoutineClicled();
    void OnBtnDeleteTaskItemClicked();
    void OnCbTypeIndexChanged(int index);
    void OnStartDateSelected(QDate date);
    void OnFinishDateSelected(QDate date);
    void OnDeadlineDateSelected(QDate date);
    void OnStartTimeSelected(QTime time);
    void OnFinishTimeSelected(QTime time);
    void OnDeadlineTimeSelected(QTime time);

    void OnCbRepeatIndexChanged(int index);

  private:
    void BlockSignals(bool block);

  private:
    Ui::RevelationRightSidebarClass ui;
    IRevelationInterface*           m_interface     = nullptr;
    IDateTimeFormatter*             m_timeFormatter = nullptr;

    TaskPrototype m_task;
    bool          m_taskValid = false;

    TaskRoutine m_routine;
    bool        m_routineValid = false;
};
