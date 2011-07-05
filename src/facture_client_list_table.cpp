#include "facture_client_list_table.h"
#include "simple_table_cell.h"

//------------------------------------------------------------------------------
facture_client_list_table::facture_client_list_table(QWidget *parent):
  facture_list_table(parent,5,get_header_list())
{
  setColumnHidden(get_nb_column(),true);
}

//------------------------------------------------------------------------------
QStringList facture_client_list_table::get_header_list(void)
{
  QStringList l_header_list;
  l_header_list << tr("Client_Id") << tr("Reason") << tr("Name") << tr("First Name") << tr("Address") << tr("City");
  return l_header_list;
}

//------------------------------------------------------------------------------
void facture_client_list_table::set_row_content(uint32_t p_row,const search_facture_client_item & p_item)
{
  facture_list_table::set_row_content(p_row,p_item);
  uint32_t l_id = p_item.get_client_id();
  QString l_id_q;
  l_id_q.setNum(l_id);
  setItem(p_row,get_nb_column(),new simple_table_cell(l_id_q,l_id));
  
  setItem(p_row,1 + get_nb_column(),new simple_table_cell(p_item.get_reason().c_str()));
  setItem(p_row,2 + get_nb_column(),new simple_table_cell(p_item.get_name().c_str()));
  setItem(p_row,3 + get_nb_column(),new simple_table_cell(p_item.get_first_name().c_str()));
  setItem(p_row,4 + get_nb_column(),new simple_table_cell(p_item.get_address().c_str()));
  setItem(p_row,5 + get_nb_column(),new simple_table_cell(p_item.get_city().c_str()));
  
}

//------------------------------------------------------------------------------
void facture_client_list_table::update(std::vector<search_facture_client_item> & p_search_facture_item_list)
{
  clearContents();
  setRowCount(p_search_facture_item_list.size());
  std::vector<search_facture_client_item>::const_iterator l_iter = p_search_facture_item_list.begin();
  std::vector<search_facture_client_item>::const_iterator l_iter_end = p_search_facture_item_list.end();
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
