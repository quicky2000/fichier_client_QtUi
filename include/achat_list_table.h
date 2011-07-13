#ifndef ACHAT_LIST_TABLE_H
#define ACHAT_LIST_TABLE_H

#include "search_achat_item.h"

#include <QTableWidget>
#include <vector>

class achat_list_table: public QTableWidget
{
  Q_OBJECT
 public:
  achat_list_table(QWidget *parent);
  void update(const std::vector<search_achat_item> & p_achat_list);
  uint32_t get_selected_achat_id(uint32_t p_row)const;
 private:
  void set_row_content(uint32_t p_row,const search_achat_item & p_achat_item);
};

#endif
