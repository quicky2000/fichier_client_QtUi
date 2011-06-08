#include "simple_table_cell.h"

simple_table_cell::simple_table_cell(const QString & p_text,uint32_t p_id):
  QTableWidgetItem(p_text),
  m_id(p_id)
{
  setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
}

uint32_t simple_table_cell::get_id(void)const
{
  return m_id;
}

void simple_table_cell::set_warning_background(void)
{
  this->setBackground(QBrush(QColor(255,128,0)));
}

//EOF
