#ifndef SIMPLE_TABLE_CELL_H
#define SIMPLE_TABLE_CELL_H

#include <QTableWidgetItem>
#include <stdint.h>

class simple_table_cell: public QTableWidgetItem
{
 public:
  simple_table_cell(const QString & p_text,uint32_t p_id=0);
  uint32_t get_id(void)const;
  void set_warning_background(void);
 private:
  uint32_t m_id;
};

#endif
