#include "facture_reason_widget.h"

#include "facture_reason_list_table.h"
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
facture_reason_widget::facture_reason_widget(fichier_client & p_fichier_client,QWidget * p_parent):
  QWidget(p_parent),
  m_modif_pending(false),
  m_create_facture_reason_button(NULL),
  m_delete_facture_reason_button(NULL),
  m_modify_facture_reason_button(NULL),
  m_reason_name_field(NULL),
  m_facture_reason_list_table(NULL),
  m_fichier_client(p_fichier_client)
{
  QVBoxLayout *l_vertical_layout = new QVBoxLayout(this);
  QHBoxLayout *l_horizontal_layout = new QHBoxLayout();
  l_vertical_layout->addLayout(l_horizontal_layout);

  l_horizontal_layout->addWidget(new QLabel(tr("Raison")+" :"));

  m_reason_name_field = new QLineEdit("");

  l_horizontal_layout->addWidget(m_reason_name_field);
  connect(m_reason_name_field,SIGNAL(textEdited(const QString&)),this, SLOT(treat_criteria_modification_event()));

  l_horizontal_layout->addStretch();
 
  l_vertical_layout->addWidget(new QLabel(tr("Raisons possibles pour les factures non attribuées")+" :"));

  m_facture_reason_list_table = new facture_reason_list_table(this);
  l_vertical_layout->addWidget(m_facture_reason_list_table);
  connect(m_facture_reason_list_table,SIGNAL(cellClicked (int, int)),this, SLOT(treat_facture_reason_selected_event(int)));
  connect(m_facture_reason_list_table,SIGNAL(itemSelectionChanged()),this, SLOT(treat_facture_reason_selection_changed_event()));

  m_create_facture_reason_button = new QPushButton(tr("&Create"),this);
  m_create_facture_reason_button->setEnabled(false);
  connect(m_create_facture_reason_button,SIGNAL(clicked()),this,SLOT(treat_create_facture_reason_event()));
  
  m_delete_facture_reason_button = new QPushButton(tr("&Delete"),this);
  m_delete_facture_reason_button->setEnabled(false);
  connect(m_delete_facture_reason_button,SIGNAL(clicked()),this,SLOT(treat_delete_facture_reason_event()));
  
  m_modify_facture_reason_button = new QPushButton(tr("&Modify"),this);
  m_modify_facture_reason_button->setEnabled(false);
  connect(m_modify_facture_reason_button,SIGNAL(clicked()),this,SLOT(treat_modify_facture_reason_event()));

  QHBoxLayout *l_button_layout = new QHBoxLayout();
  l_vertical_layout->addLayout(l_button_layout);
  
  l_button_layout->addWidget(m_create_facture_reason_button);
  l_button_layout->addWidget(m_delete_facture_reason_button);
  l_button_layout->addWidget(m_modify_facture_reason_button);
}

// Interactions with facture reason information
//-----------------------------------------------
//------------------------------------------------------------------------------
void facture_reason_widget::clear_facture_reason_information(void)
{
  m_reason_name_field->setText("");
}

//------------------------------------------------------------------------------
void facture_reason_widget::set_facture_reason_name(const std::string & p_name)
{
  m_reason_name_field->setText(p_name.c_str());
} 

//------------------------------------------------------------------------------
const std::string facture_reason_widget::get_facture_reason_name(void)const
{
  return m_reason_name_field->text().toStdString();
}

// Interactions with facture reason list
//---------------------------------------
//------------------------------------------------------------------------------
bool facture_reason_widget::is_facture_reason_selection_empty(void)const
{
  return m_facture_reason_list_table->selectedItems().isEmpty();
}

//------------------------------------------------------------------------------
uint32_t facture_reason_widget::get_selected_facture_reason_id(void)const
{
  return m_facture_reason_list_table->get_selected_facture_reason_id(m_facture_reason_list_table->currentRow());
}

//------------------------------------------------------------------------------
void facture_reason_widget::refresh_facture_reason_list(std::vector<facture_reason> & p_list)
{
  m_facture_reason_list_table->update(p_list);  
}

//------------------------------------------------------------------------------
void facture_reason_widget::set_facture_reason_list_enabled(bool p_enable)
{
  m_facture_reason_list_table->setEnabled(p_enable);
}

// Interactions with facture reason actions
//-------------------------------------------
//------------------------------------------------------------------------------
void facture_reason_widget::set_create_facture_reason_enabled(bool p_enable)
{
  m_create_facture_reason_button->setEnabled(p_enable);
}

//------------------------------------------------------------------------------
void facture_reason_widget::set_delete_facture_reason_enabled(bool p_enable)
{
  m_delete_facture_reason_button->setEnabled(p_enable);
}

//------------------------------------------------------------------------------
void facture_reason_widget::set_modify_facture_reason_enabled(bool p_enable)
{
  m_modify_facture_reason_button->setEnabled(p_enable);
}

//------------------------------------------------------------------------------
void facture_reason_widget::set_modify_facture_reason_action_name(const std::string & p_name)
{
  m_modify_facture_reason_button->setText(p_name.c_str());
}

//------------------------------------------------------------------------------
void facture_reason_widget::treat_facture_reason_selection_changed_event(void)
{
  std::cout << "QtEvent::facture reason selection changed" << std::endl ;
  if(m_facture_reason_list_table->selectedItems().isEmpty())
    {
      m_fichier_client.treat_no_more_facture_reason_selected_event();
    }
}


//------------------------------------------------------------------------------
void facture_reason_widget::treat_delete_facture_reason_event(void)
{
  std::cout << "QtEvent::delete facture reason button pressed" << std::endl ;

  m_fichier_client.treat_delete_facture_reason_event();
}

//------------------------------------------------------------------------------
void facture_reason_widget::treat_modify_facture_reason_event(void)
{
  std::cout << "QtEvent::" << m_modify_facture_reason_button->text().toStdString() << " facture_reason button clicked" << std::endl ;
  m_fichier_client.treat_modify_facture_reason_event();
}

//------------------------------------------------------------------------------
void facture_reason_widget::treat_criteria_modification_event(void)
{
  std::cout << "QtEvent::Facture reason name modification" << endl ;
  m_fichier_client.treat_facture_reason_name_modif_event();
}


//------------------------------------------------------------------------------
void facture_reason_widget::treat_create_facture_reason_event(void)
{
  std::cout << "QtEvent::Create facture_reason button clicked" << endl ;
  m_fichier_client.treat_create_facture_reason_event();
}

//------------------------------------------------------------------------------
void facture_reason_widget::treat_facture_reason_selected_event(int p_row)
{
  std::cout << "Facture reason Row selected " << p_row << endl ;
  m_fichier_client.treat_facture_reason_selected_event();
}

//------------------------------------------------------------------------------
void facture_reason_widget::set_enable(bool p_enable)
{
  m_reason_name_field->setEnabled(p_enable);
  clear_facture_reason_information();

  m_delete_facture_reason_button->setEnabled(false);
  m_modify_facture_reason_button->setEnabled(false);

  m_facture_reason_list_table->clearContents();

  if(p_enable)
    {
      treat_criteria_modification_event();
    }
}

//EOF
