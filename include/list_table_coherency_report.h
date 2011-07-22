#ifndef _LIST_TABLE_COHERENCY_REPORT_H_
#define _LIST_TABLE_COHERENCY_REPORT_H_

#include <QTableWidget>
#include <vector>
#include "coherency_report_item.h"

class list_table_coherency_report: public QTableWidget
{
 public:
  list_table_coherency_report(QWidget *parent);
  void update(std::vector<coherency_report_item> & p_list);
  uint32_t get_selected_item_id(void)const;
 private:
  void set_row_content(uint32_t p_row,const coherency_report_item & p_item);
};

#endif
