#ifndef MULTICAMNODE_H
#define MULTICAMNODE_H

#include "node/node.h"

namespace olive {

class MultiCamNode : public Node
{
  Q_OBJECT
public:
  MultiCamNode();

  NODE_DEFAULT_FUNCTIONS(MultiCamNode)

  virtual QString Name() const override;
  virtual QString id() const override;
  virtual QVector<CategoryID> Category() const override;
  virtual QString Description() const override;

  virtual ActiveElements GetActiveElementsAtTime(const QString &input, const TimeRange &r) const override;

  virtual ShaderCode GetShaderCode(const ShaderRequest &id) const override;

  virtual void Value(const NodeValueRow& value, const NodeGlobals &globals, NodeValueTable *table) const override;

  virtual void Retranslate() override;

  static const QString kCurrentInput;
  static const QString kSourcesInput;

  void SetMonitorMode(bool e) { monitor_ = e; }

  int GetSourceCount() const
  {
    return InputArraySize(kSourcesInput);
  }

  static void GetRowsAndColumns(int sources, int *rows, int *cols);
  void GetRowsAndColumns(int *rows, int *cols) const
  {
    return GetRowsAndColumns(GetSourceCount(), rows, cols);
  }

  static int RowsColsToIndex(int row, int col, int total_rows, int total_cols)
  {
    return col + row * total_cols;
  }

private:
  bool monitor_;

};

}

#endif // MULTICAMNODE_H
