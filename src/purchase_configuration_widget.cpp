#include "purchase_configuration_widget.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <iostream>
#include "fichier_client.h"

//------------------------------------------------------------------------------
purchase_configuration_widget::purchase_configuration_widget(fichier_client & p_fichier_client,QWidget * p_parent):
  QWidget(p_parent),
  m_brand_name_field(NULL),
  m_brand_list_table(NULL),
  m_create_brand_button(NULL),
  m_delete_brand_button(NULL),
  m_modify_brand_button(NULL),
  m_type_name_field(NULL),
  m_type_list_table(NULL),
  m_create_type_button(NULL),
  m_delete_type_button(NULL),
  m_modify_type_button(NULL),
  m_fichier_client(p_fichier_client)
{
  QHBoxLayout * l_main_layout = new QHBoxLayout(this);

  QGroupBox * l_brand_group_box = new QGroupBox(tr("Marque"));

  QVBoxLayout *l_brand_layout = new QVBoxLayout();
  l_brand_group_box->setLayout(l_brand_layout);

  QHBoxLayout *l_brand_information_layout = new QHBoxLayout();
  l_brand_layout->addLayout(l_brand_information_layout);

  l_brand_information_layout->addWidget(new QLabel(tr("Marque")+" :"));

  m_brand_name_field = new QLineEdit("");

  l_brand_information_layout->addWidget(m_brand_name_field);
  connect(m_brand_name_field,SIGNAL(textEdited(const QString&)),this, SLOT(treat_brand_criteria_modification_event()));

  l_brand_information_layout->addStretch();
 
  l_brand_layout->addWidget(new QLabel(tr("Marques possibles pour les achats")+" :"));

  m_brand_list_table = new named_item_list_table<marque>("Marque");
  l_brand_layout->addWidget(m_brand_list_table);
  connect(m_brand_list_table,SIGNAL(cellClicked (int, int)),this, SLOT(treat_brand_selected_event()));
  connect(m_brand_list_table,SIGNAL(itemSelectionChanged()),this, SLOT(treat_brand_selection_changed_event()));

  m_create_brand_button = new QPushButton(tr("&Create"));
  m_create_brand_button->setEnabled(false);
  connect(m_create_brand_button,SIGNAL(clicked()),this,SLOT(treat_create_brand_event()));
 
  m_delete_brand_button = new QPushButton(tr("&Delete"));
  m_delete_brand_button->setEnabled(false);
  connect(m_delete_brand_button,SIGNAL(clicked()),this,SLOT(treat_delete_brand_event()));
 
  m_modify_brand_button = new QPushButton(tr("&Modify"));
  m_modify_brand_button->setEnabled(false);
  connect(m_modify_brand_button,SIGNAL(clicked()),this,SLOT(treat_modify_brand_event()));

  QHBoxLayout *l_brand_button_layout = new QHBoxLayout();
  l_brand_layout->addLayout(l_brand_button_layout);
 
  l_brand_button_layout->addWidget(m_create_brand_button);
  l_brand_button_layout->addWidget(m_delete_brand_button);
  l_brand_button_layout->addWidget(m_modify_brand_button);

  l_main_layout->addWidget(l_brand_group_box);

  QGroupBox * l_type_group_box = new QGroupBox(tr("Type"));

  QVBoxLayout *l_type_layout = new QVBoxLayout();
  l_type_group_box->setLayout(l_type_layout);

  QHBoxLayout *l_type_information_layout = new QHBoxLayout();
  l_type_layout->addLayout(l_type_information_layout);

  l_type_information_layout->addWidget(new QLabel(tr("Type")+" :"));

  m_type_name_field = new QLineEdit("");

  l_type_information_layout->addWidget(m_type_name_field);
  connect(m_type_name_field,SIGNAL(textEdited(const QString&)),this, SLOT(treat_type_criteria_modification_event()));

  l_type_information_layout->addStretch();
 
  l_type_layout->addWidget(new QLabel(tr("Types possibles pour les achats")+" :"));

  m_type_list_table = new named_item_list_table<type_achat>("Type");
  l_type_layout->addWidget(m_type_list_table);
  connect(m_type_list_table,SIGNAL(cellClicked (int, int)),this, SLOT(treat_type_selected_event()));
  connect(m_type_list_table,SIGNAL(itemSelectionChanged()),this, SLOT(treat_type_selection_changed_event()));

  m_create_type_button = new QPushButton(tr("&Create"));
  m_create_type_button->setEnabled(false);
  connect(m_create_type_button,SIGNAL(clicked()),this,SLOT(treat_create_type_event()));
 
  m_delete_type_button = new QPushButton(tr("&Delete"));
  m_delete_type_button->setEnabled(false);
  connect(m_delete_type_button,SIGNAL(clicked()),this,SLOT(treat_delete_type_event()));
 
  m_modify_type_button = new QPushButton(tr("&Modify"));
  m_modify_type_button->setEnabled(false);
  connect(m_modify_type_button,SIGNAL(clicked()),this,SLOT(treat_modify_type_event()));

  QHBoxLayout *l_type_button_layout = new QHBoxLayout();
  l_type_layout->addLayout(l_type_button_layout);
 
  l_type_button_layout->addWidget(m_create_type_button);
  l_type_button_layout->addWidget(m_delete_type_button);
  l_type_button_layout->addWidget(m_modify_type_button);

  l_main_layout->addWidget(l_type_group_box);
}

//------------------------------------------------------------------------------
void purchase_configuration_widget::set_enable(bool p_enable)
{
  m_brand_name_field->setEnabled(p_enable);
  clear_brand_information();

  m_create_brand_button->setEnabled(false);
  m_delete_brand_button->setEnabled(false);
  m_modify_brand_button->setEnabled(false);

  m_brand_list_table->clearContents();

  if(p_enable)
    {
      treat_brand_criteria_modification_event();
    }

  m_type_name_field->setEnabled(p_enable);
  clear_type_information();

  m_create_type_button->setEnabled(false);
  m_delete_type_button->setEnabled(false);
  m_modify_type_button->setEnabled(false);

  m_type_list_table->clearContents();

  if(p_enable)
    {
      treat_type_criteria_modification_event();
    }

}

// Interactions with brand information
//------------------------------------------------------------------------------
void purchase_configuration_widget::clear_brand_information(void)
{
  m_brand_name_field->setText("");
}

//------------------------------------------------------------------------------
void purchase_configuration_widget::set_brand_name(const std::string & p_name)
{
  m_brand_name_field->setText(p_name.c_str());
}

//------------------------------------------------------------------------------
const std::string purchase_configuration_widget::get_brand_name(void)const
{
  return m_brand_name_field->text().toStdString();
}

// Interactions with brand list
//------------------------------------------------------------------------------
bool purchase_configuration_widget::is_brand_selection_empty(void)const
{
  return m_brand_list_table->selectedItems().isEmpty();
}

//------------------------------------------------------------------------------
uint32_t purchase_configuration_widget::get_selected_brand_id(void)const
{
  return m_brand_list_table->get_selected_item_id(m_brand_list_table->currentRow());
}

//------------------------------------------------------------------------------
void purchase_configuration_widget::set_brand_list(std::vector<marque> & p_list)
{
  m_brand_list_table->update(p_list);  
}

//------------------------------------------------------------------------------
void purchase_configuration_widget::set_brand_list_enabled(bool p_enable)
{
  m_brand_list_table->setEnabled(p_enable);
}

// Interactions with brand actions
//------------------------------------------------------------------------------
void purchase_configuration_widget::set_create_brand_enabled(bool p_enable)
{
  m_create_brand_button->setEnabled(p_enable);
}

//------------------------------------------------------------------------------
void purchase_configuration_widget::set_delete_brand_enabled(bool p_enable)
{
  m_delete_brand_button->setEnabled(p_enable);
}

//------------------------------------------------------------------------------
void purchase_configuration_widget::set_modify_brand_enabled(bool p_enable)
{
  m_modify_brand_button->setEnabled(p_enable);
}

//------------------------------------------------------------------------------
void purchase_configuration_widget::set_modify_brand_action_name(const std::string & p_name)
{
  m_modify_brand_button->setText(p_name.c_str());
}

// Interactions with type information
//------------------------------------------------------------------------------
void purchase_configuration_widget::clear_type_information(void)
{
  m_type_name_field->setText("");
}
//------------------------------------------------------------------------------
void purchase_configuration_widget::set_type_name(const std::string & p_name)
{
  m_type_name_field->setText(p_name.c_str());
}

//------------------------------------------------------------------------------
const std::string purchase_configuration_widget::get_type_name(void)const
{
  return m_type_name_field->text().toStdString();
}

// Interactions with type list
//------------------------------------------------------------------------------
bool purchase_configuration_widget::is_type_selection_empty(void)const
{
  return m_type_list_table->selectedItems().isEmpty();
}

//------------------------------------------------------------------------------
uint32_t purchase_configuration_widget::get_selected_type_id(void)const
{
  return m_type_list_table->get_selected_item_id(m_type_list_table->currentRow());
}

//------------------------------------------------------------------------------
void purchase_configuration_widget::set_type_list(std::vector<type_achat> & p_list)
{
  m_type_list_table->update(p_list);  
}

//------------------------------------------------------------------------------
void purchase_configuration_widget::set_type_list_enabled(bool p_enable)
{
  m_type_list_table->setEnabled(p_enable);
}

// Interactions with type actions
//------------------------------------------------------------------------------
void purchase_configuration_widget::set_create_type_enabled(bool p_enable)
{
  m_create_type_button->setEnabled(p_enable);
}

//------------------------------------------------------------------------------
void purchase_configuration_widget::set_delete_type_enabled(bool p_enable)
{
  m_delete_type_button->setEnabled(p_enable);
}

//------------------------------------------------------------------------------
void purchase_configuration_widget::set_modify_type_enabled(bool p_enable)
{
  m_modify_type_button->setEnabled(p_enable);
}

//------------------------------------------------------------------------------
void purchase_configuration_widget::set_modify_type_action_name(const std::string & p_name)
{
  m_modify_type_button->setText(p_name.c_str());
}


// Brand information related events
//------------------------------------------------------------------------------
void purchase_configuration_widget::treat_brand_criteria_modification_event(void)
{
  std::cout << "QtEvent::purchase_configuration brand name modification" << std::endl ;
  m_fichier_client.treat_purchase_configuration_brand_name_modif_event();
}

// Brand list related events
//------------------------------------------------------------------------------
void purchase_configuration_widget::treat_brand_selected_event(void)
{
  std::cout << "QtEvent::purchase_configuration brand row selected " << std::endl ;
  m_fichier_client.treat_purchase_configuration_brand_selected_event();
}

//------------------------------------------------------------------------------
void purchase_configuration_widget::treat_brand_selection_changed_event(void)
{
  std::cout << "QtEvent::purchase_configuration brand row selection changed " << std::endl ;
  if(m_brand_list_table->selectedItems().isEmpty())
    {
      m_fichier_client.treat_purchase_configuration_no_more_brand_selected_event();
    }
}

// Brand actions related events
//------------------------------------------------------------------------------
void purchase_configuration_widget::treat_create_brand_event(void)
{
  std::cout << "QtEvent::purchase_configuration Create brand button clicked" << std::endl ;
  m_fichier_client.treat_purchase_configuration_create_brand_event();
}

//------------------------------------------------------------------------------
void purchase_configuration_widget::treat_delete_brand_event(void)
{
  std::cout << "QtEvent::purchase_configuration Delete brand button clicked" << std::endl ;
  m_fichier_client.treat_purchase_configuration_delete_brand_event();
}

//------------------------------------------------------------------------------
void purchase_configuration_widget::treat_modify_brand_event(void)
{
  std::cout << "QtEvent::purchase_configuration Modify brand button clicked" << std::endl ;
  m_fichier_client.treat_purchase_configuration_modify_brand_event();
}

// Type information related events
//------------------------------------------------------------------------------
void purchase_configuration_widget::treat_type_criteria_modification_event(void)
{
  std::cout << "QtEvent::purchase configuration type name modification" << std::endl ;
  m_fichier_client.treat_purchase_configuration_type_name_modif_event();
}
// Type list related events
//------------------------------------------------------------------------------
void purchase_configuration_widget::treat_type_selected_event(void)
{
  std::cout << "QtEvent::purchase_configuration type row selected " << std::endl ;
  m_fichier_client.treat_purchase_configuration_type_selected_event();
}

//------------------------------------------------------------------------------
void purchase_configuration_widget::treat_type_selection_changed_event(void)
{
  std::cout << "QtEvent::purchase_configuration type row selection changed " << std::endl ;
  if(m_type_list_table->selectedItems().isEmpty())
    {
      m_fichier_client.treat_purchase_configuration_no_more_type_selected_event();
    }
}

// Type list action events
//------------------------------------------------------------------------------
void purchase_configuration_widget::treat_create_type_event(void)
{
  std::cout << "QtEvent::purchase_configuration Create type button clicked" << std::endl ;
  m_fichier_client.treat_purchase_configuration_create_type_event();
}

//------------------------------------------------------------------------------
void purchase_configuration_widget::treat_delete_type_event(void)
{
  std::cout << "QtEvent::purchase_configuration Delete type button clicked" << std::endl ;
  m_fichier_client.treat_purchase_configuration_delete_type_event();
}

//------------------------------------------------------------------------------
void purchase_configuration_widget::treat_modify_type_event(void)
{
  std::cout << "QtEvent::purchase_configuration Modify type button clicked" << std::endl ;
  m_fichier_client.treat_purchase_configuration_modify_type_event();
}

//EOF
