#include "keyframeviewitem.h"

#include <QApplication>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QWidget>

#include "common/qtversionabstraction.h"

KeyframeViewItem::KeyframeViewItem(NodeKeyframePtr key, qreal vcenter, QGraphicsItem *parent) :
  QGraphicsRectItem(parent),
  key_(key),
  scale_(1.0),
  middle_(vcenter)
{
  keyframe_size_ = QFontMetricsWidth(qApp->fontMetrics(), "Oi");
  setFlag(QGraphicsItem::ItemIsSelectable);
  setFlag(QGraphicsItem::ItemIsMovable);

  connect(key.get(), SIGNAL(TimeChanged(const rational&)), this, SLOT(UpdateRect()));

  UpdateRect();
}

void KeyframeViewItem::SetScale(double scale)
{
  scale_ = scale;
  UpdateRect();
}

void KeyframeViewItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
  painter->setPen(Qt::black);

  if (option->state & QStyle::State_Selected) {
    painter->setBrush(widget->palette().highlight());
  } else {
    painter->setBrush(widget->palette().text());
  }

  switch (key_->type()) {
  case NodeKeyframe::kLinear:
  {
    QPointF points[] = {
      QPointF(rect().center().x(), rect().top()),
      QPointF(rect().right(), rect().center().y()),
      QPointF(rect().center().x(), rect().bottom()),
      QPointF(rect().left(), rect().center().y())
    };

    painter->drawPolygon(points, 4);
    break;
  }
  case NodeKeyframe::kBezier:
    painter->drawEllipse(rect());
    break;
  case NodeKeyframe::kHold:
    painter->drawRect(rect());
    break;
  }
}

void KeyframeViewItem::UpdateRect()
{
  double x_center = key_->time().toDouble() * scale_;

  setRect(x_center - keyframe_size_/2, middle_ - keyframe_size_/2, keyframe_size_, keyframe_size_);
}