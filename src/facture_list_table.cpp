#include "facture_list_table.h"
#include "simple_table_cell.h"
#include "facture_status.h"
#include <vector>
#include <assert.h>

using namespace std;

facture_list_table::facture_list_table(QWidget *parent):
  QTableWidget(0,5,parent)
{
  QStringList l_h_header_list;
  l_h_header_list << tr("Id") << tr("Reference") << tr("Date") << tr("Livre Facture") << tr("Status");
  setHorizontalHeaderLabels(l_h_header_list);
  setSelectionBehavior(QAbstractItemView::SelectRows);
  setSelectionMode(QAbstractItemView::SingleSelection);
  setItemPrototype(new simple_table_cell(""));
}

uint32_t facture_list_table::get_selected_facture_item_id(uint32_t p_row)const
{
  assert(p_row < ((uint32_t)rowCount()));
  return static_cast<simple_table_cell*>(item(p_row,0))->get_id();
}

void facture_list_table::set_row_content(uint32_t p_row,const search_facture_item & p_search_facture_item)
{
      QString l_id_q;
      l_id_q.setNum(p_search_facture_item.get_id());
      setItem(p_row,0,new simple_table_cell(l_id_q,p_search_facture_item.get_id()));
      uint32_t l_facture_ref = p_search_facture_item.get_facture_ref();
      QString l_facture_ref_q;
      l_facture_ref_q.setNum(l_facture_ref);
      simple_table_cell *l_facture_ref_cell = new simple_table_cell(l_facture_ref_q,l_facture_ref);
      if(!l_facture_ref)
	{
	  l_facture_ref_cell->set_warning_background();
	}
      setItem(p_row,1,l_facture_ref_cell);
      setItem(p_row,2,new simple_table_cell(p_search_facture_item.get_date().c_str()));
      uint32_t l_livre_facture_id = p_search_facture_item.get_livre_facture_id();
      QString l_livre_facture_id_q;
      l_livre_facture_id_q.setNum(l_livre_facture_id);
      simple_table_cell * l_livre_facture_id_cell = new simple_table_cell(l_livre_facture_id_q,l_livre_facture_id);
      if(!l_livre_facture_id)
	{
	  l_livre_facture_id_cell->set_warning_background();
	}
      setItem(p_row,3,l_livre_facture_id_cell);

      const std::string & l_status = p_search_facture_item.get_facture_status();
      simple_table_cell * l_facture_status_cell = new simple_table_cell(p_search_facture_item.get_facture_status().c_str());
      if(l_status != facture_status::get_ok_status())
	{
	  l_facture_status_cell->set_warning_background();
	}
      setItem(p_row,4,l_facture_status_cell);
}

void facture_list_table::update(std::vector<search_facture_item> p_search_facture_item_list)
{
  clearContents();
  setRowCount(p_search_facture_item_list.size());
  vector<search_facture_item>::const_iterator l_iter = p_search_facture_item_list.begin();
  vector<search_facture_item>::const_iterator l_iter_end = p_search_facture_item_list.end();
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
