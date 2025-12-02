#include "RevelationListDelegate.h"
#include "RevelationListItem.h"
#include "RevelationListModel.h"
#include <QPainter>

RevelationListDelegate::RevelationListDelegate(IRevelationInterface* intf, QObject* parent /*= nullptr*/)
    : m_interface(intf), QStyledItemDelegate(parent)
{
}

RevelationListDelegate::~RevelationListDelegate()
{
}

void RevelationListDelegate::SetMouseHoverRow(int hoverRow)
{
    m_hoverRow = hoverRow;
}

void RevelationListDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    int                  taskIndex = (int)index.internalPointer();
    RevelationListModel* model     = (RevelationListModel*)index.model();
    if (taskIndex >= model->m_tasks.size())
    {
        return;
    }

    TaskPrototype task = model->m_tasks.at(taskIndex);

    QStyleOptionViewItem opt = option;
    opt.rect.adjust(2, 1, -2, -1);

    qreal devicePixelRatio = painter->device()->devicePixelRatio();

    RevelationListItem widget;
    widget.SetTaskData(task);
    widget.resize(opt.rect.size());
    widget.SetMouseHoverd(index.row() == m_hoverRow);
    widget.setGeometry(QRect(QPoint(), opt.rect.size()));

    QSize   ssize = opt.rect.size() * devicePixelRatio;
    QPixmap pm(ssize);
    pm.setDevicePixelRatio(devicePixelRatio);
    pm.fill(Qt::transparent);

    widget.render(&pm);
    painter->drawPixmap(opt.rect.topLeft(), pm);
}

QSize RevelationListDelegate::sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    QSize preffered = QStyledItemDelegate::sizeHint(option, index);
    int   width     = preffered.width();
    int   height    = 60;
    return QSize(width, height);
}
