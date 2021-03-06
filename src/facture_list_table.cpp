#include "facture_list_table.h"
#include "simple_table_cell.h"
#include "facture_status.h"
#include "fichier_client_QtUi_utils.h"
#include <vector>
#include <assert.h>

using namespace std;

//------------------------------------------------------------------------------
facture_list_table::facture_list_table(QWidget *parent):
  QTableWidget(0,m_nb_column,parent)
{
  setHorizontalHeaderLabels(get_header_list());
  setSelectionBehavior(QAbstractItemView::SelectRows);
  setSelectionMode(QAbstractItemView::SingleSelection);
  setItemPrototype(new simple_table_cell(""));
  setColumnHidden(0,true);
}

//------------------------------------------------------------------------------
facture_list_table::facture_list_table(QWidget *parent,uint32_t p_additional_column,QStringList p_additional_header):
  QTableWidget(0,m_nb_column + p_additional_column,parent)
{
  setHorizontalHeaderLabels(get_header_list()+p_additional_header);
  setSelectionBehavior(QAbstractItemView::SelectRows);
  setSelectionMode(QAbstractItemView::SingleSelection);
  setItemPrototype(new simple_table_cell(""));
  setColumnHidden(0,true);
  setColumnHidden(1,true);
}

//------------------------------------------------------------------------------
QStringList facture_list_table::get_header_list(void)
{
  QStringList l_header_list;
  l_header_list << tr("Id") << tr("Livre Facture") << tr("Numero") << tr("Date") << tr("Status");
  assert(m_nb_column == (uint32_t)l_header_list.size());
  return l_header_list;
 }

//------------------------------------------------------------------------------
uint32_t facture_list_table::get_selected_facture_item_id(uint32_t p_row)const
{
  assert(p_row < ((uint32_t)rowCount()));
  return static_cast<simple_table_cell*>(item(p_row,0))->get_id();
}

//------------------------------------------------------------------------------
void facture_list_table::set_row_content(uint32_t p_row,const search_facture_item & p_search_facture_item)
{
      QString l_id_q;
      l_id_q.setNum(p_search_facture_item.get_id());
      setItem(p_row,0,new simple_table_cell(l_id_q,p_search_facture_item.get_id()));

      uint32_t l_livre_facture_id = p_search_facture_item.get_livre_facture_id();
      QString l_livre_facture_id_q;
      l_livre_facture_id_q.setNum(l_livre_facture_id);
      simple_table_cell * l_livre_facture_id_cell = new simple_table_cell(l_livre_facture_id_q,l_livre_facture_id);
      if(!l_livre_facture_id)
	{
	  l_livre_facture_id_cell->set_warning_background();
	}
      setItem(p_row,1,l_livre_facture_id_cell);

      uint32_t l_facture_ref = p_search_facture_item.get_facture_ref();
      QString l_facture_ref_q;
      l_facture_ref_q.setNum(l_facture_ref);
      simple_table_cell *l_facture_ref_cell = new simple_table_cell(l_facture_ref_q,l_facture_ref);
      if(!l_facture_ref)
	{
	  l_facture_ref_cell->set_warning_background();
	}
      setItem(p_row,2,l_facture_ref_cell);

      setItem(p_row,3,new simple_table_cell(fichier_client_QtUi_utils::get_human_date(p_search_facture_item.get_date()).c_str()));

      const std::string & l_status = p_search_facture_item.get_facture_status();
      simple_table_cell * l_facture_status_cell = new simple_table_cell(p_search_facture_item.get_facture_status().c_str());
      if(l_status != facture_status::get_ok_status())
	{
	  l_facture_status_cell->set_warning_background();
	}
      setItem(p_row,4,l_facture_status_cell);
}

//------------------------------------------------------------------------------
void facture_list_table::update(const std::vector<search_facture_item> & p_search_facture_item_list)
{
  clearContents();
  setRowCount(p_search_facture_item_list.size());
  std::vector<search_facture_item>::const_iterator l_iter = p_search_facture_item_list.begin();
  std::vector<search_facture_item>::const_iterator l_iter_end = p_search_facture_item_list.end();
  uint32_t l_row = 0;
  while(l_iter != l_iter_end)
    {
      set_row_content(l_row,*l_iter);
      ++l_row;
      ++l_iter;
    }
  resizeColumnsToContents();
}

//------------------------------------------------------------------------------
void facture_list_table::clear(void)
{
  std::vector<search_facture_item> l_empty_list;
  this->update(l_empty_list);
}

//------------------------------------------------------------------------------
uint32_t facture_list_table::get_nb_column(void)
{
  return m_nb_column;
}

const uint32_t facture_list_table::m_nb_column = 5;

//EOF
