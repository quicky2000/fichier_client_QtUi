#include "livre_facture_table.h"
#include "simple_table_cell.h"
#include "fichier_client_QtUi_utils.h"
#include <vector>
#include <assert.h>

using namespace std;

livre_facture_table::livre_facture_table(QWidget *parent):
  QTableWidget(0,3,parent)
{
  QStringList l_h_header_list;
  l_h_header_list << tr("Id") << tr("Start Date") << tr("End Date") ;
  setHorizontalHeaderLabels(l_h_header_list);
  setSelectionBehavior(QAbstractItemView::SelectRows);
  setSelectionMode(QAbstractItemView::SingleSelection);
  setItemPrototype(new simple_table_cell(""));
}

uint32_t livre_facture_table::get_selected_livre_facture_id(uint32_t p_row)const
{
  assert(p_row < ((uint32_t)rowCount()));
  return static_cast<simple_table_cell*>(item(p_row,0))->get_id();
}

void livre_facture_table::set_row_content(uint32_t p_row,const livre_facture & p_livre_facture)
{
      QString l_id_q;
      l_id_q.setNum(p_livre_facture.get_id());
      setItem(p_row,0,new simple_table_cell(l_id_q,p_livre_facture.get_id()));
      setItem(p_row,1,new simple_table_cell(fichier_client_QtUi_utils::get_human_date(p_livre_facture.getStartDate()).c_str()));
      setItem(p_row,2,new simple_table_cell(fichier_client_QtUi_utils::get_human_date(p_livre_facture.getEndDate()).c_str()));
}

void livre_facture_table::update(std::vector<livre_facture> p_livre_facture_list)
{
  clearContents();
  setRowCount(p_livre_facture_list.size());
  vector<livre_facture>::const_iterator l_iter = p_livre_facture_list.begin();
  vector<livre_facture>::const_iterator l_iter_end = p_livre_facture_list.end();
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
