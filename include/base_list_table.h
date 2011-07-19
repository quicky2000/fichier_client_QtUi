#ifndef BASE_LIST_TABLE_H
#define BASE_LIST_TABLE_H

#include <QTableWidget>
#include <stdint.h>

class base_list_table: public QTableWidget
{
  Q_OBJECT
 public:
  base_list_table(const std::string & p_name,QWidget *parent);
  uint32_t get_selected_item_id(uint32_t p_row)const;
 private:
};

#endif
