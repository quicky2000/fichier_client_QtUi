#ifndef FACTURE_LIST_TABLE_H
#define FACTURE_LIST_TABLE_H

#include "search_facture_item.h"

#include <QTableWidget>
#include <vector>

class facture_list_table: public QTableWidget
{
  Q_OBJECT
 public:
  facture_list_table(QWidget *parent);
  void update(std::vector<search_facture_item> p_item_list);
  uint32_t get_selected_facture_item_id(uint32_t p_row)const;
 private:
  void set_row_content(uint32_t p_row,const search_facture_item & p_item);
};

#endif
