#ifndef FACTURE_REASON_LIST_TABLE_H
#define FACTURE_REASON_LIST_TABLE_H

#include "facture_reason.h"
#include <QTableWidget>
#include <vector>

class facture_reason_list_table: public QTableWidget
{
  Q_OBJECT
 public:
  facture_reason_list_table(QWidget *parent);
  void update(std::vector<facture_reason> & p_client_list);
  uint32_t get_selected_facture_reason_id(uint32_t p_row)const;
 private:
  void set_row_content(uint32_t p_row,const facture_reason & p_facture_reason_item);
};

#endif
