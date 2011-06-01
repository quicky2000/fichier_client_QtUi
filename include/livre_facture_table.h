#ifndef LIVRE_FACTURE_TABLE_H
#define LIVRE_FACTURE_TABLE_H

#include "livre_facture.h"

#include <QTableWidget>
#include <vector>

class livre_facture_table: public QTableWidget
{
  Q_OBJECT
 public:
  livre_facture_table(QWidget *parent);
  void update(std::vector<livre_facture> p_livre_facture_list);
  uint32_t get_selected_livre_facture_id(uint32_t p_row)const;
 private:
  void set_row_content(uint32_t p_row,const livre_facture & p_livre_facture_item);
};

#endif
