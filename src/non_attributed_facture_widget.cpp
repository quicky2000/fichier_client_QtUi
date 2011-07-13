#include "non_attributed_facture_widget.h"
#include "fichier_client_QtUi_utils.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QComboBox>

//------------------------------------------------------------------------------
non_attributed_facture_widget::non_attributed_facture_widget(QWidget * p_parent):
  base_facture_widget(p_parent), 
  m_reason_field(NULL)
{
  this->get_layout()->addWidget(new QLabel(tr("Raison")+" :"));
  m_reason_field = new QComboBox(this);
  m_reason_field->setSizeAdjustPolicy(QComboBox::AdjustToContents);
  connect(m_reason_field, SIGNAL(activated (int)),this,SLOT(treat_reason_selected_event(int)));
  this->get_layout()->addWidget(m_reason_field);
}

//------------------------------------------------------------------------------
void non_attributed_facture_widget::set_enabled(bool p_enabled)
{
  base_facture_widget::set_enabled(p_enabled);
  m_reason_field->setEnabled(p_enabled);
}

//------------------------------------------------------------------------------
void non_attributed_facture_widget::treat_reason_selected_event(int)
{
  std::cout << "QtEvent::reason selected" << std::endl ;
  emit reason_selected();
}

//------------------------------------------------------------------------------
const facture_reason * non_attributed_facture_widget::get_facture_reason(void)const
{
  int l_index = m_reason_field->currentIndex();
  const facture_reason * l_result = NULL;
    // Check if something is selected
  if(l_index > 0 || (!l_index && m_reasons.size() == 1))
    {
      uint32_t l_real_index = (m_reasons.size() > 1 ? l_index - 1 : 0);
      assert(l_real_index < m_reasons.size());
      l_result = &(m_reasons[l_real_index]);
    }
  return l_result;
}

//------------------------------------------------------------------------------
void non_attributed_facture_widget::set_reason_list(const std::vector<facture_reason> & p_reason_list)
{
  fichier_client_QtUi_utils::clear_combo_box_content(m_reason_field);
  m_reasons.clear();
  if(p_reason_list.size() > 1)
    {
      m_reason_field->addItem("");
    }
  std::vector<facture_reason>::const_iterator l_iter = p_reason_list.begin();
  std::vector<facture_reason>::const_iterator l_iter_end = p_reason_list.end();
  while(l_iter != l_iter_end)
    {
      m_reason_field->addItem(l_iter->getName().c_str());
      m_reasons.push_back(*l_iter);
      ++l_iter;
    }
  if(m_reason_field->count())
    {
      m_reason_field->setCurrentIndex(0);
    }
}

//------------------------------------------------------------------------------
void non_attributed_facture_widget::set_reason(uint32_t p_id)
{
  if(m_reasons.size()>1)
    {
      std::vector<facture_reason>::const_iterator l_iter = m_reasons.begin();
      std::vector<facture_reason>::const_iterator l_iter_end = m_reasons.end();
      uint32_t l_index = 1;
      while(l_iter != l_iter_end && l_iter->get_id() != p_id)
	{
	  ++l_iter;
	  ++l_index;
	}  
      assert(l_iter->get_id() == p_id);
      m_reason_field->setCurrentIndex(l_index);
    }
}


//EOF
