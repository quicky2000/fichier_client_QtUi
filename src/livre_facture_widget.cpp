#include "livre_facture_widget.h"
#include "livre_facture_table.h"
#include "facture_client_list_table.h"
#include "fichier_client.h"

#include "my_date_widget.h"
#include "non_attributed_facture_widget.h"

#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QLineEdit>

#include <iostream>
using namespace std;

//------------------------------------------------------------------------------
livre_facture_widget::livre_facture_widget(fichier_client & p_fichier_client,QWidget * p_parent):
  QWidget(p_parent),
  m_create_livre_facture_button(NULL),
  m_delete_livre_facture_button(NULL),
  m_modify_livre_facture_button(NULL),
  m_livre_id_field(NULL),
  m_start_date_field(NULL),
  m_end_date_field(NULL),
  m_livre_facture_table(NULL),
  m_create_facture_button(NULL),
  m_delete_facture_button(NULL),
  m_modify_facture_button(NULL),
  m_facture_client_list_table(NULL),
  m_fichier_client(p_fichier_client)
{
  QVBoxLayout *l_vertical_layout = new QVBoxLayout(this);
  QHBoxLayout *l_horizontal_layout = new QHBoxLayout();
  l_vertical_layout->addLayout(l_horizontal_layout);

  // Livre facture fields
  //----------------------
  l_horizontal_layout->addWidget(new QLabel(tr("Id")+" :"));

  m_livre_id_field = new QLineEdit("");
  m_livre_id_field->setInputMask("999999");

  l_horizontal_layout->addWidget(m_livre_id_field);
  //  connect(m_livre_id_field,SIGNAL(textEdited(const QString&)),this, SLOT(treat_livre_facture_id_modif_event()));
  connect(m_livre_id_field,SIGNAL(textEdited(const QString&)),this, SLOT(treat_livre_facture_id_modif_event()));

  l_horizontal_layout->addStretch();
  l_horizontal_layout->addWidget(new QLabel(tr("Start Date")+" :"));

  m_start_date_field = new my_date_widget();
  l_horizontal_layout->addWidget(m_start_date_field);
  connect(m_start_date_field,SIGNAL(textEdited(const QString&)),this, SLOT(treat_livre_facture_content_modif_event()));


  l_horizontal_layout->addStretch();
  l_horizontal_layout->addWidget(new QLabel(tr("End Date")+" :"));

  m_end_date_field = new my_date_widget();
  l_horizontal_layout->addWidget(m_end_date_field);
  connect(m_end_date_field,SIGNAL(textEdited(const QString&)),this, SLOT(treat_livre_facture_content_modif_event()));

  // Table of livre facture
  //-------------------------
  l_vertical_layout->addWidget(new QLabel(tr("Livres de facture")+" :"));

  m_livre_facture_table = new livre_facture_table(this);
  l_vertical_layout->addWidget(m_livre_facture_table);
  connect(m_livre_facture_table,SIGNAL(cellClicked (int, int)),this, SLOT(treat_livre_facture_selected_event(int)));
  connect(m_livre_facture_table,SIGNAL(itemSelectionChanged()),this, SLOT(treat_livre_facture_selection_changed_event()));

  // Livre facture Buttons 
  //-------------------------
  m_create_livre_facture_button = new QPushButton(tr("&Create"),this);
  m_create_livre_facture_button->setEnabled(false);
  connect(m_create_livre_facture_button,SIGNAL(clicked()),this,SLOT(treat_create_livre_facture_event()));

  m_delete_livre_facture_button = new QPushButton(tr("&Delete"),this);
  m_delete_livre_facture_button->setEnabled(false);
  connect(m_delete_livre_facture_button,SIGNAL(clicked()),this,SLOT(treat_delete_livre_facture_event()));

  m_modify_livre_facture_button = new QPushButton(tr("&Modify"),this);
  m_modify_livre_facture_button->setEnabled(false);
  connect(m_modify_livre_facture_button,SIGNAL(clicked()),this,SLOT(treat_modify_livre_facture_event()));

  QHBoxLayout *l_button_layout = new QHBoxLayout();
  l_vertical_layout->addLayout(l_button_layout);

  l_button_layout->addWidget(m_create_livre_facture_button);
  l_button_layout->addWidget(m_delete_livre_facture_button);
  l_button_layout->addWidget(m_modify_livre_facture_button);

  // Non attributed facture fields
  //-------------------------------
  l_vertical_layout->addWidget(new QLabel(tr("Factures du livre")+" :"));
  m_non_attributed_facture_widget = new non_attributed_facture_widget(this);
  l_vertical_layout->addWidget(m_non_attributed_facture_widget);
  connect(m_non_attributed_facture_widget,SIGNAL(new_date_entered()),this,SLOT(treat_non_attributed_facture_date_entered_event()));
  connect(m_non_attributed_facture_widget,SIGNAL(new_facture_ref_selected()),this,SLOT(treat_non_attributed_facture_ref_selected_event()));
  connect(m_non_attributed_facture_widget,SIGNAL(new_status_selected()),this,SLOT(treat_non_attributed_facture_status_selected_event()));
  connect(m_non_attributed_facture_widget,SIGNAL(new_livre_facture_selected()),this,SLOT(treat_non_attributed_facture_livre_facture_selected_event()));
  connect(m_non_attributed_facture_widget,SIGNAL(reason_selected()),this,SLOT(treat_non_attributed_facture_reason_selected_event()));

  // Table of factures
  //----------------------
  m_facture_client_list_table = new facture_client_list_table(this);
  connect(m_facture_client_list_table,SIGNAL(cellClicked (int, int)),this, SLOT(treat_facture_selected_event(int)));
  connect(m_facture_client_list_table,SIGNAL(itemSelectionChanged()),this, SLOT(treat_facture_selection_changed_event()));
  l_vertical_layout->addWidget(m_facture_client_list_table);

  // Facture buttons
  //-----------------------
  QHBoxLayout *l_facture_button_layout = new QHBoxLayout();
  m_create_facture_button = new QPushButton(tr("&Create Non attributed facture"),this);
  m_create_facture_button->setEnabled(false);
  connect(m_create_facture_button,SIGNAL(clicked()),this,SLOT(treat_create_facture_event()));

  m_delete_facture_button = new QPushButton(tr("&Delete"),this);
  m_delete_facture_button->setEnabled(false);
  connect(m_delete_facture_button,SIGNAL(clicked()),this,SLOT(treat_delete_facture_event()));

  m_modify_facture_button = new QPushButton(tr("&Modify"),this);
  m_modify_facture_button->setEnabled(false);
  connect(m_modify_facture_button,SIGNAL(clicked()),this,SLOT(treat_modify_facture_event()));

  l_facture_button_layout->addWidget(m_create_facture_button);
  l_facture_button_layout->addWidget(m_modify_facture_button);
  l_facture_button_layout->addWidget(m_delete_facture_button);

  l_vertical_layout->addLayout(l_facture_button_layout);
}

// Interactions with livre facture fields
//------------------------------------------
//------------------------------------------------------------------------------
void livre_facture_widget::clear_livre_facture_information(void)
{
  m_livre_id_field->setText("");
  m_start_date_field->setText("");
  m_end_date_field->setText("");   
}

//------------------------------------------------------------------------------
void livre_facture_widget::set_livre_facture_start_date(const std::string & p_date)
{
  m_start_date_field->set_iso_date(p_date.c_str());
}

//------------------------------------------------------------------------------
void livre_facture_widget::set_livre_facture_end_date(const std::string & p_date)
{
  m_end_date_field->set_iso_date(p_date.c_str());
}

//------------------------------------------------------------------------------
void livre_facture_widget::set_livre_facture_id(const std::string & p_id)
{
  m_livre_id_field->setText(p_id.c_str());
}

//------------------------------------------------------------------------------
const std::string livre_facture_widget::get_livre_facture_start_date(void)const
{
  return m_start_date_field->get_iso_date();
}

//------------------------------------------------------------------------------
bool livre_facture_widget::is_livre_facture_start_date_complete(void)const
{
  return m_start_date_field->is_complete();
}

//------------------------------------------------------------------------------
const std::string livre_facture_widget::get_livre_facture_end_date(void)const
{
  return m_end_date_field->get_iso_date();
}

//------------------------------------------------------------------------------
bool livre_facture_widget::is_livre_facture_end_date_complete(void)const
{
  return m_end_date_field->is_complete();
}

//------------------------------------------------------------------------------
const std::string livre_facture_widget::get_livre_facture_id(void)const
{
  return m_livre_id_field->text().toStdString();
}

// Interactions with livre facture list
//--------------------------------------
//------------------------------------------------------------------------------
bool livre_facture_widget::is_livre_facture_selection_empty(void)const
{
  return m_livre_facture_table->selectedItems().isEmpty();
}

//------------------------------------------------------------------------------
uint32_t livre_facture_widget::get_selected_livre_facture_id(void)const
{
  return m_livre_facture_table->get_selected_livre_facture_id(m_livre_facture_table->currentRow());
}

//------------------------------------------------------------------------------
void livre_facture_widget::refresh_livre_facture_list(std::vector<livre_facture> & p_list)
{
  m_livre_facture_table->update(p_list);
}


// Interactions with livre facture buttons
//------------------------------------------
//------------------------------------------------------------------------------
void livre_facture_widget::set_delete_livre_facture_enabled(bool p_enabled)
{
  m_delete_livre_facture_button->setEnabled(p_enabled);
}

//------------------------------------------------------------------------------
void livre_facture_widget::set_modify_livre_facture_enabled(bool p_enabled)
{
  m_modify_livre_facture_button->setEnabled(p_enabled);
}

//------------------------------------------------------------------------------
void livre_facture_widget::set_create_livre_facture_enabled(bool p_enabled)
{
  m_create_livre_facture_button->setEnabled(p_enabled);
}

// Interactions with non attributed facture fields
//---------------------------------------------------

//------------------------------------------------------------------------------
void livre_facture_widget::set_non_attributed_facture_date(const std::string & p_date)
{
  m_non_attributed_facture_widget->set_date(p_date);
}


//------------------------------------------------------------------------------
void livre_facture_widget::set_allowed_facture_references(const std::vector<uint32_t> & p_remaining_refs)
{
  m_non_attributed_facture_widget->set_allowed_facture_ref(p_remaining_refs);
}

//------------------------------------------------------------------------------
void livre_facture_widget::set_facture_reference(uint32_t p_ref)
{
  m_non_attributed_facture_widget->set_reference(p_ref);
}

 //------------------------------------------------------------------------------
void livre_facture_widget::set_allowed_livre_ids(const std::vector<uint32_t> & p_livre_ids)
{
  m_non_attributed_facture_widget->set_allowed_livre_ids(p_livre_ids);
}

//------------------------------------------------------------------------------
void livre_facture_widget::set_status_list(const std::vector<facture_status> & p_status_list)
{
  m_non_attributed_facture_widget->set_status_list(p_status_list);
}

//------------------------------------------------------------------------------
void livre_facture_widget::set_status(uint32_t p_id)
{
  m_non_attributed_facture_widget->set_status(p_id);
}

//------------------------------------------------------------------------------
void livre_facture_widget::set_reason_list(const std::vector<facture_reason> & p_reason_list)
{
  m_non_attributed_facture_widget->set_reason_list(p_reason_list);
}

//------------------------------------------------------------------------------
void livre_facture_widget::set_reason(uint32_t p_id)
{
  m_non_attributed_facture_widget->set_reason(p_id);
}

//------------------------------------------------------------------------------
const std::string livre_facture_widget::get_non_attributed_facture_date(void)const
{
  return m_non_attributed_facture_widget->get_iso_date();
}

//------------------------------------------------------------------------------
uint32_t livre_facture_widget::get_non_attributed_facture_livre_facture_id(void)const
{
  return m_non_attributed_facture_widget->get_livre_facture_id();
}

//------------------------------------------------------------------------------
uint32_t livre_facture_widget::get_non_attributed_facture_reference(void)const
{
  return m_non_attributed_facture_widget->get_facture_reference();
}

//------------------------------------------------------------------------------
const facture_status * livre_facture_widget::get_non_attributed_facture_status(void)const
{
  return m_non_attributed_facture_widget->get_facture_status();
}

//------------------------------------------------------------------------------
const facture_reason * livre_facture_widget::get_non_attributed_facture_reason(void)const
{
  return m_non_attributed_facture_widget->get_facture_reason();
}

//------------------------------------------------------------------------------
void livre_facture_widget::clear_non_attributed_facture_date(void)
{
  m_non_attributed_facture_widget->clear_date();
}

//------------------------------------------------------------------------------
void livre_facture_widget::enable_non_attributed_facture_fields(bool p_enable)
{
  m_non_attributed_facture_widget->set_enabled(p_enable);
}

//------------------------------------------------------------------------------
bool livre_facture_widget::is_non_attributed_facture_date_complete(void)const
{
  return m_non_attributed_facture_widget->is_date_complete();
}

//------------------------------------------------------------------------------
bool livre_facture_widget::is_non_attributed_facture_date_empty(void)const
{
  return m_non_attributed_facture_widget->is_date_empty();
}

// Interactions with non attributed facture list
//------------------------------------------------
//------------------------------------------------------------------------------
void livre_facture_widget::refresh_list_facture_of_livre_facture(std::vector<search_facture_client_item> & p_list)
{
  m_facture_client_list_table->update(p_list);  
}

//------------------------------------------------------------------------------
bool livre_facture_widget::is_list_facture_selection_empty(void)const
{
  return m_facture_client_list_table->selectedItems().isEmpty();
}

//------------------------------------------------------------------------------
uint32_t livre_facture_widget::get_list_facture_selected_id(void)const
{
  return m_facture_client_list_table->get_selected_facture_item_id(m_facture_client_list_table->currentRow());
}


// Interaction with non attributed facture buttons
//---------------------------------------------------
//------------------------------------------------------------------------------
void livre_facture_widget::set_facture_creation_enabled(bool p_enabled)
{
  m_create_facture_button->setEnabled(p_enabled);
}

//------------------------------------------------------------------------------
void livre_facture_widget::set_facture_deletion_enabled(bool p_enabled)
{
  m_delete_facture_button->setEnabled(p_enabled);
}

//------------------------------------------------------------------------------
void livre_facture_widget::set_facture_modification_enabled(bool p_enabled)
{
  m_modify_facture_button->setEnabled(p_enabled);
}

//-------
// Slots 
//-------


//------------------------------------------------------------------------------
void livre_facture_widget::treat_create_facture_event(void)
{
  cout << "QtEvent::livre_facture_widget::Create_facture button clicked" << endl ;
  m_fichier_client.treat_create_non_attributed_facture_event();
}



//------------------------------------------------------------------------------
void livre_facture_widget::treat_delete_facture_event(void)
{
  cout << "QtEvent::livre_facture_widget::delete_facture button clicked" << endl ;
  m_fichier_client.treat_delete_non_attributed_facture_event();
}

//------------------------------------------------------------------------------
void livre_facture_widget::treat_modify_facture_event(void)
{
  cout << "QtEvent::livre_facture_widget::modify_facture button clicked" << endl ;
  m_fichier_client.treat_modify_non_attributed_facture_event();
}

//------------------------------------------------------------------------------
void livre_facture_widget::treat_facture_selected_event(int row)
{
  cout << "QtEvent::livre_facture_widget::Facture selected" << endl ;
  m_fichier_client.treat_facture_selected_event();
}

//------------------------------------------------------------------------------
void livre_facture_widget::treat_facture_selection_changed_event(void)
{
  cout << "QtEvent::livre_facture_widget::Facture_selection changed" << endl ;
  // Do nothing is selection is not empty because specific event will be launched
  if(m_facture_client_list_table->selectedItems().isEmpty())
    {
      m_fichier_client.treat_no_more_facture_selected_event();
    }
}


//------------------------------------------------------------------------------
void livre_facture_widget::treat_non_attributed_facture_date_entered_event(void)
{
  std::cout << "QtEvent::livre_facture_widget::non_attributed_facture_date_entered" << std::endl;
  m_fichier_client.non_attributed_facture_date_entered();
}

//------------------------------------------------------------------------------
void livre_facture_widget::treat_non_attributed_facture_ref_selected_event(void)
{
  std::cout << "QtEvent::livre_facture_widget::non_attributed_facture_ref_selected" << std::endl;
  m_fichier_client.non_attributed_facture_reference_selected();
}

//------------------------------------------------------------------------------
void livre_facture_widget::treat_non_attributed_facture_status_selected_event(void)
{
  std::cout << "QtEvent::livre_facture_widget::non_attributed_facture_status_selected" << std::endl;
  m_fichier_client.non_attributed_facture_status_selected();
}

//------------------------------------------------------------------------------
void livre_facture_widget::treat_non_attributed_facture_reason_selected_event(void)
{
  std::cout << "QtEvent::livre_facture_widget::non_attributed_facture_reason_selected" << std::endl;
  m_fichier_client.non_attributed_facture_reason_selected();
}

//------------------------------------------------------------------------------
void livre_facture_widget::treat_non_attributed_facture_livre_facture_selected_event(void)
{
  std::cout << "QtEvent::livre_facture_widget::non_attributed_facture_livre_facture_selected" << std::endl;
  m_fichier_client.non_attributed_facture_livre_facture_selected();
}


//------------------------------------------------------------------------------
void livre_facture_widget::treat_livre_facture_selection_changed_event(void)
{
  cout << "QtEvent::livre_facture_selection_changed" << endl ;
  // Do nothing is selection is not empty because specific event will be launched
  if(m_livre_facture_table->selectedItems().isEmpty())
    {
      m_fichier_client.treat_no_more_livre_facture_selected_event();
    }
}

//------------------------------------------------------------------------------
void livre_facture_widget::treat_delete_livre_facture_event(void)
{
  cout << "QtEvent::Delete livre_facture button pressed" << endl ;
  m_fichier_client.treat_delete_livre_facture_event();
}

//------------------------------------------------------------------------------
void livre_facture_widget::treat_modify_livre_facture_event(void)
{
  cout << "QtEvent::Modify livre_facture button pressed" << endl ;
  m_fichier_client.treat_modify_livre_facture_event();
}

//------------------------------------------------------------------------------
void livre_facture_widget::treat_create_livre_facture_event(void)
{
  cout << "QtEvent::Create livre_facture button pressed" << endl ;
  m_fichier_client.treat_create_livre_facture_event();
}

//------------------------------------------------------------------------------
void livre_facture_widget::treat_livre_facture_id_modif_event(void)
{
  cout << "QtEvent::Livre facture Id modif event" << endl ;
  m_fichier_client.treat_livre_facture_id_modif_event();
}

//------------------------------------------------------------------------------
void livre_facture_widget::treat_livre_facture_content_modif_event(void)
{
  cout << "QtEvent::livre facture Content modification" << endl ;
  m_fichier_client.treat_livre_facture_content_modif_event();
}


//------------------------------------------------------------------------------
void livre_facture_widget::treat_livre_facture_selected_event(int p_row)
{
  cout << "QtEvent :: Livre_facture selected at row " << p_row << endl ;
  m_fichier_client.treat_livre_facture_selected_event();
}

//------------------------------------------------------------------------------
void livre_facture_widget::set_enable(bool p_enable)
{
  m_livre_id_field->setEnabled(p_enable);
  m_start_date_field->setEnabled(p_enable);
  m_end_date_field->setEnabled(p_enable);

  clear_livre_facture_information();

  m_delete_livre_facture_button->setEnabled(false);
  m_modify_livre_facture_button->setEnabled(false);
  m_non_attributed_facture_widget->set_enabled(false);

  m_livre_facture_table->clearContents();
  if(p_enable)
    {
      treat_livre_facture_id_modif_event();
    }
}



//EOF
