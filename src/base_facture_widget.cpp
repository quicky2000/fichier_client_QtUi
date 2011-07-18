#include "base_facture_widget.h"
#include "fichier_client_QtUi_utils.h"
#include "my_date_widget.h"
#include "facture.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <sstream>
#include <iostream>

//------------------------------------------------------------------------------
base_facture_widget::base_facture_widget(QWidget * p_parent):
  QWidget(p_parent),
  m_layout(NULL),
  m_date_field(NULL),
  m_livre_facture_id_field(NULL),
  m_facture_reference_field(NULL),
  m_status_field(NULL)
{
  m_layout = new QHBoxLayout(this);

  // Date
  m_layout->addWidget(new QLabel(tr("Date")+" :"));
  m_date_field = new my_date_widget();
  m_layout->addWidget(m_date_field);
  connect(m_date_field,SIGNAL(date_ok()),this,SLOT(date_entered()));
   
  // Livre facture
  m_layout->addWidget(new QLabel(tr("Livre Facture")+" :"));
  m_livre_facture_id_field = new QComboBox(this);
  m_livre_facture_id_field->setSizeAdjustPolicy(QComboBox::AdjustToContents);
  m_layout->addWidget(m_livre_facture_id_field);
  //  connect(m_livre_facture_id_field,SIGNAL(currentIndexChanged (int)),this,SLOT(livre_facture_selected(int)));
  connect(m_livre_facture_id_field,SIGNAL(activated (int)),this,SLOT(livre_facture_selected(int)));
   
  // Facture reference
  m_layout->addWidget(new QLabel(tr("Facture reference")+" :"));
  m_facture_reference_field = new QComboBox(this);
  m_facture_reference_field->setSizeAdjustPolicy(QComboBox::AdjustToContents);
  m_layout->addWidget(m_facture_reference_field);
  connect(m_facture_reference_field,SIGNAL(activated (int)),this,SLOT(facture_ref_selected(int))); 

  // Facture status
  m_layout->addWidget(new QLabel(tr("Status")+" :"));
  m_status_field = new QComboBox(this);
  m_status_field->setSizeAdjustPolicy(QComboBox::AdjustToContents);
  connect(m_status_field, SIGNAL(activated (int)),this,SLOT(status_selected(int)));
  m_layout->addWidget(m_status_field);
}

//------------------------------------------------------------------------------
void base_facture_widget::set_date(const std::string &p_date)
{
  m_date_field->set_iso_date(p_date);
}

//------------------------------------------------------------------------------
void base_facture_widget::set_enabled(bool p_enabled)
{
  m_date_field->setEnabled(p_enabled);;
  m_livre_facture_id_field->setEnabled(p_enabled);
  m_facture_reference_field->setEnabled(p_enabled);
  m_status_field->setEnabled(p_enabled);
}

//------------------------------------------------------------------------------
QHBoxLayout * base_facture_widget::get_layout(void)
{
  return m_layout;
}

//------------------------------------------------------------------------------
void base_facture_widget::date_entered(void)
{
  std::cout << "QtEvent::base_facture_widget::date_entered : \"" << m_date_field->get_iso_date() << "\"" << std::endl ;
  emit new_date_entered();
}

//------------------------------------------------------------------------------
void base_facture_widget::facture_ref_selected(int p_index)
{
  std::cout << "QtEvent::base_facture_widget::Facture_reference_selected index " << p_index << std::endl;
  uint32_t l_ref = get_facture_reference();
  if(l_ref)
    {
      std::cout << "QtEvent::base_facture_widget::Facture_reference_selected " << l_ref << std::endl;
    }
  emit new_facture_ref_selected();
}

//------------------------------------------------------------------------------
void base_facture_widget::livre_facture_selected(int p_index)
{
  std::cout << "QtEvent::base_facture_widget::livre_facture_selected index " << p_index << std::endl;
  uint32_t l_ref = get_livre_facture_id();
  if(l_ref)
    {
      std::cout << "QtEvent::base_facture_widget::Livre_facture selected " << l_ref << std::endl;
    }
  emit new_livre_facture_selected();
}

//------------------------------------------------------------------------------
void base_facture_widget::status_selected(int p_index)
{
  std::cout << "QtEvent::base_facture_widget::status_selected index " << p_index << std::endl;
  const facture_status * l_ptr_facture_status = get_facture_status();
  if(l_ptr_facture_status)
    {
      std::cout << "QtEvent::base_facture_widget::status selected " << *l_ptr_facture_status << std::endl;
    }
  emit new_status_selected();
}

//------------------------------------------------------------------------------
void base_facture_widget::clear_date(void)
{
  m_date_field->setText("");
}

//------------------------------------------------------------------------------
bool base_facture_widget::is_date_complete(void)const
{
  return m_date_field->is_complete();
}

//------------------------------------------------------------------------------
bool base_facture_widget::is_date_empty(void)const
{
  return m_date_field->is_empty();
}

//------------------------------------------------------------------------------
const std::string base_facture_widget::get_iso_date(void)const
{
  assert(m_date_field->is_complete());
  return m_date_field->get_iso_date();
}

//------------------------------------------------------------------------------
uint32_t base_facture_widget::get_livre_facture_id(int p_index)const
{
  uint32_t l_result = 0;
  // Check if something is selected
  if(p_index>0 || (!p_index && m_livre_facture_ids.size() == 1))
    {
      uint32_t l_real_index = (m_livre_facture_ids.size() > 1 ? p_index - 1 : 0);
      assert(l_real_index < m_livre_facture_ids.size());
      l_result = m_livre_facture_ids[l_real_index];
    }
  return l_result;
}

//------------------------------------------------------------------------------
uint32_t base_facture_widget::get_facture_reference(int p_index)const
{
  uint32_t l_result = 0;
  // Check if something is selected
  if(p_index>0 || (!p_index && m_facture_references.size() == 1))
    {
      uint32_t l_real_index = (m_facture_references.size() > 1 ? p_index - 1 : 0);
      assert(l_real_index < m_facture_references.size());
      l_result = m_facture_references[l_real_index];
    }
  return l_result;
}

//------------------------------------------------------------------------------
const facture_status * base_facture_widget::get_facture_status(int p_index)const
{
  const facture_status * l_result = NULL;
    // Check if something is selected
  if(p_index>0 || (!p_index && m_status.size() == 1))
    {
      uint32_t l_real_index = (m_status.size() > 1 ? p_index - 1 : 0);
      assert(l_real_index < m_status.size());
      l_result = &(m_status[l_real_index]);
    }
  return l_result;
}


//------------------------------------------------------------------------------
uint32_t base_facture_widget::get_livre_facture_id(void)const
{
  return get_livre_facture_id(m_livre_facture_id_field->currentIndex());
}

//------------------------------------------------------------------------------
uint32_t base_facture_widget::get_facture_reference(void)const
{
  return get_facture_reference(m_facture_reference_field->currentIndex());
}


//------------------------------------------------------------------------------
const facture_status * base_facture_widget::get_facture_status(void)const
{
  return get_facture_status(m_status_field->currentIndex());
}

//------------------------------------------------------------------------------
void base_facture_widget::set_combo_box_content(QComboBox * p_combo_box,std::vector<uint32_t> & p_current,const std::vector<uint32_t> & p_list)
{
  fichier_client_QtUi_utils::clear_combo_box_content(p_combo_box);
  p_current.clear();
  if(p_list.size() > 1)
    {
      p_combo_box->addItem("");
    }

  std::vector<uint32_t>::const_iterator l_iter = p_list.begin();
  std::vector<uint32_t>::const_iterator l_iter_end = p_list.end();
  while(l_iter != l_iter_end)
    {
      QString l_ref;
      l_ref.setNum(*l_iter);
      p_combo_box->addItem(l_ref);
      p_current.push_back(*l_iter);
      ++l_iter;
    }
  if(p_combo_box->count())
    {
      p_combo_box->setCurrentIndex(0);
    }
}

//------------------------------------------------------------------------------
void base_facture_widget::set_allowed_facture_ref(const std::vector<uint32_t> & p_list)
{
  set_combo_box_content(m_facture_reference_field,m_facture_references,p_list);
}

//------------------------------------------------------------------------------
void base_facture_widget::set_allowed_livre_ids(const std::vector<uint32_t> & p_livre_ids)
{
  set_combo_box_content(m_livre_facture_id_field,m_livre_facture_ids,p_livre_ids);
}

//------------------------------------------------------------------------------
void base_facture_widget::set_livre_id(uint32_t p_id)
{
  fichier_client_QtUi_utils::select_combo_box_content(p_id,m_livre_facture_id_field,m_livre_facture_ids);
}

//------------------------------------------------------------------------------
void base_facture_widget::set_status_list(const std::vector<facture_status> & p_status_list)
{
  fichier_client_QtUi_utils::set_combo_box_named_list(m_status_field,m_status,p_status_list);
}

//------------------------------------------------------------------------------
void base_facture_widget::set_status(uint32_t p_id)
{
  fichier_client_QtUi_utils::select_combo_box_named_content(p_id,m_status_field,m_status);
}

//------------------------------------------------------------------------------
void base_facture_widget::set_reference(uint32_t p_ref)
{
  fichier_client_QtUi_utils::select_combo_box_content(p_ref,m_facture_reference_field,m_facture_references);
}

//EOF
