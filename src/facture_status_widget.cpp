#include "facture_status_widget.h"

#include "facture_status_list_table.h"
#include "fichier_client.h"

#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QLineEdit>

#include <iostream>
using namespace std;

//------------------------------------------------------------------------------
facture_status_widget::facture_status_widget(fichier_client & p_fichier_client,QWidget * p_parent):
  QWidget(p_parent),
  m_modif_pending(false),
  m_create_facture_status_button(NULL),
  m_delete_facture_status_button(NULL),
  m_modify_facture_status_button(NULL),
  m_status_name_field(NULL),
  m_facture_status_list_table(NULL),
  m_fichier_client(p_fichier_client)
{
  QVBoxLayout *l_vertical_layout = new QVBoxLayout(this);
  QHBoxLayout *l_horizontal_layout = new QHBoxLayout();
  l_vertical_layout->addLayout(l_horizontal_layout);

  l_horizontal_layout->addWidget(new QLabel(tr("Statut")+" :"));

  m_status_name_field = new QLineEdit("");

  l_horizontal_layout->addWidget(m_status_name_field);
  connect(m_status_name_field,SIGNAL(textEdited(const QString&)),this, SLOT(criteria_modification()));

  l_horizontal_layout->addStretch();
 
  l_vertical_layout->addWidget(new QLabel(tr("Statuts possibles pour les factures")+" :"));

  m_facture_status_list_table = new facture_status_list_table(this);
  l_vertical_layout->addWidget(m_facture_status_list_table);
  connect(m_facture_status_list_table,SIGNAL(cellClicked (int, int)),this, SLOT(facture_status_selected(int)));
  connect(m_facture_status_list_table,SIGNAL(itemSelectionChanged()),this, SLOT(facture_status_selection_changed()));

  m_create_facture_status_button = new QPushButton(tr("&Create"),this);
  m_create_facture_status_button->setEnabled(false);
  connect(m_create_facture_status_button,SIGNAL(clicked()),this,SLOT(create_facture_status()));
  
  m_delete_facture_status_button = new QPushButton(tr("&Delete"),this);
  m_delete_facture_status_button->setEnabled(false);
  connect(m_delete_facture_status_button,SIGNAL(clicked()),this,SLOT(delete_facture_status()));
  
  m_modify_facture_status_button = new QPushButton(tr("&Modify"),this);
  m_modify_facture_status_button->setEnabled(false);
  connect(m_modify_facture_status_button,SIGNAL(clicked()),this,SLOT(modify_facture_status()));

  QHBoxLayout *l_button_layout = new QHBoxLayout();
  l_vertical_layout->addLayout(l_button_layout);
  
  l_button_layout->addWidget(m_create_facture_status_button);
  l_button_layout->addWidget(m_delete_facture_status_button);
  l_button_layout->addWidget(m_modify_facture_status_button);
}

//------------------------------------------------------------------------------
void facture_status_widget::facture_status_selection_changed(void)
{
  cout << "facture_status_selection_changed" << endl ;
  if(m_facture_status_list_table->selectedItems().isEmpty())
    {
      m_delete_facture_status_button->setEnabled(false);
      m_modify_facture_status_button->setEnabled(false);
    }
}


//------------------------------------------------------------------------------
uint32_t facture_status_widget::get_selected_facture_status_id(void)
{
  return m_facture_status_list_table->get_selected_facture_status_id(m_facture_status_list_table->currentRow());
}

//------------------------------------------------------------------------------
void facture_status_widget::get_selected_facture_status(facture_status & p_selected)
{
  uint32_t l_status = m_fichier_client.get_facture_status(get_selected_facture_status_id(),p_selected);
  assert(l_status);
}

//------------------------------------------------------------------------------
void facture_status_widget::delete_facture_status(void)
{
  facture_status l_selected;
  get_selected_facture_status(l_selected);

  string l_name = l_selected.getName();
  assert(l_name != facture_status::get_ok_status() && l_name != facture_status::get_non_checked_status());
  
  m_fichier_client.remove(l_selected);
  m_delete_facture_status_button->setEnabled(false);
  m_modify_facture_status_button->setEnabled(false);
  clear_text_fields();
  criteria_modification();
}

//------------------------------------------------------------------------------
void facture_status_widget::modify_facture_status(void)
{
  cout << m_modify_facture_status_button->text().toStdString() << " Facture_status clicked" << endl ;
  facture_status l_selected;
  get_selected_facture_status(l_selected);
  m_delete_facture_status_button->setEnabled(false);

  if(!m_modif_pending)
    {
      m_modif_pending = true;
      m_status_name_field->setText(l_selected.getName().c_str());
      m_modify_facture_status_button->setText("Annuler");
      m_facture_status_list_table->setEnabled(false);
    }
  else
    {
      m_facture_status_list_table->setEnabled(true);
      m_modify_facture_status_button->setText("Modify");

      l_selected.setName(m_status_name_field->text().toStdString());
      m_fichier_client.update(l_selected);
      m_modif_pending = false;

      clear_text_fields();
      criteria_modification();
    }

}


//------------------------------------------------------------------------------
void facture_status_widget::create_facture_status(void)
{
  cout << "Create Facture_status clicked" << endl ;
  string l_status_name(m_status_name_field->text().toStdString());
  
  m_create_facture_status_button->setEnabled(false);
  facture_status l_status(l_status_name);

  m_fichier_client.create(l_status);
  clear_text_fields();
  criteria_modification();
}

//------------------------------------------------------------------------------
void facture_status_widget::clear_text_fields(void)
{
  m_status_name_field->setText("");
}


//------------------------------------------------------------------------------
void facture_status_widget::set_enable(bool p_enable)
{
  m_status_name_field->setEnabled(p_enable);
  clear_text_fields();

  m_delete_facture_status_button->setEnabled(false);
  m_modify_facture_status_button->setEnabled(false);

  m_facture_status_list_table->clearContents();

  if(p_enable)
    {
      criteria_modification();
    }
}

//------------------------------------------------------------------------------
void facture_status_widget::criteria_modification(void)
{
  cout << "Facture tatus name modification" << endl ;

  string l_status_name = m_status_name_field->text().toStdString();
  cout << "Status name = \"" << l_status_name << "\"" << endl ;

  vector<facture_status> l_vector;
  if(l_status_name != "")
    {
      m_fichier_client.get_facture_status_by_name(l_status_name,l_vector);
    }
  else
    {
      m_fichier_client.get_all_facture_status(l_vector);
    }

  if(!m_modif_pending)
    {
      m_create_facture_status_button->setEnabled(l_vector.size()==0);
      m_facture_status_list_table->update(l_vector);  
    }
  else
    {
      facture_status l_selected;
      get_selected_facture_status(l_selected);
      m_modify_facture_status_button->setText((l_selected.getName() != l_status_name?"Appliquer" : "Annuler"));

      // Check if modified value is acceptable
      
      bool l_ok = l_status_name != "";
      if(l_ok && l_vector.size() == 1 && l_vector[0].getName() == l_status_name)
	{
	  l_ok = false;
	}
      m_modify_facture_status_button->setEnabled(l_ok);
    }
}

//------------------------------------------------------------------------------
void facture_status_widget::facture_status_selected(int p_row)
{
    cout << "Facture status Row selected " << p_row << endl ;
    cout << "Id of selected facture_status " << get_selected_facture_status_id() << endl;
    facture_status l_selected;
    get_selected_facture_status(l_selected);
    string l_name = l_selected.getName();

    if(l_name != facture_status::get_ok_status() && l_name != facture_status::get_non_checked_status())
      {
	m_delete_facture_status_button->setEnabled(true);
	m_modify_facture_status_button->setEnabled(true);
      }
    else
      {
	m_delete_facture_status_button->setEnabled(false);
	m_modify_facture_status_button->setEnabled(false);
      }
}

//EOF
