#include "achat_list_table.h"
#include "simple_table_cell.h"
#include "fichier_client_QtUi_utils.h"
#include <vector>
#include <assert.h>

using namespace std;

achat_list_table::achat_list_table(QWidget *parent):
  QTableWidget(0,9,parent)
{
  QStringList l_h_header_list;
  l_h_header_list << tr("Id") << tr("Date") << tr("Marque") << tr("Type")  << tr("Reference")  << tr("Prix Euro")  << tr("Prix Franc") << tr("Garantie") << tr("Livre Facture");
  setHorizontalHeaderLabels(l_h_header_list);
  setSelectionBehavior(QAbstractItemView::SelectRows);
  setSelectionMode(QAbstractItemView::SingleSelection);
  setItemPrototype(new simple_table_cell(""));
  setColumnHidden(0,true);
  setColumnHidden(8,true);
}

uint32_t achat_list_table::get_selected_achat_id(uint32_t p_row)const
{
  assert(p_row < ((uint32_t)rowCount()));
  return static_cast<simple_table_cell*>(item(p_row,0))->get_id();
}

void achat_list_table::set_row_content(uint32_t p_row,const search_achat_item & p_achat_item)
{
      QString l_id_q;
      l_id_q.setNum(p_achat_item.get_id());
      setItem(p_row,0,new simple_table_cell(l_id_q,p_achat_item.get_id()));
      setItem(p_row,1,new simple_table_cell(fichier_client_QtUi_utils::get_human_date(p_achat_item.get_date()).c_str()));
      setItem(p_row,2,new simple_table_cell(p_achat_item.get_marque().c_str()));
      setItem(p_row,3,new simple_table_cell(p_achat_item.get_type().c_str()));
      setItem(p_row,4,new simple_table_cell(p_achat_item.get_reference().c_str()));
      setItem(p_row,5,new simple_table_cell(p_achat_item.get_prix_euro().c_str()));
      setItem(p_row,6,new simple_table_cell(p_achat_item.get_prix_franc().c_str()));
      setItem(p_row,7,new simple_table_cell(p_achat_item.get_garantie().c_str()));
      QString l_livre_facture_id;
      l_id_q.setNum(p_achat_item.get_livre_facture_id());
      setItem(p_row,8,new simple_table_cell(l_livre_facture_id));
 }

void achat_list_table::update(std::vector<search_achat_item> & p_achat_list)
{
  clearContents();
  setRowCount(p_achat_list.size());
  vector<search_achat_item>::const_iterator l_iter = p_achat_list.begin();
  vector<search_achat_item>::const_iterator l_iter_end = p_achat_list.end();
  uint32_t l_row = 0;
  while(l_iter != l_iter_end)
    {
      set_row_content(l_row,*l_iter);
      ++l_row;
      ++l_iter;
    }
  resizeColumnsToContents();
}

//EOF
