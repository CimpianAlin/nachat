#include "WrappingTextEdit.hpp"

#include <QDebug>
#include <QAbstractTextDocumentLayout>

WrappingTextEdit::WrappingTextEdit(QWidget *parent) : QTextEdit(parent) {
  connect(document()->documentLayout(), &QAbstractTextDocumentLayout::documentSizeChanged,
          this, &WrappingTextEdit::document_size_changed);
  QSizePolicy policy(QSizePolicy::Ignored, QSizePolicy::Expanding);
  policy.setHorizontalStretch(1);
  policy.setVerticalStretch(1);
  setSizePolicy(policy);
  setAcceptRichText(false);
}

QSize WrappingTextEdit::sizeHint() const {
  auto margins = contentsMargins();
  QSize size = document()->size().toSize();
  size.rwidth() += margins.left() + margins.right();
  size.rheight() += margins.top() + margins.bottom();

  return size;
}

QSize WrappingTextEdit::minimumSizeHint() const {
  auto margins = contentsMargins();
  return QSize(fontMetrics().averageCharWidth(), fontMetrics().lineSpacing() + margins.top() + margins.bottom());
}

void WrappingTextEdit::document_size_changed(const QSizeF &size) {
  auto margins = contentsMargins();
  // FIXME: Should be able to rely on sizeHint and QSizePolicy::Preferred
  setMaximumHeight(size.height() + margins.top() + margins.bottom());
  updateGeometry();
}
